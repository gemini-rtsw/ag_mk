/* static char rcsid[]="$Id: ag_sad.c,v 1.5 2002/05/22 02:59:36 cjm Exp $"; */
/*
 *  FILENAME
 *  --------
 *  sad.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all the SAD functions used
 *  in the A&G unit. The SAD functions are not allowed to use
 *  global c variables from the other parts of the A&G unit
 *  (simu, debug, positions ...).
 *  They are not allowed to use global functions, which ask 
 *  global variables (ag_log, getsimu, getdebug ...).
 *  If the SAD is loaded with "init_globals, the scale and offset 
 *  global constants can be used.
 *  They cannot call hardware dependend functions.
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  agSimModeSIR - convert simulate level to string representation
 *  RecalcPos  - Calculates Real World Pos from eng. Pos.
 *
 *  DEPENDENCIES
 *  ------------
 *
 *  LIMITATIONS
 *  -----------
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth
 *
 *  HISTORY
 *  -------
 *  24-Feb-1998: Original version 			(ocf)
 */
/* *INDENT-OFF* */
/*
 * $Log: ag_sad.c,v $
 * Revision 1.5  2002/05/22 02:59:36  cjm
 * Handle dummy fourth dimension in EngPos
 *
 * Revision 1.4  2001/01/15 14:46:07  cjm
 * Replace calls to alphabeta_2_xy with agAb2xy and improve code layout
 *
 * Revision 1.3  2000/12/20 13:38:06  cjm
 * Add routine agSimModeSIR
 *
 * Revision 1.2  2000/03/18 06:40:06  cjm
 * Acceptance test version
 *
 * Revision 1.1.1.1  1998/08/05 21:16:16  Gemini
 * Initial creation of the Gemini A&G repository
 *
 * Revision 1.1.1.1  1998/08/05 21:02:28  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 * Revision 1.1.1.1  1998/08/05 20:48:52  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 * Revision 1.1.1.1  1998/08/04 20:30:55  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 */
/* *INDENT-ON* */

#include  <ag_define.h>		

/* ===================================================================== */
/*+
 *   Function name:
 *   EngPos  - Holds eng. Pos.
 *
 *   Purpose:
 *   This function reads the eng. Pos. of 1 or 2 dimensions.
 *   In debugging mode: The simulated eng.pos. are taken.
 *   In real mode: eng.pos come through an array for the 3 dimensions
 *   from DPRead
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = EngPos( struct genSubRecord *pgsub );
 *
 *   Epics in:
 *      pgsub->d    long     act.   eng. pos. dimension 1..3
 *      pgsub->e    long     comm.  eng. pos. dimension 1..3
 *      pgsub->g    long     dummy 4th coordinate (only used by SF) 
 *
 *   Epics out:
 *      pgsub->vala long       eng pos. dimension 1
 *      pgsub->valb long       eng pos. dimension 2
 *      pgsub->valc long       eng pos. dimension 3
 *      pgsub->valg long       dummy 4th coordinate
 *
 *   Return value:
 *      (<) status      (long)        Status value
 *
 *   Author:
 *   Olaf Frischmuth
 *
 *   History:
 *   24-June-1997: Original version			(ocf)
 *-
 */

long EngPossic( struct genSubRecord *pgsub )
{
  return (0);
}

long EngPos( struct genSubRecord *pgsub )
{
  *(long*)pgsub->vala = ((long *)pgsub->d)[0];	/* current Pos.1 */
  *(long*)pgsub->valb = ((long *)pgsub->d)[1];	/* dim. 2	 */
  *(long*)pgsub->valc = ((long *)pgsub->d)[2];	/* dim. 3	 */

  *(long*)pgsub->vald = ((long *)pgsub->e)[0];	/* target  Pos.1 */
  *(long*)pgsub->vale = ((long *)pgsub->e)[1];	/* dim. 2	 */
  *(long*)pgsub->valf = ((long *)pgsub->e)[2];	/* dim. 3	 */

  *(long *)pgsub->valg = *(long *)pgsub->g ;     

  return (0);
}

/* ===================================================================== */

