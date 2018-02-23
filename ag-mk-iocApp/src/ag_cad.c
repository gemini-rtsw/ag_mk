/*static char rcsid[]="$Id: ag_cad.c,v 1.12 2013/05/06 10:39:12 gemvx Exp $"; */

/*
 *  =====================================================================
 *   FILENAME
 *   -------- 
 *   ag_cad.c
 *
 *   PURPOSE
 *   -------
 *   This file contains the source for the functions used by the A&G
 *     mechanism CAD records. 
 *   The functions are used to validate the arguments given to the record.
 *
 *   FUNCTION NAME(S)
 *   ----------------
 *   CADSel     - Select
 *   CADMove    - Move mech to specified position
 *   CADEng     - Move mech to specified engineering position
 *   CADDatum   - Find mech's datum
 *   CADPark    - Park mech
 *
 *   long check_interlock 	(int mechindex, char * messages, int xpos);
 *   long CADSel		( struct cadRecord *pcad ); 
 *   long CADMove		( struct cadRecord *pcad ); 
 *   long CADEng		( struct cadRecord *pcad ); 
 *   long CADDefine		( struct cadRecord *pcad ); 
 *   long CADTest		( struct cadRecord *pcad ); 
 *   long CADStop		( struct cadRecord *pcad ); 
 *   long CADDatum		( struct cadRecord *pcad );
 *   long CADPark		( struct cadRecord *pcad ); 
 *   long PDsub			( struct genSubRecord *pgsub );
 *   long CAD_default  		( struct cadRecord  *pcad, long *pstatus);
 *   long correctionformula 	(double corrparam[10][4], double* x,  
 *				 double* y,  double* z, int mechindex)
 *
 *   REQUIREMENTS
 *   ------------
 *   The names of the subroutines in this file should be identical to those
 *   declared in the SNAM field of each CAD record. If a change is made to
 *   the name of a subroutine, that change should be reflected in the SNAM
 *   field, and vice versa.
 *
 *   The ordering of the arguments within each CAD record (A, B, C...) is
 *   defined in the description of the interface between the CAD database
 *   and its clients. Changes to that interface should be reflected in this
 *   file.
 *
 *   The input arguments for each CAD record (A, B, C...) are all strings.
 *   However, the data type of each output argument (VALA, VALB, VALC...)
 *   is determined by the (FTVA, FTVB, FTVC....) fields in the CAD record.
 *   The data types assumed here must match those declared in the CAD
 *   record properties
 *
 *   LIMITATIONS
 *   ------------
 *
 *   AUTHOR
 *   ------
 *   Steven Beard    (smb, smb@roe.ac.uk)
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 * 
 *   HISTORY
 *   -------
 *   28-Mar-1996: Original version with just CADSelect.              (smb)
 *   16-Apr-1996: Add CADMoveEng, CADDatum and
 *                CADPark.                                     	     (smb)
 *   16-Apr-1996: CADMoveEng renamed due to 15 character
 *                subroutine name length restriction in the
 *                CAD record.                                        (smb)
 *   03-May-1996: Modified to use CAD_ACCEPT/REJECT constants.       (smb)
 *   07-May-1996: All subroutine names shortened to reflect shorter
 *                names for CAD records. (I was hitting the 29
 *                character EPICS record name length limit as well
 *                as the 15 character subroutine name limit).        (smb)
 *   15-May-1996: Documentation tidied up.                           (smb)
 *   06-Jun-1996: Headers converted to Gemini standard format, as
 *                described in SPE-C-G0009. Functions CADinit and
 *                CADreset added.                                    (smb)
 *   12-Jun-1996: EPICS 3.12.2.Gem3 installed, plus latest IGPO
 *                extensions. CAD records now have a "MARK"
 *                directive.                                         (smb)
 *   19-Jun-1996: Headers modified to make them compatible with
 *                the "wflman" utility.                              (smb)
 *   25-Jun-1996: CADSel and CADPark modified to generate
 *                engineering position as output (in preparation
 *                for the use of lookup tables later).               (smb)
 *   11-Jul-1996: CAD records are not allowed to report anything
 *                other than reasons for failure through the MESS
 *                field. Diagnostic messages removed.                (smb)
 *   02-Aug-1996: Modified to make use of "lutin" and "lutout"
 *                records, so the CAD records no longer need to
 *                process lookup tables themselves.                  (smb)
 *   11-Oct-1996: Split into "syscad" and "cad". "cad" will
 *                eventually be made more generic.                   (smb)
 *   11-Oct-1996: TEMPORARY SLIT VERSION                             (smb)
 *   24-Oct-1996: Slit menu made unique                              (smb)
 *   04-Dec-1996: "printf" replaced by "cicsLogMessage" or
 *                "cicsLogLong".                                     (smb)
 *   10-Jan-1997: Problem with converting CAD outputs to anything
 *                other than a string fixed.                         (smb)
 *   1-Jun-1997:  Name changed to Cad.c. Made generic version, 
 *		  but without LUT-access			     (ocf)
 *   22-Jul-1997: Several CAD routines added and changed.
 *		  Utility routines added.			     (ocf)
 *
 */

/* *INDENT-OFF* */
/*
 * $Log: ag_cad.c,v $
 * Revision 1.12  2013/05/06 10:39:12  gemvx
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
 * Revision 1.11  2012/09/18 03:33:58  gemvx
 * merge f2 branch, implement p1/p2 flexure compensation
 *
 * Revision 1.9  2001/12/14 03:04:46  ajf
 * Automatic sequencing of the optical encoders.
 *
 * Revision 1.8  2001/12/13 05:29:26  ajf
 * Bugs found during testing of the sequencing of the optical encoders
 *
 * Revision 1.7  2001/12/13 04:03:42  ajf
 * Changes for the automatic switching on/off of the optical encoder
 *
 * Revision 1.6  2001/08/14 14:00:17  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.5  2001/01/15 14:37:00  cjm
 * Replace call to xy_2_alphabeta with agXy2ab
 *
 * Revision 1.4  2000/12/20 13:33:38  cjm
 * Many changes to remove tabs etc. and make code readable. Remove unnecessary checks on simulation mode
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

#include  <ag_define.h>		/* names for mechanisms etc. */

static long check_interlock (int mechindex, char *messages, int xpos) ;
static long correctionformula (double corrparam[10][4], double *x,
                               double *y, double *z, int mechindex) ;
/*+
 *  =====================================================================
 *   Function name:
 *   check_interlock - Check interlocking situation for either mechanism.
 *
 *   Purpose:
 *   This routine is called whenever CAD record of a mechanism wants to check
 *   whether the mechanism can be moved or if there is another mechanism
 *   blocking the move (indicated by the opposite mech's home switch).
 *
 *   Invocation:
 *   status = check_interlock (int mechindex, char * messages, int xpos);
 *
 *   Parameters in:
 *      >= mechindex  	int   	  global A&G mechanism index
 *      >= xpos		int	  actual x position of the mechanism
 *                                
 *   Parameters out:
 *      < messages    *string     string with cause of interlock situation
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Globals:
 *      External functions:
 *        getsimu(mechindex);
 *        getswitch(mechindex);
 *
 *      External variables:
 *         plcflag[][];
 *
 *   Requirements:
 *   It is assumed the plcflag array is always updated from the PMAC values.
 *
 *   Limitations:
 *   None
 *
 *   Author:
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 *
 *   History:
 *   01-Aug-1997: original version   				(ocf)
 *
 *-
 */

