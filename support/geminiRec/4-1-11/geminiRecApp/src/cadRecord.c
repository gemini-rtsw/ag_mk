/* cadRecord.c - Record Support Routines for CAD (Command Action Directive) */
/*
 *      Author: Andy Foster
 *
 *	History
 *	-------
 *	Version 1.0  15/11/95  ajf  Created.
 *	Version 1.1  24/02/96  bdg  Added FLNK. Deleted ABORT and added MARK directives.
 *                                  Added state to mark field.
 *	Version 1.2  29/03/96  bdg  Switched VAL and MESS monitors.
 *	Version 1.3  13/06/96  bdg  STOP added to state machine.
 *	Version 1.4  19/06/96  bdg  PRESET link executed in START, fixed STOP, FLNK done last.
 *	Version 1.5  06/10/96  bdg  Changed FLNK to always fire.  Added ODIR.
 *	Version 1.6  04/11/96  bdg  FLNK always fired.  Output monitors posted on changes.
 *	Version 1.7  22/12/96  bdg  Fixed outvals.
 *	Version 1.8  27/12/96  bdg  Fixed monitors on VALA-VALT.
 *	Version 1.9  07/03/97  bdg  Fixed monitor STRING copy pointer.
 *	Version 2.0  19/03/97  bdg  Added check of DB_LINK in START process of PRESET.
 *	                            Added MARK to the enum_str functions.
 *	Version 2.1  21/03/97  bdg  Process didn't handle callbacks right.
 *	Version 2.2  12/04/98  ajf  Fixed bug where output links (OUTA etc.) were fired off 
 *                                  even when user routine returned an error from MARK, 
 *                                  PRESET, START or STOP.
 *	Version 2.3  12/03/99  ajf  Fixed bug where initialisation routine was being called
 *                                  even if it was not loaded.
 *      Version 2.4  15/03/01  ajf  Changes for 3.13.
 *                                  Set precision to 1 for VERS field.
 *                                  Initialise "string" constants to 0.
 *                                  Replace "symFindbyName" by "symFindbyNameEPICS"
 *                                  for architectures which do not prepend an
 *                                  "_" (i.e. PPC).
 *	Version 2.5  11/07/01  ajf  Do not fire the OUT links on a CLEAR directive.
 *                                  Remove "goto" statement.
 *      Version 2.6  02/08/01  ajf  Add "db_post_events" on VAL for the case of mark = 0.
 *                                  This forces processing of the new apply record.
 *      Version 2.7  11/12/03  ajf  Changes to comply with the new macro for 
 *                                  "dbGetLink" in EPICS 3.13.9.
 *      Version 2.8  15/04/04  ajf  Conversion to EPICS 3.14.5.
 *      Version 2.9  27/07/12  pgr  Fixed problem 64-bit problem in subroutine address
 *
 */

#define DEBUG   0
#define VERSION 2.9

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
#include	<registryFunction.h>
#include	<epicsExport.h>

#define GEN_SIZE_OFFSET
#include	<cadRecord.h>
#undef  GEN_SIZE_OFFSET

typedef long (*SUBFUNCPTR)(cadRecord *);

/* Create RSET - Record Support Entry Table*/

static long init_record();
static long process();
static long get_value();
static long get_precision();
static long get_enum_str();
static long get_enum_strs();
static long put_enum_str();
static long cvt_dbaddr();
static long special();
#define report             NULL
#define initialize         NULL
#define get_units          NULL
#define get_array_info     NULL
#define put_array_info     NULL
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double   NULL

