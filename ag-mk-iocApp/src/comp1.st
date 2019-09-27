/*
 *  FILENAME
 *  --------
 *  comp1.stpp
 *
 *  PURPOSE
 *  -------
 *  This file contains the EPICS state transition language program for
 *  managing a one axis mechanism in the CICS
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  comp1_ss      - Process commands for a particular 1 axis component
 *
 *  PROGRAM
 *  --------
 *  comp1
 *
 *  INVOCATION
 *  -----------
 *  Include the following line in the VxWorks startup script:
 *
 *  seq &comp1, "top=ag:, sadtop=agsad:, sys=sys, mech=hw, motor=1"
 *
 *  PARAMETERS (all are input)
 *  --------------------------
 *     top      string    String to be substituted for the {top} macro
 *                        used to for the top level name of the CICS
 *                        EPICS database.
 *
 *     sadtop   string    String to be substituted for the {sad} macro
 *                        used for the name of the CICS Status/Alarm
 *                        Database.
 *
 *     sys      string    String to be substituted for the {sys} macro
 *                        used for the name of the CICS systemwide records.
 *
 *     mech     string    String to be substituted for the {mech} macro
 *                        used for the mechanism name in the motor
 *                        simulation database.
 *
 *  RETURN VALUE
 *  ------------
 *  N/A
 *
 *  GLOBALS
 *  -------
 *     EXTERNAL FUNCTIONS
 *
 *     This program makes use of the library functions included with the 
 *     EPICS state notation language (efTest, efClear, pvGet, pvPut, delay)
 *
 *     EXTERNAL VARIABLES
 *
 *     Several records in the CICS CAD, CAR, motor control and Status/Alarm
 *     database are used as external variables. See the declarations in the
 *     code for details
 *
 *  REQUIREMENTS
 *  ------------
 *  This program assumes that the EPICS database "ag_top", has been 
 *  loaded, and that this databases contain records whose names match 
 *  those in the "assign" declarations below. If any changes are made to 
 *  the names of these records, the changes must also be reflected in 
 *  this program. Failure to do this will result in one or more channels 
 *  not connecting when the program is executed
 *
 *  The ordering of the arguments within each CAD record (A, B, C...) is
 *  defined in the description of the interface between the CAD database
 *  and its clients. Changes to that interface should be reflected in this
 *  file.
 *
 *  LIMITATIONS
 *  ------------
 *  It is my intention eventually to use "option -c" to allow this program
 *  to execute before all the connections are made. At the moment I have not
 *  managed to get this option to work, so in the mean time having "init1"
 *  and "init2" states may look superfluous. I am informed that the RGO
 *  have not had any problems with "option -c".
 *
 *  The code in this file seems very monolithic, and I think it would be
 *  easier to see the big picture if parts of it were contained in callable
 *  functions. There are also several places where common code sequences
 *  could be replaced by functions, the most notable being the state
 *  "resetting", which exists merely to save duplication of the code for
 *  the "init" action.
 *
 *  The setting of the "Parked" flag is something that would probably be
 *  better off done in the EPICS database, since the Park position is
 *  contained in a lookup table readable by EPICS LUT records. I have not
 *  implemented this yet.
 *
 *  AUTHOR
 *  ------
 *  Steven Beard  (smb@roe.ac.uk)
 *
 *  HISTORY
 *  -------
 *  02-May-1996: Original version based on state notation code
 *               used for the Michelle IR spectrograph controller.     (smb)
 *  07-May-1996: CAD record names shortened. Modified to monitor
 *               counters incremented by each CAD record's STLK
 *               and SPLK forward links rather than the CAD output
 *               directly. This saves having to parse the CAD DIR
 *               field.                                                (smb)
 *  09-May-1996: Implemented behaviour is response to additional
 *               events as designed using state transition diagram.    (smb)
 *  13-May-1996: State transition design modified to ensure the
 *               CICS itself appears stateless in its response to
 *               commands (which is an OCS requirement).               (smb)
 *  16-May-1996: Simulated Datum search mechanism added to motors
 *               database.                                             (smb)
 *  17-May-1996: Bug fix: The CAR record failed to switch back to
 *               idle when the mechanism is commanded to move with
 *               demanded position the same as the current position.
 *               In this situation there was no action by the motors
 *               database, so the "moving" flag did not trigger the
 *               MOVING to IDLE change of state. (V 0.0)               (smb)
 *  03-Jun-1996: Record names in motors database modified to make it
 *               easier to duplicate this database and control more
 *               than one mechanism.                                   (smb)
 *  04-Jun-1996: Modifications suggested by Alan Pickup and Kim
 *               Gillies incorporated. The mechanism will now
 *               automatically Datum when a "move" command is
 *               received in the "not_Datumed" state. All "stop"
 *               directives for a particular mechanism are now
 *               regarded as equivalent.                               (smb)
 *  07-Jun-1996: Macro substitution added, as suggested by Chris
 *               mayer. "init" and "reset" commands added, but the
 *               "init" command is not fully implemented yet.          (smb)
 *  14-Jun-1996: EPICS 3.12.2.Gem3 installed. CAR record now has
 *               integer inputs and outputs rather than string.        (smb)
 *  26-Jun-1996: Macro substitution made the same as that used in
 *               the CAPFAST diagrams. "sad", "sys" and "motor"
 *               variables introduced. Manage "compParked" flag.       (smb)
 *  02-Jul-1996: Try using the TIMEOUT variable again. In the UAE
 *               environment it now works.                             (smb)
 *  09-Oct-1996: {sad} macro changed to {sadtop}.                      (smb)
 *  03-Nov-1996: Datum search wait now done in database rather than
 *               in state notation language. (V 1.0)                   (smb)
 *  03-Dec-1996: "printf" replaced by "cicsLogMessage" function.       (smb)
 *  11-Dec-1996: Top level macro variables now include the ":".        (smb)
 *  08-Jan-1997: Remove initialisation and connection message.        (smb)
 *  21-Jan-1997: Renamed to "comp1.stpp" and commands related to
 *               the CICS system as a whole removed. Add mechanism
 *               label to message.                                    (smb)
 *  29-Jan-1997: Bug fix: Do not alter the "resetC" CAR record.        (smb)
 *  13-Feb-1997: "reset" command removed. It has been replaced by
 *               a master "Datum" command.                             (smb)
 *  26-May-1997: Fixed bug in "resetting" state where the CAR record
 *               was not reset properly.                               (smb)
 *  11-Jul-1997: Obtain Park position from Status Alarm Database.      (smb)
 *  24-Jul-1997: Ensure there is a delay of at least 0.5 seconds
 *               before the detection of the complation of a move
 *               happens. This is done for compatibility with the
 *               multi-axis mechanisms, where this delay was
 *               necessary to solve a timing bug. The delay is
 *               ensured by adding a "&& delay(0.5)" to some of the
 *               "when" statements.                                    (smb)
 */

