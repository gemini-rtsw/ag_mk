/*
 *  FILENAME
 *  --------
 *  ag_globals.c
 *
 *  PURPOSE
 *  -------
 *  This file holds the definitions of all used 
 *  global C variables in the A&G unit software.
 *
 *  The file "ag_define.h" holds external references 
 *  to these definitions. 
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
 */

#include  <ag_define.h>

/* non-zero [1] signals m-D mechanisms, in which case the top level PLC stands on index	[0]*/
int    PlcNr    [MAX_INDEX][4];	/* PlcNr PLC prog #, max. 1 top + 3 mot PLCs */

long	plcflag [MAX_INDEX][4];	/* Home, +Lim, -Lim, ...	*/
long	currpos	[MAX_INDEX][3];	/* [0]:X, [1]:Y, [2]:z		*/
long	targpos	[MAX_INDEX][3];
long	demapos	[MAX_INDEX][3];	

double	Offset	[MAX_INDEX][3];	/* [0]:X, [1]:Y, [2]:z		*/
double	Scale	[MAX_INDEX][3];
double	ForPar	[MAX_INDEX][7];	/* Frame-of-reference params	*/
double	Limits	[MAX_INDEX][6];	/* [0]:posX, [1]:negX, [2]:Y.. 	*/

				/* Orientations:		*/
				/* [0][0]=P1RT, [0][1]=P1PA	*/
				/* [1][0]=P2RT, [1][1]=P2PA	*/
int	RTPA_OriFlag	[2][2] = {{CWCCW, CWCCW},{CWCCW, CWCCW}};	

double	Rad_Toler  	[2]    = {0,0};	    /* Radial/Focus tolerance P1/P2 */
double	Foc_Toler  	[2]    = {0,0};
double corrparam[10][4];   /* params for torque and tilt correction formulas */

long lastPLCcomm[MAX_INDEX] ;  /* Last command  sent through doPLCcomm */

/*==========================================================================*/


/* every mech. can set and reset a gis event, which will be stored here. */ 
long gis_events [MAX_INDEX];
long gis_event;			/* outgoing GIS call stored here	*/
long gis_demand;		/* incoming GIS call stored here	*/
long gis_demand_hw;		/* hardware bits, not logical meaning	*/

long debugMode[2]={DEB_FULL,DEB_FULL};	/* Current debugging level */
/**
 **				debugMode[HRWFS]/[AG]
 **				    0 = ERROR
 **                                 1 = NONE (default)
 **                                     Logging but no debugging.
 **                                     Errors and warnings, plus important
 **                                     log messages.
 **                                 2 = MIN
 **                                     Minimum debugging.
 **                                     Errors, warnings, log messages, plus
 **                                     supplemental information.
 **                                 3 = FULL
 **                                     Full debugging. All messages.
 **/


long simuMode[2] = {SIM_NONE,SIM_NONE};	/* Current simulation level */
/** 
 **				simuMode[HRWFS]/[AG]
 **                                 0 = NONE
 **                                 1 = VSM
 **                                 2 = FAST
 **                                 3 = FULL
 **/

char mechstrs [MAX_INDEX][MAX_STRING_SIZE];
char sadstrs  [MAX_INDEX][MAX_STRING_SIZE];
char menustrs [MAX_INDEX][MAXMENUSTR][MENUSTRSIZE];	
		/* max. 16 strings a' 20 in menu  */

/* max. MAX_LUTpcnt additional LUT strings */
char   LUTplus     [MAX_INDEX][MAX_LUTpcnt][MAX_STRING_SIZE]; 
long   LUTplusPos  [MAX_INDEX][MAX_LUTpcnt][3];	/* up to 3 dims	*/
long   LUTpluscount[MAX_INDEX];
char   logmenustrs [2][MAXLOGSET][MENUSTRSIZE];	/* max.30 strings a' 20 per logger */

word *pDP1, *pDP2;			/* for tests of DPRam only	*/


/*==========================================================================*/

long init_globvars (void)

