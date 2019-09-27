/* static char rcsid[]="$Id: cicsLib.c,v 1.3 2001/08/14 14:00:18 ajf Exp $"; */
/*
 *  FILENAME
 *  -------- 
 *  cicsLib.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all the library functions used by the
 *  Core Instrument Control System
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  cicsCheckBusy     - Check if character string contains CAR BUSY code
 *  cicsCheckIdle     - Check if character string contains CAD IDLE code
 *  cicsCheckMarked   - Check if character string contains CAD "marked" value
 *  cicsCheckPaused   - Check if character string contains CAR PAUSED code
 *  cicsLogMessage    - Log a message.
 *  cicsGetTop        - Get top level prefixes for EPICS database.
 *  cicsSetTop        - Set top level prefixes for EPICS database.
 *
 *  DEPENDENCIES
 *  ------------
 *
 *  LIMITATIONS
 *  ------------
 *  The maximum EPICS string size (MAX_STRING_SIZE) is quite small, and
 *  some messages might be truncated before being written to the "historyLog"
 *  record.
 *
 *  The VxWorks logMsg() function returns before the message you have given
 *  it has been displayed. On the one hand this means the function does not
 *  delay real-time code. On the other hand this means that if logMsg() is
 *  given a message buffer, that message buffer can be overwritten before
 *  the message is displayed. The symptoms are some messages getting lost
 *  while others are repeated. I have used a ring buffer in cicsLogMessage()
 *  as a means of alleviating the problem, but it will still happen if
 *  there are sufficient messages to fill the ring buffer
 *
 *  AUTHOR
 *  ------
 *  Steven Beard  (smb@roe.ac.uk)
 *  Janet Tvedt   (tvedt@noao.edu)
 *
 *  HISTORY
 *  -------
 *  04-Dec-1996: Original version with just cicsLogMessage,
 *               cicsLogLong and cicsLogString, based on Michelle
 *               logging library (which did not conform to the
 *               Gemini SPS).                                        (smb)
 *  16-Dec-1996: cicsLogFloat added.                                 (smb)
 *  10-Jan-1997: cicsLogDouble added.                                (smb)
 *  15-Jan-1997: A means of setting and testing the debug level
 *               added. Fixed some syntax and formatting problems
 *               noticed by Janet Tvedt.                             (smb)
 *  16-Jan-1997: Functions renamed to conform to new Gemini SPS.     (smb)
 *  23-Jan-1997: Removed the "static" storage class specifier on
 *               the various message string buffers. This was
 *               causing messages generated simultaneously by
 *               different parallel processes to be overwritten.
 *               Use MAX_STRING_SIZE instead of hard-wired size for
 *               log message.                                        (smb)
 *  27-Jan-1997: Modified cicsLogMessage to use a ring buffer of
 *               messages to get around a deficiency of logMsg().    (smb)
 *  04-Jun-1997: Size of message buffer increased from 40 to 64.     (smb)
 *  17-Jun-1997: Modified to use a semaphore to ensure that two
 *               tasks do not attempt to use the same element of
 *               the message buffer at the same time.                (smb)
 *  17-Jun-1997: Set top level prefixes. Janet Tvedt's database
 *               access functions added.                             (smb,tvedt)
 *  26-Jun-1997: Channel Access get and put functions added, but
 *               then transferred to "cicsLib2.c" because it was
 *               not possible to include "dbAccess.h" and
 *               "cadefs.h" in the same file..                       (smb)
 *  12-Aug-1997: Added check functions used by CAD functions.        (smb)
 *  30-Jan-1998: DBPut and DBGet moved to "DBLib.c"                  (ocf)
 */
/* *INDENT-OFF* */
/*
 * $Log: cicsLib.c,v $
 * Revision 1.3  2001/08/14 14:00:18  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.2  2000/05/06 04:28:14  cboyer
 * New version of Olaf V3-2 5May 2000
 *
 * Revision 1.1.1.1  1999/12/03 22:49:14  ajf
 * Initial creation of the Gemini A&G repository
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


/* Global Constants */

#include  <epicsStdioRedirect.h>
#include  <registryFunction.h>
#include  <epicsExport.h>
#include  <epicsStdioRedirect.h>
#include  <epicsStdlib.h>
#include  <epicsEvent.h>
#include  <epicsPrint.h>
#include  <math.h>
#include  <time.h>
#include  <string.h>
#include  <stdlib.h>

#include  <dbDefs.h>
#include  <dbCommon.h>
#include  <recSup.h>
#include  <dbAccess.h>
#include  <menuCarstates.h>

#include  <cicsConst.h>
#include  <cicsLib.h>

/* Global Variables */

