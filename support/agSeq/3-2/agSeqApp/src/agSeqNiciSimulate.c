/*
*   FILENAME
*   Put file name here
*
*   FUNCTION NAME(S)
*   agSeqNiciMoveCAD  - simulate behaviour of NICI WFS move command
*   agSeqNiciSimulate - simulate behaviour of NICI WFS probe
*   agSeqNiciStopCAD  - simulate the STOP CAD
*   agSeqNiciFollowCAD - simulate the Follow CAD
*   agSeqNiciGenericCAD - simulate a generic CAD
*   agSeqNiciToleranceCAD - simulate the tolerance command
*
*/

#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <epicsStdioRedirect.h>
#include <epicsStdlib.h>
#include <epicsEvent.h>
#include <epicsPrint.h>
#include <iocsh.h>
#include <string.h>
#include <ctype.h>

#include <dbDefs.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <menuCarstates.h>
#include <cad.h>

#include "tcsSubsysDecode.h"
#include "tcsSubsysCadSupport.h"
#include "tcsServo.h"
#include "timeLib.h"

#define STOPPED 0
#define MOVING 1
#define FOLLOWING 2

/* Guide probe state */
static int StateProbe ;

/* Guide probe parked state */
static int ParkState = 0 ;            /* Unparked */

/* Probe position */
static double x ;
static double y ;

/* Demand position from MOVE command */
static double xtarget ;
static double ytarget ;


/*+
 *   Function name:
 *   agSeqNiciSimulate
 *
 *   Purpose:
 *   Simulate behaviour of NICI WFS probe
 *
 *   Description:
 *   The routine models the X and Y motions of the NICI probe by a servo
 *   algorithm. When the probe is in position, appropriate flags are set 
 *   to signal that the probe is tracking.
 *
 *   Invocation:
 *   agSeqNiciSimulate (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *) Pointer to pgsub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *
 *   a => default startup x position (mm)
 *   b => default startup y position (mm)
 *   c => maximum probe velocity (mm/s)
 *   d => position tolerance (mm)
 *   j => Input demand array
 *
 *   Epics outputs:
 *   
 *   vala => current x (mm)
 *   valb => current y (mm)
 *   valc => x error (mm)
 *   vald => y error (mm)
 *   vale => probe state IDLE, MOVING or TRACKING
 *   valf => follow state i.e. TRACKING or NOT
 *   valg => in Position status
 *   valh => trackid
 *   vali => CAR status
 *   valj => disable or enable following processing chain
 *
 *-
 */