long check_interlock (int mechindex, char * messages, int xpos)
{
  if (getsimu(mechindex) == SIM_NONE) 
  {
	if (mechindex == p2_probe || mechindex == p2_PA3) 
 	  if (!(plcflag[ag_PA3AO][0] & HOMEFLAG))
	  { strcpy(messages, "AO blocks PWFS2");
	    return (CAD_REJECT);
	  }
	if (mechindex == ag_ao || mechindex == ag_PA3AO)
 	  if (!(plcflag[p2_PA3][0] & HOMEFLAG))
	  { strcpy(messages, "PWFS2 blocks AO");
	    return (CAD_REJECT);
	  }

	if (mechindex == lens)
	  if (!(plcflag[pimg][0] & HOMEFLAG))
	  { strcpy(messages, "Pimg blocks lens");
	    return (CAD_REJECT);
	  }
	if (mechindex == pimg)
	  if (!(plcflag[lens][0] & HOMEFLAG))
	  { strcpy(messages, "Lens blocks pimg");
	    return (CAD_REJECT);
	  }

	if (mechindex == ag_hw)
	  if (!(getswitch(cal) & HOMEFLAG))	/* pol.unit home not pressed (bit=0) ?	*/
	  { strcpy(messages, "Polarimetry unit blocks HRWFS");
	    return (CAD_REJECT);
	  }

	/* originally. Rejects should be checked and considered also for SF (top level mechanism), but that's too complicated	*/
	if (mechindex == ag_Tilt)
	  if (/* (plcflag[ag_RT2] [0] & HOMEFLAG) || */	/* checkpoint pressed (bit=1) ?	*/
	      (plcflag[ag_Tilt][0] & HOMEFLAG) )	/* serv.pos.  pressed (bit=1) ?	*/
	  { strcpy(messages, "Cannot move tilt in check/serv. pos.");		/* that are 36 chars	*/
	    return (CAD_REJECT);
	  }
	if (mechindex == ag_Lin2)			
	  if (!(plcflag[ag_Lin2][0] & HOMEFLAG) && 	/* tilt not perpend.  (bit=0) ?	*/
	       (plcflag[ag_RT2 ][0] & HOMEFLAG) &&	/* checkpoint pressed (bit=1) ?	*/
		xpos < currpos[ag_Lin2][0])
	  { strcpy(messages, "Cannot move Lin: Tilt is not perp.");
	    return (CAD_REJECT);
	  }
  }
  return (CAD_ACCEPT);
}

/*+
 *  =====================================================================
 *   Function name:
 *   CADSel - Check acceptability of "select" command.
 *
 *   Purpose:
 *   This routine is called whenever a mechanism's Sel CAD record is
 *   processed. It checks that the arguments are valid and the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Sel is the command for positioning a mechanism after named positions 
 *   taken from a LUT (look up table).
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADSel( pcad );
 *
 *   Parameters in:
 *      >= pcad->dir   *string    CAD directive
 *      >= pcad->a     *string    CAD input argument A
 *                                = mechanism's target position name
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *      < pcad->vala  *string     CAD output value A = name demand for LUT
 *      < pcad->valb  long        index for Eng CAD record of LUTplus Array+1 
 *                                  which was found to be valid
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Globals:
 *      External functions:
 *        CAD_default();
 *        queryLUT():
 *        agLogMessage();
 *        getGIS();
 *
 *      External variables:
 *         LUTplus[][];
 *         LUTpluscount[];
 *
 *   Note:
 *   The CAD record will check whether the given name is part of the 
 *   lookup table contained in a connected lut record. It will further check 
 *   whether the name can be found in the c-internal name table which can be
 *   filled with the "Define" command.
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Limitations:
 *   None
 *
 *   Author:
 *   Steven Beard    (smb, smb@roe.ac.uk)
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 *
 *   History:
 *   29-Mar-1996: Original version, based on the TCS prototype and
 *                the CAD skeleton provided by Andy Foster.          (smb)
 *   15-Apr-1996: Fix syntax errors.                                 (smb)
 *   07-May-1996: Relax command acceptance criteria.                 (smb)
 *   25-Jun-1996: Convert string given to engineering position as if
 *                translated by a lookup table.                      (smb)
 *   02-Aug-1996: The name is now converted to an engineering
 *                position using a "lutout" record. However, the old
 *                if-then-else structure remains for the time being
 *                to check the name is valid.                        (smb)
 *
 *-
 */

