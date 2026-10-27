/* devLutoutSoft.c - Device Support Routines for Soft Lutout Records */
/*
 *      Author:      Bret Goodrich
 *
 * Modification Log:
 * -----------------
 * 01a,18aug96,bdg  created
 * 01b,12oct96,bdg  moved lookup to record support where it belongs.
 *
 * History
 * -------
 * Version 1.0  16/10/97    ajf  Changes for 3.13.
 * Version 2.0  2016-08-03  mdw  Changes for R3.14/OSI.
 *
 */


#include   <alarm.h>
#include   <dbDefs.h>
#include   <dbAccess.h>
#include   <recSup.h>
#include   <devSup.h>
#include   <recGbl.h>
#include   <epicsExport.h>

#include   <lutoutRecord.h>
#include   <lut.h>

static long   init_record (struct lutoutRecord *);
static long   write_lutout (struct lutoutRecord *);

struct {
   long      number;
   DEVSUPFUN   report;
   DEVSUPFUN   init;
   DEVSUPFUN   init_record;
   DEVSUPFUN   get_ioint_info;
   DEVSUPFUN   write_lutout;
} devLutoutSoft =
{
   5,
   NULL,
   NULL,
   init_record,
   NULL,
   write_lutout
};
epicsExportAddress(dset, devLutoutSoft);


static long init_record( struct lutoutRecord *plutout )
{
  long status = 0;

  return(status);
}


static long write_lutout( struct lutoutRecord *plutout )
{
    long           i;
    long           nRequest;
    long           status;
    struct link    *plink;
    unsigned short *typptr;
    void           **valptr;

    nRequest = 1;
    plink    = &plutout->outa;
    valptr   = &plutout->vala;
    typptr   = &plutout->ftva;
    for( i=0; i<LUT_NUM_SZ; i++, plink++, valptr++, typptr++ )
      status = dbPutLink( plink, *typptr, *valptr, nRequest );

    return 0;
}
