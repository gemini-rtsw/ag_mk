/*
*   FILENAME
*   Put file name here
*
*   FUNCTION NAME(S)
*   agSeqGmMoveCAD  - simulate behaviour of GMOS WFS move command
*   agSeqGmSimulate - simulate behaviour of GMOS WFS probe
*   agSeqGmStopCAD  - simulate the STOP CAD
*   agSeqGmFollowCAD - simulate the Follow CAD
*   agSeqGmToleranceCAD - simulate the tolerance command
*   agSeqInsActiveC - combine CAR status and messages to generate activeC
*   agSeqInsProbeC  - combine CAR status and messages to generate probeC
*
*/
/* *INDENT-OFF* */
/*
 * $Log: agSeqGmosSimulate.c,v $
 * Revision 1.5  2003/03/13 00:00:16  cjm
 * Set in position false if probe parked - like the real GMOS
 *
 * Revision 1.4  2003/02/07 17:02:05  cjm
 * new code to compute the park state of the probe
 *
 * Revision 1.3  2001/09/20 15:12:14  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.2  2001/09/10 12:54:03  cjm
 * Set new followS record state
 *
 * Revision 1.1  2001/06/20 18:27:22  gemvx
 * Moved file from directory one level up
 *
 * Revision 1.4  2001/01/24 08:43:21  cjm
 * Include string.h to avoid warnings from power PC compiler
 *
 * Revision 1.3  2000/07/21 10:33:41  cjm
 * Add code to simulate the probeState record
 *
 * Revision 1.2  1999/10/15 12:52:21  cjm
 * Using subsys versions of TCS header files
 *
 * Revision 1.1  1999/10/14 14:20:56  cjm
 * Code for GMOS simulator
 *
 */
/* *INDENT-ON* */

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


/* Forward declarations */
int agNotEmptyString (char *s) ;

/*+
 *   Function name:
 *   agSeqGmSimulate
 *
 *   Purpose:
 *   Simulate behaviour of GMOS WFS probe
 *
 *   Description:
 *   The routine models the X and Y motions of the GMOS probe by a servo
 *   algorithm. When the probe is in position, appropriate flags are set 
 *   to signal that the probe is tracking.
 *
 *   Invocation:
 *   agSeqGmSimulate (pgsub)
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

long agSeqGmSimulate (struct genSubRecord *pgsub)
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
    xvel = 0.0 ;
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
    yvel = 0.0 ;

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
*  if the probe is parked. This is exactly what GMOS does. The reason
*  for this is that GMOS doesn't actually provide an inPosition flag
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

long agSeqGmParkState (struct genSubRecord *pgsub) 
{

 *(long *)pgsub->vala = ParkState ;
  return 0 ;

}


/*+
 *   Function name:
 *   agSeqGmParkCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of GMOS WFS park command
 *
 *   Description:
 *   Inputs are copied to outputs on receipt of a valid start directive.
 *   The inputs are the default park position and the outputs go to the
 *   move command.
 *
 *   Invocation:
 *   agSeqGmParkCAD (pcad)
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

long agSeqGmParkCAD (struct cadRecord *pcad)

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
 *   agSeqGmStopCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of GMOS WFS stop command
 *
 *   Description:
 *   Simply set the StateProbe variable to STOPPED. The simulation of the
 *   probe movement does the rest.
 *
 *   Invocation:
 *   agSeqGmStopCAD (pcad)
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

long agSeqGmStopCAD (struct cadRecord *pcad)

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
 *   agSeqGmFollowCAD 
 *
 *   Purpose:
 *   Provide a minimal implementation of GMOS WFS follow command
 *
 *   Description:
 *   Simply set the StateProbe variable to FOLLOWING. The simulation of the
 *   probe movement does the rest.
 *
 *   Invocation:
 *   agSeqGmFollowCAD (pcad)
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

long agSeqGmFollowCAD (struct cadRecord *pcad)

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
 *   agSeqGmMoveCAD 
 *
 *   Purpose:
 *   Implement the GMOS WFS move command
 *
 *   Description:
 *   Check that the x and y position demands are within range and then pass
 *   the demand positions to the WFS simulation code.
 *
 *   Invocation:
 *   agSeqGmMoveCAD(pcad)
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

long agSeqGmMoveCAD (struct cadRecord *pcad)

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
 *   agSeqGmToleranceCAD 
 *
 *   Purpose:
 *   Implement the GMOS WFS tolerance command
 *
 *   Description:
 *   Check that a tolernace has been given then place it on output links
 *   The input tolerance is used for both X and Y positioning accuracy. The
 *   focus tolerance which is also received is not used in GMOS.
 *
 *   Invocation:
 *   agSeqGmToleranceCAD(pcad)
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

long agSeqGmToleranceCAD (struct cadRecord *pcad)

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


/*+
 *   Function name:
 *   agSeqInsActiveC
 *
 *   Purpose:
 *   Combine lower level CAR status to form activeC
 *
 *   Description:
 *   At present just copy through the low level values 
 *
 *   Invocation:
 *   agSeqInsActiveC(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqInsActiveC (struct genSubRecord *pgsub) 

{
/* Copy status */
  *(long *)pgsub->valb = *(long *)pgsub->b ;

/* Check for error message */
  if (*(long *)pgsub->b == menuCarstatesERROR) {

    if (agNotEmptyString(pgsub->a))
      strcpy (pgsub->vala, pgsub->a) ;
    else
      strcpy (pgsub->vala, "Unspecified action error") ;
  } else {
    strcpy (pgsub->vala, " ") ;
  }
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqInsProbeC
 *
 *   Purpose:
 *   Combine lower level CAR status to form probeC
 *
 *   Description:
 *   Combine the error status and messages from the low level CAR records.
 *
 *   Invocation:
 *   agSeqInsProbeC(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqInsProbeC (struct genSubRecord *pgsub) 

{
  long simC ;             /* simC CAR value */
  long softC ;            /* softC CAR value */
  long actVal ;           /* Resultant activeC CAR value */
  char simCMess[MAX_STRING_SIZE] ;
  char softCMess[MAX_STRING_SIZE] ;
  char actMess[MAX_STRING_SIZE] ;

/* Set defualt output */
  actVal = menuCarstatesIDLE ;
  strcpy (actMess, " ");

/* Fetch all input data */
  strcpy (simCMess, pgsub->a) ;
  simC = *(long *)pgsub->b ;
  strcpy (softCMess, pgsub->c) ;
  softC = *(long *)pgsub->d ;

/* Now combine the CAR values */
  if (simC == menuCarstatesERROR || softC == menuCarstatesERROR) {
    actVal = menuCarstatesERROR ;
    if (simC == menuCarstatesERROR ) {
      if (agNotEmptyString(simCMess)) {
        strcpy (actMess, simCMess) ;
      } else {
        strcpy (actMess, "Unspecified error from probe");
      }
    } else if (softC == menuCarstatesERROR) {
      if (agNotEmptyString (softCMess)) {
        strcpy (actMess, softCMess) ;
      } else {
        strcpy (actMess, "Unspecified command error") ;
      } 
    }
  }

  if (simC == menuCarstatesBUSY || softC == menuCarstatesBUSY) {
    actVal = menuCarstatesBUSY ;
    strcpy (actMess, " ") ;
  }

/* Write outputs */
  strcpy ((char *)pgsub->vala, actMess) ;
  *(long *)pgsub->valb = actVal ;

  return 0 ;

}

