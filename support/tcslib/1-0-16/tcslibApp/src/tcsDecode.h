/*
*   FILENAME
*   tcsDecode.h
*
*   DESCRIPTION
*   Function prototypes for the tcs input decoding routines.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsDecode.h,v $
 * Revision 1.1.1.1  2005/06/20 09:54:23  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/20 09:22:18  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 14:22:51  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 10:24:04  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/14 15:13:14  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/14 11:26:20  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/13 15:21:57  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/09 14:59:13  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/08 16:04:57  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.1.1.1  1998/11/08 00:21:13  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.6  1998/07/01 12:12:27  tcs
 * Include tcsSubsysDecode.h
 *
 * Revision 1.5  1997/08/11 15:41:23  tcs
 * Add CAD for setting pointing parameters
 *
 * Revision 1.4  1997/07/25 16:44:38  cjm
 * Add tcsDcEncMode and tcsDcShtrMode
 *
 * Revision 1.3  1997/06/25 12:57:21  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.2  1997/03/05 09:41:23  tcs
 * tidy up CAD outputs
 *
 * Revision 1.1  1997/02/10 17:10:31  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.11  1997/01/23 10:45:29  tcs
 * Change epoch type to char
 *
 * Revision 1.10  1996/12/13 13:09:45  tcs
 * Add tcsDcLc
 *
 * Revision 1.9  1996/12/06 15:17:12  pbt
 * CAD subroutine and associated decode routine for CAD Follow
 *
 * Revision 1.8  1996/11/29 08:28:50  cjm
 * Add support for debug command
 *
 * Revision 1.7  1996/11/28 08:10:57  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.6  1996/11/26 15:25:43  tcs
 * Add generic double and long decode routines
 *
 * Revision 1.5  1996/11/05 11:06:37  cjm
 * Add tcsDcOnOff
 *
 * Revision 1.4  1996/10/24 12:10:45  tcs
 * add pointing origin commands
 *
 * Revision 1.3  1996/10/23 12:12:16  tcs
 * move offset unit conversion to tcsPointing
 *
 * Revision 1.2  1996/10/22 15:59:47  tcs
 * Add configuration offset commands
 *
 * Revision 1.1  1996/10/08 14:05:34  tcs
 * Input string decoding routines
 *
 */
/* *INDENT-ON* */

#ifndef DECODELIBHDEF
#define DECODELIBHDEF

/*
**
**  TCS string decode library macros and prototype function declarations.
**
**  P.T.Wallace   23 August 1996
**
**  Copyright RAL 1996.  All rights reserved.
*/

#include <cadRecord.h>
#include "tcsSubsysDecode.h"
#include "tcsConstants.h"

/* Function prototypes */
int tcsDcDt ( char*, FRAMETYPE, char*, char*, double*, double*, 
   struct cadRecord*);
int tcsDcEncMode (char*, char*, ENCMODE*, struct cadRecord*);
int tcsDcFrame ( char*, char*, FRAMETYPE*, struct cadRecord*);
int tcsDcOffCoord ( char*,  char*, OFFCOORD*, struct cadRecord*);
int tcsDcPlanet( char *prefix, char *string, PLANET* planet, struct cadRecord*);
int tcsDcRadec ( char*, FRAMETYPE, char*, char*, double*, double*, 
   struct cadRecord*);
int tcsDcShtrMode ( char*, char*, SHUTTERMODE*, struct cadRecord*) ;
int tcsDcTel ( char*, char*, TELESCOPE*, struct cadRecord*);

#endif
