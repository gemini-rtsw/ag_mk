/* carRecord.c - Record Support Routines for CAR (Command Action Response) record */
/*
 *      Author:	Andy Foster  
 *
 *      History
 *      -------
 *      Version 1.0  15/11/95  ajf  Created.
 *      Version 1.1  21/06/96  bdg  Added CLID monitor.
 *      Version 1.2  04/11/96  bdg  Post VAL monitor last.
 *      Version 1.3  19/12/96  bdg  Removed states UNKNOWN and UNAVAILABLE.
 *      Version 1.4  17/07/97  bdg  Ignore omss on non-ERROR state.
 *      Version 1.5  19/03/98  bdg  Monitor() used strcpy rather than strncmp.
 *      Version 1.6  14/03/01  ajf  Changes for 3.13.
 *                                  Set precision to 1 (for VERS field really
 *                                  but don't check on field in case
 *                                  uninitialised pointer is passed back)!
 *      Version 1.7  27/04/01  ajf  Add DEBUG macro with debug statements in process.
 *      Version 1.8  11/12/03  ajf  Changes to comply with the new macro for 
 *                                  "dbGetLink" in EPICS 3.13.9.
 *      Version 1.9  15/04/04  ajf  Conversion to EPICS 3.14.5.
 *
 */

#define DEBUG   0
#define VERSION 1.9

/* Special Error Code returned by the CAR for invalid input */
/* Users should define further error codes which start at 2 */

#define CAR_INVALID_INPUT 1

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#include	<alarm.h>
#include	<dbDefs.h>
#include	<dbEvent.h>
#include	<dbAccess.h>
#include	<dbFldTypes.h>
#include	<errMdef.h>
#include	<recGbl.h>
#include	<recSup.h>
#include	<devSup.h>
#include 	<special.h>
#include 	<epicsExport.h>

#define GEN_SIZE_OFFSET
#include	<carRecord.h>
#undef  GEN_SIZE_OFFSET

/* Create RSET - Record Support Entry Table*/

static long init_record();
static long process();
static long get_value();
static long get_enum_str();
static long get_enum_strs();
static long put_enum_str();
static long get_precision();
#define report             NULL
#define initialize         NULL
#define special            NULL
#define cvt_dbaddr         NULL
#define get_array_info     NULL
#define put_array_info     NULL
#define get_units          NULL
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double   NULL

