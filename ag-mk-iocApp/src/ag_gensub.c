/* static char rcsid[]="$Id: ag_gensub.c,v 1.31 2013/11/04 22:05:58 gemvx Exp $"; */
/*
 *  FILENAME
 *  --------
 *  gensub.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for most of the gensub functions used
 *  in the A&G unit
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  agCalcStateFlag  -  calculate a flag based on state of A&G
 *  agCalcProbeRadii -  calculate min and max probe radii
 *  agSetSlew        -  set slewing flags when track id changes
 *  long DPRead		( struct genSubRecord *pgsub );
 *  long DPR_Ini 	( struct genSubRecord *pgsub );
 *  long gis		( struct genSubRecord *pgsub );
 *  long torque 	( struct genSubRecord *pgsub );
 *  long torqueformula 	( double param[10][4], short fval[5], short defval[5] );
 *  long CalParm	( struct genSubRecord *pgsub );
 *  long CalParmInit	( struct genSubRecord *pgsub );
 *  long CalParmInit2	( struct genSubRecord *pgsub );
 *  long CalParmInit3	( struct genSubRecord *pgsub );
 *  long bc_tod		( struct genSubRecord *pgsub );
 *  long bc_tod_int	( struct genSubRecord *pgsub );
 *  long macfault 	( struct genSubRecord *pgsub );
 *  long present	( struct genSubRecord *pgsub );
 *  long inpos		( struct genSubRecord *pgsub );
 *  long xlatmain	( struct genSubRecord *pgsub );
 *  long xlatinit	( struct genSubRecord *pgsub );
 *  managelut        -  load a new lookup table and update menus
 *  long managelutinit	( struct genSubRecord *pgsub );
 *  long PutTolerance	( struct genSubRecord *pgsub );
 *  long writetols 	( struct genSubRecord *pgsub );
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
 *  24-June-1997: Original version 			(ocf)
 */
/* *INDENT-OFF* */
/*
 * $Log: ag_gensub.c,v $
 * Revision 1.31  2013/11/04 22:05:58  gemvx
 * Added reading linear stage skew.
 *
 * Revision 1.30  2012/09/18 03:33:58  gemvx
 * merge f2 branch, implement p1/p2 flexure compensation
 *
 * Revision 1.25  2004/11/23 17:55:15  gemvx
 * removed some print out
 *
 * Revision 1.24  2004/11/22 19:51:35  gemvx
 * several changes for PMAC reading, Field stop position anf CP tables
 *
 * Revision 1.23  2003/11/10 14:14:08  gemvx
 * Changes to fix busy/idle when trackid changes
 *
 * Revision 1.22  2003/11/10 14:10:13  gemvx
 * Set slew flag to get busy/idle transition when followingag_cad2.c
 *
 * Revision 1.21  2003/05/06 16:06:11  cjm
 * Enable PMAC servo after move of linear stage
 *
 * Revision 1.20  2003/04/10 13:22:35  cjm
 * Set I430 on completion of tilt mechanism move
 *
 * Revision 1.19  2003/04/08 09:08:49  cjm
 * Split mail box commands into separate commands
 *
 * Revision 1.18  2003/04/01 12:16:45  cjm
 * Reset P term of tilt table
 *
 * Revision 1.17  2003/03/25 15:06:08  cjm
 * Only set SF in position when brakes are on rotary table
 *
 * Revision 1.16  2003/03/08 23:36:19  cjm
 * Remove unnecessary tabs/spaces etc
 *
 * Revision 1.15  2001/12/14 03:04:46  ajf
 * Automatic sequencing of the optical encoders.
 *
 * Revision 1.14  2001/12/13 05:29:26  ajf
 * Bugs found during testing of the sequencing of the optical encoders
 *
 * Revision 1.13  2001/12/13 04:03:42  ajf
 * Changes for the automatic switching on/off of the optical encoder
 *
 * Revision 1.12  2001/08/14 14:00:18  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.11  2001/05/05 22:17:38  cjm
 * Modify CalParm routines to obsolete low level probe mechanism parameters
 *
 * Revision 1.10  2001/01/30 21:52:40  cjm
 * Fix bug in switching encoders on/off
 *
 * Revision 1.9  2001/01/15 14:42:47  cjm
 * declare routines used only here as static and improve code layout
 *
 * Revision 1.8  2000/12/20 13:53:50  cjm
 * Remove some checks on simulation mode, they are now obsolete
 *
 * Revision 1.7  2000/10/31 13:31:12  cjm
 * Modify managelut to use different epics outputs
 *
 * Revision 1.6  2000/05/06 04:28:13  cboyer
 * New version of Olaf V3-2 5May 2000
 *
 * Revision 1.5  2000/04/14 13:27:49  cjm
 * Merge of Hilo changes with latest Zeiss system
 *
 * Revision 1.2  2000/01/11 15:01:57  cjm
 * Use input u and output valc for probe arm length
 *
 * Revision 1.1.1.1  1999/12/03 22:49:13  ajf
 * Initial creation of the Gemini A&G repository
 *
 * Revision 1.1.1.1  1998/08/05 21:16:16  Gemini
 * Initial creation of the Gemini A&G repository
 *
 * Revision 1.1.1.1  1998/08/05 21:02:27  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 * Revision 1.1.1.1  1998/08/05 20:48:52  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 * Revision 1.2  1998/08/04 23:01:14  Gemini
 * ajf: Rename LUT's to fit in with UAE build.
 *
 * Revision 1.1.1.1  1998/08/04 20:30:55  Gemini
 * Initial creation of the Gemini A&G Repository
 *
 */
/* *INDENT-ON* */

#include <ag_define.h>
#include "agSimulate.h"

/* LUT's */
char lutstring[26][MAX_STRING_SIZE] =
{ "hrwfs_pimg",   "hrwfs_lens",    "hrwfs_clfilter", "hrwfs_ndfilter", "hrwfs_fldstop",
  "hrwfs_cal",    "hrwfs_focus",   "ag_sf",          "ag_hw",          "ag_ao",       
  "ag_p1_probe",  "ag_p1_focus",   "ag_p1_filter",   "ag_p1_fldstop",  "ag_p2_probe", 
  "ag_p2_focus",  "ag_p2_filter",  "ag_p2_fldstop",  "ag_p1_RT34",     "ag_p1_PA34",
  "ag_p2_RT34",   "ag_p2_PA34",    "ag_RT2",         "ag_Tilt",        "ag_Lin2",   
  "ag_PA3AO" 
};

static int p1TrackIdChanged = 0 ;
static int p2TrackIdChanged = 0 ;
static int p1Slewing = 0 ;
static int p2Slewing = 0 ;

static long torqueformula (double param[10][4], short fval[5], short defval[5]);
static long CalParmInit2 (struct genSubRecord *pgsub) ;
static long CalParmInit3 (struct genSubRecord *pgsub) ;
static long PutTolerance (struct genSubRecord *pgsub) ;

/*+
 *   Function name:
 *   agCalcStateFlag
 *
 *   Purpose:
 *   Calculate a flag to be used to enable/disable processing
 *
 *   Description:
 *   This routine reads in the state record from the A&G database and
 *   calculates a flag based on its value. This flag is used to enable or
 *   disable downstream processing. The flag is set to 1 if the state is
 *   RUNNING or CONFIGURING and 0 otherwise.
 *
 *   Invocation:
 *   agCalcStateFlag(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *
 *   a => Input state as a string
 *
 *   Epics outputs:
 *
 *   vala => Enable/disable flag
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *-
 */
  
long agCalcStateFlag (struct genSubRecord *pgsub)
{
  char state[MAX_STRING_SIZE] ;      /* Input state as a string */
  long flag ;                        /* Output flag value */
     
  strcpy (state, pgsub->a) ;
 
  if (!strncmp(state, "RUNNING", 7) || !strncmp(state, "CONFIGURING", 11)) {
   flag = 1 ;
  } else {
   flag = 0 ;
  }  
     
  *(long *)pgsub->vala = flag ;
 
  return 0 ;
}
 
/*+
 *   Function name:
 *   agCalcProbeRadii
 *
 *   Purpose:
 *   Calculate the max. and min. radii to which the probes can be moved
 *
 *   Description:
 *   The routine reads in the max. and min. probe arm angles and takes the
 *   minimum of the absolute values. Based on the rotary table radius and
 *   the arm length, the radial distance from the rotary table centre is
 *   calculated. This value is then projected into the focal plane to give
 *   the maximum distance at which a guide star can be picked up. Note that
 *   there is no guarantee that the star will not be vignetted at this
 *   radius. For the minimum radius the absolute difference of the probe
 *   arm length and rotary table radius is taken and projected into the
 *   focal plane.
 *
 *   Invocation:
 *   agCalcProbeRadii(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    (pgsub)  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *
 *   a => probe no. 1 or 2
 *
 *   Epics outputs:
 *
 *   vala => Minimum probe radius (mm)
 *   valb => Maximum probe radius (mm)
 *   valc => Minimum z focus (mm)
 *   vald => Maximum z focus (mm)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *-
 */
  
