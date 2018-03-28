/* mbbipRecord.c */
/* base/src/rec  mbbipRecord.c,v 1.7 1998/01/21 15:41:33 mrk Exp */
/*
 *      Original Author: Bob Dalesio
 *      Current Author:  Marty Kraimer
 *      Date:            5-9-88
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 * Modification Log:
 * -----------------
 * .01  12-12-88        lrd     lock the record while processing
 * .02  12-15-88        lrd     Process the forward scan link
 * .03  12-23-88        lrd     Alarm on locked MAX_LOCKED times
 * .04  01-13-89        lrd     delete db_read_mbbip
 * .05  03-29-89        lrd     make hardware errors MAJOR
 *                              remove hw severity spec from database
 * .06  04-07-89        lrd     add monitor detection
 * .07  05-03-89        lrd     removed process mask from arg list
 * .08  05-29-89        lrd     support 16 states
 * .09  05-30-89        lrd     fixed masks for allen-bradley IO
 * .10  06-06-89        lrd     fixed AB mbbip conversion - signal wrong
 *                              added ability to enter raw numbers if no
 *                              states are defined - like the mbbo
 * .11  12-06-89        lrd     add database fetch support
 * .12  02-08-90        lrd     add Allen-Bradley PLC support
 * .13  10-31-90	mrk	changes for new record and device support
 * .14  11-11-91        jba     Moved set and reset of alarm stat and sevr to macros
 * .15  02-05-92	jba	Changed function arguments from paddr to precord 
 * .16  02-28-92	jba	ANSI C changes
 * .17  04-10-92        jba     pact now used to test for asyn processing, not status
 * .18  04-18-92        jba     removed process from dev dev init_record parms
 * .19  07-15-92        jba     changed VALID_ALARM to INVALID alarm
 * .20  07-16-92        jba     added invalid alarm fwd link test and chngd fwd lnk to macro
 * .21  08-14-92        jba     Added simulation processing
 * .22  03-29-94        mcn     converted to fast links.
 */

#include	<epicsStdio.h>
#include	<ellLib.h>
#include	<string.h>
#include	<recGbl.h>

#include "dbDefs.h"
#include "epicsPrint.h"
#include	<alarm.h>
#include	<dbAccess.h>
#include	<dbEvent.h>
#include	<dbFldTypes.h>
#include	<devSup.h>
#include	<errMdef.h>
#include	<recSup.h>
#include	<special.h>
#define GEN_SIZE_OFFSET
#include	<mbbipRecord.h>
#undef  GEN_SIZE_OFFSET
/* Create RSET - Record Support Entry Table*/
#define report NULL
#define initialize NULL
static long init_record();
static long process();
static long  special();
#define get_value NULL
#define cvt_dbaddr NULL
#define get_array_info NULL
#define put_array_info NULL
#define get_units NULL
#define get_precision NULL
static long get_enum_str();
static long get_enum_strs();
static long put_enum_str();
#define get_graphic_double NULL
#define get_control_double NULL
#define get_alarm_double NULL
struct rset mbbipRSET={
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

struct mbbipdset { /* multi bit binary input dset */
	long		number;
	DEVSUPFUN	dev_report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record; /*returns: (-1,0)=>(failure,success)*/
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_mbbip;/*(0,2)=>(success, success no convert)*/
};
static void alarm();
static void monitor();
static long readValue();

static void init_common(pmbbip)
    struct mbbipRecord	*pmbbip;
{
        unsigned long 	*pstate_values;
	char		*pstate_string;
        short  		i;

