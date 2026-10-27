/* lutinRecord.c - record support for Lookup Table
 *
 *	Author: Bret Goodrich
 *
 *	History
 *	-------
 *	Version 1.0  25/07/96  bdg  Created.
 *	Version 1.1  12/10/96  bdg  Fixed allocation problem for old[a-d].
 *	Version 1.2  15/03/01  ajf  Changes for 3.13.
 *                                  Set precision for VERS field to 1.
 *      Version 1.3  05/07/04  ajf  Changes for 3.14.
 *
 */

#define VERSION 1.3

#include	<stdlib.h>
#include        <stdio.h>
#include        <math.h>
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
#include        <lutinRecord.h>
#undef  GEN_SIZE_OFFSET

#include <epicsExport.h>
#include <iocsh.h>
#include <errlog.h>


static int debugLevel = 0;

/* Create RSET - Record Support Entry Table*/
 
static long init_record();
static long process();
static long get_enum_strs();
static long cvt_dbaddr();
static long special();
static long get_precision();
#define	get_value           NULL
#define get_enum_str	    NULL
#define put_enum_str	    NULL
#define report		    NULL
#define initialize	    NULL
#define get_units	    NULL
#define get_array_info	    NULL
#define put_array_info	    NULL
#define get_graphic_double  NULL
#define get_control_double  NULL
#define get_alarm_double    NULL
 
rset lutinRSET =
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
epicsExportAddress(rset,lutinRSET);


struct lutindset
{
    long	number;
    DEVSUPFUN	dev_report;
    DEVSUPFUN	init;
    DEVSUPFUN	init_record;
    DEVSUPFUN	get_ioint_info;
    DEVSUPFUN	read_lutin;
};

static void	checkAlarms (lutinRecord *);
static void	monitor (lutinRecord *);
static long	read_file (lutinRecord *);


/*******************************************************************************
*/

static long init_record( lutinRecord *plutin, int pass )
{
    int i;
    long status;
    struct lutindset *pdset;

    if (pass == 0)
    {
        plutin->vers = VERSION;
	if (read_file (plutin))
	    return -1;

	/* alloc space for inputs */
	for (i = 0; i < LUT_NUM_SZ; i++)
	{
	    switch (*(&plutin->ftva+i))
	    {
		case DBF_STRING:
		    *(&plutin->vala+i) = (void *) calloc (1, MAX_STRING_SIZE);
		    *(&plutin->olda+i) = (void *) calloc (1, MAX_STRING_SIZE);
		    break;
		case DBF_DOUBLE:
		    *(&plutin->vala+i) = (void *) calloc (1, sizeof (double));
		    *(&plutin->olda+i) = (void *) calloc (1, sizeof (double));
		    break;
		case DBF_LONG:
		    *(&plutin->vala+i) = (void *) calloc (1, sizeof (long));
		    *(&plutin->olda+i) = (void *) calloc (1, sizeof (long));
		    break;
		default:
		    recGblRecordError (S_db_badChoice, (void *) plutin,
			"lutinRecord: init_record FTVx");
		    return S_db_badChoice;
	    }
	}
    }
    else if (pass == 1)
    {
	if ((pdset = (struct lutindset *) (plutin->dset)) == NULL)
	{
	    recGblRecordError (S_dev_noDSET,(void *) plutin,
		"lutinRecord: init_record");
	    return S_dev_noDSET;
	}
	if (pdset->number < 5 || pdset->read_lutin == NULL)
	{
	    recGblRecordError (S_dev_missingSup, (void *) plutin,
		"lutinRecord: init_record");
	    return S_dev_missingSup;
	}
	/* initialize input values */
	if (pdset->init_record)
	{
	    if ((status = (*pdset->init_record) (plutin)))
		return status;
	}
    }

    return 0;
}


/*******************************************************************************
*/

