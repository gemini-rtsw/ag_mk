/* lutoutRecord.c - record support for Lookup Table
 *
 *	Author: Bret Goodrich
 *
 *	History
 *	-------
 *	Version 1.0 18/07/96  bdg  Created.
 *	Version 1.1 10/09/96  bdg  Added monitors for NVAL, VALA-D.
 *	Version 1.2 10/10/96  bdg  Created space in init_record for OLDA-D.
 *	Version 1.3 12/10/96  bdg  Moved lookup here from soft dev.
 *	Version 1.4 09/07/98  ajf  Fixed bug caused by having a lookup table
 *                                 containing an NVAL of 0.
 *      Version 1.5 15/03/01  ajf  Changes for 3.13.
 *                                 Set precision of VERS field to 1.
 *      Version 1.6 05/07/04  ajf  Changes for 3.14.
 *
 */

#define VERSION 1.6

#include	<stdlib.h>
#include        <stdio.h>
#include        <string.h>

#include        <alarm.h>
#include        <dbDefs.h>
#include        <dbEvent.h>
#include        <dbAccess.h>
#include        <dbFldTypes.h>
#include        <ellLib.h>
#include        <errMdef.h>
#include        <recGbl.h>
#include        <recSup.h>
#include        <devSup.h>
#include        <special.h>
#include	<lut.h>

#define GEN_SIZE_OFFSET
#include        <lutoutRecord.h>
#undef  GEN_SIZE_OFFSET

#include <epicsExport.h>
#include <iocsh.h>
#include <errlog.h>

static int debugLevel = 0;


/* Create RSET - Record Support Entry Table */
 
static long		   init_record();
static long		   process();
static long		   get_enum_strs();
static long		   cvt_dbaddr();
static long		   special();
static long		   get_precision();
static long		   get_value();
#define get_enum_str	   NULL
#define put_enum_str	   NULL
#define report		   NULL
#define initialize	   NULL
#define get_units	   NULL
#define get_array_info	   NULL
#define put_array_info	   NULL
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double   NULL
 