{
int i, j;

debugMode[0] = debugMode[0] = DEB_FULL;

pDP1 = (word*)pmacRamAddr (0, 0xd000);	/* Access to DPRAM with pDP[44].. */
pDP2 = (word*)pmacRamAddr (1, 0xd000);

/*==========================================================================*/

for (i=0; i<MAX_INDEX; i++)
{
  LUTpluscount[i]=0;
  lastPLCcomm[i] = -1 ;

  for (j=0; j<MAX_LUTpcnt; j++)
  {
    LUTplus   [i][j][0] = 0;		/* delete additional LUT strings */
    LUTplusPos[i][j][0] = 0;		/* delete pos. of 3 dims	 */
    LUTplusPos[i][j][1] = 0;
    LUTplusPos[i][j][2] = 0;
  }

  for (j=0; j<16; j++)	menustrs [i][j][0] = 0;

  ForPar [i][0] = 0;			/* Radius RT		*/
  ForPar [i][1] = 0;			/* x-translation	*/
  ForPar [i][2] = 0;			/* y-translation	*/
  ForPar [i][3] = 0;			/* x-scale		*/
  ForPar [i][4] = 0;			/* y-scale		*/
  ForPar [i][5] = 100;			/* tolerance- real	*/
  ForPar [i][6] = 0;			/* Arm length           */

  gis_events [i] = 0;
}

/*==========================================================================*/

strncpy (mechstrs [pimg],	pimg_str, 	MAX_STRING_SIZE);
strncpy (mechstrs [lens],	lens_str, 	MAX_STRING_SIZE);
strncpy (mechstrs [clfilter],	clfilter_str,	MAX_STRING_SIZE);
strncpy (mechstrs [ndfilter],	ndfilter_str,	MAX_STRING_SIZE);
strncpy (mechstrs [fldstop],	fldstop_str,	MAX_STRING_SIZE);
strncpy (mechstrs [cal],	cal_str,	MAX_STRING_SIZE);
strncpy (mechstrs [focus],	focus_str,	MAX_STRING_SIZE);

strncpy (mechstrs [ag_sf],	ag_sf_str,	MAX_STRING_SIZE);
strncpy (mechstrs [ag_hw],	ag_hw_str,	MAX_STRING_SIZE);
strncpy (mechstrs [ag_ao],	ag_ao_str,	MAX_STRING_SIZE);

strncpy (mechstrs [p1_probe],	p1_probe_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p1_focus],	p1_focus_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p1_filter],	p1_filter_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p1_fldstop],	p1_fldstop_str,	MAX_STRING_SIZE);

strncpy (mechstrs [p2_probe],	p2_probe_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p2_focus],	p2_focus_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p2_filter],	p2_filter_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p2_fldstop],	p2_fldstop_str,	MAX_STRING_SIZE);


strncpy (mechstrs [p1_RT4],	p1_RT4_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p1_PA4],	p1_PA4_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p2_RT3],	p2_RT3_str,	MAX_STRING_SIZE);
strncpy (mechstrs [p2_PA3],	p2_PA3_str,	MAX_STRING_SIZE);

strncpy (mechstrs [ag_RT2],	ag_RT2_str,	MAX_STRING_SIZE);
strncpy (mechstrs [ag_Tilt],	ag_Tilt_str,	MAX_STRING_SIZE);
strncpy (mechstrs [ag_Lin2],	ag_Lin2_str,	MAX_STRING_SIZE);

strncpy (mechstrs [ag_PA3AO],	ag_PA3AO_str,	MAX_STRING_SIZE);


strncpy (mechstrs [hrwfs_cc],	hrwfs_cc_str,	MAX_STRING_SIZE);
strncpy (mechstrs [ag_cc],	ag_cc_str,	MAX_STRING_SIZE);

/*==========================================================================*/



strncpy (sadstrs [pimg],	pimg_sadstr, 		MAX_STRING_SIZE);
strncpy (sadstrs [lens],	lens_sadstr, 		MAX_STRING_SIZE);
strncpy (sadstrs [clfilter],	clfilter_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [ndfilter],	ndfilter_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [fldstop],	fldstop_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [cal],		cal_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [focus],	focus_sadstr,		MAX_STRING_SIZE);

strncpy (sadstrs [ag_sf],	ag_sf_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [ag_hw],	ag_hw_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [ag_ao],	ag_ao_sadstr,		MAX_STRING_SIZE);