static char cicsTop[MAX_STRING_SIZE] = "cics:";      /* Top level prefix */
static char cicsSadtop[MAX_STRING_SIZE] = "cics::";  /* Top level SAD prefix */


/* ===================================================================== */

/*+
 * Function name:
 * ciscCheckCadCarCode
 *
 * Purpose:
 * Read an input string looking for a specific code.
 *
 * Invocation:
 * status = ciscCheckCadCarCode( string, expected, altExpected);
 *
 * or
 *
 * code = ciscCheckCadCarCode( string, expected, NULL);
 *
 * Parameters in:
 *    string          *string        string containing a CAR/CAD value.
 *    expected        long           an integer value to be compared with string
 *    altExpected     *string        if not NULL, this will be compared against
 *                                   string, if the original value cannot be
 *                                   converted to a singled digit integer
 *
 * Parameters out:
 *
 * Return value:
 *    < status        unsigned int   = 1 if the given string can be converted
 *                                     to an integer equal to "expected" or,
 *                                     if it cannot, if it's equal to
 *                                     "altExpected" (in case it is not NULL)
 *                                   = 0 otherwise
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Author:
 *   Ricardo Cardenes  (rcardenes@gemini.edu)
 *
 *   History:
 *   23-Feb-2018: Original version                         (rcardenes)
 *-
 */
unsigned int ciscCheckCadCarCode(const char *string, long expected, const char *altExpected)
{
	long ivalue;           /* Argument converted to integer */
	unsigned status = 0;   /* return value */
	char *endptr;

	if ( string != NULL ) {
		/* Try to convert to integer */
		ivalue = strtol( string, &endptr, 10);

		if ( (*endptr) == 0 ) {
			/*
			 * Successful conversion.
			 * Check if the argument translates to "expected"
			 */
			if ( ivalue == expected )
				status = 1;
		}
		/* More than one character in the string. Check for the "BUSY". */
		else if ( altExpected && (strncmp( string, altExpected, MAX_STRING_SIZE ) == 0) )
		{
			status = 1;
		}
	}
	return status;
}

/* ===================================================================== */

/*+
 *   Function name:
 *   cicsCheckBusy
 *
 *   Purpose:
 *   Check whether the given string contains the CAR BUSY code.
 *
 *   Purpose:
 *   This is a utility function, used mainly by CAD function, which returns
 *   a "1" if the input argument contains the CAR code for "BUSY" and a "0"
 *   if the code contains anything else.
 *
 *   Invocation:
 *   status = cicsCheckBusy( char *string );
 *
 *   Parameters in:
 *      string        *string     string containing integer CAR value.
 *
 *   Parameters out:
 *
 *   Return value:
 *      < busyFlag    long        = 1 if the given code represents "BUSY".
 *                                = 0 if the given code contains anything else.
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Author:
 *   Steven Beard      (smb@roe.ac.uk)
 *   Ricardo Cardenes  (rcardenes@gemini.edu)
 *
 *   History:
 *   16-Apr-1997: Original version.                        (smb)
 *   11-Aug-1997: Modified to take string argument.        (smb)
 *   23-Feb-2018: Refactored to use ciscCheckCadCarCode    (rcardenes)
 *-
 */

long cicsCheckBusy( char *string ) 
{
/*
 * Check if the argument translates to "menuCarstatesBUSY".
 */
  return ciscCheckCadCarCode(string, menuCarstatesBUSY, "BUSY");
}


/* ===================================================================== */

/*+
 *   Function name:
 *   cicsCheckIdle
 *
 *   Purpose:
 *   Check whether the given string contains the CAR IDLE code.
 *
 *   Purpose:
 *   This is a utility function, used mainly by CAD functions, which
 *   returns a "1" if the input argument contains the CAR code for "IDLE"
 *   and a "0" if the code contains anything else.
 *
 *   Invocation:
 *   status = cicsCheckIdle( char *string );
 *
 *   Parameters in:
 *      string        *string     string containing integer CAR value.
 *
 *   Parameters out:
 *
 *   Return value:
 *      < idleFlag    long        = 1 if the given code represents "IDLE".
 *                                = 0 if the given code contains anything else.
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Author:
 *   Steven Beard      (smb@roe.ac.uk)
 *   Ricardo Cardenes  (rcardenes@gemini.edu)
 *
 *   History:
 *   11-Aug-1997: Original version.                        (smb)
 *   23-Feb-2018: Refactored to use ciscCheckCadCarCode    (rcardenes)
 *-
 */

long cicsCheckIdle( char *string )
{
/*
 * Check if the argument translates to "menuCarstatesIDLE".
 */
  return ciscCheckCadCarCode(string, menuCarstatesIDLE, "IDLE");
}


