/*
*   FILENAME
*   tcsSeqmacros.h
*
*   DESCRIPTION
*   This file contains useful macros for TCS sequence programs. They
*   were originally copied from the the Keck and then added to.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSeqMacros.h,v $
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
 * Revision 1.1.1.1  1998/11/08 00:21:13  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:11:13  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.3  1996/12/02 08:09:12  cjm
 * Fixes for initial az, el and debug level
 *
 * Revision 1.2  1996/11/28 08:11:01  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.1  1996/06/13 13:08:59  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#ifndef TCSSEQMACROSH
#define TCSSEQMACROSH

#define ASSVAR( _type, _intvar, _pvname) \
        _type _intvar; assign _intvar to _pvname

#define ASSNOVAR( _type, _intvar) \
        _type _intvar; assign _intvar to ""

#define MONVAR( _type, _intvar, _pvname) \
        ASSVAR( _type, _intvar, _pvname); monitor _intvar

/* N.B. These macros are defined this way to use them in sequence programs
*  that are re-entrant. They may cause problems with nested braces. However
*  the Keck trick of surrounding the macro with a %%do ... while(0) won't
*  work in a re-entrant sequence program. The snc changes dbgLevel to
*  pvar->dbgLevel and then the compiler decalres that dbgLevel is not
*  defined.
*/

#define DBGMSG( _dbgLevel, _dbgMsg) \
 if (dbgLevel & ( _dbgLevel) ) epicsPrintf ("%s", _dbgMsg) ; \

#define DBGMSGPREFIX( _dbgLevel,  _userPrefix, _dbgMsg) \
 if (dbgLevel & ( _dbgLevel) ) epicsPrintf ("%s: %s", _userPrefix, _dbgMsg) ; \

#define DBGMSGREAL( _dbgLevel, _dbgMsg, _dbgFloat) \
 if (dbgLevel & ( _dbgLevel) ) epicsPrintf ("%s %f\n",  _dbgMsg, _dbgFloat) ; \

#endif
