/*
*   FILENAME
*   agSeq
*
*   FUNCTION NAME(S)
*   agNotEmptyString   - check if a string has any alphanumeric characters
*   agSeqCADCommon     - general subroutine for use by CAD with no parameters
*   agSeqCADdebug      - handle debug command
*   agSeqCADfilterSel  - set filter for the selected OIWFS
*   agSeqCADfldStopSel - set field stop for selected OIWFS
*   agSeqCADmove       - handle the move command
*   agSeqCADoiwfsSel   - select which OIWFS is in use
*   agSeqCombineCar    - combine all CAR status to form an activeC value
*   agSeqCombineHealth - combine A&G subsystem health values
*   agSeqCombineState  - combine A&G subsystem state values
*   agSeqDcString      - match a string to list of strings
*   agSeqFollowA       - fanout continous demands
*   agSeqGmosFollowS   - compute value of followS record
*   agSeqPortMap       - map instrument names to port numbers
*   agSeqProbeOffset   - select relevant probeOffset records
*   agSeqSubsysFollow  - send continous demands to a subsystem
*   agSeqSubsysCar     - combine a subsystems CAR and message values
*   agSeqUpcaseString  - convert a string to upper case
*
*/
/* *INDENT-OFF* */
/*
 * $Log: agSeq.c,v $
 * Revision 1.32  2014/10/28 17:54:58  pedro
 * [Pedro Gigoux] Modified agSeqSubsysCar so it does not ignore the busy/idle transitions
 * when for the CC. This will allow users to ignore errors in the CC without losing so the
 * exposure does not start before the mechanisms stop moving.
 *
 * Revision 1.31  2013/11/12 18:02:05  gemvx
 * Modified to allow the TCC select GPI as the wavefront sensor in use
 *
 * Revision 1.30  2013/05/29 16:39:04  pedro
 * Added support for GPI and visitor instruments
 *
 * Revision 1.29  2013/01/31 18:43:36  pedro
 * Added logic to use the HRWFS to compute the A&G Sequencer health
 *
 * Revision 1.28  2011/03/15 01:39:38  gemvx
 * Committing in .
 *
 * Modified Files:
 * 	capfast/agSeqPorts.sch: Added port for CANOPUS.
 * 	src/common/agSeq.c: NUMLINKS updated to 13.
 * 	                    CANOPUS added to insnames array.
 * ----------------------------------------------------------------------
 *
 * Revision 1.26  2011/01/25 15:04:29  currutia
 * Added CANOPUS port
 *
 * Revision 1.26  2007/07/06 22:54:44  pedro
 * Added Phoenix port
 *
 * Revision 1.25  2007/05/18 22:37:41  pedro
 * Added NICI to the A&G sequencer code
 *
 * Revision 1.24  2005/12/07 14:41:21  anunez
 * Updated nirs to gnirs
 *
 * Revision 1.23  2005/08/01 19:36:52  anunez
 * Added support for NIFS
 *
 * Revision 1.22  2005/07/26 14:00:23  gemvx
 * Fixed bug on parsing string to integer
 *
 * Revision 1.21  2005/07/25 16:40:42  anunez
 * Added support for offset for "move" command, when BHROS is being used.
 *
 * Revision 1.20  2005/07/06 15:19:31  gemvx
 * Fixed bug in string comparison.
 * Fixed bug when sending demands to TCS using values not
 * modified by the tweaking offsets
 *
 * Revision 1.19  2005/06/30 20:41:27  anunez
 * Implemented ability to apply offsets in X and Y when bHROS is used
 *
 * Revision 1.18  2005/06/30 16:02:50  anunez
 * Modified agSeqProbeOffset to handle F2 probe offset.
 * First modifications to handle BHROS.
 *
 * Revision 1.17  2005/06/29 19:19:52  anunez
 * Comment fixed
 *
 * Revision 1.16  2005/06/23 23:14:43  anunez
 * Modifications for Flamingos-2
 *
 * Revision 1.15  2005/06/20 20:35:01  anunez
 * Added support for Flamingos-2
 *
 * Revision 1.14  2004/02/12 23:17:17  cjm
 * Add NIRS transformation
 *
 * Revision 1.13  2003/11/04 16:56:30  cjm
 * Add T-recs to list of valid instruments
 *
 * Revision 1.12  2003/03/13 00:00:39  cjm
 * Update comments
 *
 * Revision 1.11  2003/01/27 13:37:09  cjm
 * Allow Michelle as a valid option
 *
 * Revision 1.10  2002/12/06 12:15:44  cjm
 * Output index to processing system
 *
 * Revision 1.9  2001/10/30 11:01:11  ajf
 * Fix the sending of commands. Make sure only the included systems get
 * the commands.
 *
 * Revision 1.8  2001/10/04 08:34:17  cjm
 * Switch to generic transformation routines rather than instrument specific ones
 *
 * Revision 1.7  2001/10/03 10:43:48  ajf
 * ajf: Changes to incorporate the Pixel Router and OIWFS Select command.
 *
 * Revision 1.6  2001/09/25 10:40:37  ajf
 * ajf: Fix bug where certain combinations of parameters to the oiwfsSel
 *      command could crash the system.
 *
 * Revision 1.5  2001/09/20 15:12:14  ajf
 * ajf: Changes for the port to 3.13.
 *
 * Revision 1.4  2001/09/10 12:50:16  cjm
 * Force focus value to 0.0 for GMOS and NIRI and use new record to determine follow state
 *
 * Revision 1.3  2001/08/09 19:09:40  pedro
 * GMOS fixes during commisioning first commisioning run
 *
 * Revision 1.2  2001/06/20 20:37:57  gemvx
 * Add consistency checking to setting of ports
 *
 * Revision 1.1  2001/06/20 18:27:21  gemvx
 * Moved file from directory one level up
 *
 * Revision 1.18  2001/06/19 21:50:03  gemvx
 * Add routines PortMap and DcString
 *
 * Revision 1.17  2001/05/16 12:27:07  cjm
 * Write data to valj in probe offset code
 *
 * Revision 1.16  2001/05/05 23:09:24  cjm
 * Add an agSeqProbeOffset routine
 *
 * Revision 1.15  2001/04/17 15:38:21  cjm
 * Invert logic for setting followS value for NIRI and NIRS
 *
 * Revision 1.14  2000/09/29 10:15:43  cjm
 * Transform TCS demands to NIRI for both move and follow
 *
 * Revision 1.13  2000/07/21 10:34:34  cjm
 * Add routines to generate followS value for different OIWFS
 *
 * Revision 1.12  2000/02/01 07:41:42  cjm
 * Change logic so that 0 = subsystem not loaded and 1 = subsystem loaded rather than vice versa
 *
 * Revision 1.11  2000/01/14 11:31:26  cjm
 * Allow for extra input to the oiwfsSel command
 *
 * Revision 1.10  1999/11/13 02:06:45  cjm
 * Set arraysize to pgsub->noa not pgsub->noj
 *
 * Revision 1.9  1999/10/19 16:03:32  cjm
 * Code to handle fieldstopSel command and improve fanout of continuous demands
 *
 * Revision 1.8  1999/10/15 12:52:20  cjm
 * Using subsys versions of TCS header files
 *
 * Revision 1.7  1999/10/14 14:12:20  cjm
 * Extensive updates for new CAD commands
 *
 * Revision 1.6  1999/09/09 07:17:03  cjm
 * Change HROS to NIRS
 *
 * Revision 1.5  1999/08/24 08:16:40  cjm
 * Extend code for combining state values to handle multiple WFS crates and an OIWFS
 *
 * Revision 1.4  1999/08/20 13:21:18  cjm
 * Changes to accommodate multiple WFS crates and OIWFS
 *
 * Revision 1.3  1999/07/22 15:31:07  cjm
 * Add new routines OiwfsSel and SubsysCar, also rewrite others to pull in extra strings and status now that each WFS is in a separate crate
 *
 * Revision 1.2  1998/09/16 00:32:42  cjm
 * Fix typos and use correct acronym for AGWPS
 *
 * Revision 1.1.1.1  1998/07/29 16:02:28  Gemini
 * Creation of A&G sequencer
 *
 * Revision 1.1  1997/02/10 17:10:37  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1996/10/24 16:11:08  tcs
 * Pointing origin offset commands
 *
 */
/* *INDENT-ON* */

#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <epicsStdioRedirect.h>
#include <epicsStdlib.h>
#include <epicsEvent.h>
#include <epicsPrint.h>
#include <iocsh.h>
#include <string.h>
#include <ctype.h>