long CADSel( struct cadRecord *pcad ) 
{
  char messages[80];     		/* Message buffer */
  long status = CAD_ACCEPT;      	/* return status */
  int i;

  long mechindex = CAD_default(pcad, &status);

  if (status == CAD_ACCEPT)
  switch (pcad->dir)
  {
	/* CAD PRESET directive detected. Check the name given with the
	 * command and, if acceptable, write it to the CAD output.
	 */
    case menuDirectivePRESET:

	sprintf( messages, "\t%s\t- Requested = %s", pcad->name, pcad->a);
	agLogMessage( mechindex, DEB_FULL, messages);

	status = queryLUT (pcad);
	
		/* querying LUTplus always allows redefining of LUT items.  */
        for (i = 0; i < LUTpluscount[mechindex]; i++)
          if (strncmp (pcad->a, LUTplus[mechindex][i], MENUSTRSIZE) == 0)
            break;				/* stop for-loop 	*/

        if (i < LUTpluscount[mechindex])	/* name recognised 	*/
	{ status = CAD_ACCEPT;
	  *(long*)pcad->valb = i+1;	/* message to EngCAD, which is called later */
	}

	if (status!=CAD_ACCEPT)
	{ status = CAD_REJECT;
	  sprintf( messages, "Invalid name: %s", pcad->a); 
	}

	if (getGIS()) 
	{ status = CAD_REJECT;
	  sprintf( messages, "GIS is active!"); 
	}

	if (mechindex != ag_Lin2 && status == CAD_ACCEPT)		
	  status =  check_interlock (mechindex, messages, 0);		

     	if (status == CAD_ACCEPT)
	{ strncpy( pcad->vala, pcad->a, MAX_STRING_SIZE );	/* default action for all mechs */
	  ( (char*)pcad->vala) [MAX_STRING_SIZE-1] = 0;
        } else {                                           /* CAD_REJECT */
          status  = CAD_REJECT;
	  ((char*)pcad->vala) [0] = 0;
 
	  strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
	  pcad->mess [MAX_STRING_SIZE-1] = 0;
	  sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	  agLogMessage( mechindex, DEB_ERROR,  messages);
        }
    break;

    case menuDirectiveSTART:                              /* don't reset Eng mark */
    break;

    default:
      *(long*)pcad->valb = 0;                       /* reset EngCad mark */
    break;	

  }                                                            /* switch */

  if (status != CAD_ACCEPT)  strcpy( pcad->vala, "");

  return status;
}                                                              /* CADSel */
/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   CADMove 
 *
 *   Purpose:
 *   Check acceptability of "Move" command.
 *
 *   Description:
 *   This routine is called whenever a mechanism's Move CAD record is
 *   processed. It checks that the arguments are valid and the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Move is the command for positioning a mechanism in real
 *   world coordinates.
 *
 *   Invocation:
 *   status = CADMove( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad     (struct cadRecord *)  Pointer to cad record
 *
 *   Epics inputs:
 *   dir =>  CAD directive
 *   a   =>  Demanded x position (mm) 
 *   b   =>  Demanded y position (mm) 
 *   c   =>  Demanded z position (mm) 
 *
 *   Epics outputs:
 *   mess => failure message written to CAD MESS field
 *   vala => X demand (engineering units)
 *   valb => Y demand (engineering units)
 *   valc => Z demand (engineering units)
 *
 *   Function value:
 *   (<)  status      long        Status value written to CAD VAL field
 *
 *   External functions:
 *   agLogMessage     (ag_define) Macro to log a message
 *   getGIS           (ag_utils)  Return the GIS demand
 *   eng2real         (ag_utils)  Convert encoder to real units
 *   real2eng         (ag_utils)  Convert real to encoder units
 *   agXy2ab          (ag_utils)  Convert x,y to alpha, beta
 *   check_numeric    (ag_mem)    Check if input string is numeric
 *
 *   External variables:
 *   (>) Limits [][]   (double)     Limits of mechanisms
 *
 *   Prior requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Limitations:
 *   None
 *
 *   Author:
 *   Steven Beard    (smb, smb@roe.ac.uk)
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 *
 *   History:
 *   29-Mar-1996: Original version, based on the TCS prototype and
 *                the CAD skeleton provided by Andy Foster.          (smb)
 *   16-Dec-1996: Focus version.                                     (smb)
 *   10-Jan-1997: Problem of copying CAD output to anything other
 *                than a string fixed.                               (smb)
 *   29-Nov-2000: Fix bug that offsets and scales were applied twice (cjm)
 *                and remove ridiculous tabbing and layout 
 *-
 */

#define	xLIMP  Limits [mechindex][0]
#define	xLIMN  Limits [mechindex][1]
#define	yLIMP  Limits [mechindex][2]
#define	yLIMN  Limits [mechindex][3]
#define	zLIMP  Limits [mechindex][4]
#define	zLIMN  Limits [mechindex][5]

long CADMove( struct cadRecord *pcad ) 
{
  char messages[80];	/* Message buffer */
  long cvstat1;		/* conversion status */
  long cvstat2;		/* conversion status */
  long cvstat3;		/* conversion status */

  double xpos;		/* real world x-position */
  double ypos;		/* real world y-position */
  double zpos;          /* real world z-position */
  double rdiff;          /* Difference between probe and bearing radius */

  double curr, radius, x, y;                    /* only needed for PFWS  */

  long status = CAD_ACCEPT;	                /* return status */
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */
  long new_track_id = 0; /* new track ID flag. */

  int dims  = getdims (mechindex);	

  messages[0] = 0;                              /* clear logmessage */	

  if (status == CAD_ACCEPT)		
  switch (pcad->dir)
  {

	/* CAD PRESET directive detected. Check the command arguments and, if
	 * acceptable, copy them to the CAD outputs.
	 *
	 * Check the input argument was successfully converted. (cvstat 
	 * contains the number of items that "sscanf" has successfully  
	 * converted, and there should be 1).
	 */

    case menuDirectivePRESET:

      cvstat3 = sscanf( pcad->c, "%lf", &zpos );
      cvstat2 = sscanf( pcad->b, "%lf", &ypos );
      cvstat1 = sscanf( pcad->a, "%lf", &xpos );


      if ( (mechindex == p1_probe) ||     /* Limits are already in degrees, */
           (mechindex == p2_probe) )      /* but xpos/ypos are in mm!       */
      {
        if (!messages[0]) {
	  sprintf(messages, "\t%s\t- Requested x/y  = %5s %5s", pcad->name,
                  pcad->a, pcad->b );
	  agLogMessage( mechindex, DEB_FULL, messages);
	}

	#define RADIUS_RT	ForPar[mechindex][0]
	#define X_OFFSET	ForPar[mechindex][1]
	#define Y_OFFSET	ForPar[mechindex][2]
	#define X_SCALE		ForPar[mechindex][3]
	#define Y_SCALE		ForPar[mechindex][4]
	#define ARM_LENGTH      ForPar[mechindex][6] 

 /*  RADIUS_RT is just the radius of the mounting point of the probe arm; 
  *  it's not the physically allowable maximum radius at the PA limit switch.
  *  It may be allowable to drive outside RADIUS_RT since this may or 
  *  may not be within the limits.
  */
        x = xpos ;
        y = ypos ;
  	radius = sqrt(x*x+y*y);	
        rdiff = RADIUS_RT - ARM_LENGTH ;
        if (rdiff < 0.0) rdiff = -rdiff ;
        if (radius > RADIUS_RT) {
          status=CAD_REJECT;
          sprintf(messages, "Radius %3.1f too large (>%3.1f)", radius,
                  RADIUS_RT);
        }
        if (radius < rdiff) {
          status=CAD_REJECT; 
          sprintf(messages, "Radius %3.1f too small (<%3.1f)", radius,
          rdiff);
        }

	curr = eng2real(Scale[mechindex][0], Offset[mechindex][0],
                        currpos[mechindex][0]);	  
        agXy2ab (mechindex, new_track_id, xpos, ypos, ForPar[mechindex], Limits[mechindex],
		(mechindex<=p1_probe)? RTPA_OriFlag[0]: RTPA_OriFlag[1], curr,
                &xpos, &ypos);
      }

     switch (dims)
     {	case 3: 
        if (zpos<zLIMN || zpos>zLIMP) {
          status=CAD_REJECT;
          sprintf(messages, "Z out of range %3.1f,%3.1f: %3.1f",
                  zLIMN, zLIMP, zpos);
        }
	case 2:
        if (ypos<yLIMN || ypos>yLIMP) {
          status=CAD_REJECT;
          sprintf(messages, "Y out of range %3.1f,%3.1f: %3.1f",
                  yLIMN, yLIMP, ypos);
        }
	case 1:  
        if (xpos<xLIMN || xpos>xLIMP) {
          status=CAD_REJECT; 
          sprintf(messages, "X out of range %3.1f,%3.1f: %3.1f",
                  xLIMN, xLIMP, xpos);
        }
     }
     switch (dims)
     {	case 3: 
        if (cvstat3 != 1) {
          status=CAD_REJECT; 
          sprintf(messages, "Cannot read Z: (%s)", pcad->c);
        }
     	case 2:  
        if (cvstat2 != 1) {
          status=CAD_REJECT; 
          sprintf(messages, "Cannot read Y: (%s)", pcad->b);
        }
     	case 1:  
        if (cvstat1 != 1) {
          status=CAD_REJECT; 
          sprintf(messages, "Cannot read X: (%s)", pcad->a);
        }
     }
     switch (dims)
     {	case 3:  
        if (check_numeric(pcad->c)) {
          status=CAD_REJECT; 
          sprintf(messages, "Z not numeric: (%s)", pcad->c);
        }
	case 2:  
        if (check_numeric(pcad->b)) {
          status=CAD_REJECT; 
          sprintf(messages, "Y not numeric: (%s)", pcad->b);
        }
	case 1:  
        if (check_numeric(pcad->a)) {
          status=CAD_REJECT; 
          sprintf(messages, "X not numeric: (%s)", pcad->a);
        }
     }

      if (getGIS()) {
        status = CAD_REJECT;
        sprintf( messages, "GIS is active!"); 
      }

      if (status == CAD_ACCEPT)             /* decision about interlocks */
        status = check_interlock (mechindex, messages,
                 real2eng (Scale[mechindex][0], Offset[mechindex][0], xpos));		

      if (status == CAD_ACCEPT)             /*  Pos. in range */
      {      
	*(long *)pcad->vala = real2eng (Scale[mechindex][0],
                                        Offset[mechindex][0], xpos);
	*(long *)pcad->valb = real2eng (Scale[mechindex][1],
                                        Offset[mechindex][1], ypos);
	*(long *)pcad->valc = real2eng (Scale[mechindex][2], 
                                        Offset[mechindex][2], zpos);
/* Set EngCad mark, so that correction formula in CADEng can be done 	*/
	*(long *)pcad->vald = 1000;

	switch (dims) {
     	case 3:  
          sprintf(messages, "\t%s\t- Req. pos. = %3.1f %3.1f %3.1f (accepted)",
                  pcad->name, xpos, ypos, zpos ); 
          break;
     	case 2:  
          sprintf(messages, "\t%s\t- Req. pos. = %3.1f %3.1f (accepted)",
                  pcad->name, xpos, ypos );
          break;
     	case 1:  
          sprintf(messages, "\t%s\t- Requested pos. = %3.1f (accepted)",
                  pcad->name, xpos );
          break;
	default: messages[0] = 0;
          break;
        }
	if (messages[0] != 0)
	  agLogMessage( mechindex, DEB_FULL, messages);

     } else  {                                            /* CAD_REJECT */
        status  = CAD_REJECT;
        *(long *)pcad->vala = 0;
        *(long *)pcad->valb = 0;
        *(long *)pcad->valc = 0;
        *(long *)pcad->vald = 0;                   /* reset EngCad mark */
	strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
	pcad->mess [MAX_STRING_SIZE-1] = 0;
	sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	agLogMessage( mechindex, DEB_ERROR,  messages);
      }

    break;

    case menuDirectiveSTART:                            /* don't reset Eng mark */
    break;

    case menuDirectiveCLEAR:
	*(long*)pcad->c	= 0;        /* strings are now "empty strings" */
	*(long*)pcad->d	= 0;        /* doubles are not completely cleared */
	*(long*)pcad->valc = 0;     /* smaller data than longs could be */
	*(long*)pcad->vald = 0;     /* dangerous                        */
	db_post_events( pcad, &pcad->c, 1) ;
	db_post_events( pcad, &pcad->d,   1 );
	db_post_events( pcad, pcad->valc, 1 );
	db_post_events( pcad, pcad->vald, 1 );
    break;

    default:
       *(long*)pcad->vald = 0;     /* reset EngCad mark */
    break;	

  }
  return status;
}                                                          /* CADMove */

#undef	xLIMP
#undef	xLIMN
#undef	yLIMP
#undef	yLIMN
#undef	zLIMP
#undef	zLIMN

/* ===================================================================== */
long correctionformula (double corrparam[10][4], double* x,  double* y,
                        double* z, int mechindex)
{
  if (mechindex==ag_sf	)
  {			}
  if (mechindex==ag_Tilt)
  {			}
  if (mechindex==ag_Lin2)
  {			}

  return (0);
}

/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   CADEng 
 *
 *   Purpose:
 *   Check acceptability of "Eng" command.
 *
 *   Description:
 *   This routine is called whenever a mechanism's MoveEng CAD record is
 *   processed. It checks that the arguments are valid and the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Eng is the command for positioning a mechanism to
 *   a location specified in engineering units.
 *
 *   Invocation:
 *   status = CADEng( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad     (struct cadRecord *)  Pointer to cad record
 *
 *   Epics inputs:
 *   dir   =>   CAD directive
 *   a     =>   X demand (encoder units)
 *   b     =>   Y demand (encoder units)
 *   c     =>   Z demand (encoder units)
 *
 *   Epics outputs:
 *   mess  =>   failure message written to CAD MESS field
 *   vala  =>   dimension X
 *   valb  =>   dimension Y
 *   valc  =>   dimension Z
 *
 *   Function value:
 *   (<) status      long        Status value written to CAD VAL field
 *
 *   Prior requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Limitations:
 *   None
 *
 *   Author:
 *   Steven Beard    (smb, smb@roe.ac.uk)
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 *
 *   History:
 *   16-Apr-1996: Original version.                                (smb)
 *   07-May-1996: Relax command acceptance criteria.               (smb)
 *   15-May-1996: Check engineering position is within range.
 *                I tried making pcad->vala "long" rather than
 *                "string" but for some reason the value would not
 *                copy from "pos" to "pcad->vala". Until the
 *                problem is resolved I have gone back to
 *                declaring the output as a string.                (smb)
 *   10-Jan-1997: Problem of copying CAD output to anything other
 *                than a string fixed.                             (smb)
 *   30-Nov-2000  Get rid of unnecessary tabbing                   (cjm)
 *
 *-
 */

/* CAD PRESET directive detected. Check the command arguments and, if
 * acceptable, copy them to the CAD outputs.
 * Check the input argument was successfully converted. (cvstat contains the
 * number of items that "sscanf" has successfully converted, and there
 * should be 1).
 */

#define XLIMP real2eng (Scale[mechindex][0], Offset[mechindex][0], \
                        Limits[mechindex][0])
#define XLIMN real2eng (Scale[mechindex][0], Offset[mechindex][0], \
                        Limits[mechindex][1])
