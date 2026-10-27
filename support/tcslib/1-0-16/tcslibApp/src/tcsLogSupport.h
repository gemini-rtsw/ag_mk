/*
*   FILENAME
*   tcsLogSupport.h
*
*   DESCRIPTION
*   Public methods to support logging to a file on disk
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsLogSupport.h,v $
 * Revision 1.1  2014/10/01 16:23:49  cjm
 * Some simple routines to log data
 *
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSLOGSUPPORTH 
#define TCSLOGSUPPORTH 

typedef enum {HMS = 0,
              MJD =1 } LOGTSTYPE ;

/* put definitions here */
void tcsLogOpenFile();
void tcsLogCloseFile();
int tcsLogIsFileOpen();
void tcsLogMessage(char *string);

#endif