long agSeqNiciSimulate (struct genSubRecord *pgsub)
{
  static int first = TRUE ;

  static double tlast ;   /* Time at last entry */
  static double xlast ;   /* Previous X demand */
  static double ylast ;   /* Previous Y demand */
  static double xvel ;    /* Current X probe velocity */
  static double yvel ;    /* Current Y probe velocity */
  static double xerr ;    /* Current X probe error */
  static double yerr ;    /* Current y probe error */

  static struct ServoState servoStateX ;
  static struct ServoState servoStateY ;
  static struct ServoConfig servoConfigX ;
  static struct ServoConfig servoConfigY ;

  static int inPosition = FALSE ;
  static int inPositionX ;
  static int inPositionY ;

  static int substat ;    /* Subsystem status */
  static double trackid ; /* Current track id */
  static int lastInPos ;  /* Previous value of inPosition */

  unsigned long arraySize ; /* No. of elements in demand array */ 
  double xdemand ;       /* X demand position */
  double ydemand ;       /* Y demand position */
  double xdemandv ;      /* X demand velocity */
  double ydemandv ;      /* Y demand velocity */
  double xnow ;          /* Current X position */
  double ynow ;          /* Current Y position */
  double newtrack ;      /* Track id of demand */
  double tappl ;         /* Time for which demands are correct */
  double now ;           /* Current time */
  double AGSdemand[6] ;  /* Demand data array from A&G */
  double xperr, yperr ;  /* Distances from parked position */

  int stateProbe ;       /* local copy of probe state */
  int newstat ;          /* New system status */
  int linkSelect ;       /* Mask to select links to trigger */

/* Initialise variables on first pass */
  if (first) {
    StateProbe = STOPPED ;
    servoConfigX.dvmax = 12.5 ;
    servoConfigX.gs = 4.0 ;
    servoConfigX.gp = 1.0 ;
    servoConfigX.gi = 0.1 ;
    servoConfigX.pi = 1.0 ;
    servoConfigX.tok = 0.5 ;
    servoStateX.pdtold = *(double *) pgsub->a ;
    servoConfigX.noise = 0.0 ;
    timeNow(&(servoStateX.told)) ;
    servoStateX.told -= 0.05 ;
    servoStateX.tout = servoStateX.told ;
    servoStateX.vd = 0.0 ;
    servoStateX.accum = 0.0 ;
    x = servoStateX.pdtold ;
    xvel = 10.0 ;
    servoConfigY.dvmax = 12.5 ;
    servoConfigY.gs = 4.0 ;
    servoConfigY.gp = 1.0 ;
    servoConfigY.gi = 0.1 ;
    servoConfigY.pi = 1.0 ;
    servoConfigY.tok = 0.5 ;
    servoStateY.pdtold = *(double *) pgsub->b ;
    servoConfigY.noise = 0.0 ;
    timeNow(&(servoStateY.told)) ;
    servoStateY.told -= 0.05 ;
    servoStateY.tout = servoStateY.told ;
    servoStateY.vd = 0.0 ;
    servoStateY.accum = 0.0 ;
    y = servoStateY.pdtold ;
    yvel = 10.0 ;

    newstat = menuCarstatesIDLE ;
    substat = -1 ;
    trackid = 0.0 ;
    lastInPos = TRUE ;
    first = FALSE ;
  }

/* Get a local copy of the probe state in case it is changed elsewhere */
  stateProbe = StateProbe ;

/* Fetch latest velocities and tolerances */
  servoConfigX.vtmax = *(double *)pgsub->c ;
  servoConfigY.vtmax = *(double *)pgsub->c ;
  servoConfigX.pok   = *(double *)pgsub->d ;
  servoConfigY.pok   = *(double *)pgsub->d ;

/* Get demand data array */
  arraySize = pgsub->noj ;
  memcpy (AGSdemand, pgsub->j, arraySize*sizeof(double)) ;
  tappl = AGSdemand[1] ;
  newtrack = AGSdemand[2] ;
  xdemand  = AGSdemand[3] ;
  ydemand  = AGSdemand[4] ;

/* Send demands to the servo */
  timeNow(&now) ;

  xdemandv = 0.0 ;
  ydemandv = 0.0 ;

  if (stateProbe == MOVING) {
    inPositionX = tcsServo(now, xtarget, 0, &servoConfigX, &servoStateX,
                           &x, &xvel) ;
    xerr = xtarget - x ;
    inPositionY = tcsServo(now, ytarget, 0, &servoConfigY, &servoStateY,
                           &y, &yvel) ;
    yerr = ytarget - y ;

  } else if (stateProbe == FOLLOWING) {
    if (tappl > tlast) {
      xdemandv = (xdemand - xlast) / (tappl - tlast) ;
      ydemandv = (ydemand - ylast) / (tappl - tlast) ;
    }
    xnow = xdemand + xdemandv * (now - tappl) ;
    inPositionX = tcsServo(tappl, xnow, 0, &servoConfigX, &servoStateX,
                           &x, &xvel) ;
    xerr = xnow - x ;
    ynow = ydemand + ydemandv * (now - tappl) ;
    inPositionY = tcsServo(tappl, ynow, 0, &servoConfigY, &servoStateY,
                           &y, &yvel) ;
    yerr = ynow - y ;

  } else {
    inPositionX = tcsServo (now, x, 1, &servoConfigX, &servoStateX, &x, &xvel);
    xerr = 0.0 ;
    inPositionY = tcsServo (now, y, 1, &servoConfigY, &servoStateY, &y, &yvel);
    xerr = 0.0 ;

  }

/* Generate in position status */
  inPosition = inPositionX && inPositionY ;

/* Initialise the link selection field. The bits in this field are as follows:
*  bit 0 = Process the in position record
*  bit 1 = Process the track id
*  bit 2 = Process the simC CAR record
*/
  linkSelect = 0;

  if (newtrack != trackid ) {
    trackid = newtrack ;
    inPosition = FALSE ;
    linkSelect += 2 ;
  }

  if (inPosition) {
    newstat = menuCarstatesIDLE ;
    if (stateProbe == MOVING) {
      stateProbe = STOPPED ;
    }
  } else {
    newstat = menuCarstatesBUSY ;
  }

  if (newstat != substat ) {
    substat = newstat ;
    linkSelect += 4 ;
  }

  if (inPosition != lastInPos ) {
    lastInPos = inPosition ;
    linkSelect += 1 ;
  }
 

/* save demands */
  tlast = tappl ;
  xlast = xdemand ;
  ylast = ydemand ;

/* Compute probeState string */
  if (stateProbe == FOLLOWING) {
    strcpy(pgsub->vale, "TRACKING") ;
    *(long *)pgsub->valf = 1 ;
  } else if (stateProbe == MOVING) {
    strcpy(pgsub->vale, "MOVING") ;
    *(long *)pgsub->valf = 0 ;
  } else {
    strcpy (pgsub->vale, "IDLE") ;
    *(long *)pgsub->valf = 0 ;
  }

/* Compute the parked state. Note that we over ride the inPosition state
*  if the probe is parked. This is exactly what NICI does. The reason
*  for this is that NICI doesn't actually provide an inPosition flag
*  at the moment. It calls it inPosition but really it is readyToGuide
*/
  xperr = x - *(double*)pgsub->a ;
  yperr = y - *(double *)pgsub->b;
  if (xperr < 0.0 ) xperr = -xperr ;
  if (yperr < 0.0 ) yperr = -yperr ;
  if (xperr <= servoConfigX.pok && yperr <= servoConfigY.pok){
    ParkState = 1 ;
    inPosition = 0 ;
  } else {
    ParkState = 0 ;
  }

/* Output the results */
  *(double *)pgsub->vala = x ;
  *(double *)pgsub->valb = y ;
  *(double *)pgsub->valc = xerr ;
  *(double *)pgsub->vald = yerr ;
  *(long *)pgsub->valg = inPosition ;
  *(double *)pgsub->valh = trackid ;
  *(long *)pgsub->vali = substat ;
  *(long *)pgsub->valj = linkSelect ;

  return 0 ;
}