        /* determine if any states are defined */
        pstate_values = &(pmbbip->zrvl); pstate_string = pmbbip->zrst;
        pmbbip->sdef = FALSE;
        for (i=0; i<16; i++, pstate_string += sizeof(pmbbip->zrst)) {
                if((*(pstate_values+i) != 0) || (*pstate_string !='\0')) {
			pmbbip->sdef = TRUE;
			return;
		}
	}
	return;
}

static long init_record(pmbbip,pass)
    struct mbbipRecord	*pmbbip;
    int pass;
{
    struct mbbipdset *pdset;
    long status;
    int i;

    if (pass==0) return(0);

    if (pmbbip->siml.type == CONSTANT) {
	recGblInitConstantLink(&pmbbip->siml,DBF_USHORT,&pmbbip->simm);
    }
    if (pmbbip->siol.type == CONSTANT) {
	recGblInitConstantLink(&pmbbip->siol,DBF_USHORT,&pmbbip->sval);
    }
    if(!(pdset = (struct mbbipdset *)(pmbbip->dset))) {
	recGblRecordError(S_dev_noDSET,(void *)pmbbip,"mbbip: init_record");
	return(S_dev_noDSET);
    }
    /* must have read_mbbip function defined */
    if( (pdset->number < 5) || (pdset->read_mbbip == NULL) ) {
	recGblRecordError(S_dev_missingSup,(void *)pmbbip,"mbbip: init_record");
	return(S_dev_missingSup);
    }
    /* initialize mask*/
    pmbbip->mask = 0;
    for (i=0; i<pmbbip->nobt; i++) {
	pmbbip->mask <<= 1; /* shift left 1 bit*/
	pmbbip->mask |= 1;  /* set low order bit*/
    }
    if( pdset->init_record ) {
	if((status=(*pdset->init_record)(pmbbip))) return(status);
    }
    init_common(pmbbip);
    return(0);
}

static long process(pmbbip)
        struct mbbipRecord     *pmbbip;
{
	struct mbbipdset	*pdset = (struct mbbipdset *)(pmbbip->dset);
	long		status;
	unsigned char    pact=pmbbip->pact;

	if( (pdset==NULL) || (pdset->read_mbbip==NULL) ) {
		pmbbip->pact=TRUE;
		recGblRecordError(S_dev_missingSup,(void *)pmbbip,"read_mbbip");
		return(S_dev_missingSup);
	}

	status=readValue(pmbbip); /* read the new value */
	/* check if device support set pact */
	if ( !pact && pmbbip->pact ) return(0);
	pmbbip->pact = TRUE;

	recGblGetTimeStamp(pmbbip);
	if(status==0) { /* convert the value */
        	unsigned long 	*pstate_values;
        	short  		i;
		unsigned long rval = pmbbip->rval;

		if(pmbbip->shft>0) rval >>= pmbbip->shft;
		if (pmbbip->sdef){
			pstate_values = &(pmbbip->zrvl);
			pmbbip->val = 65535;         /* initalize to unknown state*/
			pmbbip->udf = TRUE;
			for (i = 0; i < 16; i++){
				if (*pstate_values == rval){
                               		pmbbip->val = i;
                               		pmbbip->udf = FALSE;
                               		break;
			    	}
			    	pstate_values++;
			}
		}else{
			/* the raw value is the desired value */
			pmbbip->val =  (unsigned short)rval;
			pmbbip->udf =  FALSE;
		}
	}
	else if(status == 2) status = 0;

	/* check for alarms */
	alarm(pmbbip);

	/* check event list */
	monitor(pmbbip);

	/* process the forward scan link record */
	recGblFwdLink(pmbbip);

	pmbbip->pact=FALSE;
	return(status);
}


static long special(paddr,after)
    struct dbAddr *paddr;
    int           after;
{
    struct mbbipRecord     *pmbbip = (struct mbbipRecord *)(paddr->precord);
    int                 special_type = paddr->special;

    if(!after) return(0);
    switch(special_type) {
    case(SPC_MOD):
	init_common(pmbbip);
	return(0);
    default:
        recGblDbaddrError(S_db_badChoice,paddr,"mbbip: special");
        return(S_db_badChoice);
    }
}

static long get_enum_str(paddr,pstring)
    struct dbAddr *paddr;
    char	  *pstring;
{
    struct mbbipRecord	*pmbbip=(struct mbbipRecord *)paddr->precord;
    char		*psource;
    int                 index;
    unsigned short      *pfield = (unsigned short *)paddr->pfield;
    unsigned short	val=*pfield;

    index = dbGetFieldIndex(paddr);
    if(index!=mbbipRecordVAL) {
	strcpy(pstring,"Illegal_Value");
    } else if(val<= 15) {
	psource = (pmbbip->zrst);
	psource += (val * sizeof(pmbbip->zrst));
	strncpy(pstring,psource,sizeof(pmbbip->zrst));
    } else {
	strcpy(pstring,"Illegal Value");
    }
    return(0);
}

static long get_enum_strs(paddr,pes)
    struct dbAddr *paddr;
    struct dbr_enumStrs *pes;
{
    struct mbbipRecord	*pmbbip=(struct mbbipRecord *)paddr->precord;
    char		*psource;
    int			i;
    short		no_str;

