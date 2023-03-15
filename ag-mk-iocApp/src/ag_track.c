/*
 *  FILENAME
 *  --------
 *  ag_track.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all gensub functions used
 *  in the A&G unit for tracking mode
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  followA
 *  interpol
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth (ocf)
 *  Karsten Ottow (ko)
 *
 *  HISTORY
 *  -------
 *  24-June-1997: Original version 			(ocf)
 *  25-Dec-97:	complete renewed			(ocf)
 */

#include <float.h>
#include <math.h>
#include  <ag_define.h>
#include  "agSimulate.h"

/* ====================================================================	*/

  #define X1 		(*(double *)pgsub->a)		/* oldest */
  #define Y1  		(*(double *)pgsub->b)
  #define Z1 		(*(double *)pgsub->c)
  #define T1 		0

  #define X2  		(*(double *)pgsub->d)
  #define Y2  		(*(double *)pgsub->e)
  #define Z2  		(*(double *)pgsub->f)
  #define T2  		(*(double *)pgsub->k)

  #define X3  		(*(double *)pgsub->g)		/* newest */
  #define Y3  		(*(double *)pgsub->h)
  #define Z3  		(*(double *)pgsub->i)
  #define T3  		(*(double *)pgsub->l)

  #define TADV    	(*(double *)pgsub->m)		/* Time-in-advance for generated demand */
  #define TRACKID 	(*(double *)pgsub->o)		/* new TRACKID */

  #define XOUT		(*(double *)pgsub->vala)
  #define YOUT		(*(double *)pgsub->valb)
  #define ZOUT		(*(double *)pgsub->valc)

  #define T		(*(double *)pgsub->vale)
  #define T0		(*(double *)pgsub->valh)
  #define TSENT		(*(double *)pgsub->valg)
  #define TRACKID_OUT	(*(double *)pgsub->valf)
  #define TRACKID_OLD	(*(double *)pgsub->vali)
  #define DEMANDCOUNT	(*(long   *)pgsub->vald)
  #define T_ABS		(*(double *)pgsub->vall)	/* absolute time	*/

  #define A		((double *)pgsub->valk)[0] 	/* coefficients 	*/
  #define B 		((double *)pgsub->valk)[1]
  #define C 		((double *)pgsub->valk)[2]
  #define D 		((double *)pgsub->valk)[3]
  #define E 		((double *)pgsub->valk)[4]
  #define F 		((double *)pgsub->valk)[5]
  #define G 		((double *)pgsub->valk)[6]
  #define H 		((double *)pgsub->valk)[7]
  #define I 		((double *)pgsub->valk)[8]
  #define DENOM 	((double *)pgsub->valk)[9]

/* it seems to be imposs. to use longs for doubles here
*  (Cannot be fed by capf. macros ?)
*/
  #define P1P2MARK	((long)*(double*)pgsub->n)	
  #define OUT		((double *)pgsub->valj)		/* array	*/
  #define NOUTVAL	(pgsub->novj)

/* ====================================================================	*/

/* vala: current x
 * valb: current y
 * valc: current z
 * vald: number of demand since start
 * vale: time of new demand
 * valf: track-ID
 * valg: time of calculation (TSENT)
 * valh: t0	(Start time of track)
 * vali: TRACKID_OLD
 * valj: Array with 1 new demand for p1/p2: follow gensub
 * valk: 9+1 coefficients
 * vall: T_ABS, absolute time
 *
 * scan: scanspeed (enum)	- normally passive
 * a/b/c: Start-X/Y/Z
 * d/e/f: Mid  -X/Y/Z
 * g/h/i: End  -X/Y/Z
 * j:	  should be left free (the only PP input)
 * k/l:   Mid/End Time
 * m:	  Time-in-advance for generated demand
 * n:	  Mark=1 for PWFS1, =2 for PWFS2
 * o:	  track-ID: if changed: start a new track!
 */

/* ===================================================================== */

