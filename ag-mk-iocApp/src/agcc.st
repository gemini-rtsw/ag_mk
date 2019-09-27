/*
 *  FILENAME
 *  --------
 *  agcc.stpp
 *
 *  PURPOSE
 *  -------
 *  This file contains the EPICS state transition language program for
 *  managing the A&G Components Controller as a whole
 *
 *  There is a state set for managing each of the system commands,
 *  which are commands such as "datum" and "park" that affect all the
 *  components as a whole. The main purpose of these command-specific
 *  state sets is to manage the CAR record associated with the command.
 *
 *  ICD14: If an instrument requires any new system commands a new state
 *  set, xxx_ss, should be added for each new command.
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  cc_ss      - Manage initialisation of A&G Components Controller.
 *  datum_ss   - Process "datum" command and manage "datumC" CAR record.
 *  park_ss    - Process "park" command and manage "parkC" CAR record.
 *  test_ss    - Process "test" command and manage "testC" CAR record.
 *
 *  PROGRAM
 *  --------
 *  agcc
 *
 *  INVOCATION
 *  -----------
 *  Include the following line in the VxWorks startup script:
 *
 *  seq &agcc, "top=ag:cc:, sadtop=ag::cc:, sys=sys"
 *
 *  PARAMETERS (all are input)
 *  --------------------------
 *     top      string    String to be substituted for the {top} macro
 *                        used to for the top level name of the A&G CC
 *                        EPICS database. The default value is "ag:cc:"
 *
 *     sadtop   string    String to be substituted for the {sad} macro
 *                        used for the name of the A&G CC Status/Alarm
 *                        Database. The default value is "ag::cc:"
 *
 *     sys      string    String to be substituted for the {sys} macro
 *                        used for the name of the A&G systemwide records.
 *                        The default value is "sys".
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
 *     Several records in the A&G CAD, CAR and Status/Alarm database
 *     are used as external variables. See the declarations in the
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
 *               A&G itself appears stateless in its response to
 *               commands (which is an OCS requirement).               (smb)
 *  16-May-1996: Simulated datum search mechanism added to motors
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
 *               automatically datum when a "move" command is
 *               received in the "not_datumed" state. All "stop"
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
 *  08-Jan-1997: Remove initialisation and connection messages.        (smb)
 *  22-Jan-1997: Component control parts removed, leaving this state
 *               notation  code concerned purely with the A&G system. (smb)
 *  29-Jan-1997: Wait until all components are IDLE before setting
 *               resetC to IDLE.                                       (smb)
 *  04-Feb-1997: Renamed from cicsSt to agcc.                      (smb)
 *  13-Feb-1997: "reset" command removed.                              (smb)
 *  19-Mar-1997: "datum" and "park" commands added.                    (smb)
 *  26-May-1997: Fixed bug in "resetting" state where the CAR record
 *               was not reset properly.                               (smb)
 *  16-Jul-1997: Make sure "initC" or "parkC" go BUSY for at least
 *               0.5 seconds, so the Instrument Sequencer can detect
 *               it.                                                   (smb)
 *  19-Jul-1997: "test" command added.				       (ocf)
 */

/* *INDENT-OFF* */
/*
 * $Log: agcc.st,v $
 * Revision 1.2  2001/08/14 14:00:18  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.1  2001/08/08 12:07:54  ajf
 * ajf: Changes for port to GEM7.
 *
 * Revision 1.2  2000/04/14 13:28:53  cjm
 * Updated for V3-1
 *
 * Revision 1.1.1.1  1998/08/05 21:16:16  Gemini
 * Initial creation of the Gemini A&G repository
 *
 * Revision 1.1.1.1  1998/08/05 21:02:28  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 * Revision 1.1.1.1  1998/08/05 20:48:52  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 * Revision 1.1.1.1  1998/08/04 20:30:55  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 */
/* *INDENT-ON* */

program agcc ("top=ag:cc:, sadtop=ag::cc:, sys=sys")


/* The following option is needed to make the code reentrant */
option +r;


%%#include <ag_define.h>

%%char message[80];     	/* Message buffer */

/*  SUBSYSTEM COMMAND DECLARATIONS
 *
 *  The following declarations assign the variables which are responsible
 *  for detecting the subsystem "init", "datum" and "park" commands.
 *
 *  (1) "long" variables are assigned to counters which are incremented
 *     in the database whenever a successful START directive is detected.
 *     The STOP directive is not monitored because it is rejected by the
 *     "init" CAD record.
 *
 *  (2) An event flag is synchronised with each "long" variable, so the
 *     flag is triggered whenever the variable changes. The net result
 *     is that an event flag is triggered whenever a command is started
 *     or stopped in the outside world.
 */

