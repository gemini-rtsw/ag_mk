/* applyRecord.c - Record Support Routines for Apply
 *
 *      Author: Bret Goodrich
 *
 *	History
 *	-------
 *	Version 1.0  14/02/95  bdg  Created.
 *	Version 1.1  21/04/96  bdg  Changed client ID to integer.
 *	Version 1.2  10/07/96  bdg  Added fwd link. Reorganized process().
 *	Version 1.3  13/07/96  bdg  Process now ignores MARK directive.
 *	Version 1.4  04/11/96  bdg  Save old directive so PRESET not done twice.
 *	Version 1.5  08/11/96  bdg  VAL monitor posted last.
 *      Version 1.6  26/11/96  bdg  Changed last field of recGblInitFastOutLink() call.
 *	Version 1.7  21/03/97  bdg  Check links exist before changing NPP to PP.
 *                                  Process didn't handle callbacks right.
 *	Version 1.8  30/04/97  bdg  Another callback fix in process.
 *	Version 1.9  02/05/97  bdg  Client ID returned as VAL.
 *	Version 2.0  04/06/97  bdg  Return only one monitor on VAL.
 *	Version 2.1  18/07/97  bdg  CLID not incremented on subroutine error.
 *	Version 2.2  15/09/97  bdg  Fixed PRESET error handling.
 *	Version 2.3  16/09/97  bdg  Fixed PRESET monitor.
 *	Version 2.4  03/11/97  ajf  Increment CLID before processing output links.
 *      Version 2.5  16/03/01  ajf  Changes for 3.13.
 *                                  Set precision to 1 for VERS field.
 *      Version 2.6  12/07/01  ajf  Rewrite the process routine.
 *                                  Only clear the MESS field on a PRESET.
 *      Version 3.0  17/07/01  ajf  Split the record processing into two halves to handle the 
 *                                  output and input links seperately. This solves the problem of
 *                                  using the record across channel access.
 *      Version 3.1  02/08/01  ajf  Partially solve problem of timeouts. A proper solution
 *                                  would involve using the client_id's between "applys" and
 *                                  "cads". This would have a large impact on pre-existing
 *                                  capfast schematics.
 *      Version 3.2  05/03/02  ajf  Fixed a bug which was causing the record to fail when
 *                                  positioned in a hierarchy of Apply's. This was caused
 *                                  by records lower down in the hierarchy issuing multiple
 *                                  PRESETS instead of a START directive. It is taken care
 *                                  of by examining the MARK field.
 *      Version 3.3  04/07/02  cjm  Fixed protocol problem with ocswish where increasing
 *                                  the client-id twice was leading to error messages
 *                                  from ocswish. This manifested itself for commands
 *                                  which take some time to complete, like slewing
 *                                  the telescope.
 *      Version 3.4  11/12/03  ajf  Changes to comply with the new macro for 
 *                                  "dbGetLink" in EPICS 3.13.9.
 *      Version 3.5  14/04/04  ajf  Conversion to EPICS 3.14.5.
 *
 */

#define DEBUG   0
#define DEBUG1  0
#define DEBUG2  0
#define VERSION 3.5

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#include	<alarm.h>
#include	<callback.h>
#include	<dbDefs.h>
#include	<dbEvent.h>
#include	<dbAccess.h>
#include	<dbFldTypes.h>
#include	<errMdef.h>
#include	<recGbl.h>
#include	<recSup.h>
#include	<devSup.h>
#include 	<special.h>
#include 	<epicsTimer.h>
#include	<epicsExport.h>

#define GEN_SIZE_OFFSET
#include	<applyRecord.h>
#undef  GEN_SIZE_OFFSET

/* Create RSET - Record Support Entry Table*/

static long init_record();
static long process();
static long get_value();
static long get_enum_str();
static long get_enum_strs();
static long put_enum_str();
static long get_precision();
static long special();
#define report             NULL
#define initialize         NULL
#define cvt_dbaddr         NULL
#define get_units          NULL
#define get_array_info     NULL
#define put_array_info     NULL
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double   NULL