#define YLIMP real2eng (Scale [mechindex][1], Offset [mechindex][1], \
                        Limits [mechindex][2])
#define YLIMN real2eng (Scale [mechindex][1], Offset [mechindex][1], \
                        Limits [mechindex][3])
#define ZLIMP real2eng (Scale [mechindex][2], Offset [mechindex][2], \
                        Limits [mechindex][4])
#define ZLIMN real2eng (Scale [mechindex][2], Offset [mechindex][2], \
                        Limits [mechindex][5])

long CADEng( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	*/
  long cvstat1, cvstat2, cvstat3, cvstat4;	/* conversion status 	*/
  long Demands[3];				/* for transfer only 	*/
  double LUTplusMark;				/* pcad->d from SelCAD	*/		

  long xLIMP, xLIMN;
  long yLIMP, yLIMN;
  long zLIMP, zLIMN;

  double xpos;					/* x- Eng position 	*/
  double ypos;					/* y- Eng position 	*/
  double zpos;					/* z- Eng position 	*/

/* Attention! Prior to the last variable declaration no simple statement! */
  long status    = CAD_ACCEPT;			/* return status 	*/
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  int 	dims = getdims (mechindex);

  xLIMP = gmax (XLIMP,XLIMN);	xLIMN = gmin (XLIMP,XLIMN);
  yLIMP = gmax (YLIMP,YLIMN);	yLIMN = gmin (YLIMP,YLIMN);
  zLIMP = gmax (ZLIMP,ZLIMN);	zLIMN = gmin (ZLIMP,ZLIMN);

  messages[0] = 0;				/* clear logmessage 	*/
      
  if (status == CAD_ACCEPT)
  switch (pcad->dir)
  {
    case menuDirectivePRESET:
 
      if (getGIS()) { 
        status = CAD_REJECT;
        sprintf( messages, "GIS is active!"); 
      }

      cvstat4 = sscanf( pcad->d, "%lf", &LUTplusMark );
      cvstat3 = sscanf( pcad->c, "%lf", &zpos );
      cvstat2 = sscanf( pcad->b, "%lf", &ypos );
      cvstat1 = sscanf( pcad->a, "%lf", &xpos );

/* to identify the source of a commanded position, LUTplusMark is used:
 * after Sel or Move, a correction is done
 */
      if ((cvstat4 == 1) && (LUTplusMark>0))	/* this will only be executed after Move and Sel commands */
      {			       /* this is to find a named pos. not in the LUT */
        if (LUTplusMark-1 < LUTpluscount[mechindex] &&
            LUTplusMark-1 < MAX_LUTpcnt) {
	  xpos = LUTplusPos[mechindex][(long)LUTplusMark-1][0];
	  ypos = LUTplusPos[mechindex][(long)LUTplusMark-1][1];
	  zpos = LUTplusPos[mechindex][(long)LUTplusMark-1][2];
        }

	correctionformula (corrparam, &xpos, &ypos, &zpos, mechindex);	
  	sprintf (messages, "%ld", (long) xpos);
	strncpy (pcad->a, messages, MAX_STRING_SIZE);
	sprintf (messages, "%ld", (long) ypos);
	strncpy (pcad->b, messages, MAX_STRING_SIZE);
	sprintf (messages, "%ld", (long) zpos);
	strncpy (pcad->c, messages, MAX_STRING_SIZE);
  	pcad->d[0] = 0;		/* reset mark from Sel, later done again*/
      }

     switch (dims) {
     case 3:  
        if (zpos<zLIMN || zpos>zLIMP)  {
          status=CAD_REJECT; 
          sprintf(messages, "Z out of range %ld,%ld: %ld", zLIMN, zLIMP,
                 (long)zpos);
        }
     case 2:  
        if (ypos<yLIMN || ypos>yLIMP)  {
          status=CAD_REJECT; 
          sprintf(messages, "Y out of range %ld,%ld: %ld", yLIMN, yLIMP,
                  (long)ypos);
        }
     case 1:  
        if (xpos<xLIMN || xpos>xLIMP)  {
          status=CAD_REJECT; 
          sprintf(messages, "X out of range %ld,%ld: %ld", xLIMN, xLIMP,
                  (long)xpos);
        }
     }
     switch (dims) {
     case 3:  
        if (cvstat3 != 1)  {
          status=CAD_REJECT; 
          sprintf(messages, "Cannot read Z: (%s)", pcad->c);
        }
     case 2:  
        if (cvstat2 != 1)  {
          status=CAD_REJECT; 
          sprintf(messages, "Cannot read Y: (%s)", pcad->b);
        }
     case 1:  
        if (cvstat1 != 1)  {
          status=CAD_REJECT; 
          sprintf(messages, "Cannot read X: (%s)", pcad->a);
        }
     }
     switch (dims) {
     case 3:
        if (check_numeric(pcad->c))  {
          status=CAD_REJECT; 
          sprintf(messages, "Z not numeric: (%s)", pcad->c);
        }
     case 2:  
        if (check_numeric(pcad->b))  {
          status=CAD_REJECT; 
          sprintf(messages, "Y not numeric: (%s)", pcad->b);
        }
     case 1:  
        if (check_numeric(pcad->a))  {
          status=CAD_REJECT; 
          sprintf(messages, "X not numeric: (%s)", pcad->a);
        }
     }

/***************  until here: decision about ranges     *****************/

      if (status == CAD_ACCEPT)
	  status =  check_interlock (mechindex, messages, xpos);

      if (status == CAD_ACCEPT)	                        /*  Pos. in range */
      {      
        *(long *)pcad->vala = (long) xpos;	/* 3 Dims hold for Start Dir. */
        *(long *)pcad->valb = (long) ypos;
        *(long *)pcad->valc = (long) zpos;

        Demands[0] = *(long *)pcad->vala;
        Demands[1] = *(long *)pcad->valb;
        Demands[2] = *(long *)pcad->valc;

	switch (dims) {
     	case 3:  
          sprintf(messages, "\t%s\t- Requested pos. = %ld %ld %ld (accepted)",
                  pcad->name, (long)xpos, (long)ypos, (long)zpos );
          break;
    	case 2:  
          sprintf(messages, "\t%s\t- Requested pos. = %ld %ld (accepted)",
                  pcad->name, (long)xpos, (long)ypos );
          break;
        case 1:  
          sprintf(messages, "\t%s\t- Requested pos. = %ld (accepted)",
                  pcad->name, (long)xpos );
          break;
        default: 
          messages[0] = 0 ;
          break ;
        }
	if (messages[0] != 0)
	  agLogMessage( mechindex, DEB_FULL, messages);
      }
      else					/* CAD_REJECT */
      { 
        status  = CAD_REJECT;
        *(long *)pcad->vala = 0;
        *(long *)pcad->valb = 0;
        *(long *)pcad->valc = 0;

	strncpy( pcad->mess, messages, MAX_STRING_SIZE );
	pcad->mess [MAX_STRING_SIZE-1] = 0;
	sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	agLogMessage( mechindex, DEB_ERROR,  messages);
      }
      break;

/* CAD START directive detected. The directive is being monitored by the SNL,
 *  which will do the appropriate action.
 */
    case menuDirectiveSTART:
    #if 0
      DemandPos[mechindex][0] = *(long *)pcad->vala;
      DemandPos[mechindex][1] = *(long *)pcad->valb;
      DemandPos[mechindex][2] = *(long *)pcad->valc;
    #endif

/* Why is this done here when its already been done in PRESET ? */
      Demands[0] = *(long *)pcad->vala;
      Demands[1] = *(long *)pcad->valb;
      Demands[2] = *(long *)pcad->valc;

      if (!(getGIS()))
      {
        if( ((mechindex == lens) || (mechindex == fldstop)) && 
            (!strcmp(pcad->e, "AUTOMATIC")) )
        {
/*          printf("cadENG: AUTOMATIC mode - switching encoder on\n"); */
          encoderSwitch(1);
        }
        doPLCcomm (mechindex, C_Move, &(Demands[0]));	/* Comm. "Move"	*/
      }
      break;

    case menuDirectiveSTOP:
        doPLCcomm (mechindex, C_Stop, NULL);            /* Comm. "Stop" */
/* Is lack of a break statement here a mistake or deliberate ? */
 

    case menuDirectiveCLEAR:
	*(long*)pcad->c 	= 0;	/* strings are now "empty strings" */
	*(long*)pcad->d 	= 0;	/* doubles are not completely cleared */
	*(long*)pcad->valc 	= 0;	/* smaller data than longs could be   */
	*(long*)pcad->vald 	= 0;	/* dangerous                          */
	db_post_events( pcad, &pcad->c,   1 );	
	db_post_events( pcad, &pcad->d,   1 );
	db_post_events( pcad, pcad->valc, 1 );
	db_post_events( pcad, pcad->vald, 1 );
        break;
  }

  pcad->d[0] 	= 0;				/* reset mark from Sel	*/

  return status;
}						/* CADEng */

