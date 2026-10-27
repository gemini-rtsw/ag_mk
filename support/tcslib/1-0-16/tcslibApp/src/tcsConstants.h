/*
*   FILENAME
*   tcsConstants.h
*
*   DESCRIPTION
*   This include file defines the constants that are needed within the Gemini
*   TCS code as well as some widely used structures.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsConstants.h,v $
 * Revision 1.2  2005/10/21 14:15:31  cjm
 * Allow extra planet code of EPHEMERIS
 *
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
 * Revision 1.1.1.1  2005/06/14 15:13:12  ajf
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
 * Revision 1.1.1.1  2005/06/08 16:04:55  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.6  2003/04/09 10:11:46  dlt
 * Add none to chop modes
 *
 * Revision 1.5  2002/02/22 11:02:10  cjm
 * Add health definitions
 *
 * Revision 1.4  2001/05/17 13:03:15  cjm
 * Remove decalration of epicsPrintf
 *
 * Revision 1.3  1999/05/24 08:06:51  cjm
 * Change limits for m2 XY offsets to match revised Lockheed software
 *
 * Revision 1.2  1999/01/05 17:07:27  epics
 * Add M1WEIGHT enumerated type
 *
 * Revision 1.1.1.1  1998/11/08 00:21:12  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.21  1998/03/23 14:34:04  cjm
 * Add ENCLIMIT type for enclosure limits
 *
 * Revision 1.20  1997/12/08 10:01:22  cjm
 * Define limits for M2 XY translation
 *
 * Revision 1.19  1997/11/19 16:07:04  tcs
 * Move TCB definition to tcsTcb.h
 *
 * Revision 1.18  1997/11/19 10:11:16  tcs
 * Change filter catchup to short circuit
 *
 * Revision 1.17  1997/11/13 13:23:35  tcs
 * Revised guide star scheme
 *
 * Revision 1.16  1997/11/05 11:43:01  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.15  1997/10/31 14:44:55  tcs
 * Add instrument angle to rotator structure
 *
 * Revision 1.14  1997/09/16 11:03:59  cjm
 * Add enumerated types for enclosure & shutter modes
 *
 * Revision 1.13  1997/09/12 13:07:03  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.12  1997/09/11 16:13:28  tcs
 * Add clipAtLimits support
 *
 * Revision 1.11  1997/07/15 13:37:10  cjm
 * Add defines for dome and shutter modes
 *
 * Revision 1.10  1997/06/25 12:57:18  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.9  1997/06/11 15:14:19  tcs
 * Implement wavelength CADs
 *
 * Revision 1.8  1997/06/09 15:53:00  tcs
 * Add position and rate to TRACKK structure
 *
 * Revision 1.7  1997/06/02 09:58:24  tcs
 * Add slew CAD
 *
 * Revision 1.6  1997/05/16 12:19:48  tcs
 * Change TCB to arrays
 *
 * Revision 1.5  1997/05/15 14:15:08  tcs
 * Move differential tracking to separate CAD
 *
 * Revision 1.4  1997/05/07 10:26:42  tcs
 * Implement target to current filter
 *
 * Revision 1.3  1997/04/16 11:55:41  tcs
 * Move tube flexure to telescope specific pointing model routines
 *
 * Revision 1.2  1997/04/07 13:56:05  pbt
 * Changes for compatability with new Gemini EPICS version RGO4
 *
 * Revision 1.1  1997/02/10 17:10:25  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.34  1997/01/24 14:25:14  tcs
 * Move tracking frame to separate CAD
 *
 * Revision 1.33  1997/01/23 10:46:41  tcs
 * kernel support for relative chopping
 *
 * Revision 1.32  1997/01/14 16:31:45  cjm
 * Add TOPEND type
 *
 * Revision 1.31  1997/01/10 15:18:54  tcs
 * FRAMETYPE EPOCH PMPXRV and TELP now defined in astLib.h
 *
 * Revision 1.30  1997/01/08 09:37:32  cjm
 * Add extra debug macros
 *
 * Revision 1.29  1997/01/03 11:16:54  tcs
 * change AZEL_MOUNT to AZEL_MNT
 *
 * Revision 1.28  1996/12/18 11:17:31  tcs
 * cleanup plus offset routines
 *
 * Revision 1.27  1996/12/12 16:38:40  cjm
 * Correct definitions of debug levels
 *
 * Revision 1.26  1996/12/05 13:12:13  tcs
 * rename initial state to catch up
 *
 * Revision 1.25  1996/12/03 16:56:30  tcs
 * New filter parameter names
 *
 * Revision 1.24  1996/12/02 11:06:18  tcs
 * Change rotator position angle to a structure
 *
 * Revision 1.23  1996/11/28 08:10:54  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.22  1996/11/26 15:32:27  tcs
 * Add filter parameters to POINTFILTER struct
 *
 * Revision 1.21  1996/11/13 14:38:53  tcs
 * Add rotator CAD
 *
 * Revision 1.20  1996/11/06 14:32:28  tcs
 * correct definition of D90
 *
 * Revision 1.19  1996/11/05 11:05:52  cjm
 * Add defines for CAD_ACCEPT and CAD_REJECT
 *
 * Revision 1.18  1996/11/04 11:39:06  tcs
 * Add flag for inertially zero proper motions in B
 *
 * Revision 1.17  1996/10/31 09:17:39  cjm
 * Add LIMITTYPE for probes
 *
 * Revision 1.16  1996/10/24 16:11:07  tcs
 * Pointing origin offset commands
 *
 * Revision 1.15  1996/10/24 12:10:42  tcs
 * add pointing origin commands
 *
 * Revision 1.14  1996/10/24 07:08:25  cjm
 * New defines for chop control
 *
 * Revision 1.13  1996/10/22 15:59:44  tcs
 * Add configuration offset commands
 *
 * Revision 1.12  1996/10/08 14:01:35  tcs
 * Add CADs for all 13 VTs & remove guide1 and target
 *
 * Revision 1.11  1996/10/07 07:10:50  cjm
 * Support 13 VTs for both preset and current targets
 *
 * Revision 1.10  1996/10/04 08:08:07  cjm
 * Support tcbdefn command and new telescope types
 *
 * Revision 1.9  1996/09/30 13:42:47  tcs
 * Make enum values explicit
 *
 * Revision 1.8  1996/09/05 16:03:44  pbt
 * Redfined data srtuctures for target fields, plus additional;
 * enumerated types etc.
 *
 * Revision 1.7  1996/07/23 15:03:49  tcs
 * include required EPICS files
 *
 * Revision 1.6  1996/07/19 15:34:47  cjm
 * Modifications for handling of configurations
 *
 * Revision 1.5  1996/07/19 13:42:59  tcs
 * add new simulator state
 *
 * Revision 1.4  1996/07/15 07:38:31  cjm
 * Use standard include heading
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSCONSTANTS_H
#define TCSCONSTANTS_H

#include <dbDefs.h>
#include <astLib.h>
#include <epicsPrint.h>

#define PI    3.1415926535897932384626433832795
#define PI2   (PI*2.0)
#define D90   (PI/2.0)
#define D2R   (PI/180.0)
#define S2R   (PI/43200.0)
#define AS2R  (PI/648000.0)
#define C     173.14463331
#define AU2KM 149597870.66
#define UTST  1.00273790934
#define R2D   (1.0/D2R)
#define TSLOW 60.0
#define STRPS (UTST * S2R)

/* Definitions of the source limit status code */