int    initStart;         /* START counter attached to init CAD record */
assign  initStart to "{top}{sys}InitP:st.VAL";
monitor initStart;
evflag  initStartFlag;   /* Event flag triggered by changes to initStart */
sync    initStart initStartFlag;

int    datumStart;        /* START counter attached to datum CAD record */
assign  datumStart to "{top}{sys}DatumP:st.VAL";
monitor datumStart;
evflag  datumStartFlag;  /* Event flag triggered by changes to datumStart */
sync    datumStart datumStartFlag;

int    parkStart;        /* START counter attached to park CAD record */
assign  parkStart to "{top}{sys}ParkP:st.VAL";
monitor parkStart;
evflag  parkStartFlag;  /* Event flag triggered by changes to parkStart */
sync    parkStart parkStartFlag;

int    testStart;        /* START counter attached to test CAD record */
assign  testStart to "{top}{sys}TestP:st.VAL";
monitor testStart;
evflag  testStartFlag;  /* Event flag triggered by changes to testStart */
sync    testStart testStartFlag;

/* CAR AND SIR RECORD DECLARATIONS
 *
 * The following declarations assign variables to records in the Status/Alarm
 * database, which are monitored by the outside world.
 */

int   initCARin;          /* Input to the initC CAR record */
assign initCARin to "{top}initC.IVAL";
int   initCARerrin;       /* Error input to the initC CAR record */
assign initCARerrin to "{top}initC.IERR";
string initCARmessin;    /* Message input to the initC CAR record */
assign initCARmessin to "{top}initC.IMSS";

int   datumCARin;         /* Input to the datumC CAR record */
assign datumCARin to "{top}datumC.IVAL";
int   datumCARerrin;      /* Error input to the datumC CAR record */
assign datumCARerrin to "{top}datumC.IERR";
string datumCARmessin;   /* Message input to the datumC CAR record */
assign datumCARmessin to "{top}datumC.IMSS";

int   parkCARin;          /* Input to the parkC CAR record */
assign parkCARin to "{top}parkC.IVAL";
int   parkCARerrin;       /* Error input to the parkC CAR record */
assign parkCARerrin to "{top}parkC.IERR";
string parkCARmessin;    /* Message input to the parkC CAR record */
assign parkCARmessin to "{top}parkC.IMSS";

int   testCARin;          /* Input to the testC CAR record */
assign testCARin to "{top}testC.IVAL";
int   testCARerrin;       /* Error input to the testC CAR record */
assign testCARerrin to "{top}testC.IERR";
string testCARmessin;    /* Message input to the testC CAR record */
assign testCARmessin to "{top}testC.IMSS";

string  compCARout;       /* Output from the compC CAR record */
assign  compCARout to "{top}hardC.VAL";
monitor compCARout;


int   ccHeart;            /* A&G Components Controller heart beat record */
assign ccHeart to "{sadtop}present.VAL";

string ccState;          /* A&G Components Controller state SIR record */
assign ccState to "{sadtop}state.VAL";

string ccHealth;         /* A&G Components Controller health SIR record */
assign ccHealth to "{sadtop}health.VAL";



/* string mailbox1;         		*/	/* PMAC 1 mailbox string */
/* assign mailbox1 to "ag:cc:pmac1mailbox.VAL";	*/
/* string mailbox2;         		*/	/* PMAC 2 mailbox string */
/* assign mailbox2 to "ag:cc:pmac2mailbox.VAL";	*/

/* EVENT FLAGS
 *
 * The following event flags are used to synchronise between state sets.
 */

evflag initialisedFlag;  /* Event flag to signal when initialised */

int mechindex;

/* ====================================================================	*/