/* Input D: Former the number of the LUT-Ouput values (INPD->LUT.NVAL):
 *  This value is valid after the first triggering of the LUT (0 before)
 * Triggering can't be done by PP at the Input, since in this case the LUT
 *  writes its values PP to the CAD inputs which is not wanted. 
 *  PP to the Park- LUT would work since the value is not used any way.
 * cvstat1 = sscanf( pcad->d, "%lf", &nval );
 * sprintf(messages, "\t%s\t- NVAL = %s (%ld)", pcad->name, pcad->d, (long) nval);
 * agLogMessage( mechindex, DEB_FULL, messages);
 */

/* ===================================================================== */
/*+
 *  =====================================================================
 *   Function name:
 *   CADDefine - Check acceptability of "Define" command.
 *
 *   Purpose:
 *   This routine is called whenever the Define CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Define is the command for renaming the current position of a 
 *   mechanism with a given name.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADDefine( pcad );
 *
 *   Parameters in:
 *      >= pcad->dir   *string     CAD directive
 *      >= pcad->a     *string     name for current position
 *
 *   Parameters out:
 *      <= pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      <= status      long        Status value written to CAD VAL field
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 *
 *   History:
 *   22-Jul-1997: Original version.                  (ocf)
 *
 *-
 */

long CADDefine( struct cadRecord *pcad ) 
{
  char messages[80];     /* Message buffer */
  long status = CAD_ACCEPT;         /* Initialise return status */
  long count;
  int  taskId;

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:

	if (strlen (pcad->a) < 1 )
	{
	  status = CAD_REJECT;
	  sprintf( messages, "Name to short (<1 char)");
	}
	if (strlen (pcad->a) > MENUSTRSIZE-1 )
	{
	  status = CAD_REJECT;
	  sprintf( messages, "Name to long (>%d char)", MENUSTRSIZE-1);
	}

	if (status == CAD_REJECT)
	{
	  strncpy( pcad->mess, messages, MAX_STRING_SIZE );
	  pcad->mess [MAX_STRING_SIZE-1] = 0;
	  sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
	  agLogMessage( mechindex, DEB_ERROR,  messages);
	}

    break;

    case menuDirectiveSTART:	/* CAD START directive detected.  */

	  count = LUTpluscount[mechindex];
	  if (count <= MAX_LUTpcnt)
	  {
	    strncpy (LUTplus[mechindex][count], pcad->a, MENUSTRSIZE-1);
	    LUTplus[mechindex][count][MENUSTRSIZE-1] = 0;

	    LUTplusPos[mechindex][count][0] = currpos[mechindex][0];	/* write pos.	*/
	    LUTplusPos[mechindex][count][1] = currpos[mechindex][1];
	    LUTplusPos[mechindex][count][2] = currpos[mechindex][2];
	    LUTpluscount [mechindex]++;
	    taskId = taskSpawn( pcad->name, 45, VX_FP_TASK, 8000, (FUNCPTR)updatemenustr,
			(int)mechindex,0, 0, 0, 0,0,0,0,0,0 );
    	    taskwdInsert (taskId, NULL, 0L);		/* updatemenustr (mechindex);	*/
	  }

	sprintf( messages, "\t%s\t- Requested name = %s, curr.pos = %ld %ld %ld", pcad->name, pcad->a, 
		currpos[mechindex][0], currpos[mechindex][1], currpos[mechindex][1]);
	agLogMessage( mechindex, DEB_FULL,  messages);

    break;
  }
  return status;
}			/* CADDefine */