long DemandSimu( struct genSubRecord *pgsub )
{
  long error;
  int  mechindex; 			
  char messages[380];					/* Message buffer */

  mechindex = (P1P2MARK == 1) ? p1_probe : p2_probe;
  if (pgsub->scan<=SCAN1s)
    if (P1P2MARK !=1 && P1P2MARK !=2)
    { sprintf( messages, "\t%s\t- Error: pwfs mark is %ld ", pgsub->name,
      P1P2MARK); 
      agprintf ("%s\n", messages);
    }

  error = get_tai(&T);	 /* t = T_ABS += 0.05;	*/
 						/* time simulated */
  if ( error<0 )
  { if (pgsub->scan<=SCAN1s)			/* >= 1 sec. scan */
    { sprintf( messages, "\t%s\t- Error %ld from get_tai, t=%16.12g",
      pgsub->name, error, T); 
      agprintf ("%s\n", messages);
      /* agLogMessage( mechindex, DEB_FULL, messages); */
    }						/* t is valid anyway */
  }

  if ((TRACKID > 0) && (TRACKID != TRACKID_OLD)) 
  {
    sprintf( messages, "\t%s\t- new track %ld -> %ld", 
	     pgsub->name, (long)TRACKID_OLD, (long)TRACKID); 
    agLogMessage( mechindex, DEB_FULL, messages);

    T0 		= T;			/* hold start time of track 	*/
    TRACKID_OLD = TRACKID;
    TRACKID_OUT = TRACKID;
    DEMANDCOUNT = 0;
  }

  T -= T0;				/* normalize time */

  if (T > (T3+T3-T2))  {T0+=T; T=0;}	/* start loop from begin	*/
  if (T >  T3)				/* back to the start in T3-T2	*/
  {
    A =  0;						/* Accel. 	*/
    D =  0;
    G =  0;
 
    B = (X1-X3) / (T3-T2);				/* Veloc. 	*/
    E = (Y1-Y3) / (T3-T2);
    H = (Z1-Z3) / (T3-T2);

    C =  X3 - B * T3;					/* Offset 	*/
    F =  Y3 - E * T3;
    I =  Z3 - H * T3;
  }
  else				/* not yet in loop back		*/
  {				
    DENOM = T2*T3*(T3-T2);	/* Coefficients for the 3 demands */

    if (DENOM > 1e-9)		/* against div-by-0: T2,T3,delta > 1ms	*/	
    { 				/* 	1e12:	     T2,T3,delta <10000s*/
      A = (X1*T3    - X1*T2    - X2*T3    + X3*T2)    / DENOM;	/* Accel. */
      D = (Y1*T3    - Y1*T2    - Y2*T3    + Y3*T2)    / DENOM;
      G = (Z1*T3    - Z1*T2    - Z2*T3    + Z3*T2)    / DENOM;
 
      B = (X1*T2*T2 - X1*T3*T3 + X2*T3*T3 - X3*T2*T2) / DENOM;	/* Veloc. */
      E = (Y1*T2*T2 - Y1*T3*T3 + Y2*T3*T3 - Y3*T2*T2) / DENOM;
      H = (Z1*T2*T2 - Z1*T3*T3 + Z2*T3*T3 - Z3*T2*T2) / DENOM;

      C =  X1;							/* Offset */
      F =  Y1;
      I =  Z1;
    }
    else
    {							/* Error	*/
      if (pgsub->scan<=SCAN1s)				/* >= 1sec scan ? */
      { sprintf(messages, 
        "\t%s\t- cannot calculate coeffs, T2=%16.12g, T3=%16.12g",
        pgsub->name, T2, T3) ;
        agLogMessage( mechindex, DEB_FULL, messages);
      }
    }
  }

  TSENT = T;					/* valg: time of calculation */
  T    += TADV;					/* calc. apply time 	*/
  XOUT 	= A *T*T + B *T + C;			/* real world coord.	*/
  YOUT 	= D *T*T + E *T + F;
  ZOUT 	= G *T*T + H *T + I;


  if (NOUTVAL == 6)
  {
    OUT[0] = TSENT + T0;			/* TSENT	*/
    OUT[1] = T     + T0;			/* tAppl	*/
    OUT[2] = TRACKID;				/* track-ID	*/
    OUT[3] = XOUT;				/* valj: Array with 1 demand */
    OUT[4] = YOUT;
    OUT[5] = ZOUT;
  }

  DEMANDCOUNT++;

  #if 0
    if (pgsub->scan<=SCAN1s)			/* >= 1 sec. scan 	*/
    {
      sprintf( messages, "Dem: A=%10.4g, B=%10.4g, C=%10.4g, D=%10.4g, E=%10.4g, F=%10.4g, G=%10.4g, H=%10.4g, I=%10.4g, x =%10.4g, y =%10.4g, z =%10.4g, t =%10.4g, TSENT=%16.12g, tAppl=%16.12g, DENOM=%8.4g", 
	A, B, C, D, E, F, G, H, I,  x, y, z, t-TADV, t-TADV+t0, t+t0, DENOM); 
      agprintf ("%s\n", messages);

/*      sprintf( messages, "Dem: A=%10.4g, B=%10.4g, C=%10.4g, x =%10.4g, y =%10.4g, z =%10.4g, t =%10.4g, TSENT=%16.12g, tAppl=%16.12g", A, B, C, x, y, z, t-TADV, t-TADV+t0, t+t0); 	*/
      /* agLogMessage( mechindex, DEB_FULL, messages);	*/
      /* agprintf ("%s\n", messages);	*/
    }
  #endif

return 0;
}				/* DemandSimu	*/
/* ===================================================================== */

long DemandSimuInit( struct genSubRecord *pgsub )
{
  X1=1;	  X2=3;   X3=5;
  Y1=2;   Y2=4;   Y3=6;
  Z1=2;   Z2=4;   Z3=8;
          T2=100; T3=200;

  T0 		= 0;
  TADV		= 1.5;
  TRACKID	= 1;
  TRACKID_OLD	= 0;		/* set outputs */
  DEMANDCOUNT	= 0;

  return 0;
}

/* ====================================================================	*/

long combineFlexCoeffs( struct genSubRecord *pgsub )
{
  double *pvala = (double *)pgsub->vala ;      /* Temp. pointer to vala */

  *pvala++ = *(double *)pgsub->a ;
  *pvala++ = *(double *)pgsub->b ;
  *pvala++ = *(double *)pgsub->c ;
  *pvala++ = *(double *)pgsub->d ;
  *pvala++ = *(double *)pgsub->e ;
  *pvala++ = *(double *)pgsub->f ;

  return 0;
}

/* ====================================================================	*/

 #undef A
 #undef B
 #undef C
 #undef D
 #undef E
 #undef F
 #undef G
 #undef H
 #undef I

 #undef X1
 #undef X2
 #undef X3
 #undef Y1
 #undef Y2
 #undef Y3
 #undef Z1
 #undef Z2
 #undef Z3

 #undef X
 #undef Y
 #undef Z

 #undef T
 #undef T0
 #undef T1
 #undef T2
 #undef T3
 #undef ID3
 #undef TADV
 #undef TNEW
 #undef TSENT
 #undef TRACKID
 #undef TRACKID_OLD
 #undef TRACKID_OUT
 #undef DEMANDCOUNT
 #undef DENOM
 #undef P1P2MARK

