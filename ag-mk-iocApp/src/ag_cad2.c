/*static char rcsid[]="$Id: ag_cad2.c,v 1.8 2013/05/06 10:39:13 gemvx Exp $"; */

/*
 *  FILENAME
 *  -------- 
 *  ag_cad2.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all the functions used by the
 *  A&G probe arm and tracking mode CAD records. These functions are used 
 *  to validate the arguments given to the CAD records.
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  long followsub		( struct genSubRecord *pgsub );
 *  long CADfollow		( struct cadRecord *pcad ) ;
 *  long CADtoleranceInit	( struct cadRecord *pcad ) ;
 *  long CADtolerance		( struct cadRecord *pcad ) ;
 *  long CADsetOrientInit	( struct cadRecord *pcad ) ;
 *  long CADsetOrient		( struct cadRecord *pcad ) ;
 *  long CADunwrap		( struct cadRecord *pcad ) ;
 *  long CADflip		( struct cadRecord *pcad ) ;
 *  long CADloggInit		( struct cadRecord *pcad ) ;
 *  long CADlogg		( struct cadRecord *pcad ) ;
 *
 *  REQUIREMENTS
 *  ------------
 *  The names of the subroutines in this file should be identical to those
 *  declared in the SNAM field of each CAD record. If a change is made to
 *  the name of a subroutine, that change should be reflected in the SNAM
 *  field, and vice versa.
 *
 *  The ordering of the arguments within each CAD record (A, B, C...) is
 *  defined in the description of the interface between the CAD database
 *  and its clients. Changes to that interface should be reflected in this
 *  file.
 *
 *  The input arguments for each CAD record (A, B, C...) are all strings.
 *  However, the data type of each output argument (VALA, VALB, VALC...)
 *  is determined by the (FTVA, FTVB, FTVC....) fields in the CAD record.
 *  The data types assumed here must match those declared in the CAD
 *  record properties
 *
 *  LIMITATIONS
 *  ------------
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth (ocf)
 * 
 *  HISTORY
 *  -------
 *  22-Mar-1998: Initial version				(ocf)
 *
 */

/* *INDENT-OFF* */
/*
 * $Log: ag_cad2.c,v $
 * Revision 1.8  2013/05/06 10:39:13  gemvx
 * ----------------------------------------------------------------------
 * Committing in .
 *
 * Modified Files: (REL-466)
 * 	src/ag/ag_cad.c: updated with new agXy2ab parameters.
 * 	src/ag/ag_cad2.c: updated with new agXy2ab parameters.
 * 	src/ag/ag_define.h
 * 	src/ag/ag_test.c: updated with new agXy2ab parameters.
 * 	src/ag/ag_track.c: updated with new agXy2ab parameters.
 * 	src/ag/ag_utils.c : new agXy2ab implementation. Now it check
 * 	if there's a new track ID in order to avoid the premature
 * 	PWFS2 RT unwrap.
 * ----------------------------------------------------------------------
 *
 * Revision 1.7  2003/11/10 14:10:13  gemvx
 * Set slew flag to get busy/idle transition when followingag_cad2.c
 *
 * Revision 1.6  2001/08/14 14:00:17  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.5  2001/01/15 14:39:18  cjm
 * Replace calls to xy_2_alphabeta with agXy2ab and improve layout
 *
 * Revision 1.4  2000/12/20 13:40:13  cjm
 * remove unnecessary tabs
 *
 * Revision 1.3  2000/05/06 04:28:13  cboyer
 * New version of Olaf V3-2 5May 2000
 *
 * Revision 1.2  2000/03/18 06:40:05  cjm
 * Acceptance test version
 *
 * Revision 1.1.1.1  1998/08/05 21:16:16  Gemini
 * Initial creation of the Gemini A&G repository
 *
 */
/* *INDENT-ON* */

#include  <ag_define.h>		/* names for mechanisms */

/* ====================================================================	*/
#define crude 	(*(long*)pgsub->a)