/* ===================================================================== */

/*+
 *   Function name:
 *   cicsCheckMarked
 *
 *   Purpose:
 *   Check whether the given string contains the CAD "marked" code.
 *
 *   Purpose:
 *   This is a utility function, used mainly by CAD functions, which returns
 *   a "1" if the input argument contains the CAD code for "marked" and a "0"
 *   if the code contains anything else.
 *
 *   Invocation:
 *   status = cicsCheckMarked( char *string );
 *
 *   Parameters in:
 *      string        *string     string containing integer CAR value.
 *
 *   Parameters out:
 *
 *   Return value:
 *      < markedFlag  long        = 1 if the given code represents "marked".
 *                                = 0 if the given code contains anything else.
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *   Ricardo Cardenes  (rcardenes@gemini.edu)
 *
 *   History:
 *   16-Apr-1997: Original version.                        (smb)
 *   11-Aug-1997: Modified to take string argument.        (smb)
 *   23-Feb-2018: Refactored to use ciscCheckCadCarCode    (rcardenes)
 *-
 */

long cicsCheckMarked( char *string )
{
/*
 * Check if the argument translates to the CAD status "MARKED" (which is integer 1)
 */
  return ciscCheckCadCarCode(string, 1, NULL);
}

/* ===================================================================== */


/*+
 *   Function name:
 *   cicsCheckPaused
 *
 *   Purpose:
 *   Check whether the given string contains the CAR PAUSED code.
 *
 *   Purpose:
 *   This is a utility function, used mainly by CAD functions, which
 *   returns a "1" if the input argument contains the CAR code for "PAUSED"
 *   and a "0" if the code contains anything else.
 *
 *   Invocation:
 *   status = cicsCheckPaused( char *string );
 *
 *   Parameters in:
 *      string        *string     string containing integer CAR value.
 *
 *   Parameters out:
 *
 *   Return value:
 *      < busyFlag    long        = 1 if the given code represents "PAUSED".
 *                                = 0 if the given code contains anything else.
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Author:
 *   Steven Beard      (smb@roe.ac.uk)
 *   Ricardo Cardenes  (rcardenes@gemini.edu)
 *
 *   History:
 *   11-Aug-1997: Original version.                        (smb)
 *   23-Feb-2018: Refactored to use ciscCheckCadCarCode    (rcardenes)
 *-
 */

long cicsCheckPaused( char *string ) 
{
/*
 * Check if the argument translates to "menuCarstatesPAUSED".
 */
  return ciscCheckCadCarCode(string, menuCarstatesPAUSED, "PAUSED");
}


/* ===================================================================== */

/*+
 *   Function name:
 *   cicsLogMessage
 *
 *   Purpose:
 *   Log an informational message.
 *
 *   Purpose:
 *   This routine is called whenever the CICS software needs to output
 *   an informational message. By directing all messages through this
 *   routine it should be possible to redirect the messages easily,
 *   for example through the "historyLog" record monitored by the Data
 *   Handling System. For the moment the messages are passed to the
 *   EPICS "errorPrintf" function.
 *
 *   Invocation:
 *   long debug;
 *   cicsLogMessage( debug, "Message" );
 *
 *   Parameters in:
 *      < message     char*       Message to be logged.
 *
 *   Parameters out:
 *
 *   Return value:
 *      This is a void function. It has no status value.
 *
 *   Globals:
 *      External functions:
 *      errlogPrintf      EPICS function for logging a message
 *
 *      External variables:
 *
 *   Requirements:
 *   It is assumed the current debug level has already been defined.
 *
 *   Limitations:
 *   This routine should not be used in very time-critical pieces of code
 *   where the time spent calling the routine and checking the debug level
 *   would be significant.
 *
 *   The "historyLog" record is not long enough to contain more than
 *   MAX_STRING_SIZE characters of the message, so history log messages
 *   might be truncated.
 *
 *   Author:
 *   Steven Beard      (smb@roe.ac.uk)
 *   Janet Tvedt       (tvedt@naoo.edu)
 *   Ricardo Cardenes  (rcardenes@gemini.edu)
 *
 *   History:
 *   03-Dec-1996: Original version.                                 (smb)
 *   15-Jan-1996: Added check on debugLevel.                        (smb)
 *   23-Jan-1997: static storage class removed from histMsg.
 *                Use MAX_STRING_SIZE to declare size of history
 *                log message.                                      (smb)
 *   27-Jan-1997: It was found that some messages delivered to
 *                logMsg() were getting lost, whereas others were.
 *                getting overwritten (see "LIMITATIONS" above. Ring
 *                buffer introduced into which pending messages can
 *                be queued.                                        (smb)
 *   17-Jun-1997: Modified to use a semaphore.                      (tvedt,smb)
 *   27-Jun-1997: Code to write history log added (but commented
 *                out, since it still needs testing).               (smb)
 *   30-Jan-1998: debuglevel and debug removed for instanciation    (ocf)
 *   23-Feb-2018: Refactored for RTEMS/EPICS 3.14
 *                It seems like EPICS OSI logger does not suffer
 *                from the same problem as vxWorks logMsg. It
 *                will save the logged messages to an internal
 *                list and print them in a separate thread, meaning
 *                that there's no need for a ring buffer. As a side
 *                effect, there's no need for the mutex any longer  (rcardenes)
 *-
 */