/* ====================================================================	*/

  #define FLEX  ((double *)pgsub->a)
  #define C0    ((double *)pgsub->a)[0]
  #define C1    ((double *)pgsub->a)[1]
  #define C2    ((double *)pgsub->a)[2]
  #define C3    ((double *)pgsub->a)[3]
  #define C4    ((double *)pgsub->a)[4]
  #define C5    ((double *)pgsub->a)[5]
  #define ZD    (*(double *)pgsub->b)
  #define RMA   (*(double *)pgsub->c)
  #define CORRECT_FLEXURE (*(long *)pgsub->d)
  #define FLEX_DEBUG (*(long *)pgsub->f)
  #define FLEX_PI   3.1415926535897932384626
  #define DEG_TO_RAD  (FLEX_PI / 180.0)

  #define DEMNEW ((double*)pgsub->j)
  #define TNEW	((double *)pgsub->j)[1]		/* tapply of new dem. 	*/
  #define IDNEW ((double *)pgsub->j)[2]
  #define XNEW	((double *)pgsub->j)[3]			/* new 		*/
  #define YNEW	((double *)pgsub->j)[4]
  #define ZNEW	((double *)pgsub->j)[5]

  #define DEM1 	((double *)pgsub->vala)
  #define T1 	((double *)pgsub->vala)[1]
  #define X1  	((double *)pgsub->vala)[3]		/* oldest 	*/
  #define Y1  	((double *)pgsub->vala)[4]
  #define Z1  	((double *)pgsub->vala)[5]

  #define DEM2 	((double *)pgsub->valb)
  #define T2 	((double *)pgsub->valb)[1]
  #define X2  	((double *)pgsub->valb)[3]
  #define Y2  	((double *)pgsub->valb)[4]
  #define Z2  	((double *)pgsub->valb)[5]

  #define DEM3 	((double *)pgsub->valc)
  #define T3 	((double *)pgsub->valc)[1]
  #define ID3 	((double *)pgsub->valc)[2]		/* new TRACKID 	*/
  #define X3  	((double *)pgsub->valc)[3]		/* newest 	*/
  #define Y3  	((double *)pgsub->valc)[4]
  #define Z3  	((double *)pgsub->valc)[5]

  #define A 	((double *)pgsub->vald)[0]		/* coefficients */
  #define B 	((double *)pgsub->vald)[1]
  #define C 	((double *)pgsub->vald)[2]
  #define D	((double *)pgsub->vald)[3]
  #define E 	((double *)pgsub->vald)[4]
  #define F	((double *)pgsub->vald)[5]
  #define G 	((double *)pgsub->vald)[6]
  #define H 	((double *)pgsub->vald)[7]
  #define I 	((double *)pgsub->vald)[8]
  #define DENOM ((double *)pgsub->vald)[9]

  #define T1DCOPY	(*(double *)pgsub->valf)
  #define ID3COPY 	(*(double *)pgsub->valg)

  #define P1P2MARK	((long)*(double*)pgsub->e)	/* am I p1 or p2? */
  #define ENOUGHMARK	(*(long *)pgsub->vale)		/* enough data?	  */

  #define INTERPOLTYPE	(*(long *)pgsub->h)
  #define OUTINTTYPE	(*(long *)pgsub->valh)

  #define ENG_INT_0	0
  #define REAL_INT_1	1
  #define XY_INT_2	2

  #define XSHIFT	(*(double *)pgsub->vali)
  #define YSHIFT 	(*(double *)pgsub->valj)
  
  #define DEMSIZE	(6 * sizeof (double)) 

  #define	PRINTTIMES(STRING)					\
	if (fastdebug)  { sprintf( messages, 				\
	"%s tn=%16.12g, T1=%16.12g, T2=%16.12g, T3=%16.12g, m=%d", 	\
	STRING, TNEW, T1, T2, T3, copymark); 				\
    	agprintf ("%s\n", messages);		}

  #define	PRINTALLCOEFF						\
    sprintf( messages, "Fol: A=%10.4g, B=%10.4g, C=%10.4g, D=%10.4g, 	\
		E=%10.4g, F=%10.4g, G=%10.4g, H=%10.4g, I=%10.4g, 	\
		x =%10.4g, y =%10.4g, z =%10.4g, X3=%10.4g, Y3=%10.4g, 	\
		Z3=%10.4g, cu=%d, tn=%16.12g, t0=%16.12g, T2=%6.4g, 	\
		T3=%6.4g, DENOM=%8.4g", 				\
	A, B, C, D, E, F, G, H, I, x, y, z, X3, Y3, Z3, 		\
	currpos[mechindex][0], TNEW, T1, T2, T3, DENOM); 		\
    agprintf ("%s\n", messages);

  #define FASTDEBUG

/* ====================================================================	*/
/*+
 *   Function name: followA
 *
 *   Purpose:
 *      To receive 20Hz demands in case of tracking mode.
 *
 *   Invocation:
 *      The function is attached to a gensub record called followA
 *      and will be called, when the gensub is triggered through a 
 *      Channel Access call
 *
 *   Parameters in:
 *	InpJ: 	Demands  (Array of 6 Doubles: TSENT, tApl, TRACKID, x, y, z)
 *
 *   Parameters out:
 * 	ValA:	Demand 1 (Array of 6 Doubles like above)	- oldest
 * 	ValB:	Demand 2
 * 	ValC:	Demand 3					- newest
 *	ValD:	9 Coefficients for interpolation
 *	VALE:	Mark =1: enough samples available
 *	VALF:	copy of start time (=VALA[1]=T1)
 *
 *   Return value:
 *
 *   Used Globals:      External functions:        External variables:
 *
 *   History:
 *   16-July-1997: 	Original version			(ko)
 *   25-Dec-97:	 	Changed					(ocf)
 */


