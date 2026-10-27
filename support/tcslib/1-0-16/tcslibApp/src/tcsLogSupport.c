/*
*   FILENAME
*   tcsLogSupport
*
*   FUNCTION NAME(S)
*   The name of each function in the module goes here along with a single line
*   comment on what it does e.g.
*   function1 - intialises the other functions, must be called first.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsLogSupport.c,v $
 * Revision 1.1  2014/10/01 16:23:49  cjm
 * Some simple routines to log data
 *
 *
 *
 */
/* *INDENT-ON* */

#include <stdio.h>

#include <timeLib.h>
#include "tcsLogSupport.h"

static FILE *fp = NULL;
int fileIsOpen = 0;
LOGTSTYPE tsType = HMS;
timescale tsScale = TAI ;

void tcsLogOpenFile() {

  if (!fp) {
    fp = fopen("tcs.log", "w");
    printf("Opening tcs.log for writing\n");
    fileIsOpen = 1;
  } else {
    printf("tcs.log is already open\n");
  }

}

void tcsLogCloseFile() {

  if (fp) {
    fclose(fp);
    fp = NULL;
    fileIsOpen = 0;
    printf("Closing tcs.log\n");
  } else {
    printf("tcs.log is already closed\n");
  }

}

int tcsLogIsFileOpen() {
 
  return fileIsOpen;

}

void tcsLogMessage(char * string) {

  char tsString[24];
  double traw;
  double mjd;
  int ymdhmsf[7];
  int ndp = 3;

  if (fp) {
    timeNow(&traw); 
    if (tsType == HMS) {
      timeThenC(traw, tsScale, ndp, ymdhmsf);
      sprintf(tsString, "%04d-%02d-%02d:%02d:%02d:%02d.%03d", ymdhmsf[0],
             ymdhmsf[1], ymdhmsf[2], ymdhmsf[3], ymdhmsf[4], ymdhmsf[5],
             ymdhmsf[6]);
    } else {
       timeThenD(traw, tsScale, &mjd);
       sprintf(tsString, "%20.12f", mjd);
    }
    fprintf(fp, "%s %s\n", tsString, string);
    fflush(fp);
  }

}
