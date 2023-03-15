#include <vxWorks.h>
#include <stdio.h>
#include <sysLib.h>
#include <types.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdioLib.h>
#include <ctype.h>
#include <string.h>

#include <dbEvent.h>
#include <dbDefs.h>
#include <dbCommon.h>
#include <recSup.h>
#include <genSubRecord.h>
#include <menuCarstates.h>

#define PASSWORD          "gemini98"

/* 
 * Checks password for access to PMAC mailbox registers
 *
 * INPUTS:
 * 	pgsub->a = Card Number (LONG).
 *      pgsub->b = Current Disable value for Mailbox (LONG).
 *      pgsub->c = Debug On/Off (LONG).
 * 	pgsub->j = Password Entry (STRING) from "dm".
 *
 * OUTPUTS:
 * 	pgsub->vala = 0/1 (GOOD/BAD)                (LONG).
 *      pgsub->valb = New disable value for Mailbox (LONG).
 *
 */

long pmacLogin( struct genSubRecord *pgsub )
{
  long card;
  long locked;
  long debug;

  card   = *(long *)pgsub->a;
  locked = *(long *)pgsub->b;
  debug  = *(long *)pgsub->c;
  if( locked )
  {
    if( !strcmp((char *)pgsub->j, PASSWORD) )
    {
      if( debug )
        printf("pmacLogin: Unlocking Mailbox for %ld\n", card);
      strcpy( (char *)pgsub->j, " " );
      *(long *)pgsub->vala = 0;
      *(long *)pgsub->valb = 0;
    }
    else
    {
      *(long *)pgsub->vala = 1;
      *(long *)pgsub->valb = 1;
    }
  }
  return(0);
}


/* 
 * Disables access to PMAC Mailbox.
 *
 * INPUTS:
 * 	pgsub->a = Card Number (LONG).
 *      pgsub->b = Current Disable value for Mailbox (LONG).
 *      pgsub->c = Debug On/Off (LONG).
 *
 * OUTPUTS:
 * 	pgsub->vala = 0/1 (GOOD/BAD)                (LONG).
 *      pgsub->valb = New disable value for Mailbox (LONG).
 *
 */

long pmacLogout( struct genSubRecord *pgsub )
{
  long card;
  long locked;
  long debug;

  card   = *(long *)pgsub->a;
  locked = *(long *)pgsub->b;
  debug  = *(long *)pgsub->c;
  if( !locked )
  {
    if( debug )
      printf("pmacLogout: Locking Mailbox for %ld\n", card);
    *(long *)pgsub->vala = 1;
    *(long *)pgsub->valb = 1;
  }
  return(0);
}
