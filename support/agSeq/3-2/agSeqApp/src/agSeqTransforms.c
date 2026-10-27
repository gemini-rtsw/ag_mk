/*
*   FILENAME
*   agSeqTransforms.c
*
*   FUNCTION NAME(S)
*   agSeqAoDeployed    - set flag depending on whether AO fold is deployed
*   agSeqInitTransform - initialise this library
*   agSeqGmosXy2Tcs - convert GMOS x,y coordinates to TCS coords.
*   agSeqGmosZ2Tcs - convert GMOS Z coordinates to TCS coords.
*   agSeqNiriXy2Tcs - convert NIRI x,y coordinates to TCS coords.
*   agSeqNiriZ2Tcs - convert NIRI Z coordinates to TCS coords.
*   agSeqNifsZ2Tcs - convert NIFS Z coordinates to TCS coords.
*   agSeqNifsXy2Tcs - convert NIFS x,y coordinates to TCS coords.
*   agSeqNirsXy2Tcs - convert GNIRS x,y coordinates to TCS coords.
*   agSeqNirsZ2Tcs - convert GNIRS Z coordinates to TCS coords.
*   agSeqF2Xy2Tcs - convert Flamingos-2 x,y coordinates to TCS coords.
*   agSeqF2Z2Tcs - convert F2 Z coordinates to TCS coords.
*   agSeqNifsXy2Tcs - convert NIFS x,y coordinates to TCS coords.
*   agSeqNifsZ2Tcs - convert NIFS coordinates to TCS coords.
*   agSeqNiciXy2Tcs - convert NICI x,y coordinates to TCS coords.
*   agSeqNiciZ2Tcs - convert NICI Z coordinates to TCS coords.
*   agSeqOiwfsCoeffs - select coefficients for current oiwfs and port
*   agSeqOiwfsPort   - keep port number updated and display coefficients
*   agSeqOiwfsXy2xy - perform an x,y transformation for the OIWFS 
*   agSeqOiwfsZ2z   - perform a z coordinate transformation for the OIWFS
*   agSeqSetOiwfsTransform - set the parameters that define the OIWFS transform
*
*   Copyright Observatory Sciences Ltd. 2000 All rights reserved.
*/
/* *INDENT-OFF* */
/*
 * $Log: agSeqTransforms.c,v $
 * Revision 1.10  2009/11/19 20:21:10  gemvx
 * use a tcs flag rather than aoFold position to determine if we are using AO
 *
 * Revision 1.9  2007/05/18 22:37:42  pedro
 * Added NICI to the A&G sequencer code
 *
 * Revision 1.8  2005/08/01 19:36:52  anunez
 * Added support for NIFS
 *
 * Revision 1.7  2005/06/30 20:41:28  anunez
 * Implemented ability to apply offsets in X and Y when bHROS is used
 *
 * Revision 1.6  2005/06/23 23:14:43  anunez
 * Modifications for Flamingos-2
 *
 * Revision 1.5  2004/02/12 23:18:49  cjm
 * Add routines for NIRS transforms
 *
 * Revision 1.4  2002/11/24 12:36:59  cjm
 * Extend to handle AO
 *
 * Revision 1.3  2001/10/04 08:44:42  cjm
 * Remove many instrument specific routines and replace with generic ones
 *
 * Revision 1.2  2001/08/09 19:09:40  pedro
 * GMOS fixes during commisioning first commisioning run
 *
 * Revision 1.1  2001/06/20 18:27:22  gemvx
 * Moved file from directory one level up
 *
 * Revision 1.4  2001/06/19 21:52:40  gemvx
 * Handle the different ports NIRI can be mounted on
 *
 * Revision 1.3  2001/03/22 16:25:23  cjm
 * Fix display of transformed coords
 *
 * Revision 1.2  2001/01/24 08:21:52  cjm
 * Include string.h to avoid warnings when compiling for power PC
 *
 * Revision 1.1  2000/09/29 10:16:41  cjm
 * File to hold routines that provide coordinate transformation routines for NIRI
 *
 *
 */
/* *INDENT-ON* */


#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <epicsStdioRedirect.h>
#include <epicsStdlib.h>
#include <epicsEvent.h>
#include <epicsPrint.h>
#include <iocsh.h>
#include <string.h>
#include <ctype.h>

#include <genSubRecord.h>

#include <slalib.h>
#include <slamac.h>

#include <agSeqTransforms.h>

epicsMutexId transformSemId ;  /* Mutex to guard updates to data */