/** How to check for channel connections (manually, from VxWorks prompt):
 **  1. Find out Task_Id of SNL task (shown after "seq" call by startup). 
 **     seqShow will show all Ids, but no names
 **  2. seqChanShow (task_Id) will show connection state of channels
 **/
 
/* ===================================================================== *
 * SNL-Rules:								 *
 * The 1st when clause will be serviced if matched			 *
 * The 2nd when clause will not be used if 1st was matched		 *
 * The more specific When must be the 1st;				 *
 *   every superset of a former When comes later with a ">=" delay	 *
 * If Whens don't form a common set (same specificity),	the later	 *
 *   needs a smaller Delay time (otherwise it is never processed).	 *
 *   That's only true if the When always leads to a state change.	 * 
 *									 *
 * Delay always refers to the time point of a state change 		 *
 * but refreshing the current state (changing again into) also counts.	 *
 * 									 *
 * The delay functions causes big problems:				 * 
 *   It actually waits until the delay is over and holds up execution	 *
 *   of other when clauses before it. 					 *
 *									 *
 * The problem is also that the c compiler doesn't optimize chained 	 *
 *   conditions, so it doesn't help to have the delay as last condition  *
 *   and the other conditions for the when clause are not met - 	 *
 *   when clauses rejected before will not be tested again until 	 *
 *   the delay is over.					   		 *
 *					 				 *
 * Note also that no precompiler marks (#if 0, #endif) are allowed	 *
 *   in the state sets, only before in the declaration area.		 *
 *									 *
 * It's impossible to query PLCRespEvFl. 				 *
 * It's always set after processing of the record. 			 *
 *
 * Due to a severe bug in the sequencer, we need a transition to the 
 *  same state which contains a delay time after which all the other
 *  conditions in this state are tested again. 
 * In each state, conditions which have to be polled and are not 
 *  event-triggered like monitored EPICS channels, are just tested once
 *  at their specified delay time.
 * In order to allow polling of e.g. global c variable conditions,
 *  such a dummy transition to itself has to be included in every state.
 * Unfortunately, that delay time has to be bigger than all other delay
 *  times in the state which doesn't allow to use timeout delays at all.
 * ====================================================================  *
 */

/* ==================================================================== */

program comp1 ("top=ag:, sadtop=ag:sad:, sys=sys, mech=hw, motor=1")
  option +r;	/*- This option is needed to make the code reentrant          */
  option +c;	/*+ Don't wait for channel conn. before starting the programs */
/*option +a;*/	/*- Use asynchronous pvGet, don't wait for completion         */
  option -l;	/*+ compiler errors ref c-lines (+ doesn't work correctly)    */
  option +d;	/*- run-time debug message on/off                             */

%%#include <ag_define.h>

/* The following constant defines a time limit in seconds within which all
 * movements should be carried out. Exceeding this limit will result in a
 * timeout error. 180 seconds = 3 minutes.
 *
 * Waiting for a timeout delay always causes problems with the delay
 *   function described above - next part is disabled therefore.	
 */
#if 0
  #define TIMEOUT 	180
  #define TIMEOUT_SIMU 	30
#endif

/* value for the response of the PMAC PLC program via DPRam
 * in which case the CAR doesn't stay (or goes to) BUSY.
 */

/* ==================================================================== */
/*
 * The following declarations assign the variables which are responsible
 * for detecting "Datum mechanism" and other commands.
 *	
 * (1) "long" variables are assigned to counters which are incremented
 *     in the database whenever a successful START or STOP directive is
 *     detected.
 *
 * (2) An event flag is synchronised with each "long" variable, so the
 *     flag is triggered whenever the variable changes. The net result
 *     is that an event flag is triggered whenever a command is started
 *     or stopped in the outside world.
 *
 * (3) Variables are also assigned to the command arguments.
 */
/* ==================================================================== */

/* (Components Controllers) SUBSYSTEM COMMAND DECLARATIONS  */
int 	InitStart;             /* START counter attached to init CAD record  */
assign  InitStart to "{top}{sys}sysInitP:st.VAL";
monitor InitStart;
evflag  InitStartFlag;   /* Event flag triggered by changes to initStart */
sync    InitStart InitStartFlag;

/* DATUM COMMAND DECLARATIONS	*/
int 	DatumStart;     /* START counter attached to ${mech}Datum CAD record */
assign  DatumStart to "{top}{mech}DatumP:st.VAL";
monitor DatumStart;
evflag  DatumStartFlag;     /* Event flag triggered by changes to DatumStart */
sync    DatumStart DatumStartFlag;

int    DatumStop;       /* STOP counter attached to ${mech}Datum CAD record */
assign  DatumStop to "{top}{mech}DatumP:sp.VAL";
monitor DatumStop;
evflag  DatumStopFlag;        /* Event flag triggered by changes to DatumStop */
sync    DatumStop DatumStopFlag;

/* Park COMMAND DECLARATIONS	*/
int 	ParkStart;        /* START counter attached to ${mech}Park CAD record */
assign  ParkStart to "{top}{mech}ParkP:st.VAL";
monitor ParkStart;
evflag  ParkStartFlag;        /* Event flag triggered by changes to ParkStart */
sync    ParkStart ParkStartFlag;

int    ParkStop;          /* STOP counter attached to ${mech}Park CAD record */
assign  ParkStop to "{top}{mech}ParkP:sp.VAL";
monitor ParkStop;
evflag  ParkStopFlag;          /* Event flag triggered by changes to ParkStop */
sync    ParkStop ParkStopFlag;

/* Soft Stop COMMAND DECLARATIONS	*/
int 	StopStart;        /* START counter attached to ${mech}Stop CAD record */
assign  StopStart to "{top}{mech}StopP:st.VAL";
monitor StopStart;
evflag  StopStartFlag;        /* Event flag triggered by changes to StopStart */
sync    StopStart StopStartFlag;

int    StopStop;          /* STOP counter attached to ${mech}Stop CAD record */
assign  StopStop to "{top}{mech}StopP:sp.VAL";
monitor StopStop;
evflag  StopStopFlag;          /* Event flag triggered by changes to StopStop */
sync    StopStop StopStopFlag;

/* MOVE COMMAND DECLARATIONS	*/
int 	EngStart;       	/* START counter attached to Eng CAD record  */
assign 	EngStart to "{top}{mech}EngP:st.VAL";
monitor	EngStart;
evflag 	EngStartFlag; 	      /* Event flag triggered by changes to EngStart */
sync 	EngStart EngStartFlag;

int 	EngStop;           /* STOP counter attached to ${mech}Eng CAD record */
assign 	EngStop to "{top}{mech}EngP:sp.VAL";
monitor EngStop;
evflag 	EngStopFlag;  		/* Event flag triggered by changes to EngStop */
sync 	EngStop EngStopFlag;