long agCalcProbeRadii (struct genSubRecord *pgsub)
{
  long probeId ;                 /* Probe identifier */
  int mechindex ;                /* Index for arrays */
  double rtRad ;                 /* Radius of rotary table */
  double arm ;                   /* Length of probe arm */
  double cosPA ;                 /* Cos of probe arm maximum angle */
  double maxPA ;                 /* Maximum probe arm angle (degs) */
  double maxRad ;                /* Maximum permitted radius (mm) */
  double minRad ;                /* Minimum permitted radius (mm) */
  double angLimit ;              /* Probe arm limit angle */
  double ssq ;                   /* Radial limit squared */
  double scale ;                 /* Scale factor to project into focal plane */
     
  probeId = *(long *)pgsub->a ;
 
  if (probeId == 1) {
   mechindex = p1_probe ;
   scale = M2TOFPLANE / (M2TOFPLANE - P1TOFPLANE) ;
  } else {
   mechindex = p2_probe ;
   scale = M2TOFPLANE / (M2TOFPLANE - P2TOFPLANE) ;
  }  
     
  rtRad = ForPar[mechindex][0] ;
  arm   = ForPar[mechindex][6] ;
     
/* Set maxPa to the minimum of the absolute values of the arm limits */
  maxPA = Limits[mechindex][2] ;
  if (maxPA < 0.0) maxPA = -maxPA ;
  angLimit = Limits[mechindex][3] ;
  if (angLimit < 0.0 ) angLimit = -angLimit ;
  if (angLimit < maxPA) maxPA = angLimit ;
     
  cosPA = cos(maxPA * PI / 180.0) ;
  ssq = rtRad*rtRad + arm*arm - 2.0*arm*rtRad*cosPA ;
  if (ssq < 0.0) ssq = -ssq ;
  maxRad = sqrt(ssq) ;
     
  minRad = rtRad - arm ;
  if (minRad < 0.0) minRad = -minRad ;
     
  *(double *)pgsub->vala = minRad * scale ;
  *(double *)pgsub->valb = maxRad * scale ;
     
/* Just copy the focus values */
  *(double *)pgsub->valc = Limits[mechindex][5] ;
  *(double *)pgsub->vald = Limits[mechindex][4] ;
  return 0 ;
     
}

/*+
 *   Function name:
 *   agSetSlew
 *
 *   Purpose:
 *   Set the slew flags when the track id changes
 *
 *   Description:
 *   Simply set the slew flags when trackid changes
 *
 *   Invocation:
 *   agSetSlew(probe)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  probe  (long)  Probe id 1 = pwfs1, 2 = pwfs2
 *
 *   Function value:
 *   None
 * 
 *-
 */

void agSetSlew (long probe)
{

  if (probe == 1) {
    p1TrackIdChanged = 1 ;
  } else if (probe == 2) {
    p2TrackIdChanged = 1 ;
  }

}


/* ====================================================================	*/

double get_tod(void)
{
  double time;

  bc635_event (&time);			/* all 5 event regs	*/
/*  time = (long)time % (24*60*60) + time - (long) time;  */	/* sec. since midnight	*/
  
  return (time);
}

/* ====================================================================	*/

long get_itod(int t[7])
{
  char messages[80];			/* Message buffer */

  long   ti;
  double td;

  td = get_tod();
  ti = (long)td;

  tai2str (messages, td);
  agLogMessage( hrwfs_cc, DEB_FULL, messages);

  return ti;
}


/* ====================================================================	*/
/* date format: ymd hms.fract 	*/
/* relies on 3 dig in fract (=ms)	*/
double set_tod(int t[7])
{					/* go from GPS to TAI	*/
  char messages[80];			/* Message buffer */

  #define d (double)
  double time = d t[3]*3600+d t[4]*60+d t[5]+d t[6]/1000;
  #undef d

  sprintf(  messages,  "TIME - time used for bc635_write/set_strobe: %f", time);
  agLogMessage( hrwfs_cc, DEB_FULL, messages);
  sprintf(  messages, "TIME - note: message below tells GPS time, not TAI.");
  agLogMessage( hrwfs_cc, DEB_FULL, messages);

  					/* bc635_set_strobe(time);	*/
  bc635_write (3,time);			/* uses same function as "ao"	*/
					/* bc635IntEnable(2,"");	*/
					/* called from BCconfigure	*/
  return (time);
}


/* ====================================================================	*/
/* Inputs:
 * a,b,c,d:	hour,min,sec,fract	long		from eng.screen
 * e:		1=Set! flag 		long		from eng.screen
 * f:		Time after tod	 	double 		from ai (sec. since midnight)
 * g:		1=Prepare PMAC1! flag 	long		from eng.screen
 * h:		1=Prepare PMAC2! flag 	long		from eng.screen
 **
 * Outputs:
 * vala,b,c,d:	current tod - 		hmsf
 * valf:	ai input (f) time	string
 * valg:	current tod		double
 */

long bc_tod( struct genSubRecord *pgsub )
{
  char messages[80];			/* Message buffer */
  int date[7];
  double t;

  if (*(long*)pgsub->e)
  {
    *(long*)pgsub->e = 0;		/* reset flag	*/
    date [3] = *(long*) pgsub->a;	/* h		*/
    date [4] = *(long*) pgsub->b;	/* m		*/
    date [5] = *(long*) pgsub->c;	/* s		*/
    date [6] = *(long*) pgsub->d;	/* fract 3 dig.	*/

    if (date[6]>10000) date[6]=10000;
    date [0] = date[1]= date[2]= 0;

    *(long *) pgsub->vala = date[3];
    *(long *) pgsub->valb = date[4];
    *(long *) pgsub->valc = date[5];
    *(long *) pgsub->vald = date[6];	/* fract	*/

    t = set_tod(date);

    *(double*) pgsub->valg = t;	
  }

  if (*(long*)pgsub->g)			/* prepare PMAC1 */
  {
    *(long*)pgsub->g = 0;		/* reset flag	*/
  }

  if (*(long*)pgsub->h)			/* prepare PMAC1 */
  {
    *(long*)pgsub->h = 0;		/* reset flag	*/
  }


  t = *(double*) pgsub->f;		/* ai -> valf	*/
  if (t > 3153.6e6) t=58;		/* (100*365*24*60*60) */
  if (t < 0) t=118;

  timeThenC (t,TAI,3,date);		/* 3 dig in fract. (=ms)*/
  sprintf( messages, "%02d.%02d.%d %02d:%02d:%02d.%03d", date[2], date[1], date[0], date[3], date[4], date[5], date[6]);
  strncpy ((char *)pgsub->valf, messages, MAX_STRING_SIZE);
  if (pgsub->scan<=SCAN2s)
    agLogMessage( hrwfs_cc, DEB_FULL, messages);

  return (0);
}

/* ====================================================================	*/
/* Bancomm - Time of day interrupt service routine
 * Gensub is Passive and is called, when ai (IO_Intr) saw a TOD interrupt
 **
 *Inputs:
 * f:		Time after tod-int.	double (sec. since midnight)
 **
 * Outputs:
 * valf:	current tod		string
 * valg:	current tod		double
 */

long bc_tod_int( struct genSubRecord *pgsub )
{
  char messages[80];			/* Message buffer */
  int date[7];
  double t;

  t = *(double*) pgsub->f;		/* ai	*/
  *(double*) pgsub->valg = t;

  timeThenC (t,TAI,3,date);		/* 3 dig in fract. (=ms)*/
  sprintf( messages, "TOD on: %02d.%02d.%d %02d:%02d:%02d.%03d", date[2],date[1],date[0],date[3],date[4],date[5],date[6]);
  strncpy ((char *)pgsub->valf, messages, MAX_STRING_SIZE);
  agLogMessage( hrwfs_cc, DEB_FULL, messages);

  return (0);
}


/* ====================================================================	*/
/* applies calculated counter torques to the DPRAM (torque PLC prog)
 * writes parameters necessary for correction of tilt to global variable corrparam
 * Input links (9 of 10 used): Doubles:
 * B:	elevation of telescope arm in deg.			NELM=1
 * D:	cassegrain rotator angle in deg.
 * F:	telescope temperature in deg C
 * H:	Pos. SFM   (array of 3 dimensions: RT, Tilt, Lin)	NELM=3 (LONGs)
 * J:	Pos. PWFS1 (array of 2 dimensions: RT, PA)
 * L:	Pos. PWFS2 (array of 2 dimensions: RT, PA)
 * N:	SFM   datumed flag (array of flag sum + 3 dimensions)	NELM=4
 * P:	PWFS1 datumed flag (array of flag sum + 3 dimensions)
 * R:	PWFS2 datumed flag (array of flag sum + 3 dimensions)
 **
 * Inputs from engineering screens: (doubles:) (also loaded as defaults by pvload)
 * A:	manual torque value RT4	  
 * C:	manual torque value PA4
 * E:	manual torque value RT3
 * G:	manual torque value PA3
 * I:	manual torque value RT2   (chars:)
 * K:	manual override: man. values (Byte, each of the 1st 5 bit for 1 source)
 * M:	manual override: disable counter torque amps (5 bit of Byte)
 **
 * Outputs:		(long)
 * VALA: torque value RT4	  
 * VALC: torque value PA4
 * VALE: torque value RT3
 * VALG: torque value PA3
 * VALI: torque value RT2
 * VALK: enabled torques (bit-sum)
 * VALL: applied torques (bit-sum)
 * VALM: manual override (bit-sum)
 * VALO: applied torque RT4 (read from PLC 27)
 * VALP: applied torque RT4 (read from PLC 27)
 * VALQ: applied torque RT4 (read from PLC 27)
 * VALR: applied torque RT4 (read from PLC 27)
 * VALS: applied torque RT4 (read from PLC 27)
 **
 * VALB: MACCON fault 1 (Tilt - PM1)
 * VALD: MACCON fault 2 (AO   - PM2)
 * VALF: MACCON fault 3 (HW   - PM2)
 * VALH: MACCON fault 1 translated string
 * VALJ: MACCON fault 1 translated string
 * VALN: MACCON fault 1 translated string
 */

#define FAULT0	(*(long*)pgsub->valb)
#define FAULT1	(*(long*)pgsub->vald)
#define FAULT2	(*(long*)pgsub->valf)

#define STR0	((char*)pgsub->valh)
#define STR1	((char*)pgsub->valj)
#define STR2	((char*)pgsub->valn)

/* ===================================================================== */

long convfault ( long fault, char * message)
{
  switch (fault)
  {	/* Max. String size (40):"0123456789012345678901234567890123456789"  */
      case 0:	sprintf (message, "%ld: Warning: short before IIT-error!", fault); break;
      case 1:	sprintf (message, "%ld: IIT-error, current to high"	, fault); break;
      case 2:	sprintf (message, "%ld: hall sensor signals missing!"	, fault); break;
      case 3:	sprintf (message, "%ld: temperature too high"		, fault); break;
      case 4:	sprintf (message, "%ld: current too high"		, fault); break;
      case 5:	sprintf (message, "%ld: voltage too low"			, fault); break;
      case 6:	sprintf (message, "%ld: voltage too high"		, fault); break;
      case 7:	sprintf (message, "%ld: no error, O.K."			, fault); break;
      default: 	sprintf (message, "%ld: unspecified error"		, fault); break;
  }
  return (0);
}