strncpy (sadstrs [p1_probe],	p1_probe_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [p1_focus],	p1_focus_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [p1_filter],	p1_filter_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [p1_fldstop],	p1_fldstop_sadstr,	MAX_STRING_SIZE);

strncpy (sadstrs [p2_probe],	p2_probe_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [p2_focus],	p2_focus_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [p2_filter],	p2_filter_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [p2_fldstop],	p2_fldstop_sadstr,	MAX_STRING_SIZE);


strncpy (sadstrs [p1_RT4],	p1_RT4_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [p1_PA4],	p1_PA4_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [p2_RT3],	p2_RT3_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [p2_PA3],	p2_PA3_sadstr,		MAX_STRING_SIZE);

strncpy (sadstrs [ag_RT2],	ag_RT2_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [ag_Tilt],	ag_Tilt_sadstr,		MAX_STRING_SIZE);
strncpy (sadstrs [ag_Lin2],	ag_Lin2_sadstr,		MAX_STRING_SIZE);

strncpy (sadstrs [ag_PA3AO],	ag_PA3AO_sadstr,	MAX_STRING_SIZE);



strncpy (sadstrs [hrwfs_cc],	hrwfs_cc_sadstr,	MAX_STRING_SIZE);
strncpy (sadstrs [ag_cc],	ag_cc_sadstr,		MAX_STRING_SIZE);

/*==========================================================================*/


  #if 0
    PPmac = &PlcNr;
    for (i=,i<sizeof(PlcNr),i++) 	/* sizeof results in Byte or Longs / Ints ? */
      *(PPmac + i) = 0;			/* better sizeof(PlcNr)*sizeof(PlcNr[0][0] ? */
  #endif
/*==========================================================================*/

for   (i=0; i<MAX_INDEX; i++)
  for (j=0; j< 4       ; j++)
    PlcNr[i][j] = 0;
/*==========================================================================*/

/* PMAC 1	*/	
PlcNr [p1_RT4]		[0]	= 1;	/* low level mech	*/
PlcNr [p1_PA4]		[0]	= 2;	/* low level mech	*/
PlcNr [ag_RT2]		[0]	= 3;	/* low level mech	*/
PlcNr [ag_Tilt]		[0]	= 4;	/* low level mech	*/
PlcNr [ag_Lin2]		[0]	= 5;	/* low level mech	*/

PlcNr [p1_focus]	[0]	= 6;
PlcNr [p1_fldstop]	[0]	= 7;
PlcNr [p1_filter]	[0]	= 8;
					/* 9..11: HD torque		*/
PlcNr [p1_probe]	[0]	= 9;	/* high level mech: PLC 1,2	*/
PlcNr [p1_probe]	[1]	= 1;
PlcNr [p1_probe]	[2]	= 2;
PlcNr [p1_probe]	[3]	= 6;

PlcNr [ag_sf]		[0]	= 10;	/* high level mech: PLC 3,4,5	*/
PlcNr [ag_sf]		[1]	= 3;
PlcNr [ag_sf]		[2]	= 4;
PlcNr [ag_sf]		[3]	= 5;

PlcNr [clfilter]	[0]	= 12;	
PlcNr [ndfilter]	[0]	= 13;
PlcNr [focus]		[0]	= 14;
					/* 15: Lin2Enc, free	*/
/* PMAC 2	*/			
PlcNr [p2_RT3]		[0]	= 17;	/* low level mech	*/
PlcNr [p2_PA3]		[0]	= 18;	/* low level mech	*/
PlcNr [ag_PA3AO]	[0]	= 19;	/* low level mech	*/

PlcNr [ag_hw]		[0]	= 20;
PlcNr [lens]		[0]	= 21;
PlcNr [p2_focus]	[0]	= 22;
PlcNr [p2_fldstop]	[0]	= 23;
PlcNr [p2_filter]	[0]	= 24;
					/* 25..28: free	*/
					/* 29/30: HD torque, former 25/26 */
PlcNr [p2_probe]	[0]	= 25;	/* high level mech: PLC 1,2	*/
PlcNr [p2_probe]	[1]	= 17;
PlcNr [p2_probe]	[2]	= 18;
PlcNr [p2_probe]	[3]	= 22;

