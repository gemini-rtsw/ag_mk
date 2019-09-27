/* static char rcsid[]="$Id: cicsDBLib.c,v 1.2 2001/08/14 14:00:18 ajf Exp $"; */
/*
 *  FILENAME
 *  -------- 
 *  cicsDBLib.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all the library functions used by the
 *  Core Instrument Control System
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  cicsDbGet         - Get a value from an EPICS field using database access
 *  cicsDbPut         - Put a value to an EPICS field using database access
 *
 *  DEPENDENCIES
 *  ------------
 *
 *  LIMITATIONS
 *  ------------
 *  none known
 *
 *  AUTHOR
 *  ------
 *  Steven Beard  (smb@roe.ac.uk)
 *  Janet Tvedt   (tvedt@noao.edu)
 *
 *  HISTORY
 *  -------
 *  30.1.98	routines moved to this file from cicsLib.c	(ocf)
 *
 */
/* *INDENT-OFF* */
/*
 * $Log: cicsDBLib.c,v $
 * Revision 1.2  2001/08/14 14:00:18  ajf
 * ajf: Changes for the port to 3.13.
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

#include  <math.h>
#include  <time.h>
#include  <epicsStdioRedirect.h>
#include  <registryFunction.h>
#include  <epicsExport.h>
#include  <epicsStdlib.h>
#include  <epicsEvent.h>
#include  <epicsPrint.h>
#include  <string.h>

#include  <dbDefs.h>
#include  <dbCommon.h>
#include  <recSup.h>
#include  <dbAccess.h>
#include  <menuCarstates.h>

#include  <cicsConst.h>
#include  <cicsLib.h>

/* ===================================================================== */
/*
 *+
 *  FUNCTION NAME:
 *  cicsDbGet
 *
 *  INVOCATION:
 *  long status;
 *  char *fieldName;  
 *  char *errMess;
 *  unsigned short type;
 *  double *outVal;
 *
 *  status = cicsDbGet(fieldName, errMess, type, &outVal);
 *
 *  PARAMETERS: (">" input, "!" modified, "<" output)
 *  > fieldName (char *)               pointer to reocord_name.field_name
 *  ! errMess   (char *)               pointer to string
 *  > type      (unsigned short)       data type to convert output to 
 *                                     (DBF_DOUBLE, DBF_LONG, etc.)
 *  < outval    (void *)               pointer to output value
 *
 *  FUNCTION VALUE:
 *  long  - status value returned to calling routine, a non-zero value
 *          indicates an error
 *
 *  PURPOSE:
 *  Function to get a value from an EPICS field by database access.
 *
 *  DESCRIPTION:
 *  This routine is called to obtain the value of the specified field 
 *  within an EPICS database record.  It handles potential errors by
 *  sending messages to the CICS logging functions and returning an
 *  error emssage and status value to the calling routine.
 *
 *  EXTERNAL VARIABLES:
 *  dbNameToAddr    - EPICS database access routine for finding record address
 *  dbGetField      - EPICS database access routine for retrieving the data
 *  cicsLogMessage  - CICS logging function for a message
 *  cicsLogString   - CICS logging function for a message + a string
 *
 *  PRIOR REQUIREMENTS:
 *  None.
 *  
 *  DEFICIENCIES:
 *  I am informed that the routine "recGblGetLinkValue" is preferred
 *  to "dbGetField" by the EPICS community (because it can choose whether
 *  to use Channel Access or Database Access according to circumstances),
 *  but "recGblGetLinkValue" is much more complicated, and I don't understand
 *  its description in the "EPICS IOC Application Developers Guide".
 *
 *  HISTORY (optional):
 *  13-Mar-1997  Original version as getDbInfo.			Janet Tvedt
 *  17-Jun-1997  Imported into cicsLib.				Steven Beard
 *-
 */