rset applyRSET={
	RSETNUMBER,
	report,
	initialize,
	init_record,
	process,
	special,
	get_value,
	cvt_dbaddr,
	get_array_info,
	put_array_info,
	get_units,
	get_precision,
	get_enum_str,
	get_enum_strs,
	put_enum_str,
	get_graphic_double,
	get_control_double,
	get_alarm_double };
epicsExportAddress(rset, applyRSET);

/* Control block for callback */

typedef struct myCallback
{
  CALLBACK        callback;
  struct dbCommon *precord;
}myCallback;

static void               monitor(applyRecord *);
static long               processLinks(applyRecord *);
static void               endInLinkProc(applyRecord *);
static void epicsShareAPI callbackRequestCancel(CALLBACK *);
#if DEBUG1
static char *printDir( int );
#endif

#define ARG_MAX           8
#define DEFAULT_TIMEOUT   3               /* 3 seconds */


static void applyCallback( CALLBACK *arg )
{
  myCallback  *pcallback;
  applyRecord *papply;

  callbackGetUser(pcallback,arg);
  papply = (applyRecord *)pcallback->precord;

#if DEBUG1
  printf("%s: applyCallback called DIR = %s\n", papply->name, printDir(papply->dir));
#endif

  dbScanLock((struct dbCommon *)papply);

  /* Cancel the watchdog timer */
  callbackRequestCancel( &pcallback->callback );

  if( !papply->pact )
  {
    papply->val  = -1;
    papply->stfg =  0;
    strcpy(papply->mess, "Subsystem timed out");
    endInLinkProc(papply);
  }
  dbScanUnlock((struct dbCommon *)papply);
}


/*******************************************************************************
* init_record
*/

static long init_record( applyRecord *papply, int pass )
{
  myCallback *pcallback;
  long status = 0;
  int i;

  if(pass == 0)
  {
    papply->vers = VERSION;

    for( i=0; i<ARG_MAX; i++ )
      (&papply->inpa+i)->value.pv_link.pvlMask |= pvlOptCP;
  }
  else if(pass == 1)
  {
    for( i=0; i<ARG_MAX; i++ )
    {
      if( (&papply->outa+i)->type == DB_LINK )
        (&papply->outa+i)->value.pv_link.pvlMask |= pvlOptPP;

      if( (&papply->ocla+i)->type == DB_LINK )
        (&papply->ocla+i)->value.pv_link.pvlMask = 0x0;

      if( (&papply->inma+i)->type == DB_LINK )
        (&papply->inma+i)->value.pv_link.pvlMask = 0x0;
    }

    papply->udf  = FALSE;
    papply->stte = menuApplyStateOUT;
    papply->lpro = 1;
    papply->top  = 1;
    papply->stfg = 0;

    if( papply->tout <= 0.0 )
      papply->tout = DEFAULT_TIMEOUT;

    pcallback          = (myCallback *)(calloc(1,sizeof(myCallback)));
    pcallback->precord = (struct dbCommon *)papply;
    papply->rpvt       = (void *)pcallback;
    callbackSetCallback(applyCallback,&pcallback->callback);
    callbackSetUser(pcallback,&pcallback->callback);
  }
  return status;
}