/*	cvstat1 = sscanf( pcad->b, "%lf", &xpos );
 *	if (cvstat1 != 1)
 *	{
 *	  status = CAD_REJECT;
 *	  sprintf( messages, "Position %ld not valid", (long)xpos);
 *	}
 */

/* old: wire B to DPRead.VALC (target pos)
 *	xpos = ((double*)pcad->b)[0];
 *	ypos = ((double*)pcad->b)[1];
 *	zpos = ((double*)pcad->b)[2];
 *	*(long*) pcad->valb = xpos;
 */

/* ===================================================================== */


/*+
 *  =====================================================================
 *   Function name:
 *   CADTest - Check acceptability of "Test" command.
 *
 *   Purpose:
 *   This routine is called whenever the Test CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Test is the command for testing the mechanism.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADTest( pcad );
 *
 *   Parameters in:
 *	>= pcad->dir   *string     CAD directive
 *	>= pcad->a     *string	   argument
 *
 *   Parameters out:
 *      <= pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      <= status      long        Status value written to CAD VAL field
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Olaf Frischmuth (ocf, frischmuth@goepel.com)
 *
 *   History:
 *   22-Jul-1997: Original version.                  (ocf)
 *
 *-
 */

long CADTest( struct cadRecord *pcad ) 
{
  long status = CAD_ACCEPT;         /* Initialise return status */
  CAD_default(pcad, &status);	/* does all default actions */

  if (status == CAD_ACCEPT)
			/* Switch according to the CAD directive in DIR field */
  switch (pcad->dir)
  {
    case menuDirectiveSTART:

/* CAD START directive detected. Do nothing. The directive is being
 * monitored by the CICS sequence code, which will start the appropriate
 * action.
 */

    break;
  }
  return status;
}			/* CADTest */

/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   CADStop - Check acceptability of "Stop" command.
 *
 *   Purpose:
 *   This routine is called whenever a mechanism's Stop CAD record is
 *   processed. It checks that the command is acceptable and returns 
 *   a status and a message, which are written to the VAL and MESS 
 *   fields of the CAD record.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADStop( pcad );
 *
 *   Parameters in:
 *      >= pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      <= pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      <= status      long        Status value written to CAD VAL field
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Olaf Frischmuth  (Frischmuth.Goepel@t-online.de)
 *
 *   History:
 *   1-Jul-1998: Original version.                  (ocf)
 *
 *-
 */
/* used by both: Follow Stop and mech stop records	*/

long CADStop( struct cadRecord *pcad ) 
{
  long status = CAD_ACCEPT;                      /* Initialise return status */
  long mechindex = CAD_default(pcad, &status);   /* does all default actions */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)
  {

    case menuDirectiveSTART:
    case menuDirectiveSTOP:			/* in case of ag:p1/p2:Stop: */
	*(long*) pcad->valb = SCANPass;	/* for ag:p1/p2:interpol.SCAN */

        doPLCcomm (mechindex, C_SoftStop, NULL); /* Comm. "SoftStop" */
    break;

    case menuDirectiveCLEAR:
        doPLCcomm (mechindex, 0, NULL);  /* clear PLC response */
    break;
  }
  return status;
}			/* CADStop */