long followsub( struct genSubRecord *pgsub )
{
  char messages[80];		/* Message buffer 	*/
  long eng[3], sample, card, motor, foc_index;	

  long mechindex = query_cadname (pgsub->name);

      if (getsimu (mechindex)==SIM_NONE)
      {
	if   ( mechindex == p2_probe )	foc_index = p2_focus;
	else { mechindex =  p1_probe;	foc_index = p1_focus; }

	card  = getcard (foc_index, 0);
        motor = getplcn (foc_index, 0);
	
	get2DPRam (TrEPsam, card, 0, &sample);	/* last written sample */
	sample = lim (sample, 0, MAXSAM-1);

	get2DPRamDP (TrPosStart + 3*sample+0, card, 0, &(eng[0])); /* X */
	get2DPRamDP (TrPosStart + 3*sample+1, card, 0, &(eng[1])); /* Y */
	get2DPRamDP (TrPosStart + 3*sample+2, card, 0, &(eng[2])); /* Z */

/* for focus, it's only necessary to prepare the position and command the probe,
 * because in following, focus will be treated as a 3d dim to probe.
 */
	if (motor>0)  
	  putDPRamDP(PosStart+motor, eng[2],card,0);	/* give focus pos*/

      }

  if (crude > 0)
    doPLCcomm (mechindex, C_Crude, eng);             /* "Crude foll" */
  else
    doPLCcomm (mechindex, C_Foll , eng);             /* "Follow" */

  sprintf( messages, "\t%s\t- accepted/PLCcomm done. crude=%ld",
           pgsub->name, crude); 
  agLogMessage ( mechindex, DEB_MIN, messages);

  return 0;
}

#undef crude

/* ====================================================================	*/
/* on CRUDETRACKING:
 * follow switches interpol only to 0.5 Hz (else to 20Hz).
 * follow doesn't switch on following with PLC command.
 * interpol copies last of 10 samples to PLC-commanded pos. (with command).
 */
/* a:		crude (=1: crude tracking) 
 * b:		mark  (=1: samples available)
 * vala:	crude tracking enabled (=1: crude tracking) 
 * valb:	SCAN of interpol record (20Hz/Pass.)
 */

long CADfollow( struct cadRecord *pcad ) 
{
  char messages[80];     		/* Message buffer 	*/
  long status = CAD_ACCEPT;      	/* return status 	*/
  long cvstat1, cvstat2;		/* conversion status	*/
  double mark, crude;			/* =1: samples avail.	*/
  /* long eng[3], sample, card, motor, foc_index;	*/

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */
  if   (mechindex == p2_probe) ;
  else  mechindex =  p1_probe;

  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:

	if (getGIS()) 
	{
	  status = CAD_REJECT;
	  sprintf( messages, "GIS is active!"); 
 	  strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
	  sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	  agLogMessage( mechindex, DEB_ERROR,  messages);
	}

      	cvstat1 = sscanf( pcad->b, "%lf", &mark );

        if (( cvstat1 == 1 ) && !check_numeric(pcad->b))
        { 

/* 3/7/99: Test on "enough data" must not be made in the new version where  
* the followA record is enabled on a follow command and disabled on a stop. 			*/
/*
 *	  if (mark!=0)
 *	  {
 *	    sprintf( messages, "\t%s\t- enough data available, mark=%g", pcad->name, mark);
 *	    agLogMessage( mechindex, DEB_MIN, messages);
 *	  }
 *	  else
 *	  { 
 *	    status = CAD_REJECT;
 *	    sprintf( messages, "not enough data, mark=%g", mark); 
 *	    strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
 *	    sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
 * 	    agLogMessage( mechindex, DEB_MIN, messages);
 *	  }
*/
        }
        else
        { status = CAD_REJECT;
	  sprintf(messages, "mark not numeric: (%s)", pcad->b);
          strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
          sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
 	  agLogMessage( mechindex, DEB_ERROR, messages);
  	}
	
    break;

    case menuDirectiveSTART:
      cvstat2 = sscanf( pcad->a, "%lf", &crude );
      *(long*) pcad->vala = (crude > 0)? 1 : 0;
      *(long*) pcad->valb = SCAN20hz;			/* actual start	*/
      if (mechindex == p1_probe) {
	agSetSlew (1) ;
      } else {
        agSetSlew (2) ;
      }
    break;

    case menuDirectiveSTOP:
      CADStop (pcad);					/* Comm. "Stop"	*/
    break;
  }							/* switch	*/
  return status;
}							/* CADfollow */