#define NO_LIMIT 0
#define BELOW_EL_LIMIT 1
#define NEVER_RISES 2
#define BELOW_HORIZON 3

/* Definitions for TCS simulations */

#define STOPPED 0
#define MOVING 1 
#define FOLLOWING 2
#define STOPPING 3
#define DT 0.05

/* definitions for chop types and modes */

#define CHOP_RADEC 0
#define CHOP_AZEL  1

#define TWOPOSN 0
#define THREEPOSN 1
#define TRIANGLE 2
#define NOCHOP 3

/* Definitions for optics model */

#define NUMTOPENDS 3

/* X Y Limits for M2. The limits were doubled to the present values on 22/5/99
*  when the M2 software was modified
*/
#define M2XLIMIT 5.0
#define M2YLIMIT 10.0

/* Definitions of debug levels.  */

#define DBG_NONE 0x0001
#define DBG_MIN  0x0002
#define DBG_FULL 0x0004

/* Definitions of health values. These should come from a system wide file */
#define GOODHEALTH 0
#define WARNHEALTH 1
#define BADHEALTH  2

/* And some macros */

#define DBGMSG( _dbgLevel, _dbgMsg) \
  do { \
     if (dbgLevel & (_dbgLevel) ) errlogPrintf ("%s\n", _dbgMsg) ; \
  } while(0)