static long process( lutinRecord *plutin )
{
    struct lutindset *pdset = (struct lutindset *) (plutin->dset);
    long i, status;
    unsigned long pact = plutin->pact;
    LUT *p;
    char *psval;
    double *pdval;
    long *plval;

					/* if bad devSup, set PACT and exit */
    if (pdset == NULL || pdset->read_lutin == NULL)
    {
	plutin->pact = TRUE;
	recGblRecordError (S_dev_missingSup, (void *) plutin,
	    "lutinRecord: read_lutin");
	return S_dev_missingSup;
    }
					/* read inputs from devSup */
    status = (*pdset->read_lutin) (plutin);
					/* if async devSup then exit */
    if (!pact && plutin->pact)
	return 0;
					/* finish processing */
    plutin->pact = TRUE;

    plutin->val[0] = '\0';
					/* find closest match in table */
    for (p = (LUT *) ellFirst ((ELLLIST *)plutin->ltbl); p != NULL;
	p = (LUT *) ellNext ((ELLNODE *) p))
    {
	for (i = 0; i < p->nval; i++)
	{
	    if (plutin->selb & (1 << i))
	    {
	        if (*(&plutin->ftva+i) == DBF_STRING)
	        {
		    psval = (char *) *(&plutin->vala+i);
		    if (strncmp (psval, p->val[i].sval, LUT_TAG_SZ) != 0)
		        break;
	        }
	        else if (*(&plutin->ftva+i) == DBF_DOUBLE)
	        {
		    pdval = (double *) *(&plutin->vala+i);
		    /* if value out of tolerance, this isn't the right set */
		    if (*pdval < p->val[i].dval - fabs (p->tol_lo[i].dval) ||
		        *pdval > p->val[i].dval + p->tol_hi[i].dval)
		        break;
	        }
	        else if (*(&plutin->ftva+i) == DBF_LONG)
	        {
		    plval = (long *) *(&plutin->vala+i);
		    /* if value out of tolerance, this isn't the right set */
		    if (*plval < p->val[i].lval - abs (p->tol_lo[i].lval) ||
		        *plval > p->val[i].lval + p->tol_hi[i].lval)
		        break;
	        }
	    }
	}
	if (i == p->nval)
	{
	    strncpy (plutin->val, p->tag, LUT_TAG_SZ);
	    break;
	}
    }
					/* time stamp */
    recGblGetTimeStamp (plutin);
					/* alarms */
    checkAlarms (plutin);
					/* monitors */
    monitor (plutin);
					/* forward link */
    recGblFwdLink (plutin);

    plutin->pact = FALSE;
    return status;
}


/*******************************************************************************
*/

static long special (
    struct dbAddr *paddr,
    int after)
{
    lutinRecord *plutin = (lutinRecord *) paddr->precord;
 
    if (!after)
	return 0;

    if (!plutin->load)
	return 0;

    plutin->load = 0;
    ellFree (plutin->ltbl);
    return (read_file (plutin));
}


/*******************************************************************************
*/