/* ====================================================================	*/

long CADtoleranceInit( struct cadRecord *pcad ) 
{
/*  char messages[80];     	*/			/* Message buffer */
  long status = CAD_ACCEPT;      	/* return status  */

  long mechindex = query_cadname(pcad->name);	/* does all default actions */

     if (mechindex < p2_probe)
      { 
	*(double*) pcad->vala  =  Rad_Toler [0];	/* P1:RT */
        *(double*) pcad->valb  =  Foc_Toler [0];

        *(double*) pcad->vala  =  ForPar [p1_probe][5];
        *(double*) pcad->valb  =  ForPar [p1_focus][5];
	sprintf  ( pcad->a, "%g", Rad_Toler [0]);
	sprintf  ( pcad->b, "%g", Foc_Toler [0]);
      }
      else
      {
	*(double*) pcad->vala  =  Rad_Toler [1];
        *(double*) pcad->valb  =  Foc_Toler [1];	/* P2:PA */

        *(double*) pcad->vala  =  ForPar [p2_probe][5];
        *(double*) pcad->valb  =  ForPar [p2_focus][5];
	sprintf  ( pcad->a, "%g", Rad_Toler [1]);
	sprintf  ( pcad->b, "%g", Foc_Toler [1]);
      }

  return status;
}				/* CADOrientInit */

/* ====================================================================	*/

#define TolLimR	200
#define TolLimF	20

long CADtolerance( struct cadRecord *pcad ) 
{
  char messages[80];     	/* Message buffer	*/
  long cvstat1;			/* conversion status	*/
  long cvstat2;			/* conversion status	*/
  double tola, tolb;
  long status = CAD_ACCEPT;	/* return status	*/

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:

      cvstat1 = sscanf( pcad->a, "%lf", &tola );
      cvstat2 = sscanf( pcad->b, "%lf", &tolb );

      if (( cvstat1 == 1 ) && !check_numeric(pcad->a) &&
	  ( cvstat2 == 1 ) && !check_numeric(pcad->b) &&
	  ( fabs (tola) < TolLimR) && (fabs (tolb) < TolLimF) )
      { 
        *(double*) pcad->vala = tola;
        *(double*) pcad->valb = tolb;

	sprintf( messages, "\t%s\t- Requested tolerances = %3.2f, %3.2f", pcad->name, tola, tolb );
	agLogMessage( mechindex, DEB_MIN, messages);
      }
      else
      {
        if ( (cvstat1 != 1 ) || check_numeric(pcad->a) )
	  	sprintf(messages, "Rad. tol. not numeric: (%s)", pcad->a);
	else  if ( (cvstat2 != 1 ) || check_numeric(pcad->b) )
	  	sprintf(messages, "Foc. tol. not numeric: (%s)", pcad->b);
	else  if ( fabs (tola) >= TolLimR)
	  	sprintf(messages, "Rad. tol. > %d: %3.2f", TolLimR, tola);
	else	sprintf(messages, "Foc. tol. > %d: %3.2f", TolLimF, tolb);

        status = CAD_REJECT;
        strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
        sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
 	agLogMessage( mechindex, DEB_ERROR, messages);
      }

    break;

    case menuDirectiveSTART:

      if (mechindex < p2_probe)
      { Rad_Toler[0] = *(double*) pcad->vala;
	Foc_Toler[0] = *(double*) pcad->valb;
        ForPar [p1_probe][5] = *(double*) pcad->vala;
        ForPar [p1_focus][5] = *(double*) pcad->valb;
      }
      else
      { Rad_Toler[1] = *(double*) pcad->vala;
	Foc_Toler[1] = *(double*) pcad->valb;
        ForPar [p2_probe][5] = *(double*) pcad->vala;
        ForPar [p2_focus][5] = *(double*) pcad->valb;
      }

    break;

    case menuDirectiveCLEAR:						/* show currents on 	*/
	status = CADtoleranceInit (pcad);			/*  inputs and outputs!	*/
    break;

  }			/* switch	*/

  return status;
}				/* CADTolerance */


