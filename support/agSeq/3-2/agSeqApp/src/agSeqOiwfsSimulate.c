/*
*   FILENAME
*   agSeqOiwfsSimulate.c
*
*   FUNCTION NAME(S)
*   prmSelectCAD  - simulate Pixel Router Select command.
*
*/
/* *INDENT-OFF* */
/*
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
#include <cadRecord.h>
#include <menuCarstates.h>
#include <cad.h>

/*+
 *   Function name:
 *   prmSelectCAD 
 *
 *   Purpose:
 *   Provides a minimal implementation of the Pixel Router
 *   select command
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *       pcad->a     PRM Input  Channel  (STRING)
 *       pcad->b     PRM Output Channel  (STRING)
 *       pcad->vala  PRM Input  Channel  (LONG)
 *       pcad->valb  PRM Output Channel  (LONG)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

#define MIN_CHANNEL_IN  1
#define MAX_CHANNEL_IN  4
#define MIN_CHANNEL_OUT 1
#define MAX_CHANNEL_OUT 2

long prmSelectCAD( cadRecord *pcad )
{
  long status;
  long channelIn;
  long channelOut;

  status = CAD_ACCEPT;
  switch(pcad->dir) 
  {
    case menuDirectiveMARK:
      break;

    case menuDirectivePRESET:
      channelIn  = atol(pcad->a);
      if( (channelIn < MIN_CHANNEL_IN) || (channelIn > MAX_CHANNEL_IN) )
      {
        sprintf( pcad->mess, "Input channel no: %ld invalid", channelIn );
        status = CAD_REJECT;
      }
      else
      {
        *(long *)pcad->vala = channelIn;
        channelOut = atol(pcad->b);
        if( (channelOut < MIN_CHANNEL_OUT) || (channelOut > MAX_CHANNEL_OUT) )
        {
          sprintf( pcad->mess, "Output channel no: %ld invalid", channelOut );
          status = CAD_REJECT;
        }
        else
          *(long *)pcad->valb = channelOut;
      }
      break;

    case menuDirectiveSTART:
      break;

    case menuDirectiveSTOP:
      break;

    case menuDirectiveCLEAR:
      break;

    default:
      sprintf( pcad->mess, "Unknown directive: %d", pcad->dir );
      break;
  }
  return status;
}


long prmTestCAD( cadRecord *pcad )
{
  long status;

  status = CAD_ACCEPT;
  switch(pcad->dir) 
  {
    case menuDirectiveMARK:
    case menuDirectivePRESET:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
    case menuDirectiveCLEAR:
      break;

    default:
      sprintf( pcad->mess, "Unknown directive: %d", pcad->dir );
      break;
  }
  return status;
}
