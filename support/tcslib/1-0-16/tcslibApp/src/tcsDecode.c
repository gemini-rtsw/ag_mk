/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsDecode.c
*
*   FUNCTION NAME(S)
*   tcsDcDebug    - check that debug level is NONE, MIN or FULL
*   tcsDcDt       - decode a differential track rate
*   tcsDcDouble   - decode a double
*   tcsDcEncMode  - decode an enclosure operating mode
*   tcsDcEpoch    - decode an epoch
*   tcsDcFrame    - decode a coordinate frame
*   tcsDcLong     - decode a long
*   tcsDcLc       - convert a string to lowercase
*   tcsDcLen      - find length of string excluding whitespace
*   tcsDcNotEmpty - check if a string contains any alphanumeric data
*   tcsDcOffset   - decode an offset
*   tcsDcOffCoord - decode an offset coordinate type
*   tcsDcOnOff    - check a string is one of On or Off
*   tcsDcPlanet   - decode a planet name
*   tcsDcPmra     - decode a proper motion in RA
*   tcsDcPmdec    - decode a proper motion in Dec
*   tcsDcPx       - decode a parallax
*   tcsDcRadec    - decode an RA/Dec or Az/El
*   tcsDcRv       - decode a radial velocity
*   tcsDcShtrMode - decode a shutter operating mode
*   tcsDcString   - decode a string
*   tcsDcT0       - decode a reference time
*   tcsDcTel      - decode a virtual telescope name
*   tcsDcUc       - convert a string to uppercase
*   tcsDcWl       - decode a wavelength
*/
/*
 * $Log: tcsDecode.c,v $
 * Revision 1.2  2005/08/19 15:06:47  cjm
 * Increase MAXPO from 1000 to 10000
 *
 * Revision 1.1.1.1  2005/06/20 09:54:22  ajf
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
 * Revision 1.3  2002/04/16 15:46:32  cjm
 * Add tcsDcNotEmpty routine
 *
 * Revision 1.2  2002/02/20 15:49:58  dlt
 * Improve TT handling
 *
 * Revision 1.1.1.1.2.1  2002/02/20 15:37:29  dlt
 * Enhance TT decoding
 *
 * Revision 1.1.1.1  1998/11/08 00:21:12  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.17  1998/07/06 15:35:42  tcs
 * Fix bug in tcsDcUc that allowed input string to write beyond the length of output string
 *
 * Revision 1.16  1997/12/15 11:42:21  tcs
 * Allow ICRS
 *
 * Revision 1.15  1997/11/13 13:24:45  tcs
 * Revised guide star scheme
 *
 * Revision 1.14  1997/11/05 11:36:08  tcs
 * Correct typo
 *
 * Revision 1.13  1997/10/01 10:30:28  tcs
 * Reject blank RA/Dec
 *
 * Revision 1.12  1997/08/11 15:41:22  tcs
 * Add CAD for setting pointing parameters
 *
 * Revision 1.11  1997/07/25 16:44:21  cjm
 * Add tcsDcEncMode and tcsDcShtrMode
 *
 * Revision 1.10  1997/06/25 12:57:20  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.9  1997/05/28 16:33:47  cjm
 * Fix minor typo
 *
 * Revision 1.8  1997/05/15 14:12:18  tcs
 * fix typo in comments
 *
 * Revision 1.7  1997/05/08 15:17:35  tcs
 * remove AZEL_MNT
 *
 * Revision 1.6  1997/04/23 10:04:49  tcs
 * allow dms for Az/El
 *
 * Revision 1.5  1997/03/11 11:18:45  tcs
 * Use slaDafin for RA?dec
 *
 * Revision 1.4  1997/03/05 14:51:39  tcs
 * Terminate RA/Dec strings properly
 *
 * Revision 1.3  1997/03/05 11:14:14  tcs
 * Allow colons in RA/Dec
 *
 * Revision 1.2  1997/03/05 09:36:56  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:10:30  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.15  1997/01/23 10:45:28  tcs
 * Change epoch type to char
 *
 * Revision 1.14  1997/01/03 11:18:19  tcs
 * change AZEL_MOUNT to AZEL_MNT
 *
 * Revision 1.13  1996/12/13 13:09:43  tcs
 * Add tcsDcLc
 *
 * Revision 1.12  1996/12/06 15:17:10  pbt
 * CAD subroutine and associated decode routine for CAD Follow
 *
 * Revision 1.11  1996/11/29 08:28:48  cjm
 * Add support for debug command
 *
 * Revision 1.10  1996/11/28 08:10:56  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.9  1996/11/26 15:25:42  tcs
 * Add generic double and long decode routines
 *
 * Revision 1.8  1996/11/07 16:16:48  tcs
 * correct decoding of reference times
 *
 * Revision 1.7  1996/11/06 13:34:44  tcs
 * correct units of differential tracking
 *
 * Revision 1.6  1996/11/05 11:06:25  cjm
 * Add tcsDcOnOff
 *
 * Revision 1.5  1996/10/25 10:12:44  tcs
 * Correct differential tracking units
 *
 * Revision 1.4  1996/10/24 12:10:44  tcs
 * add pointing origin commands
 *
 * Revision 1.3  1996/10/23 12:12:15  tcs
 * move offset unit conversion to tcsPointing
 *
 * Revision 1.2  1996/10/22 15:59:46  tcs
 * Add configuration offset commands
 *
 * Revision 1.1  1996/10/08 14:05:33  tcs
 * Input string decoding routines
 *
 */
/* *INDENT-ON* */



#include <string.h>
#include <math.h>
#include <ctype.h>
#include "slalib.h"
#include "tcsConstants.h"
#include "tcsCadSupport.h"
#include "tcsDecode.h"

