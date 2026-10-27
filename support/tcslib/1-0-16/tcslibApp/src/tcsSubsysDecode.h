/*
*   FILENAME
*   tcsSubsysDecode.h
*
*   DESCRIPTION
*   Function prototypes for the tcs input decoding routines.
*   that can be used by both the TCS and its subsystems. In
*   particular the routines here don't require the inclusion of 
*   tcsConstants.h which can cause name space clashes in some
*   TCS subsystems.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSubsysDecode.h,v $
 * Revision 1.1.1.1  2005/06/20 09:54:24  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/20 09:22:19  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 14:22:52  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 10:24:05  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/14 15:13:15  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/14 11:26:21  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/13 15:21:58  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/09 14:59:14  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/08 16:04:58  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.2  2002/04/16 15:47:03  cjm
 * Add declaration of tcsDcNotEmpty
 *
 * Revision 1.1.1.1  1998/11/08 00:21:14  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1998/07/01 12:13:57  tcs
 * Initial version
 * 
 *
 */
/* *INDENT-ON* */

#ifndef TCSSUBSYSDECODEH
#define TCSSUBSYSDECODEH

/*
**
**  TCS string decode library macros and prototype function declarations.
**
**  P.T.Wallace   23 August 1996
**
**  Copyright RAL 1996.  All rights reserved.
*/

#include <cadRecord.h>

/* Minimum size of strings to receive messages, including null terminator */
#define LSTRING 40

/* Function prototypes */
int tcsDcDebug (char*, char*, int*, char*, struct cadRecord*) ;
int tcsDcFollow (char*, char*, long*, struct cadRecord*) ;
int tcsDcDouble ( char*, char*, double*, struct cadRecord*);
int tcsDcEpoch ( char*, char*, char*, double*, struct cadRecord*);
int tcsDcLong ( char*, char*, long*, struct cadRecord*);
char* tcsDcLc ( char*, int, char* );
int tcsDcLen ( char* );
int tcsDcOffset ( char*, char*, double*, struct cadRecord*);
int tcsDcOnOff (char *prefix, char *string, int *code, struct cadRecord*) ;
int tcsDcNotEmpty (char*);
int tcsDcPmra ( char*, char*, double*, struct cadRecord*);
int tcsDcPmdec ( char*, char*, double*, struct cadRecord*);
int tcsDcPo ( char*, char*, double*, struct cadRecord*);
int tcsDcPx ( char*, char*, double*, struct cadRecord*);
int tcsDcRv ( char*, char*, double*, struct cadRecord*);
int tcsDcString ( char**, char*, char*, int*, struct cadRecord*);
int tcsDcT0 ( char*, char*, double*, struct cadRecord*);
char* tcsDcUc ( char*, int, char* );
int tcsDcWl ( char*, char*, double*, struct cadRecord*);

#endif