rset cadRSET={
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
epicsExportAddress(rset,cadRSET);

static void monitor();
static long do_sub();

#define ARG_MAX 20

/* Sizes of field types */
static int sizeofTypes[] = {0, 1, 1, 2, 2, 4, 4, 4, 8, 2};

#if DEBUG
static char *printDir( int dir );
#endif


static long init_record( cadRecord *pcad, int pass )
{
  SUBFUNCPTR     psubroutine;
  SUBFUNCPTR     subAddr;
  long	         status;
  struct link    *plink;
  void           **valptr, **oldptr;
  unsigned short *typptr;
  char           *cptr;
  int            i;

  status = 0;
  if( pass == 0 )
  {
    pcad->vers = VERSION;

    /* Is this CAD record a 2-state or 3-state machine?
       This replaces the need for a "subCad" record.
     */

    if( pcad->mflg == cadMFLG_THREE_STATES )
      pcad->base = 0;
    else
      pcad->base = 1;

#if DEBUG
    printf("init_record: Number of Args = %d\n", pcad->ctyp);
#endif

    valptr  = &pcad->vala;
    oldptr  = &pcad->olda;
    typptr  = &pcad->ftva;
    for( i=0; i<pcad->ctyp; i++, valptr++, oldptr++, typptr++ )
    {
      if( *typptr == DBF_STRING )
      {
        *valptr = (char *)calloc(1, MAX_STRING_SIZE);
        *oldptr = (char *)calloc(1, MAX_STRING_SIZE);
        status  = 0;
      }
      else if( *typptr == DBF_DOUBLE )
      {
        *valptr  = (char *)calloc(1, sizeof(double));
        *oldptr  = (char *)calloc(1, sizeof(double));
        status  = 0;
      }
      else if( *typptr == DBF_LONG )
      {
        *valptr  = (char *)calloc(1, sizeof(long));
        *oldptr  = (char *)calloc(1, sizeof(long));
        status  = 0;
      }
      else
      {
        recGblRecordError(S_db_badChoice, (void *)pcad, "cadRecord(init_record)");
        status = S_db_badChoice;
      }
    }
  }
  else if( pass == 1 )
  {
    if( pcad->siml.type == CONSTANT )
      recGblInitConstantLink(&pcad->siml, DBF_ENUM, &pcad->simm);

    if( pcad->siol.type == CONSTANT )
      recGblInitConstantLink(&pcad->siol, DBF_LONG, &pcad->sval);

    plink = &pcad->inpa;
    cptr  = pcad->a;
    for( i=0; i<pcad->ctyp; i++, plink++, cptr+=MAX_STRING_SIZE )
    {
      if( (*plink).type == CONSTANT )
      {
        if( recGblInitConstantLink(plink, DBF_STRING, cptr) )
        {
          if( !strncmp((char *)cptr, "0.0", 3) )
            strcpy((char *)cptr, " ");
          pcad->udf = FALSE;
        }
        else
          pcad->udf = TRUE;
      }
    }

    /* Find the user initialisation routine and call it if there is one */
 
    if( pcad->inam[0] != '\0' )
    {
      subAddr = (SUBFUNCPTR)registryFunctionFind( pcad->inam );
      if( !subAddr )
      {
        recGblRecordError(S_db_BadSub,(void *)pcad,"cadRecord(init_record)");
        status = S_db_BadSub;
      }
      else
      {
        psubroutine = subAddr;
        status      = psubroutine(pcad);
      }
    }

    if( !status )
    {
      /* Find the subroutine to call at Process time */

      if( pcad->snam[0] != '\0' )
      {
        subAddr = (SUBFUNCPTR)registryFunctionFind( pcad->snam );
        if( !subAddr )
        {
          recGblRecordError(S_db_BadSub,(void *)pcad,"recCad(init_record)");
          status = S_db_BadSub;
        }
        else
          pcad->sadr = (long)subAddr;
      }
    }

    if( !status )
    {
      pcad->dir  = menuDirectiveCLEAR;
      pcad->mark = pcad->base;
      pcad->udf  = FALSE;
    }

    if( pcad->udf == TRUE )
      recGblSetSevr(pcad, UDF_ALARM, INVALID_ALARM);
  }
  return( status );
}


static long process( cadRecord *pcad )
{
  long           status;
  long           error;
  int            i;
  struct link    *plink;
  char           *cptr;
  void           **valptr;
  long           nRequest;
  long           options;
  unsigned short *typptr;

  pcad->pact = TRUE;

#if DEBUG
  printf("%s: Process: Dir = %s\n", pcad->name, printDir(pcad->dir));
#endif

  if( (pcad->dir == menuDirectivePRESET || pcad->dir == menuDirectiveSTART ||
       pcad->dir == menuDirectiveSTOP) && pcad->mark == 0 )
  {
    /* Process the forward link */
    db_post_events(pcad, &pcad->val, 1);
    recGblFwdLink(pcad);
    pcad->pact = FALSE;
  }
  else
  {
    status   = 0;
    error    = 0;
    nRequest = 1;
    options  = 0;
    status   = dbGetLink( &(pcad->siml), DBR_ENUM, &(pcad->simm), &options, &nRequest );
    if( !status )
    {
      if( pcad->simm != menuSimulationNONE )
      {
        nRequest = 1;
        options  = 0;
        status   = dbGetLink( &(pcad->siol), DBR_LONG, &(pcad->sval), &options, &nRequest );
        if( status )
          recGblRecordError( S_dev_badInpType, (void *)pcad, "cadRecord: process" );
        recGblSetSevr(pcad, SIMM_ALARM, pcad->sims);
      }
    }
 
    if( !status )
    {
      plink = &pcad->inpa;
      cptr  = pcad->a;
      for( i=0; i<pcad->ctyp; i++, plink++, cptr+=MAX_STRING_SIZE )
      {
        nRequest = 1;
        options  = 0;
        status   = dbGetLink( plink, DBR_STRING, cptr, &options, &nRequest );
        if( !RTN_SUCCESS(status) )
          status = 1;
      }
    }

    if( !status )
    {
      switch( pcad->dir )
      {
        case menuDirectiveMARK:
          error = do_sub(pcad);
          if( pcad->simm != menuSimulationNONE )
            error = pcad->sval;
          pcad->val  = error;
          pcad->osim = pcad->simm;
          pcad->ocid = pcad->icid;
          if( !error )
            pcad->mark = 1;
          break;

        case menuDirectiveCLEAR:
          error = do_sub(pcad);
          if( pcad->simm != menuSimulationNONE )
            error = pcad->sval;
          pcad->val  = error;
          pcad->osim = pcad->simm;
          pcad->ocid = pcad->icid;
          if( !error )
            pcad->mark = pcad->base;
          break;

        case menuDirectivePRESET:
          error = do_sub(pcad);
          if( pcad->simm != menuSimulationNONE )
            error = pcad->sval;
          pcad->val  = error;
          pcad->osim = pcad->simm;
          pcad->ocid = pcad->icid;
          if( !error )
            pcad->mark = 2;
          break;

        case menuDirectiveSTART:
          if( pcad->mark == 1 )
          {
            pcad->dir  = menuDirectivePRESET;
            error      = do_sub(pcad);
            pcad->val  = error;
            pcad->osim = pcad->simm;
            pcad->ocid = pcad->icid;
            if( !error )
            {
              /* Fire off PRESET forward link */
              dbScanFwdLink( &(pcad->plnk) );
              pcad->mark = 2;

              /* Put the values on the output links */

              plink  = &pcad->outa;
              valptr = &pcad->vala;
              typptr = &pcad->ftva;
              for( i=0; i<pcad->ctyp; i++, plink++, valptr++, typptr++ )
              {
                nRequest = 1;
                status   = dbPutLink( plink, *typptr, *valptr, nRequest );
              }

              recGblGetTimeStamp(pcad);
              monitor(pcad, 0);

              pcad->dir  = menuDirectiveSTART;
              error      = do_sub(pcad);
              if( pcad->simm != menuSimulationNONE )
                error = pcad->sval;
              pcad->val  = error;
              pcad->osim = pcad->simm;
              pcad->ocid = pcad->icid;
            }
            pcad->mark = pcad->base;
          }
          else if( pcad->mark == 2 )
          {
            error = do_sub(pcad);
            if( pcad->simm != menuSimulationNONE )
              error = pcad->sval;
            pcad->val  = error;
            pcad->osim = pcad->simm;
            pcad->ocid = pcad->icid;
            pcad->mark = pcad->base;
          }
          break;

        case menuDirectiveSTOP:
          if (pcad->mark > 0)
          {
            error = do_sub(pcad);
            if( pcad->simm != menuSimulationNONE )
              error = pcad->sval;
            pcad->val  = error;
            pcad->osim = pcad->simm;
            pcad->ocid = pcad->icid;
          }
          if( !error )
            pcad->mark = pcad->base;
          break;

        default:
          error = 1;
	  printf("Unknown CAD Directive: %d (%s)\n", pcad->dir, pcad->name);
          break;
      }

      /* enforce rule that MESS is empty if VAL is 0 */
      if( pcad->val == 0 )
      {
        *pcad->mess = '\0';

        /* Put the values on the output links for all directives except CLEAR */

        if( pcad->dir != menuDirectiveCLEAR )
        {
          plink  = &pcad->outa;
          valptr = &pcad->vala;
          typptr = &pcad->ftva;
          for( i=0; i<pcad->ctyp; i++, plink++, valptr++, typptr++ )
          {
            nRequest = 1;
            status   = dbPutLink( plink, *typptr, *valptr, nRequest );
          }
        }
      }

      recGblGetTimeStamp (pcad);
      monitor(pcad, 1);

      if( !error )
      {
        switch( pcad->dir )
        {
  	  case menuDirectiveMARK:
#if DEBUG
            printf("CAD: Setting off MARK Link\n");
#endif
            dbScanFwdLink( &(pcad->mlnk) );
	    break;

	  case menuDirectiveCLEAR:
#if DEBUG
            printf("CAD: Setting off CLEAR Link\n");
#endif
            dbScanFwdLink( &(pcad->clnk) );
	    break;

          case menuDirectivePRESET:
#if DEBUG
            printf("CAD: Setting off PRESET Link\n");
#endif
            dbScanFwdLink( &(pcad->plnk) );
	    break;

          case menuDirectiveSTART:
#if DEBUG
            printf("CAD: Setting off START Link\n");
#endif
            dbScanFwdLink( &(pcad->stlk) );
	    break;

          case menuDirectiveSTOP:
#if DEBUG
            printf("CAD: Setting off STOP Link\n");
#endif
            dbScanFwdLink( &(pcad->splk) );
	    break;

          default:
	    break;
        }
      }
    }
    /* Process the forward link */
    recGblFwdLink(pcad);
    pcad->pact = FALSE;
  }
  return(0);
}


static long get_value( cadRecord *pcad, struct valueDes *pvdes )
{
    pvdes->field_type  = DBF_LONG;
    pvdes->no_elements = 1;
    pvdes->pvalue      = (void *)(&pcad->val);
    return(0);
}


static void monitor( cadRecord *pcad, int reset )
{
  unsigned short monitor_mask;
  void **valptr, **oldptr;
  unsigned short *typptr;
  short i;

  if( reset )
    monitor_mask = recGblResetAlarms(pcad);
  else
    monitor_mask = 0;

  monitor_mask |= DBE_VALUE | DBE_LOG;
       
  /* Raise Monitors on VAL, MESS, OSIM, OCID, MARK */

  if(monitor_mask)
  {
    if (pcad->val != 0 || strncmp (pcad->omss, pcad->mess, MAX_STRING_SIZE) != 0)
    {
      db_post_events(pcad, &pcad->mess, monitor_mask);
      strncpy (pcad->omss, pcad->mess, MAX_STRING_SIZE);
    }
    db_post_events(pcad, &pcad->val,  monitor_mask);
    db_post_events(pcad, &pcad->osim, monitor_mask);
    db_post_events(pcad, &pcad->ocid, monitor_mask);
    db_post_events(pcad, &pcad->mark, monitor_mask);

    valptr  = &pcad->vala;
    oldptr  = &pcad->olda;
    typptr  = &pcad->ftva;
    for( i=0; i<pcad->ctyp; i++, valptr++, oldptr++, typptr++ )
    {
      if( *typptr == DBF_STRING )
      {
	if (strncmp ((char *) *valptr, (char *) *oldptr, MAX_STRING_SIZE) != 0)
	  db_post_events (pcad, *valptr, monitor_mask);
	strncpy ((char *) *oldptr, (char *) *valptr, MAX_STRING_SIZE);
      }
      else if( *typptr == DBF_DOUBLE )
      {
	if (*(double *) *valptr != *(double *) *oldptr)
	  db_post_events (pcad, *valptr, monitor_mask);
	*(double *) *oldptr = *(double *) *valptr;
      }
      else if( *typptr == DBF_LONG )
      {
        if (*(long *) *valptr != *(long *) *oldptr)
	  db_post_events (pcad, *valptr, monitor_mask);
	*(long *) *oldptr = *(long *) *valptr;
      }
    }
    if (pcad->val == 0)			/* copy and fire ODIR if VAL is OK */
    {
      pcad->odir = pcad->dir;
      db_post_events(pcad, &pcad->odir, monitor_mask);
    }
  }
  return;
}


static long get_enum_str( struct dbAddr *paddr, char *pstring )
{
  cadRecord *pcad = (cadRecord *)paddr->precord;

  if( pcad->dir == menuDirectiveMARK)
  {
    strncpy(pstring,"MARK",4);
    pstring[4] = 0;
  }
  else if( pcad->dir == menuDirectiveCLEAR)
  {
    strncpy(pstring,"CLEAR",5);
    pstring[5] = 0;
  }
  else if( pcad->dir == menuDirectivePRESET )
  {
    strncpy(pstring,"PRESET",6);
    pstring[6] = 0;
  }
  else if( pcad->dir == menuDirectiveSTART )
  {
    strncpy(pstring,"START",5);
    pstring[5] = 0;
  }
  else if( pcad->dir == menuDirectiveSTOP )
  {
    strncpy(pstring,"STOP",4);
    pstring[4] = 0;
  }
  else
    strcpy(pstring,"Illegal_Value");

  return(0);
}


static long get_enum_strs( struct dbAddr *paddr, struct dbr_enumStrs *pes )
{
  pes->no_str = 5;
  memset(pes->strs,'\0',sizeof(pes->strs));
  strncpy(pes->strs[0],"MARK",4);
  strncpy(pes->strs[1],"CLEAR",5);
  strncpy(pes->strs[2],"PRESET",6);
  strncpy(pes->strs[3],"START",5);
  strncpy(pes->strs[4],"STOP",4);
  return(0);
}


static long put_enum_str( struct dbAddr *paddr, char *pstring )
{
  cadRecord *pcad = (cadRecord *)paddr->precord;

  if( !strncmp(pstring,"MARK",4) )
    pcad->dir = menuDirectiveMARK;
  else if( !strncmp(pstring,"CLEAR",5) )
    pcad->dir = menuDirectiveCLEAR;
  else if( !strncmp(pstring,"PRESET",6) )
    pcad->dir = menuDirectivePRESET;
  else if( !strncmp(pstring,"START",5) )
    pcad->dir = menuDirectiveSTART;
  else if( !strncmp(pstring,"STOP",4) )
    pcad->dir = menuDirectiveSTOP;
  else
    return(S_db_badChoice);
  return(0);
}


static long get_precision( struct dbAddr *paddr, long *pprecision )
{
  cadRecord *pcad = (cadRecord *)paddr->precord;
  int       fieldIndex;

  fieldIndex = dbGetFieldIndex(paddr);
  if( fieldIndex == cadRecordVERS )
  {
    *pprecision = 1;
    return 0;
  }

  *pprecision = pcad->prec;
  if(paddr->pfield==(void *)&pcad->val)
    return(0);
  recGblGetPrec(paddr, pprecision);
  return(0);
}


static long do_sub( cadRecord *pcad )
{
  long       status;
  SUBFUNCPTR psubroutine;

  /* If there is a routine, call it */

  if( pcad->snam[0] != '\0' )
  {
    /* psubroutine = (SUBFUNCPTR)((void *)pcad->sadr); */
    psubroutine = (SUBFUNCPTR)registryFunctionFind( pcad->snam );
    if( !psubroutine )
    {
      recGblRecordError(S_db_BadSub,(void *)pcad,"cadRecord(do_sub)");
      status = S_db_BadSub;
    }
    else
    {
      status = psubroutine(pcad);
/*
      If the user returns an error and we are not in simulation mode
      then set an alarm. If we are in simulation mode, the alarm will
      already have been set to SIMM_ALARM in "process".
*/
      if( status && (pcad->simm == menuSimulationNONE) )
        recGblSetSevr(pcad, SOFT_ALARM, pcad->ersv);
    }
  }
  else
    status = 0;

  return( status );
}


static long cvt_dbaddr( struct dbAddr *paddr )
{
  long      error;
  int       fieldIndex;
  cadRecord *pcad;

  pcad       = (cadRecord *)paddr->precord;
  error      = 0;
  fieldIndex = dbGetFieldIndex(paddr);
  switch( fieldIndex )
  {
    case cadRecordVALA:
      paddr->pfield     = pcad->vala;
      paddr->field_type = pcad->ftva;
      break;
  
    case cadRecordVALB:
      paddr->pfield     = pcad->valb;
      paddr->field_type = pcad->ftvb;
      break;
  
    case cadRecordVALC:
      paddr->pfield     = pcad->valc;
      paddr->field_type = pcad->ftvc;
      break;
  
    case cadRecordVALD:
      paddr->pfield     = pcad->vald;
      paddr->field_type = pcad->ftvd;
      break;
  
    case cadRecordVALE:
      paddr->pfield     = pcad->vale;
      paddr->field_type = pcad->ftve;
      break;
  
    case cadRecordVALF:
      paddr->pfield     = pcad->valf;
      paddr->field_type = pcad->ftvf;
      break;
  
    case cadRecordVALG:
      paddr->pfield     = pcad->valg;
      paddr->field_type = pcad->ftvg;
      break;
  
    case cadRecordVALH:
      paddr->pfield     = pcad->valh;
      paddr->field_type = pcad->ftvh;
      break;
  
    case cadRecordVALI:
      paddr->pfield     = pcad->vali;
      paddr->field_type = pcad->ftvi;
      break;
  
    case cadRecordVALJ:
      paddr->pfield     = pcad->valj;
      paddr->field_type = pcad->ftvj;
      break;
  
    case cadRecordVALK:
      paddr->pfield     = pcad->valk;
      paddr->field_type = pcad->ftvk;
      break;
  
    case cadRecordVALL:
      paddr->pfield     = pcad->vall;
      paddr->field_type = pcad->ftvl;
      break;

    case cadRecordVALM:
      paddr->pfield     = pcad->valm;
      paddr->field_type = pcad->ftvm;
      break;
  
    case cadRecordVALN:
      paddr->pfield     = pcad->valn;
      paddr->field_type = pcad->ftvn;
      break;
  
    case cadRecordVALO:
      paddr->pfield     = pcad->valo;
      paddr->field_type = pcad->ftvo;
      break;
  
    case cadRecordVALP:
      paddr->pfield     = pcad->valp;
      paddr->field_type = pcad->ftvp;
      break;
  
    case cadRecordVALQ:
      paddr->pfield     = pcad->valq;
      paddr->field_type = pcad->ftvq;
      break;
  
    case cadRecordVALR:
      paddr->pfield     = pcad->valr;
      paddr->field_type = pcad->ftvr;
      break;
  
    case cadRecordVALS:
      paddr->pfield     = pcad->vals;
      paddr->field_type = pcad->ftvs;
      break;
  
    case cadRecordVALT:
      paddr->pfield     = pcad->valt;
      paddr->field_type = pcad->ftvt;
      break;
  
    case cadRecordOLDA:
      paddr->pfield     = pcad->olda;
      paddr->field_type = pcad->ftva;
      break;
  
    case cadRecordOLDB:
      paddr->pfield     = pcad->oldb;
      paddr->field_type = pcad->ftvb;
      break;
  
    case cadRecordOLDC:
      paddr->pfield     = pcad->oldc;
      paddr->field_type = pcad->ftvc;
      break;
  
    case cadRecordOLDD:
      paddr->pfield     = pcad->oldd;
      paddr->field_type = pcad->ftvd;
      break;
  
    case cadRecordOLDE:
      paddr->pfield     = pcad->olde;
      paddr->field_type = pcad->ftve;
      break;
  
    case cadRecordOLDF:
      paddr->pfield     = pcad->oldf;
      paddr->field_type = pcad->ftvf;
      break;
  
    case cadRecordOLDG:
      paddr->pfield     = pcad->oldg;
      paddr->field_type = pcad->ftvg;
      break;
  
    case cadRecordOLDH:
      paddr->pfield     = pcad->oldh;
      paddr->field_type = pcad->ftvh;
      break;
  
    case cadRecordOLDI:
      paddr->pfield     = pcad->oldi;
      paddr->field_type = pcad->ftvi;
      break;
  
    case cadRecordOLDJ:
      paddr->pfield     = pcad->oldj;
      paddr->field_type = pcad->ftvj;
      break;
  
    case cadRecordOLDK:
      paddr->pfield     = pcad->oldk;
      paddr->field_type = pcad->ftvk;
      break;
  
    case cadRecordOLDL:
      paddr->pfield     = pcad->oldl;
      paddr->field_type = pcad->ftvl;
      break;

    case cadRecordOLDM:
      paddr->pfield     = pcad->oldm;
      paddr->field_type = pcad->ftvm;
      break;
  
    case cadRecordOLDN:
      paddr->pfield     = pcad->oldn;
      paddr->field_type = pcad->ftvn;
      break;
  
    case cadRecordOLDO:
      paddr->pfield     = pcad->oldo;
      paddr->field_type = pcad->ftvo;
      break;
  
    case cadRecordOLDP:
      paddr->pfield     = pcad->oldp;
      paddr->field_type = pcad->ftvp;
      break;
  
    case cadRecordOLDQ:
      paddr->pfield     = pcad->oldq;
      paddr->field_type = pcad->ftvq;
      break;
  
    case cadRecordOLDR:
      paddr->pfield     = pcad->oldr;
      paddr->field_type = pcad->ftvr;
      break;
  
    case cadRecordOLDS:
      paddr->pfield     = pcad->olds;
      paddr->field_type = pcad->ftvs;
      break;
  
    case cadRecordOLDT:
      paddr->pfield     = pcad->oldt;
      paddr->field_type = pcad->ftvt;
      break;

    default:
      error = 1;
      printf("cadRecord: cvt_dbaddr - Could not find field\n");
      break;
  }

  if( !error )
  {
    paddr->no_elements    = 1;
    paddr->dbr_field_type = paddr->field_type;
    if( paddr->field_type == DBF_STRING )
      paddr->field_size = MAX_STRING_SIZE;
    else
      paddr->field_size = sizeofTypes[paddr->field_type];
  }
  return(error);
}


static long special( struct dbAddr *paddr, int after )
{
    cadRecord *pcad;

    if( !after )
      return 0;

    pcad = (cadRecord *)paddr->precord;

    if(paddr->special == SPC_MOD)
    {
	pcad->mark = 1;
        db_post_events(pcad, &pcad->mark, 1);
    }
    else
    {
	recGblDbaddrError (S_db_badChoice, paddr, "cadRecord: special");
	return (S_db_badChoice);
    }

    return 0;
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