/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   CADDatum - Check acceptability of "Datum" command.
 *
 *   Purpose:
 *   This routine is called whenever the Datum CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Datum is the command for locating the selector's datum
 *   and initialising its coordinate system (assuming the selector
 *   is positioned by dead reckoning). The command has no arguments.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADDatum( pcad );
 *
 *   Parameters in:
 *      >= pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      <= pcad->mess   *string    failure message written to CAD MESS field
 * 	vala 		*string	   constant string/name for lutout
 * 	valc 		long 	   CAD_Accept in case of start directive
 * 	vald 		long 	   command for gensub 
 * 
 *   Return value:
 *      <= status      long        Status value written to CAD VAL field
 *
 *   Note:
 *   To really do the action, the record/routine uses another record/routine
 *   connected to it, "PDSub()"
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Olaf Frischmuth  (Frischmuth.Goepel@t-online.de)
 *
 *   History:
 *   22-Jul-1997: Original version.                  (ocf)
 *-
 */

#define PD_OK		44
#define PD_ACCEPT	99
#define PD_REJECT	0

long CADDatum( struct cadRecord *pcad ) 
{
  char messages[80];                            /* Message buffer */

  long status    = CAD_ACCEPT;                  /* Initialise return status */
  long mechindex = CAD_default(pcad, &status);  /* does all default actions */

  *(long*)pcad->valc = PD_REJECT;		/* default for gensub */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)
  {
			/* CAD PRESET directive detected. Arguments checking.
			 *  A mechanism is not allowed to move for datuming,
			 *  if another mechanism occupies the space.
	 		*/
    case menuDirectivePRESET:
      if (getGIS()) 
      { status = CAD_REJECT;
        sprintf( messages, "GIS is active!"); 
      }						/* decision about interlocks */
      else	status = check_interlock (mechindex, messages, 	
    	real2eng (Scale[mechindex][0], Offset[mechindex][0], 0));		

      if (status == CAD_ACCEPT)	
      { *(long*)pcad->valb = PD_OK;		/* for gensub */
        *(long*)pcad->vald = C_Datum;		/* for gensub */
        strcpy( pcad->a,    datumstr);		/* name for queryLUT */
        strcpy( pcad->vala, datumstr);		/* name for lutout */
      }
      else					/* CAD_REJECT */
      { status  = CAD_REJECT;
        strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
        pcad->mess [MAX_STRING_SIZE-1] = 0;
        sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
        agLogMessage( mechindex, DEB_ERROR,  messages);
      }
    break;

    case menuDirectiveSTART:
      if (*(long*)pcad->valb == PD_OK)
          *(long*)pcad->valc  = PD_ACCEPT;	/* for gensub */
    break;

    case menuDirectiveSTOP:
      doPLCcomm (mechindex, C_Stop, NULL);	/* Comm. "Stop" */
    break;
  }
  return status;
}						/* CADDatum */


/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   CADPark - Check acceptability of "Park" command.
 *
 *   Purpose:
 *   This routine is called whenever the Park CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   Park is the command for moving to park position and clamping the mechanism. 
 *   The command has no arguments.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADPark( pcad );
 *
 *   Parameters in:
 *      >= pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      <= pcad->mess  *string     failure message written to CAD MESS field
 * 	vala 		*string	   constant string/name for lutout
 * 	valc 		long 	   CAD_Accept in case of start directive
 * 	vald 		long 	   command for gensub 
 *
 *   Return value:
 *      <= status      long        Status value written to CAD VAL field
 *
 *   Note:
 *   To really do the action, the record/routine uses another record/routine
 *   connected to it, "PDSub()"
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Olaf Frischmuth  (Frischmuth.Goepel@t-online.de)
 *
 *   History:
 *   22-Jul-1997: Original version.                  (ocf)
 *-
 */

long CADPark( struct cadRecord *pcad ) 
{
  char messages[80];                           /* Message buffer */

  long status = CAD_ACCEPT;                    /* Initialise return status */
  long mechindex = CAD_default(pcad, &status); /* does all default actions */

  *(long*)pcad->valc  = PD_REJECT;             /* default for gensub */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)
  {
  case menuDirectivePRESET:    /* CAD PRESET directive detected. Arguments checking. */
    if (getGIS()) 
    {
      status = CAD_REJECT;
      sprintf( messages, "GIS is active!"); 
      strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
      pcad->mess [MAX_STRING_SIZE-1] = 0;
      sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
      agLogMessage( mechindex, DEB_ERROR,  messages);
    }
    else
    {
      *(long*)pcad->valb = PD_OK; 		/* for gensub */
      *(long*)pcad->vald = C_Park;		/* for gensub */
      strcpy( pcad->a,    parkstr);		/* name for queryLUT */
      strcpy( pcad->vala, parkstr);		/* name for lutout */
    }
    break;

    case menuDirectiveSTART:
      if (*(long*)pcad->valb == PD_OK)
          *(long*)pcad->valc  = PD_ACCEPT;	/* for gensub */
    break;

    case menuDirectiveSTOP:
      doPLCcomm (mechindex, C_Stop, NULL);	/* Comm. "Stop"	*/
    break;

  }
  return status;
}						/* CADPark */


/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   PDsub - Do "Datum" and "Park" actions after triggered by commands.
 *
 *   Purpose:
 *   This routine is called whenever the Datum or Park CAD records are
 *   processed and trigger it. It checks that the command
 *   is acceptable and gives the Park/Datum commands to the 
 *   PMAC PLC programs via DPRAM.
 *
 *   Invocation:
 *   long PDsub( struct genSubRecord *pgsub )
 *
 *   Parameters in:
 * 	a,b,c 	long 	Eng.Pos. 3 Coordinates 
 * 	d 	long 	PD_ACCEPT/PD_REJECT from CAD
 * 	e 	long 	command (park/datum)
 * 	f	-
 * 	g	long	number of elements of LUT entry	
 * 	j	long		
 *
 *   Parameters out:
 * 	vala/b/c long 	Eng.Pos. 3 Coordinates - 
 *			copy for Eng CAD (that the user sees the pos.)
 * 	vald		link to LUT.VAL (asklut)
 * 
 *   Return value:
 *   None used.
 *
 *   Requirements:
 *   None
 *
 *   Author:
 *   Olaf Frischmuth  (Frischmuth.Goepel@t-online.de)
 *
 *   History:
 *   22-Jul-1997: Original version.                  (ocf)
 *-
 */

/* INAM= asklut! (see ag_utils.c)	*/

#undef 	XLIMP
#undef 	XLIMN
#undef 	YLIMP
#undef 	YLIMN
#undef 	ZLIMP
#undef 	ZLIMN
/* there are no hard limits; the park/datum pos can be 50% outside
*  of the normal range	xnew = 1.5lim1 - 0.5lim2 
*/
#define	XLIMP real2eng (Scale[mechindex][0], Offset [mechindex][0], \
                        1.5*Limits [mechindex][0] - 0.5*Limits [mechindex][1])
#define	XLIMN real2eng (Scale[mechindex][0], Offset [mechindex][0], \
                        1.5*Limits [mechindex][1] - 0.5*Limits [mechindex][0])
#define	YLIMP real2eng (Scale[mechindex][1], Offset [mechindex][1], \
                        1.5*Limits [mechindex][2] - 0.5*Limits [mechindex][3])
#define YLIMN real2eng (Scale[mechindex][1], Offset [mechindex][1], \
                        1.5*Limits [mechindex][3] - 0.5*Limits [mechindex][2])
#define ZLIMP real2eng (Scale[mechindex][2], Offset [mechindex][2], \
                        1.5*Limits [mechindex][4] - 0.5*Limits [mechindex][5])
