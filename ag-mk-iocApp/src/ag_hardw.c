/*
 *  FILENAME
 *  --------
 *  ag_hardw.c
 *
 *  PURPOSE
 *  -------
 *  This file contains all utility routines with almost direct hardware access
 *  (to PMAC or XYCOM) in the A&G unit. (2nd layer from the PMAC hardware.)
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *
 *  setXYCOM  - set and read XYCOM digital I/O card
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth (ocf)
 *
 *  HISTORY
 *  -------
 *  25-Apr-1998:   Original version                       (ocf)
 *  02-Aug-2000:   Check for presence of XYCOM card       (cjm)
 *
 */

#include  <ag_define.h>		/* names for mechanisms */

/*==========================================================================*/

/* ======================================================================== */
  #define motad(mot)		(FGDatBuff + FGMotOfs*(mot-1))
  #define mota2(mot)		(BGDatBuff + BGMotOfs*(mot-1))
  #define CNTFAC		3072                             /* (32*96) */
/* ======================================================================== */

long getDPvals (int motor, int card, long *lval, double *dval1,
                double *dval2, double *dval3)
{
  #if 0
  *lval  = ((getXY (motad(motor)+StatWor1,    card, 0) >> 8) & 0xffff) |	/* 24/hi16->32/lo16 */
  	   ((getXY (mota2(motor)+StatWor2,    card, 0) &  0xffff) << 16);	/* 24/lo16->32/hi16 */
  #endif

  pmacRamGetX (pmac2hostaddr (card, motad(motor)+StatWor1, 0), (long*)dval1);
  pmacRamGetX (pmac2hostaddr (card, mota2(motor)+StatWor2, 0), (long*)dval2);
  *lval  = ((*(long*)dval1 >> 8) & 0xffff) | ((*(long*)dval2 &  0xffff) << 16 );

  getDPRamD2 (motad(motor)+ActPos,  card, 0, dval1);
  getDPRamD2 (motad(motor)+CommPos, card, 0, dval2);
  getDPRamD2 (mota2(motor)+TargPos, card, 0, dval3);

  return (0);
}
  #undef motad
  #undef mota2
  #undef CNTFAC

/* ==================================================================== */
/* ==================================================================== */

#define CNTFAC		3072					/* (32*96) */
#define HIBITS		5461.3333333333333

/* statt 2: sizeof(short)	*/

#define trans64(addr) ( ( (double)  (							\
			( (  0xff & (long) *(short*)(addr+1*2)) << 16)  | 		\
			  (0xffff & (long) *(short*)(addr+0*2))      )	) / CNTFAC  + 	\
			( (double)  (							\
			( (         (long) *(short*)(addr+3*2)) << 16)  | 		\
			  (0xffff & (long) *(short*)(addr+2*2))      )	) * HIBITS  ) 	

/* ===================================================================== */
/* 48 Bit fixed 
 * This version doesn't have the poblem with 32 bit overflow any more.
 * Val = LSW / 3072 + MSW * 16Mio/3072 	
 * 5461.3333333333333 = 16777216.0 / CNTFAC			
 */
#if 0
void getDPRamD2 (long pmacaddr, short card, short offset, double *Val)
{
  *Val = *(double*) pmac2hostaddr (card, pmacaddr, offset);	/* 64 bits*/
  *Val = trans64((byte*)Val);	
}
/* ==================================================================== */
void getDPRamD2raw (long adr, double *Val)
{
  *Val = *(double*) adr;			/* 64 bits		*/
  *Val = trans64((byte*)Val);	
}
#endif

void getDPRamD2 (long pmacaddr, short card, short offset, double *Val)
{
  pmacRamGetD ((PMAC_DPRAM *) pmac2hostaddr (card, pmacaddr, offset), Val);
  *Val/=CNTFAC;
}
/* ==================================================================== */
void getDPRamD2raw (long adr, double *Val)
{
  pmacRamGetD ((PMAC_DPRAM *)adr, Val);
  *Val/=CNTFAC;
}

/* ==================================================================== */
/* ==================================================================== */

/*+
 *   Function name:
 *   setXYCOM
 *
 *   Purpose:
 *   Read and set the xycom card to interact with the GIS
 *
 *   Description:
 *   This routine reads the current GIS demand from port 6 and sets any 
 *   events on port 7. 
 *
 *   Invocation:
 *   setXYCOM()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   None
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   This routine completely bypasses EPICS. Standard EPICS mbbi
 *   and mbbo records should be used instead.
 *
 *-
 */

long setXYCOM (void)
{
  byte inport, outport;
  static int first = 1 ;
  char dummy ;

  outport = 	(gis_event == GIS_ON)	? GIS_SET : GIS_CLEAR;

  if (devReadProbe (sizeof(char), (void *)xycomBase, &dummy) != OK) {
    if (first) {
      printf ("*** WARNING: Failed to detect XYCOM card ***\n") ;
      first = 0 ;
    }
    inport = GIS_CLEAR ;

  } else {

    portDirRegAddr = 0x80;		/* port 7: Output	*/
    inport = port6addr & GIS_MASK;
    port7addr = (8	  & (~GIS_MASK)) | outport;	/* set bits to 1 */
  }

  gis_demand_hw = inport;			/* store bits, not meaning*/

  gis_demand =	(inport == GIS_CLEAR)	? GIS_OFF : 
		(inport == GIS_SET) 	? GIS_ON  : GIS_UNDEFINED;


  return (0);
}

/* ==================================================================== */
/* ==================================================================== */
