/* static char rcsid[]="$Id: ag_cadcc.c,v 1.8 2001/12/13 04:03:42 ajf Exp $"; */
/*
 *  FILENAME
 *  -------- 
 *  cadcc.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all the functions used by the
 *  CICS SYSTEM CAD records. These functions are used to validate the arguments
 *  given to the CAD record
 *
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  CADinit        - Initialise
 *  CAD_datumCC    - Datum
 *  CAD_parkCC     - Park
 *  CAD_testCC     - Test
 *  CADdebug       - Debug
 *  CADreboot      - Reboot
 *
 *  long CADinitInit	( struct cadRecord *pcad ) ;
 *  long CADinit	( struct cadRecord *pcad ) ;
 *  long CADdebugInit	( struct cadRecord *pcad ) ;
 *  long CADdebug	( struct cadRecord *pcad ) ;
 *  long CAD_datumCC	( struct cadRecord *pcad ) ;
 *  long CAD_parkCC	( struct cadRecord *pcad ) ;
 *  long CAD_testCC	( struct cadRecord *pcad ) ;
 *  long CADreboot	( struct cadRecord *pcad ) ;
 *  long checkBusy	( struct cadRecord *pcad ) ;
 *  long rebootsub 	( struct genSubRecord *pgsub );
 *
 *  DEPENDENCIES
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
 *  Steven Beard  (smb@roe.ac.uk)
 *
 *  HISTORY
 *  -------
 *  28-Mar-1996: Original version with just CADfilterSelect.        (smb)
 *  16-Apr-1996: Add CADfilterMoveEng, CADfilterDatum and
 *               CADfilterPark.                                     (smb)
 *  16-Apr-1996: CADfilterMoveEng renamed due to 15 character
 *               subroutine name length restriction in the
 *               CAD record.                                        (smb)
 *  03-May-1996: Modified to use CAD_ACCEPT/REJECT constants.       (smb)
 *  07-May-1996: All subroutine names shortened to reflect shorter
 *               names for CAD records. (I was hitting the 29
 *               character EPICS record name length limit as well
 *               as the 15 character subroutine name limit).        (smb)
 *  15-May-1996: Documentation tidied up.                           (smb)
 *  06-Jun-1996: Headers converted to Gemini standard format, as
 *               described in SPE-C-G0009. Functions CADinit and
 *               CADreset added.                                    (smb)
 *  12-Jun-1996: EPICS 3.12.2.Gem3 installed, plus latest IGPO
 *               extensions. CAD records now have a "MARK"
 *               directive.                                         (smb)
 *  19-Jun-1996: Headers modified to make them compatible with
 *               the "wflman" utility.                              (smb)
 *  25-Jun-1996: CADfiltSel and CADfiltPark modified to generate
 *               engineering position as output (in preparation
 *               for the use of lookup tables later).               (smb)
 *  11-Jul-1996: CAD records are not allowed to report anything
 *               other than reasons for failure through the MESS
 *               field. Diagnostic messages removed.                (smb)
 *  02-Aug-1996: Modified to make use of "lutin" and "lutout"
 *               records, so the CAD records no longer need to
 *               process lookup tables themselves.                  (smb)
 *  11-Oct-1996: Split into "sysCad" and "filtCad". "filtCad" will
 *               eventually be made more generic.                   (smb)
 *  04-Dec-1996: "printf" replaced by "cicsLogMessage" or
 *               "cicsLogString".                                   (smb)
 *  05-Dec-1996: Components Controller and Detector Controller
 *               versions merged and moved to general CICS library,
 *               since both may need to use the same sequence
 *               commands.                                          (smb)
 *  13-Feb-1997: Start removing the "reset" command. Add "datum"
 *               and "park".                                        (smb)
 *  21-Mar-1997: "reboot" and "endObserve" added. Data label added
 *               to "observe".                                      (smb)
 *  16-Apr-1997: Second input argument of CAD records used to
 *               sense whether the instrument is busy and the
 *               sequence command should be rejected.               (smb)
*/
/* *INDENT-OFF* */
/*
 * $Log: ag_cadcc.c,v $
 * Revision 1.8  2001/12/13 04:03:42  ajf
 * Changes for the automatic switching on/off of the optical encoder
 *
 * Revision 1.7  2001/08/14 14:00:17  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.6  2000/12/20 13:41:57  cjm
 * remove unnecessary tabbing
 *
 * Revision 1.5  2000/05/06 04:28:13  cboyer
 * New version of Olaf V3-2 5May 2000
 *
 * Revision 1.4  2000/04/14 13:27:49  cjm
 * Merge of Hilo changes with latest Zeiss system
 *
 * Revision 1.1.1.1  1998/08/05 21:16:16  Gemini
 * Initial creation of the Gemini A&G repository
 *
 */