rset lutoutRSET =
{
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
epicsExportAddress(rset,lutoutRSET);

struct lutoutdset
{
    long	number;
    DEVSUPFUN	dev_report;
    DEVSUPFUN	init;
    DEVSUPFUN	init_record;
    DEVSUPFUN	get_ioint_info;
    DEVSUPFUN	write_lutout;
} lutoutdset;




static void	checkAlarms ( lutoutRecord * );
static void	monitor ( lutoutRecord * );
static long	read_file ( lutoutRecord * );


/*******************************************************************************
*/

static long init_record( lutoutRecord *plutout, int pass )
{
    int i;
    long status;
    struct lutoutdset *pdset;

    if (pass == 0)
    {
        plutout->vers = VERSION;

	/* read remote data file */
	if (read_file (plutout))
	    return -1;

	/* alloc space for inputs */
	for (i = 0; i < LUT_NUM_SZ; i++)
	{
	    switch (*(&plutout->ftva+i))
	    {
		case DBF_STRING:
		    *(&plutout->vala+i) = (void *) calloc (1, MAX_STRING_SIZE);
		    *(&plutout->olda+i) = (void *) calloc (1, MAX_STRING_SIZE);
		    break;
		case DBF_DOUBLE:
		    *(&plutout->vala+i) = (void *) calloc (1, sizeof (double));
		    *(&plutout->olda+i) = (void *) calloc (1, sizeof (double));
		    break;
		case DBF_LONG:
		    *(&plutout->vala+i) = (void *) calloc (1, sizeof (long));
		    *(&plutout->olda+i) = (void *) calloc (1, sizeof (long));
		    break;
		default:
		    recGblRecordError (S_db_badChoice, (void *) plutout,
			"lutoutRecord: init_record FTVx");
		    return S_db_badChoice;
	    }
	}
    }
    else if (pass == 1)
    {
	if ((pdset = (struct lutoutdset *) (plutout->dset)) == NULL)
	{
	    recGblRecordError (S_dev_noDSET,(void *) plutout,
		"lutoutRecord: init_record");
	    return S_dev_noDSET;
	}
	if (pdset->number < 5 || pdset->write_lutout == NULL)
	{
	    recGblRecordError (S_dev_missingSup, (void *) plutout,
		"lutoutRecord: init_record");
	    return S_dev_missingSup;
	}
	/* initialize input values */
	if (pdset->init_record)
	{
	    if ((status = (*pdset->init_record) (plutout)))
		return status;
	}
    }

    return 0;
}


/*******************************************************************************
*/

static long process( lutoutRecord *plutout )
{
    struct lutoutdset *pdset = (struct lutoutdset *) (plutout->dset);
    long i, status;
    unsigned long pact = plutout->pact;
    LUT *p;

					/* if no dev sup, set PACT and exit */
    if (pdset == NULL || pdset->write_lutout == NULL)
    {
	plutout->pact = TRUE;
	recGblRecordError (S_dev_missingSup, (void *) plutout,
	    "lutoutRecord: Process write_lutout");
	return S_dev_missingSup;
    }

    plutout->nval = 0;

					/* find configuration in table */
    for (p = (LUT *) ellFirst ((ELLLIST *)plutout->ltbl); p != NULL;
	p = (LUT *) ellNext ((ELLNODE *) p))
    {
	if (strncmp (p->tag, plutout->val, LUT_TAG_SZ) == 0)
	{
					/* copy config to LUT value fields */
	    for (i = 0; i < p->nval; i++)
	    {
					/* only write the selected bits */
		if (plutout->selb & (1 << i))
		{
		    if (*(&plutout->ftva+i) == DBF_STRING)
		        strncpy ((char *) *(&plutout->vala+i),
			    p->val[i].sval, LUT_TAG_SZ);
		    else if (*(&plutout->ftva+i) == DBF_DOUBLE)
		        *(double *) *(&plutout->vala+i) = p->val[i].dval;
		    else if (*(&plutout->ftva+i) == DBF_LONG)
		        *(long *) *(&plutout->vala+i) = p->val[i].lval;
		}
	    }
	    /* set number of outputs */
	    plutout->nval = p->nval;
	    break;
	}
    }
					/* send values out via device support */
    status = (*pdset->write_lutout) (plutout);
					/* if async devSup then exit */
    if (!pact && plutout->pact)
	return 0;
					/* finish processing */
    plutout->pact = TRUE;

					/* time stamp */
    recGblGetTimeStamp (plutout);
					/* alarms */
    checkAlarms (plutout);
					/* monitors */
    monitor (plutout);
					/* forward link */
    recGblFwdLink (plutout);

    plutout->pact = FALSE;
    return status;
}


/*******************************************************************************
*/

static long special (
    struct dbAddr *paddr,
    int after)
{
    lutoutRecord *plutout = (lutoutRecord *) paddr->precord;

    if (!after)
	return 0;

    if (!plutout->load)
	return 0;

    plutout->load = 0;
    ellFree (plutout->ltbl);
    return (read_file (plutout));
}


/*******************************************************************************
*/

static long get_value( lutoutRecord *plutout, struct valueDes *pvdes )
{
    pvdes->field_type  = DBF_STRING;
    pvdes->no_elements = 1;
    pvdes->pvalue      = (void *) (&plutout->val[0]);
    return 0;
}


static long cvt_dbaddr( struct dbAddr *paddr )
{
    long         error;
    int          fieldIndex;
    lutoutRecord *plutout;

    plutout    = (lutoutRecord *)paddr->precord;
    error      = 0;
    fieldIndex = dbGetFieldIndex(paddr);
    switch( fieldIndex )
    {
      case lutoutRecordVALA:
        paddr->pfield     = plutout->vala;
        paddr->field_type = plutout->ftva;
        break;

      case lutoutRecordVALB:
        paddr->pfield     = plutout->valb;
        paddr->field_type = plutout->ftvb;
        break;

      case lutoutRecordVALC:
        paddr->pfield     = plutout->valc;
        paddr->field_type = plutout->ftvc;
        break;

      case lutoutRecordVALD:
        paddr->pfield     = plutout->vald;
        paddr->field_type = plutout->ftvd;
        break;

      case lutoutRecordOLDA:
        paddr->pfield     = plutout->olda;
        paddr->field_type = plutout->ftva;
        break;

      case lutoutRecordOLDB:
        paddr->pfield     = plutout->oldb;
        paddr->field_type = plutout->ftvb;
        break;

      case lutoutRecordOLDC:
        paddr->pfield     = plutout->oldc;
        paddr->field_type = plutout->ftvc;
        break;

      case lutoutRecordOLDD:
        paddr->pfield     = plutout->oldd;
        paddr->field_type = plutout->ftvd;
        break;

      default:
        error = 1;
        break;
    }

    if( !error )
    {
      paddr->no_elements    = 1;
      paddr->dbr_field_type = paddr->field_type;
      if(paddr->field_type == DBF_STRING)
	paddr->field_size = MAX_STRING_SIZE;
      else if(paddr->field_type == DBF_DOUBLE)
	paddr->field_size = sizeof(double);
      else if(paddr->field_type == DBF_LONG)
	paddr->field_size = sizeof(long);
    }

    return(error);
}


/*******************************************************************************
*/

static long get_enum_strs (
    struct dbAddr *paddr,
    struct dbr_enumStrs *pes)
{
    lutoutRecord *plutout = (lutoutRecord *) paddr->precord;
    LUT *p;

    pes->no_str = 0;
    memset (pes->strs, '\0', sizeof (pes->strs));
    for (p = (LUT *) ellFirst ((ELLLIST *)plutout->ltbl); p != NULL;
	p = (LUT *) ellNext ((ELLNODE *) p))
    {
	strncpy (pes->strs[pes->no_str++], p->tag, MAX_STRING_SIZE);
	if (pes->no_str >= DB_MAX_CHOICES)
	    break;
    }
    return 0;
}


/*******************************************************************************
*/

static long get_precision( struct dbAddr *paddr, long *precision )
{
  lutoutRecord *plutout = (lutoutRecord *)paddr->precord;
  int          fieldIndex;

  fieldIndex = dbGetFieldIndex(paddr);
  if( fieldIndex == lutoutRecordVERS )
  {
    *precision = 1;
    return 0;
  }

  *precision = plutout->prec;
  if(paddr->pfield == (void *) plutout->val)
    return 0;
  recGblGetPrec(paddr, precision);

  return 0;
}


/*******************************************************************************
*/

static void checkAlarms( lutoutRecord *plutout )
{
    if (plutout->nval == 0)
    {
	recGblSetSevr (plutout, SOFT_ALARM, INVALID_ALARM);
    }
}


/*******************************************************************************
*
* monitors are posted for changes in any of the following PVs:
*  VAL, NVAL, VALA, VALB, VALC, VALD
*/

static void monitor( lutoutRecord *plutout )
{
    double *pdval, *pdoval;
    long *pival, *pioval;
    unsigned short monitor_mask;
    int i;

    monitor_mask = recGblResetAlarms (plutout);
    monitor_mask |= DBE_VALUE|DBE_LOG;

    if (strncmp (plutout->val, plutout->oval, MAX_STRING_SIZE) != 0)
    {
	db_post_events (plutout, &plutout->val, monitor_mask);
	strncpy (plutout->oval, plutout->val, MAX_STRING_SIZE);
    }
    if (plutout->nval != plutout->onvl)
    {
	db_post_events (plutout, &plutout->nval, monitor_mask);
	plutout->onvl = plutout->nval;
    }

    for (i = 0; i < plutout->nval; i++)
    {
	if (plutout->selb & (1 << i))
	{
	    switch (*(&plutout->ftva+i))
	    {
	    case DBF_STRING:
		if (strncmp (*(&plutout->vala+i), *(&plutout->olda+i),
		    LUT_TAG_SZ) != 0)
		{
		    db_post_events (plutout, *(&plutout->vala+i), monitor_mask);
		    strncpy (*(&plutout->olda+i), *(&plutout->vala+i),
			LUT_TAG_SZ);
		}
		break;
	    case DBF_DOUBLE:
		pdval = (double *) *(&plutout->vala+i);
		pdoval = (double *) *(&plutout->olda+i);
		if (*pdval != *pdoval)
		{
		    db_post_events (plutout, pdval, monitor_mask);
		    *pdoval = *pdval;
		}
		break;
	    case DBF_LONG:
		pival = (long *) *(&plutout->vala+i);
		pioval = (long *) *(&plutout->olda+i);
		if (*pival != *pioval)
		{
		    db_post_events (plutout, pival, monitor_mask);
		    *pioval = *pival;
		}
		break;
	    }
	}
    }
}


/*******************************************************************************
* read_file
*
* Read the data base.
*/

static long read_file( lutoutRecord *plutout )
{
    FILE *fp;
    char buf[256], tag[LUT_TAG_SZ];
    LUT *p;
    long n, count, status;

    p = NULL;
    /* read data file from remote disk */
    plutout->ltbl = (void *) malloc (sizeof (ELLLIST));
    ellInit ((ELLLIST *) plutout->ltbl);

    if (!plutout->fdir || !plutout->fdir[0] ||
	!plutout->fnam || !plutout->fnam[0])
    {
	return 0;
    }

    sprintf (buf, "%s/%s", plutout->fdir, plutout->fnam);
    if (debugLevel > 0)
	    errlogPrintf("Reading %s\n", buf);
    if ((fp = fopen (buf, "r")) == NULL)
    {
	recGblRecordError (S_db_badField, (void *) plutout, "lutoutRecord: read_file FDIR | FNAM");
	return -1;
    }

    status = 0;
    count = -1;
    while (status == 0)
    {
	/* new entry */
	if (count == -1)
	{
	    /* skip blank lines and comments */
	    n = fscanf (fp, "%s", tag);
	    if (n == -1) { /* EOF */
		break;
	    }
	    else if (n == 0 || tag[0] == '#')
	    {
		(void) fgets (buf, sizeof (buf)-1, fp);
	    }
	    /* create new node, read tag and number of values */
	    else
	    {
		p = (LUT *) malloc (sizeof (LUT));
		ellAdd ((ELLLIST *) plutout->ltbl, (ELLNODE *) p);
		strncpy (p->tag, tag, LUT_TAG_SZ);
		if (fscanf (fp, "%ld", &p->nval) != 1)
		    status = -1;
		else if( p->nval )
		    count++;
	    }
	}
	/* add values in existing entry */
	else
	{
	    /* FTVx defined as a string */
	    if (*(&plutout->ftva+count) == DBF_STRING &&
		fscanf (fp, "%s%ld%ld", p->val[count].sval,
		    &p->tol_lo[count].lval, &p->tol_hi[count].lval) != 3)
	    {
		status = -1;
	    }
	    /* FTVx defined as a double */
	    else if (*(&plutout->ftva+count) == DBF_DOUBLE &&
		fscanf (fp, "%lf%lf%lf", &p->val[count].dval,
		    &p->tol_lo[count].dval, &p->tol_hi[count].dval) != 3)
	    {
		status = -1;
	    }
	    /* FTVx defined as a long */
	    else if (*(&plutout->ftva+count) == DBF_LONG &&
		fscanf (fp, "%ld%ld%ld", &p->val[count].lval,
		    &p->tol_lo[count].lval, &p->tol_hi[count].lval) != 3)
	    {
		status = -1;
	    }

	    count = ((count >= p->nval-1) ? -1 : count + 1);
	}
    }

    fclose (fp);

    return status;
}

static const iocshArg debugLevelArg = { "level", iocshArgInt };
static const iocshArg *setDebugLevelArgs[] = { &debugLevelArg };
static const iocshFuncDef setDebugLevelFuncDef = {"lutoutSetDebug", 1, setDebugLevelArgs};
static void setDebugLevelFunc(const iocshArgBuf *args) {
	int rawValue = args[0].ival;

	if ((rawValue >= 0) && (rawValue < 3))
		debugLevel = rawValue;
	else if (rawValue > 0)
		debugLevel = 2;
	else
		debugLevel = 0;
}

static void lutoutRegister(void) {
	iocshRegister(&setDebugLevelFuncDef, setDebugLevelFunc);
}

epicsExportRegistrar(lutoutRegister);