static long process( applyRecord *papply )
{
  myCallback *pcallback;
  long status = 0;
  int  i;

  papply->pact = TRUE;

#if DEBUG1
  printf("\n");
#endif
  switch( papply->stte )
  {
    case menuApplyStateOUT:
      if( papply->lpro )
      {
#if DEBUG1
        printf("%s: OUT with link processing - Do nothing\n", papply->name);
#endif
        papply->pact = FALSE;
        return status;
      }
      papply->lpro = 1;

#if DEBUG
      printf("%s: Process routine - Processing the output links DIR = %s\n", papply->name, printDir(papply->dir));
#endif

      for(i=0; i<ARG_MAX; i++)
      {
        if( dbIsLinkConnected(&papply->inpa + i) )
          papply->nprc++;
      }
      if( !papply->nprc )
      {
        recGblRecordError( S_dev_badInpType, (void *)papply, "applyRecord: No connected inputs");
        papply->pact = FALSE;
        return S_dev_badInpType;
      }
#if DEBUG1
      else
        printf("%s: There are %ld CA connections\n", papply->name, papply->nprc);
#endif

      if( papply->dir != menuDirectiveMARK )
      {
        /* Setup the timeout watchdog */
        pcallback = (myCallback *)(papply->rpvt);
        callbackSetPriority( papply->prio, &pcallback->callback );
#if DEBUG1
        printf("%s: Starting the watchdog timer\n", papply->name);
#endif
        callbackRequestDelayed( &pcallback->callback, papply->tout );
      }

      switch( papply->dir )
      {
        case menuDirectiveCLEAR:
#if DEBUG
          printf("apply record: %s: CLEAR\n", papply->name);
#endif
          processLinks(papply);
          break;

        case menuDirectiveMARK:
#if DEBUG
          printf("apply record: %s: MARK\n", papply->name);
#endif
          endInLinkProc(papply);
          papply->pact = FALSE;
          return status;
          break;

        case menuDirectivePRESET:
#if DEBUG
          printf("apply record: %s: PRESET\n", papply->name);
#endif
#if DEBUG2
          if( !strcmp(papply->name, "tcs:apply")      ||
              !strcmp(papply->name, "tcs:com:apply")  ||
              !strcmp(papply->name, "tcs:com:apply3") ||
              !strcmp(papply->name, "tcs:com:apply32") )
            printf("%s: OUT - PRESET case\n", papply->name);
#endif

          /* Only clear error message on PRESET */
          *papply->mess = '\0';
          if( papply->top )
            papply->clid++;

#if DEBUG1
          printf("%s: process: DIR = %s: CLID = %ld\n", papply->name, printDir(papply->dir), papply->clid);
#endif
          processLinks(papply);
          break;

        case menuDirectiveSTART:
#if DEBUG
          printf("apply record: %s: START\n", papply->name);
#endif
          if( (papply->val < 0) || ((papply->mark != menuDirectivePRESET) && !papply->stfg) )
          {
#if DEBUG2
            if( !strcmp(papply->name, "tcs:apply")      ||
                !strcmp(papply->name, "tcs:com:apply")  ||
                !strcmp(papply->name, "tcs:com:apply3") ||
                !strcmp(papply->name, "tcs:com:apply32") )
              printf("%s: OUT - START but doing PRESET first\n", papply->name);
#endif
            papply->stfg = 1;
            papply->dir  = menuDirectivePRESET;

            /* Only clear error message on PRESET */
            *papply->mess = '\0';
            if( papply->top )
              papply->clid++;
          }
          else
          {
#if DEBUG2
            if( !strcmp(papply->name, "tcs:apply")      ||
                !strcmp(papply->name, "tcs:com:apply")  ||
                !strcmp(papply->name, "tcs:com:apply3") ||
                !strcmp(papply->name, "tcs:com:apply32") )
              printf("%s: OUT - START and doing START\n", papply->name);
#endif
            papply->stfg = 0;
          }

#if DEBUG1
          printf("%s: process: START: DIR = %s: CLID = %ld, stfg = %ld\n", papply->name, printDir(papply->dir), papply->clid, papply->stfg);
#endif

          processLinks(papply);
          break;

        case menuDirectiveSTOP:
#if DEBUG
          printf("apply record: %s: STOP\n", papply->name);
#endif
          processLinks(papply);
          break;

        default:
          printf("Unknown directive: %d\n", papply->dir);
          break;
      }

      papply->stte = menuApplyStateIN;
      break;


    case menuApplyStateIN:
      if( !papply->lpro )
      {
#if DEBUG1
        printf("%s: IN with DIR processing - Do nothing\n", papply->name);
#endif
        papply->pact = FALSE;
        return status;
      }

      papply->nprc--;
      if( !papply->nprc )
      {
        /* Cancel the watchdog timer if there is one */
        pcallback = (myCallback *)(papply->rpvt);
#if DEBUG1
        printf("%s: Cancelling the watchdog timer\n", papply->name);
#endif
        callbackRequestCancel( &pcallback->callback );

        /* CLEAR is a special case - leave the client ID as it is */
        if( papply->dir != menuDirectiveCLEAR )
        {

#if DEBUG
          printf("\n%s: Process routine - Processing the input links DIR = %s\n", papply->name, printDir(papply->dir));
#endif
          processLinks(papply);

          /*
             If VAL is positive or 0, return the client id else return CAD_REJECT to indicate
             an error. For the case of an error, do not send START following a PRESET.
          */

          if( papply->val >= 0 )
            papply->val  = papply->clid;
          else
            papply->stfg = 0;
        }

        endInLinkProc(papply);

        /* Handle the case where we are doing a PRESET followed by a START */
        /* We have just done the PRESET, so now do the START               */
        if( papply->stfg )
        {
          papply->lpro = 0;
          papply->dir  = menuDirectiveSTART;
#if DEBUG2
          if( !strcmp(papply->name, "tcs:apply")      ||
              !strcmp(papply->name, "tcs:com:apply")  ||
              !strcmp(papply->name, "tcs:com:apply3") ||
              !strcmp(papply->name, "tcs:com:apply32") )
            printf("%s: IN - Just done PRESET now call START\n", papply->name);
#endif
          process( papply );
        }
      }
      break;

    default:
      printf("%s: Apply record \"process\" internal state error\n", papply->name);
      break;
  }
  papply->mark = papply->dir;
  papply->pact = FALSE;
  return status;
}