/* *INDENT-ON* */

#include  <ag_define.h>
// To include "reboot"
// #include  <devIocStatsOSD.h>
/* ===================================================================== */

/*+
 *   Function name:
 *   CADinit
 *
 *   Purpose:
 *   User defined function for "init" CAD record
 *
 *   Purpose:
 *   This routine is called whenever the init CAD record is processed.
 *   It checks that the command is acceptable and returns a status and a
 *   message, which are written to the VAL and MESS fields of the CAD record.
 *
 *   init is the command for reinitialising the subsystem.
 *   The command has no arguments
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADinit( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *      > pcad->b     long        Instrument busy flag. The command will be
 *                                rejected if this flag happens to be exactly
 *                                equal to CICS_BUSY.
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   06-Jun-1996: Original version.                        (smb)
 *   16-Apr-1997: Check on instrument being busy added.    (smb)
 *-
 */

long CADinitInit( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  long status = CAD_ACCEPT;         		/* Initialise return status */

  long mechindex = query_cadname(pcad->name);	/* does all default actions */

  /* value from vala will be copied to SAD automatically */
  strncpy( pcad->a, SIM_str(getsimu(mechindex)), MAX_STRING_SIZE );
  strncpy( pcad->vala,strntoupper(pcad->a, MAX_STRING_SIZE),
           MAX_STRING_SIZE );
  *(long *)pcad->valb = getsimu(mechindex) ;

  sprintf( messages,"\t%s\t- default simulation level = %s, idx=%ld",
           pcad->name, (char*)pcad->a, mechindex);
  agLogMessage( mechindex, DEB_MIN, messages);

  return status;
}			/* CADinitInit */

/*------------------------------*/

long CADinit( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  static long simu;   				/* Required simu level	    */
  long status = CAD_ACCEPT;         		/* Initialise return status */

  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  /* ajf - This is a hack to prevent INIT from being rejected when a 
     simulation level is not sent through "a". Check the current
     simulation level and use that if one is not explicitly sent.
  */
  if( !strcmp( pcad->a, "" ) )
    strcpy(pcad->a, SIM_str(getsimu(mechindex)));

  if (status == CAD_ACCEPT)
  switch (pcad->dir) {

    case menuDirectivePRESET:

     sprintf( messages,"\t%s\t- Requested simulation level = %s",
              pcad->name, (char*)pcad->a);
     agLogMessage( mechindex, DEB_MIN, messages);

/* Don't allow switching from simulation to non-simulation modes and 
*  vice versa
*/
     if (strcmp(strntoupper(pcad->a, MAX_STRING_SIZE),SIM_NONE_str)==0) {
       if (getsimu(mechindex) != menuSimulationNONE) {
         status = CAD_REJECT ;
         strcpy(pcad->mess, "Reboot to switch to simulation mode");
       } else {
         simu=menuSimulationNONE;
       }
     } else {
       if (getsimu(mechindex) == menuSimulationNONE) {
         status = CAD_REJECT ;
         strcpy(pcad->mess, "Rebbot to switch from simulation mode") ;
       } else {
         if (strcmp(strntoupper(pcad->a, MAX_STRING_SIZE),SIM_VSM_str) ==0)
           simu=menuSimulationVSM;
         else if (strcmp(strntoupper(pcad->a,MAX_STRING_SIZE),SIM_FAST_str)==0) 
           simu=menuSimulationFAST;
         else if (strcmp(strntoupper(pcad->a,MAX_STRING_SIZE),SIM_FULL_str)==0) 
           simu=menuSimulationFULL;
         else {
           status = CAD_REJECT;
           sprintf( messages,"Invalid simulation level" );
           strncpy( pcad->mess, messages, MAX_STRING_SIZE );
           sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
           agLogMessage( mechindex, DEB_ERROR, messages);
         }
       }
     }


    break;

    case menuDirectiveSTART:
      if (mechindex==hrwfs_cc)
        simuMode[HRWFS] = simu;
      else
        simuMode[AG]    = simu;
          
      strncpy( pcad->vala,strntoupper(pcad->a, MAX_STRING_SIZE),
              MAX_STRING_SIZE );
      *(long *)pcad->valb = simu ;

    break;

    case menuDirectiveSTOP:

/* CAD STOP directive detected. It is not possible to stop initialisation
 * once it has started, so reject the directive.
 */
      status = CAD_REJECT;
      sprintf(messages, "Cannot be stopped");
      strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
      sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
      agLogMessage( mechindex, DEB_ERROR,  messages);
      break;
      break;
  }
  return status;
}			/* CADInit */