long cicsDbGet(char *fieldName, char *errMess, unsigned short type, void *outVal)
{
    struct dbAddr addr;
    long ret, options=0L, nRq = 1L;
    long status;
    
    status = PASS;

    /* Get the address of the data structure  and handle any errors */
    if( (ret = dbNameToAddr (fieldName,&addr)) != 0L)
    {
	status = FAIL;
	sprintf(errMess, "dbNameToAddr error = %ld, dbName=\"%s\"", ret, fieldName);
	cicsLogMessage( errMess);
    }

    /* If address found, get the data.  Handle any errors. */
    if( status == PASS )
    {
       if( (ret = dbGetField(&addr, type, outVal, &options, &nRq, NULL)) != 0L)
       {
	   status = FAIL;
	   sprintf(errMess, "dbGet error = %ld", ret);
	   cicsLogMessage( errMess);
        }
    }

    /* Return error status */
    return status;
}


/* ===================================================================== */

/*
 *+
 *  FUNCTION NAME:
 *  cicsDbPut
 *
 *  INVOCATION:
 *  char *fieldName;
 *  char *errMess;
 *  unsigned short type;
 *  double outVal;
 *  long status;
 *
 *  status = cicsDbPut(fieldName, errMess, DBF_DOUBLE, &outVal)
 *
 *  PARAMETERS: (">" input, "!" modified, "<" output)
 *  > fieldName (char *)           pointer to record+field name
 *  ! errMess   (char *)           pointer to string
 *  > type      (unsigned short)   data type of value to put
 *  > outVal    (void *)           pointer of data to put
 *
 *  FUNCTION VALUE:
 *  long  Status value returned to calling routine, a non-zero value indicates
 *        an error
 *
 *  PURPOSE:
 *  Function to put a value into an EPICS field by database access
 *
 *  DESCRIPTION:
 *  This routine may be called by a user subroutine to put a value
 *  into an EPICS databaser record field.  The complete field name must
 *  be specified (for example: sytem:subsystem:recordx.FIELDY).  This function
 *  will also handle errors by logging them through the CICS logging functions
 *  and by returning an error message and status value to the calling routine.
 *
 *  EXTERNAL VARIABLES:
 *  dbNameToAddr    - EPICS database access routine for finding record address
 *  dbPutField      - EPICS database access routine for putting the data
 *  cicsLogMessage  - CICS logging function for a message
 *  cicsLogString   - CICS logging function for a message + a string
 *
 *  PRIOR REQUIREMENTS:
 *  None
 *
 *  DEFICIENCIES:
 *  I am informed that the routine "recGblGetLinkValue" is preferred
 *  to "dbGetField" by the EPICS community (because it can choose whether
 *  to use Channel Access or Database Access according to circumstances),
 *  but "recGblGetLinkValue" is much more complicated, and I don't understand
 *  its description in the "EPICS IOC Application Developers Guide".
 *
 *  HISTORY (optional):
 *  19-Mar-1997  Original version as putDbInfo.			Janet Tvedt
 *  17-Jun-1997  Imported into cicsLib				Steven Beard
 *-
 */


long cicsDbPut(char *fieldName, char *errMess, unsigned short type, void *outVal)
{
    struct dbAddr addr;
    long ret, nRq = 1L;
    long status;
    
    
    status = PASS;

    /* Get the address of the data structure  and handle any errors */
    if( (ret = dbNameToAddr (fieldName,&addr)) != 0L)
    {
	status = FAIL;
	sprintf(errMess, "dbNameToAddr error = %ld, dbName=\"%s\"", ret, fieldName);
	cicsLogMessage( errMess);
    }

    /* If address found, write the data.  Handle any errors. */
    if( status == PASS )
    {
       if( (ret = dbPutField(&addr, type, outVal, nRq)) != 0L)
       {
	   status = FAIL;
	   sprintf(errMess, "dbPutField error = %ld", ret);
	   cicsLogMessage( errMess);
       }
    }

    /* Return error status */
    return status;
}

/* ===================================================================== */
