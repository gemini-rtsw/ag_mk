/* devLutinSoft.c - Device Support Routines for Soft LUT Input */
/*
 *      Author:      Bret Goodrich
 *      Date:      12jul96
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 * Modification Log:
 * -----------------
 * 01a,23aug96,bdg  created
 * 01b,03sep96,bdg  changes to tolerance
 * 01c,12oct96,bdg  moved lookup to recSup, where it belongs
 *
 * History
 * -------
 * Version 1.0  16/10/97   ajf  Changes for 3.13.
 * Version 2.0  2016-08-03 mdw  Changes for R3.14/OSI
 *
*/


#include   <stdio.h>

#include   <alarm.h>
#include   <dbDefs.h>
#include   <dbAccess.h>
#include   <recSup.h>
#include   <devSup.h>
#include   <recGbl.h>
#include   <epicsExport.h>

#include   <lutinRecord.h>
#include   <lut.h>

static long   init_record (struct lutinRecord  *);
static long   read_lutin (struct lutinRecord  *);

struct {
   long      number;
   DEVSUPFUN   report;
   DEVSUPFUN   init;
   DEVSUPFUN   init_record;
   DEVSUPFUN   get_ioint_info;
   DEVSUPFUN   read_lutin;
} devLutinSoft =
{
   5,
   NULL,
   NULL,
   init_record,
   NULL,
   read_lutin
};
epicsExportAddress(dset, devLutinSoft);

/*******************************************************************************
*/

static long init_record( struct lutinRecord *plutin )
{
    int            i;
    long           status;
    struct link    *plink;
    void           **valptr;
    unsigned short *typptr;

    status = 0;
    plink  = &plutin->inpa;
    typptr = &plutin->ftva;
    valptr = &plutin->vala;
    for(i = 0; i < LUT_NUM_SZ; i++, plink++, typptr++, valptr++ )
    {
   /* lutin.inp must be a CONSTANT or a PV_LINK or a DB_LINK */
   switch (plink->type)
   {
     case CONSTANT:
            if( recGblInitConstantLink(plink, *typptr, *valptr) )
         plutin->udf = FALSE;
            break;

     case PV_LINK:
     case CA_LINK:
     case DB_LINK:
            break;

     default:
       recGblRecordError(S_db_badField, (void *)plutin,
      "devLutinSoft(init_record) Illegal INP field");
       status = S_db_badField;
       break;
   }
    }
    return(status);
}


/*******************************************************************************
*/

static long read_lutin( struct lutinRecord *plutin )
{
    long           status;
    long           nRequest;
    long           options;
    long           i;
    struct link    *plink;
    void           **valptr;
    unsigned short *typptr;

               /* get all input links */
    nRequest = 1;
    options  = 0;
    plink    = &plutin->inpa;
    valptr   = &plutin->vala;
    typptr   = &plutin->ftva;
    for( i=0; i<LUT_NUM_SZ; i++, plink++, valptr++, typptr++ )
    {
        status = dbGetLinkValue(plink, *typptr, *valptr, &options, &nRequest);
   if( status )
        {
          printf("Status %ld from dbGetLink (%ld)\n", status, i);
          break;
        }
    }
    return(status);
}