long followA( struct genSubRecord *pgsub )
{
  double oldT1, oldT2;                /* Saved timestamps when shifting data */
  double t2n, t3n, x, y, z;
  double curr;
  double sinZen, shift;
  int    mechindex, status, copymark=7;
  char   messages[580];					/* Message buffer */
  int    fastdebug = 1;
  long   new_track_id;

  x = XNEW;
  y = YNEW;
  z = ZNEW;

  /* Apply Flexure correction here */

  if (CORRECT_FLEXURE) {
    /* AWE need to check the validity of coefficients and ZD, RMA */
    sinZen = sin(ZD * DEG_TO_RAD);
    if (FLEX_DEBUG) {
      printf("P%ld Flexure sinZen: %f \n",P1P2MARK, sinZen);
      printf("C0: %f, C1: %f, C2: %f, C3: %f, C4: %f, C5: %f \n",C0, C1, C2, C3, C4, C5);
      printf("RMA+C1: %f in rad: %f, sin(RMA+C1): %f\n",(RMA+C1), (RMA+C1)*DEG_TO_RAD, sin((RMA+C1)*DEG_TO_RAD));
    }
    /* shift in X */
    shift = C0 * sinZen * sin((RMA+C1)*DEG_TO_RAD) + C2 *sinZen;
    /* confirm value is ok */
    XSHIFT=shift;
    /* shift in Y */
    shift = C3 * sinZen * sin((RMA+C4)*DEG_TO_RAD) + C5 *sinZen;
    /* confirm value is ok */
    YSHIFT=shift;
    x=x+XSHIFT;
    y=y+YSHIFT;

    if (FLEX_DEBUG) {
      printf("P%ld Flexure X: %f XSHIFT: %f newX: %f\n",P1P2MARK, XNEW, XSHIFT, x);
      printf("P%ld Flexure Y: %f YSHIFT: %f newY: %f\n\n",P1P2MARK, YNEW, YSHIFT, y);
    }

  } else {
    XSHIFT =0;
    YSHIFT =0;
  }

  if ((INTERPOLTYPE == REAL_INT_1) || (INTERPOLTYPE == ENG_INT_0)) {
    mechindex = (P1P2MARK == 1) ? p1_probe : p2_probe;

    curr   = eng2real(Scale[mechindex][0], Offset[mechindex][0], 
                      currpos[mechindex][0]);
    if (IDNEW != ID3)
    {
         new_track_id = 1;
    } else {
         new_track_id = 0;
    }
    status = agXy2ab (mechindex, new_track_id, x, y, ForPar[mechindex], Limits[mechindex], 
	(mechindex <= p1_probe)? RTPA_OriFlag[0]: RTPA_OriFlag[1], curr,
        &x, &y);

    if (INTERPOLTYPE == ENG_INT_0) {
      x = real2eng (Scale[mechindex][0], Offset[mechindex][0], x);
      y = real2eng (Scale[mechindex][1], Offset[mechindex][1], y);
      z = real2eng (Scale[mechindex][2], Offset[mechindex][2], z);
    }
  }

  if (IDNEW != ID3) {                                   /* new track */
    if (fastdebug) {
      sprintf (	messages, "\t%s\t- new track %d -> %d", 
		pgsub->name, (int)ID3, (int)IDNEW); 
      agprintf  (	"%s\n", messages);  
    } 
    copymark = 0;
  }
  else if (TNEW >  T3) { copymark = 1; }		/* new dem. is newest */  
  else if (TNEW == T3) { copymark = 2; PRINTTIMES ("Fol: TNEW replaces T3 !") }
  else if (TNEW >  T2) { copymark = 3; PRINTTIMES ("Fol: TNEW older than T3 !") }
  else if (TNEW == T2) { copymark = 4; PRINTTIMES ("Fol: TNEW replaces T2 !") }
  else if (TNEW >  T1) { copymark = 5; PRINTTIMES ("Fol: TNEW older than T2 !") }
  else if (TNEW == T1) { copymark = 6; PRINTTIMES ("Fol: TNEW replaces T1 !") }
  else 		       { copymark = 7; PRINTTIMES ("Fol: TNEW older than T1 !") }

  switch (copymark)	/* 1st: shifting of values	*/
  {			/* 2nd: copying Input J in place, updating xyz */
    case 0: oldT1 = T1 ;                        /* Save time stamps */
            oldT2 = T2 ;
            memcpy (DEM1, DEMNEW, DEMSIZE);     /* new track: */
    	    memcpy (DEM2, DEMNEW, DEMSIZE);	/* delete all old dem.	*/
    	    memcpy (DEM3, DEMNEW, DEMSIZE);
            T1 = oldT1 ;                        /* Restore time stamps */
            T2 = oldT2 ; 
    	    X1=X2=X3 = x;			/* copy real/eng. coo.	*/	
    	    Y1=Y2=Y3 = y;
    	    Z1=Z2=Z3 = z;
            agSetSlew (P1P2MARK);       break;

    case 1: memcpy (DEM1, DEM2,   DEMSIZE);	/* T is newest of 3	*/	
	    memcpy (DEM2, DEM3,   DEMSIZE);			
    case 2: memcpy (DEM3, DEMNEW, DEMSIZE);	/* T equals newest dem.	*/
    	    X3 = x;  Y3 = y;  Z3 = z;		
            break;                              /* copy real/eng. coo.	*/

    case 3: memcpy (DEM1, DEM2,   DEMSIZE);	/* T is newer than 2	*/
    case 4: memcpy (DEM2, DEMNEW, DEMSIZE);	/* T equals middle dem.	*/
            X2 = x;  Y2 = y;  Z2 = z;	
            break;                              /* copy real/eng. coo.	*/

    case 5: 					/* T is newer than 1	*/
    case 6: memcpy (DEM1, DEMNEW, DEMSIZE);	/* T equals oldest dem.	*/
    	    X1 = x;  Y1 = y;  Z1 = z;	
            break;		                /* copy real/eng. coo.	*/
  }


  OUTINTTYPE 	= INTERPOLTYPE;			/* link to interp. rec.	*/
  T1DCOPY 	= T1;
  ID3COPY 	= ID3;
					/* calc. Coeff. from 3 demands	*/
  t2n = T2 - T1;				/* normalized times	*/
  t3n = T3 - T1;

  DENOM = t2n*t3n*(t3n-t2n);

  if (DENOM > 1e-9 && DENOM < 1e9)    /* against div-by-0: t2,t3,delta > 1ms */
  { 
    A = (X1*t3n - X1*t2n - X2*t3n + X3*t2n ) / DENOM;	/* Accel./2 */
    D = (Y1*t3n     - Y1*t2n     - Y2*t3n     + Y3*t2n    ) / DENOM;
    G = (Z1*t3n     - Z1*t2n     - Z2*t3n     + Z3*t2n    ) / DENOM;

    B = (X1*t2n*t2n - X1*t3n*t3n + X2*t3n*t3n - X3*t2n*t2n) / DENOM; /* Veloc.*/
    E = (Y1*t2n*t2n - Y1*t3n*t3n + Y2*t3n*t3n - Y3*t2n*t2n) / DENOM;
    H = (Z1*t2n*t2n - Z1*t3n*t3n + Z2*t3n*t3n - Z3*t2n*t2n) / DENOM;

    C =  X1;							/* Offset */
    F =  Y1;
    I =  Z1;

    ENOUGHMARK = 1;
  }
  else ENOUGHMARK=DENOM=A=B=C=D=E=F=G=H=I= 0;

#if 1					/* print debugging messages...	*/				
  if (DENOM>1.9)			/* (not faster than 2 Hz) */
  {
    if (P1P2MARK != 1 && P1P2MARK != 2)
    { sprintf( messages, "\t%s\t- Error: pwfs mark is %d ", 
	       pgsub->name, (int) P1P2MARK);        
      agprintf ("%s\n", messages);
    }
/*    PRINTALLCOEFF	*/
  }
#endif

  return(0);
}

/* ====================================================================	*/

 #undef A
 #undef B
 #undef C
 #undef D
 #undef E
 #undef F	
 #undef G
 #undef H
 #undef I
 #undef DENOM
 #undef FLEX
 #undef C0
 #undef C1
 #undef C2
 #undef C3
 #undef C4
 #undef C5
 #undef ZD
 #undef RMA
 #undef XSHIFT
 #undef YSHIFT
 #undef CORRECT_FLEXURE 
 #undef FLEX_DEBUG
 #undef FLEX_PI
 #undef DEG_TO_RAD
 #undef X1
 #undef X2
 #undef X3
 #undef Y1
 #undef Y3 
 #undef Y3
 #undef Z1
 #undef Z2
 #undef Z3

 #undef x
 #undef y
 #undef z

 #undef t
 #undef T1
 #undef T2
 #undef T3
 #undef ID3
 #undef TADV
 #undef TNEW
 #undef TSENT
 #undef TRACKID
 #undef TRACKID_OLD
 #undef TRACKID_OUT
 #undef DEMANDCOUNT
 #undef INTERPOLTYPE
 #undef P1P2MARK
 #undef PRINTALLCOEFF