/* Length of string for uppercased coorindinate type (excluding terminator). */
#define LSUC 40
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDcDebug
 *
 *   Purpose:
 *   Check if input string is one of NONE, MIN or FULL
 *
 *   Description:
 *   This routine checks whether the debug level specified by the user 
 *   is valid. Current allowed values are NONE, MIN or FULL. The check is
 *   case insensitive and minimum match. If the input string can't be
 *   matched, an error code and message are returned. If a match is 
 *   obtained then an integer code is returned representing the debug
 *   level. This code is generated by OR'ing together the relevant
 *   debug level constants.
 *
 *   Invocation:
 *   tcsDcDebug (&prefix, &string, &code, &level, &cad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   prefix   (char *)  Prefix for message
 *      (>)   string   (char *)  String to decode
 *      (<)   code     (int *)   Return code
 *      (<)   level    (char *)  Returned level as uppercase string
 *      (<)   pcad     (struct cadRecord *)  CAD record
 *
 *   Function value:
 *   (<)  status  (int)  Return status
 *         0 => OK
 *        -1 => Invalid string
 * 
 *-
 */
/* *INDENT-ON* */



int tcsDcDebug(char *prefix, char *string, int *code, char *level, 
   struct cadRecord *pcad)
{
    int n, ls;
    char ucString[LSUC];        /* upper case version of string */

/* Uppercase the input string, stripping any trailing blanks */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, ucString);

    if (!ls) {
        *code = DBG_NONE;
        strcpy(level, "NONE");
        return 0;
    } else if (!strncmp(ucString, "N", 1)) {
        *code = DBG_NONE;
        strcpy(level, "NONE");
        return 0;
    } else if (!strncmp(ucString, "M", 1)) {
        *code = DBG_NONE | DBG_MIN;
        strcpy(level, "MIN");
        return 0;
    } else if (!strncmp(ucString, "F", 1)) {
        *code = DBG_NONE | DBG_MIN | DBG_FULL;
        strcpy(level, "FULL");
        return 0;
    } else {
        *code = 0;
        tcsCsAppendMessageN(pcad, prefix, "invalid input", (char*)NULL);
        return -1;
    }

}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDcFollow
 *
 *   Purpose:
 *   Check if input string is one of ON or OFF
 *
 *   Description:
 *   This routine checks whether the Follow switch specified by the user 
 *   is valid. Current allowed values are ON or OFF. The check is
 *   case insensitive and minimum match. If the input string can't be
 *   matched, an error code and message are returned. 
 *
 *   Invocation:
 *   tcsDcFollow (&prefix, &string, &fswitch, &cad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   prefix   (char *)  Prefix for message
 *      (>)   string   (char *)  String to decode
 *      (<)   fswitch  (long *)  Returned switch as integer (0 = OFF, 1 = ON)
 *      (<)   pcad     (struct cadRecord *)  CAD record
 *
 *   Function value:
 *   (<)  status  (int)  Return status
 *         0 => OK
 *        -1 => Invalid string
 * 
 *-
 */
/* *INDENT-ON* */



int tcsDcFollow(char *prefix, char *string, long *fswitch, 
   struct cadRecord *pcad)
{
    int n, ls;
    char ucString[LSUC];        /* upper case version of string */

/* Uppercase the input string, stripping any trailing blanks */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, ucString);

    if (!ls) {
        *fswitch = 0;
        return 0;
    } else if (!strncmp(ucString, "ON", 2)) {
        *fswitch = 1;
        return 0;
    } else if (!strncmp(ucString, "OF", 2)) {
        *fswitch = 0;
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "invalid input", (char*)NULL);
        return -1;
    }

}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c D t
**  - - - - - - - -
**
**  Decode two strings containing, respectively, differential tracking
**  rates in either right ascension and declination or azimuth and
**  elevation.
**
**  Given:
**    prefix    char*    prefix to start message
**    frame     int      frame ID
**    string1   char*    string to decode, containing RA/Az rate
**    string2   char*    string to decode, containing Dec/El rate
**
**  Returned (arguments):
**    dr        double*  RA/Az rate (radians per day)
**    dd        double*  Dec/El rate (radians per day)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal rates
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int         minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    AZEL_MNT     FRAMETYPE      frame ID for mount az/el
**    AZEL_TOPO    FRAMETYPE        "   "   "  topocentric az/el
**    APPT         FRAMETYPE        "   "   "  geocentric apparent RA/dec
**    FK5          FRAMETYPE        "   "   "  IAU 1976 RA/dec
**    FK4          FRAMETYPE        "   "   "  pre IAU 1976 RA/dec
**    S2R          double         seconds to radians
**    AS2R         double         arcseconds to radians
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  Incoming units:
**
**         RA         seconds of time per second
**         Dec        arcseconds per second
**         Az         arcseconds per second
**         El         arcseconds per second
**
**    2  A blank or empty string returns zero for that quantity.
**
**    3  If either rate is outside the allowed range (see below),
**       neither is changed and a function value of -1 is returned.
**
**    4  If either rate has been decoded successfully but the string
*        has not been exhausted, the value is returned but with a
**       function value of +2.
**
**    5  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Maximum dRA/dt */
#define MAXDR 10000.0

/* Maximum dDec/dt */
#define MAXDD 10000.0

/* Maximum dAz/dt */
#define MAXDA 10000.0

/* Maximum dAz/dt */
#define MAXDE 10000.0