/* ====================================================================	*/

long CADsetOrientInit( struct cadRecord *pcad ) 
{
/*  char messages[80];     	*/	/* Message buffer */
  long status = CAD_ACCEPT;      	/* return status  */

  long mechindex = query_cadname(pcad->name);	/* does all default actions */

     if (mechindex < p2_probe)
      { *(double*) pcad->vala  =  RTPA_OriFlag [0][0];	/* P1:RT */
        *(double*) pcad->valb  =  RTPA_OriFlag [0][1];
        sprintf  ( pcad->a, "%s", ORI_str( RTPA_OriFlag [0][0]));
        sprintf  ( pcad->b, "%s", ORI_str( RTPA_OriFlag [0][1]));
      }
      else
      { *(double*) pcad->vala = RTPA_OriFlag [1][0];
        *(double*) pcad->valb = RTPA_OriFlag [1][1];	/* P2:PA */
        sprintf  ( pcad->a, "%s", ORI_str( RTPA_OriFlag [1][0]));
        sprintf  ( pcad->b, "%s", ORI_str( RTPA_OriFlag [1][1]));
      }

  return status;
}				/* CADOrientInit */

/* ====================================================================	*/


long CADsetOrient( struct cadRecord *pcad ) 
{
  char messages[80];     		/* Message buffer */
  long status = CAD_ACCEPT;      	/* return status  */

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */
  
  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:

      strntoupper((char*)pcad->a, 80);
      	if (strcmp( (char*)pcad->a, CW_str )   == 0) *(double*) pcad->vala = (double)CW;
  else	if (strcmp( (char*)pcad->a, CCW_str)   == 0) *(double*) pcad->vala = (double)CCW;
  else	if (strcmp( (char*)pcad->a, CWCCW_str) == 0) *(double*) pcad->vala = (double)CWCCW;
  else 
  { status = CAD_REJECT;
    if (strcmp( (char*)pcad->a, "") == 0)
		sprintf( messages, "No empty strings accepted (RT)!"); 
    else	sprintf( messages, "Unknown Orient mode (RT): %s", pcad->a); 
  }

      strntoupper((char*)pcad->b, 80);
 	if (strcmp( (char*)pcad->b, CW_str )   == 0) *(double*) pcad->valb = (double)CW;
  else	if (strcmp( (char*)pcad->b, CCW_str)   == 0) *(double*) pcad->valb = (double)CCW;
  else	if (strcmp( (char*)pcad->b, CWCCW_str) == 0) *(double*) pcad->valb = (double)CWCCW;
  else
  { status = CAD_REJECT;
    if (strcmp( (char*)pcad->b, "") == 0)
		sprintf( messages, "No empty strings accepted (PA)!"); 
    else	sprintf( messages, "Unknown Orient mode (PA): %s", pcad->b); 
  }

  if (status != CAD_ACCEPT)
  {
    status = CAD_REJECT;
    strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
    sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
    agLogMessage( mechindex, DEB_ERROR,  messages);
  }

    break;

    case menuDirectiveSTART:

      if (mechindex < p2_probe)
      { RTPA_OriFlag [0][0] = (int) *(double*) pcad->vala;	/* P1:RT */
        RTPA_OriFlag [0][1] = (int) *(double*) pcad->valb;
      }
      else
      { RTPA_OriFlag [1][0] = (int) *(double*) pcad->vala;
        RTPA_OriFlag [1][1] = (int) *(double*) pcad->valb;	/* P2:PA */
      }

    break;

    case menuDirectiveCLEAR:						/* show currents on 	*/
	status = CADsetOrientInit (pcad);			/*  inputs and outputs!	*/
    break;
  }			/* switch	*/
  return status;
}				/* CADOrient */

