/* sirRecord.c - Record Support Routines for SIR (Status Item Record) records
 *
 *      Author:	Andy Foster 
 *
 *      History
 *      -------
 *      Version 1.0  15/11/95  ajf  Created.
 *      Version 1.1  22/12/96  bdg  Fixed cvt_dbaddr.
 *      Version 1.2  08/07/97  bdg  Added arrays and RVAL.
 *      Version 1.3  05/08/97  ajf  Fixed bug for monitoring LONG values.
 *      Version 1.4  15/09/97  bdg  Fixed init INP of CONSTANTs.
 *      Version 1.5  08/10/97  bdg  Added put_array_info and get_array_info.
 *			            Fixed read of sval to val.
 *      Version 1.6  22/01/98  ajf  Fixed raising of monitors on individual array
 *                                  elements.
 *      Version 1.7  26/01/98  ajf  Fixed raising of alarms by checking individual array
 *                                  elements.
 *      Version 1.8  14/03/01  ajf  Changes for 3.13.
 *                                  Initialise "string" constants to 0.
 *                                  Make sure that dbGetLinkValue is always called
 *                                  so that memcpy works.
 *                                  Set precision to 1 for VERS field.
 *                                  Replace "symFindbyName" by "symFindbyNameEPICS"
 *                                  for architectures which do not prepend an
 *                                  "_" (i.e. PPC).
 *	Version 1.9  27/04/01  ajf  Only call "dbGetLink" if not a constant link.
 *                                  Remove unnecessary redefinition of "dbGetLink".
 *      Version 2.0  11/12/03  ajf  Changes to comply with the new macro for "dbGetLink"
 *                                  in EPICS 3.13.9. Note: This record needs a rewrite!!
 *      Version 2.1  15/04/04  ajf  Conversion to EPICS 3.14.5.
 *      Version 2.2  27/07/12  pgr  Fix 64-bit problem in subroutine address
 *
 */

#define DEBUG   0
#define VERSION 2.2

#include        <stdlib.h>
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
#include 	<registryFunction.h>
#include 	<epicsExport.h>

#define GEN_SIZE_OFFSET
#include        <sirRecord.h>
#undef  GEN_SIZE_OFFSET

typedef long (*SUBFUNCPTR)(sirRecord *);

/* Create RSET - Record Support Entry Table*/
static long process (sirRecord *);
static long get_value (sirRecord *, struct valueDes *);
static long get_units (struct dbAddr *, char *);
static long init_record (sirRecord *, int);
static long cvt_dbaddr (struct dbAddr *);
static long get_precision (struct dbAddr *, long *);
static long get_alarm_double (struct dbAddr *, struct dbr_alDouble *);
static long get_array_info (struct dbAddr *, long *, long *);
static long put_array_info (struct dbAddr *, long);
#define report              NULL
#define initialize          NULL
#define special             NULL
#define get_enum_str        NULL
#define get_enum_strs       NULL
#define put_enum_str        NULL
#define get_graphic_double  NULL
#define get_control_double  NULL

rset sirRSET = {
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
  get_alarm_double
};
epicsExportAddress(rset, sirRSET);

static long findField( int, struct dbAddr *, long *, long );

static int sizeofTypes[] =
{
  MAX_STRING_SIZE, 1, 1, 2, 2, 4, 4, 4, 8, 2
};

static void monitor (sirRecord *);
static void checkAlarms (sirRecord *);


static long init_record( sirRecord *psir, int pass )
{
  long       status;
  SUBFUNCPTR subAddr;

  status = 0;
  if (pass == 0)
  {
    psir->vers = VERSION;
					/* reset array sizes */
    if (psir->nelm <= 0)
      psir->nelm = 1;
    psir->nord = 0;
					/* allocate space for results */
    if( psir->ftvl <= DBF_ENUM )
    {
      psir->val  = (char *) calloc (psir->nelm, sizeofTypes[psir->ftvl]);
      psir->rval = (char *) calloc (psir->nelm, sizeofTypes[psir->ftvl]);
      psir->sval = (char *) calloc (psir->nelm, sizeofTypes[psir->ftvl]);
      psir->mval = (char *) calloc (psir->nelm, sizeofTypes[psir->ftvl]);
      psir->aval = (char *) calloc (psir->nelm, sizeofTypes[psir->ftvl]);
      status = 0;
    }
    else
    {
      recGblRecordError (S_db_badChoice, (void *) psir, "recSir(init_record)");
      return S_db_badChoice;
    }
    return 0;
  }

  if( psir->siml.type == CONSTANT )
    recGblInitConstantLink(&psir->siml, DBF_ENUM, &psir->simm);

  if( (psir->siol.type == CONSTANT) && (psir->nelm < 2) )
  {
    recGblInitConstantLink(&psir->siol, psir->ftvl, &psir->sval);
    if( (psir->ftvl == DBF_STRING) && (!strncmp(psir->sval, "0.0", 3)) )
      strcpy(psir->sval, " ");
  }
					/* Find the subroutine */
  if (psir->snam[0] != '\0')
  {
    subAddr = (SUBFUNCPTR)registryFunctionFind(psir->snam);
    if( !subAddr )
    {
      recGblRecordError (S_db_BadSub, (void *) psir, "recSir(init_record)");
      return S_db_BadSub;
    }
    else
      psir->sadr = (long)subAddr;
  }

  if( (psir->inp.type == CONSTANT) && (psir->nelm < 2) )
  {
    if( !recGblInitConstantLink(&psir->inp, psir->ftvl, psir->val) )
    {
      recGblRecordError(S_db_badChoice, (void *) psir, "sirRecord: CONSTANT INP");
      status = S_db_badChoice;
    }
    else
    {
      if( (psir->ftvl == DBF_STRING) && (!strncmp(psir->val, "0.0", 3)) )
        strcpy(psir->val, " ");
      status = 0;
    }
  }

  psir->udf = FALSE;
  return status;
}