static double oiwfs2tcs[2][MAXOIWFS][6][6] = {
	                      {{{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
                               {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
                               {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}}, 
	                      {{{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
			       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
			       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}} 
                               };

static double tcs2oiwfs[2][MAXOIWFS][6][6] = {
	                      {{{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
			       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
			       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}}, 
	                      {{{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}, 
	                       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
			       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
			       {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, 
	                        {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}} 
                               };

static double oiwfsFocusScale[MAXOIWFS] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0} ;
static double oiwfsFocusZero[MAXOIWFS]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} ;

static int currentPort[MAXOIWFS] = {0, 0, 0, 0, 0, 0, 0, 0, 0} ; /* Default to not mounted  */

static int initTransform = 0 ;     /* Flag to indicate if library is inited */

static long aoDeployed = 0 ;       /* Flag for AO fold */

/*+
 *   Function name:
 *   agSeqAoDeployed
 *
 *   Purpose:
 *   Set flag if the tcs is configured in AO mode
 *
 *   Description:
 *   Read the UseAO state from the TCS and set a flag (for oi-ao blending targets)
 *
 *   Invocation:
 *   agSeqAoDeployed(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *      a = > Named position of the AO fold 
 *
 *   Epics outputs:
 *      vala => State of fold (1 = IN 0 = OUT)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqAoDeployed (struct genSubRecord *pgsub)
{

  if (!strcmp(pgsub->a, "Yes")) {
    aoDeployed = 1 ;
  } else {
    aoDeployed = 0 ;
  }
  
  *(long *)pgsub->vala = aoDeployed ; 

  return 0 ;

}


/*+
 *   Function name:
 *   agSeqInitTransform
 *
 *   Purpose:
 *   Initialise the mutex that guards the transform coefficients
 *
 *   Description:
 *   Simply create the semaphore and set the initialisation flag
 *
 *   Invocation:
 *   agSeqInitTransform(void)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *   Deficiencies:
 *   There is no check that the semaphore is actually created
 *
 *-
 */

void agSeqInitTransform (void) 
{
  if (!initTransform) {
    transformSemId = epicsMutexMustCreate () ;
    initTransform = TRUE ;
  }
}

/*+
 *   Function name:
 *   agSeqOiwfsCoeffs
 *
 *   Purpose:
 *   Output the current transformation coefficients for the current OIWFS
 *
 *   Description:
 *   The index of the current OIWFS is fetched and then the transformation
 *   coefficients for that OIWFS are output as an array for access by
 *   other EPICS systems e.g. the TCS. Note that the coefficients exported
 *   are those that transform an x, y from the TCS frame to the OIWFS
 *   frame.
 *
 *   Invocation:
 *   agSeqOiwfsCoeffs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *      a = > index to OIWFS
 *
 *   Epics outputs:
 *      valj => array of 6 transformation coefficients
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long agSeqOiwfsCoeffs (struct genSubRecord *pgsub)
{
  int oiwfs ;

  oiwfs = (int) (*(long *)pgsub->a) ;

  memcpy (pgsub->valj, tcs2oiwfs[aoDeployed][oiwfs][currentPort[oiwfs]], 
          6*sizeof(double));

  return 0 ;
}

/*+
 *   Function name:
 *   agSeqOiwfsPort
 *
 *   Purpose:
 *   Update the port number for the OIWFS and display current coefficients
 *
 *   Description:
 *   This routine reads the current port number for a specified OIWFS 
 *   and uses this to compute and then display the current
 *   conversion coefficients between TCS and OIWFS coordinates.
 *
 *   Invocation:
 *   agSeqOiwfsPort(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Index to OIWFS
 *   b => OIWFS port number 
 *   c => 1 = Coeffs with AO 0 = Coeffs without AO
 *
 *   Epics outputs:
 *   vala => Orientation (degs) 
 *   valb => Non-perp (degs)
 *   valc => X scale
 *   vald => Y scale
 *   vale => X zero point
 *   valf => Y zero point
 *   valg => Focus scale
 *   valh => Focus zero point
 *   valj => Array of current transformation coefficients
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqOiwfsPort (struct genSubRecord *pgsub) 
{
  double xz, yz ;    /* Transform zero points */
  double xs, ys ;    /* Transform scales */
  double orient ;    /* Orientation of frames (rads) */
  double nonperp ;   /* Non-perp of frames (rads) */
  int oiwfs;         /* Index for instrument */
  int port ;         /* Port for this instrument */
  int aoDeployed;    /* Flag for AO coefficients */

  oiwfs = (int)(*(long *)pgsub->a) ;
  port  = (int)(*(long *)pgsub->b) ;
  aoDeployed = (int)(*(long *)pgsub->c) ;
  currentPort[oiwfs] = port ;

/* Decompose into scales zero points etc. */
  slaDcmpf (oiwfs2tcs[aoDeployed][oiwfs][port], &xz, &yz, &xs, &ys, 
            &nonperp, &orient) ;

/* Output to EPICS links */
  *(double *)pgsub->vala = orient / DD2R ;
  *(double *)pgsub->valb = nonperp / DD2R ;
  *(double *)pgsub->valc = xs ;
  *(double *)pgsub->vald = ys ;
  *(double *)pgsub->vale = xz ;
  *(double *)pgsub->valf = yz ;
  *(double *)pgsub->valg = oiwfsFocusScale[oiwfs] ;
  *(double *)pgsub->valh = oiwfsFocusZero[oiwfs] ;
  memcpy (pgsub->valj, tcs2oiwfs[aoDeployed][oiwfs][port], 6 *sizeof(double));

  return 0 ;

}

/*+
 *   Function name:
 *   agSeqOiwfsXy2xy
 *
 *   Purpose:
 *   Transform OIWFS coordinates from one x,y frame to another
 *
 *   Description:
 *   The routine transforms a set of coordinates xin, yin to another set
 *   xout, yout according to the formulae xout = a + b*xin + c*yin,
 *   yout = d + e*xin + f*yin. The coefficients of the transform are
 *   copied from the global database to local values under the protection
 *   of a semaphore. This ensures a consistent set of parameters is always
 *   used, even if the user is in the middle of updating them. Whether
 *   TCS coords are converted to OIWFS coords or vice versa is determined
 *   by a flag. If true then TCS coords are transformed to OIWFS coords. If
 *   false then OIWFS coords transform to TCS coords.
 *
 *   Invocation:
 *   agSeqOiwfsXy2xy (oiwfs, direction, xin, yin, &xout, &yout)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    oiwfs     (int)      Index to oiwfs 
 *      (>)    direction (int)      Flag to control direction of transform
 *      (>)    xin       (double)   Input x coordinate
 *      (>)    yin       (double)   Input y coordinate
 *      (<)    xout      (double *) Output x coordinate
 *      (<)    xout      (double *) Output y coordinate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void agSeqOiwfsXy2xy (int oiwfs, int direction, double xin, double yin,
                     double *xout, double *yout) 
{

  int i ;             /* loop index */
  double params[6] ;  /* local copies of the transform coefficients */

  if (!initTransform) 
    agSeqInitTransform() ;

  epicsMutexLock(transformSemId) ;
  if (direction) {
    for ( i = 0; i < 6 ; i++) {
     params[i] = tcs2oiwfs[aoDeployed][oiwfs][currentPort[oiwfs]][i] ;
    }
  } else {
    for ( i = 0; i < 6 ; i++) {
     params[i] = oiwfs2tcs[aoDeployed][oiwfs][currentPort[oiwfs]][i] ;
    }
  }
  epicsMutexUnlock(transformSemId) ;
  
  *xout = params[0] + params[1] * xin + params[2] * yin ;
  *yout = params[3] + params[4] * xin + params[5] * yin ;

}


/*+
 *   Function name:
 *   agSeqOiwfsZ2z
 *
 *   Purpose:
 *   Transform OIWFS coordinates from one z frame to another
 *
 *   Description:
 *   This routine is complementary to agSeqOiwfsXy2xy and transforms the
 *   focus scale from the TCS frame to the OIWFS frame or vice versa.
 *   A simple linear transformation is provided with protection against
 *   division by zero along with guarantees that the coefficients of the
 *   transformation are always consistent.
 *
 *   Invocation:
 *   agSeqOiwfsZ2z (oiwfs, direction, zin, &zout)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    oiwfs     (int)      Index to oiwfs
 *      (>)    direction (int)      Flag to control direction of transform
 *      (>)    zin       (double)   Input z coordinate
 *      (<)    zout      (double *) Output z coordinate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void agSeqOiwfsZ2z (int oiwfs, int direction, double zin, double *zout) 
{

  double params[2] ;  /* local copies of the transform coefficients */

  if (!initTransform) 
    agSeqInitTransform() ;

  epicsMutexLock(transformSemId) ;
  if (direction) {
    if (oiwfsFocusScale[oiwfs] != 0) {
       params[1] = 1.0/oiwfsFocusScale[oiwfs] ;
       params[0] = -oiwfsFocusZero[oiwfs] * params[1] ;
    } else {
       params[0] = 0.0 ;
       params[1] = 0.0 ;
    }
  } else {
    params[0] = oiwfsFocusZero[oiwfs] ;
    params[1] = oiwfsFocusScale[oiwfs] ;
  }
  epicsMutexUnlock(transformSemId) ;
  
  *zout = params[0] + params[1] * zin ;

}

/*+
 *   Function name:
 *   agSeqSetOiwfsTransform
 *
 *   Purpose:
 *   Set the parameters of the transform between TCS and OIWFS coordinates.
 *   
 *   Description:
 *   The parameters of the transformation are read in in the format most
 *   useful to a user i.e. the relative orientation and non perpendicularity,
 *   scales in x and y and zero points. These parameters are defined for
 *   the sense OIWFS -> TCS. These 6 parameters are then transformed into
 *   the format xn = a +b*xt + c*yt, yn = d + e*xt + f*yt. The slalib routine
 *   slaInvf is then used to derive the inverse transformation and both
 *   sets of coefficients are stored for later use.
 *
 *   Invocation:
 *   agSeqSetOiwfsTransform (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub   (struct gensubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => relative orientation (degs)
 *   b => non-perpendicularity (degs)
 *   c => x scale ;
 *   d => y scale ;
 *   e => x zero point ;
 *   f => y zero point ;
 *   g => focus scale ;
 *   h => focus zero point ;
 *   i => port number
 *   j => index to OIWFS
 *   k => 0 for non-ao coefficients 1 for ao coefficients
 *
 *   Epics outputs:
 *   vala => array of affine coeffs to take OIWFS coords into TCS coords
 *   valb => array of affine coeffs to take TCS coords into OIWFS coords
 *   valc => current relative orientation (degs)
 *   vald => current non-perpendicularity (degs)
 *   vale => current x scale ;
 *   valf => current y scale ;
 *   valg => current x zero point ;
 *   valh => current y zero point ;
 *   vali => current focus scale ;
 *   valj => current focus zero point ;
 *
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   slaInvf        (slalib)   Invert an affine transform
 *-
 */

long agSeqSetOiwfsTransform (struct genSubRecord *pgsub) 
{

  double orient ;             /* Relative orientation (rads) */
  double nonperp ;            /* Non perpendicularity (degs) */
  double xscale, yscale ;     /* Scales in x and y */
  double xzero, yzero ;       /* Zero points in x and y */
  double focusScale ;         /* Focus scaling */
  double focusZero ;          /* Focus zero point */

  double costh, sinth ;       /* cos/sine of orientation */
  double cosp2, sinp2 ;       /* cos/sine of non-perp semi-angle */
  double Acoeff, Bcoeff ;
  double Ccoeff, Dcoeff ;     /* Intermediate variables */
 
  double localo2t[6] ;        /* Local copy of oiwfs to tcs params */ 
  double localt2o[6] ;        /* Local copy of tcs to oiwfs params */
 
  int jstat ;                 /* Status from inversion */
  int i ;                     /* Loop counter */
  int port ;                  /* Port number for this transform */
  int oiwfs ;                 /* Index to oiwfs */
  int ao ;                    /* 1 for AO coefficients */

/* Read in all user data. Note there is no check on the validity. This is
*  assumed done at the EPICS level.
*/
  orient = *(double *)pgsub->a * DD2R ;
  nonperp = *(double *)pgsub->b * DD2R ;
  xscale  = *(double *)pgsub->c ;
  yscale  = *(double *)pgsub->d ;
  xzero   = *(double *)pgsub->e ;
  yzero   = *(double *)pgsub->f ;
  focusScale = *(double *)pgsub->g;
  focusZero  = *(double *)pgsub->h;
  port    = (int) (*(long *)pgsub->i) ;
  oiwfs   = (int) (*(long *)pgsub->j) ;
  ao      = (int)(*(long *)pgsub->k) ;

/* Convert these numbers into the corresponding affine connection coeffs */
  costh = cos(orient) ;
  sinth = sin(orient) ;
  cosp2 = cos(nonperp/2) ;
  sinp2 = sin(nonperp/2) ;
  Acoeff = costh * cosp2 + sinth * sinp2 ;
  Bcoeff = costh * sinp2 + sinth * cosp2 ;
  Ccoeff = costh * sinp2 - sinth * cosp2 ;
  Dcoeff = costh * cosp2 - sinth * sinp2 ;

  localo2t[1] = Acoeff * xscale ;
  localo2t[2] = Bcoeff * yscale ;
  localo2t[0] = localo2t[1] * xzero + localo2t[2] * yzero ;
  localo2t[4] = Ccoeff * xscale ;
  localo2t[5] = Dcoeff * yscale ;
  localo2t[3] = localo2t[4] * xzero + localo2t[5] * yzero ;

  if (xscale < 0.0) {
    localo2t[2] = -localo2t[2] ;
    localo2t[4] = -localo2t[4] ;
  }
  
/* Invert the transformation */
  slaInvf (localo2t, localt2o, &jstat) ;
  
/* If inversion was successful then we have a valid set of coefficients to
*  transform OIWFS coords to TCS and vice versa so store these away for
*  later use
*/

   if (!transformSemId)
     printf("Semaphore transformSemId not created!! Not initializing matrixes!\n");
   if (jstat == 0 && transformSemId) {
      epicsMutexLock(transformSemId) ;
      for (i = 0; i < 6 ; i++) {
         oiwfs2tcs[ao][oiwfs][port][i] = localo2t[i] ;
         tcs2oiwfs[ao][oiwfs][port][i] = localt2o[i] ;
      }
    oiwfsFocusScale[oiwfs] = focusScale ;
    oiwfsFocusZero[oiwfs]  = focusZero ;
    epicsMutexUnlock(transformSemId) ;
    memcpy (pgsub->vala, localo2t, 6 * sizeof(double)) ;
    memcpy (pgsub->valb, localt2o, 6 * sizeof(double)) ;
    *(double *)pgsub->valc = orient/DD2R ;
    *(double *)pgsub->vald = nonperp/DD2R ;
    *(double *)pgsub->vale = xscale ;
    *(double *)pgsub->valf = yscale ;
    *(double *)pgsub->valg = xzero ;
    *(double *)pgsub->valh = yzero ;
    *(double *)pgsub->vali = focusScale ;
    *(double *)pgsub->valj = focusZero ;
  }

  return 0 ;
}

/*----------------------------------- GMOS -------------------------------*/

/*+
 *   Function name:
 *   agSeqGmosXy2Tcs
 *
 *   Purpose:
 *   Convert GMOS x,y coordinates into the TCS frame of reference
 *
 *   Description:
 *   This function assumes a linear correspondence between the x,y 
 *   coordinate frame of the GMOS OIWFS and the TCS one. The relationship
 *   is xt = a + b*xn + c*yn, yt = d + e*xn + f*yn. 
 *
 *   Invocation:
 *   agSeqGmosXy2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => GMOS x coordinate
 *   b => GMOS y coordinate
 *
 *   Epics outputs:
 *   vala => TCS x coordinate (mm in focal plane)
 *   valb => TCS y coordinate (mm in focal plane) 
 *   valc => GMOS raw x coordinate
 *   vald => GMOS raw y coordinate
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqGmosXy2Tcs (struct genSubRecord *pgsub) 
{
  double xn, yn ;     /* GMOS coords */
  double xt, yt ;     /* TCS coords mm in focal plane */
  int useOffsets = 0; /* Flag to decide if we should apply offsets or not */
  double xOffset = 0.0, yOffset = 0.0; /* Offsets in X and Y */
  xn = *(double *)pgsub->a ;
  yn = *(double *)pgsub->b ;

  agSeqOiwfsXy2xy (GMOS, GMOS2TCS, xn, yn, &xt, &yt) ;

  /* Determine if we should use offset or not */
  /* Offset only if the instrument is used in conjunction with bHROS */

  if (strcmp( (char *)pgsub->e, "BHROS" ) == 0) {
    useOffsets = 1;
  }

  if (useOffsets) {
    xOffset = *(double *)pgsub->c;
    yOffset = *(double *)pgsub->d;
  }
  

  *(double *)pgsub->vala = xt - xOffset;
  *(double *)pgsub->valb = yt - yOffset;
  *(double *)pgsub->valc = xn ;
  *(double *)pgsub->vald = yn ;
  
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqGmosZ2Tcs
 *
 *   Purpose:
 *   Convert GMOS focus coordinate into the TCS frame of reference
 *
 *   Description:
 *   Convert the GMOS focus value by a simple linear transformation to
 *   the TCS frame of reference.
 *
 *   Invocation:
 *   agSeqGmosZ2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => GMOS z coordinate
 *
 *   Epics outputs:
 *   vala => TCS z coordinate (mm)
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqGmosZ2Tcs (struct genSubRecord *pgsub) 
{
  double zn ;     /* GMOS coord */
  double zt ;     /* TCS coord (mm) */

  zn = *(double *)pgsub->a ;

  agSeqOiwfsZ2z (GMOS, GMOS2TCS, zn, &zt) ;

  *(double *)pgsub->vala = zt ;
  
  return 0 ;

}

/*------------------------------NIRS----------------------------*/   

/*+
 *   Function name:
 *   agSeqNirsXy2Tcs
 *
 *   Purpose:
 *   Convert Nirs x,y coordinates into the TCS frame of reference
 *
 *   Description:
 *   This function assumes a linear correspondence between the x,y 
 *   coordinate frame of the Nirs OIWFS and the TCS one. The relationship
 *   is xt = a + b*xn + c*yn, yt = d + e*xn + f*yn. 
 *
 *   Invocation:
 *   agSeqNirsXy2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Nirs x coordinate
 *   b => Nirs y coordinate
 *
 *   Epics outputs:
 *   vala => TCS x coordinate (mm in focal plane)
 *   valb => TCS y coordinate (mm in focal plane) 
 *   valc => Raw Nirs coordinate in "X"
 *   vald => Raw Nirs coordinate in "Y"
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNirsXy2Tcs (struct genSubRecord *pgsub) 
{
  double xn, yn ;     /* Nirs coords */
  double xt, yt ;     /* TCS coords mm in focal plane */

  xn = *(double *)pgsub->a ;
  yn = *(double *)pgsub->b ;

  agSeqOiwfsXy2xy (NIRS, NIRS2TCS, xn, yn, &xt, &yt) ;

  *(double *)pgsub->vala = xt ;
  *(double *)pgsub->valb = yt ;
  *(double *)pgsub->valc = xn ;
  *(double *)pgsub->vald = yn ;
  
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqNirsZ2Tcs
 *
 *   Purpose:
 *   Convert Nirs focus coordinate into the TCS frame of reference
 *
 *   Description:
 *   Convert the Nirs focus value by a simple linear transformation to
 *   the TCS frame of reference.
 *
 *   Invocation:
 *   agSeqNirsZ2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Nirs z coordinate
 *
 *   Epics outputs:
 *   vala => TCS z coordinate (mm)
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNirsZ2Tcs (struct genSubRecord *pgsub) 
{
  double zn ;     /* Nirs coord */
  double zt ;     /* TCS coord (mm) */

  zn = *(double *)pgsub->a ;

  agSeqOiwfsZ2z (NIRS, NIRS2TCS, zn, &zt) ;

  *(double *)pgsub->vala = zt ;
  
  return 0 ;

}

/*------------------------- NIRI ------------------------------ */

/*+
 *   Function name:
 *   agSeqNiriXy2Tcs
 *
 *   Purpose:
 *   Convert NIRI x,y coordinates into the TCS frame of reference
 *
 *   Description:
 *   This function assumes a linear correspondence between the x,y 
 *   coordinate frame of the NIRI OIWFS and the TCS one. The relationship
 *   is xt = a + b*xn + c*yn, yt = d + e*xn + f*yn. 
 *
 *   Invocation:
 *   agSeqNiriXy2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => NIRI x coordinate
 *   b => NIRI y coordinate
 *
 *   Epics outputs:
 *   vala => TCS x coordinate (mm in focal plane)
 *   valb => TCS y coordinate (mm in focal plane) 
 *   valc => Raw NIRI coordinate in "X"
 *   vald => Raw NIRI coordinate in "Y"
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNiriXy2Tcs (struct genSubRecord *pgsub) 
{
  double xn, yn ;     /* NIRI coords */
  double xt, yt ;     /* TCS coords mm in focal plane */

  xn = *(double *)pgsub->a ;
  yn = *(double *)pgsub->b ;

  agSeqOiwfsXy2xy (NIRI, NIRI2TCS, xn, yn, &xt, &yt) ;

  *(double *)pgsub->vala = xt ;
  *(double *)pgsub->valb = yt ;
  *(double *)pgsub->valc = xn ;
  *(double *)pgsub->vald = yn ;
  
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqNiriZ2Tcs
 *
 *   Purpose:
 *   Convert NIRI focus coordinate into the TCS frame of reference
 *
 *   Description:
 *   Convert the NIRI focus value by a simple linear transformation to
 *   the TCS frame of reference.
 *
 *   Invocation:
 *   agSeqNiriZ2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => NIRI z coordinate
 *
 *   Epics outputs:
 *   vala => TCS z coordinate (mm)
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNiriZ2Tcs (struct genSubRecord *pgsub) 
{
  double zn ;     /* NIRI coord */
  double zt ;     /* TCS coord (mm) */

  zn = *(double *)pgsub->a ;

  agSeqOiwfsZ2z (NIRI, NIRI2TCS, zn, &zt) ;

  *(double *)pgsub->vala = zt ;
  
  return 0 ;

}

/*-------------------------------- Flamingos-2 ----------------------------*/

/*+
 *   Function name:
 *   agSeqF2Xy2Tcs
 *
 *   Purpose:
 *   Convert Flamingos-2 x,y coordinates into the TCS frame of reference
 *
 *   Description:
 *   This function assumes a linear correspondence between the x,y 
 *   coordinate frame of the Flamingos-2 OIWFS and the TCS one. 
 *   The relationship
 *   is xt = a + b*xn + c*yn, yt = d + e*xn + f*yn. 
 *
 *   Invocation:
 *   agSeqF2Xy2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => F2 x coordinate
 *   b => F2 y coordinate
 *
 *   Epics outputs:
 *   vala => TCS x coordinate (mm in focal plane)
 *   valb => TCS y coordinate (mm in focal plane) 
 *   valc => F2 raw x coordinate
 *   vald => F2 raw y coordinate
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqF2Xy2Tcs (struct genSubRecord *pgsub) 
{
  double xn, yn ;     /* F2 coords */
  double xt, yt ;     /* TCS coords mm in focal plane */

  xn = *(double *)pgsub->a ;
  yn = *(double *)pgsub->b ;

  agSeqOiwfsXy2xy (F2, F22TCS, xn, yn, &xt, &yt) ;

  *(double *)pgsub->vala = xt ;
  *(double *)pgsub->valb = yt ;
  *(double *)pgsub->valc = xn ;
  *(double *)pgsub->vald = yn ;
  
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqF2Z2Tcs
 *
 *   Purpose:
 *   Convert Flamingos-2 focus coordinate into the TCS frame of reference
 *
 *   Description:
 *   Convert the Flamingos-2 focus value by a simple linear transformation to
 *   the TCS frame of reference.
 *
 *   Invocation:
 *   agSeqF2Z2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => GMOS z coordinate
 *
 *   Epics outputs:
 *   vala => TCS z coordinate (mm)
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqF2Z2Tcs (struct genSubRecord *pgsub) 
{
  double zn ;     /* Flamingos-2 coord */
  double zt ;     /* TCS coord (mm) */

  zn = *(double *)pgsub->a ;

  agSeqOiwfsZ2z (F2, F22TCS, zn, &zt) ;

  *(double *)pgsub->vala = zt ;
  
  return 0 ;

}

/*------------------------- NIFS ------------------------------ */

/*+
 *   Function name:
 *   agSeqNifsZ2Tcs
 *
 *   Purpose:
 *   Convert NIFS focus coordinate into the TCS frame of reference
 *
 *   Description:
 *   Convert the NIFS focus value by a simple linear transformation to
 *   the TCS frame of reference.
 *
 *   Invocation:
 *   agSeqNifsZ2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => NIFS z coordinate
 *
 *   Epics outputs:
 *   vala => TCS z coordinate (mm)
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNifsZ2Tcs (struct genSubRecord *pgsub) 
{
  double zn ;     /* NIFS coord */
  double zt ;     /* TCS coord (mm) */

  zn = *(double *)pgsub->a ;

  agSeqOiwfsZ2z (NIFS, NIFS2TCS, zn, &zt) ;

  *(double *)pgsub->vala = zt ;
  
  return 0 ;

}


/*+
 *   Function name:
 *   agSeqNifsXy2Tcs
 *
 *   Purpose:
 *   Convert NIFS x,y coordinates into the TCS frame of reference
 *
 *   Description:
 *   This function assumes a linear correspondence between the x,y 
 *   coordinate frame of the NIFS OIWFS and the TCS one. The relationship
 *   is xt = a + b*xn + c*yn, yt = d + e*xn + f*yn. 
 *
 *   Invocation:
 *   agSeqNifsXy2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => NIFS x coordinate
 *   b => NIFS y coordinate
 *
 *   Epics outputs:
 *   vala => TCS x coordinate (mm in focal plane)
 *   valb => TCS y coordinate (mm in focal plane) 
 *   valc => Raw NIFS coordinate in "X"
 *   vald => Raw NIFS coordinate in "Y"
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNifsXy2Tcs (struct genSubRecord *pgsub) 
{
  double xn, yn ;     /* NIFS coords */
  double xt, yt ;     /* TCS coords mm in focal plane */

  xn = *(double *)pgsub->a ;
  yn = *(double *)pgsub->b ;

  agSeqOiwfsXy2xy (NIFS, NIFS2TCS, xn, yn, &xt, &yt) ;

  *(double *)pgsub->vala = xt ;
  *(double *)pgsub->valb = yt ;
  *(double *)pgsub->valc = xn ;
  *(double *)pgsub->vald = yn ;
  
  return 0 ;

}