/* ====================================================================	*/
/* Start/Stop directives are given to Eng CAD record directly,	 
 * during tracking it's enough to switch the Orientations
 */
long CADflip( struct cadRecord *pcad ) 
{
  char   messages[80];     		/* Message buffer */
  long   status = CAD_ACCEPT;      	/* return status  */
  double target[3], dummy[3], current[3];
  double x,y,currpos;
  double RTpos,PApos,FOCpos;
  int    ori[2], p1p2index;
  long   proberesp;				/* probe response */
  long new_track_id = 0;

  long mechindex = CAD_default(pcad, &status);	

  sprintf ((char*)pcad->vala, "%.8g", 0.0);    /* output strings */
  sprintf ((char*)pcad->valb, "%.8g", 0.0);    /*   to "Eng" CAD */
  sprintf ((char*)pcad->valc, "%.8g", 0.0);
  *(long*)pcad->vald = 0;                      /* 0 = disable Eng CAD trigger */

    switch (pcad->dir)
    {
      case menuDirectiveMARK:
      case menuDirectiveSTOP:
	  switch (pcad->dir)			/* enable Eng CAD trigger */
   	  { case menuDirectiveMARK:	*(long*)pcad->vald =  8;   break;
   	    case menuDirectiveCLEAR:	*(long*)pcad->vald = 16;   break;
   	    case menuDirectivePRESET:	*(long*)pcad->vald = 32+7; break;
   	    case menuDirectiveSTART:	*(long*)pcad->vald = 64+7; break;
   	    case menuDirectiveSTOP:	*(long*)pcad->vald =128;   break;
	    default:		*(long*)pcad->vald =  8;   break;
	  }
      break;
    } 

  if (status == CAD_ACCEPT)
    switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
    {
      case menuDirectivePRESET:
      case menuDirectiveSTART:

	if (getGIS()) 
	{
	  status = CAD_REJECT;
	  sprintf( messages, "GIS is active!"); 
 	  strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
	  sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	  agLogMessage( mechindex, DEB_ERROR,  messages);
	}

	getpos (mechindex, current, dummy, target);
	RTpos  = eng2real (Scale[mechindex][0], Offset[mechindex][0], 
                           (long) target[0]);
	PApos  = eng2real (Scale[mechindex][1], Offset[mechindex][1], 
                           (long) target[1]);
	FOCpos = eng2real (Scale[mechindex][2], Offset[mechindex][2], 
                           (long) target[2]);

        agAb2xy (mechindex, RTpos, PApos, ForPar[mechindex], ori, &x, &y) ;

					/* RT Ori stays unchanged 	*/
	ori[1] = (ori[1] == CW) ? CCW:CW;	/* PA Ori changes	*/

        proberesp = getresponse (mechindex, 0);	/* are we tracking ? 	*/
		
        if ((proberesp == TRACK_ON) || (proberesp == CRUDE_ON ))
	{						  
	  if (pcad->dir == menuDirectiveSTART) /* just change PA ORI, don't give Move */
	  {
	    p1p2index = (mechindex <= p1_probe) ? 0 : 1; 
	    RTPA_OriFlag[p1p2index][1] = ori[1];
	    if (mechindex == p1_probe) {
	      agSetSlew(1) ;
            } else {
              agSetSlew(2) ;
            }
	  }
/* in tracking, "followA" or "interpol" always call agXy2ab with the
 * current setting of the ORIs. Changing those would cause the probe to 
 * flip/unwrap automatically without stopping the tracking.
 * Without tracking, we have to give a Move command to the PMAC.
 */
	}
	else
	{			/* if not tracking, give Move Eng command */
				/* calc. new eng pos. wrt. new armOrient  */
	  currpos = eng2real(Scale[mechindex][0], Offset[mechindex][0], 
                             current[0]);	  
          agXy2ab (mechindex, new_track_id,  x, y, ForPar[mechindex], Limits[mechindex],
                   ori, currpos, &RTpos, &PApos) ;

	  RTpos  = real2eng (Scale[mechindex][0], Offset[mechindex][0], RTpos);
	  PApos  = real2eng (Scale[mechindex][1], Offset[mechindex][1], PApos);
	  FOCpos = target[2];

	  sprintf ((char*)pcad->vala, "%.8g", RTpos);	/* output strings */
	  sprintf ((char*)pcad->valb, "%.8g", PApos);	/* to "Eng" CAD	*/
 	  sprintf ((char*)pcad->valc, "%.8g", FOCpos);

	  switch (pcad->dir)			/* enable Eng CAD trigger */
   	  { case menuDirectiveMARK:	*(long*)pcad->vald =  8;   break;
   	    case menuDirectiveCLEAR:	*(long*)pcad->vald = 16;   break;
   	    case menuDirectivePRESET:	*(long*)pcad->vald = 32+7; break;
   	    case menuDirectiveSTART:	*(long*)pcad->vald = 64+7; break;
   	    case menuDirectiveSTOP:	*(long*)pcad->vald =128;   break;
	    default:		*(long*)pcad->vald =  8;   break;
	  }
	}
      break;
  }				/* switch	*/
  return status;
}				/* CADFlip */

