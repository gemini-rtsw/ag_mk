/*
 *  FILENAME
 *  --------
 *  ag_pmac.c
 *
 *  PURPOSE
 *  -------
 *  This file contains all utility routines with direct hardware access
 *  to PMAC in the A&G unit (1st layer from the PMAC hardware).
 *
 *  The logic of the routines was mainly copied from the PMAC driver library
 *  in order to finally replace that.  
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth (ocf)
 *
 *  HISTORY
 *  -------
 *  25-Apr-1998:	Original version			(ocf)
 *
 */

/* ====================================================================	*/
/* =======   16 bits	===============================================	*/

long pmacRamGetHree ( volatile short * pDpram, long *pVal )
{  return *pVal = 0x0000ffff & (long) pDpram[0];	}

/* ====================================================================	*/

long pmacRamPutHree ( volatile short * pDpram, long val )
{  return pDpram[0] = (short) (0x0000ffff & val); 	}

/* ====================================================================	*/
/* =======   24 bits	===============================================	*/
/* problem: readings are not at same time point				*/

long pmacRamGetXree ( volatile short * pDpram, long *pVal )
{  
  return *pVal = ((0x000000ff & (long) pDpram[1]) << 16) | (0x0000ffff & (long) pDpram[0]);	
}

/* ====================================================================	*/

long pmacRamPutXree ( volatile short * pDpram, long val )
{
  pDpram[0] = (short)  (0x0000ffff & val);
  pDpram[1] = (short) ((0x00ff0000 & val) >> 16);
  return val;
}

/* ====================================================================	*/
/* =======   32 bits	===============================================	*/

long pmacRamGetDPree ( volatile short * pDpram, long * pVal)
{
  return *pVal = (((long) pDpram[1]) << 16) | (0x0000ffff & (long) pDpram[0]);	
}

/* ====================================================================	*/

long pmacRamPutDPree ( volatile short * pDpram, long val )
{
  pDpram[0] = (short)  (0x0000ffff & val);
  pDpram[1] = (short)  (             val >> 16);
  return val;
}

/* ====================================================================	*/