/* CAR RECORD DECLARATIONS	*/
int 	compCARin;        	/* Output to the {mech}C CAR record */
assign	compCARin to "{top}{mech}C.IVAL";
int 	compCARerrin;     	/* Error Output to the ${mech}C CAR record */
assign	compCARerrin to "{top}{mech}C.IERR";
string	compCARmessin;  	/* Message Output to the ${mech}C CAR record */
assign	compCARmessin to "{top}{mech}C.IMSS";

/* SAD - formerly motor related assignments (in case of multiple motors) */
string 	compHealth;     	/* Mechanism health SIR record */
assign	compHealth to "{sadtop}{mech}Health.VAL";

string 	compState;      	/* Mechanism state SIR record */
assign	compState to "{sadtop}{mech}State.VAL";

string 	compLabel;      	/* Component label */
assign 	compLabel to "{sadtop}{mech}Label.FDSC";

/* demanded engineering positions		*/
int 	EngPos[3];       /* Required mechanism engineering position */
assign 	EngPos[0] to  "{top}{mech}Eng.VALA";
assign 	EngPos[1] to  "{top}{mech}Eng.VALA";
assign 	EngPos[2] to  "{top}{mech}Eng.VALA";

/* MOTORS DATABASE DECLARATIONS		*/
/*
 * The following declarations assign variables to the motor simulation
 * database, which comes below this state notation code and simulates the
 * underlying mechanism control.
 *
 * formerly motor related assignments (also in case of one motor):
 */

/* long    motorParkPos;       Mechanism's Parked position 	*/
/* assign  motorParkPos to "{sadtop}{mech}ParkPos.VAL"; 	*/

short 	motorEnable[3];        /* Binary record to enable mechanism movement */
assign	motorEnable[0] to "{top}{mech}:enable.VAL";	/* assign all	*/
assign	motorEnable[1] to "{top}{mech}:enable.VAL";	
assign	motorEnable[2] to "{top}{mech}:enable.VAL";	
	
short 	motorDsearch[3];     /* Binary record to switch on Datum search mode */
assign	motorDsearch[0] to "{top}{mech}:dsearch.VAL";	/* assign all	*/
assign	motorDsearch[1] to "{top}{mech}:dsearch.VAL";
assign	motorDsearch[2] to "{top}{mech}:dsearch.VAL";	
monitor	motorDsearch;					/* monitor all	*/

int 	motorDemand[3];        		/* Mechanism demand position */
assign	motorDemand[0] to "{top}{mech}:demand.VAL";	/* assign all	*/
assign	motorDemand[1] to "{top}{mech}:demand.VAL";
assign	motorDemand[2] to "{top}{mech}:demand.VAL";
monitor	motorDemand;					/* monitor all	*/

int 	motorCurrent[3];       		/* Mechanism current position */
assign	motorCurrent[0] to "{top}{mech}:current.VAL";	/* assign all	*/
assign	motorCurrent[1] to "{top}{mech}:current.VAL";	
assign	motorCurrent[2] to "{top}{mech}:current.VAL";	
monitor	motorCurrent;					/* monitor all	*/

short 	motorMoving[3];  /* Binary record to switch on when mech should move */
assign	motorMoving[0] to "{top}{mech}:moving.VAL";	/* assign all	*/
assign	motorMoving[1] to "{top}{mech}:moving.VAL";
assign	motorMoving[2] to "{top}{mech}:moving.VAL";
monitor	motorMoving;					/* monitor all	*/

/* unsigned char motorScan[3];	*/	/* string with scanrate; doesn't work with number	*/
string 	motorScan[3];    	/* record scan to switch on when simu on */
assign	motorScan[0] to "{top}{mech}:diff.SCAN";	/* assign all	*/
assign	motorScan[1] to "{top}{mech}:diff.SCAN";
assign	motorScan[2] to "{top}{mech}:diff.SCAN";

/* ==================================================================== */
/* own added links to PMAC related records				*/

int 	EngDIR;		/* Eng CAD record / DIRECTIVE input (to stop motions) */
assign	EngDIR to "{top}{mech}Eng.DIR";

#define PLCResp 		(read_dpram (respaddr))
#define PLCFlag 		(read_dpram (flagaddr))

#if 0
/* note that it's not possible to use explicit casts in SNL                   */
/* escaping to pure c-code is possible with %{ and }% after the last state    */
#define PLCResp 		((  %{ (long) }%  *respaddr) & 0xffff)
#define PLCFlag 		((  %{ (long) }%  *flagaddr) & 0xffff)
#define PLCResp 		getresponse (mechindex, 0)	
#define PLCFlag 		getplcflags (mechindex, 0)
evflag 	PLCRespEvFl;            /* Event flag triggered by changes to PLCResp */
sync 	PLCResp PLCRespEvFl;	/* (doesn't work)		*/
long 	PLCResp;		/* gensub VALx: PLC response */
long 	PLCFlag;		/* gensub VALx: PLC flags */
assign	PLCResp to "{top}{mech}xlat.VALE";
monitor	PLCResp;
assign	PLCFlag to "{top}{mech}xlat.VALG";
monitor	PLCFlag;
#endif

int 	numbdim;		/* number of mech's dimensions	*/
assign	numbdim to "{top}{mech}CalParm.VALE";

int 	compDatumed;       /* Flag to be set when Datumed in simulation mode */
assign	compDatumed to "{top}{mech}DPRead.G";

int 	compParked;         /* Flag to be set when Parked in simulation mode */
assign	compParked to "{top}{mech}DPRead.H";

/* ==================================================================== */
char message [100];     	/* Message buffer - formerly 80 bytes 	*/
char compdescr[80];     	/* Descr.  buffer */
int  mechindex;
long * respaddr;		/* to hold the precalculated addresses	*/
long * flagaddr;		/*   for accessing the PMAC DPRAM	*/

int  i;

/* ==================================================================== */
/* the following is a text macro used in the Searching for Datum state to check the PLC response */

#define CHECK_DATUM_FOUND		{				  \
     							                  \
       if (PLCResp < 0)	/* Error message from PLC - e.g. Interlocking */  \
        sprintf( message, "\t%s (%d)\t- Error %d on Datum search.",       \
          compdescr, mechindex, PLCResp);                                 \
      else  										\
        if (PLCFlag & DATUFLAG)     /* Datumed flag set by PLC program */ \
        {   compDatumed = TRUE;		pvPut( compDatumed );             \
            sprintf( message, "\t%s (%d)\t- Datum found (no move pending).",  		\
              		compdescr, mechindex );}					\
      else  sprintf( message, "\t%s (%d)\t- timeout on Datum search.", 			\
              		compdescr, mechindex);						\
      											\
      agLogMessage( mechindex, DEB_MIN, message );		}
      
/* ==================================================================== */
/* the following is a text macro used after receiving a Start Flag transition		*/

#define STARTFLAG_REACTION(STRING)	{                                  \
     							                   \
      sprintf( message, "\t%s (%d)\t- %s. (State: %s)",                    \
      		 compdescr, mechindex, STRING, compState);                 \
      agLogMessage( mechindex, DEB_MIN, message );                         \
						                           \
      for (i=0;i<numbdim;i++)		/* set demand	*/                 \
      { pvGet(EngPos[i]);  motorDemand[i]=EngPos[i];  pvPut(motorDemand[i]);  }	  }
      