/* ====================================================================	*/
/* Start/Stop directives are given to Eng CAD record directly,	 
 * during tracking it's enough to switch the Orientations
 */
long CADunwrap( struct cadRecord *pcad ) 
{
  char messages[80];     		/* Message buffer */
  long   status = CAD_ACCEPT;      	/* return status  */
  double target[3], dummy[3], current[3];
  double x,y;
  double RTpos,PApos,FOCpos;
  int    ori[2], p1p2index;
  long   proberesp;			/* probe response */

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  sprintf ((char*)pcad->vala, "%.8g", 0.0);	/* output strings           */
  sprintf ((char*)pcad->valb, "%.8g", 0.0);	/*   to "Eng" CAD	    */
  sprintf ((char*)pcad->valc, "%.8g", 0.0);
  *(long*)pcad->vald = 0;                    /* 0 = disable Eng CAD trigger */

    switch (pcad->dir)
    {
      case menuDirectiveMARK:
      case menuDirectiveSTOP:
	  switch (pcad->dir)			/* enable Eng CAD trigger */
   	  { case menuDirectiveMARK:	*(long*)pcad->vald =  8;   break;
   	    case menuDirectiveCLEAR:	*(long*)pcad->vald = 16;   break;
   	    case menuDirectivePRESET:	*(long*)pcad->vald = 32+7; break;
   	    case menuDirectiveSTART:	*(long*)pcad->vald = 64+7; break;
   	    case menuDirectiveSTOP:	*(long*)pcad->vald =128;   break;
	    default:		*(long*)pcad->vald =  8;   break;
	  }
      break;
    } 

  if (status == CAD_ACCEPT)
    switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
    {
      case menuDirectivePRESET:
      case menuDirectiveSTART:
        if (getGIS()) 
        {
	  status = CAD_REJECT;
	  sprintf( messages, "GIS is active!"); 
 	  strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
	  sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	  agLogMessage( mechindex, DEB_ERROR,  messages);
        }

	getpos (mechindex, current, dummy, target);
	RTpos  = eng2real (Scale[mechindex][0], Offset[mechindex][0], 
                           (long) target[0]);
	PApos  = eng2real (Scale[mechindex][1], Offset[mechindex][1], 
                           (long) target[1]);
	FOCpos = eng2real (Scale[mechindex][2], Offset[mechindex][2], 
                           (long) target[2]);
						
        agAb2xy (mechindex, RTpos, PApos, ForPar[mechindex], ori, &x, &y) ;

					/* PA Ori stays unchanged 	*/
	ori[0] = (ori[0] == CW) ? CCW:CW;	/* RT Ori changes	*/

        proberesp = getresponse (mechindex, 0);		/* are we tracking ? */
		
        if ((proberesp == TRACK_ON) || (proberesp == CRUDE_ON ))
	{			/* just change PA ORI, don't give Move	*/
	  if (pcad->dir == menuDirectiveSTART		&&		
	     (RTpos >  360-Limits[mechindex][0] ||	/* > 140 ?	*/
	      RTpos < -360-Limits[mechindex][1] ))	/* <-140 ?      */
	  {
	    p1p2index = (mechindex <= p1_probe) ? 0 : 1; 
	    RTPA_OriFlag[p1p2index][0] = ori[0];
	  }
/* in tracking, "followA" or "interpol" always call agXy2ab with the
 * current setting of the ORIs. Changing those would cause the probe to 
 * flip/unwrap automatically without stopping the tracking.
 * Without tracking, we have to give a Move command to the PMAC.
 */
	}
	else			/* if not tracking, give Move Eng command */
	{	
	#if 0			/* 0 for complete ICD conform.	*/
	  if (RTpos <=  360-Limits[mechindex][0] &&	/* < 140 ? 	*/
	      RTpos >= -360-Limits[mechindex][1] ) ;	/* >-140 ? 	*/
          {
	    status = CAD_REJECT;			/* not in overlap! */
	    sprintf( messages, "Not in overlap!"); 
 	    strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
	    sprintf( messages, "\t%s\t- Reject: %s", pcad->name, pcad->mess);
	    agLogMessage( mechindex, DEB_ERROR,  messages);
          }
	#endif
	
	  if (status == CAD_ACCEPT)
      	  {			/* "0" says: use RT_Ori, if in overlap!	*/
	    if (RTpos >  360-Limits[mechindex][0] ||	/* > 140 ?	*/
	        RTpos < -360-Limits[mechindex][1] ) 	/* <-140 ?      */
	    {
				/* calc. new eng pos. wrt. new RTOrient	*/
	    /*  agXy2ab (mechindex, new_track_id, x, y, ForPar[mechindex], Limits[mechindex],
             *           ori, 0, &RTps, &PApos);   
	     * RTpos = real2eng (Scale[mechindex][0], Offset[mechindex][0], RTpos);
	     * PApos = real2eng (Scale[mechindex][1], Offset[mechindex][1], PApos);
	     */
	      FOCpos = target [2];
	      PApos  = target [1];
	      RTpos  = RTpos > 0 ? RTpos - 360 : RTpos + 360;
	      RTpos  = real2eng (Scale[mechindex][0], Offset[mechindex][0], RTpos);

	      sprintf ((char*)pcad->vala, "%.8g", RTpos); /* output strings */
	      sprintf ((char*)pcad->valb, "%.8g", PApos); /*   to "Eng" CAD */
	      sprintf ((char*)pcad->valc, "%.8g", FOCpos);

	      switch (pcad->dir)		/* enable Eng CAD trigger */
   	      { case menuDirectiveMARK:	  *(long*)pcad->vald =  8;   break;
   	        case menuDirectiveCLEAR:	  *(long*)pcad->vald = 16;   break;
   	        case menuDirectivePRESET:  *(long*)pcad->vald = 32+7; break;
   	        case menuDirectiveSTART:	  *(long*)pcad->vald = 64+7; break;
   	        case menuDirectiveSTOP:	  *(long*)pcad->vald =128;   break;
	        default:	  *(long*)pcad->vald =  8;   break;
	      }
	    }						/* in overlap	*/
	  }						/* no REJECT	*/
        }						/* not tracking	*/
      break;						/* cases	*/
    }							/* switch	*/
  return status;			
}							/* CADUnwrap 	*/