/* ====================================================================	*/

  #define T1 	((double *)pgsub->a)[1]			/* oldest 	*/
  #define T2 	((double *)pgsub->b)[1]
  #define T3 	((double *)pgsub->c)[1]			/* newest 	*/

							/* coefficients */
  #define A 	((double *)pgsub->d)[0]			/* Accel. X	*/
  #define B 	((double *)pgsub->d)[1]			/* Veloc. X	*/
  #define C 	((double *)pgsub->d)[2]			/* Offset X	*/
  #define D 	((double *)pgsub->d)[3]			/* Y		*/
  #define E 	((double *)pgsub->d)[4]
  #define F 	((double *)pgsub->d)[5]
  #define G 	((double *)pgsub->d)[6]			/* Z		*/
  #define H 	((double *)pgsub->d)[7]
  #define I 	((double *)pgsub->d)[8]
  #define DENOM	((double *)pgsub->d)[9]			/* DENOM	*/
  #define prevTrack 	((double *)pgsub->b)[2]         /* Previous trackID */
  #define newTrack 	((double *)pgsub->c)[2]		/* newest trackID */

/* SAMtoWRITE setting too big isn't dangerous (thinking that PMAC could
*  find an old sample during precalculations): 
*  the EPICS calculation takes place alwys prior to PMACSample
*  and samples wil always be written just behind PMACSample.
*  (exception: if a WHILE.. DWELL is necessary in the PLC prog 
*  due to an error; then we can "clamp" an error.)
*/
  #define SAMtoWRITE	20		/* samples to be written at once */
  #define SAMinADV	0		/* samples ahead (in advance)	 */
  #define MAXSAM	20		/* size of sample array in DPRam */
  #define SAMSPEED	(*(double *)pgsub->i)	/* 5e-3: Stepsize (in sec) of a PMAC move */

  #define P1P2MARK 	((long)*(double*)pgsub->e)
  #define OUTTYPE	(*(long *)pgsub->g)
  #define INTERPOLTYPE	(*(long *)pgsub->h)

  #define	xOUT	(*(double *)pgsub->vala)
  #define	yOUT	(*(double *)pgsub->valb)
  #define	zOUT	(*(double *)pgsub->valc)
  #define	vxOUT	(*(double *)pgsub->vald)
  #define	vyOUT	(*(double *)pgsub->vale)
  #define	vzOUT	(*(double *)pgsub->valf)

  #define	t	(*(double *)pgsub->valg)	/* tApply	*/
  #define	GLSAM	(*(long   *)pgsub->valh)
  #define	SAMPLE	(*(long   *)pgsub->vali)

  #define	PRINTALLVALS	{ sprintf( messages, 							\
	"Int: x=%13.7g, y=%13.7g, z=%13.7g, vx=%10.4g, vy=%10.4g, vz=%10.4g, tAppl=%16.12g, Sam=%ld",	\
	x, y, z, vx, vy, vz, t, sample); 								\
	agprintf ("%s\n", messages);		}

  #define	PRINTALLCOEFF	{ sprintf( messages, 							\
	"A=%10.4g, B=%10.4g, C=%10.4g, D=%10.4g, E=%10.4g, F=%10.4g, G=%10.4g, H=%10.4g, I=%10.4g, tnow=%16.12g, T1=%16.12g", \
	A, B, C, D, E, F, G, H, I, tnow, T1); 								\
    	agprintf ("%s\n", messages);		}								

/* ====================================================================	*/
/*+
 *   Function name: interpol
 *
 *   Purpose:
 *	To calculate the 200Hz demands for PMAC DPRam
 *   Invocation:
 *	When the associated gensub record is triggered
 *   Parameters in:
 *	A, B, C:	3 last demands from TCS
 *	D:		coefficients for interpolation
 *   Parameters out:
 *	The calculated position and velocity will be copied to DPRam directly.
 *	Addresses are: 	DF00..DF3B for 20 X,Y,Z position demands  (60 * 32 bit)
 *			DF40..DF7B for 20 X,Y,Z velocity  demands (60 * 32 bit)
 *	writing by: extern long putDPRamX (long pmacaddr, long Val, short card)
 *			a:=0xDF00;	putDPRamX (a+i, Pos, 0)
 *	Demanded and actual position may be logged
 *   Return value:
 *
 *   Globals:    External functions:    External variables:
 *
 *   Author:
 *   Karsten Ottow (ko), Olaf Frischmuth (ocf)
 *
 *   History:
 *   16-July-97: Original version			(ko)
 *   25-Dec- 97: renewed  version			(ocf)
 */
/*  
 *  In/Outputs:
 *  A,B,C:	oldest/middle/newest demand	DOUBLE
 *  D:		quadratic fit parameters	DOUBLE
 *  E:		Mark=1 for PWFS1, =2 for PWFS2	DOUBLE
 *  F:		T1 copy			DOUBLE
 *  G:		OUTTYPE				LONG
 *  H:		INTERPOLTYPE			LONG
 *  I:		SAMSPEED			DOUBLE
 *
 *  vala/b/c:	current x,y,z			DOUBLE
 *  vald/e/f:	vx,vy,vz			DOUBLE
 *  valg:	time				DOUBLE		tApply
 *  valh:	global sample			DOUBLE		0..xxxx
 *  vali:	sample or table			DOUBLE		0..19 or # of written arrays
 */