/*------------------------- NICI ------------------------------ */

/*+
 *   Function name:
 *   agSeqNiciZ2Tcs
 *
 *   Purpose:
 *   Convert NICI focus coordinate into the TCS frame of reference
 *
 *   Description:
 *   Convert the NICI focus value by a simple linear transformation to
 *   the TCS frame of reference.
 *
 *   Invocation:
 *   agSeqNiciZ2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => NICI z coordinate
 *
 *   Epics outputs:
 *   vala => TCS z coordinate (mm)
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciZ2Tcs (struct genSubRecord *pgsub) 
{
  double zn ;     /* NICI coord */
  double zt ;     /* TCS coord (mm) */

  zn = *(double *)pgsub->a ;

  agSeqOiwfsZ2z (NICI, NICI2TCS, zn, &zt) ;

  *(double *)pgsub->vala = zt ;
  
  return 0 ;

}

/*+
 *   Function name:
 *   agSeqNiciXy2Tcs
 *
 *   Purpose:
 *   Convert NICI x,y coordinates into the TCS frame of reference
 *
 *   Description:
 *   This function assumes a linear correspondence between the x,y 
 *   coordinate frame of the NICI OIWFS and the TCS one. The relationship
 *   is xt = a + b*xn + c*yn, yt = d + e*xn + f*yn. 
 *
 *   Invocation:
 *   agSeqNiciXy2Tcs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub (struct genSubRecord *pgsub) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => NICI x coordinate
 *   b => NICI y coordinate
 *
 *   Epics outputs:
 *   vala => TCS x coordinate (mm in focal plane)
 *   valb => TCS y coordinate (mm in focal plane) 
 *   valc => Raw NICI coordinate in "X"
 *   vald => Raw NICI coordinate in "Y"
 *
 *   Function value:
 *   (<)  long  (int)  Return status, 0 = OK
 * 
 *-
 */

