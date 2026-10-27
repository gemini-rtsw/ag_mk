/*
*   FILENAME
*   tcsSeqConstants.h
*
*   DESCRIPTION
*   This file contains constants that are used in TCS sequence
*   programs. Any sequence program that includes this header file
*   must first be run through the C pre-processor before being
*   passed to snc.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSeqConstants.h,v $
 * Revision 1.1.1.1  2005/06/20 09:54:23  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/20 09:22:19  ajf
 * Initial creation of the Gemini TCS 3-14 repository
 *
 * Revision 1.1.1.1  2005/06/17 14:22:51  ajf
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
 * Revision 1.1.1.1  2005/06/08 16:04:57  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.3  2002/02/22 11:01:31  cjm
 * Remove health definitions
 *
 * Revision 1.2  2001/09/25 16:29:01  ptaylor
 * Add constant definitions for GPOL & increase number of subsystems
 *
 * Revision 1.1.1.1  1998/11/08 00:21:13  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:11:07  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/11/28 08:10:59  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.1  1996/06/13 13:09:50  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#ifndef TCSSEQCONSTANTSH
#define TCSSEQCONSTANTSH

/* Definitions of the various initialisation states */

#define BOOTING 0
#define INITIALISING 1
#define RUNNING 2

/* Definitions of each of the TCS subsystems, the abbreviations used are
*  those defined in Table 5 of the Gemini Software Programming
*  Standards. At this time (May 96) not all subsystems are included
*/

#define MAXSUBSYS 11         /* Maximum number of TCS subsystems */
#define NOSUBSYS  11        /* Current number of TCS subsystems */

#define MC 0                /* Mount */
#define M1 1                /* Primary */
#define M2 2                /* Secondary */
#define CR 3                /* Cass Rotator */
#define EC 4                /* Enclosure */
#define AG 5                /* A&G */
#define AO 6                /* Adaptive Optics */
#define WS 7                /* Weather server */
#define GP 8                /* GPOL */
#define AOM 9               /* Adaptive Optics Module (Canopus) */
#define GSAOI 10            /* Gemini South AO imager */


/* definitions of debug levels. These should be included from elsewhere */

#define DBG_NONE  0x0001
#define DBG_MIN   0x0002
#define DBG_FULL  0x0004


#endif