PlcNr [ag_ao]		[0]	= 27;	/* high level mech: PLC 1,3	*/
PlcNr [ag_ao]		[1]	= 17;
PlcNr [ag_ao]		[2]	= 19;

PlcNr [cal]		[0]	= 29;	/* not a separate channel - PLC13 */
PlcNr [pimg]		[0]	= 31;	/* formerly 27	*/
PlcNr [fldstop]		[0]	= 32;	/* formerly 28	*/

/* getcard will automatically bring card 1 for CC mechindex.
 **  doPLCcomm will do both PMACs anyway
 */

PlcNr [hrwfs_cc]	[0]	= 36;	/* global dat/park: PLC20 (36-16) */
/*PlcNr[hrwfs_cc]	[1]	= 36;*/	/* special: means   PLC20 / PMAC1 */ 
PlcNr [ag_cc]		[0]	= 37;	/* global dat/park: PLC21 (37-16) */
/*PlcNr[ag_cc]		[1]	= 37;*/	/* special: means   PLC21 / PMAC1 */

/*==========================================================================*/

for   (i=0; i<MAX_INDEX; i++)
  for (j=0; j< 6       ; j++)
    Limits[i][j] = 0;


/* Multi dimensional mechs sequence: RT,PA or RT,Tilt,Lin	*/
/*==========================================================================*/
/* offsets in real world coordinates!	
 * Offset = Pos. of logic zero, expressed in real coord.
 */

Offset [pimg]		[0] = 0;
Offset [lens]		[0] = 0;
Offset [clfilter]	[0] = 0;
Offset [ndfilter]	[0] = 0;
Offset [fldstop]	[0] = 0;
Offset [cal]		[0] = 0;
Offset [focus]		[0] = 0;
 
Offset [ag_hw]		[0] = 0;

Offset [p1_focus]	[0] = 0;
Offset [p1_filter]	[0] = 0;
Offset [p1_fldstop]	[0] = 0;

Offset [p2_focus]	[0] = 0;
Offset [p2_filter]	[0] = 0;
Offset [p2_fldstop]	[0] = 0;

Offset [p1_RT4]		[0] = 0;
Offset [p1_PA4]		[0] = 0;
Offset [p2_RT3]		[0] = 0;
Offset [p2_PA3]		[0] = 0;

Offset [ag_RT2]		[0] = 0;
Offset [ag_Tilt]	[0] = 0;
Offset [ag_Lin2]	[0] = 0;

Offset [ag_PA3AO]	[0] = 0;

/* --------------------------------------------------------------------	*/
/* M-D sequence: RT,PA or RT,Tilt,Lin	*/

Offset [ag_sf]		[0] = Offset[ag_RT2] [0];	/* 3D	*/
Offset [ag_sf]		[1] = Offset[ag_Tilt][0];	/* 3D	*/
Offset [ag_sf]		[2] = Offset[ag_Lin2][0];	/* 3D	*/

Offset [ag_ao]		[0] = Offset[p2_RT3]  [0];	/* 2D	*/
Offset [ag_ao]		[1] = Offset[ag_PA3AO][0];	/* 2D	*/

Offset [p1_probe]	[0] = Offset[p1_RT4][0];	/* 3D	*/
Offset [p1_probe]	[1] = Offset[p1_PA4][0];	/* 3D	*/
Offset [p1_probe]	[2] = Offset[p1_focus][0];	/* 3D	*/

Offset [p2_probe]	[0] = Offset[p2_RT3][0];	/* 3D	*/
Offset [p2_probe]	[1] = Offset[p2_PA3][0];	/* 3D	*/
Offset [p2_probe]	[2] = Offset[p2_focus][0];	/* 3D	*/


/*==========================================================================*/

Scale [pimg]		[0] = 1000;			/* mm...	*/
Scale [lens]		[0] = 1000;
Scale [clfilter]	[0] = 536.6666;			/* degree	*/
Scale [ndfilter]	[0] = 536.6666;
Scale [fldstop]		[0] = 227.5555;			/* mm		*/
Scale [cal]		[0] = 1;			/* logical units */
Scale [focus]		[0] = 95040;			/* mm		*/
 