long agSeqNiciXy2Tcs (struct genSubRecord *pgsub) 
{
  double xn, yn ;     /* NICI coords */
  double xt, yt ;     /* TCS coords mm in focal plane */

  xn = *(double *)pgsub->a ;
  yn = *(double *)pgsub->b ;

  agSeqOiwfsXy2xy (NICI, NICI2TCS, xn, yn, &xt, &yt) ;

  *(double *)pgsub->vala = xt ;
  *(double *)pgsub->valb = yt ;
  *(double *)pgsub->valc = xn ;
  *(double *)pgsub->vald = yn ;
  
  return 0 ;

}
long agSeqGensubInit (struct genSubRecord *pgsub) 
{
  
  return 0 ;

}

epicsRegisterFunction(agSeqOiwfsCoeffs);
epicsRegisterFunction(agSeqInitTransform);
epicsRegisterFunction(agSeqSetOiwfsTransform);
epicsRegisterFunction(agSeqNifsZ2Tcs);
epicsRegisterFunction(agSeqNifsXy2Tcs);
epicsRegisterFunction(agSeqF2Xy2Tcs);
epicsRegisterFunction(agSeqOiwfsPort);
epicsRegisterFunction(agSeqNiriZ2Tcs);
epicsRegisterFunction(agSeqAoDeployed);
epicsRegisterFunction(agSeqNiriXy2Tcs);
epicsRegisterFunction(agSeqNirsXy2Tcs);
epicsRegisterFunction(agSeqNiciXy2Tcs);
epicsRegisterFunction(agSeqGmosXy2Tcs);
epicsRegisterFunction(agSeqGensubInit);