/* ===================================================================== */

long macfault ( struct genSubRecord *pgsub )
{
  long fault[3] = {-1, -1, -1};

  if (getsimu(ag_cc) == SIM_NONE)
  {
    fault[0] =  getDPRam (TorqEnStart+Fault_Ofs, 0, 0)       & 7;	/* Get fault  PM1 */
    fault[1] =  getDPRam (TorqEnStart+Fault_Ofs, 1, 0)       & 7;	/* Get fault1 PM2 */
    fault[2] = (getDPRam (TorqEnStart+Fault_Ofs, 1, 0) >> 4) & 7;	/* Get fault2 PM2 */
  }

  if (	(FAULT0 != fault[0] || STR0[0] == 0)  ||
	(FAULT1 != fault[1] || STR0[1] == 0)  ||
	(FAULT2 != fault[2] || STR0[2] == 0)  )
  {
    convfault (fault[0], STR0);
    convfault (fault[1], STR1);
    convfault (fault[2], STR2);

    FAULT0 = fault[0];
    FAULT1 = fault[1];
    FAULT2 = fault[2];
  }

  return (0);
}

/* ===================================================================== */

long torque ( struct genSubRecord *pgsub )
{
  int    i;
  short  v[5][4];			/* addr.,manual values	 */
  short  fval [5], defval[5];		/* formula output values */
  long   ena, applied=0;

  macfault (pgsub);			/* sub to disp. faults 	*/

  corrparam[0][0] = *(double*)pgsub->b;	/* elevation		*/
  corrparam[1][0] = *(double*)pgsub->d;	/* cass. rot.		*/
  corrparam[2][0] = *(double*)pgsub->f;	/* tel. temp.		*/

#if 0	/* values are not used for now, disconnected in capfast-schematic */
  for (i=0; i<3; i++)			/* Mech.pos.		*/
  { corrparam[3][i] = ((long*)pgsub->h)[i]; 		/* SF	*/
    corrparam[4][i] = ((long*)pgsub->j)[i];		/* P1	*/
    corrparam[5][i] = ((long*)pgsub->l)[i];		/* P2	*/
  }

  for (i=0; i<4; i++)			 		/* Mech.flags	*/
  { corrparam[6][i] = ((long*)pgsub->n)[i]; 		/* SF		*/
    corrparam[7][i] = ((long*)pgsub->p)[i];		/* P1		*/
    corrparam[8][i] = ((long*)pgsub->r)[i];		/* P2		*/
  }
#endif

  defval[0] = 	*(long*)pgsub->a;			/* default values */
  defval[1] = 	*(long*)pgsub->c;
  defval[2] = 	*(long*)pgsub->e;
  defval[3] = 	*(long*)pgsub->g;
  defval[4] = 	*(long*)pgsub->i;

  v[0][0] = 	*(long*)pgsub->a;			/* manual values */
  v[1][0] = 	*(long*)pgsub->c;
  v[2][0] = 	*(long*)pgsub->e;
  v[3][0] = 	*(long*)pgsub->g;
  v[4][0] = 	*(long*)pgsub->i;

  v[0][1] = 0;	  v[0][2] = 0;				/* address, card */
  v[1][1] = 1;	  v[1][2] = 0;				/* PA4		*/
  v[2][1] = 0;	  v[2][2] = 1;				/* RT3		*/
  v[3][1] = 1;	  v[3][2] = 1;				/* PA3		*/
  v[4][1] = 2;	  v[4][2] = 0;				/* RT2		*/

  torqueformula (corrparam, fval, defval);

  for (i=0; i<5; i++) {
 	/* if bit: val from eng.screen, else val from formula 	*/
    v[i][0] = (*(long*)pgsub->k & (1<<i)) ? v[i][0]: fval[i];	
    if (abs(v[i][0])>8000) v[i][0]= v[i][0]<0 ? -8000 : 8000; 	/* limit to x %	*/

    if (getsimu(ag_cc) == SIM_NONE)
    {
      putDPRam         (TorqValStart+v[i][1], v[i][0], v[i][2], 0);	/* Write Torque value	*/
      ena    = getDPRam (TorqEnStart+v[i][1], v[i][2], 0);		/* Get enabled response	*/
      v[i][3]= getDPRam(TorqActStart+v[i][1], v[i][2], 0);		/* Get applied response	*/
    }
    else ena = 0;

    applied |= (ena & 1)? (1<<i) : 0;  /* bit 0=1: applied! */

    ena = (*(long*)pgsub->m & (1<<i)) ? ena&~0x100:ena|0x100;	/* if bit en=0 else =1	*/
							/* set/clear bit */
    if (getsimu(ag_cc) == SIM_NONE)
      putDPRam (TorqEnStart+v[i][1], ena, v[i][2], 0);	/* Write amp en. */
  }

  *(long*)pgsub->vala = v[0][0];		/* output used values */
  *(long*)pgsub->valc = v[1][0];		/* PA4 demanded torque	*/
  *(long*)pgsub->vale = v[2][0];		/* RT3 demanded torque	*/
  *(long*)pgsub->valg = v[3][0];		/* PA3 demanded torque	*/
  *(long*)pgsub->vali = v[4][0];		/* RT2 demanded torque	*/

  *(long*)pgsub->valo = v[0][3];		/* RT4 actual torque	*/
  *(long*)pgsub->valp = v[1][3];		/* PA4 actual torque	*/
  *(long*)pgsub->valq = v[2][3];		/* RT3 actual torque	*/
  *(long*)pgsub->valr = v[3][3];		/* PA3 actual torque	*/
  *(long*)pgsub->vals = v[4][3];		/* RT2 actual torque	*/

  *(long*)pgsub->vall = applied & 0x1f;		/* applied torques	*/
  *(long*)pgsub->valk = (~*(long*)pgsub->m) & 0x1f;	/* enabled torques */
  *(long*)pgsub->valm = ( *(long*)pgsub->k) & 0x1f;	/* manual  overide */

return (0);
}

/* ===================================================================== */
/* Defaults should be 1500 (RT, eventually 3000) and 3000 (PA, eventually 6000)	*/

long torqueformula ( double param[10][4], short fval[5], short defval[5] )
{
  fval[0] = defval[0];				/* RT4	*/
  fval[1] = defval[1];				/* PA4	*/
  fval[2] = defval[2];				/* RT3	*/
  fval[3] = defval[3];				/* PA3	*/
  fval[4] = defval[4];				/* RT2	*/

  return (0);
}

/* ===================================================================== */
/*+
 *   Function name:
 *   gis
 *
 *   Purpose:
 *   This function reads and sets GIS events and demands.
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = gis( struct genSubRecord *pgsub );
 *
 *   Parameters:
 *      (!)  pgsub (struct genSubrecord *)  Pointer to gensub record 
 *
 *   Return value:
 *      (<) status      (long)        Status value
 *
 *   Epics inputs:
 *   a => GIS demand bit 0/1
 *   c => Manual override
 *   d => Manual demand On/Off
 *   e => Manual event On/Off 
 *
 *   Epics outputs:
 *   vala => GIS event bit 0/1
 *   valb => GIS event bit 0/1
 *   vald => Current GIS demand
 *   vale => Current GIS event
 *   valf => GIS demand bit 
 *   valg => GIS demand bit
 *
 *   Author:
 *   Olaf Frischmuth
 *
 *   History:
 *   24-Feb-1998: Original version			(ocf)
 *-
 */

long gis( struct genSubRecord *pgsub )
{
  char messages[80];                                     /* Message buffer */
  long val; 

/* generate GIS event if PMAC reports conditions (AO and P2 both not home) */ 
  val = getDPRam  (TorqEnStart + GIS_Ofs, 1, 0);         /* PLC GIS flag   */
  if    (val) 		setGIS(ag_PA3AO, GIS_ON );
  else	if (gis_event)	setGIS(ag_PA3AO, GIS_OFF);

  if (*(long*)pgsub->c)                                  /* override on */
    gis_event = (*(long*)pgsub->e) ? GIS_ON : GIS_OFF;
 
  setXYCOM();						/* acts on glob.var. */

  if (*(long*)pgsub->c)                                 /* override on */
  { gis_demand    = (*(long*)pgsub->d) ? GIS_ON  : GIS_OFF;
    gis_demand_hw = (*(long*)pgsub->d) ? GIS_SET : GIS_CLEAR;
  }

  *(long*) pgsub->valh = 0;                      /* 0= Stop command disabled */
						 /* by default               */
  if (*(long*)pgsub->vale != gis_event)
  { sprintf( messages, 
	"GIS: output event changed to %ld (%s)", 
	gis_event, GIS_str(gis_event)); 
    agLogMessage( ag_cc, DEB_MIN, messages);
    *(long*) pgsub->valh = (gis_event) ? 1 : 0;  /* 1= Stop command enabled  */
  }
  if (*(long*)pgsub->vald != gis_demand)
  { sprintf( messages,
	"GIS: input demand changed to %ld (%s)", 
	gis_demand, GIS_str(gis_demand)); 
    agLogMessage( ag_cc, DEB_MIN, messages);
    *(long*) pgsub->valh = (getGIS()) ? 1 : 0;  /* 1= Stop command enabled   */
  }

  *(long*)pgsub->vald = gis_demand;		/* output to eng.screen	*/
  *(long*)pgsub->vale = gis_event;		/* ->store compare vals	*/

  val =   (gis_event == GIS_ON) ? GIS_SET : GIS_CLEAR;
  *(long*)pgsub->vala = (val&1) ? 1:0;		/* output bits		*/
  *(long*)pgsub->valb = (val&2) ? 1:0;

  val = gis_demand_hw;
  *(long*)pgsub->valf = (val&1) ? 1:0;		/* output bits		*/
  *(long*)pgsub->valg = (val&2) ? 1:0;

  return (0);
}