/* This routine is only here because we ran out of outputs on the
*  main simulation record
*/

long agSeqNiciParkState (struct genSubRecord *pgsub) 
{

 *(long *)pgsub->vala = ParkState ;
  return 0 ;

}


/*+
 *   Function name:
 *   agSeqNiciParkCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of NICI WFS park command
 *
 *   Description:
 *   Inputs are copied to outputs on receipt of a valid start directive.
 *   The inputs are the default park position and the outputs go to the
 *   move command.
 *
 *   Invocation:
 *   agSeqNiciParkCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *   a => X park position (mm)
 *   b => Y park position (mm)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciParkCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   break ;

   case menuDirectiveSTART :
    
    strcpy (pcad->vala, pcad->a) ;
    strcpy (pcad->valb, pcad->b);
    break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   agSeqNiciStopCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of NICI WFS stop command
 *
 *   Description:
 *   Simply set the StateProbe variable to STOPPED. The simulation of the
 *   probe movement does the rest.
 *
 *   Invocation:
 *   agSeqNiciStopCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciStopCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   break ;

   case menuDirectiveSTART :
    
    StateProbe = STOPPED ;
    break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   agSeqNiciFollowCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of NICI WFS follow command
 *
 *   Description:
 *   Simply set the StateProbe variable to FOLLOWING. The simulation of the
 *   probe movement does the rest.
 *
 *   Invocation:
 *   agSeqNiciFollowCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciFollowCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   break ;

   case menuDirectiveSTART :
    
    StateProbe = FOLLOWING ;
    break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   agSeqNiciGenericCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of NICI command that does nothing
 *
 *   Description:
 *   To prevent dead channels.
 *
 *   Invocation:
 *   agSeqNiciGenericCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciGenericCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   break ;

   case menuDirectiveSTART :
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   agSeqNiciMoveCAD 
 *
 *   Purpose:
 *   Implement the NICI WFS move command
 *
 *   Description:
 *   Check that the x and y position demands are within range and then pass
 *   the demand positions to the WFS simulation code.
 *
 *   Invocation:
 *   agSeqNiciMoveCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => demand X position (mm)
 *      b => demand Y position (mm)
 *      c => minimum X position (mm)
 *      d => maximum X position (mm)
 *      e => minimum Y position (mm)
 *      f => maximum Y position (mm)
 * 
 *   EPICS output paramters:
 *      vala => output written to fields VALA etc.
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciMoveCAD (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  double xmin, xmax ;     /* Permitted range of X (mm) */
  double ymin, ymax ;     /* Permitted range of Y (mm) */
  static double xdem ;    /* Demanded X position */
  static double ydem ;    /* Demanded Y position */