ss cc_ss
{

/*+
 *   Function name:
 *   State set "cc_ss"
 *
 *   Purpose:
 *   Manage initialisation of A&G Components Controller
 *
 *   This state set initialises the system. It then monitors the CAD record
 *   associated with the INIT command and reinitialises the system when
 *   necessary.
 *
 *   Invocation:
 *   Invoked automatically when sequence program "agcc" starts.
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
 *   Same as requirements for program "agcc"
 *
 *   Limitations:
 *   Same as limitations for program "agcc"
 *
 *-
 */

/* -------------------------------------------------------------------- */
/* state init1 - This is the state the comp_ss state set begins in
 * when it first starts running. Its purpose is just to issue a message
 * indicating that the A&G state notation code has started. Execution
 * then passes immediately to state init2.
 */
  state init1
  {
    when ()
    {
      efClear( initialisedFlag );

/* The issuing of the startup messages has been commented out because it
 * cluttered up the console screen. It can be reinstated for system tests.
 */
    mechindex = query_cadname (macValueGet("top"));

    sprintf( message, "A&G CC connecting...:	%s", macValueGet("top"));
    agLogMessage( mechindex, DEB_FULL, message );

    } state init2
  }

/* -------------------------------------------------------------------- */
/* state init2 - In this state comp_ss carries out all the initialisation
 * which is necessary before commands can be executed.
 */
 
  state init2
  {					/* Wait until all the appropriate connections have been made. */
    when ( pvConnectCount( ) == pvChannelCount( ) )
    {
      sprintf( message, "A&G CC connected. Initialising...:	%s", macValueGet("top"));
      agLogMessage( mechindex, DEB_FULL, message );

/* Send a "busy" event to the initC CAR record. Clients can check this record
 * to determine when the system is initialising and when it becomes ready
 * to receive commands.
 */
      initCARin = menuCarstatesBUSY;			pvPut( initCARin );	

      strcpy( ccState, "INITIALISING" );	pvPut( ccState );
      strcpy( ccHealth, "GOOD" );		pvPut( ccHealth );

      ccHeart = 0;				pvPut ( ccHeart );	/* Initialise the heart beat */

/* Here I will include other housekeeping actions, such as reading
 * lookup tables from a file.
 */

      efClear( initStartFlag  );	/* Ensure the event flags to be	monitored	*/
      efClear( datumStartFlag ); 	/*   later are initially cleared. 		*/
      efClear( parkStartFlag  );
      efClear( testStartFlag  );

      strcpy( ccState, "RUNNING" );	/* Initialisation complete, so set the A&G state. */
      pvPut ( ccState );

      sprintf( message, "A&G CC Initialisation completed: %s, mi=%d", macValueGet("top"), mechindex );
      agLogMessage( mechindex, DEB_FULL, message );

/* Send an "idle" event to the initC CAR record to inform clients the system
 * is ready to receive commands.
 */
      initCARin = menuCarstatesIDLE;		pvPut( initCARin );

      efSet( initialisedFlag );		/* Set the initialised flag to start the other state sets. */

    } state running			/* Jump to the "running" state. */
  }
 
/* -------------------------------------------------------------------- */
/* state running - This is the main state for the A&G. It will remain in
 * this state until told to reinitialise.
 */

  state running
  {

/* Wait until an event flag is triggered indicating when a CAD record has been
 * activated.
 */
    when ( efTest( initStartFlag ) )
    {
      efClear( initStartFlag );

      agLogMessage( mechindex, DEB_MIN, "A&G - Init command activated.");

      strcpy( ccState, "RESETTING" );	/* Switch to the "resetting" state. */
      pvPut( ccState );

/* Ensure that compCARout is BUSY, so the next state transition is triggered
 * by a change from BUSY to IDLE.
 */
  /*    strcpy( compCARout, "BUSY" );	*/

    } state resetting

    when ( delay( 1.0 ) )		/* Every second increment the heart beat */
    {
      ccHeart = ccHeart + 1;
      pvPut( ccHeart );
    } state running
 }

/* -------------------------------------------------------------------- */
/* state resetting - This state is entered while waiting for all the
 * system components to reset. Rather than wait for the components to
 * go idle, it is safer to wait until they are not busy, as this allows
 * for one or more components to go into the error state.
 * Ensure there is a delay of at least 0.5 seconds so the Instrument Sequencer
 * will notice the change.
 */
  state resetting
  {
    when ( /* (strcmp( compCARout, "BUSY" ) != 0) && */
    		delay( 5.5 ) )
    {
      agLogMessage( mechindex, DEB_FULL, "Init - all components idle." );

      strcpy( ccState, "RUNNING" );	pvPut( ccState );	/* Reset the SAD records */
      
      datumCARin = menuCarstatesIDLE;	pvPut( datumCARin );		/* Reset any CAR records*/
      parkCARin  = menuCarstatesIDLE;	pvPut( parkCARin );		/*  which may have been */
      testCARin  = menuCarstatesIDLE;	pvPut( testCARin );		/*  left BUSY. 		*/
      ccHeart 	 = 0;		pvPut ( ccHeart );		/* Initialise the heart beat */

    } state running		/* Finally switch back to the "running" state. */

/* NOTE: There is a problem in that, in a situation where none
 * of the components are moving when the INIT command is issued, the
 * compCARout field is already IDLE when the "resetting" state is entered.
 * This ought to cause an immediate change of state to "init2". Unfortunately,
 * although compCARout is already IDLE it will only generate a monitor if
 * it changes, so the above "when" statement will never be triggered.
 * As a work around, the field is also polled here every second.
 */
/*
    when ( delay( 2.5 ) )
    { pvGet( compCARout );
    } state resetting
*/
  }
}