static long processLinks( applyRecord *papply )
{
  long status;
  long nRequest;
  long opt;
  int i;

  status   = 0;

  switch( papply->stte )
  {
    case menuApplyStateOUT:

      /* send CLID and DIR to all output links */
      for(i=0; i<ARG_MAX; i++)
      {
        nRequest = 1;
        status   = dbPutLink( &papply->ocla+i, DBR_LONG, &papply->clid, nRequest );
        status   = dbPutLink( &papply->outa+i, DBR_ENUM, &papply->dir,  nRequest );
      }
      break;

    case menuApplyStateIN:

      /* Get the values from the input links */
      for(i=0; i<ARG_MAX; i++)
      {
        nRequest = 1;
        opt      = 0;
        status   = dbGetLink( &papply->inpa+i, DBR_LONG, &papply->val, &opt, &nRequest );
        if( status )
        {
          recGblRecordError( S_dev_badInpType, (void *)papply, "applyRecord: INP LINK" );
          return S_dev_badInpType;
        }

        if( papply->val < 0 )
        {
          nRequest = 1;
          opt      = 0;
          status   = dbGetLink( &papply->inma+i, DBR_STRING, papply->mess, &opt, &nRequest );
          if( status )
          {
            recGblRecordError( S_dev_badInpType, (void *)papply, "applyRecord: MESSAGE LINK" );
            return S_dev_badInpType;
          }
          break;
        }
      }
      break;

    default:
      printf("%s: Apply record \"processLinks\" internal state error\n", papply->name);
      break;
  }
  return( status );
}


static void endInLinkProc( applyRecord *papply )
{
  papply->nprc = 0;
  papply->stte = menuApplyStateOUT;

  recGblGetTimeStamp(papply);
  monitor(papply);
  recGblFwdLink(papply);
}


/*******************************************************************************
* get_value
*/

static long get_value( applyRecord *papply, struct valueDes *pvdes )
{
    pvdes->field_type  = DBF_LONG;
    pvdes->no_elements = 1;
    pvdes->pvalue      = (void *)&papply->val;

    return 0;
}


/*******************************************************************************
* get_enum_str
*/