int tcsDcDt(char *prefix, FRAMETYPE frame, char *string1, char *string2,
            double *dr, double *dd, struct cadRecord *pcad)
{
    int n, j, m;
    double f, vm1, vm2, d1, d2;
    char mesrx[] = "RA rate out of range";
    char mesrb[] = "illegal RA rate";
    char mesdx[] = "Dec rate out of range";
    char mesdb[] = "illegal Dec rate";
    char mesax[] = "Az rate out of range";
    char mesab[] = "illegal Az rate";
    char mesex[] = "El rate out of range";
    char meseb[] = "illegal El rate";
    char *px1, *pb1, *px2, *pb2;

/* Accept the frame ID. */
    switch (frame) {
    case AZEL_MNT:
    case AZEL_TOPO:
        f = AS2R * 86400.0;
        px1 = mesax;
        px2 = mesex;
        pb1 = mesab;
        pb2 = meseb;
        vm1 = MAXDA;
        vm2 = MAXDE;
        break;
    case APPT:
    case FK5:
    case FK4:
        f = S2R * 86400.0;
        px1 = mesrx;
        px2 = mesdx;
        pb1 = mesrb;
        pb2 = mesdb;
        vm1 = MAXDR;
        vm2 = MAXDD;
        break;
    default:
        tcsCsAppendMessageN(pcad, prefix, "illegal frame ID", (char*)NULL);
        return -1;
    }

/* Look for blank input. */
    if (!tcsDcLen(string1) && !tcsDcLen(string2)) {
        *dr = 0.0;
        *dd = 0.0;
        return 0;
    }
/* Decode the RA/Az rate. */
    m = 1;
    d1 = 0.0;
    slaDfltin(string1, &m, &d1, &j);
    if (j < 2) {
        if (fabs(d1) > vm1) {
            tcsCsAppendMessageN(pcad, prefix, px1, (char*)NULL);
            return -1;
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, pb1, (char*)NULL);
        return -1;
    }

/* Decode the Dec/El rate. */
    n = 1;
    d2 = 0.0;
    slaDfltin(string2, &n, &d2, &j);
    if (j < 2) {
        if (fabs(d2) > vm2) {
            tcsCsAppendMessageN(pcad, prefix, px2, (char*)NULL);
            return -1;
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, pb2, (char*)NULL);
        return -1;
    }

/* OK: return the values and verify end of string reached. */
    *dr = d1 * f;
    *dd = d2 * AS2R * 86400.0;
    if ((int) string1[m - 1] == '\0' &&
        (int) string2[n - 1] == '\0') {
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
        return 2;
    }
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - - -
**   t c s D c D o u b l e
**  - - - - - - - - - - - -
**
**  Decode a string containing a double
**
**  Given:
**    prefix    char*     prefix to start message
**    string    char*     string to decode
**
**  Returned (arguments):
**    d         double*  value
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal proper motion
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, a value of 0.0
**       is returned.
**
**    2  If the value has been decoded successfully but
**       the string has not been exhausted, the value is returned
**       but with a function value of +2.
**
**    3  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcDouble(char *prefix, char *string, double *d, struct cadRecord *pcad)
{
    int n, j;
    double p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *d = 0.0;
        return 0;
    }
/* Decode the value. */
    n = 1;
    slaDfltin(string, &n, &p, &j);
    if (j < 1) {

        /* OK: return the value and verify end of string reached. */
        *d = p;
        if ((int) string[n - 1] == '\0') {
            return 0;
        } else {
            tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
            return 2;
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal value", (char*)NULL);
    }
    return -1;
}


/*+
 *   Function name:
 *   tcsDcEncMode
 *
 *   Purpose:
 *   Decode a string representing one of the enclosure operating modes
 *
 *   Description:
 *   The routine decodes an input string to check that it is one of the 
 *   valid operating modes of the enclosure. The match with the valid modes
 *   is case independent and minimum match. If the input string is blank
 *   then the mode defaults to BASIC. The routine returns an identifier of
 *   type ENCMODE and a zero error code if the string is successfully decoded.
 *
 *   Invocation:
 *   status = tcsDcEncMode (prefix, string, &encMode, &cad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *      (>)   prefix   (char *)      Prefix for message
 *      (>)   string   (char *)      String to decode
 *      (<)   encMode  (ENCMODE *)   Enclosure Mode
 *      (!)   cad      (struct cadRecord *) Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, -1 Invalid string
 * 
 *   External functions:
 *   tcsCsAppendMessageN (tcsCadSupport)  Append a message
 *
 *-
 */

int tcsDcEncMode (char *prefix, char *string, ENCMODE *encMode, struct 
                  cadRecord *pcad) 

{
  int n, ls ;
  char ucString[LSUC] ;      /* upper case version of string */

/* Upper case the input string, stripping any trailing blanks */

  n = LSUC - 1 ;
  if (( ls = tcsDcLen(string)) > n)
     ls = n;
  tcsDcUc (string, ls +1, ucString);

  if (!ls) {
    *encMode = BASIC ;
    return 0 ;
  } else if (!strncmp (ucString, "B", 1)) {
    *encMode = BASIC ;
    return 0 ;
  } else if (!strncmp (ucString, "MINV", 4)) {
    *encMode = MINVIBRATION ;
    return 0 ;
  } else if (!strncmp (ucString, "MINS", 4)) {
    *encMode = MINSCATTER ;
    return 0 ;
  } else {
    tcsCsAppendMessageN (pcad, prefix, "invalid input", (char *)NULL) ;
    return -1 ;
  }

}

/* *INDENT-OFF* */
/*
**  - - - - - - - - - - -
**   t c s D c E p o c h
**  - - - - - - - - - - -
**
**  Decode a string containing an epoch (e.g. "J2000").
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    type      int*     'B' = Besselian
**                       'J' = Julian
**    epoch     double*  epoch
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal epoch
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDbjin, slaKbj
**
**  Notes:
**
**    1  If a blank or empty string is supplied, epoch J2000
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the type and epoch are not changed and a function value
**       of -1 is returned.
**
**    3  If the epoch has been decoded successfully but the
**       string has not been exhausted, the type and epoch are
**       returned but with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range */
#define MINEP 1850.0
#define MAXEP 2100.0

int tcsDcEpoch(char *prefix, char *string, char *type, double *epoch, 
   struct cadRecord *pcad)
{
    int n, j1, j2, j;
    char k;
    double e;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *type = 'J';
        *epoch = 2000.0;
        return 0;
    }
/* Decode the epoch. */
    n = 1;
    slaDbjin(string, &n, &e, &j1, &j2);
    if (!j1) {
        if (e >= MINEP && e <= MAXEP) {
            slaKbj(j2, e, &k, &j);
            if (!j) {
                *type = (int) k;
                *epoch = e;

                /* OK: verify end of string reached. */
                if ((int) string[n - 1] == '\0') {
                    return 0;
                } else {
                    tcsCsAppendMessageN(pcad, prefix, "leftover text", 
                       (char*)NULL);
                    return 2;
                }
            } else {
                tcsCsAppendMessageN(pcad, prefix, "prefix not B or J", 
                   (char*)NULL);
                return -1;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "epoch out of range", 
               (char*)NULL);
            return -1;
        }
    }
    tcsCsAppendMessageN(pcad, prefix, "illegal epoch", (char*)NULL);
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - -
**   t c s D c F r a m e
**  - - - - - - - - - - -
**
**  Decode a string containing a frame (coordinate system) name.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    frame     FRAMETYPE*     frame ID
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int      0 = OK
**                      -1 = illegal frame
**                      +1 = blank or null string supplied
**
**  Defined in decodelib.h:
**    LSTRING      int    minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    AZEL_MNT     FRAMETYPE    frame ID for mount az/el
**    AZEL_TOPO    FRAMETYPE      "   "   "  topocentric az/el
**    APPT         FRAMETYPE      "   "   "  geocentric apparent RA/dec
**    FK5          FRAMETYPE      "   "   "  IAU 1976 RA/dec
**    FK4          FRAMETYPE      "   "   "  pre IAU 1976 RA/dec
**
**  Called:  tcsDcUc, tcsDcLen
**
**  Notes:
**
**    1  If a blank or empty string is supplied, a frame ID
**       of FK5 is returned.
**
**    2  If the string does not contain a recognized frame name,
**       the frame ID is not changed and a function value of -1
**       is returned.
**
**    3  Each frame has several aliases:  see the code.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcFrame(char *prefix, char *string, FRAMETYPE * frame, 
   struct cadRecord *pcad)
{
    int n, ls;
    char suc[LSUC];

/* Fold the frame name to uppercase, stripping trailing blanks. */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, suc);

/* Identify frame, return ID, message and status. */
    if (!ls) {
        *frame = FK5;
        return 0;
    } else if (!strcmp(suc, "FK4") ||
               !strcmp(suc, "B1950") ||
               !strcmp(suc, "1950") ||
               !strcmp(suc, "1950.0")) {
        *frame = FK4;
        return 0;
    } else if (!strcmp(suc, "FK5") ||
               !strcmp(suc, "ICRS") ||
               !strcmp(suc, "J2000") ||
               !strcmp(suc, "2000") ||
               !strcmp(suc, "2000.0")) {
        *frame = FK5;
        return 0;
    } else if (!strcmp(suc, "APPT") ||
               !strcmp(suc, "APPARENT") ||
               !strcmp(suc, "GEOCENTRIC APPARENT") ||
               !strcmp(suc, "APPARENT PLACE")) {
        *frame = APPT;
        return 0;
    } else if (!strcmp(suc, "AZ/EL") ||
               !strcmp(suc, "AZEL_TOPO") ||
               !strcmp(suc, "AZEL") ||
               !strcmp(suc, "TOPOCENTRIC AZ/EL") ||
               !strcmp(suc, "TOPOCENTRIC AZ EL")) {
        *frame = AZEL_TOPO;
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "unrecognized frame", (char*)NULL);
        return -1;
    }
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - -
**   t c s D c L o n g
**  - - - - - - - - - -
**
**  Decode a string containing an integer
**
**  Given:
**    prefix    char*     prefix to start message
**    string    char*     string to decode
**
**  Returned (arguments):
**    i         int*     value
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal proper motion
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaIntin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, a value of 0
**       is returned.
**
**    2  If the value has been decoded successfully but
**       the string has not been exhausted, the value is returned
**       but with a function value of +2.
**
**    3  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcLong(char *prefix, char *string, long *i, struct cadRecord *pcad)
{
    int n, j;
    long p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *i = 0;
        return 0;
    }