/*+
 *   Function name:
 *   RecalcPos  - Calculates Real World Pos from eng. Pos.
 *
 *   Purpose:
 *   This function reads the eng. Pos. of 1 or 2 dimensions.
 *   The real pos. are pushed into the gensub in advance.
 *
 *   Depending on the PV of the calling gensub different routines are used.
 *   (for 2d mechs, a different algorithm than for 1d mechs)
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = RecalcPos( struct genSubRecord *pgsub );
 *
 *   Parameters in:
 *      > pgsub->a    double     eng. pos. dimension 1
 *      > pgsub->b    double     eng. pos. dimension 2
 *      > pgsub->c    double     eng. pos. dimension 3
 *      > pgsub->i    double[3]  Scales dimension 1..3
 *      > pgsub->j    double[3]  Offset dimension 1..3
 *
 *   Parameters out:
 *      < pgsub->vala double     Real world pos. dimension 1
 *      < pgsub->valb double     Real world pos. dimension 2
 *      < pgsub->valc double     Real world pos. dimension 3
 *
 *   In case of p1/p2:probe:
 *	< pgsub->vala double     x
 *	< pgsub->valb double     y
 *	< pgsub->valg double     RT angle
 *	< pgsub->valh double     PA angle
 *	< pgsub->vald double     x target
 *	< pgsub->vale double     y target
 *	< pgsub->vali double     RT angle target
 *	< pgsub->valj double     PA angle target
 *
 *
 *   Return value:
 *      (<) status      (long)        Status value
 *
 *   Author:
 *   Olaf Frischmuth
 *
 *   History:
 *   24-June-1997: Original version			(ocf)
 *-
 */
/* Eng -> Real	*/
/*  outval = inval - Offset[mechindex][i]) / Scale[mechindex][i];	*/

/* Part of the following routine is necessary to make the coordinate 
 **  systems of P1 and P2 equal. P1 and P2 are mechanically mirrored: 
 * If the RT is on it's 0-position 
 **  (which allows it to go 220 deg to either side from that position), 
 **  the mounting point of P2 would be 90 deg to the right and
 **  the mounting point of P1 would be 90 deg to the left.
 ** TableAngle should be measured from the y-axis and this matches
 **   the design of P2, while it has to be corrected for P1.
 * Therefore, we subtract 180 deg from the real position of RT3 here.
 * The range is limited and normalized to +-180 deg.
 */


#define Acurr		(*(double *)pgsub->vala)
#define Bcurr		(*(double *)pgsub->valb)
#define Ccurr		(*(double *)pgsub->valc)

#define Atarg		(*(double *)pgsub->vald)
#define Btarg		(*(double *)pgsub->vale)
#define Ctarg		(*(double *)pgsub->valf)

#define ORI		((int   *)pgsub->valk)
#define FORPARM		((double*)pgsub->h)
#define P1P2MARK	(*(long *)pgsub->g)
  
#define RTCURR		(*(double *)pgsub->valg) 	/* RT / deg Curr. */
#define PACURR		(*(double *)pgsub->valh) 	/* PA / deg Curr. */
#define RTTARG		(*(double *)pgsub->vali) 	/* RT / deg Targ. */
#define PATARG		(*(double *)pgsub->valj) 	/* PA / deg Targ. */


long RecalcPos( struct genSubRecord *pgsub )
{
  long mechindex = 0 ;

  Acurr = eng2real ( ((double*)pgsub->i)[0], ((double*)pgsub->j)[0], 
                    *(long *)pgsub->a );	/* current */
  Bcurr = eng2real ( ((double*)pgsub->i)[1], ((double*)pgsub->j)[1], 
                    *(long *)pgsub->b );
  Ccurr = eng2real ( ((double*)pgsub->i)[2], ((double*)pgsub->j)[2], 
                    *(long *)pgsub->c );

  Atarg = eng2real ( ((double*)pgsub->i)[0], ((double*)pgsub->j)[0], 
                    *(long *)pgsub->d );	/* target  */
  Btarg = eng2real ( ((double*)pgsub->i)[1], ((double*)pgsub->j)[1], 
                    *(long *)pgsub->e );
  Ctarg = eng2real ( ((double*)pgsub->i)[2], ((double*)pgsub->j)[2], 
                    *(long *)pgsub->f );

					/* if (FORPARM[0] != 0)		*/
  if (P1P2MARK==1 || P1P2MARK==2)	/* only true for p1/p2:probe */
  {
    PACURR = Bcurr; 			/* PA / deg Curr. */
    PATARG = Btarg;  			/* PA / deg Targ. */

    if (P1P2MARK==2) {
      RTCURR = Acurr;			/* RT / deg Curr. */
      RTTARG = Atarg; 			/* RT / deg Targ. */
      mechindex = p2_probe ;
    } else {				/* Correction for PWFS1 only */
      RTCURR = Acurr;			/* RT / deg Curr. */
      RTTARG = Atarg; 			/* RT / deg Targ. */
      mechindex = p1_probe ;

/* Since RT3 is mechanically mirrored to RT4, a 180 deg correction 
 * is necessary for RT4 to make the output values "tableAngle" equal. 
 * In a mail from 6.12.1999, Jacques Sebag requested
 * not to make the correction. That's why the following code is inactive.
 */

#if 0
      RTCURR = normAngle (Acurr - 180, 180);
      RTTARG = normAngle (Atarg - 180, 180);
#endif
    }

    Ctarg = normAngle( Acurr+Bcurr, 180);     /* angle of probe / Gemini FOR */

    agAb2xy (mechindex, Acurr, Bcurr, FORPARM, ORI, &Acurr, &Bcurr) ; 
    agAb2xy (mechindex, Atarg, Btarg, FORPARM, ORI, &Atarg, &Btarg) ; 

  }
  return 0;
}