/* ===================================================================== */
/*+
 *   Function name:
 *   CADdebug
 *
 *   Purpose:
 *   User defined function for "debug" CAD record
 *
 *   Purpose:
 *   This routine is called whenever the debug CAD record is processed.
 *   It checks that the command is acceptable and returns a status and a
 *   message, which are written to the VAL and MESS fields of the CAD record.
 *   If a valid debug level is given the internal debug level is altered.
 *
 *   debug is the command for setting the desired debugging level.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADdebug( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *      > pcad->a     *string     CAD input argument A
 *                                = Requested debug level
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *      < pcad->vala  *string     CAD output value A
 *                                = Set debug level
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   17-Mar-1997: Original version.                        (smb)
 *-
 */

long CADdebugInit( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  long status = CAD_ACCEPT;         		/* Initialise return status */
  long mechindex = query_cadname(pcad->name);		/* does all default actions */

      /* value from vala will be copied to SAD automatically */
      strncpy( pcad->a,   DEB_str(getdebug(mechindex)), 	 MAX_STRING_SIZE );
      strncpy( pcad->vala,strntoupper(pcad->a, MAX_STRING_SIZE), MAX_STRING_SIZE );

      sprintf( messages,"\t%s\t- default debug mode = %s, idx=%ld", pcad->name, (char*)pcad->a, mechindex);
      agLogMessage( mechindex, DEB_MIN, messages);


  return status;
}			/* CADdebugInit */

/*------------------------------*/

long CADdebug( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  static long debug, testdebug;   		/* Required debug level	    */
  long status = CAD_ACCEPT;         		/* Initialise return status */
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:
      sprintf( messages,"\t%s\t- Requested debug level = %s", pcad->name, (char*)pcad->a);
      agLogMessage( mechindex, DEB_MIN, messages);

	   if (strcmp(strntoupper(pcad->a, MAX_STRING_SIZE),DEB_NONE_str) ==0)  debug=DEB_NONE;
      else if (strcmp(strntoupper(pcad->a, MAX_STRING_SIZE),DEB_MIN_str)  ==0)  debug=DEB_MIN;
      else if (strcmp(strntoupper(pcad->a, MAX_STRING_SIZE),DEB_FULL_str) ==0)  debug=DEB_FULL;
      else
      {
        status = CAD_REJECT;
        sprintf( messages,"Invalid debug level" );
        strncpy( pcad->mess, messages, MAX_STRING_SIZE );
        sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
        agLogMessage( mechindex,  DEB_ERROR, messages);
      }
 
	/* vaulue from vala will b copied to SAD automatically */
     if (status == CAD_ACCEPT)
       strncpy( pcad->vala,strntoupper(pcad->a, MAX_STRING_SIZE), MAX_STRING_SIZE );

    break;    

    case menuDirectiveSTART:

      testdebug = getdebug (mechindex);

      if (mechindex==hrwfs_cc)	debugMode[HRWFS] = debug;
      else			debugMode[AG]    = debug;

      if (testdebug < DEB_FULL)		/* show messages if not yet shown due to small debug level */
      { sprintf( messages, "\t%s (%ld)\t- START directive.", pcad->name, mechindex ); 
        agLogMessage( mechindex, DEB_FULL, messages);
      }
      if (testdebug < DEB_MIN)		/* show messages if not yet shown due to small debug level */
      { sprintf( messages,"\t%s\t- Requested debug level = %s", pcad->name, (char*)pcad->a);
        agLogMessage( mechindex, DEB_MIN, messages);
      }
    break;

    case menuDirectiveSTOP:
/* CAD STOP directive detected. The normal way to debug an observation is
 * through the ABORT sequence command, so reject this directive.
 */
      status = CAD_REJECT;
      sprintf(messages, "Cannot be stopped");
      strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
      sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
      agLogMessage( mechindex, DEB_ERROR,  messages);
      break;
  }
  return status;
}			/* CADdebug */