static long process( sirRecord *psir )
{
  SUBFUNCPTR psubroutine;
  long       status;
  long       nReq;
  long       opt;

  psir->pact = TRUE;

  if( psir->siml.type != CONSTANT )
  {
    nReq   = 1;
    opt    = 0;
    status = dbGetLink( &psir->siml, DBR_ENUM, &psir->simm, &opt, &nReq );
    if(status)
    {
      recGblRecordError( S_dev_badInpType, (void *)psir, "sirRecord: Process SIML" );
      return S_dev_badInpType;
    }
  }

  if( psir->simm != menuSimulationNONE )  /* simulation */
  {
    if( psir->siol.type != CONSTANT )
    {
      nReq   = psir->nelm;
      opt    = 0;
      status = dbGetLink( &psir->siol, psir->ftvl, psir->sval, &opt, &nReq );
      if(status)
      {
        recGblRecordError( S_dev_badInpType, (void *)psir, "sirRecord: Process SIOL" );
        return S_dev_badInpType;
      }
    }

    /* copy sim value into raw val */
    nReq = psir->nelm;
    memcpy( psir->rval, psir->sval, nReq*sizeofTypes[psir->ftvl]);
    recGblSetSevr(psir, SIMM_ALARM, psir->sims);
  }
  else					/* not simulation */
  {
    if( psir->inp.type != CONSTANT )
    {
      nReq   = psir->nelm;
      opt    = 0;
      status = dbGetLink( &psir->inp, psir->ftvl, psir->rval, &opt, &nReq );
      if(status)
      {
        recGblRecordError( S_dev_badInpType, (void *)psir, "sirRecord: Process INP" );
        return S_dev_badInpType;
      }
    }
    else
    {
      /* copy val into raw val */
      nReq = psir->nelm;
      memcpy( psir->rval, psir->val, nReq*sizeofTypes[psir->ftvl]);
    }
  }
  psir->nord = nReq;

  /* fills VAL only when nReq>0
   * if INP is blank, nothing happens
   * Must do this whether in simulation or not
   */

  nReq = psir->nelm;
  memcpy( psir->val, psir->rval, nReq*sizeofTypes[psir->ftvl] );

					/* do subroutine */
  /* psubroutine = (SUBFUNCPTR)((void *)psir->sadr); */
  psubroutine = (SUBFUNCPTR)registryFunctionFind(psir->snam);
  if( psubroutine )
  {
    status = psubroutine(psir);
    if (status)
    {
      recGblSetSevr (psir, SOFT_ALARM, psir->brsv);
      status = 0;
    }
  }

  strcpy(psir->omss, psir->imss);
					/* general record processing */
  recGblGetTimeStamp (psir);
  checkAlarms (psir);			/* Check for Alarms */
  monitor (psir);			/* Check Event list */
  recGblFwdLink (psir);			/* process forward scan link record */

  psir->pact = FALSE;
  return 0;
}


static long get_value( sirRecord *psir, struct valueDes *pvdes )
{
  pvdes->no_elements = psir->nelm;
  pvdes->pvalue      = psir->val;
  pvdes->field_type  = psir->ftvl;
  return 0;
}


static long cvt_dbaddr( struct dbAddr *paddr )
{
  int  error;
  int  flag;
  long no_elements;
  long nNew;

#if DEBUG
  printf("Calling cvt_dbaddr...\n");
#endif

  flag  = 1;
  nNew  = 0;
  error = findField( flag, paddr, &no_elements, nNew );
  if( error )
    printf("cvt_dbaddr: Could not find field\n");
 
  return(0);
}


