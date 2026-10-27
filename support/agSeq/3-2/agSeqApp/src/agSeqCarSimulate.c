/*
*   FILENAME
*   agSeqCarSimulate.c
*
*   FUNCTION NAME(S)
*   agSeqInsActiveC - combine CAR status and messages to generate activeC
*   agSeqInsProbeC  - combine CAR status and messages to generate probeC
*
*/

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
#include <genSubRecord.h>
#include <cadRecord.h>
#include <menuCarstates.h>
#include <cad.h>

#include "tcsSubsysDecode.h"
#include "tcsSubsysCadSupport.h"
#include "tcsServo.h"
#include "timeLib.h"


/* Forward declarations */
int agNotEmptyString (char *s) ;


/*+
 *   Function name:
 *   agSeqInsActiveC
 *
 *   Purpose:
 *   Combine lower level CAR status to form activeC
 *
 *   Description:
 *   At present just copy through the low level values 
 *
 *   Invocation:
 *   agSeqInsActiveC(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqInsActiveC (struct genSubRecord *pgsub) 

{
/* Copy status */
  *(long *)pgsub->valb = *(long *)pgsub->b ;

/* Check for error message */
  if (*(long *)pgsub->b == menuCarstatesERROR) {

    if (agNotEmptyString(pgsub->a))
      strcpy (pgsub->vala, pgsub->a) ;
    else
      strcpy (pgsub->vala, "Unspecified action error") ;
  } else {
    strcpy (pgsub->vala, " ") ;
  }
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqInsProbeC
 *
 *   Purpose:
 *   Combine lower level CAR status to form probeC
 *
 *   Description:
 *   Combine the error status and messages from the low level CAR records.
 *
 *   Invocation:
 *   agSeqInsProbeC(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub record
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqInsProbeC (struct genSubRecord *pgsub) 

{
  long simC ;             /* simC CAR value */
  long softC ;            /* softC CAR value */
  long actVal ;           /* Resultant activeC CAR value */
  char simCMess[MAX_STRING_SIZE] ;
  char softCMess[MAX_STRING_SIZE] ;
  char actMess[MAX_STRING_SIZE] ;

/* Set defualt output */
  actVal = menuCarstatesIDLE ;
  strcpy (actMess, " ");

/* Fetch all input data */
  strcpy (simCMess, pgsub->a) ;
  simC = *(long *)pgsub->b ;
  strcpy (softCMess, pgsub->c) ;
  softC = *(long *)pgsub->d ;

/* Now combine the CAR values */
  if (simC == menuCarstatesERROR || softC == menuCarstatesERROR) {
    actVal = menuCarstatesERROR ;
    if (simC == menuCarstatesERROR ) {
      if (agNotEmptyString(simCMess)) {
        strcpy (actMess, simCMess) ;
      } else {
        strcpy (actMess, "Unspecified error from probe");
      }
    } else if (softC == menuCarstatesERROR) {
      if (agNotEmptyString (softCMess)) {
        strcpy (actMess, softCMess) ;
      } else {
        strcpy (actMess, "Unspecified command error") ;
      } 
    }
  }

  if (simC == menuCarstatesBUSY || softC == menuCarstatesBUSY) {
    actVal = menuCarstatesBUSY ;
    strcpy (actMess, " ") ;
  }

/* Write outputs */
  strcpy ((char *)pgsub->vala, actMess) ;
  *(long *)pgsub->valb = actVal ;

  return 0 ;

}

epicsRegisterFunction(agSeqInsActiveC);
epicsRegisterFunction(agSeqInsProbeC);