#define ZLIMN real2eng (Scale [mechindex][2], Offset [mechindex][2], \
                        1.5*Limits [mechindex][5] - 0.5*Limits [mechindex][4])

long PDsub( struct genSubRecord *pgsub )
{
  char messages[80];		/* Message buffer 	*/
  long pos[3];			/* xyz - Eng position 	*/
  long comm, stat, nelm;	/* command		*/
  unsigned short dir, odir;	/* cad directives	*/
  long xLIMP, xLIMN;
  long yLIMP, yLIMN;
  long zLIMP, zLIMN;

  long mechindex = query_cadname (pgsub->name);

  pos[0] = *(long *)pgsub->a;
  pos[1] = *(long *)pgsub->b;
  pos[2] = *(long *)pgsub->c;
  stat   = *(long *)pgsub->d;
  comm   = *(long *)pgsub->e;
  nelm   = *(long *)pgsub->g;
  dir	 = *(unsigned short *)pgsub->h;
  odir	 = *(unsigned short *)pgsub->i;

  xLIMP = gmax (XLIMP,XLIMN);	xLIMN = gmin (XLIMP,XLIMN);
  yLIMP = gmax (YLIMP,YLIMN);	yLIMN = gmin (YLIMP,YLIMN);
  zLIMP = gmax (ZLIMP,ZLIMN);	zLIMN = gmin (ZLIMP,ZLIMN);

  if (pos[0]<xLIMN || pos[0]>xLIMP)
    pos[0]=0;                                 /* reset pos. far out of range */
  if (pos[1]<yLIMN || pos[1]>yLIMP)  pos[0]=0;
  if (pos[2]<zLIMN || pos[2]>zLIMP)  pos[0]=0;

  *(long *)pgsub->vala = pos[0];
  *(long *)pgsub->valb = pos[1];
  *(long *)pgsub->valc = pos[2];


  if ( (stat == PD_ACCEPT) && ((comm==C_Datum) || (comm==C_Park)) )  {
    if( ((mechindex == lens) || (mechindex == fldstop)) && 
        (!strcmp((char *)pgsub->f, "AUTOMATIC")) )
    {
/*      printf("PDsub: AUTOMATIC mode - switching encoder on\n"); */
      encoderSwitch(1);
    }
    doPLCcomm ( mechindex, comm, &(pos[0]));		/* Pos from LUT	*/
    sprintf   ( messages, "\t%s (%ld)\t- accepted/PLCcomm done.",
                pgsub->name, mechindex); 
    agLogMessage ( mechindex, DEB_FULL, messages);
  }

  return 0;
}

/* ===================================================================== */
#if 0
    sprintf( messages, "\tcomm=%d, pos[0]=%d, stat=%d, nelm=%d, dir=%d, odir=%d", 
		comm, pos[0], stat, nelm, dir, odir); 
    agLogMessage( mechindex, DEB_FULL, messages);
#endif
/* ===================================================================== */

/*+
 *  =====================================================================
 *   Function name:
 *   CAD_default
 *
 *   Purpose:
 *   returns mechindex in cases CAD_preset, CAD_start and CAD_stop 
 *
 *   Invocation:
 *   long CAD_default (struct cadRecord  *pcad, long *pstatus)
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CAD_default( pcad );
 *
 *   Parameters in:
 *      >= pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      <= pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      <= status      long        Status value written to CAD VAL field
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Olaf Frischmuth  (Frischmuth.Goepel@t-online.de)
 *
 *   History:
 *   22-Jul-1997: Original version.                  (ocf)
 *-
 */

long CAD_default (struct cadRecord  *pcad, long *pstatus)
{ 
  char messages[80];     /* Message buffer */
  long mechindex = query_cadname (pcad->name);

  if (mechindex >= MAX_INDEX)
  {
    *pstatus = CAD_REJECT;
    sprintf( messages, "Unknown CAD name, %s", pcad->name );  
    strncpy( pcad->mess, messages, MAX_STRING_SIZE );
    pcad->mess [MAX_STRING_SIZE-1] = 0;
    sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
    agLogMessage( mechindex, DEB_ERROR,  messages);
  }

/*  else  */

  switch (pcad->dir)
  {
    case menuDirectiveMARK:			/* CAD MARK directive detected. Nothing needs to be done. 	*/

      sprintf( messages, "\t%s (%ld)\t- MARK directive.", pcad->name, mechindex ); 
      agLogMessage( mechindex, DEB_FULL, messages);
    break;

    case menuDirectivePRESET:				/* CAD PRESET directive detected. Arguments checking. 	*/

      sprintf( messages, "\t%s (%ld)\t- PRESET directive.", pcad->name, mechindex ); 
      agLogMessage( mechindex, DEB_FULL, messages);
    break;

    case menuDirectiveSTART:
	/* CAD START directive detected. Do nothing. The directive is being
	 * monitored by the CICS sequence code, which will start the appropriate
	 * action.
	 */
      sprintf( messages, "\t%s (%ld)\t- START directive.", pcad->name, mechindex ); 
      agLogMessage( mechindex, DEB_FULL, messages);
    break;

    case menuDirectiveSTOP:
	/* CAD START directive detected. Do nothing. The directive is being
	 * monitored by the CICS sequence code, which will start the appropriate
	 * action.
	 */
      sprintf( messages, "\t%s (%ld)\t- STOP directive.", pcad->name, mechindex ); 
      agLogMessage( mechindex, DEB_FULL, messages);
    break;

    case menuDirectiveCLEAR:			/* CAD CLEAR directive detected. */
	sprintf( messages, "\t%s (%ld)\t- CLEAR directive.", pcad->name, mechindex ); 
      	agLogMessage( mechindex, DEB_FULL, messages);
	/* strcpy( pcad->mess, "\0");	*/
					/* only 2 In/Outputs are cleared, since some CADs have only 2	*/
	*(long*)pcad->a 	= 0;				/* strings are now "empty strings"	*/
	*(long*)pcad->b 	= 0;				/* doubles are not completely cleared	*/
	*(long*)pcad->vala 	= 0;				/* smaller data than longs could be 	*/
	*(long*)pcad->valb 	= 0;				/*   dangerous.				*/
	/* strcpy ( pcad->a,    "\0");
	 * strcpy ( pcad->b,    "\0");
	 * strcpy ( pcad->vala, "\0");
	 * strcpy ( pcad->valb, "\0");
	 */
	db_post_events( pcad, &pcad->a,   1 );		/* unknown, what these commands stand for	*/
	db_post_events( pcad, &pcad->b,   1 );
	db_post_events( pcad, pcad->vala, 1 );
	db_post_events( pcad, pcad->valb, 1 );
    break;

    default:			/* Unrecognised CAD directive detected. This is regarded as an error. 	*/
      *pstatus = CAD_REJECT;
      sprintf( messages,"Unrecognised CAD directive" );
      strncpy( pcad->mess, messages, MAX_STRING_SIZE );
      pcad->mess [MAX_STRING_SIZE-1] = 0;
      sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
      agLogMessage( mechindex,  DEB_ERROR, messages);
    break;
  }
  return mechindex;	
}

/* ===================================================================== */
/* ===================================================================== */