/* ===================================================================== */

/*+
 *   Function name:
 *   CAD_datumCC
 *
 *   Purpose:
 *   This routine is called whenever the datum CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   datum is the command for datuming the subsystem (i.e. making all the
 *   components locate their reference or index points).
 *   The command has no arguments.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CAD_datumCC( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   13-Feb-1997: Original version.                        (smb)
 *   16-Apr-1997: Check on instrument being busy added.    (smb)
 *-
 */

long CAD_datumCC( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  long arg[3], cvstat1;
  double param;
  long status    = CAD_ACCEPT;         		/* Initialise return status */
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */


/* preparation of later necessary arguments for the CC-PLCs	*/
/* P_SmallPLC (=0) means: CC-PLC commands only interlocked mechs
 * (hrfws: only pimg/lens, gbd: only AO/PWFS2).
 * All the other mechs are commanded by EPICS.
 * If this parameter is P_BigPLC (=1), CC-PLC commands all mechs.
 */

  param  = 0; cvstat1= sscanf( pcad->a, "%lf", &(param) );
  param  = (param == P_BigPLC) ? P_BigPLC : P_SmallPLC; 
  arg[2] = arg[1] =  arg[0] = param;

  if (pcad->dir==menuDirectiveSTART && param==P_BigPLC)
        *(long*)pcad->vala = 0;         /* 0 disables subsequent mech calls */
  else  *(long*)pcad->vala = 1;		/* 1=enabled                        */

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
    break;    

    case menuDirectiveSTART:
      if ((getsimu(mechindex)==SIM_NONE) && !(getGIS()))
      {		
        sprintf( messages, "\t%s\t- Starting PLC%ld on cards %ld and 0", 
	  pcad->name, getplcn (mechindex, 0), getcard (mechindex, 0));
        agLogMessage( mechindex, DEB_FULL,  messages);

        doPLCcomm (mechindex, C_Datum, arg);	/* Cmd. for PM1/PM2	*/
      }
    break;

    case menuDirectiveSTOP:
      if (getsimu(mechindex)==SIM_NONE)
      {
        sprintf( messages, "\t%s\t- Stopping PLC%ld on cards %ld and 0", 
	  pcad->name, getplcn (mechindex, 0), getcard (mechindex, 0));
        agLogMessage( mechindex, DEB_FULL,  messages);

        doPLCcomm (mechindex, C_Stop, arg);	/* Cmd. for PM1/PM2	*/
      }
      break;
  }
  return status;
}			/* CAD_datumCC */

/* ===================================================================== */

/*+
 *   Function name:
 *   CAD_parkCC
 *
 *   Purpose:
 *   This routine is called whenever the park CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   park is the command for parking all the components in the subsystem
 *   (i.e. moving them to a position where the instrument can be safely
 *   shut down).
 *   The command has no arguments.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CAD_parkCC( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   13-Feb-1997: Original version.                        (smb)
 *   16-Apr-1997: Check on instrument being busy added.    (smb)
 *-
 */

long CAD_parkCC( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  long arg[3], cvstat1;
  double param;
  long status    = CAD_ACCEPT;         		/* Initialise return status */
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

/* preparation of later necessary arguments for the CC-PLCs	*/
/* P_SmallPLC (=0) means: CC-PLC commands only interlocked mechs
 * (hrfws: only pimg/lens, gbd: only AO/PWFS2).
 * All the other mechs are commanded by EPICS.
 * If this parameter is 1, CC-PLC commands all mechs.
 */

  param  = 0; cvstat1= sscanf( pcad->a, "%lf", &(param) );
  param  = (param == P_BigPLC) ? P_BigPLC : P_SmallPLC; 
  arg[2] = arg[1] =  arg[0] = param;

  if (pcad->dir==menuDirectiveSTART && param==P_BigPLC)
        *(long*)pcad->vala = 0;          /* 0 disables subsequent mech calls */
  else  *(long*)pcad->vala = 1;          /* 1=enabled                        */

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
    break;    

    case menuDirectiveSTART:
      if ((getsimu(mechindex)==SIM_NONE) && !(getGIS()))
      {
        sprintf( messages, "\t%s\t- Starting PLC%ld on cards %ld and 0", 
	  pcad->name, getplcn (mechindex, 0), getcard (mechindex, 0));
        agLogMessage( mechindex, DEB_FULL,  messages);

        doPLCcomm (mechindex, C_Park, arg);             /* Cmd. for PM1/PM2 */
      }
    break;

    case menuDirectiveSTOP:
      if (getsimu(mechindex)==SIM_NONE)
      {
        sprintf( messages, "\t%s\t- Stopping PLC%ld on cards %ld and 0", 
	  pcad->name, getplcn (mechindex, 0), getcard (mechindex, 0));
        agLogMessage( mechindex, DEB_FULL,  messages);

        doPLCcomm (mechindex, C_Stop, arg);            /* Cmd. for PM1/PM2 */
      }
      break;
  }
  return status;
}			/* CAD_parkCC */