/* ===================================================================== */
/* 
 *  INPUTS:
 *	psir->rval = Health of TIME (STRING). This will be 0/1/2.
 *
 *  OUTPUTS:
 *	psir->val  = Health (STRING) -  (for Engineering Screens).
 *			GOOD
 *			WARNING
 *                      BAD
 */

long TimeSir( struct sirRecord *psir )
{
  switch( atol( (char *)psir->rval ) )
  {
    case 0:	strcpy( (char*)psir->val, "GOOD"     );	break;
    case 1:	strcpy( (char*)psir->val, "WARNING"  );	break;
    case 2:	strcpy( (char*)psir->val, "BAD"      );	break;
    default:	strcpy( (char*)psir->val, "undefined");
      		return -1;				 break;
  }
  return 0;
}

/* ==================================================================== */
/* 
 *  INPUTS:
 *	psir->rval = Following State (STRING). This will be 0/1.
 *
 *  OUTPUTS:
 *	psir->val  = Following State (STRING) -  (for Engineering Screens).
 *				OFF
 *				ON
 */

long followSIR( struct sirRecord *psir )
{
  long state;
  long ret;

  ret   = 0;
  state = atol( (char *)psir->rval );
  switch( state )
  {
    case 0:
      strcpy( (char *)psir->val, "OFF" );
      break;

    case 1:
      strcpy( (char *)psir->val, "ON" );
      break;

    default:
      strcpy( (char *)psir->val, "  " );
      ret = -1;
  }
  return ret;
}
/* ===================================================================== */
/* 
 *  INPUTS:
 *	psir->rval = Health of follow demands (STRING). This will be 0/1/2.
 *
 *  OUTPUTS:
 *	psir->val  = Health (STRING) -  (for Engineering Screens).
 *			GOOD
 *			LATE
 *                      BAD
 */

long arraySSIR( struct sirRecord *psir )
{
  switch( atol( (char *)psir->rval ) )
  {
    case 1:	strcpy( (char*)psir->val, "GOOD"     );	break;
 /* case x:	strcpy( (char*)psir->val, "LATE"  );	break;	*/
    case 0:	strcpy( (char*)psir->val, "BAD"      );	break;
    default:	strcpy( (char*)psir->val, "undefined");
      		return -1;				 break;
  }
  return 0;
}
/* ==================================================================== */

/*+
 *   Function name:
 *   agSimModeSIR
 *
 *   Purpose:
 *   Convert the simulation level into a name
 *
 *   Description:
 *   Reads the input level and converts the level to a corresponding name.
 *   If the level is invalid the the simulation mode is assumed to be
 *   "NONE". The routine is copied from simulateSIR.c in the CRCS.
 *
 *   Invocation:
 *   agSimModeSIR(psir)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psir    (struct sirRecord *)   Pointer to SIR record structure
 *
 *   Epics inputs:
 *   rval => Simulate Level. This will be 0/1/2/3 encoded as a string.
 *
 *   Epics outputs:
 *   val  => Simulation name NONE, VSM, FAST or FULL
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */


long agSimModeSIR( struct sirRecord *psir )
{
  long level;
  long ret;

  ret   = 0;
  level = atol( (char *)psir->rval );
  switch( level )
  {
    case SIM_NONE:
      strcpy( (char *)psir->val, "NONE" );
      break;

    case SIM_VSM:
      strcpy( (char *)psir->val, "VSM" );
      break;

    case SIM_FAST:
      strcpy( (char *)psir->val, "FAST" );
      break;

    case SIM_FULL:
      strcpy( (char *)psir->val, "FULL" );
      break;

    default:
      strcpy( (char *)psir->val, "NONE" );
      ret = -1;
      break;
  }
  return ret;
}
epicsRegisterFunction(TimeSir);
epicsRegisterFunction(RecalcPos);
epicsRegisterFunction(EngPossic);
epicsRegisterFunction(EngPos);
epicsRegisterFunction(followSIR);
epicsRegisterFunction(arraySSIR);
epicsRegisterFunction(agSimModeSIR);
