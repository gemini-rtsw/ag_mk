/*
*   FILENAME
*   tcsChannelAccess.h
*
*   DESCRIPTION
*   Function prototypes for tcsChannelAccess library
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsChannelAccess.h,v $
 * Revision 1.1.1.1  2005/06/20 09:54:20  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/20 09:22:16  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 14:22:48  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 10:24:02  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/14 15:13:11  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/14 11:26:18  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/13 15:21:55  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/09 14:59:10  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/08 16:04:54  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.1.1.1  1998/11/08 00:21:12  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:10:18  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/09/06 10:49:52  pbt
 * Added standard prologue
 *
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSCHANNELACCESS_H
#define TCSCHANNELACCESS_H

int tcsCaPut(const char *top, const char *pvname, void *val);
int tcsCaGet(const char *top, const char *pvname, void *val);
int tcsPutCadField(const char *top, const char *cadname, const char field, void *val);
int tcsCaEventHandler(char *top, char *pvname, void (*handler)(struct event_handler_args) );
#endif
