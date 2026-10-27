/* cmdTimeoutRecord.c - Record Support Routines for Command Timeout
 *                      This record implements the protocol of sending
 *                      a command between two Gemini EPICS systems.
 *
 *      Author: Andy Foster
 *
 *	History
 *	-------
 *	Version 1.0  14/03/02  ajf  Created.
 *      Version 1.1  11/12/03  ajf  Changes to comply with the new macro for 
 *                                  "dbGetLink" in EPICS 3.13.9.
 *      Version 1.2  05/07/04  ajf  Converted to 3.14.
 *
 */

#define VERSION 1.2

#define DEBUG 0

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

#define GEN_SIZE_OFFSET
#include	<cmdTimeoutRecord.h>
#undef  GEN_SIZE_OFFSET

#include "epicsExport.h"


/* Create RSET - Record Support Entry Table*/

static long init_record();
static long process();
static long special();
static long get_precision();
#define get_value          NULL
#define get_enum_str       NULL
#define get_enum_strs      NULL
#define put_enum_str       NULL
#define report             NULL
#define initialize         NULL
#define cvt_dbaddr         NULL
#define get_units          NULL
#define get_array_info     NULL
#define put_array_info     NULL
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double   NULL

rset cmdTimeoutRSET={
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
epicsExportAddress(rset, cmdTimeoutRSET);

/* Control block for callback */

typedef struct myCallback
{
  CALLBACK        callback;
  struct dbCommon *precord;
}myCallback;

static void epicsShareAPI callbackRequestCancel(CALLBACK *pcallback);
static void cancelWatchDog( cmdTimeoutRecord *pcto );
static void startWatchDog( cmdTimeoutRecord *pcto );
static void monitor(cmdTimeoutRecord *);
static void endProcessing(cmdTimeoutRecord *);
static void getCARMessVal(cmdTimeoutRecord *);
static void setCARMessVal(cmdTimeoutRecord *, char *, long);
static void getCADMessVal(cmdTimeoutRecord *);
static void setCADVal(cmdTimeoutRecord *, long);
#if DEBUG
static char *printDir( int );
#endif

#define DEFAULT_TIMEOUT   3               /* 3 seconds */


static void cmdTimeoutCallback( CALLBACK *arg )
{
  myCallback       *pcallback;
  cmdTimeoutRecord *pcto;
  char             buf[MAX_STRING_SIZE];

  callbackGetUser(pcallback,arg);
  pcto = (cmdTimeoutRecord *)pcallback->precord;

  dbScanLock((struct dbCommon *)pcto);
  cancelWatchDog(pcto);
  if( !pcto->pact )
  {
    switch( pcto->stte )
    {
      case menuCTOStateMARK_RESP:
      case menuCTOStatePRESET_RESP:
      case menuCTOStateSTART_RESP:
      case menuCTOStateSTOP_RESP:
        strcpy(buf, "Subsystem CAD no response");
        break;

      case menuCTOStateCAR_RESP:
        strcpy(buf, "Subsystem CAR no response");
        break;

      default:
        strcpy(buf, "Subsystem timeout");
        break;
    }
    setCARMessVal(pcto, buf, menuCarstatesERROR);
    endProcessing(pcto);
  }
  dbScanUnlock((struct dbCommon *)pcto);
}


static void startWatchDog( cmdTimeoutRecord *pcto )
{
  myCallback *pcallback;

  /* Setup the timeout watchdog */
  pcallback = (myCallback *)(pcto->rpvt);

  callbackSetPriority( pcto->prio, &pcallback->callback );
  callbackRequestDelayed( &pcallback->callback, pcto->tout );
}


static void cancelWatchDog( cmdTimeoutRecord *pcto )
{
  myCallback *pcallback;

  /* Cancel the watchdog timer if there is one */
  pcallback = (myCallback *)(pcto->rpvt);

  callbackRequestCancel( &pcallback->callback );
}


static long init_record( cmdTimeoutRecord *pcto, int pass )
{
  myCallback *pcallback;
  long status = 0;

  if(pass == 0)
  {
    pcto->vers                            = VERSION;
    (&pcto->icdv)->value.pv_link.pvlMask |= pvlOptCP;
    (&pcto->icrv)->value.pv_link.pvlMask |= pvlOptCP;
  }
  else if(pass == 1)
  {
    if( (&pcto->odir)->type == DB_LINK )
      (&pcto->odir)->value.pv_link.pvlMask |= pvlOptPP;

    if( (&pcto->oval)->type == DB_LINK )
      (&pcto->oval)->value.pv_link.pvlMask |= pvlOptPP;

    if( (&pcto->omss)->type == DB_LINK )
      (&pcto->omss)->value.pv_link.pvlMask = 0x0;

    pcto->udf  = FALSE;
    pcto->stte = menuCTOStateMARK_CMD;
    pcto->lpro = 1;
    pcto->cnt  = 0;

    if( pcto->tout <= 0.0 )
      pcto->tout = DEFAULT_TIMEOUT;

    pcallback          = (myCallback *)(calloc(1,sizeof(myCallback)));
    pcallback->precord = (struct dbCommon *)pcto;
    pcto->rpvt         = (void *)pcallback;
    callbackSetCallback(cmdTimeoutCallback, &pcallback->callback);
    callbackSetUser(pcallback, &pcallback->callback);
  }
  return status;
}


static long process( cmdTimeoutRecord *pcto )
{
  long status = 0;
  char buf[MAX_STRING_SIZE];

  pcto->pact = TRUE;

  if( !pcto->pflg )
  {
#if DEBUG
    printf("%s: process not doing anything: %s\n", pcto->name, printDir(pcto->dir));
#endif
    pcto->pact = FALSE;
    return status;
  }

  switch( pcto->stte )
  {
    case menuCTOStateMARK_CMD:
      if( pcto->lpro )
      {
        pcto->pact = FALSE;
        return status;
      }
      pcto->cnt++;
      pcto->lpro = 1;
#if DEBUG
      printf("state MARK_CMD\n");
#endif

      setCARMessVal(pcto, " ", menuCarstatesBUSY);
      if( !dbIsLinkConnected(&pcto->odir) )
      {
        sprintf(buf, "(%s) not connected", pcto->name);
        setCARMessVal(pcto, buf, menuCarstatesERROR);
        endProcessing(pcto);
      }
      else
      {
        setCADVal(pcto, menuDirectiveMARK);
        pcto->stte = menuCTOStateMARK_RESP;
        startWatchDog(pcto);
      }
      break;


    case menuCTOStateMARK_RESP:
      if( !pcto->lpro )
      {
        pcto->pact = FALSE;
        return status;
      }
      pcto->cnt++;
#if DEBUG
      printf("state MARK RESP\n");
#endif
      cancelWatchDog(pcto);
      if( pcto->dir == menuDirectiveSTART )
      {
        setCADVal(pcto, menuDirectiveSTART);
        pcto->stte = menuCTOStatePRESET_RESP;
      }
      else
      {
        setCADVal(pcto, menuDirectiveSTOP);
        pcto->stte = menuCTOStateSTOP_RESP;
      }
      startWatchDog(pcto);
      break;


    case menuCTOStatePRESET_RESP:
      if( !pcto->lpro )
      {
        pcto->pact = FALSE;
        return status;
      }
      pcto->cnt++;
#if DEBUG
      printf("state PRESET RESP\n");
#endif
      cancelWatchDog(pcto);

      getCADMessVal(pcto);
      if( pcto->val < 0 )
      {
        setCARMessVal(pcto, pcto->mess, menuCarstatesERROR);
        endProcessing(pcto);
      }
      else
      {
        pcto->stte = menuCTOStateSTART_RESP;
        startWatchDog(pcto);
      }
      break;


    case menuCTOStateSTART_RESP:
      if( !pcto->lpro )
      {
        pcto->pact = FALSE;
        return status;
      }
      pcto->cnt++;
#if DEBUG
      printf("state START RESP\n");
#endif
      cancelWatchDog(pcto);

      getCADMessVal(pcto);
      if( pcto->val < 0 )
      {
        setCARMessVal(pcto, pcto->mess, menuCarstatesERROR);
        endProcessing(pcto);
      }
      else
      {
        pcto->stte = menuCTOStateCAR_RESP;
        startWatchDog(pcto);
      }
      break;


    case menuCTOStateSTOP_RESP:
      if( !pcto->lpro )
      {
        pcto->pact = FALSE;
        return status;
      }
      pcto->cnt++;
#if DEBUG
      printf("state STOP RESP\n");
#endif
      cancelWatchDog(pcto);

      getCADMessVal(pcto);
      if( pcto->val < 0 )
      {
        setCARMessVal(pcto, pcto->mess, menuCarstatesERROR);
        endProcessing(pcto);
      }
      else
      {
        pcto->stte = menuCTOStateCAR_RESP;
        startWatchDog(pcto);
      }
      break;


    case menuCTOStateCAR_RESP:
      if( !pcto->lpro )
      {
        pcto->pact = FALSE;
        return status;
      }
      pcto->cnt++;
#if DEBUG
      printf("state CAR RESP\n");
#endif
      cancelWatchDog(pcto);

      getCARMessVal(pcto);
      if( pcto->val == menuCarstatesBUSY )
        strcpy(pcto->mess, " ");
      setCARMessVal(pcto, pcto->mess, pcto->val);
      endProcessing(pcto);
      break;

    default:
      printf("Should never see this: Process (%s)\n", pcto->name);
      break;
  }
  pcto->pact = FALSE;
  return status;
}


static void endProcessing( cmdTimeoutRecord *pcto )
{
  pcto->pact = FALSE;
  pcto->stte = menuCTOStateMARK_CMD;
  recGblGetTimeStamp(pcto);
  monitor(pcto);
  recGblFwdLink(pcto);
#if DEBUG
  printf("Should see this at end of all processing (%ld)\n", pcto->cnt);
#endif
  pcto->cnt = 0;
}


static void monitor( cmdTimeoutRecord *pcto )
{
  unsigned short monitor_mask;

  monitor_mask  = recGblResetAlarms(pcto);
  monitor_mask |= DBE_VALUE | DBE_LOG;

  /* Raise monitors on VAL and MESS */
  if(monitor_mask)
  {
    db_post_events( pcto, pcto->mess, monitor_mask);
    db_post_events( pcto, &pcto->val, monitor_mask);
  }
  return;
}


static long special( struct dbAddr *paddr, int after )
{
  int              fieldIndex;
  cmdTimeoutRecord *pcto;

  pcto       = (cmdTimeoutRecord *)(paddr->precord);
  fieldIndex = dbGetFieldIndex(paddr);
  if(after)
  {
    switch( fieldIndex )
    {
      case cmdTimeoutRecordDIR:
        switch(pcto->dir)
        {
          case menuDirectiveMARK:
#if DEBUG
            printf("%s: special: MARK (0)\n", pcto->name);
#endif
            pcto->pflg = 0;
            break;

          case menuDirectiveCLEAR:
#if DEBUG
            printf("%s: special: CLEAR (0)\n", pcto->name);
#endif
            pcto->pflg = 0;
            break;

          case menuDirectivePRESET:
#if DEBUG
            printf("%s: special: PRESET (0)\n", pcto->name);
#endif
            pcto->pflg = 0;
            break;

          case menuDirectiveSTART:
#if DEBUG
            printf("%s: special: START (1)\n", pcto->name);
#endif
            pcto->pflg = 1;
            break;

          case menuDirectiveSTOP:
#if DEBUG
            printf("%s: special: STOP (1)\n", pcto->name);
#endif
            pcto->pflg = 1;
            break;

          default:
            break;
        }
        pcto->lpro = 0;
        break;

      default:
        printf("%s: special: Should never see this\n", pcto->name);
        break;
    }
  }
  return 0;
}


static long get_precision( struct dbAddr *paddr, long *pprecision )
{
  *pprecision = 1;
  return 0;
}


void getCARMessVal( cmdTimeoutRecord *pcto )
{
  long status;
  long nRequest;
  long opt;

  nRequest = 1;
  opt      = 0;
  status   = dbGetLink( &pcto->icrm, DBR_STRING, pcto->mess, &opt, &nRequest );

  nRequest = 1;
  opt      = 0;
  status   = dbGetLink( &pcto->icrv, DBR_LONG,   &pcto->val, &opt, &nRequest );
}


void setCARMessVal( cmdTimeoutRecord *pcto, char *errMsg, long val )
{
  long status;
  long nRequest = 1;

  strncpy(pcto->mess, errMsg, MAX_STRING_SIZE);
  pcto->val = val;
  status    = dbPutLink( &pcto->omss, DBR_STRING,  pcto->mess, nRequest );
  status    = dbPutLink( &pcto->oval, DBR_LONG,   &pcto->val,  nRequest );
}


void getCADMessVal( cmdTimeoutRecord *pcto )
{
  long status;
  long nRequest;
  long opt;

  nRequest = 1;
  opt      = 0;
  status   = dbGetLink( &pcto->icdm, DBR_STRING, pcto->mess, &opt, &nRequest );

  nRequest = 1;
  opt      = 0;
  status   = dbGetLink( &pcto->icdv, DBR_LONG,   &pcto->val, &opt, &nRequest );
}

void setCADVal( cmdTimeoutRecord *pcto, long val )
{
  long status;
  long nRequest = 1;

#if DEBUG
  printf("%s: Sending DIR = %s\n", pcto->name, printDir(val) );
#endif

  pcto->val = val;
  status    = dbPutLink( &pcto->odir, DBR_LONG, &pcto->val, nRequest );
}


static void epicsShareAPI callbackRequestCancel(CALLBACK *pcallback)
{
  epicsTimerId timer = (epicsTimerId)pcallback->timer;

  epicsTimerCancel(timer);
}


#if DEBUG
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