#include <dbDefs.h>
#include <dbEvent.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>
#include <genSubRecord.h>

#include <tcsSubsysDecode.h>
#include <tcsSubsysCadSupport.h>
#include "timeLib.h"

#include <agSeqTransforms.h>

/* Forward declarations */
int agNotEmptyString (char *s) ;
void agSeqUpcaseString (char *in, char *out) ;


/*+
 *   Function name:
 *   agNotEmptyString
 *
 *   Purpose:
 *   Check if a string has any alphanumeric characters
 *
 *   Description:
 *   Check each character in a null terminated string to see if it is
 *   alphanumeric. If there are any alphanumeric characters then return
 *   true otherwise return false.
 *
 *   Invocation:
 *   status = agNotEmptyString(s)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    s        (char *)   Null terminated string
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = FALSE otherwise TRUE 
 * 
 *   Deficiencies:
 *   What happens if the string isn't terminated with a NULL ?
 *
 *-
 */

int agNotEmptyString (char *s) 

{
  int status = FALSE ;

  while (*s != '\0') {
   if (isalnum((int)*s)){
    status = TRUE ;
    break ;
   }
   s++ ;
  }

  return status ;
}


/*+
 *   Function name:
 *   agSeqCADcommon
 *
 *   Purpose:
 *   Implement a A&G sequence command that has no parameters
 *
 *   Description:
 *   This is essentially a null routine as there are no CAD parameters to
 *   check.
 *
 *   Invocation:
 *   agSeqCADCommon (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => input on field A etc.
 *
 *   EPICS output paramters:
 *      vala => output written to fields VALA etc.
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 */