/* ===================================================================== */
/* ===================================================================== */

/*+
 *   Function name:
 *   CAD_testCC
 *
 *   Purpose:
 *   This routine is called whenever the test CAD record is
 *   processed. It checks that the command
 *   is acceptable and returns a status and a message, which are written
 *   to the VAL and MESS fields of the CAD record.
 *
 *   test is the command for testing all the components in the subsystem
 *   (i.e. moving them to a position where the instrument can be safely
 *   shut down).
 *   The command has no arguments.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CAD_testCC( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *      > pcad->b     long        Instrument busy flag. The command will be
 *                                rejected if this flag happens to be exactly
 *                                equal to CICS_BUSY.
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   13-Feb-1997: Original version.                        (smb)
 *   16-Apr-1997: Check on instrument being busy added.    (smb)
 *-
 */

long CAD_testCC( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  long status = CAD_ACCEPT;         		/* Initialise return status */
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  *(long*)pcad->vala = 1;			/* 1=enables subsequent mech calls */

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
    break;    

    case menuDirectiveSTART:
      if ((getsimu(mechindex)==SIM_NONE) && !(getGIS()))
      {
      }
    break;

    case menuDirectiveSTOP:
      if (getsimu(mechindex)==SIM_NONE)
      {
      }
      break;
  }
  return status;
}			/* CAD_testCC */

/* ===================================================================== */
/*+
 *   Function name:
 *   CADreboot
 *
 *   Purpose:
 *   User defined function for "reboot" CAD record
 *
 *   Purpose:
 *   This routine is called whenever the reboot CAD record is processed.
 *   It checks that the command is acceptable and returns a status and a
 *   message, which are written to the VAL and MESS fields of the CAD record.
 *
 *   reboot is the command for rebooting the IOC.
 *   The command has no arguments
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADreboot( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      < status      long        Status value written to CAD VAL field
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure.
 *
 *   It is also assumed some other subroutine will do the actual rebooting.
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   16-Mar-1997: Original version.                        (smb)
 *-
 */

long CADreboot( struct cadRecord *pcad ) 
{
  char messages[80];				/* Message buffer 	    */
  long status = CAD_ACCEPT;         		/* Initialise return status */
  long mechindex = CAD_default(pcad, &status);	/* does all default actions */

  if (status == CAD_ACCEPT)
  switch (pcad->dir)	/* Switch according to the CAD directive in DIR field */
  {
    case menuDirectivePRESET:
/* CAD PRESET directive detected. Check that a reboot is allowed at this time.
 * AT THE MOMENT IT IS ASSUMED A REBOOT IS ALWAYS ALLOWED.
 */
    break;

    case menuDirectiveSTART:
/* Note that "reboot()" is not called here. It is assumed a subroutine record
 * will be activated to do the actual rebooting once the CAR record has been
 * set BUSY.
 */

    if (getsimu(mechindex)==SIM_NONE)
    {
      agLogMessage( mechindex, DEB_NONE,
        "\n\n    *** REBOOTING ***\n\n" );
    }
    else
    {
      agLogMessage( mechindex, DEB_NONE,
        "\n\n    *** REBOOTING - Simulated ***\n\n" );
    }

    break;

    case menuDirectiveSTOP:
/* CAD STOP directive detected. It is not possible to stop reboot
 * once it has started, so reject the directive.
 */
      status = CAD_REJECT;
      sprintf(messages, "Cannot be stopped");
      strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
      sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
      agLogMessage( mechindex, DEB_ERROR,  messages);
      break;
  }
  return status;
}			/* CADreboot */

/* ===================================================================== */

