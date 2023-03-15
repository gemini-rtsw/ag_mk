/*
*   FILENAME
*   agSimulate.c
*
*   FUNCTION NAME(S)
*   agMechSimDump  - print out the current status of a simulator
*   agMechSimFlags - fetch bit flags to show datumed, parked etc.
*   agMechSimInit  - initialise the data needed by the simulator
*   agMechSimPosn  - return simulated mechanism posns
*   agMechSimResp  - simulated PLC response 
*   agMechSimTrack - provide target demands to simulators for tracking
*   agMechSimulate - simulate an A&G mechanism
*   agSimCommand   - set a demand and command for a simulated mechanism
*
*   HISTORY
*   -------
*   26-Feb-2018:       Migrated mutex to OSI                   (rjc)
*/
/* *INDENT-OFF* */
/*
 * $Log: agSimulate.c,v $
 * Revision 1.4  2003/07/09 11:56:00  cjm
 * In simulator give correct PMAC response when following
 *
 * Revision 1.3  2003/03/25 15:05:03  cjm
 * Simulate brakes and amp enabled flags
 *
 * Revision 1.2  2001/08/14 14:00:17  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.1  2000/12/20 13:48:29  cjm
 * Code to simulate a low level A&G mechanism
 *
 */
/* *INDENT-ON* */

#include "ag_define.h"
#include "tcsServo.h"

#define SIM_STOPPED   0
#define SIM_MOVING    1
#define SIM_FOLLOWING 2

#define PLC_IDLE 0
#define PLC_DATUM_IN_PROG 101
#define PLC_PARK_IN_PROG  102  
#define PLC_STOP_IN_PROG  103  
#define PLC_MOVE_IN_PROG  104
#define PLC_FOLLOW_ON     205

static epicsMutexId agSimSemId ;
static int agSimInit = FALSE ;

/* Initialise default values for all the mechanisms servos 
*  It is important that this array of structures has MAX_MECH_INDEX + 1
*  members.
*/