/* ==================================================================== */

ss datum_ss
{

/*+
 *   Function name:
 *   State set "datum_ss"
 *
 *   Purpose:
 *   Manage datumC CAR record of A&G Components Controller
 *
 *   This state set monitors the CAD record associated with the DATUM
 *   command and ensures the "datumC" CAR record is set BUSY and IDLE
 *   at the correct times. The actual datuming of the mechanisms is handled
 *   by the EPICS database, which reports its progress through the "compC"
 *   CAR record. The state set is necessary purely to ensure there is
 *   a "datumC" CAR record with the behaviour expected by the OCS.
 *
 *   Invocation:
 *   Invoked automatically when sequence program "agcc" starts.
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
 *   Same as requirements for program "agcc"
 *
 *   Limitations:
 *   Same as limitations for program "agcc"
 *
 *-
 */

/* -------------------------------------------------------------------- */

  state datum_init
  {

/* state datum_init - Wait until the main state set is initialised.
 */

    when ( efTest( initialisedFlag ) )
    {

    } state datum_idle
  }

/* -------------------------------------------------------------------- */

  state datum_idle
  {


/* state datum_idle - The state set remains in this state until a "datum"
 * command is recognised.
 */

/* Wait until the "datum" CAD record is activated.
 */

    when ( efTest( datumStartFlag ) )
    {
      efClear( datumStartFlag );

      agLogMessage( mechindex, DEB_MIN, "A&G - Datum command activated.");

      datumCARin = menuCarstatesBUSY;
      pvPut( datumCARin );

/*
 * Ensure that compCARout is BUSY, so the next state transition is triggered
 * by a change from BUSY to IDLE, and switch to the "datum_busy" state.
 */
      strcpy( compCARout, "BUSY" );

    } state datum_busy
  }

/* -------------------------------------------------------------------- */

  state datum_busy
  {

/* state datum_busy -  This state is entered while waiting for all the
 * system components to datum. Rather than wait for the components to
 * go idle, it is safer to wait until they are not busy, as this allows
 * for one or more components to go into the error state.
 */

    when ( (strcmp( compCARout, "BUSY" ) != 0) && delay( 3.0 ) )
    {

      agLogMessage( mechindex, DEB_FULL, "Datum - all components idle." );

/* Reset the "datumC" CAR record back to IDLE and switch back to the
 * "datum_idle" state.
 */

      datumCARin = menuCarstatesIDLE;
      pvPut( datumCARin );

    } state datum_idle

/*                               --  --  --                              */       
/*
 * NOTE: There is a problem in that, if there is a situation where none of
 * the components moves in response to the DATUM command, the compCARout
 * field will remain IDLE when the "datum_busy" state is entered.
 * This ought to cause an immediate change of state to "datum_idle".
 * Unfortunately, although compCARout is IDLE it will only generate a monitor
 * if it changes, so the above "when" statement will never be triggered.
 * As a work around, the field is also polled here every 3 seconds.
 */

    when ( delay( 3.0 ) )
    {

      pvGet( compCARout );

    } state datum_busy
  }
}


/* ==================================================================== */