/* Decode the value. */
    n = 1;
    slaIntin(string, &n, &p, &j);
    if (j < 1) {

        /* OK: return the value and verify end of string reached. */
        *i = p;
        if ((int) string[n - 1] == '\0') {
            return 0;
        } else {
            tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
            return 2;
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal integer", (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c L c
**  - - - - - - - -
**
**  Convert a string to lowercase.
**
**  Given:
**     in      char*    string to be converted
**     lout    int      length of output string (including terminator)
**
**  Returned:
**     out     char*    string after conversion
**
**  Notes:
**
**  1  The *out pointer is also returned as the function value.
**
**  2  The two arguments can refer to the same string.
**
*/
/* *INDENT-ON* */



char *
 tcsDcLc(char *in, int lout, char *out)
{
    int i, c;

    out[lout - 1] = (char) '\0';
    for (i = 0; i < lout; i++) {
        c = (int) in[i];
        out[i] = (char) tolower(c);
        if (c == '\0')
            break;
    }
    return out;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - -
**   t c s D c L e n
**  - - - - - - - - - -
**
**  Length of a string excluding any trailing whitespace.
**
**  Given:
**     *string      char     the string
**
**  Returned (function value):
**                  int      length excluding trailing spaces
**
**  The minimum length returned is 0.
**
*/
/* *INDENT-ON* */




int tcsDcLen(char *string)
{
    int l, i, c;

    l = 0;
    for (i = 0;
         (c = (int) string[i++]) != '\0';
         l = isspace(c) ? l : i);
    return l;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - - -
**   t c s D c P l a n e t
**  - - - - - - - - - - - -
**
**  Decode a string containing a planet name.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    planet    PLANET*  code for planet
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int      0 = OK
**                      -1 = unrecognised name
**                      +1 = blank or null string supplied
**
**  Defined in decodelib.h:
**    LSTRING      int    minimum size of strings to receive messages
**
**  Called:  tcsDcUc, tcsDcLen
**
**  Notes:
**
**    1  If a blank or empty string is supplied, a planert name
**       of NONE is returned.
**
**    2  If the string does not contain a recognized frame name,
**       the planet is not changed and a function value of -1
**       is returned.
**
**    3  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcPlanet(char *prefix, char *string, PLANET * planet, 
   struct cadRecord *pcad)
{
    int n, ls;
    char suc[LSUC];

/* Fold the planet name to uppercase, stripping trailing blanks. */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, suc);

/* Identify frame, return ID, message and status. */
    if (!ls) {
        *planet = NO_PLANET; /* NONE; ...................Rippa 20160430 NONE NOT FOUND*/
        return 0;
    } else if (!strcmp(suc, "MERCURY") ) {
        *planet = MERCURY;
        return 0;
    } else if (!strcmp(suc, "VENUS") ) {
        *planet = VENUS;
        return 0;
    } else if (!strcmp(suc, "MOON") ) {
        *planet = MOON;
        return 0;
    } else if (!strcmp(suc, "MARS") ) {
        *planet = MARS;
        return 0;
    } else if (!strcmp(suc, "JUPITER") ) {
        *planet = JUPITER;
        return 0;
    } else if (!strcmp(suc, "SATURN") ) {
        *planet = SATURN;
        return 0;
    } else if (!strcmp(suc, "URANUS") ) {
        *planet = URANUS;
        return 0;
    } else if (!strcmp(suc, "NEPTUNE") ) {
        *planet = NEPTUNE;
        return 0;
    } else if (!strcmp(suc, "PLUTO") ) {
        *planet = PLUTO;
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "unrecognized planet", (char*)NULL);
        return -1;
    }
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - -
**   t c s D c P m d e c
**  - - - - - - - - - - -
**
**  Decode a string containing a proper motion in Dec (arcsec/year).
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    pmd       double*  proper motion (radians per year)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal proper motion
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    AS2R      double   arcseconds to radians
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, zero proper motion
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the proper motion is not changed and a function value
**       of -1 is returned.
**
**    3  If the proper motion has been decoded successfully but the
**       string has not been exhausted, the value is returned but
*        with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range (ample) */
#define MAXPMD 100.0

int tcsDcPmdec(char *prefix, char *string, double *pmd, struct cadRecord *pcad)
{
    int n, j;
    double p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *pmd = 0.0;
        return 0;
    }
/* Decode the proper motion. */
    n = 1;
    slaDfltin(string, &n, &p, &j);
    if (j < 1) {
        if (fabs(p) <= MAXPMD) {

            /* OK: return the value and verify end of string reached. */
            *pmd = p * AS2R;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, 
               "Dec proper motion out of range", (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal Dec proper motion", 
           (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - - - - -
**   t c s D c O f f C o o r d
**  - - - - - - - - - - - - - -
**
**  Decode a string containing a offset coordinate type.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    coord     OFFCOORD*   offset coordinate type
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int      0 = OK
**                      -1 = illegal name
**                      +1 = blank or null string supplied
**
**  Defined in decodelib.h:
**    LSTRING      int    minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    RADEC        OFFCOORD
**    TANPLANE     OFFCOORD
**
**  Called:  tcsDcUc, tcsDcLen
**
**  Notes:
**
**    1  If the string does not contain a recognized coordinate type,
**       the type is not changed and a function value of -1
**       is returned.
**
**    3  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcOffCoord(char *prefix, char *string, OFFCOORD * coord,
   struct cadRecord *pcad)
{
    int n, ls;
    char suc[LSUC];

/* Fold the coordinate type to uppercase, stripping trailing blanks. */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, suc);

/* Identify coordinate type, return ID, message and status. */
    if (!ls) {
        *coord = RADEC;
        return 0;
    } else if (!strcmp(suc, "RADEC")) {
        *coord = RADEC;
        return 0;
    } else if (!strcmp(suc, "AZEL")) {
        *coord = RADEC;
        return 0;
    } else if (!strcmp(suc, "TANGENT PLANE")) {
        *coord = TANPLANE;
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "unrecognized coordinate type", 
           (char*)NULL);
        return -1;
    }
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - - -
**   t c s D c O f f s e t 
**  - - - - - - - - - - - -
**
**  Decode a string containing a offset in theta2.
**
**  Given:
**    prefix    char*     prefix to start message
**    string    char*     string to decode
**
**  Returned (arguments):
**    dtheta2   double*  offset (radians)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal proper motion
**                       +1 = blank or null string supplied
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, zero proper motion
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the proper motion is not changed and a function value
**       of -1 is returned.
**
**    3  If the offset has been decoded successfully but
**       the string has not been exhausted, the value is returned
**       but with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range (ample) */
#define MAXOFF 3600.0

int tcsDcOffset(char *prefix, char *string, double *dtheta2, 
   struct cadRecord *pcad)
{
    int n, j;
    double p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *dtheta2 = 0.0;
        return 0;
    }
/* Decode the offset. */
    n = 1;
    slaDfltin(string, &n, &p, &j);
    if (j < 1) {
        if (fabs(p) <= MAXOFF) {

            /* OK: return the value and verify end of string reached. */
            *dtheta2 = p;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, 
               "Dec/Elevation offset out of range", (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal Dec/Elevation offset", 
           (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDcOnOff
 *
 *   Purpose:
 *   Check if input string is one of On or Off
 *
 *   Description:
 *   Many parameters to CAD records can take the two values On or Off. This
 *   routine is a general utility that checks the input string for these
 *   two values. If the input string doesn't match (the match is case
 *   insensitive) then an error code and message are returned. If the
 *   string does match then an integer code is returned with 0 indicating
 *   Off and 1 indicating On.
 *
 *   Invocation:
 *   tcsDcOnOff (&prefix, &string, &code, &cad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   prefix   (char *)  Prefix for message
 *      (>)   string   (char *)  String to decode
 *      (<)   code     (int *)   Return code
 *      (<)   pcad     (struct cadRecord *)  CAD record
 *
 *   Function value:
 *   (<)  status  (int)  Return status
 *         0 => OK
 *        -1 => Invalid string
 * 
 *-
 */
/* *INDENT-ON* */



int tcsDcOnOff(char *prefix, char *string, int *code, struct cadRecord *pcad)
{
    int n, ls;
    char ucString[LSUC];        /* upper case version of string */

/* Uppercase the input string, stripping any trailing blanks */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, ucString);

    if (!ls) {
        *code = 0;
        return 0;
    } else if (!strcmp(ucString, "OFF")) {
        *code = 0;
        return 0;
    } else if (!strcmp(ucString, "ON")) {
        *code = 1;
        return 0;
    } else {
        *code = 0;
        tcsCsAppendMessageN(pcad, prefix, "invalid input", (char*)NULL);
        return -1;
    }

}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - -
**   t c s D c P m r a
**  - - - - - - - - - -
**
**  Decode a string containing a proper motion in RA (s/year).
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    pmr       double*  proper motion (radians per year)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal proper motion
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    S2R       double   seconds of time to radians
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, zero proper motion
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the proper motion is not changed and a function value
**       of -1 is returned.
**
**    3  If the proper motion has been decoded successfully but
**       the string has not been exhausted, the value is returned
**       but with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range (ample) */
#define MAXPMR 10.0

int tcsDcPmra(char *prefix, char *string, double *pmr, struct cadRecord *pcad)
{
    int n, j;
    double p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *pmr = 0.0;
        return 0;
    }
/* Decode the proper motion. */
    n = 1;
    slaDfltin(string, &n, &p, &j);
    if (j < 1) {
        if (fabs(p) <= MAXPMR) {

            /* OK: return the value and verify end of string reached. */
            *pmr = p * S2R;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "RA proper motion out of range",
               (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal RA proper motion", 
           (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c P o
**  - - - - - - - -
**
**  Decode a string containing a pointing origin or pointing origin offset.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    po        double*  po (millimetres)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal value
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, zero 
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the pointing origin is not changed and a function value of -1
**       is returned.
**
**    3  If the value has been decoded successfully but the
**       string has not been exhausted, the value is returned but
*        with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range */
#define MAXPO 10000.0

int tcsDcPo(char *prefix, char *string, double *po, struct cadRecord *pcad)
{
    int n, j;
    double p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *po = 0.0;
        return 0;
    }
/* Decode the pointing origin. */
    n = 1;
    slaDfltin(string, &n, &p, &j);
    if (j < 1) {
        if (fabs(p) <= MAXPO) {

            /* OK: return the value and verify end of string reached. */
            *po = p;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "pointing origin out of range", 
               (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal pointing origin", 
           (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c P x
**  - - - - - - - -
**
**  Decode a string containing a stellar parallax.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    parallax  double*  parallax (arcsec)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal parallax
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, zero parallax
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the parallax is not changed and a function value of -1
**       is returned.
**
**    3  If the parallax has been decoded successfully but the
**       string has not been exhausted, the value is returned but
*        with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range (allow for Nemesis) */
#define MAXPX 10.0

int tcsDcPx(char *prefix, char *string, double *parallax, 
   struct cadRecord *pcad)
{
    int n, j;
    double p;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *parallax = 0.0;
        return 0;
    }
/* Decode the parallax. */
    n = 1;
    slaDfltin(string, &n, &p, &j);
    if (j < 1) {
        if (p >= 0.0 && p <= MAXPX) {

            /* OK: return the value and verify end of string reached. */
            *parallax = p;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "parallax out of range", 
               (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal parallax", (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - -
**   t c s D c R a d e c
**  - - - - - - - - - - -
**
**  Decode two strings containing, respectively, either right ascension
**  and declination or azimuth and elevation.
**
**  Given:
**    prefix    char*    prefix to start message
**    frame     int      frame ID
**    string1   char*    string to decode, containing RA/Az
**    string2   char*    string to decode, containing Dec/El
**
**  Returned (arguments):
**    r         double*  RA/Az (radians)
**    d         double*  Dec/El (radians)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal coordinates
**                       +1 = blank or null string supplied
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int         minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    AZEL_MNT     FRAMETYPE      frame ID for mount az/el
**    AZEL_TOPO    FRAMETYPE        "   "   "  topocentric az/el
**    APPT         FRAMETYPE        "   "   "  geocentric apparent RA/dec
**    FK5          FRAMETYPE        "   "   "  IAU 1976 RA/dec
**    FK4          FRAMETYPE        "   "   "  pre IAU 1976 RA/dec
**    D2R          double         degrees to radians
**
**  Called:  tcsDcLen, slaDfltin, slaIntin
**
**  Notes:
**
**    1  The strings contain decimal fields (in free format):
**
**         RA         hours minutes seconds
**         Dec        +/- degrees arcminutes arcseconds
**         Az         degrees
**         El         degrees
**
**    2  The allowed ranges are as follows.
**
**       frame = AZEL_MNT, AZEL_TOPO:
**
**          r from -359.999... to +359.999
**          d from 0 to 90
**
**       frame = APPT, FK4, FK5:
**
**          r from 00 00 00.0 to 23 59 59.999...
**          d from -90 00 00.0 to +90 00 00.0
**
**    3  Azimuth is interpreted as follows.
**
**       frame = AZEL_MNT:
**
**         Supplied values in the range -270 to +360 are interpreted
**         literally.  Supplied values in the range -360 to -270 are
**         expressed in the range 0-90.
**
**       frame = AZEL_TOPO:
**
**         Supplied values are folded into the range 0-360.
**
**    4  If either coordinate is outside the allowed range, neither
**       is changed and a function value of -1 is returned.
**
**    5  If either coordinate has been decoded successfully but the
**       string has not been exhausted, the value is returned but
**       with a function value of +2.
**
**    6  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcRadec(char *prefix, FRAMETYPE frame, char *string1, char *string2,
               double *r, double *d, struct cadRecord *pcad)
{
    char lstr1[LSUC], lstr2[LSUC];
    int n, i, j, m;
    double ar, ed;

/*
   ** -------------
   ** PRELIMINARIES
   ** -------------
 */

/* Look for blank input. */
    if (!tcsDcLen(string1)) {
        tcsCsAppendMessageN(pcad, prefix, "blank RA/Azimuth", 
                   (char*)NULL);
        *r = 0.0;
        *d = 0.0;
        return 1;
    }
    if (!tcsDcLen(string2)) {
        tcsCsAppendMessageN(pcad, prefix, "blank Dec/Elevation", 
                   (char*)NULL);
        *r = 0.0;
        *d = 0.0;
        return 1;
    }

/* Copy input strings replacing colons ith commas. */
    for ( i = 0; i < LSUC; i++ ) {
        lstr1[i] = string1[i] == ':' ? ',' : string1[i];
        if ( lstr1[i] == '\0' ) break;
    }
    if ( i == LSUC) lstr1[ LSUC - 1 ] = '\0';
    for ( i = 0; i < LSUC; i++ ) {
        lstr2[i] = string2[i] == ':' ? ',' : string2[i];
        if ( lstr2[i] == '\0' ) break;
    }
    if ( i == LSUC) lstr2[ LSUC - 1 ] = '\0';
/*
   ** ----------------------------
   ** SWITCH ACCORDING TO FRAME ID
   ** ----------------------------
 */

    switch (frame) {
    case AZEL_MNT:
    case AZEL_TOPO:


        /*
           ** Decode azimuth
           ** --------------
         */

        m = 1;
        slaDafin(lstr1, &m, &ar, &j);

        /* OK if number supplied, and in the range +/-360. */
        if (j < 1) {
            if (fabs(ar) >= PI2) {
                tcsCsAppendMessageN(pcad, prefix, "azimuth out of range", 
                   (char*)NULL);
                return -1;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "illegal azimuth", (char*)NULL);
            return -1;
        }

        /* Fold azimuths outside wrap range. */
        ar = ar > -(PI + D90) ? ar : ar + PI2;


        /*
           ** Decode elevation
           ** ----------------
         */

        n = 1;
        slaDafin(lstr2, &n, &ed, &j);

        /* OK if number supplied, and in the range 0-90. */
        if (j < 1) {
            if (ed < 0.0 || ed > D90) {
                tcsCsAppendMessageN(pcad, prefix, "elevation out of range", 
                   (char*)NULL);
                return -1;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "illegal elevation", 
               (char*)NULL);
            return -1;
        }

        break;

    case APPT:
    case FK5:
    case FK4:


        /*
           ** Decode right ascension
           ** ----------------------
         */

        m = 1;
        slaDafin(lstr1, &m, &ar, &j);
        ar *= 15.0;

        /* Give up if error already. */
        if (j < 0) {
            tcsCsAppendMessageN(pcad, prefix, "illegal RA", (char*)NULL);
            return -1;
        } else {
            if (ar > PI2 || ar < 0.0 ) {
                tcsCsAppendMessageN(pcad, prefix, "RA out of range", 
                   (char*)NULL);
                return -1;
            }
        }

        /*
           ** Decode declination
           ** ------------------
         */

        n = 1;
        slaDafin(lstr2, &n, &ed, &j);

        /* Give up if error already. */
        if (j < 0) {
            tcsCsAppendMessageN(pcad, prefix, "illegal Dec", (char*)NULL);
            return -1;
        } else {
            if (ed > D90 || ed < -D90 ) {
                tcsCsAppendMessageN(pcad, prefix, "Dec out of range", 
                   (char*)NULL);
                return -1;
            }
        }

        break;

    default:
        tcsCsAppendMessageN(pcad, prefix, "illegal frame ID", (char*)NULL);
        return -1;
    }


/*
   ** -------
   ** WRAP UP
   ** -------
 */

/* Return the values and verify end of string reached. */
    *r = ar;
    *d = ed;
    if ((int) lstr1[m - 1] == '\0' &&
        (int) lstr2[n - 1] == '\0') {
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
        return 2;
    }
}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c R v
**  - - - - - - - -
**
**  Decode a string containing a stellar radial velocity (km/s).
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    rv        double*  radial velocity (km/s)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal radial velocity
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, zero radial velocity
**       is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the radial velocity is not changed and a function value
**       of -1 is returned.
**
**    4  If the radial velocity has been decoded successfully but
**       the string has not been exhausted, the value is returned
**       but with a function value of +2.
**
**    5  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Allowed range (ample) */
/*#define MAXRV 1000.0*/
#define MAXRV 299792.458

int tcsDcRv(char *prefix, char *string, double *rv, struct cadRecord *pcad)
{
    int n, j;
    double v;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *rv = 0.0;
        return 0;
    }
/* Decode the radial velocity. */
    n = 1;
    slaDfltin(string, &n, &v, &j);
    if (j < 1) {
        if (fabs(v) <= MAXRV) {

            /* OK: return the value and verify end of string reached. */
            *rv = v;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "RV out of range", (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal RV", (char*)NULL);
    }
    return -1;
}


/*+
 *   Function name:
 *   tcsDcShtrMode
 *
 *   Purpose:
 *   Decode a string representing the shutter operating mode
 *
 *   Description:
 *   The routine decodes an input string to check that it is one of the 
 *   valid operating modes of the shutters. The match with the valid modes
 *   is case independent and minimum match. If the input string is blank
 *   then the mode defaults to FULLYOPEN. The routine returns an identifier of
 *   type SHUTTERMODE and a zero error code if the string is 
 *   successfully decoded.
 *
 *   Invocation:
 *   status = tcsDcShtrMode (prefix, string, &shtrMode, &cad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *      (>)   prefix   (char *)      Prefix for message
 *      (>)   string   (char *)      String to decode
 *      (<)   encMode  (SHUTTERMODE *)   Shutter Mode
 *      (!)   cad      (struct cadRecord *) Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, -1 Invalid string
 * 
 *   External functions:
 *   tcsCsAppendMessageN (tcsCadSupport)  Append a message
 *
 *-
 */

int tcsDcShtrMode (char *prefix, char *string, SHUTTERMODE *shtrMode, struct 
                  cadRecord *pcad) 

{
  int n, ls ;
  char ucString[LSUC] ;      /* upper case version of string */

/* Upper case the input string, stripping any trailing blanks */

  n = LSUC - 1 ;
  if (( ls = tcsDcLen(string)) > n)
     ls = n;
  tcsDcUc (string, ls +1, ucString);

  if (!ls) {
    *shtrMode = FULLYOPEN ;
    return 0 ;
  } else if (!strncmp (ucString, "F", 1)) {
    *shtrMode = FULLYOPEN ;
    return 0 ;
  } else if (!strncmp (ucString, "T", 1)) {
    *shtrMode = TRACKING ;
    return 0 ;
  } else {
    tcsCsAppendMessageN (pcad, prefix, "invalid input", (char *)NULL) ;
    return -1 ;
  }

}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDcString
 *
 *   Purpose:
 *   Decode a string 
 *
 *   Description:
 *   This routine decodes a string by matching it to one of the elements in
 *   a supplied array of strings and returns the index of the matching string.
 *
 *   Invocation:
 *   status = tcsDcString (match, prefix, string, &shtrMode, &cad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *      (>)   match    (char **)     Pointer to array of string to match
 *      (>)   prefix   (char *)      Prefix for message
 *      (>)   string   (char *)      String to decode
 *      (<)   index    (int *)       Index of matching string
 *      (!)   cad      (struct cadRecord *) Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, -1 Invalid string
 * 
 *   External functions:
 *   tcsCsAppendMessageN (tcsCadSupport)  Append a message
 *
 *-
 */

int tcsDcString(char **match, char *prefix, char *string, 
                  int *index, struct cadRecord *pcad) 

{
  int n, ls ;
  char ucString[LSUC] ;      /* upper case version of string */

/* Upper case the input string, stripping any trailing blanks */

  n = LSUC - 1 ;
  if (( ls = tcsDcLen(string)) > n) ls = n;
  tcsDcUc (string, ls +1, ucString);

  for ( *index = 0; match[*index]; (*index)++ ) {
    if (!strcmp (ucString, match[*index])) return 0 ;
  } 
  tcsCsAppendMessageN (pcad, prefix, "invalid input", (char *)NULL) ;
  return -1 ;

}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c T 0
**  - - - - - - - -
**
**  Decode a string containing a reference epoch.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    t0        double*              reference epoch (TT MJD)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**    status    int      +2 = string was blank
**                       +1 = OK, result is fraction of 1 day
**                        0 = OK, result is MJD
**                       -1 = rejected: illegal reference epoch
**                       -2 = rejected: trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin, slaDfltin, slaDtf2d, slaCaldj
**
**  Notes:
**
**    1  Several different formats are accepted, as follows (all
**       numbers are free-format and any number of digits can be
**       used):
**
**       string                   value                 status
**
**       dddddd.d                 MJD                      0
**       yyyy mm dd hh mm ss.s    MJD                      0
**       yy mm dd hh mm ss.s      MJD, 1950-2049 AD        0
**       hh mm ss.s               fraction of a day       +1
**       blank                    0.0                     +2
**
**       If a blank or empty string is supplied, a zero result and
**       a function value +2 are returned.  It is suggested that
**       under these circumstances the calling program sets t0 equal
**       to the current MJD TT, obtained from the Time Service by
**       calling timeNowD.  Thus blank means "now".
**
**       If three fields are presented, this is interpreted as a time
**       of day;  t0 is then in the range 0-1 (unless hours was
**       greater than 24) and the function value is set to +1.  It is
**       suggested that under these circumstances the calling program
**       obtains the current MJD TT from the Time Service by calling
**       timeNowD and adds the integer part to t0.  Thus time-only
**       means "today, at the specified time".  (Use of this technique
**       close to 0 hours is clearly risky in a real-time sense.)
**
**    2  If the epoch is outside the allowed range (see below), it is
**       not changed and a function value of -1 is returned.
**
**    3  If the epoch has been decoded successfully but the string has
**       not been exhausted, a value is returned but with a function
**       value of -2.
**
**    4  See the code for the various messages that can result.
**
**    5  MJD means JD minus 2400000.5.  Single numbers less than
**       2400000.5 are interpreted as MJD, otherwise JD is assumed.
**
*/
/* *INDENT-ON* */



/* Allowed MJD range */
#define MINT0 10000.0
#define MAXT0 100000.0

int tcsDcT0(char *prefix, char *string, double *t0, struct cadRecord *pcad)
{
    int n, i, j;
    long iy, imo, id, ih, im;
    double d, s, t;


/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *t0 = 0.0;
        return 2;
    }
    
/* Decode up to seven +ve doubles. */
    i = 1;
    for (n = 0; n < 7; n++) {
        slaDfltin(string, &i, &d, &j);
        if (j == 1) {
            break;
        } else if (j) {
            n = 0;
            break;
        }
    }

/* If all is well, the field count should now be 1, 3 or 6. */

/* Examine number of fields. */
    if (n == 1) {

        /* Handle JD/MJD case. */
        i = 1;
        slaDfltin(string, &i, &d, &j);
        if (j) {
            n = 0;
        } else {
            if (d >= 2400000.5)
                d -= 2400000.5;
        }
            
    } else if (n == 3) {

        /* Handle time-of-day case. */
        d = 0.0;
        i = 1;
        slaIntin(string, &i, &ih, &j);
        if (j)
            n = 0;
        slaIntin(string, &i, &im, &j);
        if (j)
            n = 0;
        slaDfltin(string, &i, &s, &j);
        if (j)
            n = 0;
        slaDtf2d((int) ih, (int) im, s, &d, &j);
        if (j)
            n = 0;

    } else if (n == 6) {

        /* Handle full date and time case. */
        d = 0.0;
        i = 1;
        slaIntin(string, &i, &iy, &j);
        if (j)
            n = 0;
        slaIntin(string, &i, &imo, &j);
        if (j)
            n = 0;
        slaIntin(string, &i, &id, &j);
        if (j)
            n = 0;
        slaCaldj((int) iy, (int) imo, (int) id, &d, &j);
        if (j)
            n = 0;
        slaIntin(string, &i, &ih, &j);
        if (j)
            n = 0;
        slaIntin(string, &i, &im, &j);
        if (j)
            n = 0;
        slaDfltin(string, &i, &s, &j);
        if (j)
            n = 0;
        slaDtf2d((int) ih, (int) im, s, &t, &j);
        if (j)
            n = 0;
        d += t;

    } else {
        n = 0;
    }
/* Return value and status as appropriate. */
    if (n > 0) {
        if (n == 3 || (d >= MINT0 && d <= MAXT0)) {

            /* OK: return the value and verify end of string reached. */
            *t0 = d;
            if ((int) string[i - 1] == '\0') {
                return n == 3 ? 1 : 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return -2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "epoch out of range", 
               (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal epoch", (char*)NULL);
    }
    return -1;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - -
**   t c s D c T e l
**  - - - - - - - - -
**
**  Decode a string containing a telescope name.
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    tel       TELESCOPE*  telescope
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int      0 = OK
**                      -1 = illegal name
**
**  Defined in decodelib.h:
**    LSTRING      int    minimum size of strings to receive messages
**
**  Defined in tcsConstants.h:
**    MOUNT        TELESCOPE    telescope ID for mount
**    SOURCE_A     TELESCOPE         "   "    "  source chop state A
**    SOURCE_B     TELESCOPE         "   "    "    "      "    "   B
**    SOURCE_C     TELESCOPE         "   "    "    "      "    "   C
**    PWFS1        TELSCOPE          "   "    "  PWFS1
**    PWFS2        TELSCOPE          "   "    "  PWFS2
**    OIWFS        TELSCOPE          "   "    "  OIWFS
**
**  Called:  tcsDcUc, tcsDcLen
**
**  Notes:
**
**    1  If the string does not contain a recognized telescope name,
**       the telescope ID is not changed and a function value of -1
**       is returned.
**
**    2  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



int tcsDcTel(char *prefix, char *string, TELESCOPE * tel, 
   struct cadRecord *pcad)
{
    int n, ls;
    char suc[LSUC];

/* Fold the telescope name to uppercase, stripping trailing blanks. */
    n = LSUC - 1;
    if ((ls = tcsDcLen(string)) > n)
        ls = n;
    tcsDcUc(string, ls + 1, suc);

/* Identify telescope, return ID, message and status. */
    if (!ls) {
        *tel = MOUNT;
        return 0;
    } else if (!strcmp(suc, "MOUNT")) {
        *tel = MOUNT;
        return 0;
    } else if (!strcmp(suc, "SOURCE_A")) {
        *tel = SOURCE_A;
        return 0;
    } else if (!strcmp(suc, "SOURCE_B")) {
        *tel = SOURCE_B;
        return 0;
    } else if (!strcmp(suc, "SOURCE_C")) {
        *tel = SOURCE_C;
        return 0;
    } else if (!strcmp(suc, "PWFS1")) {
        *tel = PWFS1;
        return 0;
    } else if (!strcmp(suc, "PWFS2")) {
        *tel = PWFS2;
        return 0;
    } else if (!strcmp(suc, "OIWFS")) {
        *tel = OIWFS;
        return 0;
    } else {
        tcsCsAppendMessageN(pcad, prefix, "unrecognized telescope!", 
           (char*)NULL);
        return -1;
    }
}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c U c
**  - - - - - - - -
**
**  Convert a string to uppercase.
**
**  Given:
**     in      char*    string to be converted
**     lout    int      length of output string (including terminator)
**
**  Returned:
**     out     char*    string after conversion
**
**  Notes:
**
**  1  The *out pointer is also returned as the function value.
**
**  2  The two arguments can refer to the same string.
**
*/
/* *INDENT-ON* */



char *
 tcsDcUc(char *in, int lout, char *out)
{
    int i, c;

    out[lout - 1] = (char) '\0';
    for (i = 0; i < lout - 1; i++) {
        c = (int) in[i];
        out[i] = (char) toupper(c);
        if (c == '\0')
            break;
    }
    return out;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - -
**   t c s D c W l
**  - - - - - - - -
**
**  Decode a string containing an effective wavelength (microns).
**
**  Given:
**    prefix    char*    prefix to start message
**    string    char*    string to decode
**
**  Returned (arguments):
**    wl        double*  wavelength (microns)
**    pcad      struct cadRecord *   CAD record
**
**  Returned (function value):
**              int       0 = OK
**                       -1 = illegal wavelength
**                       +2 = OK but trailing garbage
**
**  Defined in decodelib.h:
**    LSTRING   int      minimum size of strings to receive messages
**
**  Called:  tcsDcLen, slaDfltin
**
**  Notes:
**
**    1  If a blank or empty string is supplied, a wavelength of
**       0.55 micron is returned.
**
**    2  If the value is outside the allowed range (see below),
**       the wavelength is not changed and a function value
**       of -1 is returned.
**
**    3  If the wavelength has been decoded successfully but the
**       string has not been exhausted, the value is returned but
**       with a function value of +2.
**
**    4  See the code for the various messages that can result.
**
*/
/* *INDENT-ON* */



/* Shortest wavelength allowed */
#define MINWL 0.2

int tcsDcWl(char *prefix, char *string, double *wl, struct cadRecord *pcad)
{
    int n, j;
    double w;

/* Look for blank input. */
    if (!tcsDcLen(string)) {
        *wl = 0.55;
        return 0;
    }
/* Decode the wavelength. */
    n = 1;
    slaDfltin(string, &n, &w, &j);
    if (j == 0) {
        if (w >= MINWL) {

            /* OK: return the value and verify end of string reached. */
            *wl = w;
            if ((int) string[n - 1] == '\0') {
                return 0;
            } else {
                tcsCsAppendMessageN(pcad, prefix, "leftover text", (char*)NULL);
                return 2;
            }
        } else {
            tcsCsAppendMessageN(pcad, prefix, "wavelength out of range", 
               (char*)NULL);
        }
    } else {
        tcsCsAppendMessageN(pcad, prefix, "illegal wavelength", (char*)NULL);
    }
    return -1;
}

/*+
 *   Function name:
 *   tcsDcNotEmpty
 *
 *   Purpose:
 *   Check if a string has any alphanumeric characters
 *
 *   Description:
 *   Check each character in a null terminated string to see if it is
 *   alphanumeric. If there are any alphanumeric characters then return
 *   true otherwise return false.
 *
 *   Invocation:
 *   status = tcsDcNotEmpty(s)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    s        (char *)   Null terminated string
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = FALSE otherwise TRUE
 *
 *   Deficiencies:
 *   What happens if the string isn't terminated with a NULL ?
 *
 *-
 */

int tcsDcNotEmpty (char *s)

{
  int status = FALSE ;

  while (*s != '\0') {
   if (isalnum((int)*s)){
    status = TRUE ;
    break ;
   }
   s++ ;
  }

  return status ;
}