Scale [ag_hw]		[0] = 10000;
 
Scale [p1_focus]	[0] = 99648;			/* mm		*/
Scale [p1_filter]	[0] = 227.5555;			/* degree...	*/
Scale [p1_fldstop]	[0] = 227.5555;

Scale [p2_focus]	[0] = 99648;			/* mm		*/
Scale [p2_filter]	[0] = 227.5555;			/* degree...	*/
Scale [p2_fldstop]	[0] = 227.5555;

Scale [p1_RT4]		[0] = 41111.1111;		/* degree...	*/
Scale [p1_PA4]		[0] = 10000;
Scale [p2_RT3]		[0] = 41111.1111;
Scale [p2_PA3]		[0] = 10000;

Scale [ag_RT2]		[0] = 41111.1111;
Scale [ag_Tilt]		[0] = 10000;
Scale [ag_Lin2]		[0] = 1000;			/* mm		*/

Scale [ag_PA3AO]	[0] = 10000;			/* degree	*/

/* --------------------------------------------------------------------	*/
/* Multi dimensional mech. sequence: RT,PA or RT,Tilt,Lin	*/

Scale [ag_sf]		[0] = Scale[ag_RT2] [0];	/* 3D	*/
Scale [ag_sf]		[1] = Scale[ag_Tilt][0];	/* 3D	*/
Scale [ag_sf]		[2] = Scale[ag_Lin2][0];	/* 3D	*/

Scale [ag_ao]		[0] = Scale[p2_RT3]  [0];	/* 2D	*/
Scale [ag_ao]		[1] = Scale[ag_PA3AO][0];	/* 2D	*/

Scale [p1_probe]	[0] = Scale[p1_RT4][0];		/* 3D	*/
Scale [p1_probe]	[1] = Scale[p1_PA4][0];		/* 3D	*/
Scale [p1_probe]	[2] = Scale[p1_focus][0];	/* 3D	*/

Scale [p2_probe]	[0] = Scale[p2_RT3][0];		/* 3D	*/
Scale [p2_probe]	[1] = Scale[p2_PA3][0];		/* 3D	*/
Scale [p2_probe]	[2] = Scale[p2_focus][0];	/* 3D	*/


/*==========================================================================*/
for (i=0; i<MAX_INDEX; i++)
  for (j=0; j<6; j++)
    Limits [i][j] = 0;			/* defaults are written later	*/

Limits [pimg]		[0] =  31;			/* 31000*/
Limits [pimg]		[1] = -11.5;
Limits [lens]		[0] =  37;
Limits [lens]		[1] = -6.1;
Limits [clfilter]	[0] =  720;			/* 193600 * 2	*/
Limits [clfilter]	[1] = -720;
Limits [ndfilter]	[0] =  720;
Limits [ndfilter]	[1] = -720;
Limits [fldstop]	[0] =  113;
Limits [fldstop]	[1] = -19;
Limits [cal]		[0] =  1;
Limits [cal]		[1] =  0;
Limits [focus]		[0] =  11.57;			/* 1100000	*/
Limits [focus]		[1] = -1.05;			/* -100000	*/

Limits [ag_hw]		[0] =  46.9;			/* outside	*/
Limits [ag_hw]		[1] = -27.1;			/* inside	*/
 
Limits [p1_focus]	[0] =  18.77;			/* 1870000	*/
Limits [p1_focus]	[1] = -3.01;			/* -300000	*/
Limits [p1_filter]	[0] =  720;			/* 82000 * 2	*/
Limits [p1_filter]	[1] = -720;
Limits [p1_fldstop]	[0] =  720;
Limits [p1_fldstop]	[1] = -720;

Limits [p2_focus]	[0] =  18.77;
Limits [p2_focus]	[1] = -3.01;
Limits [p2_filter]	[0] =  720;
Limits [p2_filter]	[1] = -720;
Limits [p2_fldstop]	[0] =  720;
Limits [p2_fldstop]	[1] = -7202;