#define DBGMSGREAL( _dbgLevel, _dbgMsg, _dbgFloat) \
  do { \
     if (dbgLevel & (_dbgLevel) ) errlogPrintf ("%s %f\n", _dbgMsg, _dbgFloat) ; \
  } while(0)

#define DBGMSGINT( _dbgLevel, _dbgMsg, _dbgInt) \
  do { \
     if (dbgLevel & (_dbgLevel) ) epicsPrintf ("%s %d\n", _dbgMsg, _dbgInt) ; \
  } while(0)

/* The following can be used in the fast loop to generate a "one-shot" message
*  when a trackid changes. This prevents messages being generated at
*  20Hz
*/

#define ONEDBGMSG( _dbgLevel, _dbgMsg) \
  do { \
     if ((dbgLevel & (_dbgLevel)) && (oldTrackid != newTrackid) )  \
         epicsPrintf ("%s\n", _dbgMsg) ; \
  } while(0)


#define ONEDBGMSGREAL( _dbgLevel, _dbgMsg, _dbgFloat) \
  do { \
     if ((dbgLevel & (_dbgLevel)) && (oldTrackid != newTrackid) ) \
        epicsPrintf ("%s %f\n", _dbgMsg, _dbgFloat) ; \
  } while(0)


/* Typedefs for frequently used enumerated constants */

/* top ends */
typedef enum { F16 = 0,
               F6  = 1,
               PRIME = 2
             } TOPEND ;

/* Telescope control blocks */
typedef enum { CURRENT = 0,
               PRESET = 1
             } TCBDEFN ;

/* Virtual telescopes */
typedef enum { MOUNT = 0,
               SOURCE_A = 1,
               SOURCE_B = 2,
               SOURCE_C = 3,
               PWFS1 = 4,
               PWFS2 = 5,
               OIWFS = 6,
               G1 = 7,
               G2 = 8,
               G3 = 9,
               G4 = 10
              } TELESCOPE ;

typedef enum { MOUNT_M =    0x0001,
               SOURCE_A_M = 0x0002,
               SOURCE_B_M = 0x0004,
               SOURCE_C_M = 0x0008,
               PWFS1_M =  0x0010,
               PWFS2_M =  0x0020,
               OIWFS_M =  0x0040,
               G1_M = 0x0080,
               G2_M = 0x0100,
               G3_M = 0x0200,
               G4_M = 0x0400
             } TELESCOPE_M ;

/* Cable wraps */
typedef enum { AZIMUTH = 0,
               ROTATOR = 1
              } WRAP ;
 
/* Offset types */
typedef enum {
               ABSOLUTE = 0,
               RELATIVE = 1
             } OFFSETTYPE ;
 
/* Offset coordinate systems */
typedef enum {
               RADEC = 0,
               TANPLANE = 1
             } OFFCOORD ;

typedef enum {
               XY = 0,
               RADIAL = 1
             } LIMITTYPE ;

/* Solar sytem objects - these should match the numbers used by slaRdplan */
typedef enum {
               EPHEMERIS = -2,
               ORBIT = -1,
               NO_PLANET = 0,
               MERCURY = 1,
               VENUS = 2,
               MOON = 3,
               MARS = 4,
               JUPITER = 5,
               SATURN = 6,
               URANUS = 7,
               NEPTUNE = 8,
               PLUTO = 9
            } PLANET ;

/* Shutter and dome operating modes */

typedef enum { 
              BASIC = 0,
              MINVIBRATION = 1,
              MINSCATTER = 2
             } ENCMODE ;

typedef enum {
              FULLYOPEN = 0,
              TRACKING = 1
             } SHUTTERMODE ;

typedef enum {
              CENTRED = 0,
              RISING  = 1,
              SETTING = 2
             } SOURCEMODE ;

/* Methods of combining aO data */

typedef enum {
              NOWEIGHTS = 0,
              ERRORS = 1
             } M1WEIGHT ;

typedef enum {
              INVALID = -1,
              NOLIMIT  = 0,
              TOPSHTR = 1,
              BOTSHTR = 2,
              LEADEDGE = 3,
              TRAILEDGE = 4
             } ENCLIMIT ;

#endif