static long findField( int flag, struct dbAddr *paddr, long *no_elements, long nNew )
{
  long      error;
  int       fieldIndex;
  sirRecord *psir;

  psir       = (sirRecord *)paddr->precord;
  error      = 0;
  fieldIndex = dbGetFieldIndex(paddr);
  switch( fieldIndex )
  {
    case sirRecordVAL:
      if( flag == 1 )
        paddr->pfield = psir->val;
      break;

    case sirRecordRVAL:
      if( flag == 1 )
        paddr->pfield = psir->rval;
      break;

    case sirRecordSVAL:
      if( flag == 1 )
        paddr->pfield = psir->sval;
      break;

    default:
      error = 1;
      break;
  }

  if( !error )
  {
    if( flag == 1 )
    {
      paddr->no_elements    = psir->nelm;
      paddr->field_type     = psir->ftvl;
      paddr->dbr_field_type = paddr->field_type;
      if( paddr->field_type == DBF_STRING )
        paddr->field_size = MAX_STRING_SIZE;
      else
        paddr->field_size = sizeofTypes[paddr->field_type];
    }
    else if( flag == 2 )
      *no_elements = psir->nelm;
    else if( flag == 3 )
      psir->nelm = nNew;
  }
 
  return(error);
}


static long get_units( struct dbAddr *paddr, char *punits )
{
  sirRecord *psir = (sirRecord *) paddr->precord;

  strncpy (punits, psir->egu, sizeof (psir->egu));
  return 0;
}


static long get_precision( struct dbAddr *paddr, long *precision )
{
  sirRecord *psir = (sirRecord *) paddr->precord;
  int       fieldIndex;
 
  fieldIndex = dbGetFieldIndex(paddr);
  if( fieldIndex == sirRecordVERS )
  {
    *precision = 1;
    return(0);
  }

  *precision = psir->prec;
  if(paddr->pfield == (void *) psir->val) 
    return 0;
  recGblGetPrec (paddr, precision);
  return 0;
}


static void monitor( sirRecord *psir )
{
  unsigned short monitor_mask;
  double         delta;
  double         current;
  double         archived;
  double         monitored;
  double         *dptr;
  double         *mptr;
  double         *aptr;
  long           currentL;
  long           archivedL;
  long           monitoredL;
  long           *dptrL;
  long           *mptrL;
  long           *aptrL;
  int            i;

  /* Initialised for the sake of the compiler */
  mptr  = NULL;
  aptr  = NULL;
  mptrL = NULL;
  aptrL = NULL;

  monitor_mask = recGblResetAlarms (psir);

  if( psir->ftvl == DBF_STRING )
  {
    if( memcmp(psir->mval, psir->val, psir->nelm*sizeofTypes[psir->ftvl]) )
    {
      monitor_mask |= DBE_VALUE;
      memcpy(psir->mval, psir->val, psir->nelm*sizeofTypes[psir->ftvl]);
    }

    if( memcmp(psir->aval, psir->val, psir->nelm*sizeofTypes[psir->ftvl]) )
    {
      monitor_mask |= DBE_LOG;
      memcpy(psir->aval, psir->val, psir->nelm*sizeofTypes[psir->ftvl]);
    }
  }
  else if( psir->ftvl == DBF_DOUBLE || psir->ftvl == DBF_LONG )
  {
    for(i=0; i<psir->nelm; i++)
    {
      if( psir->ftvl == DBF_DOUBLE )
      {
        dptr      = (double *)psir->val;
        mptr      = (double *)psir->mval;
        aptr      = (double *)psir->aval;
        current   = dptr[i];
        monitored = mptr[i];
        archived  = aptr[i];
      }
      else
      {
        dptrL      = (long *)psir->val;
        mptrL      = (long *)psir->mval;
        aptrL      = (long *)psir->aval;
        currentL   = dptrL[i];
        monitoredL = mptrL[i];
        archivedL  = aptrL[i];
        current    = (double)currentL;
        monitored  = (double)monitoredL;
        archived   = (double)archivedL;
      }
      delta = monitored - current;
      if (delta < 0.0)
        delta = -delta;
      if (delta > psir->mdel)
      {
        monitor_mask |= DBE_VALUE;
        if( psir->ftvl == DBF_DOUBLE )
          mptr[i]  = current;
        else
          mptrL[i] = current;
      }

      delta = archived - current;
      if (delta < 0.0)
        delta = -delta;
      if (delta > psir->adel)
      {
        monitor_mask |= DBE_LOG;
        if( psir->ftvl == DBF_DOUBLE )
          aptr[i]  = current;
        else
          aptrL[i] = current;
      }
    }
  }

  if( monitor_mask )
    db_post_events (psir, psir->val, monitor_mask);

  /* Check output string field for raising monitors */
 
  monitor_mask = 0;
  if (strncmp (psir->mmss, psir->omss, sizeof (psir->omss)))
  {
    monitor_mask |= DBE_VALUE;
    strncpy (psir->mmss, psir->omss, sizeof (psir->omss));
  }

  /* Check output string field for archiving changes */
 
  if (strncmp (psir->amss, psir->omss, sizeof(psir->omss)))
  {
    monitor_mask |= DBE_LOG;
    strncpy (psir->amss, psir->omss, sizeof (psir->omss));
  }

  if(monitor_mask)
    db_post_events (psir, &(psir->omss[0]), monitor_mask);
  
  return;
}