long agSeqCADCommon (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   break ;

   case menuDirectiveSTART :

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   agSeqCADdebug
 *
 *   Purpose:
 *   Implement the debug command in the A&G sequencer 
 *
 *   Description:
 *   This routine simply pulls in the parameter sent with the debug command,
 *   checks it for validity and if it is OK passes it on to the debug
 *   commands in the components controller and WFS processing systems.
 *
 *   Invocation:
 *   agSeqCADdebug (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => requested debug level 
 *
 *   EPICS output paramters:
 *      vala => demanded debug level 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 */

long agSeqCADdebug (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char dbgLevel[MAX_STRING_SIZE] ;  /* Requested debug level */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

    agSeqUpcaseString (pcad->a, dbgLevel) ;

    if (!strncmp(dbgLevel, "NONE", 4) || !strncmp (dbgLevel, "MIN", 3) ||
        !strncmp(dbgLevel, "FULL", 4) ) {

    } else {
   
      status = CAD_REJECT ;
      strcpy (pcad->mess, "ag: debug must be NONE, MIN or FULL");
    }

   break ;

   case menuDirectiveSTART :

/* just copy the debug level to the output */
    strcpy (pcad->vala, dbgLevel); 

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   agSeqCADfilterSel
 *
 *   Purpose:
 *   Implement the OIWFS filterSel command 
 *
 *   Description:
 *   Check that the currently selected OIWFS has a filter. If it has then
 *   simply pass the demand on. If it hasn't then reject the command with 
 *   a suitable error message.
 *
 *   Invocation:
 *   agSeqCADfilterSel (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Demanded filter 
 *      d => index to selected OIWFS
 *
 *   EPICS output paramters:
 *      vala => Demanded filter 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 */

long agSeqCADfilterSel (struct cadRecord *pcad)
{

  long status ;           /* Return status */
  long oiwfsIndex ;       /* Index to selected OIWFS */

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;
  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

    status = CAD_REJECT ;

/* Check that command is valid for the currently selected OIWFS. At present
*  it is known that GMOS doesn't have an OIWFS filter
*/
   if (tcsDcLong("OIWFS index: ", pcad->d, &oiwfsIndex, pcad)) break ;
   if (oiwfsIndex == 1) {
     tcsCsAppendMessage(pcad, "GMOS has no filter") ;
     break ;
   }
   
/* Check for null input */
   if (!tcsDcLen(pcad->a)) {
     tcsCsAppendMessage (pcad, "No OIWFS filter specified") ;
     break ;
   }

   status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
/* Simply copy demand filter name to output */
     strcpy (pcad->vala, pcad->a) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   agSeqCADfldStopSel
 *
 *   Purpose:
 *   Implement the OIWFS fldstopSel command 
 *
 *   Description:
 *   Check that the currently selected OIWFS has a field stop. If it has then
 *   simply pass the demand on. If it hasn't then reject the command with 
 *   a suitable error message.
 *
 *   Invocation:
 *   agSeqCADfldstopSel (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Demanded field stop 
 *      d => index to selected OIWFS
 *
 *   EPICS output paramters:
 *      vala => Demanded field stop 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 */

long agSeqCADfldStopSel (struct cadRecord *pcad)
{

  long status ;           /* Return status */
  long oiwfsIndex ;       /* Index to selected OIWFS */

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;
  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

    status = CAD_REJECT ;

/* Check that command is valid for the currently selected OIWFS. At present
*  none of gmos, nirs or niri has a field stop.
*/
   if (tcsDcLong("OIWFS index: ", pcad->d, &oiwfsIndex, pcad)) break ;
   if (oiwfsIndex < 5) {
     tcsCsAppendMessage(pcad, "OIWFS has no field stop") ;
     break ;
   }
   
/* Check for null input */
   if (!tcsDcLen(pcad->a)) {
     tcsCsAppendMessage (pcad, "No OIWFS field stop specified") ;
     break ;
   }

   status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
/* Simply copy demand field stop name to output */
     strcpy (pcad->vala, pcad->a) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   agSeqCADmove
 *
 *   Purpose:
 *   Implement the OIWFS move command 
 *
 *   Description:
 *   The inputs are checked to ensure that the demands are not null
 *   and that they are valid numbers. Depending on the selected
 *   OIWFS, a transformation may be applied to the demands to convert
 *   them from x,y in the focal plane to the coordinate system of the
 *   OIWFS. 
 *
 *   Invocation:
 *   agSeqCADmove (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => X position demand (mm)
 *      b => Y position demand (mm) 
 *      d => Index to the current OIWFS
 *      e => X offset
 *      f => Y offset
 *      g => Z offset
 *      h => Instrument name
 *
 *   EPICS output paramters:
 *      vala => X position demand (OIWFS coords) 
 *      valb => Y position demand (OIWFS coords)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   Deficiences:
 *   Currently there is no check that the demanded X and Y are within range
 *   it is assumed this will be done by the instrument.
 * 
 */

long agSeqCADmove (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  long oiwfsIndex ;          /* Index to OIWFS */
  double xin, yin;           /* X and Y probe demands */
  static double xout, yout ; /* Transformed x, y demands */
  double xoff, yoff;

/* Set message prefix */
  tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;
  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT ;

/* Chesick for null or invalid x input */
   if (!tcsDcLen(pcad->a)) {
     tcsCsAppendMessage(pcad, "No x demand") ;
     break ;
   }
   if (tcsDcDouble("X :", pcad->a, &xin, pcad)) break ;

/* Now do the same for the y demand */
   if (!tcsDcLen(pcad->b)) {
     tcsCsAppendMessage(pcad, "No y demand") ;
     break ;
   }
   if (tcsDcDouble("Y :", pcad->b, &yin, pcad)) break ;

/* Fetch which OIWFS we are dealing with */
   if (tcsDcLong("OIWFS index: ", pcad->d, &oiwfsIndex, pcad)) break ;

   if (oiwfsIndex == 3) {
     agSeqOiwfsXy2xy (NIRI, TCS2NIRI, xin, yin, &xout, &yout) ;
   } else if (oiwfsIndex == 1) {
     agSeqOiwfsXy2xy (GMOS, TCS2GMOS, xin, yin, &xout, &yout) ;
     /* If BHROS is being used, apply offsets */
      if (strcmp(pcad->h, "BHROS") == 0) { 
	if (sscanf (pcad->e, "%lg", &xoff) > 0)
	    xout += xoff;
	if (sscanf (pcad->f, "%lg", &yoff) > 0)
	    yout += yoff;
     }
   } else {
     xout = xin ;
     yout = yin ;
   }

   status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
     sprintf (pcad->vala, "%.3f", xout) ;
     sprintf (pcad->valb, "%.3f", yout) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   agSeqCADoiwfsSel 
 *
 *   Purpose:
 *   Select the OIWFS to which commands are sent and status received
 *
 *   Description:
 *   The oiwfSel command selects which instrument is to receive the commands
 *   sent to the OIWFS and from which instrument status is to be read. On
 *   startup the instrument is set to "NONE" so that all commands and status
 *   are handled internally by the A&G sequencer. "NONE" may also be 
 *   selected at any time if no OIWFS is in use. If "NONE" is not specified
 *   then the routine also checks which system is to be used to handle the
 *   processing of the WFS data.
 *
 *   Invocation:
 *   agSeqCADoiwfsSel (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => OIWFS to use e.g. "NONE", "GMOS", "GNIRS" etc. 
 *      b => Processing system to use "NONE", "WFS" or "AO"
 *
 *   EPICS output paramters:
 *      vala => index to OIWFS as integer
 *      valb => index of OIWFS as string 
 *      valc => index to processing system
 *      vald => original index to processing system
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long agSeqCADoiwfsSel (struct cadRecord *pcad)

{

  long status = 0 ;           /* Return status */
  static char *oiwfsNames[] = {"NONE", "GMOS",  "GNIRS",
			       "NIRI", "F2",    "NIFS",
			       "NICI", "GSAOI", "GPI",
			       NULL} ;
  static char *outNames[] = {"WFS", "AO"} ;
  static int oiwfsIndex ;
  static int outIndex ;
  static char instrument[40]; /* name of the selected instrument */
   
/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {
    case menuDirectivePRESET :
   
/* If no instrument is specified then default to "NONE" */

      if( !tcsDcLen(pcad->a) )
      {
        oiwfsIndex = 0;
        strcpy( pcad->a, oiwfsNames[oiwfsIndex] );
        db_post_events( pcad, pcad->a, 1 );
        status = CAD_ACCEPT;
        strcpy( instrument, oiwfsNames[oiwfsIndex]); 
      }
      else 
      {
        /* If the instrument is BHROS, override it to GMOS using a temporary 
           variable. 
	   The Instrument name (BHROS in this case) will be in pcad->a
        */
	char strTemp[40]; 
        strcpy(instrument, pcad->a);
	strcpy(strTemp, pcad->a); 
	if (strcmp(pcad->a, "BHROS") == 0) {
	  strcpy(strTemp, "GMOS");
	}
	
 
        if( tcsDcString (oiwfsNames, " ", strTemp, &oiwfsIndex, pcad) )
          status = CAD_REJECT;
        else if( !oiwfsIndex )
          status = CAD_ACCEPT;
        else
        {
          if( !tcsDcLen(pcad->b) )
          {
            tcsCsAppendMessage(pcad, "Must select a processing system") ;
            status = CAD_REJECT;
          }
          else
          {
            if( tcsDcString(outNames, " ", pcad->b, &outIndex, pcad) )
              status = CAD_REJECT;
            else
            {
              outIndex++;
              status = CAD_ACCEPT;
            }
          }
        }
      }
      break ;

   case menuDirectiveSTART :

    *(long *)pcad->vala = oiwfsIndex;
    sprintf(pcad->valb, "%d", oiwfsIndex);
    sprintf(pcad->valc, "%d", outIndex);
    outIndex-- ;
    sprintf(pcad->vald, "%d", outIndex);
    /* Write the name of the validated instrument on valf */
    strncpy (pcad->valf, instrument, 40);
    /* sprintf(pcad->valf, "%s", instrument);  */

   status = CAD_ACCEPT ;
   break ;

   case menuDirectiveMARK :
   status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTOP :
   status = CAD_ACCEPT ;
   break ;

   case menuDirectiveCLEAR :
   status = CAD_ACCEPT ;
   break ;

  }

  return status ;
}



/*+
 *   Function name:
 *   agSeqCombineCar
 *
 *   Purpose:
 *   Combine CAR status and messages into a single activeC value
 *
 *   Description:
 *   This routine combines the CAR values from all the A&G subsystems
 *   into a single CAR value for the A&G as a whole. If any of the 
 *   CAR values are set to ERR then the error message is propagated to
 *   the output. Note, by the time this routine is called, it is guaranteed
 *   that there will be a message string with any CAR value that is set
 *   to ERR. Also, any subsystem that has been configured out will have had
 *   its CAR value set to IDLE and its message string set to NULL.
 *
 *   Invocation:
 *   agSeqCombineCar (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *
 *   Epics inputs:
 *
 *   a => CC activeC CAR value
 *   b => HRWFS activeC CAR value
 *   c => PWFS1 activeC CAR value
 *   d => PWFS2 activeC CAR value
 *   e => OIWFS activeC CAR value
 *   f => oifsC activeC CAR value
 *   k => CC activeC CAR message 
 *   l => HRWFS activeC CAR message 
 *   m => PWFS1 activeC CAR message 
 *   n => PWFS2 activeC CAR message 
 *   o => OIWFS activeC CAR message 
 *   p => oiwfsC activeC CAR message 
 *
 *   Epics outputs:
 *
 *   vala => Overall A&G activeC message
 *   valb => Overall A&G activeC value
 * 
 *-
 *   Copyright OSL 1999. All rights reserved
 */


long agSeqCombineCar (struct genSubRecord *pgsub) 

{

 long actCVal ;                     /* Overall activeC value */
 char actCMess[MAX_STRING_SIZE] ;   /* Overall activeC message */
 long ccActCVal ;                   /* ActiveC value for CC */
 char ccMess[MAX_STRING_SIZE];      /* CC message */
 long hrwfsActCVal ;                /* ActiveC value for HRWFS */
 char hrwfsMess[MAX_STRING_SIZE];   /* HRWFS message */
 long pwfs1ActCVal ;                /* ActiveC value for PWFS1 */
 char pwfs1Mess[MAX_STRING_SIZE];   /* PWFS1 message */
 long pwfs2ActCVal ;                /* ActiveC value for PWFS2 */
 char pwfs2Mess[MAX_STRING_SIZE];   /* PWFS2 message */
 long oiwfsActCVal ;                /* ActiveC value for OIWFS */
 char oiwfsMess[MAX_STRING_SIZE];   /* OIWFS message */
 long oiwfsCVal ;                   /* CAR value for oiwfsC */
 char oiwfsCMess[MAX_STRING_SIZE] ; /* oiwfsC message */

/* Set default output */

 actCVal = menuCarstatesIDLE ;
 strcpy (actCMess, " ") ;

/* Fetch all input data */
 ccActCVal    = *(long *)pgsub->a ;
 hrwfsActCVal = *(long *)pgsub->b ;
 pwfs1ActCVal = *(long *)pgsub->c ;
 pwfs2ActCVal = *(long *)pgsub->d ;
 oiwfsActCVal = *(long *)pgsub->e ;
 oiwfsCVal    = *(long *)pgsub->f ;

 strcpy (ccMess, (char *)pgsub->k) ;
 strcpy (hrwfsMess, (char *)pgsub->l) ;
 strcpy (pwfs1Mess, (char *)pgsub->m) ;
 strcpy (pwfs2Mess, (char *)pgsub->n) ;
 strcpy (oiwfsMess, (char *)pgsub->o) ;
 strcpy (oiwfsCMess, (char *)pgsub->p) ;
 
/* Now combine the CAR values to make a single combined output value. If
*  any of the CAR records are BUSY then the overall status is BUSY. If none
*  are BUSY but at least one is in ERR then output ERR otherwise output 
*  IDLE. 
*/

  
 if (ccActCVal == menuCarstatesERROR || hrwfsActCVal == menuCarstatesERROR ||
     pwfs1ActCVal == menuCarstatesERROR || pwfs2ActCVal == menuCarstatesERROR ||
     oiwfsActCVal == menuCarstatesERROR || oiwfsCVal == menuCarstatesERROR ) {
   actCVal = menuCarstatesERROR ;
   if (ccActCVal == menuCarstatesERROR) {
     if (agNotEmptyString(ccMess)) {
       strcpy (actCMess, ccMess) ;
     } else  {
       strcpy (actCMess, "Unspecified error from CC") ;
     }
   } else if (hrwfsActCVal == menuCarstatesERROR) {                       
     if (agNotEmptyString(hrwfsMess)) {
       strcpy (actCMess, hrwfsMess) ;
     } else  {
       strcpy (actCMess, "Unspecified error from HRWFS") ;
     }
   } else if (pwfs1ActCVal == menuCarstatesERROR) {                       
     if (agNotEmptyString(pwfs1Mess)) {
       strcpy (actCMess, pwfs1Mess) ;
     } else  {
       strcpy (actCMess, "Unspecified error from PWFS1") ;
     }
   } else if (pwfs2ActCVal == menuCarstatesERROR) {                       
     if (agNotEmptyString(pwfs2Mess)) {
       strcpy (actCMess, pwfs2Mess) ;
     } else  {
       strcpy (actCMess, "Unspecified error from PWFS2") ;
     }
   } else if (oiwfsActCVal == menuCarstatesERROR) {                       
     if (agNotEmptyString(oiwfsMess)) {
       strcpy (actCMess, oiwfsMess) ;
     } else  {
       strcpy (actCMess, "Unspecified error from OIWFS") ;
     }
   } else if (oiwfsCVal == menuCarstatesERROR) {                       
     if (agNotEmptyString(oiwfsCMess)) {
       strcpy (actCMess, oiwfsCMess) ;
     } else  {
       strcpy (actCMess, "Unspecified error from OIWFS select") ;
     }
   }
 

 }


 if (ccActCVal == menuCarstatesBUSY || hrwfsActCVal == menuCarstatesBUSY ||
     pwfs1ActCVal == menuCarstatesBUSY || pwfs2ActCVal == menuCarstatesBUSY ||
     oiwfsActCVal == menuCarstatesBUSY || oiwfsCVal == menuCarstatesBUSY) {
   actCVal = menuCarstatesBUSY ;
   strcpy(actCMess, " ") ;
 }

 strcpy((char *)pgsub->vala, actCMess) ;
 *(long *)pgsub->valb = actCVal ;

 return 0 ;

}

/*+
 *   Function name:
 *   agSeqCombineHealth
 *
 *   Purpose:
 *   Combine the health values of the GBDCC and AGWPS 
 *   to make a single combined health value for the A&G system
 *
 *   Description:
 *   The input values of the A&G components controller and WFS processing
 *   system are combined such that the "worst" value is always output as
 *   the combined health of the system. For example if the health of the 
 *   CC is WARNING and the AGWPS is GOOD the overall health will be WARNING.
 *   An output message is also provided as a further diagnostic.
 *
 *   Invocation:
 *   agSeqCombineHealth (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *
 *   Epics inputs:
 *      a => CC health message
 *      b => CC health as a string
 *      c => OIWFS DC health message
 *      d => OIWFS DC health as a string
 *      e => PWFS1 health message
 *      f => PWFS1 health as a string
 *      g => PWFS2 health message
 *      h => PWFS2 health as a string
 *      i => HRWFS health message
 *      j => HRWFS health as a string
 *      k => OIWFS health message
 *      l => OIWFS health as a string
 *
 *   Epics outputs:
 *      vala => Health message if available
 *      valb => Combined A&G health, GOOD, WARNING or BAD
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Input values should be upper cased prior to comparison
 *
 *-
 */

long agSeqCombineHealth (struct genSubRecord *pgsub)

{

 char outhealth[8] ;
 char mess[40], str[80] ;
 char *sys = "";
 char *prefix = "";

 strcpy (outhealth, "BAD") ;     /* Initialise to BAD */
 strcpy (mess, "Invalid health from GBDCC or AGWPS") ;  

 if (!strncmp((char *)pgsub->b, "GOOD", 4) &&
     !strncmp((char *)pgsub->d, "GOOD", 4) &&
     !strncmp((char *)pgsub->f, "GOOD", 4) &&
     !strncmp((char *)pgsub->h, "GOOD", 4) &&
     !strncmp((char *)pgsub->j, "GOOD", 4) &&
     !strncmp((char *)pgsub->l, "GOOD", 4)) { 
   strcpy (outhealth, "GOOD") ;
   strcpy (mess, " ") ;
 } else {

   if (!strncmp ((char *)pgsub->b, "WARNING", 7) ||
       !strncmp ((char *)pgsub->d, "WARNING", 7) ||
       !strncmp ((char *)pgsub->f, "WARNING", 7) ||
       !strncmp ((char *)pgsub->h, "WARNING", 7) ||
       !strncmp ((char *)pgsub->j, "WARNING", 7) ||
       !strncmp ((char *)pgsub->l, "WARNING", 7)) {
     strcpy(outhealth, "WARNING") ;
     if (!strncmp((char *)pgsub->b, "WARNING", 7)) {	/* a&g cc */
       if (agNotEmptyString((char *)pgsub->a))
         strcpy (mess, (char *)pgsub->a) ;
       else
         strcpy (mess, "Problem with components controller") ;
       sys = "A&G";
       prefix = "A&G";
      } else if (!strncmp((char *)pgsub->d, "WARNING", 7)) {	/* oiwfs dc */
       if (agNotEmptyString((char *)pgsub->c))
         strcpy (mess, (char *)pgsub->c) ;
       else
         strcpy (mess, "Unspecified problem with OIWFS ") ;
       sys = "OIWFS";
       prefix = "OI DC";
      } else if (!strncmp((char *)pgsub->f, "WARNING", 7)) {	/* pwfs1 dc */
       if (agNotEmptyString((char *)pgsub->e))
         strcpy (mess, (char *)pgsub->e) ;
       else
         strcpy (mess, "Unspecified problem with PWFS1 ") ;
       sys = "PWFS1";
       prefix = "P1 DC";
      } else if (!strncmp((char *)pgsub->h, "WARNING", 7)) {	/* pwfs2 dc */
       if (agNotEmptyString((char *)pgsub->g))
         strcpy (mess, (char *)pgsub->g) ;
       else
         strcpy (mess, "Unspecified problem with PWFS2 ") ;
       sys = "PWFS2";
       prefix = "P2 DC";
      } else if (!strncmp((char *)pgsub->j, "WARNING", 7)) {	/* hrwfs dc */
       if (agNotEmptyString((char *)pgsub->i))
         strcpy (mess, (char *)pgsub->i) ;
       else
         strcpy (mess, "Unspecified problem with HRWFS") ;
       sys = "HRWFS";
       prefix = "HR DC";
      } else if (!strncmp((char *)pgsub->l, "WARNING", 7)) {	/* oiwfs cc */
       if (agNotEmptyString((char *)pgsub->k))
         strcpy (mess, (char *)pgsub->k) ;
       else
         strcpy (mess, "Unspecified problem with OIWFS probe") ;
       sys = "OIWFS";
       prefix = "OI CC";
      }
   }

   if (!strncmp ((char *)pgsub->b, "BAD", 3) || 
       !strncmp ((char *)pgsub->d, "BAD", 3) ||
       !strncmp ((char *)pgsub->f, "BAD", 3) ||
       !strncmp ((char *)pgsub->h, "BAD", 3) ||
       !strncmp ((char *)pgsub->j, "BAD", 3) ||
       !strncmp ((char *)pgsub->l, "BAD", 3)) { 
     strcpy(outhealth, "BAD") ;
     if (!strncmp((char *)pgsub->b, "BAD", 3)) {	/* a&g cc */
       if (agNotEmptyString((char *)pgsub->a))
         strcpy (mess, (char *)pgsub->a) ;
       else
         strcpy (mess, "Problem with components controller") ;
       sys = "A&G";
       prefix = "A&G";
     } else if (!strncmp((char *)pgsub->d, "BAD", 3)) {	/* oiwfs dc */
       if (agNotEmptyString((char *)pgsub->c))
         strcpy (mess, (char *)pgsub->c) ;
       else
         strcpy (mess, "Unspecified problem with OIWFS") ;
       sys = "OIWFS";
       prefix = "OI DC";
     } else if (!strncmp((char *)pgsub->f, "BAD", 3)) { /* pwfs1 dc */
       if (agNotEmptyString((char *)pgsub->e))
         strcpy (mess, (char *)pgsub->e) ;
       else
         strcpy (mess, "Unspecified problem with PWFS1") ;
       sys = "PWFS1";
       prefix = "P1 DC";
     } else if (!strncmp((char *)pgsub->h, "BAD", 3)) { /* pwfs2 dc */
       if (agNotEmptyString((char *)pgsub->g))
         strcpy (mess, (char *)pgsub->g) ;
       else
         strcpy (mess, "Unspecified problem with PWFS2") ;
       sys = "PWFS2";
       prefix = "P2 DC";
     } else if (!strncmp((char *)pgsub->j, "BAD", 3)) {	/* hrwfs */
       if (agNotEmptyString((char *)pgsub->i))
         strcpy (mess, (char *)pgsub->i) ;
       else
         strcpy (mess, "Unspecified problem with HRWFS") ;
       sys = "HRWFS";
       prefix = "HR DC";
     } else if (!strncmp((char *)pgsub->l, "BAD", 3)) {	/* oiwfs cc */
       if (agNotEmptyString((char *)pgsub->k))
         strcpy (mess, (char *)pgsub->k) ;
       else
         strcpy (mess, "Unspecified problem with OIWFS probe") ;
       sys = "OIWFS";
       prefix = "OI CC";
     }
   }
 }

 /* Prepend the system name to the error message if it's not there already,
  * and the message string is not empty (no error condition).
  * The system name to search for is not the same as the one that's prepended.
  * Limit the number of characters that get copied to the record field.
  */
 if (strlen (mess) > 0 && strstr (mess, sys) == NULL)
    sprintf (str, "%s: %s", prefix, mess);
 else
    sprintf (str, "%s", mess);
 strncpy ((char *)pgsub->vala, str, 40) ;

 strcpy ((char *)pgsub->valb, outhealth) ;

 return 0 ;

}


/*+
 *   Function name:
 *   agSeqCombineState
 *
 *   Purpose:
 *   Generate a state value from the states of the CC and WFSPS and OIWFS
 *
 *   Description:
 *   This routine generates an overall "state" value from the combined
 *   states of the Components Controller and WFS Processing System.
 *   The input states are expressed as strings and the output state by
 *   a number (see ICD 7b). As far as the output state is concerned,
 *   the input states "CONFIGURING" are treated as being equivalent to
 *   "RUNNING". 
 *
 *   Invocation:
 *   agSeqCombineState (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure

 *
 *   Epics inputs:
 *   a => Flag to say if CC state is to be used
 *   b => Flag to say if OIWFS DC state is to be used
 *   c => Flag to say if PWFS1 state is to be used
 *   d => Flag to say if PWFS2 state is to be used
 *   e => Input state of CC
 *   f => Input state of OIWFS DC 
 *   g => Input state of PWFS1 
 *   h => Input state of PWFS2 
 *   i => Input state of OIWFS 
 *
 *   Epics outputs:
 *   vala => Overall state of A&G as string
 *   valb => Overall state of A&G as a number
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqCombineState (struct genSubRecord *pgsub) 
{

  int ccLoaded ;
  int oiwfsDcLoaded ;
  int pwfs1Loaded ;
  int pwfs2Loaded ;
  int  agState ;                        /* Overall state of A&G */
  char ccStateStr[MAX_STRING_SIZE] ;    /* State of CC */
  char oiwfsDcStateStr[MAX_STRING_SIZE] ; /* State of OIWFS DC */
  char pwfs1StateStr[MAX_STRING_SIZE] ; /* State of PWFS1 */
  char pwfs2StateStr[MAX_STRING_SIZE] ; /* State of PWFS2 */
  char oiwfsStateStr[MAX_STRING_SIZE] ; /* State of OIWFS */
  int ccState, oiwfsDcState ;           /* States as numbers */
  int pwfs1State, pwfs2State ;
  int oiwfsState ;
  char *states[] = {"BOOTING", "INITIALISING", "RUNNING"} ;


  ccLoaded = *(long *)pgsub->a ;
  oiwfsDcLoaded = *(long *)pgsub->b ;
  pwfs1Loaded = *(long *)pgsub->c ;
  pwfs2Loaded = *(long *)pgsub->d ;

  if (!ccLoaded) {
    strcpy(ccStateStr, "RUNNING") ;
  } else {
    agSeqUpcaseString( (char *)pgsub->e, ccStateStr) ;
  }

  if (!oiwfsDcLoaded) {
    strcpy(oiwfsDcStateStr, "RUNNING") ;
  } else {
    agSeqUpcaseString( (char *)pgsub->f, oiwfsDcStateStr) ;
  }

  if (!pwfs1Loaded) {
    strcpy(pwfs1StateStr, "RUNNING") ;
  } else {
    agSeqUpcaseString( (char *)pgsub->g, pwfs1StateStr) ;
  }

  if (!pwfs2Loaded) {
    strcpy(pwfs2StateStr, "RUNNING") ;
  } else {
    agSeqUpcaseString( (char *)pgsub->h, pwfs2StateStr) ;
  }

  agSeqUpcaseString ((char *)pgsub->i, oiwfsStateStr) ;

/* Convert string state to a number */

  ccState = 0 ;      /* Assume it is BOOTING by default */

  if (!strncmp (ccStateStr, "INITIALISING", 12) ||
      !strncmp (ccStateStr, "INITIALIZING", 12) )
    ccState = 1 ;

  if (!strncmp (ccStateStr, "RUNNING", 7)      ||
      !strncmp (ccStateStr, "CONFIGURING", 11) ||
      !strncmp (ccStateStr, "RESETTING", 9)    )
    ccState = 2 ;


  oiwfsDcState = 0 ;      /* Assume it is BOOTING by default */

  if (!strncmp (oiwfsDcStateStr, "INITIALISING", 12) ||
      !strncmp (oiwfsDcStateStr, "INITIALIZING", 12) )
    oiwfsDcState = 1 ;

  if (!strncmp (oiwfsDcStateStr, "RUNNING", 7) ||
      !strncmp (oiwfsDcStateStr, "CONFIGURING", 11) )
    oiwfsDcState = 2 ;

  pwfs1State = 0 ;      /* Assume it is BOOTING by default */

  if (!strncmp (pwfs1StateStr, "INITIALISING", 12) ||
      !strncmp (pwfs1StateStr, "INITIALIZING", 12) )
    pwfs1State = 1 ;

  if (!strncmp (pwfs1StateStr, "RUNNING", 7) ||
      !strncmp (pwfs1StateStr, "CONFIGURING", 11) )
    pwfs1State = 2 ;

  pwfs2State = 0 ;      /* Assume it is BOOTING by default */

  if (!strncmp (pwfs2StateStr, "INITIALISING", 12) ||
      !strncmp (pwfs2StateStr, "INITIALIZING", 12) )
    pwfs2State = 1 ;

  if (!strncmp (pwfs2StateStr, "RUNNING", 7) ||
      !strncmp (pwfs2StateStr, "CONFIGURING", 11) )
    pwfs2State = 2 ;

  oiwfsState = 0 ;      /* Assume it is BOOTING by default */

  if (!strncmp (oiwfsStateStr, "INITIALISING", 12) ||
      !strncmp (oiwfsStateStr, "INITIALIZING", 12) )
    oiwfsState = 1 ;

  if (!strncmp (oiwfsStateStr, "RUNNING", 7) ||
      !strncmp (oiwfsStateStr, "CONFIGURING", 11) )
    oiwfsState = 2 ;

/* Set overall state to lowest of the individual states */

  agState = 2 ;
  if (ccState < agState )
    agState = ccState ;
  if (oiwfsDcState < agState) agState = oiwfsDcState ;
  if (pwfs1State < agState) agState = pwfs1State ;
  if (pwfs2State < agState) agState = pwfs2State ;
  if (oiwfsState < agState) agState = oiwfsState ;

  strcpy ((char *)pgsub->vala, states[agState]) ;
  *(long *)pgsub->valb = (long)agState ;

  return 0 ;

}


/*+
 *   Function name:
 *   agSeqSubsysCar
 *
 *   Purpose:
 *   Combine CAR status and messages into a single activeC value
 *
 *   Description:
 *   This routine combines the activeC and commSentC CAR values of a
 *   single A&G subsystem into a single CAR value. A flag is used to
 *   say whether the values should be ignored or not. If this is set the
 *   routine simple outputs an IDLE status together with a null message. 
 *   If the flag is not set and the subsystem has an ERROR status set then
 *   a check is made to ensure that an error message has been provided. If 
 *   not then a default message is output.
 *
 *   Invocation:
 *   agSeqSubsysCar (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *
 *   Epics inputs:
 *
 *   a => Flag to indicate if subsystem data should be used
 *   b => Name of subsystem 
 *   c => subsystem command sent CAR value 
 *   d => subsystem activeC CAR value
 *   e => subsystem command sent CAR message 
 *   f => subsystem activeC CAR message 
 *
 *   Epics outputs:
 *
 *   vala => Overall subsystem activeC message
 *   valb => Overall subsystem activeC value
 * 
 *-
 *   Copyright OSL 1999. All rights reserved.
 */


long agSeqSubsysCar (struct genSubRecord *pgsub) 
{
    long subsysPresent ;       /* Flag to indicate if data should be used */
    long actCVal ;             /* Overall activeC value */
    char actCMess[MAX_STRING_SIZE] ; /* Overall activeC message */
    long subsysActCVal ;       /* ActiveC values for subsystem */
    long subsysCommSentVal;    /* Subsys command sent CAR value */
    char subsysMess[MAX_STRING_SIZE];    /* CC message */
    char subsysCsMess[MAX_STRING_SIZE];  /* CC message from "command sent" CAR */
    char subsysName[MAX_STRING_SIZE];     /* Name of subsystem */

    /* Fecth input data.
     */
    subsysPresent = *(long *)pgsub->a ;
    strcpy(subsysName, (char *)pgsub->b) ; 
    subsysCommSentVal = *(long *)pgsub->c ;
    subsysActCVal = *(long *)pgsub->d ;
    strcpy(subsysCsMess, (char *)pgsub->e);
    strcpy(subsysMess, (char *)pgsub->f) ;

    errlogPrintf("present=%ld, subsys=[%s], sentval=%ld, actval=%ld\n", subsysPresent, subsysName, subsysCommSentVal, subsysActCVal); /* DEBUG - REMOVE */

    /* Set default output
     */
    actCVal = menuCarstatesIDLE ;
    strcpy (actCMess, " ") ;

    /* Handle error condition. Errors are ignored if the ignore system flag is set.
     */
    if (subsysPresent) {
	errlogPrintf("Processing error\n");
	if (subsysActCVal == menuCarstatesERROR || subsysCommSentVal == menuCarstatesERROR ) {
	    actCVal = menuCarstatesERROR ;
	    if (subsysCommSentVal == menuCarstatesERROR) {
		if (agNotEmptyString(subsysCsMess)) {
		    strcpy (actCMess, subsysCsMess) ;
		} else  {
		    sprintf (actCMess, "Error sending command to %s", subsysName) ;
		}
	    } else if (subsysActCVal == menuCarstatesERROR) {
		if (agNotEmptyString(subsysMess)) {
		    strcpy (actCMess, subsysMess) ;
		} else  {
		    sprintf (actCMess, "Unspecified error from %s", subsysName) ;
		}
	    }
	}
    }

   /* Handle BUSY transitions. They should not be ignored in the case of A&G CC, regarless
    * of the value of the ignore system flag. This allow the observer to ignore errors in
    * the CC without losing the BUSY/IDLE transitions. This prevents an exposure from
    * starting while a mechanism (e.g. science fold) is still moving. [REL-1392]
    */
    if (subsysPresent) {
	errlogPrintf("processing busy\n"); /* DEBUG - REMOVE */
	if (subsysActCVal == menuCarstatesBUSY || subsysCommSentVal == menuCarstatesBUSY ) {
	    actCVal = menuCarstatesBUSY ;
	    strcpy(actCMess, " ") ;
	}
    } else if (strcmp(subsysName, "CC") == 0) {
	errlogPrintf("ignoring busy except cc\n"); /* DEBUG - REMOVE */
	if (subsysActCVal == menuCarstatesBUSY || subsysCommSentVal == menuCarstatesBUSY ) {
	    actCVal = menuCarstatesBUSY ;
	    strcpy(actCMess, " ") ;
	}
    }

    strcpy((char *)pgsub->vala, actCMess) ;
    *(long *)pgsub->valb = actCVal ;
    return 0 ;

#if 0
/* old code left here while testing changes */
/* Set default output */

 actCVal = menuCarstatesIDLE ;
 strcpy (actCMess, " ") ;

/* Fetch input data on the basis of whether or not a particular subsystem
*  is configured in or not 
*/

 subsysPresent = *(long *)pgsub->a ;


 if (subsysPresent) {

   strcpy(subsysName, (char *)pgsub->b) ; 
   subsysCommSentVal = *(long *)pgsub->c ;
   subsysActCVal = *(long *)pgsub->d ;
   strcpy(subsysCsMess, (char *)pgsub->e);
   strcpy(subsysMess, (char *)pgsub->f) ;
   
/* Now combine the CAR values to make a single combined output value. If
*  any of the CAR records are BUSY then the overall status is BUSY. If none
*  are BUSY but at least one is in ERR then output ERR otherwise output 
*  IDLE.
*/

   if (subsysActCVal == menuCarstatesERROR || subsysCommSentVal == menuCarstatesERROR ) {
     actCVal = menuCarstatesERROR ;
     if (subsysCommSentVal == menuCarstatesERROR) {
       if (agNotEmptyString(subsysCsMess)) {
         strcpy (actCMess, subsysCsMess) ;
       } else  {
         sprintf (actCMess, "Error sending command to %s", subsysName) ;
       }
     } else if (subsysActCVal == menuCarstatesERROR) {
       if (agNotEmptyString(subsysMess)) {
         strcpy (actCMess, subsysMess) ;
       } else  {
         sprintf (actCMess, "Unspecified error from %s", subsysName) ;
       }
     }

   }

   if (subsysActCVal == menuCarstatesBUSY || subsysCommSentVal == menuCarstatesBUSY ) {
     actCVal = menuCarstatesBUSY ;
     strcpy(actCMess, " ") ;
   }

 }

 strcpy((char *)pgsub->vala, actCMess) ;
 *(long *)pgsub->valb = actCVal ;

 return 0 ;

#endif
}

/*+
 *   Function name:
 *   agSeqDcString
 *
 *   Purpose:
 *   Decode a string
 *
 *   Description:
 *   This routine decodes a string by matching it to one of the elements in
 *   a supplied array of strings and returns the index of the matching string.
 *   It is stolen with minor changes from an original by Dave Terrett
 *
 *   Invocation:
 *   status = agSeqDcString (match, string, &index)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)   match    (char **)     Pointer to array of string to match
 *      (>)   string   (char *)      String to decode
 *      (<)   index    (int *)       Index of matching string
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, -1 Invalid string
 *
 *-
 */

int agSeqDcString(char **match, char *string, int *index) 

{
  int n, ls ;
  char ucString[MAX_STRING_SIZE] ;      /* upper case version of string */

/* Upper case the input string, stripping any trailing blanks */

  n = MAX_STRING_SIZE - 1 ;
  if (( ls = tcsDcLen(string)) > n) ls = n;
  tcsDcUc (string, ls +1, ucString);

  for ( *index = 0; match[*index]; (*index)++ ) {
    if (!strcmp (ucString, match[*index])) return 0 ;
  }

  return -1 ;

}



/*+
 *   Function name:
 *   agSeqFollowA
 *
 *   Purpose:
 *   Fan out TCS stream of demands to appropriate OIWFS
 *
 *   Description:
 *   The record to which this subroutine is attached processes each time 
 *   input values are written to port J. The values are then written out to
 *   the port appropriate to the currently selected OIWFS. Depending on
 *   the selected OIWFS, the TCS demands may be transformed into the frame
 *   of reference of the OIWFS.
 *   To protect subsystems from having to handle apply times that remain fixed
 *   the timestamp for all output demands is updated even though the position
 *   updates are only sent to the OIWFS that is selected.
 *   Note also that the focus value is set to zero here. In the original
 *   design this was done at the TCS level. However, to allow for future
 *   OIWFS that might want to know what the focal plane curvature is, it has
 *   been transferred here.
 *
 *   Invocation:
 *   agSeqFollowA (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *
 *   Epics inputs:
 *
 *   a => index of current OIWFS 
 *   j => array of timestamped position demands 
 *
 *   Epics outputs:
 *
 *   vala => Outputs for "none" 
 *   valb => outputs for gmos
 *   valc => outputs for nirs
 *   vald => outputs for niri
 *   vale => outputs for f2
 *   valf => outputs for nifs
 *   valg => outputs for nici
 * 
 *-
 *   Copyright OSL 1999. All rights reserved.
 */


long agSeqFollowA (struct genSubRecord *pgsub) 

{

 unsigned long arraySize ;      /* Number of elements of tcsDemands */
 long oiwfsIndex ;              /* Index to selected OIWFS */
 double niriFrame[6] ;          /* Demands in NIRI frame of reference */
 double nirsFrame[6] ;          /* Demands in GNIRS frame of reference */
 double gmosFrame[6] ;          /* Demands in GMOS frame of reference */
 double f2Frame[6]   ;          /* Demands in Flamingos-2 frame of reference */  
 double nifsFrame[6] ;          /* Demands in NIFS frame of reference */
 double niciFrame[6] ;          /* Demands in NICI frame of reference */
   

/* Fetch input data */
 oiwfsIndex = *(long *)pgsub->a ;
 arraySize = pgsub->noj ;

/* For each OIWFS, update the apply and sent times */
 memcpy (pgsub->vala, pgsub->j, 2*sizeof(double)) ;
 memcpy (pgsub->valb, pgsub->j, 2*sizeof(double)) ;
 memcpy (pgsub->valc, pgsub->j, 2*sizeof(double)) ;
 memcpy (pgsub->vald, pgsub->j, 2*sizeof(double)) ;
 memcpy (pgsub->vale, pgsub->j, 2*sizeof(double)) ;
 memcpy (pgsub->valf, pgsub->j, 2*sizeof(double)) ;
 memcpy (pgsub->valg, pgsub->j, 2*sizeof(double)) ;

/* Now write demands to appropriate output */
 switch (oiwfsIndex) {

  case 0:
    memcpy (pgsub->vala, pgsub->j, arraySize*sizeof(double)) ;
    break ;

  case 1:
    memcpy (gmosFrame, pgsub->j, arraySize*sizeof(double)) ;
    agSeqOiwfsXy2xy(GMOS, TCS2GMOS, *((double *)pgsub->j+3),
                   *((double *)pgsub->j+4), &gmosFrame[3], &gmosFrame[4] ) ;
    agSeqOiwfsZ2z (GMOS, TCS2GMOS, 0.0, &gmosFrame[5]) ;
    memcpy (pgsub->valb, gmosFrame, arraySize*sizeof(double)) ;
    break ;

  case 2:
    memcpy (nirsFrame, pgsub->j, arraySize*sizeof(double)) ;
    agSeqOiwfsXy2xy(NIRS, TCS2NIRS, *((double *)pgsub->j+3),
                    *((double *)pgsub->j+4), &nirsFrame[3], &nirsFrame[4] ) ;
    agSeqOiwfsZ2z (NIRS, TCS2NIRS, 0.0, &nirsFrame[5]) ;
    memcpy (pgsub->valc, nirsFrame, arraySize*sizeof(double)) ;
    break ;

  case 3:
    memcpy (niriFrame, pgsub->j, arraySize*sizeof(double)) ;
    agSeqOiwfsXy2xy(NIRI, TCS2NIRI, *((double *)pgsub->j+3),
                    *((double *)pgsub->j+4), &niriFrame[3], &niriFrame[4] ) ;
    agSeqOiwfsZ2z (NIRI, TCS2NIRI, 0.0, &niriFrame[5]) ;
    memcpy (pgsub->vald, niriFrame, arraySize*sizeof(double)) ;
    break ;
    
  case 4:
    memcpy (f2Frame, pgsub->j, arraySize*sizeof(double)) ;
    agSeqOiwfsXy2xy(F2, TCS2F2, *((double *)pgsub->j+3),
                    *((double *)pgsub->j+4), &f2Frame[3], &f2Frame[4] ) ;
    agSeqOiwfsZ2z (F2, TCS2F2, 0.0, &f2Frame[5]) ;
    memcpy (pgsub->vale, f2Frame, arraySize*sizeof(double)) ;
    break ;   

  case 5:
    memcpy (nifsFrame, pgsub->j, arraySize*sizeof(double)) ;
    agSeqOiwfsXy2xy(NIFS, TCS2NIFS, *((double *)pgsub->j+3),
                    *((double *)pgsub->j+4), &nifsFrame[3], &nifsFrame[4] ) ;
    agSeqOiwfsZ2z (NIFS, TCS2NIFS, 0.0, &nifsFrame[5]) ;
    memcpy (pgsub->valf, nifsFrame, arraySize*sizeof(double)) ;
    break ;

  case 6:
    memcpy (niciFrame, pgsub->j, arraySize*sizeof(double)) ;
    agSeqOiwfsXy2xy(NICI, TCS2NICI, *((double *)pgsub->j+3),
                    *((double *)pgsub->j+4), &niciFrame[3], &niciFrame[4] ) ;
    agSeqOiwfsZ2z (NICI, TCS2NICI, 0.0, &niciFrame[5]) ;
    memcpy (pgsub->valg, niciFrame, arraySize*sizeof(double)) ;
    break ;

  default :
    break ;

 }

 return 0 ;

}

/*+
 *   Function name:
 *   agSeqGmosFollowS
 *
 *   Purpose:
 *   Generate a value for the followS record to show if OIWFS is tracking
 *
 *   Description:
 *   Simply translate the string that GMOS provides into one of the allowed
 *   values for followS.
 *   N.B. This routine was simplified considerably when it turned out the GMOS
 *   probeState record was never implemented. Instead use followS which simply
 *   takes the values 1 or 0
 *
 *   Invocation:
 *   agSeqGmosFollowS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a =>  Flag indicating the GMOS tracking state
 *
 *   Epics outputs:
 *   vala => State of tracking either On or Off
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqGmosFollowS (struct genSubRecord *pgsub)
{

  if (*(long *)pgsub->a == 1)
    strcpy(pgsub->vala, "On") ;
  else
    strcpy (pgsub->vala, "Off") ;
 
  return 0 ;
}

/*+
 *   Function name:
 *   agSeqOiwfsFollowS
 *
 *   Purpose:
 *   Generate a value for the followS record to show if OIWFS is tracking
 *
 *   Description:
 *   Simply translate the index the OIWFS provides into one of the allowed
 *   values for followS. This simple translation is done in C code because 
 *   of problems that were encountered using combinations of EPICS records 
 *   when trying to propagate the severity.
 *
 *   Invocation:
 *   agSeqOiwfsFollowS (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => flag to show following state 
 * 
 *   Epics outputs:
 *   vala => State of tracking either On or Off
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqOiwfsFollowS (struct genSubRecord *pgsub)
{

/* N.B. this routine is used for NIRI, NIFS and NIRS for
*  which 1 = Off and 0 = On i.e. inverted relative
*  to the normal logic
*/
  if (*(long *)pgsub->a == 0)
    strcpy(pgsub->vala, "On") ;
  else
    strcpy (pgsub->vala, "Off") ;
 
  return 0 ;
}

/*+
 *   Function name:
 *   agSeqPortMap
 *
 *   Purpose:
 *   Map instrument names to port numbers
 *
 *   Description:
 *   Five strings are read in from the port records. These strings contain
 *   the names of the instruments that are currently mounted there. The
 *   instrument name is then looked up to check if it is one that is known 
 *   about and if it is then the port number is written to the appropriate
 *   output. If a blank string is read then it is assumed that no instrument
 *   is mounted on that port. 
 *
 *   Invocation:
 *   agSeqPortMap(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *   b => Port 1 instrument
 *   d => Port 2 instrument
 *   f => Port 3 instrument
 *   h => Port 4 instrument
 *   j => Port 5 instrument
 *
 *   Epics outputs:
 *   vala => Port no. for GCAL
 *   valb => Port no. for Altair
 *   valc => Port no. for NIRI
 *   vald => Port no. for GMOS
 *   vale => Port no. for GNIRS
 *   valf => Port no. for NIFS
 *   valg => Port no. for Michelle
 *   valh => Port no. for TRECS
 *   vali => Port no. for Flamingos-2
 *   valj => Port no. for NICI
 *   valk => Port no. for PHOENIX
 *   vall => Port no. for GSOAI
 *   valm => Port no. for CANOPUS
 *   valn => Port no. for GPI
 *   valo => Port no. for VISITOR
 *
 *   Deficiences:
 *   It is not recommended that this routine is executed other than at
 *   load time. If it is then during the update of the output links you
 *   will get occurences where more than one instrument is apparently
 *   mounted on the same port. This is probably benign but it is better
 *   to edit the pv file agSeqPorts.pv and then boot the A&G rather than
 *   update a running system.
 *-
 */

/* Update this each time you make use of more output links. This number
   should match the number of instruments in the insnames array.
 */

#define NUMLINKS 15

long agSeqPortMap(struct genSubRecord *pgsub)
{

/* List of instruments. N.B. these must be in the same order as the output
*  links being used to write the names
*/
  char *insnames[] = {"GCAL",  "ALTAIR", "NIRI",     "GMOS",
		      "GNIRS", "NIFS",   "IGRINS2", "TRECS",
		      "F2",    "NICI",   "PHOENIX",  "GSAOI",
		      "CANOPUS", "GPI",  "VISITOR", NULL};
  int linksWritten[NUMLINKS] ;    /* Array of flags to indicate links updated */
  int i ;                         /* Loop index */
  int index ;                     /* Index of instrument found */
  void **valptr ;                

  for (i = 0; i < NUMLINKS ; i++ ) {
    linksWritten[i] = 0 ;
  }   
  sprintf (pgsub->valu, "%s", "") ;

/* Check for empty string and if not try and decode it to a known instrument */
  if (tcsDcLen(pgsub->b)) {
    if (agSeqDcString (insnames, pgsub->b, &index) == 0) {
      if (linksWritten[index]) {
        sprintf (pgsub->valu, "Port 1: %s already assigned", (char *)pgsub->b);
      } else {
        linksWritten[index] = 1 ;
        valptr = &pgsub->vala + index;
        *(long *)*valptr  = 1 ;
      }
    } else {
      sprintf (pgsub->valu, "Port 1: %s not recognised", (char *)pgsub->b);
    }

  }

  if (tcsDcLen(pgsub->d)) {
    if (agSeqDcString (insnames, pgsub->d, &index) == 0) {
      if (linksWritten[index]) {
        sprintf (pgsub->valu, "Port 2: %s already assigned", (char *)pgsub->d);
      } else {
        linksWritten[index] = 1 ;
        valptr = &pgsub->vala + index;
        *(long *)*valptr  = 2 ;
      }
    } else {
      sprintf (pgsub->valu, "Port 2: %s not recognised", (char *)pgsub->d);
    }
  }

  if (tcsDcLen(pgsub->f)) {
    if (agSeqDcString (insnames, pgsub->f, &index) == 0) {
      if (linksWritten[index]) {
        sprintf (pgsub->valu, "Port 3: %s already assigned", (char *)pgsub->f);
      } else {
        linksWritten[index] = 1 ;
        valptr = &pgsub->vala + index;
        *(long *)*valptr  = 3 ;
      }
    } else {
      sprintf (pgsub->valu, "Port 3: %s not recognised", (char *)pgsub->f);
    }
  }

  if (tcsDcLen(pgsub->h)) {
    if (agSeqDcString (insnames, pgsub->h, &index) == 0) {
      if (linksWritten[index]) {
        sprintf (pgsub->valu, "Port 4: %s already assigned", (char *)pgsub->h);
      } else {
        linksWritten[index] = 1 ;
        valptr = &pgsub->vala + index;
        *(long *)*valptr  = 4 ;
      }
    } else {
      sprintf (pgsub->valu, "Port 4: %s not recognised", (char *)pgsub->h);
    }
  }

  if (tcsDcLen(pgsub->j)) {
    if (agSeqDcString (insnames, pgsub->j, &index) == 0) {
      if (linksWritten[index]) {
        sprintf (pgsub->valu, "Port 5: %s already assigned", (char *)pgsub->j);
      } else {
        linksWritten[index] = 1 ;
        valptr = &pgsub->vala + index;
        *(long *)*valptr  = 5 ;
      }
    } else {
      sprintf (pgsub->valu, "Port 5: %s not recognised", (char *)pgsub->j);
    }
  }

/* Now clear any links that don't have instruments assigned */
  for (i = 0; i < NUMLINKS; i++) {
    if (!linksWritten[i]) {
      valptr = &pgsub->vala + i ;
      *(long *)*valptr = 0 ;
    }
  }
    
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqProbeOffset
 *
 *   Purpose:
 *   Select correct OIWFS input and place on output link
 *
 *   Description:
 *   Currently a very simple routine that checks the index of the
 *   selected OIWFS and then routes that OIWFS's probe offsets to
 *   the output link
 *
 *   Invocation:
 *   agSeqProbeOffset(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *   a => index of current OIWFS
 *   b => array of probe offset data from GMOS
 *   c => array of probe offset data from Flamingos 2
 *
 *   Epics outputs:
 *   vala => array of OIWFS data
 *-
 */

long agSeqProbeOffset(struct genSubRecord *pgsub)
{
  long oiwfsIndex ;
  double dummy[9] ;
  int i ;

  oiwfsIndex = *(long *)pgsub->a ;

/* Currently only GMOS and F2 uses the probe offset facility */
  if (oiwfsIndex == 1) {
    memcpy(pgsub->valj, pgsub->b, 9 * sizeof(double)) ;
  } else if (oiwfsIndex == 4) {
    memcpy(pgsub->valj, pgsub->c, 9 * sizeof(double)) ;
  } else{
    timeNow(&dummy[0]) ;
    dummy[1] = dummy[0] ;
    for (i = 2; i<9 ; i++)
      dummy[i] = 0.0 ;
    memcpy(pgsub->valj, &dummy[0], 9 * sizeof(double)) ;
  } 

  return 0 ;

}


/*+
 *   Function name:
 *   agSeqSubsysFollow
 *
 *   Purpose:
 *   Pass input demands on to a subsystem OIWFS
 *
 *   Description:
 *   This routine simple passes on its input demands to a subsystem OIWFS.
 *   It also splits up the incomming demand array into separate elements
 *   and writes these out for diagnostic purposes.
 *
 *   Invocation:
 *   agSeqSubsysFollow (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *
 *   Epics inputs:
 *
 *   a => array of timestamped position demands 
 *   b => tweak offset in X
 *   c => tweak offset in Y
 *   d => tweak offset in Z
 *   e => instrument name 
 *   Epics outputs:
 *
 *   vala =>  Array of timestamped position demands 
 *   valb => time data was originally sent
 *   valc => time for which data applies
 *   vald => trackid
 *   vale => x demand (mm)
 *   valf => y demand (mm)
 *   valg => z demand (mm)
 * 
 *-
 *   Copyright OSL 1999. All rights reserved.
 */


long agSeqSubsysFollow (struct genSubRecord *pgsub) 

{

 double tcsDemands[6] ;         /* Array of demands */
 unsigned long arraySize ;      /* Number of elements of tcsDemands */

 double offsetX, offsetY, offsetZ; /* Offset to be used to tweak the demands */
 int useOffset = 0;   /* Flag to indicate wheater we should 
			 apply the offsets or not*/          

/* Fetch input data */
 arraySize = pgsub->noa ;
 memcpy (tcsDemands, pgsub->a, arraySize*sizeof(double)) ;

/* Determine if we need to use offsets or not 
   Currently we only apply them for BHROS */

 if (strcmp(pgsub->e, "BHROS") == 0) {
   useOffset = 1;
 }


 if (useOffset) {
  /* Fetch offset values  */
   offsetX = *(double *)pgsub->b;
   offsetY = *(double *)pgsub->c;
   offsetZ = *(double *)pgsub->d;
   tcsDemands[3] += offsetX;
   tcsDemands[4] += offsetY;
   tcsDemands[5] += offsetZ;
 }

/* Write output data */
 memcpy (pgsub->vala, tcsDemands, arraySize*sizeof(double)) ;
 *(double *)pgsub->valb = tcsDemands[0] ;
 *(double *)pgsub->valc = tcsDemands[1] ;
 *(double *)pgsub->vald = tcsDemands[2] ;
 *(double *)pgsub->vale = tcsDemands[3] ;
 *(double *)pgsub->valf = tcsDemands[4] ;
 *(double *)pgsub->valg = tcsDemands[5] ;

 return 0 ;

}

/*+
 *   Function name:
 *   agSeqUpcaseString
 *
 *   Purpose:
 *   Convert a string to upper case
 *
 *   Description:
 *   Perform a characeter by characeter conversion to upper case.
 *
 *   Invocation:
 *   agSeqUpcaseString (in, out)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    in       (char *)   Input string
 *      (<)    out      (char *)   Output string
 *
 *   Function value:
 *   None
 * 
 *-
 */

void agSeqUpcaseString (char *in, char *out)

{
  int c ;

  while (*in != '\0') {

    c = (int)(*in) ;
    *out = (char)toupper(c) ;
    out++ ;
    in++ ;
  }
  *out = '\0' ;

  return ;
}
long agSeqInit (struct cadRecord *pcad)

{
  return 0;
}
epicsRegisterFunction(agSeqCombineHealth);
epicsRegisterFunction(agSeqGmosFollowS);
epicsRegisterFunction(agSeqSubsysCar);
epicsRegisterFunction(agSeqCombineState);
epicsRegisterFunction(agSeqCADmove);
epicsRegisterFunction(agSeqCADCommon);
epicsRegisterFunction(agSeqCADfilterSel);
epicsRegisterFunction(agSeqFollowA);
epicsRegisterFunction(agSeqPortMap);
epicsRegisterFunction(agSeqCADdebug);
epicsRegisterFunction(agSeqProbeOffset);
epicsRegisterFunction(agSeqOiwfsFollowS);
epicsRegisterFunction(agSeqSubsysFollow);
epicsRegisterFunction(agSeqCombineCar);
epicsRegisterFunction(agSeqCADfldStopSel);
epicsRegisterFunction(agSeqCADoiwfsSel);
epicsRegisterFunction(agSeqInit);
