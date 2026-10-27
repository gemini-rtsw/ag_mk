/*
*   FILENAME
*   agSeqTransforms.h
*
*   DESCRIPTION
*   Header file for agSeqTransforms.c
*
*   Copyright Observatory Sciences Ltd. 2000 All rights reserved
*/
/* *INDENT-OFF* */
/*
 * $Log: agSeqTransforms.h,v $
 * Revision 1.7  2007/05/18 22:37:42  pedro
 * Added NICI to the A&G sequencer code
 *
 * Revision 1.6  2005/08/01 19:36:52  anunez
 * Added support for NIFS
 *
 * Revision 1.5  2005/06/23 23:14:43  anunez
 * Modifications for Flamingos-2
 *
 * Revision 1.4  2004/02/12 23:17:58  cjm
 * Add symbols for NIRS transforms
 *
 * Revision 1.3  2001/10/04 08:46:30  cjm
 * remove instrument specific decalrations
 *
 * Revision 1.2  2001/08/09 19:09:40  pedro
 * GMOS fixes during commisioning first commisioning run
 *
 * Revision 1.1  2001/06/20 18:27:22  gemvx
 * Moved file from directory one level up
 *
 * Revision 1.1  2000/09/29 10:17:16  cjm
 * Header file for agseqTransforms.c
 *
 *
 */
/* *INDENT-ON* */

#ifndef  AGSEQTRANSFORMS_H
#define  AGSEQTRANSFORMS_H 

/* Flags used to define the direction of the coordinate transformation.
 * They should be INST->TCS=0, TCS->INST=1.
 */
#define GMOS2TCS	0
#define TCS2GMOS	1
#define NIRS2TCS	0
#define TCS2NIRS	1
#define NIRI2TCS	0
#define TCS2NIRI	1
#define F22TCS		0
#define TCS2F2		1
#define NIFS2TCS	0
#define TCS2NIFS	1
#define NICI2TCS	0
#define TCS2NICI	1

/* Define an index for each OIWFS. If more instruments are added the 
*  MAXOIWFS parameter needs to be increased.
*/
#define NOOIWFS 	0
#define GMOS		1
#define NIRS		2
#define NIRI		3
#define F2		4
#define NIFS		5
#define NICI		6
#define GSAOI		7
#define GPI		8
#define MAXOIWFS	9

void agSeqOiwfsXy2xy (int oiwfs, int direction, double xin, double yin, 
                     double *xout, double *yout) ;
void agSeqOiwfsZ2z   (int oiwfs, int direction, double zin, double *zout) ;

#endif