static long cvt_dbaddr( struct dbAddr *paddr )
{
    long        error;
    int         fieldIndex;
    lutinRecord *plutin;

    plutin     = (lutinRecord *)paddr->precord;
    error      = 0;
    fieldIndex = dbGetFieldIndex(paddr);
    switch( fieldIndex )
    {
      case lutinRecordVALA:
        paddr->pfield     = plutin->vala;
	paddr->field_type = plutin->ftva;
        break;

      case lutinRecordVALB:
        paddr->pfield     = plutin->valb;
	paddr->field_type = plutin->ftvb;
        break;

      case lutinRecordVALC:
        paddr->pfield     = plutin->valc;
	paddr->field_type = plutin->ftvc;
        break;

      case lutinRecordVALD:
        paddr->pfield     = plutin->vald;
	paddr->field_type = plutin->ftvd;
        break;

      case lutinRecordOLDA:
        paddr->pfield     = plutin->olda;
	paddr->field_type = plutin->ftva;
        break;

      case lutinRecordOLDB:
        paddr->pfield     = plutin->oldb;
	paddr->field_type = plutin->ftvb;
        break;

      case lutinRecordOLDC:
        paddr->pfield     = plutin->oldc;
	paddr->field_type = plutin->ftvc;
        break;

      case lutinRecordOLDD:
        paddr->pfield     = plutin->oldd;
	paddr->field_type = plutin->ftvd;
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
    lutinRecord *plutin = (lutinRecord *) paddr->precord;
    LUT *p;

    pes->no_str = 0;
    memset (pes->strs, '\0', sizeof (pes->strs));
    for (p = (LUT *) ellFirst ((ELLLIST *)plutin->ltbl); p != NULL;
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

static long get_precision(struct dbAddr *paddr, long *precision)
{
  lutinRecord *plutin = (lutinRecord *)paddr->precord;
  int         fieldIndex;
 
  fieldIndex = dbGetFieldIndex(paddr);
  if( fieldIndex == lutinRecordVERS )
  {
    *precision = 1;
    return 0;
  }

  *precision = plutin->prec;
  if(paddr->pfield == (void *)plutin->val)
    return 0;
  recGblGetPrec (paddr, precision);
  return 0;
}


/*******************************************************************************
*/

static void checkAlarms( lutinRecord *plutin )
{
    if (plutin->val[0] == '\0')
    {
	strncpy (plutin->val, "INVALID", LUT_TAG_SZ);
	recGblSetSevr (plutin, SOFT_ALARM, INVALID_ALARM);
    }
}


/*******************************************************************************
* monitors are posted for changes in any of the following PVs:
*  VAL, NVAL, VALA, VALB, VALC, VALD
*/

static void monitor( lutinRecord *plutin )
{
    double *pdval, *pdoval;
    long *pival, *pioval;
    unsigned short monitor_mask;
    int i;

    monitor_mask = recGblResetAlarms (plutin);
    monitor_mask |= DBE_VALUE|DBE_LOG;

    if (strncmp (plutin->val, plutin->oval, MAX_STRING_SIZE) != 0)
    {
	db_post_events (plutin, &plutin->val, monitor_mask);
	strncpy (plutin->oval, plutin->val, MAX_STRING_SIZE);
    }
    if (plutin->nval != plutin->onvl)
    {
	db_post_events (plutin, &plutin->nval, monitor_mask);
	plutin->onvl = plutin->nval;
    }

    for (i = 0; i < plutin->nval; i++)
    {
	if (plutin->selb & (1 << i))
	{
	    switch (*(&plutin->ftva+i))
	    {
	    case DBF_STRING:
		if (strncmp (*(&plutin->vala+i), *(&plutin->olda+i),
		    LUT_TAG_SZ) != 0)
		{
		    db_post_events (plutin, *(&plutin->vala+i), monitor_mask);
		    strncpy (*(&plutin->olda+i), *(&plutin->vala+i),
			LUT_TAG_SZ);
		}
		break;
	    case DBF_DOUBLE:
		pdval = (double *) *(&plutin->vala+i);
		pdoval = (double *) *(&plutin->olda+i);
		if (*pdval != *pdoval)
		{
		    db_post_events (plutin, pdval, monitor_mask);
		    *pdoval = *pdval;
		}
		break;
	    case DBF_LONG:
		pival = (long *) *(&plutin->vala+i);
		pioval = (long *) *(&plutin->olda+i);
		if (*pival != *pioval)
		{
		    db_post_events (plutin, pival, monitor_mask);
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
* Read the data file from the remote disk.  The method need to be improved.
*/

static long read_file( lutinRecord *plutin )
{
    FILE *fp;
    char buf[256], tag[LUT_TAG_SZ];
    LUT *p;
    long n, count, status;

    p = NULL;
    plutin->ltbl = (void *) malloc (sizeof (ELLLIST));
    ellInit ((ELLLIST *) plutin->ltbl);

    if (!plutin->fdir || !plutin->fdir[0] ||
	!plutin->fnam || !plutin->fnam[0])
    {
	return 0;
    }

    sprintf (buf, "%s/%s", plutin->fdir, plutin->fnam);
    if (debugLevel > 0)
	    errlogPrintf("Reading %s\n", buf);
    if ((fp = fopen (buf, "r")) == NULL)
    {
	recGblRecordError (S_db_badField, (void *) plutin, "lutinRecord: read_file FDIR | FNAM");
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
	    /* EOF */
	    if (n == -1) {
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
		ellAdd ((ELLLIST *) plutin->ltbl, (ELLNODE *) p);
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
	    if (*(&plutin->ftva+count) == DBF_STRING &&
		fscanf (fp, "%s%ld%ld", p->val[count].sval,
		    &p->tol_lo[count].lval, &p->tol_hi[count].lval) != 3)
	    {
		status = -1;
	    }
	    /* FTVx defined as a double */
	    else if (*(&plutin->ftva+count) == DBF_DOUBLE &&
		fscanf (fp, "%lf%lf%lf", &p->val[count].dval,
		    &p->tol_lo[count].dval, &p->tol_hi[count].dval) != 3)
	    {
		status = -1;
	    }
	    /* FTVx defined as a long */
	    else if (*(&plutin->ftva+count) == DBF_LONG &&
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
static const iocshFuncDef setDebugLevelFuncDef = {"lutinSetDebug", 1, setDebugLevelArgs};
static void setDebugLevelFunc(const iocshArgBuf *args) {
	int rawValue = args[0].ival;

	if ((rawValue >= 0) && (rawValue < 3))
		debugLevel = rawValue;
	else if (rawValue > 0)
		debugLevel = 2;
	else
		debugLevel = 0;
}

static void lutinRegister(void) {
	iocshRegister(&setDebugLevelFuncDef, setDebugLevelFunc);
}

epicsExportRegistrar(lutinRegister);
