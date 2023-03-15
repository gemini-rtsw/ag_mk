/*
*   FILENAME
*   agSimulate.h
*   Put file name here
*
*   DESCRIPTION
*   Header file for A&G simulation facilities
*
*/
/* *INDENT-OFF* */
/*
 * $Log: agSimulate.h,v $
 * Revision 1.1  2000/12/20 13:48:57  cjm
 * Header file for agSimulate.c
 *
 *
 */
/* *INDENT-ON* */

#ifndef AGSIMULATEH 
#define AGSIMULATEH 

void agSimCommand (int mechindex, long command, long posn) ;
long agMechSimFlags (long mechindex, int offset) ;
long agMechSimResp (long mechindex, int offset) ;
double agMechSimPosn (long mechindex, int offset) ;
void agMechSimTrack (long mechindex, double posn) ;

#endif