/* ===================================================================== */
/* ===================================================================== */
#if 0
/* formerly parts of gis routine	*/
  long val0, val1, mechindex, i, arg[3];
  int  motor;

    for (i=0; i<2; i++)
    {
      mechindex = (i==0)? hrwfs_cc : ag_cc;

      if (getsimu (mechindex) == SIM_NONE)
      {
	/* val0 = getresponse (mechindex,0);	*/

        motor = getplcn (mechindex, 0); 	
      	val0  = getDPRam (FlagStart + motor, 0, 0);		/* 1/0 -> card number	*/
      	val1  = getDPRam (FlagStart + motor, 1, 0);

	arg[0] = P_BigCC;		/* if P_BigCC (=1), CC-PLC commands all mechs	*/
  	arg[1] = arg[0];	
  	arg[2] = 0;

		/* after all CC-PLC finished the last Stop command ... */
      	if ( ( val0 != C_Stop     ) && (val0 != C_Stop+100     ) &&
             ( val0 != C_SoftStop ) && (val0 != C_SoftStop+100 ) && 
	     ( val1 != C_Stop     ) && (val1 != C_Stop+100     ) &&
             ( val1 != C_SoftStop ) && (val1 != C_SoftStop+100 )  )

		/* ... give a new one	*/
          doPLCcomm (mechindex, C_SoftStop, arg);
      }
    }
#endif
/* ===================================================================== */

/*+
 *   Function name:
 *   present
 *
 *   Purpose:
 *   This function reads the time from the bancomm card.
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = present( struct genSubRecord *pgsub );
 *
 *   Parameters in:
 *
 *   Parameters out:
 *      < pgsub->vala string     time and date
 *
 *   Return value:
 *      < status      long        Status value
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Limitations:
 *
 *   Author:
 *   Olaf Frischmuth
 *
 *   History:
 *   24-Jan-1998: Original version			(ocf)
 *-
 */
/* vala: date/time string from vxworks
 * valb: TAI sec. double (sec since 1970) 
 * valc: date/time string from bancomm
 * vald: TAI sec. double (sec since 1970)
 */

long present( struct genSubRecord *pgsub )
{
  char messages[80];			/* Message buffer 	*/
  long status;				/* return status 	*/
  long error;
  int  date[7];				/* ymd hms.fract 	*/
  double t;

  error = timeNow(&t);			/* get t in s since 1970 */
  if ( error)
  {
    sprintf( messages, "\t%s\t- Error %ld from timeNow", pgsub->name, error); 
    if (pgsub->scan<=SCAN2s)
      agLogMessage( hrwfs_cc, DEB_FULL, messages);	
  }

  tai2str (messages, t);

  strncpy ((char *)pgsub->valb, messages, MAX_STRING_SIZE);
  *(double*) pgsub->vala = t;
 
  if (pgsub->scan<=SCAN2s)
    agLogMessage( hrwfs_cc, DEB_FULL, messages);

/* ===================================================================== */

  error = bc635_read (&t);		/* BC-hardware reg time	*/

  timeThenC (t,TAI,3,date);		/* 3 dig in fract. (=ms)*/
  sprintf( messages, "%02d.%02d.%d %02d:%02d:%02d.%03d", date[2],date[1],date[0],date[3],date[4],date[5],date[6]);

  strncpy ((char *)pgsub->vald, messages, MAX_STRING_SIZE);
  *(double*) pgsub->valc = t;
 
  if (pgsub->scan<=SCAN2s)
    agLogMessage( hrwfs_cc, DEB_FULL, messages);


  status = 0;
  return status;
}

/* ===================================================================== */
/* Inputs:
 * a,b,c:	current  x,y,z pos. from simu records		long	no array
 * e,i,k:	demanded x,y,z pos. from Eng CAD	  	long	no array
 * g,h:		datumed/parked flag from SNL (simu-mode)	long	no array
 * i:		unused						long	no array
 * j:		mechindex					long	no array
 *
 * Outputs:
 * vala,b,c: 	Current/Demanded/target Pos.			double	array[3]
 * vald: 	MSW 1/MSW 2					long	array[4]
 * vale: 	Response from PLC prog				long	array[4]
 * valf: 	Flags from PLC prog				long	array[4]
 * valg,h:	datumed/parked flags, pulled out by SAD SIRs	long	no array
 * vali:	PLC demanded position				long	array[4]
 * valj:	PLC number (PMAC2, if>16)			long	array[4]
 * valk:	Linear skew					long    no array
 * vall:	Stan requested pmac var @offset db40		long    no array
 * valm:	Stan requested pmac var @offset db41		long    no array
 * 
 * note: getDPRamDP can be used, but hi 8b must be cut.
 *	  better is getDPRamXY.
 */

#define DEMAND0		(*(long *)pgsub->e)
#define DEMAND1		(*(long *)pgsub->i)
#define DEMAND2		(*(long *)pgsub->k)

#define DATFLIN		(*(long *)pgsub->g)
#define PARFLIN		(*(long *)pgsub->h)
#define MECHINDEX	(*(long *)pgsub->j)

#define CURR		( (long *)pgsub->vala)	/* array pointers	*/
#define DEMA		( (long *)pgsub->valb)  /* NELM=3		*/
#define TARG		( (long *)pgsub->valc)
#define MSWX		( (long *)pgsub->vald)	/* NELM=4		*/
#define RESP		( (long *)pgsub->vale)
#define FLAG		( (long *)pgsub->valf)
#define DATFLOUT	(*(long *)pgsub->valg)
#define PARFLOUT	(*(long *)pgsub->valh)
#define PDEM		( (long *)pgsub->vali)
#define PLCNROUT	( (long *)pgsub->valj)	/* NELM=8		*/

#define LINSKEW		(*(long *)pgsub->valk)  /* Linear stage skew	*/
#define POS_ECT_CNT	(*(long *)pgsub->vall)  /* SFLinear Position encode ECT count */
#define SKW_ECT_CNT	(*(long *)pgsub->valm)  /* SFLinear Skew encode ECT count */


long DPRead( struct genSubRecord *pgsub )
{
/*  char  messages[80];		*/		/* Message buffer	*/
  int   card, PLCn;				/* PMAC-#, PMAC-ch.	*/
  int	i, k;
  long  lassign;
  double dcurr[3];
  double ddema[3];
  double dtarg[3];

  get2DPRamDP(LinSkewOffset, 0, 0, &lassign);  
  LINSKEW = lassign;
  get2DPRamDP(PosECTCntOffset, 0, 0, &lassign);  
  POS_ECT_CNT = lassign;
  get2DPRamDP(SkwECTCntOffset, 0, 0, &lassign);  
  SKW_ECT_CNT = lassign;

 /* printf("linear skew %ld\n", lassign); */

for  (i=0; i<4; i++)		/* top, x, y, z	*/
{
  PLCn = PLCNROUT[i];		/* PLC #	*/
  card = PLCNROUT[i+4] ;
  k = (i<=1) ? 0 : i-1;		/* bei i=0: k=0, i=1: k=0, i=2: k=1...*/
  				/* Value at i=0 is only ok at 1D mech!	*/
  if ((PLCn>0) && (PLCn<=16))   /* there is a PLC in the array	*/
  {
    if (getsimu(MECHINDEX)==SIM_NONE) {
      if ((PLCn<=4) || (PLCn==6))			/* normal ch.	*/
        getDPvals (PLCn, card,  &(MSWX[i]),  &(dcurr[k]),  &(ddema[k]),  
                   &(dtarg[k]) );
      else {    
        get2DPRamDP (CalcPosStart + Ch5_Src_Ofs, card, 0, &lassign);
        if (PLCn == lassign) 
          getDPvals (5, card,  &(MSWX[i]),  &(dcurr[k]),  &(ddema[k]), 
                     &(dtarg[k]) );
        else {    
          get2DPRamDP (CalcPosStart + Ch7_Src_Ofs, card, 0, &lassign);
          if (PLCn == lassign) 
      	    getDPvals (7, card,  &(MSWX[i]),  &(dcurr[k]),  &(ddema[k]), 
                       &(dtarg[k]) );
          else {    
            get2DPRamDP (CalcPosStart + Ch8_Src_Ofs, card, 0, &lassign);
            if (PLCn == lassign) 
      	      getDPvals (8, card,  &(MSWX[i]),  &(dcurr[k]),  &(ddema[k]),  
                         &(dtarg[k]) );
 	    else									/* not on 5/7/8: must be inact.	*/
  	    { get2DPRamDP (CalcPosStart +PLCn, card, 0, &lassign);  
              dcurr[k]=lassign;                             /* 32b calc.Pos.*/
   	      get2DPRamDP (CalcDemStart +PLCn, card, 0, &lassign);  
              ddema[k]=lassign;                             /* 32b dem. Pos.*/
    	      get2DPRamDP (CalcTargStart+PLCn, card, 0, &lassign);  
              dtarg[k]=lassign;                             /* 32b targ Pos.*/
  	      MSWX[i] = getDPRam (CalcMSWStart +PLCn, card, 0) | /* hi 16 MSW1	*/
      	               (getDPRam   (CalcMSWStart +PLCn, card, 2)<<16);	/* lo 16 MSW2	*/
   	    }										/* inact. "switched" motors */
	  }
	}
      }

      RESP[i] = (long) ((short) getDPRam (FlagStart+ PLCn, card, 0)); 
      PDEM[i] = (long) ((short) getDPRam (PosStart + PLCn, card, 0));
      FLAG[i] = (long) ((unsigned short) getDPRam (PLCflagsStart+ PLCn, card, 0));

      if (k==0)	  { 
        MSWX[0]=MSWX[i]; 
     /* RESP[0]=RESP[i]; */ 
     /* FLAG[0]=FLAG[i]; */
      } else { 
        MSWX[0] &= MSWX[i];   
     /* FLAG[0] &= FLAG[i]; */		/* calc. "AND"	*/
     /*if (RESP[i]  < RESP[0])  RESP[0]  = RESP[i]; */ 
      }	                                /* PLC resp. */

      DATFLOUT = (FLAG[0] & 1) ? 1:0;   /* Datum flag */
      PARFLOUT = (FLAG[0] & 2) ? 1:0; 	/* Parked flag */

    } else {                           /* simulated */

      dcurr[k] = agMechSimPosn(MECHINDEX, k) ; 
      switch (k)
      { case 0: ddema[k] = dtarg[k] = DEMAND0; break ;
	case 1: ddema[k] = dtarg[k] = DEMAND1; break;
	case 2: ddema[k] = dtarg[k] = DEMAND2; break;
      }
      MSWX[i]=0; 	PDEM[i]=0;
      FLAG[i] = agMechSimFlags(MECHINDEX, i) ;
      RESP[i] = agMechSimResp(MECHINDEX, i) ;
      LINSKEW = rand() % 100;
      DATFLOUT = (FLAG[0] & 1) ? 1:0;   /* Datum flag */
      PARFLOUT = (FLAG[0] & 2) ? 1:0; 	/* Parked flag */
    }							/* simulated	*/
    currpos[MECHINDEX][k] = (long) dcurr[k];		/* set globals	*/
    demapos[MECHINDEX][k] = (long) ddema[k];
    targpos[MECHINDEX][k] = (long) dtarg[k];
    plcflag[MECHINDEX][i] =        FLAG[i];
  }                                             /* (if PLC ex.) */
  else break;						/* save time if 1dim */
}

#if 0
  if ((pgsub->scan==SCAN10s)||(pgsub->scan==SCAN5s))	/* 10/5 Sec.	*/
  {
    sprintf( messages, "\t%s\t- triggered, mot=%d, card=%d, pos=%f", 
             pgsub->name, PLCn, card, *(double*)pgsub->vala); 
    agLogMessage( MECHINDEX, DEB_FULL, messages);
  }
#endif

  for (i=0; i<3; i++)
  {
    CURR[i] = dcurr[i];
    DEMA[i] = ddema[i];
    TARG[i] = dtarg[i];
  }

  return (0);
}
							/* (DPRead)	*/