rset carRSET={
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
epicsExportAddress(rset, carRSET);

static void monitor();
static void car_state_machine();


static void car_state_machine( carRecord *pcar, int in )
{
  switch(pcar->val)
  {
    case menuCarstatesIDLE:
      switch(in)
      {
        case menuCarstatesBUSY:
          pcar->val = menuCarstatesBUSY;
          break;
        default:
          break;
      }
      break;

    case menuCarstatesPAUSED:
      switch(in)
      {
        case menuCarstatesIDLE:
          pcar->val = menuCarstatesIDLE;
          break; 
        case menuCarstatesERROR:
          pcar->val = menuCarstatesERROR;
          break;
        case menuCarstatesBUSY:
          pcar->val = menuCarstatesBUSY;
          break;
        default:
          break;
      }
      break;

    case menuCarstatesERROR:
      switch(in)
      {
        case menuCarstatesIDLE:
          pcar->val = menuCarstatesIDLE;
          break; 
        case menuCarstatesBUSY:
          pcar->val = menuCarstatesBUSY;
          break;
        default:
          break;
      }
      break;

    case menuCarstatesBUSY:
      switch(in)
      {
        case menuCarstatesIDLE:
          pcar->val = menuCarstatesIDLE;
          break; 
        case menuCarstatesBUSY:
          pcar->val = menuCarstatesBUSY;
          break;
        case menuCarstatesPAUSED:
          pcar->val = menuCarstatesPAUSED;
          break;
        case menuCarstatesERROR:
          pcar->val = menuCarstatesERROR;
          break;
        default:
          break;
      }
      break;
  }
}


static long init_record( carRecord *pcar, int pass )
{
  long status;

  status = 0;
  if( pass == 1 )
  {
    pcar->udf  = TRUE;
    pcar->vers = VERSION;

    if( pcar->siml.type == CONSTANT )
      recGblInitConstantLink(&pcar->siml, DBF_ENUM, &pcar->simm);
  
    if( pcar->siol.type == CONSTANT )
      recGblInitConstantLink(&pcar->siol, DBF_LONG, &pcar->sval);

    pcar->val  = menuCarstatesIDLE;
    strcpy(pcar->imss, "");
    pcar->oerr = 0;

    if( pcar->icid.type == CONSTANT )
      recGblInitConstantLink(&pcar->icid, DBF_LONG, &pcar->clid);

    pcar->udf = FALSE;
  }
  return(status);
}


static long process( carRecord *pcar )
{
  long status;
  long nRequest;
  long options;

#if DEBUG
  switch( pcar->ival )
  {
    case menuCarstatesIDLE:
      printf("%s CAR in -> IDLE\n", pcar->name);
      break;

    case menuCarstatesPAUSED:
      printf("%s CAR in -> PAUSED\n", pcar->name);
      break;

    case menuCarstatesBUSY:
      printf("%s CAR in -> BUSY\n", pcar->name);
      break;

    case menuCarstatesERROR:
      printf("%s CAR in -> ERROR\n", pcar->name);
      break;

    default:
      printf("Unknown CAR input: %d (%s)\n", pcar->ival, pcar->name);
      break;
  }
#endif

  pcar->pact = TRUE;

  /* get input client ID */

  nRequest = 1;
  options  = 0;
  status   = dbGetLink( &pcar->icid, DBR_LONG, &pcar->clid, &options, &nRequest );
  if( !status )
  {
    /* get the simulation level */
    nRequest = 1;
    options  = 0;
    status   = dbGetLink( &pcar->siml, DBR_ENUM, &pcar->simm, &options, &nRequest );
    if( !status )
    {
      if( pcar->simm != menuSimulationNONE )
      {
        nRequest = 1;
        options  = 0;
        status   = dbGetLink( &pcar->siol, DBR_LONG, &pcar->sval, &options, &nRequest );
        if( status )
          recGblRecordError( S_dev_badInpType, (void *)pcar, "carRecord: SIOL" );
        recGblSetSevr(pcar, SIMM_ALARM, pcar->sims);
      }
    }
    else
      recGblRecordError( S_dev_badInpType, (void *)pcar, "carRecord: SIML" );

    if( !status )
    {
      if( pcar->ival == menuCarstatesIDLE || pcar->ival == menuCarstatesPAUSED ||
          pcar->ival == menuCarstatesBUSY || pcar->ival == menuCarstatesERROR )
      {
        car_state_machine( pcar, pcar->ival );
        if(pcar->ival == menuCarstatesERROR)
          strcpy( pcar->omss, pcar->imss );
        else
          pcar->omss[0] = '\0';

        if( (pcar->val == menuCarstatesERROR) && (pcar->simm == menuSimulationNONE) )
          recGblSetSevr(pcar, SOFT_ALARM, pcar->ersv);

        if( pcar->simm == menuSimulationNONE )
          pcar->oerr = pcar->ierr;
        else
          pcar->oerr = pcar->sval;
      }
      else
      {
        strcpy( pcar->omss, "INVALID INPUT" );
        pcar->oerr = CAR_INVALID_INPUT;
      }

      recGblGetTimeStamp( pcar );
      monitor(pcar);
      recGblFwdLink(pcar);
    }
  }
  else
    recGblRecordError( S_dev_badInpType, (void *)pcar, "carRecord: ICID" );

  pcar->pact = FALSE;

  return(status);
}


static long get_value( carRecord *pcar, struct valueDes *pvdes )
{
    pvdes->field_type  = DBF_STRING;
    pvdes->no_elements = 1;
    pvdes->pvalue      = (void *)(&pcar->val);
    return(0);
}


static void monitor( carRecord *pcar )
{
  unsigned short monitor_mask;
  int flag = FALSE;

  monitor_mask = recGblResetAlarms(pcar);

  if (pcar->val != pcar->mval || pcar->clid != pcar->mcid)
  {
    monitor_mask |= DBE_VALUE;
    pcar->mval = pcar->val;
    pcar->mcid = pcar->clid;
    if( strncmp(pcar->mmss, pcar->omss, MAX_STRING_SIZE) )
      flag = TRUE;
    strncpy (pcar->mmss, pcar->omss, MAX_STRING_SIZE);
    pcar->merr = pcar->oerr;
  }

  if (pcar->val != pcar->aval || pcar->clid != pcar->acid)
  {
    monitor_mask |= DBE_LOG;
    pcar->aval = pcar->val;
    pcar->acid = pcar->clid;
    if( strncmp(pcar->amss, pcar->omss, MAX_STRING_SIZE) )
      flag = TRUE;
    strncpy( pcar->amss, pcar->omss, MAX_STRING_SIZE );
    pcar->aerr = pcar->oerr;
  }

  if (monitor_mask)
  {
    db_post_events( pcar, &pcar->clid, monitor_mask );
    if (flag)
      db_post_events( pcar, &(pcar->omss[0]), monitor_mask ); 
    db_post_events( pcar, &(pcar->oerr), monitor_mask ); 
    db_post_events( pcar, &pcar->val, monitor_mask ); 
  }

  return;
}


static long get_enum_str( struct dbAddr *paddr, char *pstring )
{
  carRecord *pcar = (carRecord *) paddr->precord;

  if (pcar->val == menuCarstatesIDLE)
    strcpy (pstring, "IDLE");
  else if (pcar->val == menuCarstatesPAUSED)
    strcpy (pstring, "PAUSED");
  else if (pcar->val == menuCarstatesERROR)
    strcpy (pstring, "ERROR");
  else if (pcar->val == menuCarstatesBUSY)
    strcpy (pstring, "BUSY");
  else
    strcpy(pstring,"Illegal_Value");

  return 0;
}


static long get_enum_strs( struct dbAddr *paddr, struct dbr_enumStrs *pes )
{
  pes->no_str = 4;
  memset (pes->strs,'\0', sizeof(pes->strs));
  strcpy (pes->strs[0], "IDLE");
  strcpy (pes->strs[1], "PAUSED");
  strcpy (pes->strs[2], "ERROR");
  strcpy (pes->strs[3], "BUSY");
  return 0;
}


static long put_enum_str( struct dbAddr *paddr, char *pstring )
{
  carRecord *pcar = (carRecord *)paddr->precord;
 
  if (!strncmp (pstring,"IDLE", 4) )
    pcar->val = menuCarstatesIDLE;
  else if (!strncmp (pstring,"PAUSED",6) )
    pcar->val = menuCarstatesPAUSED;
  else if( !strncmp(pstring,"ERROR",5) )
    pcar->val = menuCarstatesERROR;
  else if( !strncmp(pstring,"BUSY",4) )
    pcar->val = menuCarstatesBUSY;
  else
    return(S_db_badChoice);

  return(0);
}


static long get_precision( struct dbAddr *paddr, long *pprecision )
{
  *pprecision = 1;
  return(0);
}
