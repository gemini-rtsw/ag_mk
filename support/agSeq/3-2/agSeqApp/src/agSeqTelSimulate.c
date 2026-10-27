/*
*   FILENAME
*   Put file name here
*
*   FUNCTION NAME(S)
*   agSeqTelFollow  - simulate follow coming from the TCS
*
*/

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
#include <timeLib.h>


/*+
 *   Function name:
 *   agSeqTelFollow
 *
 *   Purpose:
 *   Simulate follow coming from the TCS
 *
 *   Description:
 *
 *   Invocation:
 *   agSeqTelFollow (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *) Pointer to pgsub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *
 *   a => default startup x position (mm)
 *   b => default startup y position (mm)
 *   c => maximum probe velocity (mm/s)
 *   d => position tolerance (mm)
 *
 *   Epics outputs:
 *   
 *   valj => 
 *
 *-
 */

long agSeqTelFollow (struct genSubRecord *pgsub)
{
	double	x0, y0, z0, dx, dy, dz;
	double	demand[6];
   	double cbTimeStamp;

	x0 = *((double *) pgsub->a);
	y0 = *((double *) pgsub->b);
	z0 = *((double *) pgsub->c);
	dx = *((double *) pgsub->d);
	dy = *((double *) pgsub->e);
	dz = *((double *) pgsub->f);

	printf ("x0=%g, y0=%g, z0=%g, dx=%g, dy=%g, dz=%g\n",
		x0, y0, z0, dx, dy, dz);

	x0 = x0 + dx;
	y0 = y0 + dy;

	*((double *) pgsub->a) = x0;
	*((double *) pgsub->b) = y0;

        /* go get another timestamp */
        if (timeNow (&cbTimeStamp) != 0)
        {
           errlogPrintf ("agSeqTelFollow - error reading timeStamp\n");
        }
	demand[0] = cbTimeStamp;
	demand[1] = demand[0] + 10;
	demand[2] = 1958;
	demand[3] = x0;
	demand[4] = y0;
	demand[5] = z0;

	memcpy (pgsub->vala, demand, 6 * sizeof(double));

	return 0L;
}