/* ===================================================================== */

long DPR_Ini ( struct genSubRecord *pgsub )
{
  long i;

#if EXTRADEBUG
  char messages[80];		/* Message buffer	*/
#endif

#if EXTRADEBUG
  sprintf( messages, "%22s \t- init called", pgsub->name); 
  agprintf ("%s\n", messages);
#endif

  MECHINDEX   = query_cadname (pgsub->name);

  for  (i=0; i<4; i++)					/* top, x, y, z	*/
  {
    PLCNROUT[i]   = getplcn (MECHINDEX, i);
    PLCNROUT[i+4] = getcard (MECHINDEX, i);
  }

  return (0);
}

/* ===================================================================== */

#undef DEMAND0
#undef DEMAND1
#undef DEMAND2

#undef DATFLIN
#undef PARFLIN
#undef MECHINDEX

#undef CURR
#undef DEMA
#undef TARG
#undef MSWX
#undef RESP
#undef FLAG
#undef PDEM
#undef PLCNROUT

#undef DATFLOUT
#undef PARFLOUT

/* ===================================================================== */

#define 	PLCRESPIN		(*(long*)pgsub->j)
#define 	CARVALOUT		(*(long*)pgsub->vala)
#define 	HEALTHOUT		( (char*)pgsub->valb)

long CarHandler( struct genSubRecord *pgsub )
{
  long mindex ;      

  mindex = query_cadname(pgsub->name) ;

  if (PLCRESPIN < 0)
    CARVALOUT = menuCarstatesERROR;	
  else if (PLCRESPIN > 0 && PLCRESPIN != FOLLOW_ON && PLCRESPIN != FOLLOW_ON2)
    CARVALOUT = menuCarstatesBUSY;
  else
    CARVALOUT = menuCarstatesIDLE;

  if (PLCRESPIN >=  0)
    strcpy (HEALTHOUT,"GOOD");
  else if (PLCRESPIN >= -9  || (PLCRESPIN >= -20 && PLCRESPIN <= -16))
    strcpy (HEALTHOUT,"BAD");
  else
    strcpy (HEALTHOUT,"WARNING");

/* Check if the CAR has been triggered by the probes slewing */
  if (mindex == p1_probe && p1Slewing)
    CARVALOUT = menuCarstatesBUSY;
    
  if (mindex == p2_probe && p2Slewing)
    CARVALOUT = menuCarstatesBUSY;

  return (0);
}

#undef	PLCRESPIN
#undef	CARVALOUT
#undef	HEALTHOUT

/* ===================================================================== */
/* calculation of inPosition-Bit is done by xlatmain
 * if parked: inPos = true
 * if PLC IDLE and inPos = false : Warning (health)
 */

  #define MSWIN(i)	(((long*)pgsub->a)[i] )
  #define RESPIN	(((long*)pgsub->b)[0] )
  #define FLAGSIN(i)	(((long*)pgsub->c)[i] )
  #define MECHINDEX	(*(long*)pgsub->d)

  #define PARKIN(i)	(((long*)pgsub->c)[i] & PARKFLAG) /* PLCF/bit1 */
  #define INPOSIN(i)	(((long*)pgsub->c)[i] & IPOSFLAG) /* PLCF/bit5 */
  #define INPOMIN(i)	(((long*)pgsub->c)[i] & POSMFLAG) /* PLCF/bit2 */
  #define BRAKED(i)     (((long*)pgsub->c)[i] & BRONFLAG) /* PLCF/bit4 */

  #define STRINGOUT	( (char*)pgsub->vala)
  #define INPOSOUT	(*(long*)pgsub->valb)
  #define INDEXout	(*(long*)pgsub->valc)
  #define POSMOUT	(*(long*)pgsub->vald)	/* inPositionMode-Bit */
  #define RESPOUT	(*(long*)pgsub->vale)	
  #define FOLLOUT	(*(long*)pgsub->valf)
  #define FLAGS0OUT	(*(long*)pgsub->valg)
  #define PLCSTROUT	( (char*)pgsub->valh)
  #define MSW0OUT	(*(long*)pgsub->vali)
  #define LODISV	(*(long*)pgsub->valj)

/* ===================================================================== */

#define SETTLED 5