/* ==================================================================== */

#define CHECK_CAR_HEALTH		{                                  \
     									   \
      if       (PLCResp >= 0)    	strcpy (compHealth,"GOOD");        \
      else if  (PLCResp >=-9 || 					   \
      	       (PLCResp>=-20 && 					   \
      		PLCResp<=-16 ))		strcpy (compHealth,"BAD");	   \
           else 			strcpy (compHealth,"WARNING");	   \
     									   \
      if       (PLCResp < 0)		compCARin = menuCarstatesERROR;		   \
      else  if (PLCResp > 0 && 						   \
      		PLCResp!=FOLLOW_ON && 					   \
      		PLCResp!=FOLLOW_ON2)	compCARin = menuCarstatesBUSY;		   \
            else   			compCARin = menuCarstatesIDLE;		   \
      pvPut (compCARin);						   \
      pvPut (compHealth);						   \
									   \
      if (PLCFlag & DATUFLAG)						   \
      {   compDatumed = TRUE;		pvPut( compDatumed );	}	}

/* ==================================================================== */

#if 0
      /* pvGet (compCARin);		*/  /* it's not possible */        \
      /* if    (compCARin == menuCarstatesBUSY)	*/  /* to switch from IDL*/        \
#endif					    /* to ERROR directly */        \

/* ==================================================================== */