Limits [p1_RT4]		[0] =  223;
Limits [p1_RT4]		[1] = -223;
Limits [p1_PA4]		[0] =  90;			/* inside, 900000	*/
Limits [p1_PA4]		[1] = -25;			/* outside	*/
Limits [p2_RT3]		[0] =  223;
Limits [p2_RT3]		[1] = -223;
Limits [p2_PA3]		[0] =  90;			/* inside	*/
Limits [p2_PA3]		[1] = -25;			/* outside	*/

Limits [ag_RT2]		[0] =  223;
Limits [ag_RT2]		[1] = -223;
Limits [ag_Tilt]	[0] =  45;			/* up, 425000	*/
Limits [ag_Tilt]	[1] = -45;			/* down		*/
Limits [ag_Lin2]	[0] =  0;
Limits [ag_Lin2]	[1] = -316;

Limits [ag_PA3AO]	[0] = +30;			/* inside	*/
Limits [ag_PA3AO]	[1] = -47;			/* outside	*/

/* --------------------------------------------------------------------	*/

Limits [ag_sf]		[0] = Limits[ag_RT2] [0];	/* 3D	*/
Limits [ag_sf]		[1] = Limits[ag_RT2] [1];	/* 3D	*/
Limits [ag_sf]		[2] = Limits[ag_Tilt][0];	/* 3D	*/
Limits [ag_sf]		[3] = Limits[ag_Tilt][1];	/* 3D	*/
Limits [ag_sf]		[4] = Limits[ag_Lin2][0];	/* 3D	*/
Limits [ag_sf]		[5] = Limits[ag_Lin2][1];	/* 3D	*/

Limits [ag_ao]		[0] = Limits[p2_RT3]  [0];	/* 2D	*/
Limits [ag_ao]		[1] = Limits[p2_RT3]  [1];	/* 2D	*/
Limits [ag_ao]		[2] = Limits[ag_PA3AO][0];	/* 2D	*/
Limits [ag_ao]		[3] = Limits[ag_PA3AO][1];	/* 2D	*/

Limits [p1_probe]	[0] = Limits[p1_RT4][0];	/* 3D	*/
Limits [p1_probe]	[1] = Limits[p1_RT4][1];	/* 3D	*/
Limits [p1_probe]	[2] = Limits[p1_PA4][0];	/* 3D	*/
Limits [p1_probe]	[3] = Limits[p1_PA4][1];	/* 3D	*/
Limits [p1_probe]	[4] = Limits[p1_focus][0];	/* 3D	*/
Limits [p1_probe]	[5] = Limits[p1_focus][1];	/* 3D	*/

Limits [p2_probe]	[0] = Limits[p2_RT3][0];	/* 3D	*/
Limits [p2_probe]	[1] = Limits[p2_RT3][1];	/* 3D	*/
Limits [p2_probe]	[2] = Limits[p2_PA3][0];	/* 3D	*/
Limits [p2_probe]	[3] = Limits[p2_PA3][1];	/* 3D	*/
Limits [p2_probe]	[4] = Limits[p2_focus][0];	/* 3D	*/
Limits [p2_probe]	[5] = Limits[p2_focus][1];	/* 3D	*/

/*==========================================================================*/

ForPar [p1_probe]	[0] = 400.00;			/* Rad. RT4/mm	*/
ForPar [p1_probe]	[1] = 0;			/* FOR x   /mm	*/
ForPar [p1_probe]	[2] = 0;			/* FOR y   /mm	*/
ForPar [p1_probe]	[3] =-1;			/* FOR x Scale	*/
ForPar [p1_probe]	[4] =-1;			/* FOR y Scale	*/
ForPar [p1_probe]       [6] = 400.0;                    /* Probe arm /mm */

ForPar [p2_probe]	[0] = 400.00;			/* Rad. RT3/mm	*/
ForPar [p2_probe]	[1] = 0;			/* FOR x   /mm	*/
ForPar [p2_probe]	[2] = 0;			/* FOR y   /mm	*/
ForPar [p2_probe]	[3] = 1;			/* FOR x Scale	*/
ForPar [p2_probe]	[4] = 1;			/* FOR y Scale	*/
ForPar [p2_probe]       [6] = 400.0;                    /* Probe arm /mm */

/*==========================================================================*/


return 0;
}			/* init_globvars */