long xlatmain( struct genSubRecord *pgsub )
{

  static int p1Counter = 0 ;        /* Loop counter for in position status */
  static int p2Counter = 0 ;        /* Loop counter for in position status */
  long terminator ;
  char response[MAX_STRING_SIZE];
  char errmsg[MAX_STRING_SIZE];
  long card ;

  card = getcard (MECHINDEX,0) ;

/* For the SF only set the in position flag if the rotary table is braked.
*  The RT is the only one of the three components that has a brake.
*  Unfortuneately, the PLC code erroneously clears the brake field of the
*  composite mechanism before placing it in DP Ram so we have to fetch
*  it from the low-level mechanism
*/
/* Remove this ... RT2 inpos should not depend on the brakes right now */
 /* also check the parked flag ... the inposition bit gets set to early */
   if (MECHINDEX == ag_RT2) {
     INPOSOUT = (INPOSIN(0) && PARKIN(0))  ? TRUE : FALSE;
/*     RT2Braked = BRAKED(0) ; */
/*     if (INPOSIN(0) && BRAKED(0)) { */
/*       INPOSOUT = TRUE ; */
/*     } else { */
/*       INPOSOUT = FALSE ; */
/*     } */
/*   } else if (MECHINDEX == ag_sf) { */
/*     if (INPOSIN(0) && RT2Braked) { */
/*       INPOSOUT = TRUE ; */
/*     } else { */
/*       INPOSOUT = FALSE ; */
/*     } */
   } else {
     INPOSOUT = INPOSIN(0) ? TRUE : FALSE;
   } 

  POSMOUT  = INPOMIN(0)  ? TRUE : FALSE;
  MSW0OUT  = MSWIN(0);
  FLAGS0OUT= FLAGSIN(0);			/* first flags entry for SAD */


  if (RESPOUT != RESPIN) {
    RESPOUT = RESPIN;				/* hold translated value */

    switch (RESPIN)
    { /* Max. String size (40):   "0123456789012345678901234567890123456789"  */
      case 0:  

/* For the SF tilt we reset the P term of the servo when the mechanism is
*  in position to cut down the noise seen by Altair.
*  This may be a temporary fix until the PMAC code is changed.
*  This is only needed for Gemini North so uncomment the following section
*  before installing there.
*/

/*
         if (MECHINDEX == ag_Tilt) {
           terminator = drvPmacMbxWriteRead (card, "#4k I430=2000 j/ j=*", response, errmsg);
           if (errmsg[0]) {
             printf ("xlatmain: failed to restart SF tilt mechanism\n");
           }
         }
*/

/* Here we keep the SF linear stage servo running. There have been problems
*  with the stage slipping under gravity
*/
         if ((MECHINDEX == ag_Lin2 || MECHINDEX == ag_sf) && 
              lastPLCcomm[MECHINDEX] == C_Move) {
           terminator = drvPmacMbxWriteRead (card, "#5 j/", response, errmsg);
           if (errmsg[0]) {
             printf ("xlatmain: failed to enable SF linear servo\n");
           }
    
         }
         sprintf (STRINGOUT, "%ld: Idle", RESPIN); 
         break;

      case 1:
         sprintf (STRINGOUT, "%ld: Datum commanded (no ACK)", RESPIN); 
         break;
      case 2:
         sprintf (STRINGOUT, "%ld:  Park commanded (no ACK)"	, RESPIN); 
         break;
      case 3:	sprintf (STRINGOUT, "%ld:  Stop commanded (no ACK)"	, RESPIN); break;
      case 4:	sprintf (STRINGOUT, "%ld:  Move commanded (no ACK)"	, RESPIN); break;
      case 5:	sprintf (STRINGOUT, "%ld: Follow commanded (no ACK)"	, RESPIN); break;
      case 6:	sprintf (STRINGOUT, "%ld: internal Datum/Park command"	, RESPIN); break;
      case 7:	sprintf (STRINGOUT, "%ld: internal Datum/Move command"	, RESPIN); break;
      case 8:	sprintf (STRINGOUT, "%ld: internal Datum/Move/Follow cmd", RESPIN); break;
      case 9:	sprintf (STRINGOUT, "%ld: crude follow command (no ACK)" , RESPIN); break;
      case 10:	sprintf (STRINGOUT, "%ld: soft stop commanded (no ACK)" 	, RESPIN); break;

      case 101:	sprintf (STRINGOUT, "%ld: Datum in progress"		, RESPIN); break;
      case 102:	sprintf (STRINGOUT, "%ld:  Park in progress"		, RESPIN); break;
      case 103:	sprintf (STRINGOUT, "%ld:  Stop in progress"		, RESPIN); break;
      case 104:	sprintf (STRINGOUT, "%ld:  Move in progress"		, RESPIN); break;
      case 105:	sprintf (STRINGOUT, "%ld: Move/Follow: moving to start"	, RESPIN); break;
      case 106:	sprintf (STRINGOUT, "%ld: Datum/Park in progress"	, RESPIN); break;
      case 107:	sprintf (STRINGOUT, "%ld: Datum/Move in progress"	, RESPIN); break;
      case 108:	sprintf (STRINGOUT, "%ld: Datum/Move/Follow in progress"	, RESPIN); break;
      case 109:	sprintf (STRINGOUT, "%ld: crude following in progress"  	, RESPIN); break;
      case 110:	sprintf (STRINGOUT, "%ld: soft stop in progress"        	, RESPIN); break;
      case 205:	sprintf (STRINGOUT, "%ld: Follow switched on"		, RESPIN); break;
      case 209:	sprintf (STRINGOUT, "%ld: Crude follow switched on"	, RESPIN); break;

      case -1:	sprintf (STRINGOUT, "%ld: error: timeout on homing"	, RESPIN); break;
      case -2:	sprintf (STRINGOUT, "%ld: error: timeout on parking"	, RESPIN); break;
      case -3:	sprintf (STRINGOUT, "%ld: error: timeout on positioning"	, RESPIN); break;
      case -4:	sprintf (STRINGOUT, "%ld: error: timeout moving to limit", RESPIN); break;
      case -5:	sprintf (STRINGOUT, "%ld: timeout allocating a channel"	, RESPIN); break;
      case -6:	sprintf (STRINGOUT, "%ld: error: timeout at 1st move"	, RESPIN); break;
      case -7:	sprintf (STRINGOUT, "%ld: error: timeout at 2nd move"	, RESPIN); break;
      case -8:	sprintf (STRINGOUT, "%ld: error: timeout at 3d  move"	, RESPIN); break;
      case -9:	sprintf (STRINGOUT, "%ld: error: unknown command"	, RESPIN); break;

      case -10:	sprintf (STRINGOUT, "%ld: error:    PWFS2 blocks move."	, RESPIN); break;
      case -11:	sprintf (STRINGOUT, "%ld: error:   AOFold blocks move."	, RESPIN); break;
      case -12:	sprintf (STRINGOUT, "%ld: error: Pol.unit blocks move."	, RESPIN); break;
      case -13:	sprintf (STRINGOUT, "%ld: error:     Lens blocks move."	, RESPIN); break;
      case -14:	sprintf (STRINGOUT, "%ld: error:     pimg blocks move."	, RESPIN); break;
      case -15:	sprintf (STRINGOUT, "%ld: MACCON amp fault! Reset amp!"  , RESPIN); break;

      case -16:	sprintf (STRINGOUT, "%ld: error at homing PLCn 7"	, RESPIN); break;
      case -17:	sprintf (STRINGOUT, "%ld: error at homing PLCn 8"	, RESPIN); break;
      case -18:	sprintf (STRINGOUT, "%ld: error at homing PLCn 7/2"	, RESPIN); break;
      case -19:	sprintf (STRINGOUT, "%ld: error at homing PLCn 8/2"	, RESPIN); break;
      case -20:	sprintf (STRINGOUT, "%ld: error: inaccurate measurement"	, RESPIN); break;	/* out of range	*/
      case -21:	sprintf (STRINGOUT, "%ld: timeout in sub PLC program"	, RESPIN); break;

      case -23:	sprintf (STRINGOUT, "%ld: timeout in high level PLC"	, RESPIN); break;
      case -24:	sprintf (STRINGOUT, "%ld: AO and PWFS2 both not at home"	, RESPIN); break;
      case -25:	sprintf (STRINGOUT, "%ld: Tilt interlocks Linear (Mod2)"	, RESPIN); break;
      case -26:	sprintf (STRINGOUT, "%ld: Linear interlocks Tilt (Mod2)"	, RESPIN); break;
      case -27:	sprintf (STRINGOUT, "%ld: probably noise on limit switch", RESPIN); break;
      case -28:	sprintf (STRINGOUT, "%ld: pos. limit switch reached"    	, RESPIN); break;
      case -29:	sprintf (STRINGOUT, "%ld: neg. limit switch reached"    	, RESPIN); break;

      case -30:	sprintf (STRINGOUT, "%ld: Cannot follow, no demands!"   	, RESPIN); break;
      case -31:	sprintf (STRINGOUT, "%ld: Timeout starting follow!"     	, RESPIN); break;
      case -32:	sprintf (STRINGOUT, "%ld: Error: Motion prog is running!", RESPIN); break;

      default: 	
	if      (RESPIN>-100 && RESPIN<0)
		sprintf (STRINGOUT, "%ld: unspecified error occured!"	, RESPIN);
	else if (RESPIN>-1000 && RESPIN<-100)
		sprintf (STRINGOUT, "%ld: Error: unknown command %ld!"	, RESPIN, (RESPIN+100)*-1);
	else	sprintf (STRINGOUT, "%ld: unknown response!"		, RESPIN); 
	break;

    }	/* case	*/

    switch (RESPIN)
    {	
	case 105:
	case 205:
	case 108:
	case 109:  FOLLOUT = 1;	   /* PLC shows that follow was switched on */
	  break;

        default:   FOLLOUT = 0;	   /* PLC shows that no follow is in progress */
	  break;
    }										/* case	*/
    LODISV = 1;			/* CAR update enabled	*/

  } else {                      /* RESPOUT == RESPIN    */
    LODISV = 0;                 /* CAR update disabled  */
  }

/* The code here is triggered when the track id changes. It is placed
*  here so that the downstream EPICS processing can be re-used to set
*  the busy/idle flags as if it was being done by the PLC. The 
*  original delivered A&G did not take any notice of a change in the
*  trackid which is why it has had to be grafted on here.
*/
  if (MECHINDEX == p1_probe ) {
    if (p1TrackIdChanged && FOLLOUT) {
      p1TrackIdChanged = 0 ;          /* Make sure we only set BUSY once */
      p1Slewing = 1 ;
      LODISV = 1 ;                    /* Trigger down stream processing */
    } else {                         
      if (p1Slewing) {                /* Only do anything if we are slewing */
        if (INPOSOUT) {                
          p1Counter++ ;
        } else {
          p1Counter = 0 ;
        }
/* Must be in position for enough cycles as a check against overshoot and
*  also check that follow hasn't been turned off during the slew
*/
        if (p1Counter == SETTLED || !FOLLOUT) { 
          LODISV  = 1 ;
          p1Slewing = 0 ;
          p1Counter = 0 ;
        }
      }
    }
  }

  if (MECHINDEX == p2_probe ) {
    if (p2TrackIdChanged && FOLLOUT) {
      p2TrackIdChanged = 0 ;          /* Make sure we only set BUSY once */
      p2Slewing = 1 ;
      LODISV = 1 ;                    /* Trigger down stream processing */
    } else {                         
      if (p2Slewing) {                /* Only do anything if we are slewing */
        if (INPOSOUT) {                
          p2Counter++ ;
        } else {
          p2Counter = 0 ;
        }
        if (p2Counter == SETTLED || !FOLLOUT) { 
          LODISV  = 1 ;
          p2Slewing = 0 ;
          p2Counter = 0 ;
        }
      }
    }
  }

  return (0);
}

/* ===================================================================== */

long xlatinit( struct genSubRecord *pgsub )
{
#if EXTRADEBUG
  char messages[80];		/* Message buffer	*/
#endif

  RESPOUT = RESPIN + 1111;	/* RESPOUT!=RESPIN, do xlat */
  xlatmain (pgsub);

#if EXTRADEBUG
  sprintf( messages, "%22s \t- init called", pgsub->name); 
  agprintf ("%s\n", messages);
  /* long mechindex = query_cadname (pgsub->name); */
  /* agLogMessage( mechindex, DEB_NONE, messages); */
#endif

  MECHINDEX   = query_cadname (pgsub->name);
  INDEXout  = MECHINDEX;

  sprintf (PLCSTROUT, "%ld(%ld)", getplcn (MECHINDEX, 0), getcard (MECHINDEX, 0) +1);
  LODISV = 1;			/* CAR update enabled	*/

  return (0);
}

  #undef 	FLAGSIN
  #undef 	INPOSIN
  #undef 	MECHINDEX
  #undef 	RESPIN
  #undef 	STRINGOUT
  #undef 	INPOSOUT
  #undef 	INDEXout
  #undef 	POSMOUT
  #undef 	RESPOUT	
  #undef	FOLLOUT
  #undef	FLAGS0OUT
  #undef	PLCSTROUT

/* ===================================================================== */
long managelutinit( struct genSubRecord *pgsub )
{
  long mechindex = query_cadname (pgsub->name);

  asklut (pgsub);

  if (!((char*) pgsub->e)[0])
  	sprintf ((char*) pgsub->f, "%s.lut", lutstring[mechindex]);
  else	strncpy ((char*) pgsub->f, (char*) pgsub->e, MAX_STRING_SIZE);
         	((char*) pgsub->f) [MAX_STRING_SIZE-1] = 0;	

  return (0);
}

/* ===================================================================== */