/*******************************************************************************
*/
static long get_alarm_double (
  struct dbAddr *paddr,
  struct dbr_alDouble *pad)
{
  sirRecord *psir = (sirRecord *) paddr->precord;

  if (paddr->pfield == (void *) &psir->val)
  {
    pad->upper_alarm_limit   = psir->hihi;
    pad->upper_warning_limit = psir->high;
    pad->lower_warning_limit = psir->low;
    pad->lower_alarm_limit   = psir->lolo;
  }
  else 
    recGblGetAlarmDouble (paddr, pad);

  return 0;
}


static void checkAlarms( sirRecord *psir )
{
  double          dval;
  long            lval;
  float           hyst, lalm, hihi, high, low, lolo;
  unsigned short  hhsv, llsv, hsv, lsv;
  double          *dptr;
  long            *dptrL;
  int             i;
 
  /* Initialised for the sake of the compiler */
  dval = 0.0;

  if (psir->udf == TRUE)
  {
    recGblSetSevr (psir, UDF_ALARM, INVALID_ALARM);
    return;
  }

  if (psir->ftvl == DBF_DOUBLE || psir->ftvl == DBF_LONG)
  {
    hihi = psir->hihi;
    lolo = psir->lolo;
    high = psir->high;
    low  = psir->low;
    hhsv = psir->hhsv;
    llsv = psir->llsv;
    hsv  = psir->hsv;
    lsv  = psir->lsv;
    hyst = psir->hyst; 
    lalm = psir->lalm;

    for(i=0; i<psir->nelm; i++)
    {
      if( psir->ftvl == DBF_DOUBLE )
      {
        dptr = (double *)psir->val;
        dval = dptr[i];
      }
      else
      {
        dptrL = (long *)psir->val;
        lval  = dptrL[i];
        dval  = (double)lval;
      }
 
      /* alarm condition hihi */

      if( hhsv && (dval >= hihi || ((lalm==hihi) && (dval >= hihi-hyst))) )
      {
        if( recGblSetSevr (psir, HIHI_ALARM, psir->hhsv) )
          psir->lalm = hihi;
        return;
      }

      /* alarm condition lolo */

      if( llsv && (dval <= lolo || ((lalm==lolo) && (dval <= lolo+hyst))) )
      {
        if( recGblSetSevr (psir, LOLO_ALARM, psir->llsv) )
          psir->lalm = lolo;
        return;
      }

      /* alarm condition high */

      if( hsv && (dval >= high || ((lalm==high) && (dval >= high-hyst))) )
      {
        if( recGblSetSevr (psir, HIGH_ALARM, psir->hsv) )
          psir->lalm = high;
        return;
      }

      /* alarm condition low */

      if( lsv && (dval <= low || ((lalm==low) && (dval <= low+hyst))) )
      {
        if( recGblSetSevr (psir, LOW_ALARM, psir->lsv) )
          psir->lalm = low;
        return;
      }
    }

    /* we only get here if the whole array (val) is out of alarm by at least hyst */

    psir->lalm = dval;
  }
}


static long put_array_info( struct dbAddr *paddr, long nNew )
{
  int  error;
  int  flag;
  long no_elements;
 
#if DEBUG
  printf("Calling put_array_info...\n");
#endif   
  flag  = 3;
  error = findField( flag, paddr, &no_elements, nNew );
  if( error )
    printf("put_array_info: Could not find field\n");
  return(0);
}


static long get_array_info( struct dbAddr *paddr, long *no_elements, long *offset )
{
  int  error;
  int  flag;
  long nNew;

#if DEBUG
  printf("Calling get_array_info...\n");
#endif   
  *offset = 0;
  nNew    = 0;
  flag    = 2;
  error   = findField( flag, paddr, no_elements, nNew );
  if( error )
    printf("get_array_info: Could not find field\n");
  return(0);
}