    no_str = 0;
    memset(pes->strs,'\0',sizeof(pes->strs));
    for(i=0,psource=(pmbbip->zrst); i<16; i++, psource += sizeof(pmbbip->zrst) ) {
	strncpy(pes->strs[i],psource,sizeof(pmbbip->zrst));
	if(*psource!=0) no_str=i+1;
    }
    pes->no_str=no_str;
    return(0);
}

static long put_enum_str(paddr,pstring)
    struct dbAddr *paddr;
    char          *pstring;
{
    struct mbbipRecord     *pmbbip=(struct mbbipRecord *)paddr->precord;
        char              *pstate_name;
        short             i;

        if (pmbbip->sdef){
                pstate_name = pmbbip->zrst;
                for (i = 0; i < 16; i++){
                        if(strncmp(pstate_name,pstring,sizeof(pmbbip->zrst))==0){
        			pmbbip->val = i;
					pmbbip->udf =  FALSE;
                                return(0);
                        }
                	pstate_name += sizeof(pmbbip->zrst);
                }
        }
	return(S_db_badChoice);
}

static void alarm(pmbbip)
    struct mbbipRecord	*pmbbip;
{
	unsigned short *severities;
	unsigned short	val=pmbbip->val;

        /* check for udf alarm */
        if(pmbbip->udf == TRUE ){
                recGblSetSevr(pmbbip,UDF_ALARM,INVALID_ALARM);
        }

        /* check for  state alarm */
        /* unknown state */
        if (val > 15){
                recGblSetSevr(pmbbip,STATE_ALARM,pmbbip->unsv);
        } else {
        	/* in a state which is an error */
        	severities = (unsigned short *)&(pmbbip->zrsv);
                recGblSetSevr(pmbbip,STATE_ALARM,severities[pmbbip->val]);
	}

        /* check for cos alarm */
	if(val == pmbbip->lalm) return;
        recGblSetSevr(pmbbip,COS_ALARM,pmbbip->cosv);
	pmbbip->lalm = val;
	return;
}

static void monitor(pmbbip)
    struct mbbipRecord	*pmbbip;
{
	unsigned short	monitor_mask;

        monitor_mask = recGblResetAlarms(pmbbip);
        /* check for value change */
        if (pmbbip->mlst != pmbbip->val){
                /* post events for value change and archive change */
                monitor_mask |= (DBE_VALUE | DBE_LOG);
                /* update last value monitored */
                pmbbip->mlst = pmbbip->val;
        }
        /* send out monitors connected to the value field */
        if (monitor_mask){
                db_post_events(pmbbip,&pmbbip->val,monitor_mask);
	}
        if(pmbbip->oraw!=pmbbip->rval) {
                db_post_events(pmbbip,&pmbbip->rval,monitor_mask|DBE_VALUE);
                pmbbip->oraw = pmbbip->rval;
        }
        return;
}

static long readValue(pmbbip)
	struct mbbipRecord	*pmbbip;
{
	long		status;
        struct mbbipdset 	*pdset = (struct mbbipdset *) (pmbbip->dset);

	if (pmbbip->pact == TRUE){
		status=(*pdset->read_mbbip)(pmbbip);
		return(status);
	}

	status=dbGetLink(&(pmbbip->siml),DBR_USHORT,&(pmbbip->simm),0,0);
	if (status)
		return(status);

	/* TODO: FIX THIS. WHAT IS 'NO' AND WHAT IS 'YES'? */
	/*
	if (pmbbip->simm == NO){
		status=(*pdset->read_mbbip)(pmbbip);
		return(status);
	}
	if (pmbbip->simm == YES){
		status=dbGetLink(&(pmbbip->siol),DBR_USHORT,&(pmbbip->sval),0,0);
		if (status==0){
			pmbbip->val=pmbbip->sval;
			pmbbip->udf=FALSE;
		}
                status=2; // dont convert
	} else {
		status=-1;
		recGblSetSevr(pmbbip,SOFT_ALARM,INVALID_ALARM);
		return(status);
	}
	*/
        recGblSetSevr(pmbbip,SIMM_ALARM,pmbbip->sims);

	return(status);
}