ss park_ss
{

/*+
 *   Function name:
 *   State set "park_ss"
 *
 *   Purpose:
 *   Manage parkC CAR record of A&G Components Controller
 *
 *   This state set monitors the CAD record associated with the DATUM
 *   command and ensures the "parkC" CAR record is set BUSY and IDLE
 *   at the correct times. The actual parking of the mechanisms is handled
 *   by the EPICS database, which reports its progress through the "compC"
 *   CAR record. The state set is necessary purely to ensure there is
 *   a "parkC" CAR record with the behaviour expected by the OCS.
 *
 *   Invocation:
 *   Invoked automatically when sequence program "agcc" starts.
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
 *   Same as requirements for program "agcc"
 *
 *   Limitations:
 *   Same as limitations for program "agcc"
 *
 *-
 */


/* -------------------------------------------------------------------- */

  state park_init
  {

/* state park_init - Wait until the main state set is initialised.
 */

    when ( efTest( initialisedFlag ) )
    {

    } state park_idle
  }

/* -------------------------------------------------------------------- */

  state park_idle
  {


/* state park_idle - The state set remains in this state until a "park"
 * command is recognised.
 */

/* Wait until the "park" CAD record is activated.
 */

    when ( efTest( parkStartFlag ) )
    {
      efClear( parkStartFlag );

      agLogMessage( mechindex, DEB_MIN, "A&G - Park command activated.");

      parkCARin = menuCarstatesBUSY;
      pvPut( parkCARin );

/*
 * Ensure that compCARout is BUSY, so the next state transition is triggered
 * by a change from BUSY to IDLE, and switch to the "park_busy" state.
 */
      strcpy( compCARout, "BUSY" );

    } state park_busy
  }

/* -------------------------------------------------------------------- */

  state park_busy
  {

/* state park_busy -  This state is entered while waiting for all the
 * system components to park. Rather than wait for the components to
 * go idle, it is safer to wait until they are not busy, as this allows
 * for one or more components to go into the error state.
 */

    when ( (strcmp( compCARout, "BUSY" ) != 0) && delay( 3.0 ) )
    {

      agLogMessage( mechindex, DEB_FULL, "Park - all components idle." );

/* Reset the "parkC" CAR record back to IDLE and switch back to the
 * "park_idle" state.
 */

      parkCARin = menuCarstatesIDLE;
      pvPut( parkCARin );

    } state park_idle

/*                               --  --  --                              */       
/*
 * NOTE: There is a problem in that, in a situation where all the components
 * are already parked when the PARK command is issued, the compCARout field
 * will remain IDLE when the "park_busy" state is entered.
 * This ought to cause an immediate change of state to "park_idle".
 * Unfortunately, although compCARout is IDLE it will only generate a monitor
 * if it changes, so the above "when" statement will never be triggered.
 * As a work around, the field is also polled here every 3 seconds.
 */

    when ( delay( 3.0 ) )
    {

      pvGet( compCARout );

    } state park_busy
  }
}



/* ==================================================================== */

ss test_ss
{

/*+
 *   Function name:
 *   State set "test_ss"
 *
 *   Purpose:
 *   Manage testC CAR record of A&G Components Controller
 *
 *   This state set monitors the CAD record associated with the DATUM
 *   command and ensures the "testC" CAR record is set BUSY and IDLE
 *   at the correct times. The actual testing of the mechanisms is handled
 *   by the EPICS database, which reports its progress through the "compC"
 *   CAR record. The state set is necessary purely to ensure there is
 *   a "testC" CAR record with the behaviour expected by the OCS.
 *
 *   Invocation:
 *   Invoked automatically when sequence program "agcc" starts.
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
 *   Same as requirements for program "agcc"
 *
 *   Limitations:
 *   Same as limitations for program "agcc"
 *
 *-
 */


/* -------------------------------------------------------------------- */

  state test_init
  {

/* state test_init - Wait until the main state set is initialised.
 */

    when ( efTest( initialisedFlag ) )
    {

    } state test_idle
  }

/* -------------------------------------------------------------------- */

  state test_idle
  {


/* state test_idle - The state set remains in this state until a "test"
 * command is recognised.
 */

/* Wait until the "test" CAD record is activated.
 */

    when ( efTest( testStartFlag ) )
    {
      efClear( testStartFlag );

      agLogMessage( mechindex, DEB_MIN, "A&G - Test command activated.");

      testCARin = menuCarstatesBUSY;
      pvPut( testCARin );

/*
 * Ensure that compCARout is BUSY, so the next state transition is triggered
 * by a change from BUSY to IDLE, and switch to the "test_busy" state.
 */
      strcpy( compCARout, "BUSY" );

    } state test_busy
  }

/* -------------------------------------------------------------------- */

  state test_busy
  {

/* state test_busy -  This state is entered while waiting for all the
 * system components to test. Rather than wait for the components to
 * go idle, it is safer to wait until they are not busy, as this allows
 * for one or more components to go into the error state.
 */

    when ( (strcmp( compCARout, "BUSY" ) != 0)  && delay( 3.0 ) )
    {

      agLogMessage( mechindex, DEB_FULL, "Test - all components idle." );

/* Reset the "testC" CAR record back to IDLE and switch back to the
 * "test_idle" state.
 */

      testCARin = menuCarstatesIDLE;
      pvPut( testCARin );

    } state test_idle

/*                               --  --  --                              */       
/*
 * NOTE: There is a problem in that, in a situation where all the components
 * are already parked when the test command is issued, the compCARout field
 * will remain IDLE when the "test_busy" state is entered.
 * This ought to cause an immediate change of state to "test_idle".
 * Unfortunately, although compCARout is IDLE it will only generate a monitor
 * if it changes, so the above "when" statement will never be triggered.
 * As a work around, the field is also polled here every 3 seconds.
 */

    when ( delay( 3.0 ) )
    {

      pvGet( compCARout );

    } state test_busy
  }
}