/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

    status = CAD_REJECT ;

/* Make sure an X demand position is specified */
    if (!tcsDcLen(pcad->a)) {
      tcsCsAppendMessage (pcad, "No X demand given") ;
      break ;
    }
    if (tcsDcDouble ("X :", pcad->a, &xdem, pcad)) break ;

/* Now make sure a Y demand position is given */
    if (!tcsDcLen(pcad->b)) {
      tcsCsAppendMessage (pcad, "No Y demand given") ;
      break ;
    }
    if (tcsDcDouble ("Y :", pcad->b, &ydem, pcad)) break ;

/* Now check limits */
   if (tcsDcDouble ("Min. X: ", pcad->c, &xmin, pcad)) break ;
   if (tcsDcDouble ("Max. X: ", pcad->d, &xmax, pcad)) break ;
   if (tcsDcDouble ("Min. Y: ", pcad->e, &ymin, pcad)) break ;
   if (tcsDcDouble ("Max. Y: ", pcad->f, &ymax, pcad)) break ;
   if (xdem < xmin || xdem > xmax ) {
     tcsCsAppendMessage (pcad, "X demand out of range");
     break ;
   }
   if (ydem < ymin || ydem > ymax ) {
     tcsCsAppendMessage (pcad, "Y demand out of range");
     break ;
   }

   status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

/* Copy demanded positions to target positions and set the prove state */
   xtarget = xdem ;
   ytarget = ydem ;
   StateProbe = MOVING ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   agSeqNiciToleranceCAD 
 *
 *   Purpose:
 *   Implement the NICI WFS tolerance command
 *
 *   Description:
 *   Check that a tolernace has been given then place it on output links
 *   The input tolerance is used for both X and Y positioning accuracy. The
 *   focus tolerance which is also received is not used in NICI.
 *
 *   Invocation:
 *   agSeqNiciToleranceCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => X/Y position tolerance (mm)
 *      b => Z position tolerance (mm)
 * 
 *   EPICS output paramters:
 *      vala => X position tolerance 
 *      valb => Y position tolerance 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciToleranceCAD (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static double xtol ;    /* Demanded X position tolerance (mm) */

/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

    status = CAD_REJECT ;

/* Make sure a tolerance is specified */
    if (!tcsDcLen(pcad->a)) {
      tcsCsAppendMessage (pcad, "No tolerance given") ;
      break ;
    }
    if (tcsDcDouble ("Tolerance :", pcad->a, &xtol, pcad)) break ;

   if (xtol < 0.0 || xtol > 1.0 ) {
     tcsCsAppendMessage (pcad, "Tolerance out of range");
     break ;
   }
   status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

   *(double *)pcad->vala = xtol ;
   *(double *)pcad->valb = xtol ;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

epicsRegisterFunction(agSeqNiciSimulate);
epicsRegisterFunction(agSeqNiciParkState);
epicsRegisterFunction(agSeqNiciToleranceCAD);
epicsRegisterFunction(agSeqNiciFollowCAD);
epicsRegisterFunction(agSeqNiciStopCAD);
epicsRegisterFunction(agSeqNiciParkCAD);
epicsRegisterFunction(agSeqNiciMoveCAD);
epicsRegisterFunction(agSeqNiciGenericCAD);