static long get_enum_str (
    struct dbAddr *paddr,
    char *pstring)
{
    applyRecord *papply = (applyRecord *) paddr->precord;

    switch (papply->dir)
    {
	case menuDirectiveMARK:
	    strcpy (pstring, "MARK");
	    break;

	case menuDirectiveCLEAR:
	    strcpy (pstring, "CLEAR");
	    break;

	case menuDirectivePRESET:
	    strcpy (pstring, "PRESET");
	    break;

	case menuDirectiveSTART:
	    strcpy (pstring, "START");
	    break;

	case menuDirectiveSTOP:
	    strcpy (pstring, "STOP");
	    break;

	default:
	    strcpy (pstring, "Illegal_Value");
	    return -1;
	    break;
    }

    return 0;
}


/*******************************************************************************
* get_enum_strs
*/

static long get_enum_strs (
    struct dbAddr *paddr,
    struct dbr_enumStrs *pes)
{
    pes->no_str = 5;
    memset (pes->strs, '\0', sizeof (pes->strs));
    strcpy (pes->strs[0], "MARK");
    strcpy (pes->strs[1], "CLEAR");
    strcpy (pes->strs[2], "PRESET");
    strcpy (pes->strs[3], "START");
    strcpy (pes->strs[4], "STOP");

    return 0;
}


/*******************************************************************************
* put_enum_str
*/

static long put_enum_str (
    struct dbAddr *paddr,
    char *pstring)
{
    applyRecord *papply = (applyRecord *) paddr->precord;

    if (!strcmp (pstring, "MARK"))
	papply->dir = menuDirectiveMARK;
    else if (!strcmp (pstring, "CLEAR"))
	papply->dir = menuDirectiveCLEAR;
    else if (!strcmp (pstring, "PRESET"))
	papply->dir = menuDirectivePRESET;
    else if (!strcmp (pstring, "START"))
	papply->dir = menuDirectiveSTART;
    else if (!strcmp (pstring, "STOP"))
	papply->dir = menuDirectiveSTOP;
    else
	return (S_db_badChoice);

    return 0;
}


/*******************************************************************************
* monitor
*/

static void monitor( applyRecord *papply )
{
    unsigned short monitor_mask;

    monitor_mask = recGblResetAlarms (papply);
    monitor_mask |= DBE_VALUE | DBE_LOG;

    /*
     * Raise monitors on VAL and MESS.  The latter only fires if
     * there is an error in VAL or the MESS changes.
     */
    if (monitor_mask)
    {
	db_post_events (papply, &papply->clid, monitor_mask);
	if (papply->val < 0 || strncmp (papply->omss, papply->mess, MAX_STRING_SIZE) != 0)
	{
	    db_post_events (papply, &papply->mess, monitor_mask);
	    strncpy (papply->omss, papply->mess, MAX_STRING_SIZE);
	}
	db_post_events (papply, &papply->val, monitor_mask);
    }

    return;
}


static long get_precision( struct dbAddr *paddr, long *pprecision )
{
  *pprecision = 1;
  return 0;
}


static long special( struct dbAddr *paddr, int after )
{
  int         fieldIndex;
  applyRecord *papply;

  papply     = (applyRecord *)(paddr->precord);
  fieldIndex = dbGetFieldIndex(paddr);
  if(after)
  {
    switch( fieldIndex )
    {
      case applyRecordDIR:
        papply->lpro = 0;
        break;

      case applyRecordCLID:
        papply->top = 0;
        break;

      default:
        printf("%s: special: Should never see this\n", papply->name);
        break;
    }
  }
  return 0;
}


static void epicsShareAPI callbackRequestCancel(CALLBACK *pcallback)
{
  epicsTimerId timer = (epicsTimerId)pcallback->timer;

  epicsTimerCancel(timer);
}


#if DEBUG1
static char *printDir( int dir )
{
  static char *ret = NULL;

  if( !ret )
    ret = (char *)malloc(8);

  switch( dir )
  {
    case 0:
      strcpy(ret, "MARK");
      break;

    case 1:
      strcpy(ret, "CLEAR");
      break;

    case 2:
      strcpy(ret, "PRESET");
      break;

    case 3:
      strcpy(ret, "START");
      break;

    case 4:
      strcpy(ret, "STOP");
      break;

    default:
      printf("Should never see this\n");
      break;
  }
  return( ret );
}
#endif
