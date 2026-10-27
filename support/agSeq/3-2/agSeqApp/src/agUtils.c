/*
*   FILENAME
*   utils
*
*   FUNCTION NAME(S)
*   superFanoutSelectIndex - calculate the index for the super fanout symbol
*
*/
/* *INDENT-OFF* */
/*
 * $Log: agUtils.c,v $
 * Revision 1.3  2007/05/18 22:37:42  pedro
 * Added NICI to the A&G sequencer code
 *
 * Revision 1.2  2005/07/26 23:51:08  anunez
 * Logic for setting indexes was improved
 *
 * Revision 1.1  2005/07/26 21:53:32  anunez
 * First Release of agUtils.c
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

#include <genSubRecord.h>
#include <cad.h>
#include <cadRecord.h>


/*+
 *   Function name:
 *   superFanoutSelIndex
 *
 *   Purpose:
 *   Given an Index, set the appropiate LNK to be processed. 
 *
 *   Description:
 *   Given an Index, this routine will store a link number (between 1 and 5), 
 *   into the corresponding output values. 
 *
 *   Invocation:
 *   superFanoutSelIndex(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    pgsub (struct genSubRecord *pgsub)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK, -1 = Index out of range  
 * 
 *
 *   Epics inputs:
 *
 *   a => Index of the link to activate
 *
 *   Epics outputs:
 *
 *   vala => Converted index for first fanout
 *   valb => Converted index for second fanout
 *   valb => Converted index for third fanout
 *
 *   Notes:
 *   If more fanouts are needed, the corresponding values should be written to the
 *   following valX epics outputs
 */


long superFanoutSelIndex (struct genSubRecord *pgsub) 
{

  const int NUMLINKS = 6;  /* Number on links in any fanout */
  const int TOTAL_FANOUTS = 3;  /* Total fanouts we have 
				 * Update this constant if more 
				 * fanouts are added */
  int value = *(int *)pgsub->a; /* Index to be transformed */
  
  long correctedValue; /* corrected value to trigger into the fanout */
  int i; /*just a simple iteration index */

  /* First, clear everything */
  *(long *)pgsub->vala = 0;
  *(long *)pgsub->valb = 0;
  *(long *)pgsub->valc = 0;

  /* Zero or negative values will be rejected */
  if (value <= 0) return -1; 
  
  for (i = 0; i <= TOTAL_FANOUTS; i++) {
    if (value <= NUMLINKS * i) {
      correctedValue = (value + i - 1) % (NUMLINKS +1);
      /* (long *)(pgsub->vala + i - 1) = correctedValue;  */
      switch (i) {
      case 1: *(long *)pgsub->vala = correctedValue;
	break;
      case 2: *(long *)pgsub->valb = correctedValue;
	break;
      case 3: *(long *)pgsub->valc = correctedValue;
	break;
      }
      return 0;
    }
  }
  
  return -1; /* Error. Index out of range */

}

/*+
 *   Function name:
 *   noopCad
 *
 *   Purpose:
 *   Noop routine for CAD records
 *
 *   Description:
 *   This routine is provided for CAD records that don't do anything and
 *   always return CAD_ACCEPT. It is intended for simulators and debugging.
 *
 *   Invocation:
 *   noopCad(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   (>) pcad (struct cadRecord *pcad)	Pointer to CAD structure
 *
 *   Function value:
 *   (<) status (long)	Always CAD_ACCEPT
 * 
 *   Epics inputs:
 *   None
 *
 *   Epics outputs:
 *   None
 */

long noopCad (struct cadRecord *pcad)
{
    return CAD_ACCEPT;
}
epicsRegisterFunction(superFanoutSelIndex);