/*	ori[0] = (mechindex<=p1_probe)? RTPA_OriFlag[0][0]: RTPA_OriFlag[1][0];	 RT stays */
/* ====================================================================	*/

/* a:	filename			string
 * b:	start time in Unix sec		double
 * c:	duration in sec			double
 * d:	frequency of read		enum (long)
 * e:	set to be logged		long
 *
 * vala: filename			string
 * valb: start time in Unix sec		double
 * valc: end   time in Unix sec		double
 * vald: frequency of read		enum (long)
 * vale: logset				long
 * valf: frequency of read		enum (long) copy
 * valg: work directory (pwd)		string
 * valh: time of command		string
 *
 * calls flushlogfile and prepare_log from ag_logg.c!
 */

long CADloggInit( struct cadRecord *pcad ) 
{ 
  double t;

  getcwd( (char *)pcad->valg, MAX_STRING_SIZE );
  ((char *)pcad->valg)[MAX_STRING_SIZE-1] = 0;		/* terminate	*/
  bc635_read (&t);
  strcpy ((char*)pcad->valh, "startup:");
  tai2str ((char*)pcad->valh+strlen((char*)pcad->valh) , t);
  return CAD_ACCEPT;
}

long CADlogg( struct cadRecord *pcad ) 
{
  char messages[80];     			/* Message buffer */
  long cvstat1, cvstat2, cvstat3, cvstat4;	/* conversion status	*/
  double start, duration;
  long logset, scanrate;
  double t;
  
  long status = CAD_ACCEPT;      		/* return status  */

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  getcwd( (char *)pcad->valg, MAX_STRING_SIZE );
  ((char *)pcad->valg)[MAX_STRING_SIZE-1] = 0;		/* terminate	*/

  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:
      if ( *(char *) pcad->a == 0)			/* error could	*/
      { strcpy((char *) pcad->a,"ag_test.log");		/* be messaged	*/
      }

      cvstat1 = sscanf( pcad->b, "%lf", &start    );
      cvstat2 = sscanf( pcad->c, "%lf", &duration );
      cvstat3 = sscanf( pcad->d, "%ld",  &scanrate );
      cvstat4 = sscanf( pcad->e, "%ld",  &logset   );

      if (( cvstat1 == 1 ) && !check_numeric(pcad->b) &&
	  ( cvstat2 == 1 ) && !check_numeric(pcad->c) &&
	  ( cvstat3 == 1 ) && !check_numeric(pcad->d) &&
	  ( cvstat4 == 1 ) && !check_numeric(pcad->e) )
      {

        bc635_read (&t);	
	tai2str ((char*)pcad->valh, t);

	/* the following means:	absolute time if start>1e7
	 *			relative time if start>=0, <1e7
	 *			start=0 relative, if start<0
	 */

	if (start <= 1e7)				/* ca. 100 days	*/
	  start = start<=0 ? t : start+t;		/* if 0: actual time */

        strncpy (pcad->vala,pcad->a,MAX_STRING_SIZE);	/* filename	*/
        *(long  *) pcad->vale = logset;
        *(double*) pcad->valb = start;
	if (duration <= 0)  duration = 1.0e18;		/* endless	*/
  	*(double*) pcad->valc = start + duration;	/* end time	*/

        if (scanrate >= SCAN10s)
          *(long  *) pcad->valf = scanrate;
        else
	{
          *(long  *) pcad->valf = SCAN20hz;
          sprintf(messages, "Scanrate out of range");
          status = CAD_REJECT;
          strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
          sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
 	  agLogMessage( mechindex, DEB_ERROR, messages);
	}

        if ((logset>9) || (logset<0))
        {
          sprintf(messages, "Logset out of range");
          status = CAD_REJECT;
          strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
          sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
 	  agLogMessage( mechindex, DEB_ERROR, messages);
        }
      }
      else
      {
        sprintf(messages, "Parameter not valid");
        status = CAD_REJECT;
        strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
        sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
 	agLogMessage( mechindex, DEB_ERROR, messages);
      }

    break;

    case menuDirectiveSTART:
      prepare_log (pcad->a, *(long*)pcad->vale, 
		&(logsrcs[(mechindex == p1_probe)? 0:1]));	/* name, logset	*/
      *(long*) pcad->vald = *(long*)pcad->valf;			/* actual start	*/
    break;

    case menuDirectiveSTOP:
      *(long*) pcad->vald = SCANPass;
      flushlogfile(pcad->a, "a", 
		&(logsrcs[(mechindex == p1_probe)? 0:1]));
    break;

  }				/* switch	*/

  return status;
}				/* CADLogg */


/* ====================================================================	*/