static struct ServoConfig defServoConfig[] = {
  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},             /* Pupil Imager */
  {200.0, 1000.0, 20.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},      /* Lens         */
  {1000.0, 5000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},     /* Col. filter  */
  {1000.0, 5000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},     /* ND filter    */
  {500.0, 2500.0, 20.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},      /* Field stop   */
  {0.1, 0.5, 20.0, 5.0, 0.5, 10.0, 0.1, 0.1, 0.0},           /* Cal. source  */
  {20000.0, 100000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},  /* Focus        */
  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},             /* Sci. fold    */
  {2000.0, 20000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* Camera arm   */
  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},             /* AO           */
  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},             /* P1 probe     */
  {20000.0, 100000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},  /* P1 focus     */
  {500.0, 2500.0, 20.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},      /* P1 filter    */
  {500.0, 2500.0, 20.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},      /* P1 fldstop   */
  {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},             /* P2 probe     */
  {20000.0, 100000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},  /* P2 focus     */
  {500.0, 2500.0, 20.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},      /* P2 filter    */
  {500.0, 2500.0, 20.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},      /* P2 fldstop   */
  {8000.0, 40000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* P1 RT4       */
  {2000.0, 10000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* P1 PA4       */
  {8000.0, 40000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* P2 RT3       */
  {2000.0, 10000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* P2 PA3       */
  {8000.0, 80000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* SF RT2       */
  {2000.0, 20000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* SF Tilt      */
  {1000.0, 50000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0},    /* SF Lin2      */
  {8000.0, 40000.0, 40.0, 5.0, 0.5, 10.0, 2.0, 0.1, 0.0}};   /* AO arm       */


/* Array of structures to hold state of each simulated mechanism */
struct agMechSim {
  struct ServoState  servoState ;
  struct ServoConfig servoConfig ;
  int state ;                              /* MOVING, STOPPED or FOLLOWING */
  int lastState ;
  int command ; 
  double demand ;                          /* Follow demand position */
  double target ;                          /* Move/datum/park demand */
  double posn ;                            /* Current position */
  double vel ;                             /* Current velocity */
  int parked ;
  int datumed ;
  int inpos ;
  int resp ;                               /* Simulated PLC response */
  int init ;
  int braked ;                     
  int ampenabled ;
} ;

static struct agMechSim agMechSims[MAX_MECH_INDEX + 1] ;


/*+
 *   Function name:
 *   agMechSimDump
 *
 *   Purpose:
 *   Print out current state of simulator for debug purposes
 *
 *   Description:
 *   Checks that the index is valid and then prints out the current
 *   contents of the agmechSim structure
 *
 *   Invocation:
 *   agMechSimDump(mechindex)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   mechindex    (int)   Mechanism index
 *
 *   Function value:
 *   None
 * 
 *-
 */

void agMechSimDump (int mechindex)

{
  if (mechindex < 0 || mechindex > MAX_MECH_INDEX + 1) {
    printf ("Mechanism index out of range\n") ;
  } else {
    printf ("Follow demand %f\n", agMechSims[mechindex].demand) ;
    printf ("Move demand   %f\n", agMechSims[mechindex].target) ;
    printf ("Current posn  %f\n", agMechSims[mechindex].posn ) ;
    printf ("Current vel.  %f\n", agMechSims[mechindex].vel) ;
    printf ("\n") ;
    printf ("Command index %d\n", agMechSims[mechindex].command) ;
    printf ("State index   %d\n", agMechSims[mechindex].state) ;
    printf ("InPos flag    %d\n", agMechSims[mechindex].inpos) ;
    printf ("Datum flag    %d\n", agMechSims[mechindex].datumed) ;
    printf ("Parked flag   %d\n", agMechSims[mechindex].parked) ;
    printf ("Braked flag   %d\n", agMechSims[mechindex].braked) ;
    printf ("Amp enabled   %d\n", agMechSims[mechindex].ampenabled) ;
    printf ("PLC response  %d\n", agMechSims[mechindex].resp) ;
    printf ("Init flag     %d\n", agMechSims[mechindex].init) ;
  }

}

/*+
 *   Function name:
 *   agMechSimFlags
 *
 *   Purpose:
 *   Fetch datumed, parked and in position flags.
 *
 *   Description:
 *   This routine fetches the flags that indicate whether the mechanism is
 *   datumed, parked and in position. It is the equivalent for the simulators
 *   of what getDPRam does for the real hardware. 
 *
 *   Invocation:
 *   flags = agMechSimFlags(mechindex, offset)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    mechindex  (long)   Mechanism index
 *      (<)    offset     (int)    Offset for compound mechanisms
 *
 *   Function value:
 *   (<)  flags  (long)  Flags encoded as a bit pattern 
 * 
 *-
 */

long agMechSimFlags (long mechindex, int offset)

{
  long flags = 0 ;         /* Initialise flags to zero */

/* If the mechanism is the pupil imager then force it to always be in position,
*  parked and datumed. The pupil imager has been physically removed from
*  the A&G but the A&G software still processes these flags even when not
*  in simulation.
*/
  if (mechindex == pimg) {

     flags = flags | IPOSFLAG | PARKFLAG | DATUFLAG ;

  } else if (mechindex == ag_ao) {
     if (agMechSims[p2_RT3].inpos && agMechSims[ag_PA3AO].inpos)
       flags |= IPOSFLAG ;

     if (agMechSims[p2_RT3].parked && agMechSims[ag_PA3AO].parked)
       flags |= PARKFLAG ;

     if (agMechSims[p2_RT3].datumed && agMechSims[ag_PA3AO].datumed)
       flags |= DATUFLAG ;

  } else if (mechindex == ag_sf) {
     if (agMechSims[ag_RT2].inpos && agMechSims[ag_Tilt].inpos &&
         agMechSims[ag_Lin2].inpos)
       flags |= IPOSFLAG ;

     if (agMechSims[ag_RT2].parked && agMechSims[ag_Tilt].parked &&
         agMechSims[ag_Lin2].parked)
       flags |= PARKFLAG ;

     if (agMechSims[ag_RT2].datumed && agMechSims[ag_Tilt].datumed &&
         agMechSims[ag_Lin2].datumed)
       flags |= DATUFLAG ;

     if (agMechSims[ag_RT2].ampenabled || agMechSims[ag_Tilt].ampenabled || 
         agMechSims[ag_Lin2].ampenabled)
       flags |= AENAFLAG ;

  } else if (mechindex == p1_probe) {
     if (agMechSims[p1_RT4].inpos && agMechSims[p1_PA4].inpos &&
         agMechSims[p1_focus].inpos)
       flags |= IPOSFLAG ;

     if (agMechSims[p1_RT4].parked && agMechSims[p1_PA4].parked &&
         agMechSims[p1_focus].parked)
       flags |= PARKFLAG ;

     if (agMechSims[p1_RT4].datumed && agMechSims[p1_PA4].datumed &&
         agMechSims[p1_focus].datumed)
       flags |= DATUFLAG ;

  } else if (mechindex == p2_probe) {
     if (agMechSims[p2_RT3].inpos && agMechSims[p2_PA3].inpos &&
         agMechSims[p2_focus].inpos)
       flags |= IPOSFLAG ;

     if (agMechSims[p2_RT3].parked && agMechSims[p2_PA3].parked &&
         agMechSims[p2_focus].parked)
       flags |= PARKFLAG ;

     if (agMechSims[p2_RT3].datumed && agMechSims[p2_PA3].datumed &&
         agMechSims[p2_focus].datumed)
       flags |= DATUFLAG ;

  } else {
    if (agMechSims[mechindex].inpos )
       flags |= IPOSFLAG ;

    if (agMechSims[mechindex].parked)
       flags |= PARKFLAG ;

    if (agMechSims[mechindex].datumed)
       flags |= DATUFLAG ;

    if (agMechSims[mechindex].ampenabled)
       flags |= AENAFLAG ;

    if (mechindex == ag_RT2) {
      if (agMechSims[mechindex].braked)
         flags |= BRONFLAG ;
    }
  }

  return flags ;
}

/*+
 *   Function name:
 *   agMechSimInit
 *
 *   Purpose:
 *   Initialise the data needed by the mechanism simulators
 *
 *   Description:
 *   Creates the semaphore used to guard the mecahism simulators
 *
 *   Invocation:
 *   agMechSimInit (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *)  Pointer to gensub record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agMechSimInit (struct genSubRecord *pgsub) 
{

  if (!agSimInit) {
    agSimSemId = epicsMutexMustCreate();
    agSimInit = TRUE ;
  }

  if (!agSimSemId)
    return -1 ;
  else
    return 0 ;

}

/*+
 *   Function name:
 *   agMechSimPosn
 *
 *   Purpose:
 *   Return current psoition of simulator 
 *
 *   Description:
 *   For the real mechanisms, the EPICS system reads the current mechanism
 *   positions from dual ported RAM. This is the equivalent routine for
 *   the simulators except that the positions are read from an area of
 *   static memory.
 *
 *   Invocation:
 *   resp = agMechSimPosn(mechindex, offset)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    mechindex  (long)   Mechanism index
 *      (<)    offset     (int)    Offset for compound mechanisms
 *
 *   Function value:
 *   (<)  resp  (double)  Position of simulated mechanism (encoder units) 
 * 
 *-
 */

double agMechSimPosn (long mechindex, int offset)

{
  long i ;                             /* Local index */

  i = mechindex ;

  if (mechindex == p1_probe) {
    if (offset == 2)
      i = p1_focus ;
    else if (offset == 1)
      i = p1_PA4 ;
    else
      i = p1_RT4 ;
  } else if (mechindex == p2_probe) {
    if (offset == 2)
      i = p2_focus ;
    else if (offset == 1)
      i = p2_PA3 ;
    else
      i = p2_RT3 ;
  } else if (mechindex == ag_sf) {
    if (offset == 2)
      i = ag_Lin2 ;
    else if (offset == 1)
      i = ag_Tilt ;
    else
      i = ag_RT2 ;
  } else if (mechindex == ag_ao) {
      if (offset == 1)
        i = ag_PA3AO ;
      else
        i = p2_RT3 ;
  }
   
  return agMechSims[i].posn ;
}


/*+
 *   Function name:
 *   agMechSimResp
 *
 *   Purpose:
 *   Return simulated PLC response
 *
 *   Description:
 *   This function simply returns a number that simulates the numbers
 *   returned by the PLC programs in the PMAC cards. 
 *
 *   Invocation:
 *   resp = agMechSimResp(mechindex, offset)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    mechindex  (long)   Mechanism index
 *      (<)    offset     (int)    Offset for compound mechanisms
 *
 *   Function value:
 *   (<)  resp  (long)  simulated PLC response code 
 * 
 *-
 */

long agMechSimResp (long mechindex, int offset)
{

/* For compound mechanisms set the response on the basis of the command
*  For single mechanisms the response has already been set by the mechanism
*  simulator
*/
  if ((mechindex == ag_ao) || mechindex == p1_probe || 
      (mechindex == p2_probe) || (mechindex == ag_sf) ) {
    if (agMechSims[mechindex].command == C_Datum)  
      agMechSims[mechindex].resp = PLC_DATUM_IN_PROG ;
    else if (agMechSims[mechindex].command == C_Park)  
      agMechSims[mechindex].resp = PLC_PARK_IN_PROG ;
    else if (agMechSims[mechindex].command == C_Move)  
      agMechSims[mechindex].resp = PLC_MOVE_IN_PROG ;
    else if (agMechSims[mechindex].command == C_Stop ||
             agMechSims[mechindex].command == C_SoftStop )  
      agMechSims[mechindex].resp = PLC_STOP_IN_PROG ;
    else if (agMechSims[mechindex].command == C_Foll ||
             agMechSims[mechindex].command == C_Crude )  
      agMechSims[mechindex].resp = PLC_FOLLOW_ON ;
  }

/* Reset the response if all the sub mechanisms of the compound mechanism
*  are back to idle
*/
  if (mechindex == ag_ao) {
    if (agMechSims[p2_RT3].resp == PLC_IDLE &&
        agMechSims[ag_PA3AO].resp == PLC_IDLE)
      agMechSims[mechindex].resp = PLC_IDLE ;
  } else if (mechindex == ag_sf) {
    if (agMechSims[ag_RT2].resp == PLC_IDLE &&
        agMechSims[ag_Tilt].resp == PLC_IDLE &&
        agMechSims[ag_Lin2].resp == PLC_IDLE )
      agMechSims[mechindex].resp = PLC_IDLE ;
  } else if (mechindex == p1_probe) {
    if (agMechSims[p1_RT4].resp == PLC_IDLE &&
        agMechSims[p1_PA4].resp == PLC_IDLE &&
        agMechSims[p1_focus].resp == PLC_IDLE )
      agMechSims[mechindex].resp = PLC_IDLE ;
  } else if (mechindex == p2_probe) {
    if (agMechSims[p2_RT3].resp == PLC_IDLE &&
        agMechSims[p2_PA3].resp == PLC_IDLE &&
        agMechSims[p2_focus].resp == PLC_IDLE )
      agMechSims[mechindex].resp = PLC_IDLE ;
  }

  return (long)agMechSims[mechindex].resp ;
  
}

/*+
 *   Function name:
 *   agMechSimTrack
 *
 *   Purpose:
 *   Provide the tracking demand for a mechanism
 *
 *   Description:
 *   The routine writes the demand into the appropriate mechanism
 *   structure for use by the servo algorithm. Note that the command to 
 *   set the mechanism into follow mode is done through the normal
 *   agSimCommand route.
 *
 *   Invocation:
 *   agMechSimTrack (mechindex, posn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   mechindex  (int)    Index to mechanism
 *      (>)   posn       (double)   Demand position
 *   
 *
 *   Function value:
 *   None
 * 
 *-
 */

void agMechSimTrack (int mechindex, double posn)
{

   agMechSims[mechindex].demand = posn ;

}

/*+
 *   Function name:
 *   agMechSimulate
 *
 *   Purpose:
 *   Simulates an A&G mechanism
 *
 *   Description:
 *   Each time the function is called the current state of the simulated
 *   mechanism is checked and the servo routine called with appropriate
 *   parameters. The current state of the mechanism is then output.
 *
 *   Invocation:
 *   agMechSimulate(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Gensub record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agMechSimulate (struct genSubRecord *pgsub)
{

 int mech  ;                              /* Mechanism index */
 double noise ;                           /* servo noise */
 double startPosn ;                       /* Default start position */
 double maxVel ;                          /* Maximum velocity */
 double now ;                             /* current TAI time */
 double mechError ;                       /* Mechanism error */

 int newCommand ;                         /* Latest command */
 int newState ;                           /* Latest state */
 double newDemand ;                       /* Latest demand */

/* Pull in the record inputs */
 mech      = *(long *)pgsub->a ;
 noise     = *(double *)pgsub->b ;
 startPosn = *(double *)pgsub->c ;
 maxVel    = *(double *)pgsub->d ;
 
/* Check if this particular mechanism has been initialised and if not set
*  the servo configuration parameters etc. 
*/

 if (!agMechSims[mech].init) {
   agMechSims[mech].servoConfig = defServoConfig[mech] ;
   agMechSims[mech].servoState.pdtold = startPosn ; 
   timeNow(&(agMechSims[mech].servoState.told) ) ;
   agMechSims[mech].servoState.told -=0.05 ;         /* assumes scan is 20hz */
   agMechSims[mech].servoState.tout = agMechSims[mech].servoState.told ;
   agMechSims[mech].posn = startPosn ;
   agMechSims[mech].vel  = 0.0 ;
   agMechSims[mech].init = TRUE ;
   if (mech == ag_RT2) agMechSims[mech].braked = TRUE;
 }

/* Update with the latest input parameters */
  agMechSims[mech].servoConfig.noise = noise ;
  agMechSims[mech].servoConfig.vtmax = maxVel ;

/* Read the current time. */
  timeNow(&now) ;

/* Fetch the latest data from the simulation structure */
  epicsMutexMustLock(agSimSemId);
    newState = agMechSims[mech].state ;
    newDemand = agMechSims[mech].target ;
    newCommand = agMechSims[mech].command ;
  epicsMutexUnlock(agSimSemId);

/* Compute the new position of the mechanism based on its state */
  if (newState == SIM_MOVING) {

/* Clear parked and perhaps datumed flags if appropriate */
    agMechSims[mech].parked = FALSE ;
    agMechSims[mech].ampenabled = TRUE ;
    if (mech == ag_RT2) agMechSims[mech].braked = FALSE;
    if (newCommand == C_Datum) {
        agMechSims[mech].datumed = FALSE ;
        agMechSims[mech].resp    = PLC_DATUM_IN_PROG ;
    } else if (newCommand == C_Park) {
        agMechSims[mech].resp    = PLC_PARK_IN_PROG ;
    } else {
        agMechSims[mech].resp    = PLC_MOVE_IN_PROG ;
    }

/* Compute the new position of the mechanism */
    agMechSims[mech].inpos = tcsServo (now, newDemand, 0,
                           &agMechSims[mech].servoConfig,
                           &agMechSims[mech].servoState ,
                           &agMechSims[mech].posn,
                           &agMechSims[mech].vel ) ;
    mechError = newDemand - agMechSims[mech].posn ;

/* Set any flags that are appropriate */
    if (agMechSims[mech].inpos) {
      if (newCommand == C_Park) {
          agMechSims[mech].parked = TRUE ;
      } else if (newCommand == C_Datum) {
          agMechSims[mech].datumed = TRUE ;
      }
      agMechSims[mech].state = SIM_STOPPED ;
    }
      
  } else if (newState == SIM_FOLLOWING) {

    agMechSims[mech].parked = FALSE ;
    agMechSims[mech].ampenabled = TRUE ;
    if (mech == ag_RT2) agMechSims[mech].braked = FALSE;
    agMechSims[mech].resp    = PLC_FOLLOW_ON ;

    agMechSims[mech].inpos = tcsServo (now, agMechSims[mech].demand, 0,
                             &agMechSims[mech].servoConfig,
                             &agMechSims[mech].servoState ,
                             &agMechSims[mech].posn,
                             &agMechSims[mech].vel ) ;
    mechError = agMechSims[mech].demand - agMechSims[mech].posn ;

  } else {

    if (agMechSims[mech].lastState != SIM_STOPPED) {
      agMechSims[mech].target = agMechSims[mech].posn ;
    }

    agMechSims[mech].inpos = tcsServo (now, agMechSims[mech].target, 1,
                           &agMechSims[mech].servoConfig,
                           &agMechSims[mech].servoState ,
                           &agMechSims[mech].posn,
                           &agMechSims[mech].vel ) ;

    if (agMechSims[mech].inpos) {
      agMechSims[mech].ampenabled = FALSE;
      if (mech == ag_RT2) agMechSims[mech].braked = TRUE; 
      agMechSims[mech].resp    = PLC_IDLE ;
    } else {
      agMechSims[mech].resp    = PLC_STOP_IN_PROG ;
    }
      
    mechError = agMechSims[mech].target - agMechSims[mech].posn ;
  }
 
  agMechSims[mech].lastState = agMechSims[mech].state ;

/* Write to the record outputs */
  *(long *)pgsub->valb = (long)floor(agMechSims[mech].posn) ;

  return 0 ;


}


/*+
 *   Function name:
 *   agSimCommand
 *
 *   Purpose:
 *   Issue a command to a specified mecahnism
 *
 *   Description:
 *   The routine simply stores the comamnd and if appropriate the demand
 *   position in the mechanism structure ready for the next pass of
 *   the agMechSimulate routine
 *
 *   Invocation:
 *   agSimCommand (mechindex, command, posn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   mechindex  (int)    Index to mechanism
 *      (>)   command    (long)   Index to command
 *      (>)   posn       (long)   Demand position
 *   
 *
 *   Function value:
 *   None
 * 
 *-
 */

void agSimCommand (int mechindex, long command, long posn)
{

  long demState ;                           /* Demand state */

/* Check the command and set the demand state */
  if (command == C_Datum || command == C_Move || command == C_Park) {
    demState = SIM_MOVING ;
  } else if (command == C_Foll || command == C_Crude ) {
    demState = SIM_FOLLOWING ;
  } else {                        /* Treat anything else as a stop */
    demState = SIM_STOPPED ;
  }

  epicsMutexMustLock(agSimSemId);
     agMechSims[mechindex].command = command ;
     agMechSims[mechindex].state = demState ;
     if ((command != C_Foll) && (command != C_Crude))
       agMechSims[mechindex].target = posn ;
  epicsMutexUnlock(agSimSemId);

}
epicsRegisterFunction(agMechSimulate);
epicsRegisterFunction(agMechSimInit);