/*+
 *   Function name:
 *   rebootsub
 *
 *   Purpose:
 *   Reboot the IOC.
 *
 *   Purpose:
 *   This routine is called when a "reboot" command has been confirmed
 *   and does whatever is necessary to reboot the IOC.
 *
 *   Invocation:
 *   status = cicsReboot( struct subRecord *psub );
 *
 *   Parameters in:
 * 
 *   Parameters out:
 *
 *   Return value:
 *      This is a void function. It has no status value.
 *
 *   Globals:
 *      External functions:
 *      cicsLogMessage   CICS function for cicsLogging a message.
 *      reboot           VxWorks function for rebooting the IOC
 *
 *      External variables:
 *
 *   Requirements:
 *
 *   Limitations:
 *
 *   Author:
 *   Olaf Frischmuth (ocf)
 *
 *   History:
 *   30-Jan-1998:	original version		(ocf)
 *-
 */

long rebootsub ( struct genSubRecord *pgsub )
{
  long status = 0;
  int mechindex = query_cadname (pgsub->name);

  if (getsimu(mechindex)==SIM_NONE)
  {
  //  if (*(long*)pgsub->a == 0)		/* note: function is called twice:	*/
    					/* once for printing a message (a=-1)	*/
   //   reboot( BOOT_QUICK_AUTOBOOT );	/* once for reboot  + printing (a=0)	*/
   // else
      agprintf("\n\n    %s\n\n", "*** give reboot command ***" );
  }
  else
  {
    if (*(long*)pgsub->a == 0)
      agLogMessage( mechindex, DEB_NONE,
         "\n\n    *** give reboot command - Simulated ***\n\n" );
  } 

  return status;
}

/* ===================================================================== */
/*+
 *   Function name:
 *   checkBusy
 *
 *   Purpose:
 *   Check whether instrument is busy, based on second CAD argument.
 *
 *   Purpose:
 *   This is a utility function, called by the above CAD routines, which
 *   looks at the second CAD argument, pcad->b, and determines whether
 *   a command should be rejected due to the instrument being busy.
 *
 *   Invocation:
 *   struct cadRecord *pcad;
 *   status = CADreboot( pcad );
 *
 *   Parameters in:
 *      > pcad->dir   *string     CAD directive
 *      > pcad->b     long        Instrument busy flag. The command will be
 *                                rejected if this flag happens to be exactly
 *                                equal to CICS_BUSY.
 *
 *   Parameters out:
 *      < pcad->mess  *string     failure message written to CAD MESS field
 *
 *   Return value:
 *      < status      long        Status value written to the CAD VAL field.
 *                                Returned CAD_REJECT is instrument is busy.
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *   It is assumed the CAD record has already been initialised and the
 *   directive and any arguments have already been assembled into the pcad
 *   structure.
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   16-Apr-1997: Original version.                        (smb)
 *   16-Apr-1997: Check on instrument being busy added.    (smb)
 *-
 */

/* Check the input argument was successfully converted. (cvstat contains the
 * number of items that "sscanf" has successfully converted, and there
 * should be 1).
 * If the argument cannot be converted, just assume the command can go ahead.
 *
 * If the argument contains "CICS_BUSY" the instrument is busy and the
 * command should be rejected.
 */

long checkBusy( struct cadRecord *pcad ) 
{
  long busyFlag;       		/* busy flag */
  char messages[80];
  long status = CAD_ACCEPT;	/* return status */

      /* Convert the second input argument to an integer. */
  long cvstat = sscanf( pcad->b, "%ld", &busyFlag );
  int mechindex = query_cadname (pcad->name);

  sprintf(messages, "\t%s\t- Busy flag = %ld", pcad->name, busyFlag);
  agLogMessage( mechindex, DEB_FULL,  messages);

  if (( cvstat == 1 )&&( busyFlag == menuCarstatesBUSY ))
    {
      status = CAD_REJECT;
      sprintf(messages, "Instrument is busy - command rejected.");
      strncpy( pcad->mess, messages, MAX_STRING_SIZE );	
      sprintf( messages, "\t%s\t- %s", pcad->name, pcad->mess);
      agLogMessage( mechindex, DEB_ERROR,  messages);
    }

  return status;
}

/* ===================================================================== */


/* ===================================================================== */
epicsRegisterFunction(CADreboot);
epicsRegisterFunction(CAD_datumCC);
epicsRegisterFunction(CAD_testCC);
epicsRegisterFunction(CADinit);
epicsRegisterFunction(CAD_parkCC);
epicsRegisterFunction(CADdebug);
epicsRegisterFunction(rebootsub);
epicsRegisterFunction(CADdebugInit);
epicsRegisterFunction(CADinitInit);