/*+
 *   Function name:
 *   managelut
 *
 *   Purpose:
 *   Load a new lookup table and update associated menus
 *
 *   Description:
 *   Depending on the control variable read from input j, the routine either
 *   triggers the loading of a new lookup table or it spawns a task to
 *   load the LUT selections into a mbbi record.
 *
 *   Invocation:
 *   managelut(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *)  Pointer to gensub record 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *   e => default LUT filename
 *   f => current LUT filename
 *   j => trigger to process record
 *
 *   Epics outputs:
 *   vala => LUT filename
 *   valb => LUT filename
 *   valc => LUT filename
 *   vale => trigger for load of new LUT file
 *   valf => trigger for load of new LUT file
 *   valg => trigger for load of new LUT file
 * 
 *   Deficiencies:
 *   It would be better if the reloading of the LUT automatically triggered
 *   the update of the menu strings rather than making the user process
 *   this record twice. The problem with this is the relatively long time
 *   it takes the associated lutout record to load the new file.
 *
 *-
 */


long managelut( struct genSubRecord *pgsub )
{
  char messages[80];                             /* Message buffer */
  long mechindex = query_cadname (pgsub->name);

  *(long*) pgsub->vale = 0;
  *(long*) pgsub->valf = 0;
  *(long*) pgsub->valg = 0;

  switch (*(long*)pgsub->j)
  {
    case 2:                                      /* load all 3 luts */
      if (((char*) pgsub->f)[0] == 0)            /* empty string?   */
        strncpy ((char*) pgsub->f, (char*) pgsub->e, MAX_STRING_SIZE);

      ((char*) pgsub->f)[MAX_STRING_SIZE-1] = 0;  /* terminate */
      strncpy ((char*) pgsub->vala, (char*) pgsub->f, MAX_STRING_SIZE);
      strncpy ((char*) pgsub->valb, (char*) pgsub->f, MAX_STRING_SIZE);
      strncpy ((char*) pgsub->valc, (char*) pgsub->f, MAX_STRING_SIZE);
      *(long*) pgsub->vale = 1;                   /* signal "load" */
      *(long*) pgsub->valf = 1;                   /* signal "load" */
      *(long*) pgsub->valg = 1;                   /* signal "load" */
      break;

    case 1:
      asklut(pgsub);                             /* ask lut, put strings */

      epicsThreadMustCreate(
		      pgsub->name,
		      priorityMedium, // In vxWorks this was 45
		      epicsThreadGetStackSize(epicsThreadStackSmall),
		      (EPICSTHREADFUNC)updatemenustr,
		      (void *)mechindex
		      );
      break;
    case 0:
      break;                                 /* no cmd */

    default:
      sprintf( messages, "%s \t- called, f=%ld", pgsub->name,*(long*)pgsub->j);
      agLogMessage( mechindex, DEB_FULL, messages);
      break;
  }

  *(long*)pgsub->j = 0;                     /* reset command */

  return (0);
}

/* ===================================================================== */
/* update of output arrays with values from Inputs	*/

long CalParmInit( struct genSubRecord *pgsub )
{
  long   status=0;		/* return status	*/
  long mechindex = query_cadname (pgsub->name);

  ((double*) pgsub->vala)[0] = Scale [mechindex][0];
  ((double*) pgsub->vala)[1] = Scale [mechindex][1];
  ((double*) pgsub->vala)[2] = Scale [mechindex][2];

  ((double*) pgsub->valb)[0] = Offset[mechindex][0];
  ((double*) pgsub->valb)[1] = Offset[mechindex][1];
  ((double*) pgsub->valb)[2] = Offset[mechindex][2]; /* Frame params: */

  ((double*) pgsub->valc)[0] = ForPar[mechindex][0]; /* Radius Rotary table */
  ((double*) pgsub->valc)[1] = ForPar[mechindex][1]; /* Translation F.O.R / x */
  ((double*) pgsub->valc)[2] = ForPar[mechindex][2]; /* Translation F.O.R / y */
  ((double*) pgsub->valc)[3] = ForPar[mechindex][3]; /* Scale F.O.R / x	      */
  ((double*) pgsub->valc)[4] = ForPar[mechindex][4]; /* Scale F.O.R / y       */
  ((double*) pgsub->valc)[5] = ForPar[mechindex][5]; /* Tol. of inPosition    */
  ((double*) pgsub->valc)[6] = ForPar[mechindex][6]; /* Arm length            */

  ((double*) pgsub->vald)[0] = Limits[mechindex][0]; /* RT +Lim  (+220)  */
  ((double*) pgsub->vald)[1] = Limits[mechindex][1]; /* RT -Lim  (-220)  */
  ((double*) pgsub->vald)[2] = Limits[mechindex][2]; /* Y  +Lim               */
  ((double*) pgsub->vald)[3] = Limits[mechindex][3]; /* Y  -Lim               */
  ((double*) pgsub->vald)[4] = Limits[mechindex][4]; /* Z  +Lim               */
  ((double*) pgsub->vald)[5] = Limits[mechindex][5]; /* Z  -Lim               */   

  CalParmInit2(pgsub);
  CalParmInit3(pgsub);
  PutTolerance(pgsub);			/* copies Tolerances to DPRam */

  return (status);
}

/* ===================================================================== */

/*+
 *   Function name:
 *   CalParm
 *
 *   Purpose:
 *   Set the calibration parameters for a mechanism
 *
 *   Description:
 *   The index of the mechanism is checked and depending on whether the
 *   mechanism is a low-level one or a composite the internal calibration
 *   parameters are either fetched from the EPICS into links or set from
 *   data previously fetched from EPICS.
 *
 *   Invocation:
 *   status = CalParm(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub (struct genSubRecord *)  Pointer to gensub record 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long CalParm( struct genSubRecord *pgsub )
{
  long status=0;		/* return status	*/
  long mechindex = query_cadname (pgsub->name);

  if (mechindex == p1_probe || mechindex == p2_probe) {
    Scale [mechindex][0] = *(double*) pgsub->a;
    Scale [mechindex][1] = *(double*) pgsub->c;
    Scale [mechindex][2] = *(double*) pgsub->e;
    Offset[mechindex][0] = *(double*) pgsub->b;
    Offset[mechindex][1] = *(double*) pgsub->d;
    Offset[mechindex][2] = *(double*) pgsub->f;

/* Note that the tolerance for the focus drive is set when the probe gensub
*  record is processed. This means that all parameters for the sub
*  mechanisms are generated by the probe composite mechanism
*/
    if (mechindex == p1_probe) {
      ForPar[p1_focus][5] = *(double *)pgsub->k ;
    } else {
      ForPar[p2_focus][5] = *(double *)pgsub->k ;
    }

    ForPar[mechindex][0] = *(double*) pgsub->g; 
    ForPar[mechindex][1] = *(double*) pgsub->h; 
    ForPar[mechindex][2] = *(double*) pgsub->i;
    ForPar[mechindex][3] = *(double*) pgsub->r;
    ForPar[mechindex][4] = *(double*) pgsub->s;
    ForPar[mechindex][5] = *(double*) pgsub->t; 
    ForPar[mechindex][6] = *(double*) pgsub->u;

/* Set limits for +X, -X, +Y, -Y, +Z, -Z */  
    Limits[mechindex][0] = fmax(*(double*)pgsub->l, *(double*)pgsub->m); 
    Limits[mechindex][1] = fmin(*(double*)pgsub->l, *(double*)pgsub->m);
    Limits[mechindex][2] = fmax(*(double*)pgsub->n, *(double*)pgsub->o);
    Limits[mechindex][3] = fmin(*(double*)pgsub->n, *(double*)pgsub->o);
    Limits[mechindex][4] = fmax(*(double*)pgsub->p, *(double*)pgsub->q);
    Limits[mechindex][5] = fmin(*(double*)pgsub->p, *(double*)pgsub->q);

  } else if (mechindex == p1_focus) {
   
    Scale [mechindex][0] = Scale [p1_probe][2] ;
    Offset[mechindex][0] = Offset[p1_probe][2] ;
    Limits[mechindex][0] = Limits[p1_probe][4] ;
    Limits[mechindex][1] = Limits[p1_probe][5] ;

  } else if (mechindex == p2_focus) {
   
    Scale [mechindex][0] = Scale [p2_probe][2] ;
    Offset[mechindex][0] = Offset[p2_probe][2] ;
    Limits[mechindex][0] = Limits[p2_probe][4] ;
    Limits[mechindex][1] = Limits[p2_probe][5] ;

  } else if (mechindex == p1_RT4) {

    Scale [mechindex][0] = Scale [p1_probe][0] ;
    Offset[mechindex][0] = Offset[p1_probe][0] ;
    Limits[mechindex][0] = Limits[p1_probe][0] ;
    Limits[mechindex][1] = Limits[p1_probe][1] ;
    ForPar[mechindex][5] = ForPar[p1_probe][5] ;

  } else if (mechindex == p1_PA4) {

    Scale [mechindex][0] = Scale [p1_probe][1] ;
    Offset[mechindex][0] = Offset[p1_probe][1] ;
    Limits[mechindex][0] = Limits[p1_probe][2] ;
    Limits[mechindex][1] = Limits[p1_probe][3] ;
    ForPar[mechindex][5] = ForPar[p1_probe][5] ;

  } else if (mechindex == p2_RT3) {

    Scale [mechindex][0] = Scale [p2_probe][0] ;
    Offset[mechindex][0] = Offset[p2_probe][0] ;
    Limits[mechindex][0] = Limits[p2_probe][0] ;
    Limits[mechindex][1] = Limits[p2_probe][1] ;
    ForPar[mechindex][5] = ForPar[p2_probe][5] ;

  } else if (mechindex == p2_PA3) {

    Scale [mechindex][0] = Scale [p2_probe][1] ;
    Offset[mechindex][0] = Offset[p2_probe][1] ;
    Limits[mechindex][0] = Limits[p2_probe][2] ;
    Limits[mechindex][1] = Limits[p2_probe][3] ;
    ForPar[mechindex][5] = ForPar[p2_probe][5] ;

  } else {

    Scale [mechindex][0] = *(double*) pgsub->a;
    Scale [mechindex][1] = *(double*) pgsub->c;
    Scale [mechindex][2] = *(double*) pgsub->e;
    Offset[mechindex][0] = *(double*) pgsub->b;
    Offset[mechindex][1] = *(double*) pgsub->d;
    Offset[mechindex][2] = *(double*) pgsub->f;

    ForPar[mechindex][5] = *(double*) pgsub->t; 

    Limits[mechindex][0] = fmax(*(double*)pgsub->l, *(double*)pgsub->m); 
    Limits[mechindex][1] = fmin(*(double*)pgsub->l, *(double*)pgsub->m);
    Limits[mechindex][2] = fmax(*(double*)pgsub->n, *(double*)pgsub->o);
    Limits[mechindex][3] = fmin(*(double*)pgsub->n, *(double*)pgsub->o);
    Limits[mechindex][4] = fmax(*(double*)pgsub->p, *(double*)pgsub->q);
    Limits[mechindex][5] = fmin(*(double*)pgsub->p, *(double*)pgsub->q);
  }

  status = CalParmInit(pgsub);

  return (status);
}
/* ===================================================================== */
long writetol (int mechindex)
{
  long   tol;

  tol = fabs (Scale[mechindex][0] * ForPar [mechindex][5]);

  if (getsimu(mechindex)==SIM_NONE)	
    putDPRamDP (ToleranceStart + getplcn (mechindex, 0), tol, getcard (mechindex, 0), 0);

  return (0);
}