long interpol( struct genSubRecord *pgsub )
{
  double tnow;				/* actual time offset/s	*/
  long    i, error, card;
  long	 sample;			/* number [0..MAXSAMPLE-1]	*/
  long 	 mechindex; 			/* query_cadname (pgsub->name);	*/
  long   status;
  double curr;
  double x,y,z,vx,vy,vz;			
  char   messages[380];			/* Message buffer 		*/
  long   new_track_id;

  /* Initialize error to remove warnings */
  error = 0;

  /* ------------------------------------------	*/
  mechindex = (P1P2MARK  ==        1) ? p1_probe : p2_probe;
  card      = (mechindex == p1_probe) ? 0        : 1;

  if (pgsub->scan<=SCAN1s)
    if (P1P2MARK != 1 && P1P2MARK != 2) {
      sprintf( messages, "\t%s\t- Error: pwfs mark is %ld ", pgsub->name,
      P1P2MARK); 
      agprintf ("%s\n", messages);
    }

  if (T1>1e8)
    error = get_tai(&tnow);		/* get t in sec. since 1970 	*/
  if ( error < 0 )
  { if (pgsub->scan<=SCAN1s)		/* >= 1 sec. scan 		*/
    { sprintf( messages, "\t%s\t- Error %ld from get_tai, t=%16.12g",
               pgsub->name, error, t); 
      agLogMessage( mechindex, DEB_FULL, messages);
    }					/* time is valid anyway		*/
  }

  /* ------------------------------------------	*/
  SAMSPEED = lim (SAMSPEED, 0.005, 10);
  t = tnow;
  if (T1>1e8)	t -= T1;		/* normalize current time	*/
  else 
  { if  (GLSAM>100000) GLSAM=0;
    t  = GLSAM * SAMSPEED;		/* use relative time mode	*/
  }
  t += SAMSPEED * (SAMinADV + 1.5);	/* tApply_end of start sample	*/
  sample = getDPRam (TrPMsam, card, 0);	/* read next PMAC sample	*/
  sample = lim (sample + SAMinADV, 0, MAXSAM-1); /* don't exceed MAXSAM-1! */

  /* ------------------------------------------	*/

  for (i=0; i<SAMtoWRITE; i++)
  {
    x = A*t*t + B*t + C;		/* real world coord. of end pos.*/
    y = D*t*t + E*t + F;				
    z = G*t*t + H*t + I;

    vx= 2*A*t + B;			/* velocities			*/
    vy= 2*D*t + E;			/* (end velocity is calc.)	*/
    vz= 2*G*t + H;					

    /* ----------------------------------------	*/

    if (INTERPOLTYPE == ENG_INT_0)	/* not xy or real interpol. 	*/
    {  xOUT = x;    yOUT = y;    zOUT = z; /* eng. interpl., output is eng */
      vxOUT = vx;  vyOUT = vy;  vzOUT = vz;
      if (pgsub->scan <= SCAN1s) PRINTALLVALS;
      if (OUTTYPE != ENG_INT_0)  OUTTYPE = ENG_INT_0;   /* only eng. out is possible	*/
    }
    else				/* xy or real interpol. 	*/
    {
      if (OUTTYPE == XY_INT_2)
      {  xOUT =  x;   yOUT =  y;   zOUT =  z;
        vxOUT = vx;  vyOUT = vy;  vzOUT = vz;
	if (pgsub->scan <= SCAN1s) PRINTALLVALS;
      }

      if (INTERPOLTYPE == XY_INT_2)
      {
        curr = eng2real(Scale[mechindex][0], Offset[mechindex][0], 
                        currpos[mechindex][0]);
        new_track_id = ( prevTrack == newTrack )?0:1;

        status = agXy2ab (mechindex, new_track_id, x,y, ForPar[mechindex], Limits[mechindex], 
		(mechindex<=p1_probe)? RTPA_OriFlag[0]:  RTPA_OriFlag[1], curr,
                &x, &y);
/* the transformations vx -> valpha, vy -> vbeta must take place here.
 * vz is already calculated right.
 */
      }
      else  if (OUTTYPE == XY_INT_2)  OUTTYPE = REAL_INT_1;	
      
      if (OUTTYPE == REAL_INT_1)
      {  xOUT =  x;   yOUT =  y;   zOUT =  z;
        vxOUT = vx;  vyOUT = vy;  vzOUT = vz;
	if (pgsub->scan <= SCAN1s) PRINTALLVALS;
      }

      x  = real2eng (Scale[mechindex][0], Offset[mechindex][0], x);
      y  = real2eng (Scale[mechindex][1], Offset[mechindex][1], y);
      z  = real2eng (Scale[mechindex][2], Offset[mechindex][2], z);
      vx =   vx  *   Scale[mechindex][0];
      vy =   vy  *   Scale[mechindex][1];
      vz =   vz  *   Scale[mechindex][2];

      if (OUTTYPE == ENG_INT_0)	
      {  xOUT =  x;   yOUT =  y;   zOUT =  z;
        vxOUT = vx;  vyOUT = vy;  vzOUT = vz;
	if (pgsub->scan <= SCAN1s) PRINTALLVALS;
      }
    }

  /* ------------------------------------------	*/
	/* sample is the actual Sample which is just being calculated.
	 *  3 words further is the next sample.
	 */

    #if 1	
    if (getsimu(mechindex) == SIM_NONE) {
      putDPRamDP (TrPosStart + 3*sample+0, x, card, 0);
      putDPRamDP (TrPosStart + 3*sample+1, y, card, 0);
      putDPRamDP (TrPosStart + 3*sample+2, z, card, 0);	/* v: units are cts/s.*/
      putDPRamDP (TrVelStart + 3*sample+0, vx,card, 0);	/* X vel. sample      */
      putDPRamDP (TrVelStart + 3*sample+1, vy,card, 0);	/* Y vel. sample      */
      putDPRamDP (TrVelStart + 3*sample+2, vz,card, 0);	/* Z vel. sample      */

      putDPRam (TrEPsam, sample, card, 0);		/* last written sample*/
    } else {
      if (mechindex == p1_probe) {
        agMechSimTrack(p1_RT4, x);
        agMechSimTrack(p1_PA4, y);
        agMechSimTrack(p1_focus, z);
      } else if (mechindex == p2_probe) {
        agMechSimTrack(p2_RT3, x);
        agMechSimTrack(p2_PA3, y);
        agMechSimTrack(p2_focus, z);
      }
    }
    #endif
    /* ----------------------------------------	*/

    sample++;
    sample  = wrapsam (sample, MAXSAM);		/* don't exceed MAXSAM-1!  */
    GLSAM  += 1;				/* global sample           */
    SAMPLE  = sample;

    t += SAMSPEED;				/* calculate new tApply    */

  }	
						/* for loop over samples   */
  /* SAMPLE  += 1;	*/			/* meaning of vali is "table#"	*/
  /* if (pgsub->scan<=SCAN1s)	PRINTALLCOEFF	*/	/* >= 1 sec. scan  */

  return(0);
}


 #undef A
 #undef B
 #undef C
 #undef D
 #undef E
 #undef F
 #undef G
 #undef H
 #undef I

 #undef X1
 #undef X2
 #undef X3
 #undef Y1
 #undef Y2
 #undef Y3
 #undef Z1
 #undef Z2
 #undef Z3

 #undef x
 #undef y
 #undef z
 #undef vx
 #undef vy
 #undef vz

 #undef t
 #undef T1
 #undef T2
 #undef T3
 #undef ID3
 #undef TADV
 #undef TNEW
 #undef TSENT
 #undef TRACKID
 #undef TRACKID_OLD
 #undef TRACKID_OUT
 #undef DEMANDCOUNT
 #undef P1P2MARK

