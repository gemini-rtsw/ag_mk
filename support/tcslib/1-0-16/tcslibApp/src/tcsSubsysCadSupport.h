/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsSubsysCadSupport.h
*
*   DESCRIPTION
*   Declares CAD support routines that can be used by
*   both the TCS and its subsystems
*
*/
/*
 * $Log: tcsSubsysCadSupport.h,v $
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
 * Revision 1.1.1.1  2005/06/09 14:59:13  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/08 16:04:58  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.1.1.1  1998/11/08 00:21:13  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1998/07/01 12:13:56  tcs
 * Initial version
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSSUBSYSCADSUPPORTH
#define TCSSUBSYSCADSUPPORTH

#include <cadRecord.h>

char* tcsCsCadName( struct cadRecord* pcad);
void tcsCsSetMessage( struct cadRecord* pcad, char* string);
void tcsCsAppendMessage( struct cadRecord* pcad, char* string);
void tcsCsSetMessageN( struct cadRecord* pcad, ...);
void tcsCsAppendMessageN( struct cadRecord* pcad, ...);
void tcsCsSetOutputField( char* string, char* field);

#endif