/* ===================================================================== */
/* update of DPRam with Tolerances, copies Tolerances to DPRam		*/

long PutTolerance( struct genSubRecord *pgsub )
{
  long   status=0;		/* return status	*/
  long   mechindex = query_cadname (pgsub->name);

  writetol (mechindex);

  return (status);
}

/* ===================================================================== */
long writetols ( struct genSubRecord *pgsub )
{
  int i;
  
  for (i=0; i<MAX_MECH_INDEX; i++)
    writetol (i);

  return (0);
}

/* ===================================================================== */
/* Update of Input fields, so that Value is visible at Input field 
 * as well as at Output array.
 */
 
long CalParmInit2( struct genSubRecord *pgsub )
{
  long   status=0;		/* return status	*/
  long mechindex = query_cadname (pgsub->name);

  *(double*) pgsub->a =   Scale [mechindex][0];
  *(double*) pgsub->c =	  Scale [mechindex][1];
  *(double*) pgsub->e =   Scale [mechindex][2];
  *(double*) pgsub->b =   Offset[mechindex][0];
  *(double*) pgsub->d =   Offset[mechindex][1];
  *(double*) pgsub->f =   Offset[mechindex][2];

  *(double*) pgsub->g =   ForPar[mechindex][0];
  *(double*) pgsub->h =   ForPar[mechindex][1];
  *(double*) pgsub->i =   ForPar[mechindex][2];
  *(double*) pgsub->r =   ForPar[mechindex][3];
  *(double*) pgsub->s =   ForPar[mechindex][4];
  *(double*) pgsub->t =   ForPar[mechindex][5];
  *(double*) pgsub->u =   ForPar[mechindex][6];
 
  *(double*) pgsub->l =   Limits[mechindex][0];		/* +Lim X	*/
  *(double*) pgsub->m =   Limits[mechindex][1];		/* -Lim X	*/
  *(double*) pgsub->n =   Limits[mechindex][2];		/* +Lim Y	*/
  *(double*) pgsub->o =   Limits[mechindex][3];		/* -Lim Y	*/
  *(double*) pgsub->p =   Limits[mechindex][4];		/* +Lim Z	*/
  *(double*) pgsub->q =   Limits[mechindex][5];		/* -Lim Z	*/

  return (status);
}
/* ===================================================================== */
/* put number of dimensions to VALE and VALF, index to VALG
 */
 
long CalParmInit3( struct genSubRecord *pgsub )
{
  long   status=0;		/* return status	*/
  int i,j;
  long mechindex = query_cadname (pgsub->name);

  j = getdims(mechindex);
  i=j-2;


  *(long*) pgsub->vale = (long) j;			/* # dim	*/
  *(long*) pgsub->valf = (long) i;			/* different coding */
  *(long*) pgsub->valg = (long) mechindex;

  return (status);
}


/* This is my routine for switching the encoders on and off - ocf */

long encoderRelay( genSubRecord *pgsub )
{
  long val;
  long mode;

  mode = *(long *)pgsub->a;
 
  if( mode )
  {
    val = *(long *)pgsub->j;
    encoderSwitch(val);
  }
/*
  else
    printf("encoderRelay did nothing\n");
*/

  return(0);
}

/* ==================================================================== */


long testDPRam (long addr, long pmac, long offset)
{
return (long) ((short) getDPRam (addr, pmac, offset));
}


/* ===================================================================== */
/* Inputs:
 * a,b,c:	current  x,y,z pos. from simu records		long	no array
 * d,e,f:	demanded x,y,z pos. from Eng CAD	  	long	no array
 * g,h:		datumed/parked flag from SNL (simu-mode)	long	no array
 * i:				unused				long	no array
 * j:		mechindex					long	no array
 *
 * Outputs:
 * vala,b,c: 	Current/Demanded/target Pos.			double	array[3]
 * vald: 	MSW 1/MSW 2					long	array[4]
 * vale: 	Response from PLC prog				long	array[4]
 * valf: 	Flags from PLC prog				long	array[4]
 * valg,h:	datumed/parked flags, pulled out by SAD SIRs	long	no array
 * vali:	PLC demanded position				long	array[4]
 * valj:	PLC number (PMAC2, if>16)			long	array[4]
 * 
 * note: getDPRamDP can be used, but hi 8b must be cut.
 *	  better is getDPRamXY.
 */

#define CURR		( (long *)pgsub->vala)	/* array pointers	*/
#define DEMA		( (long *)pgsub->valb)  /* NELM=3		*/
#define TARG		( (long *)pgsub->valc)
#define MSWX		( (long *)pgsub->vald)	/* NELM=4		*/
#define RESP		( (long *)pgsub->vale)
#define FLAG		( (long *)pgsub->valf)
#define PDEM		( (long *)pgsub->vali)
#define PLCNROUT	( (long *)pgsub->valj)	/* NELM=8		*/

#define DATFLOUT	(*(long *)pgsub->valg)
#define PARFLOUT	(*(long *)pgsub->valh)


long DPReadMem( struct genSubRecord *pgsub )
{
  int   card, motor;				/* PMAC-#, PMAC-ch.	*/
  long  outVal;
  long  status;
  int mechindex;
  int diff;
  char response[MAX_STRING_SIZE];
  char errmsg[MAX_STRING_SIZE];
  char fldName[MAX_STRING_SIZE];

  long   xpos;

  mechindex = query_cadname (pgsub->name);
  motor = getplcn (mechindex, 0);
  card  = getcard (mechindex, 0);

/* AWE: while testing in simulation mode, this kept giving PMAC errors ... now fixed*/
if (getsimu(mechindex)==SIM_NONE) {

  if ( card == 1 && motor == 1) {

     status = drvPmacMbxWriteRead (card, "M304", response, errmsg);
     if (errmsg[0]) 
         printf ("Write failed: M304 response was %s\n", errmsg);

     strncpy ((char*) pgsub->vala, (char*) response, MAX_STRING_SIZE);

     status = drvPmacMbxWriteRead (card, "M1004", response, errmsg);
     if (errmsg[0]) 
         printf ("Write failed: M1004 response was %s\n", errmsg);

     strncpy ((char*) pgsub->valb, (char*) response, MAX_STRING_SIZE);
  }

  if (mechindex == p1_fldstop) {

    status=cicsDbGet(AG_TOP(":p1:fldstop:demand.VAL"),errmsg,DBF_LONG,&outVal);
    status=cicsDbGet(AG_TOP(":p1:fldstopState.VAL"),errmsg,DBF_STRING,response);
    status=cicsDbGet(AG_TOP(":p1:fldstopName.VAL"),errmsg,DBF_STRING,fldName);

    xpos = currpos[mechindex][0];

    diff = xpos - outVal;

    if (( diff < -5 || diff > 5) && (strcmp(response,"IDLE") == 0 )) {
        status=cicsDbPut(AG_TOP(":p1:fldstopEng.A"),errmsg,DBF_LONG,&xpos);
        status=cicsDbPut(AG_TOP(":p1:fldstopEng.DIR"),errmsg,DBF_STRING,"0");
        status=cicsDbPut(AG_TOP(":p1:fldstopEng.DIR"),errmsg,DBF_STRING,"3");
    }
  }

  if (mechindex == p2_fldstop) {

    status=cicsDbGet(AG_TOP(":p2:fldstop:demand.VAL"),errmsg,DBF_LONG,&outVal);
    status=cicsDbGet(AG_TOP(":p2:fldstopState.VAL"),errmsg,DBF_STRING,response);
    status=cicsDbGet(AG_TOP(":p2:fldstopName.VAL"),errmsg,DBF_STRING,fldName);

    xpos = currpos[mechindex][0];

    diff = xpos - outVal;

    if (( diff < -5 || diff > 5) && (strcmp(response,"IDLE") == 0 )) {
        status=cicsDbPut(AG_TOP(":p2:fldstopEng.A"),errmsg,DBF_LONG,&xpos);
        status=cicsDbPut(AG_TOP(":p2:fldstopEng.DIR"),errmsg,DBF_STRING,"0");
        status=cicsDbPut(AG_TOP(":p2:fldstopEng.DIR"),errmsg,DBF_STRING,"3");
    }
  }
}
  return (0);
}
epicsRegisterFunction(DPRead);
epicsRegisterFunction(CalParm);
epicsRegisterFunction(xlatmain);
epicsRegisterFunction(CarHandler);
epicsRegisterFunction(DPReadMem);
epicsRegisterFunction(managelut);
epicsRegisterFunction(present);
epicsRegisterFunction(encoderRelay);
epicsRegisterFunction(agCalcStateFlag);
epicsRegisterFunction(gis);
epicsRegisterFunction(bc_tod_int);
epicsRegisterFunction(writetols);
epicsRegisterFunction(bc_tod);
epicsRegisterFunction(torque);
epicsRegisterFunction(agCalcProbeRadii);
epicsRegisterFunction(DPR_Ini);
epicsRegisterFunction(CalParmInit);
epicsRegisterFunction(xlatinit);
epicsRegisterFunction(managelutinit);