/* ====================================================================	*/
#define TRACKIDIN 	(((double *)pgsub->a)[2])
#define TRACKIDIN2 	(*(double *)pgsub->b   )
#define P1P2MARK 	((long)*(double*)pgsub->e)

#define TCALC 		(*(double *)pgsub->vala)
#define TRACKID 	(*(double *)pgsub->valb)
#define	angle	 	(*(double *)pgsub->valc)
#define xOfs	 	(*(double *)pgsub->vald)
#define xErr	 	(*(double *)pgsub->vale)
#define yOfs	 	(*(double *)pgsub->valf)
#define yErr	 	(*(double *)pgsub->valg)
#define zOfs	 	(*(double *)pgsub->valh)
#define zErr	 	(*(double *)pgsub->vali)
#define ArrOut	 	( (double *)pgsub->valj)

/* ====================================================================	*/
/* running at 20Hz (triggered by interpol only in case of tracking)
 * calculates probe Offsets (20 Hz demands - actual positions)
 * just reads the last demand and actual position from the DPRam
 * calculates differences
 * calculates xy coordinates.
 */

/* a:		actual demand (just for getting TRACKID)	DOUBLE
 * b:		another copy of trackId
 * e:		Mark=1 for PWFS1, =2 for PWFS2			DOUBLE
 *
 * vala..vali:	copies of the 9 parts of the output array (for eng.screen) 
 * valj:	output array, written to wfs records		DOUBLE
 */

long calcOffset ( struct genSubRecord *pgsub )
{
  char   messages[380];			/* Message buffer 		*/
  int    error, ori[2];
  long 	 mechindex; 	
  long   motor[3], card, sample, mode;
  double   edem[3], etarg[3];
  double          eact[3];
  double  dem[3],  act[3], t;
  long MSWX[3], ldem[3];
  long new_track_id;

  /* ------------------------------------------	*/
  #if 1
  if (pgsub->scan<=SCAN1s)
    if (P1P2MARK != 1 && P1P2MARK != 2)
    { sprintf( messages, "\t%s\t- Error: pwfs mark is %ld ", pgsub->name, P1P2MARK); 
      agprintf ("%s\n", messages);
    }
  #endif
  /* ------------------------------------------	*/

  mechindex = (P1P2MARK == 1) ? p1_probe : p2_probe;
  card 	    = (P1P2MARK == 1) ? 0 : 1;

#if 0
     motor[0] = PlcNr[mechindex][0];  
     motor[1] = PlcNr[mechindex][1];  
     motor[2] = PlcNr[mechindex][2]; 
     card=0;						/* PMAC1	*/
     if (motor[0]>16) {card=1;				/* PMAC2	*/
	 motor[0]-=16; motor[1]-=16; motor[2]-=16; }
#endif

  motor[0] = getplcn (mechindex, 1);
  motor[1] = getplcn (mechindex, 2);
  motor[2] = getplcn (mechindex, 3);

  TRACKID = (TRACKIDIN == 0) ? TRACKIDIN2 : TRACKIDIN;				/* copy in to out		*/
  new_track_id = (TRACKIDIN == TRACKID) ? 0 : 1;		
  error   = get_tai(&t);							/* get t in sec. since 1970 	*/

  if (getsimu(mechindex)==SIM_NONE)
  {
    mode   = getDPRam (FlagStart+ PLC30, card, 0);				/* PLC flags			*/


     getDPvals (motor[0], card,  &(MSWX[0]),  &(eact[0]),  &(edem[0]),  &(etarg[0]) );
     getDPvals (motor[1], card,  &(MSWX[1]),  &(eact[1]),  &(edem[1]),  &(etarg[1]) );
     getDPvals (motor[2], card,  &(MSWX[2]),  &(eact[2]),  &(edem[2]),  &(etarg[2]) );


    if ((mode == TRACKMODE) || (mode == CRUDEMODE))
    {
      get2DPRam (TrPMsam, card, 0, &sample);					/* last read sample		*/
      sample =   wrapsam (sample,  MAXSAM );					/* don't exceed MAXSAM-1!	*/

      get2DPRamDP (TrPosStart + 3*sample+0, card, 0, &(ldem[0]));		/* get demanded pos.		*/
      get2DPRamDP (TrPosStart + 3*sample+1, card, 0, &(ldem[1]));
      get2DPRamDP (TrPosStart + 3*sample+2, card, 0, &(ldem[2]));
      edem[0] = (double) ldem[0];
      edem[1] = (double) ldem[1];
      edem[2] = (double) ldem[2];
    }
    else
    {
#if 1
      get2DPRamDP (PosStart+motor[0], card, 0, &(ldem[0]) ); 			/* PLC pos.			*/
      get2DPRamDP (PosStart+motor[1], card, 0, &(ldem[1]) );      
      get2DPRamDP (PosStart+motor[2], card, 0, &(ldem[2]) );
      edem[0] = (double) ldem[0];
      edem[1] = (double) ldem[1];
      edem[2] = (double) ldem[2];
#endif
    }
    
#if 0
    getDPRamD2 (motad(motor[0])+ActPos, card, 0, &(eact[0]));			/* get act.pos.			*/
    getDPRamD2 (motad(motor[1])+ActPos, card, 0, &(eact[1]));
    getDPRamD2 (motad(motor[2])+ActPos, card, 0, &(eact[2]));
#endif
  }

  dem[0] = eng2real ( Scale[mechindex][0], Offset[mechindex][0], (long)edem[0] );	/* demands 		*/
  dem[1] = eng2real ( Scale[mechindex][1], Offset[mechindex][1], (long)edem[1] );
  dem[2] = eng2real ( Scale[mechindex][2], Offset[mechindex][2], (long)edem[2] );

  act[0] = eng2real ( Scale[mechindex][0], Offset[mechindex][0], (long)eact[0] );	/* actual 		*/
  act[1] = eng2real ( Scale[mechindex][1], Offset[mechindex][1], (long)eact[1] );
  act[2] = eng2real ( Scale[mechindex][2], Offset[mechindex][2], (long)eact[2] );

  angle = normAngle( act[0]+act[1], 180);					/* angle of probe / Gemini FOR	*/
 
  agAb2xy (mechindex, act[0], act[1], ForPar[mechindex], ori, &xOfs, &yOfs) ;
  agAb2xy (mechindex, dem[0], dem[1], ForPar[mechindex], ori, &dem[0], &dem[1]);
  zOfs = act[2];

  xOfs -= dem[0];   yOfs -= dem[1];   zOfs -= dem[2];	/* calc. difference */ 
  xErr  = 0.01;     
  yErr  = 0.01;     
  zErr  = 0.01;	/* (mm) estimated accuracy of encoder 	*/

  if (pgsub->scan==SCAN1s || pgsub->scan==SCAN1s)	
  { sprintf( messages, "\t%s\t- eng: %7d %7d %7d, real: %10.4g %10.4g %10.4g, dem: %10.4g %10.4g %10.4g", 
	pgsub->name, (int)eact[0], (int)eact[1], (int)eact[2], act[0], act[1], act[2], dem[0], dem[1], dem[2]); 
    agprintf ("%s\n", messages);
  }

  TCALC = t;				/* replace old time 		*/
  ArrOut[0] = TCALC;  	
  ArrOut[1] = TRACKID;	
  ArrOut[2] = angle;			/* Output to arr 		*/

  ArrOut[3] = xOfs;	ArrOut[4] = xErr;
  ArrOut[5] = yOfs;	ArrOut[6] = yErr;	
  ArrOut[7] = zOfs;	ArrOut[8] = zErr;

  return (0);
}