void cicsLogMessage ( const char * message )
{
 /* char fieldName[MAX_STRING_SIZE]; <--- COMMENTED OUT FOR NOW */
                                     /* Field name of history log record */

    char histMsg[MAX_STRING_SIZE];   /* Message to be written to history log */


/* Only display the message if the debug value associated with it is less
 * than or equal to the current debug level.
 */

/*    if ( debug <= debugLevel )
*    {
*/
/* At this point the message can be written to the "historyLog" record.
 * Using PvPut. This is still to be added.
 */

/* Copy that part of the message which can fit in the history log. */

      strncpy( histMsg, message, MAX_STRING_SIZE );

/* Copy the message to the history log using Channel Access. */

// TODO: Test this and uncomment
/* NOTE: THE FOLLOWING LINES ARE COMMENTED OUT, AS THEY HAVEN'T BEEN TESTED YET.
 */
#if 0
   sprintf( fieldName, "%shistoryLog.VAL", cicsSadtop );
   status = cicsCaPut( fieldName, errMess, DBF_STRING, histMsg );
#endif

      errlogPrintf( "%s\n", message);

 /*   } */

}



/* ===================================================================== */

/*+
 *   Function name:
 *   cicsGetTop
 *
 *   Purpose:
 *   Get the current top level record name prefixes.
 *
 *   Purpose:
 *   This routine is called to get the current top level record name prefixes.
 *
 *   Invocation:
 *   status = cicsGetTop( char *top, char *sadtop  );
 *   It may be invoked from the VxWorks startup script.
 *
 *   Parameters in:
 * 
 *   Parameters out:
 *      > top       *string      Top level record name prefix.
 *      > sadtop    *string      Top level SAD record name prefix.
 *
 *   Return value:
 *      ! status    long         status=PASS if the function worked
 *                               status=FAIL if the strings provided were
 *                               not of sufficient length.
 *
 *   Globals:
 *      External functions:
 *
 *      External variables:
 *
 *   Requirements:
 *
 *   Limitations:
 *   The supplied strings must be at least MAX_STRING_LENGTH in size.
 *   This function ought to check for this, but I am not sure how to
 *   do it (since for some reason sizeof( top ) always returns 4 and
 *   strlen( top ) returns 0).
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   21-Aug-1997: Original version.                  (smb)
 *-
 */

long cicsGetTop ( char* top, char* sadtop )
{
    long status;

    status = PASS;

/*
 * Copy the contents of the static variables cicsTop and cicsSadtop
 * into the supplied character strings.
 */

    strncpy( top, cicsTop, MAX_STRING_SIZE );
    strncpy( sadtop, cicsSadtop, MAX_STRING_SIZE );

    return status;
}


/* ===================================================================== */

/*+
 *   Function name:
 *   cicsSetTop
 *
 *   Purpose:
 *   Set the current top level record name prefixes.
 *
 *   Purpose:
 *   This routine is called to define the top level record name prefixes.
 *
 *   Invocation:
 *   cicsSetTop( const char *top, const char *sadtop  );
 *   It may be invoked from the VxWorks startup script.
 *
 *   Parameters in:
 *      < top       *string      Top level record name prefix.
 *      < sadtop    *string      Top level SAD record name prefix.
 * 
 *   Parameters out:
 *
 *   Return value:
 *      This is a void function. It has no status value.
 *
 *   Globals:
 *      External functions:
 *
 *      External variables:
 *
 *   Requirements:
 *
 *   Limitations:
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   17-Jun-1997: Original version.                  (smb)
 *-
 */

void cicsSetTop ( const char* top, const char* sadtop )
{

/*
 * Copy at most MAX_STRING_SIZE characters to the static variables
 * "cicsTop" and "cicsSadtop". These variables are used within cicsLib
 * and can be obtained by calling the cicsGetTop function.
 */

    strncpy( cicsTop, top, MAX_STRING_SIZE );
    strncpy( cicsSadtop, sadtop, MAX_STRING_SIZE );
}


/* ===================================================================== */