ss comp1_ss
{

/*+
 *   Function name:
 *   State set "comp1_ss"
 *
 *   Purpose:
 *   Manage mechanism operations
 *
 *   This state set initialises the system. It then monitors the CAD records
 *   and triggers appropriate actions in the motor simulation database.
 *
 *   Invocation:
 *   Invoked automatically when sequence program "comp1" started
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *   None
 *
 *   Return value:
 *   N/A
 *
 *   External functions:
 *   EPICS sequencer functions used are
 *   efClear    - Clear event flag
 *   efTest     - Test event flag
 *   pvGet      - Get a process variable
 *   pvPut      - Put a process variable
 *   delay      - Wait for a specified length of time
 *
 *   External variables:
 *   See definitions above
 *
 *   Requirements:
 *   Same as requirements for program "comp1"
 *
 *   Limitations:
 *   Same as limitations for program "comp1"
 *
 *-
 */

/* -------------------------------------------------------------------- */
/* state init1 - This is the state the comp1_ss state set begins in
 * when it first starts running. Its purpose is just to issue a message
 * indicating that the CICS state notation code has started. Execution
 * then passes immediately to state init2.
 */

  state init1
  {
    when ()
    {
      sprintf( message, "%s%s",  macValueGet("top"), macValueGet("mech"));
      mechindex = query_cadname (message);

      sprintf( message, "Comp connecting...:	%s%s", macValueGet("top"), macValueGet("mech"));
      agLogMessage( mechindex, DEB_FULL, message );

    } state init2
  }

/* ==================================================================== */
/* --------------------------------------------------------------------	*/
/* ==================================================================== */
/* state init2 - In this state comp1_ss carries out all the initialisation
 * which is necessary before commands can be executed.
 *
 * Wait until all the appropriate connections have been made.
 */

  state init2
  {
    when ( pvConnectCount() >= pvChannelCount() )
    {
      sprintf( compdescr, "%s%s", macValueGet("top"), macValueGet("mech"));
      pvGet  (numbdim);
      pvGet  (compLabel);		/* Obtain the label for the component */

      sprintf( message, "Comp connected:	%s (%s), index=%d, dims=%d", 
      			compdescr, compLabel, mechindex, numbdim);
      agLogMessage( mechindex, DEB_FULL, message );

      respaddr = getrespaddr (mechindex, 0);	/* precalculate DPRAM	*/
      flagaddr = getflagaddr (mechindex, 0);	/*   access addresses	*/

      if (numbdim < 1)	   numbdim = 1;
      if (numbdim > 3)	   numbdim = 3;
      
      /* sprintf( message, "about to connect: %s, index=%d, coc=%d, chc=%d", 
       *		 compdescr, mechindex, pvConnectCount( ), pvChannelCount( ));
       * agLogMessage( mechindex, DEB_FULL, message );
       */
       
      if   (numbdim > 1)
      {
	sprintf (message,"%s%s", compdescr,"Eng.VALB" );       pvAssign  (EngPos      [1], message);
	sprintf (message,"%s%s", compdescr,":2:enable.VAL" );  pvAssign  (motorEnable [1], message);
	sprintf (message,"%s%s", compdescr,":2:moving.VAL" );  pvAssign  (motorMoving [1], message);
	sprintf (message,"%s%s", compdescr,":2:dsearch.VAL");  pvAssign  (motorDsearch[1], message);
	sprintf (message,"%s%s", compdescr,":2:current.VAL");  pvAssign  (motorCurrent[1], message);
	sprintf (message,"%s%s", compdescr,":2:demand.VAL" );  pvAssign  (motorDemand [1], message);
	sprintf (message,"%s%s", compdescr,":2:diff.SCAN"  );  pvAssign  (motorScan   [1], message);
	
        if (numbdim > 2)
        {
	sprintf (message,"%s%s", compdescr,"Eng.VALC" );       pvAssign  (EngPos      [2], message);
	sprintf (message,"%s%s", compdescr,":3:enable.VAL" );  pvAssign  (motorEnable [2], message);
	sprintf (message,"%s%s", compdescr,":3:moving.VAL" );  pvAssign  (motorMoving [2], message);
	sprintf (message,"%s%s", compdescr,":3:dsearch.VAL");  pvAssign  (motorDsearch[2], message);
	sprintf (message,"%s%s", compdescr,":3:current.VAL");  pvAssign  (motorCurrent[2], message);
	sprintf (message,"%s%s", compdescr,":3:demand.VAL" );  pvAssign  (motorDemand [2], message);
	sprintf (message,"%s%s", compdescr,":3:diff.SCAN"  );  pvAssign  (motorScan   [2], message);
	}
      }	

					/* Set initial state, health, and flags. */
      strcpy( compState,"INITIALISING"); pvPut( compState );
      strcpy( compHealth,"GOOD");	 pvPut( compHealth );	
      compParked  = FALSE;	 pvPut( compParked );

	/* Other housekeeping actions may be included here, such as reading
	 * lookup tables from a file. */

	/* Ensure the event flags to be monitored later are initially cleared. */
      efClear( InitStartFlag  );
      efClear( DatumStartFlag );
      efClear( DatumStopFlag  );
      efClear( ParkStartFlag  );
      efClear( ParkStopFlag   );
      efClear( StopStartFlag  );
      efClear( StopStopFlag   );
      efClear( EngStartFlag   );
      efClear( EngStopFlag    );
/*    efClear( PLCRespEvFl    );	*/

    } state init3
    
    when (delay(10))
    {   
      pvGet  (numbdim);
      sprintf( 	message, "unconnected: %s, index=%d, coc=%d, chc=%d", 
      		compdescr, mechindex, pvConnectCount( ), pvChannelCount( ));
      agLogMessage( mechindex, DEB_FULL, message );
    } state init2
  }
     
/* ==================================================================== */
/* state init3 - In this state we check if Datum is already reached
 * to get rid of the former "Datum found" messages.
 **
 * Jump (default) to "not_Datumed" because the mechanism is assumed
 * to use either incremental encoders or movement by dead reckoning.
 * If the mechanism used absolute encoders you could jump straight
 * to the "idle" state from here.
 */

  state init3
  {
  /* first when clause will be serviced first if matched		*/
    when ( (((getsimu(mechindex)==SIM_NONE))) && (PLCFlag & DATUFLAG) )
    {
      compDatumed = TRUE;		pvPut( compDatumed );
    } state init_idle
  
  /* 2nd when clause will not be used if 1st was matched although 2nd is always matched	*/
    when ()
    {
    } state init_not_Datumed
  }     

/* ==================================================================== */
/* -------------------------------------------------------------------- */
/* ==================================================================== */
  state init_not_Datumed
  {
    when()
    {
      CHECK_CAR_HEALTH;
      compCARin = menuCarstatesIDLE;			pvPut( compCARin );
      strcpy ( compState, "NOT_DATUMED" );	pvPut( compState );
      compDatumed = FALSE;
      for (i=0;i<numbdim;i++)			motorMoving[i] = FALSE;
    } state not_Datumed
  }
  
  state init_not_Datumed_delayed
  {  when(delay (0.5))  	{  } 	state init_not_Datumed  }

/* -------------------------------------------------------------------- */

/* Ensure the motorMoving flag is TRUE so that the next change in state
 * will be triggered by a TRUE to FALSE transition. (Failing to do this
 * could cause an immediate change of state if, due to some latency, the
 * underlying mechanism has not yet started moving).
 *
 * Set the simu database into dsearch mode and enable movement. 
 *
 * Update the mechanism flags.
 * The mechanism cannot be Parked during the Datum search.
 */

  state init_searching_for_Datum
  {
    when()
    {
      CHECK_CAR_HEALTH;
      compCARin    = menuCarstatesBUSY;		pvPut( compCARin  );  
      strcpy( compState, "SEARCHING_FOR_DATUM" ); pvPut( compState );
      compParked   = FALSE;		pvPut( compParked );

      for (i=0;i<numbdim;i++)
      { motorDsearch[i] = TRUE;  	pvPut( motorDsearch[i] );
        motorEnable [i] = TRUE;	 	pvPut( motorEnable [i] );
        motorMoving [i] = TRUE;
      }
    } state searching_for_Datum
  }
    
/* -------------------------------------------------------------------- */

  state init_idle
  {
    when()
    {
      CHECK_CAR_HEALTH;
      strcpy ( compState, "IDLE" );	pvPut( compState );
      compCARin = menuCarstatesIDLE;		pvPut( compCARin );
      for (i=0;i<numbdim;i++)		motorMoving[i] = FALSE;
    } state idle
  }
  
  state init_idle_delayed
  {  when(delay (0.5))  	{  } 	state init_idle  }
  
 /* -------------------------------------------------------------------- */

  state init_moving
  {
    when()
    {
      CHECK_CAR_HEALTH;
      strcpy ( compState, "MOVING" );	pvPut( compState  );
      compCARin    = menuCarstatesBUSY;		pvPut( compCARin  ); 
      compParked   = FALSE;		pvPut( compParked );
      efClear( DatumStartFlag );
      
      for (i=0;i<numbdim;i++)
      { motorDsearch[i] = FALSE; 	pvPut( motorDsearch[i] );
        motorEnable [i] = TRUE;	  	pvPut( motorEnable [i] );
      }
    } state moving
  } 

/* ==================================================================== */
/* -------------------------------------------------------------------- */
/* ==================================================================== */
/* state not_Datumed - This is the first state after initialisation for
 * mechanisms which have incremental encoders, or which are moved by dead
 * reckoning, and hence need to be Datumed before they can be positioned.
 * This state might also be entered if the position of the mechanism is
 * lost for any reason (such as a temporary power failure in the encoders).
 *
 * Wait until an event flag is triggered indicating when a CAD record has been
 * activated.
 * ===================================================================== */

  state not_Datumed
  {
/* ====================================================================	*/
/* Start of CAD flag reactions						*/
/* ====================================================================	*/
/* no datum is necessary to park most of the mechs			*/
/* in not_Datumed, the PLC responses are observed for CAR->IDLE		*/

    when ( efTestAndClear( ParkStartFlag ) )
    {
      STARTFLAG_REACTION ("Park command activated");
    } state init_not_Datumed	

    when ( efTestAndClear( DatumStartFlag ) )
    {
      STARTFLAG_REACTION ("Datum command activated");
    } state init_searching_for_Datum

    when ( efTestAndClear( InitStartFlag ) )
    {  } state resetting
   
/* ==================================================================== */
/* It is not possible to position the mechanism until it has been Datumed.
 * A Datum search is initiated automatically and the demand position is
 * updated so the mechanism will go to this position once the Datum search
 * has finished.
 */
   when ( efTest( EngStartFlag ) )
    {
      STARTFLAG_REACTION ("Move command activated");
 
      sprintf( message, "\t%s (%d)\t- Demanded position = %d", 
      		compdescr, mechindex, motorDemand[0] );
      for (i=1;i<numbdim;i++)
        sprintf( message, "%s, %d", message, motorDemand[i] );
      agLogMessage( mechindex, DEB_MIN, message );

    } state init_searching_for_Datum

/* ==================================================================== */
/* Although the "stop" command is acceptable, a warning should be issued
 * because the command is not expected unless the mechanism is moving.
 */
    when ( efTestAndClear( DatumStopFlag) || 
    	   efTestAndClear( ParkStopFlag ) ||
    	   efTestAndClear( StopStopFlag ) || 
    	   efTestAndClear( StopStartFlag) || 
    	   efTestAndClear( EngStopFlag  ) ) 
    {
      STARTFLAG_REACTION ("Stop command activated");
   /* compCARin    = menuCarstatesBUSY;  pvPut( compCARin  );  */  /* done by CAD already */

      sprintf( message,"\t%s (%d)\t- WARNING: Mechanism not moving - command ignored.",
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );
      
    } state init_not_Datumed_delayed

/* ==================================================================== */
/* Start of non-simulated conditions (state not_Datumed)		*/
/* ==================================================================== */
/* the 1st When is a subset of the 2nd : it has to have a >= delay time	*/

    when ( getsimu(mechindex)==SIM_NONE		&&
    	  (PLCFlag & DATUFLAG)			&&
    	   delay(1.0)				)
    {
      compDatumed = TRUE;		pvPut( compDatumed );
      sprintf( message, "\t%s (%d)\t- Datum found (no move pending).", 
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );
      
    } state init_idle   
    
/* ==================================================================== */

    when ( delay(2.0) )			/* condition polling time n sec	*/
    {  } state not_Datumed
    
/* ==================================================================== */
    
  }		/* (state not_Datumed)	*/

/* ==================================================================== */
/* -------------------------------------------------------------------- */
/* ==================================================================== */
/* state searching_for_Datum - This state is only used for mechanisms which
 * have incremental encoders, or which are moved by dead reckoning, and hence
 * need to be Datumed before they can be positioned. The state is entered when
 * the mechanism is in the process of finding its Datum.
 *
 * Datum search completes when no move is pending. Wait at least 0.5 seconds. 
 * ===================================================================== 
 */

  state searching_for_Datum
  {
/* ====================================================================	*
 * Start of CAD flag reactions						*
 * ====================================================================	*/
/* The commands will have no effect because the Datum search is already in progress. */

    when ( efTestAndClear( DatumStartFlag ) || efTest( ParkStartFlag ) )
    {
      if (efTest( ParkStartFlag ))
           { STARTFLAG_REACTION ( "Park command activated"); }
      else { STARTFLAG_REACTION ("Datum command activated"); }
      
      if (efTestAndClear( ParkStartFlag ))
           sprintf( message, "\t%s (%d)\t- INFO: Datum search in progress.",compdescr, mechindex );
      else sprintf( message, "\t%s (%d)\t- INFO: Datum search already in progress.",compdescr, mechindex);
      agLogMessage( mechindex, DEB_MIN, message );

    } state init_searching_for_Datum
    

    when ( efTestAndClear( InitStartFlag ) )
    {  } state resetting

/* ==================================================================== */
/* In the "searching_for_Datum" state the current location of the mechanism
 * is unknown. The demand position is updated, and the mechanism will attempt
 * to go to this position only when the Datum search has been completed.
 *
 * Copy the demanded engineering position to the motors database and enable
 * motor movement.
 */
   when ( efTestAndClear( EngStartFlag ) )
    {
      STARTFLAG_REACTION ("Move command activated");

      sprintf( message,"\t%s (%d)\t- WARNING: Searching for Datum - waiting until finished", 
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );
 
      sprintf( message, "\t%s (%d)\t- Demanded position = %d", 
      		compdescr, mechindex, motorDemand[0] );
      for (i=1;i<numbdim;i++)
        sprintf( message, "%s, %d", message, motorDemand[i] );
      agLogMessage( mechindex, DEB_MIN, message );
      
    } state init_searching_for_Datum

/* ==================================================================== */
/* Because the Datum search was interrupted, the Datum has not yet been found,
 * so switch back to the "not_Datumed" state.
 */
   when ( efTestAndClear( DatumStopFlag) || 
 	  efTestAndClear( ParkStopFlag ) ||   	  
    	  efTestAndClear( StopStopFlag ) || 
    	  efTestAndClear( StopStartFlag) || 
 	  efTestAndClear( EngStopFlag  ) )
    {
      STARTFLAG_REACTION ("Stop command activated");
   /* compCARin    = menuCarstatesBUSY;  pvPut( compCARin  );  */  /* done by CAD already */
      
      for (i=0;i<numbdim;i++)
      { motorEnable [i] = FALSE; 	pvPut( motorEnable [i] );	/* Disable movement. 	*/
        motorDsearch[i] = FALSE; 	pvPut( motorDsearch[i] );	/* Cancel Datum search mode. */
      }

      if (getsimu(mechindex)!=SIM_NONE)					/* IDLE only if simulated */
      { compCARin = menuCarstatesIDLE;		pvPut( compCARin );	}
      
    } state init_not_Datumed_delayed

/* ==================================================================== */
/* Start of non-simulated conditions (state searching_for_Datum)	*/
/* ==================================================================== */

    when ( getsimu(mechindex)==SIM_NONE	&& PLCResp < 0 && delay (1) )
    {
      CHECK_DATUM_FOUND;
    } state init_not_Datumed

/* ==================================================================== */

    when ( getsimu(mechindex)==SIM_NONE	&& PLCResp==0 && delay (1) )
    {
      CHECK_DATUM_FOUND;
    } state init_idle
    
/* ==================================================================== */

    when ( delay(2.0) )			/* condition polling time n sec	*/
    {  } state searching_for_Datum
   
/* ==================================================================== */
/* Start of simulation mode conditions	(state searching_for_Datum)	*/
/* ==================================================================== */

    when( getsimu(mechindex)!=SIM_NONE 		&&
	  motorDsearch[0] == FALSE	       	&&
	  motorDemand [0] == motorCurrent [0] 	&&
 	  motorDemand [1] == motorCurrent [1]  	&&
	  motorDemand [2] == motorCurrent [2]  	&&
	  delay(0.5) 				)
    {
      sprintf( message, "\t%s (%d)\t- Datum found (no simulated move pending).", 
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );
      compDatumed = TRUE;	pvPut( compDatumed );	/* Set the Datumed flag true. */

    } state init_idle
    
/* ==================================================================== */
/* Datum search completes, move is pending. Wait at least 0.5 seconds. */

    when( getsimu(mechindex)!=SIM_NONE 		&&
	  motorDsearch[0] == FALSE 		&& 
	  motorDsearch[1] == FALSE 		&& 
	  motorDsearch[2] == FALSE 		&& 
	( motorDemand [0] != motorCurrent [0] 	||
	  motorDemand [1] != motorCurrent [1] 	||
	  motorDemand [2] != motorCurrent [2] )	&&
	  delay(0.8)				)
    {
      sprintf( message, "\t%s (%d)\t- Datum found (move pending).", compdescr, mechindex );
      agLogMessage( mechindex, DEB_FULL, message );

      compDatumed = TRUE;		pvPut( compDatumed );
      strcpy( compState, "MOVING" );	pvPut( compState );

      for (i=0;i<numbdim;i++)		motorMoving[i] = TRUE;

    } state init_moving
    
/* ==================================================================== */
/* in Simu-Mode, assume "datumed" after an error (timeout) anyway
 *
 * Waiting for a timeout delay always causes problems with the delay
 *   function described above - next part is disabled therefore.	
 */
 
/*  when( getsimu(mechindex)!=SIM_NONE		&&
    	  delay(TIMEOUT_SIMU) 			)
    { sprintf( message, "\t%s (%d)\t- Datum TO, Ds=%d %d %d, Cur=%d %d %d, CDO=%d", 
    		compdescr, mechindex,
      		motorDsearch[0], motorDsearch[1], motorDsearch[2], 
           	motorCurrent[0], motorCurrent[1], motorCurrent[2], TRUE);
      agLogMessage( mechindex, DEB_MIN, message );
    } state init_idle
*/

  }		/* (state searching_for_Datum)	*/

/* ==================================================================== */
/* -------------------------------------------------------------------- */
/* ==================================================================== */
/* state idle - This is the state which is entered after the Datum 
 * has been successfully found and the coordinate system established.
 *
 * Wait until an event flag is triggered indicating when a CAD record 
 * has been activated.
 * ===================================================================== */

  state idle
  {
/* ====================================================================	*/
/* Start of CAD flag reactions						*/
/* ====================================================================	*/

    when ( efTestAndClear( DatumStartFlag ) )
    {
      STARTFLAG_REACTION ("Datum command activated");
    } state init_searching_for_Datum

    when ( efTestAndClear( ParkStartFlag ) )
    {
      STARTFLAG_REACTION ("Park command activated");
    } state init_moving
    
    when ( efTestAndClear( InitStartFlag ) )
    {  } state resetting

/* ==================================================================== */
/* If the current and demand positions are the same:
 * Set the motorMoving flag to FALSE and then switch to the "moving" state.
 * This flag setting will cause almost immediate switch back to the "idle"
 * state.
 *
 * If the current and demand positions are different:
 * Ensure the motorMoving flag is TRUE so that the next change in state
 * will be triggered by a TRUE to FALSE transition. (Failing to do this
 * could cause an immediate change of state if, due to some latency, the
 * underlying mechanism has not yet started moving).
 */
    when ( efTestAndClear( EngStartFlag ) )
    {
      STARTFLAG_REACTION ("Move command activated");

      sprintf( message, "\t%s (%d)\t- Demanded position = %d", 
      		compdescr, mechindex, motorDemand[0] );
      for (i=1;i<numbdim;i++)
        sprintf( message, "%s, %d", message, motorDemand[i] );
      agLogMessage( mechindex, DEB_MIN, message );

      for (i=0;i<numbdim;i++)
      { pvGet(motorCurrent[i] );
        if (  motorCurrent[i] == motorDemand[i]) motorMoving[i] = FALSE;
        else					 motorMoving[i] = TRUE;
      }

    } state init_moving

/* ==================================================================== */
/* Although the "stop" command is acceptable, a warning should be issued
 * because the command is not expected unless the mechanism is moving.
 */
 
    when ( efTestAndClear( DatumStopFlag) || 
	   efTestAndClear( ParkStopFlag ) ||
    	   efTestAndClear( StopStopFlag ) || 
    	   efTestAndClear( StopStartFlag) || 
    	   efTestAndClear( EngStopFlag  ) )
    {
      STARTFLAG_REACTION ("Stop command activated");
   /* compCARin    = menuCarstatesBUSY;  pvPut( compCARin  );  */  /* done by CAD already */

      sprintf( message,"\t%s (%d)\t- WARNING: Mechanism is not moving.",
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );

    } state init_idle_delayed

/* ==================================================================== */
/* Start of non-simulated conditions (state idle)			*/
/* ==================================================================== */
  
    when ( getsimu(mechindex)==SIM_NONE  &&  PLCResp > 0	&&
       	   PLCResp != FOLLOW_ON && PLCResp != FOLLOW_ON2	&&
       	   delay (1)	)
    {  } state init_moving	
    
/* ==================================================================== */

    when ( delay(2.0) )			/* condition polling time n sec	*/
    {  } state idle
    
/* ==================================================================== */
/* Start of simulation mode conditions (state idle)			*/
/* ==================================================================== */
/* ==================================================================== */
/* Whenever there is a loss of mechanism position the controller should
 * return to the "not_Datumed" state.
 */
    when ( getsimu(mechindex)!=SIM_NONE	&& compDatumed == FALSE )
    {
      sprintf( message, "\t%s (%d)\t- Mechanism Datum flag lost.", 
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );

      compParked = FALSE;	pvPut( compParked );

    } state init_not_Datumed

/* ==================================================================== */

/* Send a "busy" event to the mechanism CAR record.  The event is probably the
 * result of an engineer poking around with the database.
 * The mechanism cannot be Parked during the movement. 
 *
 * Change state according to the status of the mechanism control flags 
 */
    when ( getsimu(mechindex)!=SIM_NONE	&&
    	   compDatumed    == TRUE		&&
    	 ( motorMoving[0] == TRUE || 
    	   motorMoving[1] == TRUE || 
   	   motorMoving[2] == TRUE ))
    {
      sprintf( message,"\t%s (%d)\t- Mechanism started moving spontaneously!", 
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );

      compCARin = menuCarstatesBUSY;	pvPut( compCARin );
      compParked = FALSE;	pvPut( compParked );
      strcpy( compState, "MOVING" ); pvPut( compState );

    } state init_moving

/* ==================================================================== */
  }		/* (state idle)	*/


/* ==================================================================== */
/* -------------------------------------------------------------------- */
/* ==================================================================== */
/* state moving - This state is entered when the mechanism is moving to a
 * demanded location.
 * 
 * Wait until an event flag is triggered indicating when a CAD record has been
 * activated. Incoming commands do not change the current state directly, but
 * the state will change when the commands cause the "compDatumed" and
 * "motorMoving" flags to change.
 * ===================================================================== */

  state moving
  {
/* ====================================================================	*/
/* Start of CAD flag reactions						*/
/* ====================================================================	*/

    when ( efTestAndClear( DatumStartFlag ) )
    {
      STARTFLAG_REACTION ("Datum command activated");
      sprintf( message, "\t%s (%d)\t- INFO: Current movement abandoned.",
      		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );
      
    } state init_searching_for_Datum
    
    when ( efTestAndClear( ParkStartFlag ) )
    {
      STARTFLAG_REACTION ("Park command activated");
      sprintf( message, "\t%s (%d)\t- INFO: Current movement abandoned.",
       		compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );
      
    } state init_moving
    
    when ( efTestAndClear( InitStartFlag ) )
    {  } state resetting
    
/* ==================================================================== */
/* Copy the demanded engineering position to the motors database and enable
 * motor movement.
 *
 * Continue in the "moving" state. The mechanism will keep moving,
 * but it will now have a new demanded position.
 */
 
    when ( efTestAndClear( EngStartFlag ) )
    {
      STARTFLAG_REACTION ("Move command activated");
      sprintf( message, "\t%s (%d)\t- INFO: Old move command overridden.",
        compdescr, mechindex );
      agLogMessage( mechindex, DEB_MIN, message );

      sprintf( message, "\t%s (%d)\t- New demanded position = %d", 
        compdescr, mechindex, motorDemand[0] );
      for (i=1;i<numbdim;i++)       sprintf( message, "%s, %d", message, motorDemand[i] );
      agLogMessage( mechindex, DEB_MIN, message );
 
     } state init_moving
     
/* ==================================================================== */
/* Stopflag in non-simulated mode should not lead to IDLE immediately ?!*/ 
    when ( /* (getsimu(mechindex)==SIM_NONE ) && */
	  (efTestAndClear( DatumStopFlag) || 
  	   efTestAndClear( ParkStopFlag ) || 
    	   efTestAndClear( StopStopFlag ) || 
    	   efTestAndClear( StopStartFlag) || 
   	   efTestAndClear( EngStopFlag  ) ))
    {
      STARTFLAG_REACTION ("Stop command activated");
   /* compCARin    = menuCarstatesBUSY;  pvPut( compCARin  );  */  /* done by CAD already */

      for (i=0;i<numbdim;i++)
      { motorEnable[i] = FALSE;	pvPut( motorEnable[i] );
      }
    } state init_idle_delayed

/* ==================================================================== */
/* Start of non-simulated conditions (state moving)			*/
/* ==================================================================== */

    when (  (getsimu(mechindex)==SIM_NONE)  && delay (0.8) 	&&  
    	  ( (PLCResp <= 0)	   			   || 
    	    (PLCResp==FOLLOW_ON) || (PLCResp==FOLLOW_ON2)  )	)	
    {       
      STARTFLAG_REACTION ("Move finished, mechanism idle");
    } state init_idle

/* ==================================================================== */
/* Due to a severe bug in the sequencer, we need a transition to the 
 *  same state which contains a delay time after which all the other
 *  conditions in this state are tested again. 
 * In each state, conditions which have to be polled and are not 
 *  event-triggered like monitored EPICS channels, are just tested once
 *  at their specified delay time.
 * In order to allow polling of e.g. global c variable conditions,
 *  such a dummy transition to itself has to be included in every state.
 * Unfortunately, that delay time has to be bigger than all other delay
 *  times in the state which doesn't allow to use timeout delays at all.
 * There is no need to specify more than 1 delay in a state.
 */

    when ( delay(1.0) )			/* condition polling time n sec	*/
    {  } state moving

  
/* Even a dummy transition to a dummy state which will never be used 
 *  helps once at the end of the specified delay but doesn't help 
 *  with polling conditions multiple times.
 */
    when ( FALSE  &&  delay(6.0) )
    {  }   state init1

/* ==================================================================== */
/* Start of simulation mode conditions (state moving)			*/
/* ==================================================================== */
/* Ensure there is a delay of at least 0.5 seconds before the mechanism
 * stop event is detected.
 *
 * If the mechanism has successfully reached the demanded position, and
 * it has stopped in the Parked position, set the "Parked" flag. This extra
 * check ensures that the "Parked" flag is only set when the mechanism is
 * successfully asked to Park, and it has not accidentally stopped or found
 * itself at the Park position.
 */
    when ( getsimu(mechindex)!=SIM_NONE 	&&
     	   motorMoving[0] == FALSE  	 	&& 
     	   motorMoving[1] == FALSE  		&& 
     	   motorMoving[2] == FALSE   		&&
    	   delay (0.5)				)
    {
      for (i=0;i<numbdim;i++)
      { pvGet( motorDemand [i] );
        pvGet( motorCurrent[i] );
      }
      
      if (( motorCurrent[0] == motorDemand[0] )&& (motorCurrent[0] == 0) &&
	  ( motorCurrent[1] == motorDemand[1] )&& (motorCurrent[1] == 0) &&
	  ( motorCurrent[2] == motorDemand[2] )&& (motorCurrent[2] == 0) )
      {  compParked = TRUE;	pvPut( compParked );	}

      sprintf( message, "\t%s (%d)\t- Mechanism stopped moving.",
        compdescr, mechindex);
      agLogMessage( mechindex, DEB_MIN, message );
      sprintf( message, "\t%s (%d)\t- Demand=%d Current=%d.",
        compdescr, mechindex, motorDemand[0], motorCurrent[0]);
      agLogMessage( mechindex, DEB_FULL, message );
 
    } state init_idle
    
/* ==================================================================== */
/* Since an error has occurred from which recovery is possible, the health
 * of the mechanism changes to WARNING.
 * Continue in the "moving" state and wait for the operator to do something.
 *
 * Waiting for a timeout delay always causes problems with the delay
 *   function described above - next part is disabled therefore.	
 */
/*  when ( getsimu(mechindex)!=SIM_NONE 	&&
    	   delay(TIMEOUT_SIMU) 			)
    { sprintf( message, "\t%s (%d)\t- ERROR: Movement timed out - still trying.", 
    		compdescr, mechindex );
      agLogMessage( mechindex, DEB_ERROR, message );
      compCARin 	= menuCarstatesERROR;		pvPut ( compCARin );
      compCARerrin 	= FAIL;			pvPut ( compCARerrin );
      strcpy ( compCARmessin, "Timed out" ); 	pvPut ( compCARmessin );
      strcpy ( compHealth,    "WARNING" );   	pvPut ( compHealth );
     } state init_moving
*/

  }		/* (state moving)	*/

/* ==================================================================== */
/* -------------------------------------------------------------------- */
/* ==================================================================== */
/* state resetting - This state is entered while the mechanism is
 * waiting for the system to start resetting. Once this happens, the
 * component is reset.
 * Reset the motors database 
 * ===================================================================== */

  state resetting
  {
    when ()
    {
      strcpy( compState, "RESETTING" ); pvPut( compState );
      strcpy( compHealth, "GOOD" ); 	pvPut( compHealth );
      strcpy( compCARmessin, " " ); 	pvPut( compCARmessin );
      compCARerrin = PASS;	 	pvPut( compCARerrin );
      compCARin    = menuCarstatesBUSY;	 	pvPut( compCARin );
      compParked   = FALSE; 		pvPut( compParked );
            
      sprintf( message, "\t%s (%d)\t- Init command activated.", 
      		compdescr, mechindex);
      agLogMessage( mechindex, DEB_MIN, message );

      for (i=0;i<numbdim;i++)
      { motorEnable [i] = FALSE; 	pvPut( motorEnable [i] );
        motorDsearch[i] = FALSE; 	pvPut( motorDsearch[i] );
        motorDemand [i] = 0;		pvPut( motorDemand [i] );
        
      /* The simu global variable was set just before by CAD_init.
       * Now, switch on the simulation database for the mechanism.
       */
        if ( (((getsimu(mechindex)==SIM_NONE))) )
	     strcpy (motorScan[i], "Passive" ); /* motorScan[i] = SCAN_Pass;  */
	else strcpy (motorScan[i], "1 second"); /* motorScan[i] = SCAN_1s;    */
	pvPut ( motorScan [i] );
      }

      if ( getsimu(mechindex)==SIM_NONE )
      {  EngDIR = menuDirectiveMARK;	pvPut( EngDIR );	/* stop all current motions	*/
      }
    } state resetting2
  }

  state resetting2
  {
    when (delay (0.1))
    {  
      if ( getsimu(mechindex)==SIM_NONE )
      {  EngDIR = menuDirectiveSTOP;	pvPut( EngDIR );	/* stop all current motions	*/
      }
    } state resetting3
  }

  state resetting3
  {
    when (delay (1.5))
    {    } state init_not_Datumed
  }
}

/* ==================================================================== */
/* ==================================================================== */