/* ====================================================================	*/
#undef P1P2MARK
/* ====================================================================	*/
#define INARR0 		( (double *)pgsub->a)	/* 6  items, follow dem. */
#define INARR1 		( (double *)pgsub->b)	/* 6  items,		 */
#define INARR2 		( (double *)pgsub->c)	/* 10 items, foll coeff. */
#define INARR3 		( (double *)pgsub->d)	/* 10 items, simu coeff. */
#define P1P2MARK 	( (long)  *(double*)pgsub->e)
#define SELECTOR	(*(long   *)pgsub->f)
#define INARR4 		( (double *)pgsub->g)	/* 6  items, old dem. */
#define INARR5 		( (double *)pgsub->h)	/* 6  items, mid dem. */
#define INARR6 		( (double *)pgsub->i)	/* 6  items, new dem. */

#define OUT0 		(*(double *)pgsub->vala)
#define OUT1 		(*(double *)pgsub->valb)
#define	OUT2	 	(*(double *)pgsub->valc)
#define OUT3	 	(*(double *)pgsub->vald)
#define OUT4	 	(*(double *)pgsub->vale)
#define OUT5	 	(*(double *)pgsub->valf)
#define OUT6	 	(*(double *)pgsub->valg)
#define OUT7	 	(*(double *)pgsub->valh)
#define OUT8	 	(*(double *)pgsub->vali)
#define OUTARR	 	( (double *)pgsub->valj)

/* ====================================================================	*/
/* running at a rate specified on dm screen
 * allows to monitor demands
 * what it monitors depends on a flag input
 */

long monitor ( struct genSubRecord *pgsub )
{
  char   messages[380];			/* Message buffer 		*/

  /* ------------------------------------------	*/
  #if 1
  if (pgsub->scan<=SCAN1s)
    if (P1P2MARK != 1 && P1P2MARK != 2)
    { sprintf( messages, "\t%s\t- Error: pwfs mark is %ld ", pgsub->name, P1P2MARK); 
      agprintf ("%s\n", messages);
    }
  #endif
  /* ------------------------------------------	*/

  switch (SELECTOR)
  { 
    case 0:  
      OUT0 = INARR0[0];
      OUT1 = INARR0[1];
      OUT2 = INARR0[2];
      OUT3 = INARR0[3];
      OUT4 = INARR0[4];
      OUT5 = INARR0[5];
      OUT6 = 0;
      OUT7 = 0;
      OUT8 = 0;		 break;
    case 1:  
      OUT0 = INARR1[0];
      OUT1 = INARR1[1];
      OUT2 = INARR1[2];
      OUT3 = INARR1[3];
      OUT4 = INARR1[4];
      OUT5 = INARR1[5];
      OUT6 = 0;
      OUT7 = 0;
      OUT8 = 0;		 break;
    case 2:  
      OUT0 = INARR2[0];
      OUT1 = INARR2[1];
      OUT2 = INARR2[2];
      OUT3 = INARR2[3];
      OUT4 = INARR2[4];
      OUT5 = INARR2[5];
      OUT6 = INARR2[6];
      OUT7 = INARR2[7];
      OUT8 = INARR2[8];	 break;
    case 3:  
      OUT0 = INARR3[0];
      OUT1 = INARR3[1];
      OUT2 = INARR3[2];
      OUT3 = INARR3[3];
      OUT4 = INARR3[4];
      OUT5 = INARR3[5];
      OUT6 = INARR3[6];
      OUT7 = INARR3[7];
      OUT8 = INARR3[8];  break;
    case 4:  
      OUT0 = INARR4[0];
      OUT1 = INARR4[1];
      OUT2 = INARR4[2];
      OUT3 = INARR4[3];
      OUT4 = INARR4[4];
      OUT5 = INARR4[5];
      OUT6 = 0;
      OUT7 = 0;
      OUT8 = 0;		 break;
    case 5:  
      OUT0 = INARR5[0];
      OUT1 = INARR5[1];
      OUT2 = INARR5[2];
      OUT3 = INARR5[3];
      OUT4 = INARR5[4];
      OUT5 = INARR5[5];
      OUT6 = 0;
      OUT7 = 0;
      OUT8 = 0; 	 break;
    default:
    case 6:  
      OUT0 = INARR6[0];
      OUT1 = INARR6[1];
      OUT2 = INARR6[2];
      OUT3 = INARR6[3];
      OUT4 = INARR6[4];
      OUT5 = INARR6[5];
      OUT6 = 0;
      OUT7 = 0;
      OUT8 = 0;		 break;
  }

  return (0);
}

/* ====================================================================	*/
epicsRegisterFunction(interpol);
epicsRegisterFunction(combineFlexCoeffs);
epicsRegisterFunction(monitor);
epicsRegisterFunction(DemandSimu);
epicsRegisterFunction(followA);
epicsRegisterFunction(calcOffset);
epicsRegisterFunction(DemandSimuInit);
