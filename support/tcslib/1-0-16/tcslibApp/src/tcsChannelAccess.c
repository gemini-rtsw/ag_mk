/*
*   FILENAME
*   tcsChannelAccess.c
*
*   FUNCTION NAME(S)
*   tcsCaEventHandler - Define Channel Access event handler routine for use with TCS channel access.
*   tcsCaPut          - Put a value to an EPICS variable using channel access
*   tcsCaGet          - Get a value from an EPICS variable using channel access
*   tcsPutCadField    - Put a value using CA, into an input field of a TCS CAD record
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsChannelAccess.c,v $
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
 * Revision 1.1.1.1  2005/06/14 15:13:11  ajf
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
 * Revision 1.1.1.1  2005/06/08 16:04:54  ajf
 * Initial creation of the Gemini TCS3-14 repository
 *
 * Revision 1.1.1.1  1998/11/08 00:21:12  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:10:17  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1996/09/05 16:41:06  pbt
 * Subroutine library to facilitate using Channel Access in TCS code
 *
 *
 *
 */
/* *INDENT-ON* */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cadef.h>
#include <db_access.h>
#include "tcsChannelAccess.h"
#include  <dbDefs.h>
#include  <dbEvent.h>

/*+
 *   Function name
 *   print_ca_create_channel_error
 *
 *   Purpose:
 *   Ancillary function that prints an error message for ca_crete_channel
 *
 *   Description:
 *   Takes information about the function where the error happened, and the
 *   arguments passed to ca_create_channel, and prints out a meaningful (for
 *   humans) error message.
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)  fname    (const char *)  The name of the function where the error occurred
 *      (>)  dbname   (const char *)  The name of the pv that the CA was trying to connect to
 *      (>)  prio     (int)           The priority that was assigned to the CA
 *      (>)  status   (int)           The error code
 *
 *   Function value:
 *
 *   External functions:
 *
 *   External variables:
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *   No known problems for this function
 *
 *-
 */
static void print_ca_create_channel_error(const char *fname, const char *dbname, int prio, int status) {
  // TODO: eventually we probably want all printfs to turn into console debug functions
  switch(status) {
    case ECA_BADSTR:
      printf("%s : Invalid string '%s'", fname, dbname);
      break;
    case ECA_ALLOCMEM:
      printf("%s : Unable to allocate memory", fname);
      break;
    case ECA_BADPRIORITY:
      printf("%s : Invalid priority '%d' for channel '%s' (%d <= prio <= %d)", fname, prio, dbname, CA_PRIORITY_MIN, CA_PRIORITY_MAX);
      break;
    case ECA_UNAVAILINSERV:
      printf("%s : channel '%s' not supported by attached service", fname, dbname);
      break;
    default:
      printf("%s : unknown error when trying to connect to channel '%s'", fname, dbname);
      break;
  }
}

/*+
 *   Function name:
 *   tcsCaEventHandler
 *
 *   Purpose:
 *   Define an EPICS Channel Access event handler routine.
 *
 *   Description:
 *   Uses Channel Access library function ca_create_subscription to define a handler
 *   subroutine which is called whenever a event is posted for the specified 
 *   record
 *
 *   Invocation:
 *   tcsCaEventHandler(top, pvname, handler)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  top     (char *)     The top-level database name string
 *      (>)  pvname  (char *)     The name of the EPICS variable to be monitored
 *      (>)  handler (function)   An event handler which will be called to handle events
 *                                posted for the specified record.
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Channel Access return status, 0 = OK
 * 
 *   External functions:
 *   ca_create_channel, ca_pend_io, ca_create_subscription      Channel Access library
 *
 *   External variables:
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
int tcsCaEventHandler(char *top, char *pvname,
                             void (*handler)(struct event_handler_args) )
{
  chid chan ;
  int ca_status ;
  char dbname[MAX_STRING_SIZE] ;

  sprintf(dbname, "%s%s",top, pvname) ;
  if ((ca_status = ca_create_channel(dbname, NULL, NULL, CA_PRIORITY_DEFAULT, &chan)) != ECA_NORMAL) {
    print_ca_create_channel_error("tcsCaEventHandler", dbname, CA_PRIORITY_DEFAULT, ca_status);
    return -1;
  }
  ca_status = ca_pend_io(1.0) ;
  if (ca_status == ECA_TIMEOUT)
    {
     printf("tcsCaEventHandler : Unable to find %s \n", dbname) ;
     return(-1) ;
    }
   ca_status = ca_create_subscription(ca_field_type(chan),
		  		      1u,                     // Element count to be read from the channel
				      			      // 1u comes from automatic translation from ca_add_event
				      chan,
				      DBE_VALUE | DBE_ALARM,  // Trigger when dead band exceeded and when alarm state changes
				      			      // Default when translating from ca_add_event
		   		      handler,
				      top,
				      NULL);

  /*
   * TODO: Check this mask. Maybe we want to apply it to the suscription,
   *       instead of the default VALUE|ALARM
   */
  /* ca_status =  db_post_events(&chan, &chan->VAL, DBE_VALUE|DBE_LOG); */
  if (ca_status != ECA_NORMAL)
  {
   // TODO: We could probably give a more explicit message...
   printf ("tcsCaEventHandler : Failed to initialize event handler for %s\n", dbname);
   return(-1);
  }
  else
  {
   printf ("tcsCaEventHandler : Initialized event handler for %s OK\n", dbname);
   return(0);
  }
}

/*+
 *   Function name:
 *   tcsCaPut
 *
 *   Purpose:
 *   Put a value using Channel Access.
 *
 *   Description:
 *   Uses CA library calls to set the value.
 *
 *   Invocation:
 *   tcsCaPut(top, pvname, val)
 *
 *   Parameters: (">" input, "!" modified, "<" output) 
 *      (>)  top     (char *)     The top-level database name string
 *      (>)  pvname  (char *)     The name of the EPICS variable to be set
 *      (>)  val     (void *)     The value to be put.
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Channel Access return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   ca_create_channel, ca_pend_io, ca_put      Channel Access library
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
int tcsCaPut(const char *top, const char *pvname, void *val)
{
   chid chan ;
   int ca_status ;
   char dbname[MAX_STRING_SIZE] ;

   sprintf(dbname, "%s%s", top, pvname);
   if ((ca_status = ca_create_channel(dbname, NULL, NULL, CA_PRIORITY_DEFAULT, &chan)) != ECA_NORMAL) {
      print_ca_create_channel_error("tcsCaPut", dbname, CA_PRIORITY_DEFAULT, ca_status);
      return -1;
   }
   ca_status = ca_pend_io(1.0) ;
   if (ca_status == ECA_TIMEOUT)
     {
      printf("tcsCaPut : Unable to find %s \n", dbname) ;
      return(-1) ;
     }
   ca_status = ca_put(ca_field_type(chan), chan, val) ;
   if (ca_status == ECA_TIMEOUT)
     {
      printf("tcsCaPut : ca_put returns error for %s \n", dbname) ;
      return(-1) ;
     }
   return(0) ;
}


/*+
 *   Function name:
 *   tcsCaGet
 *
 *   Purpose:
 *   Read a value using Channel Access.
 *
 *   Description:
 *   Uses CA library calls to get the value.
 *
 *   Invocation:
 *   tcsCaGet(top, pvname, val)
 *
 *   Parameters: (">" input, "!" modified, "<" output) 
 *      (>)  top     (char *)     The top-level database name string
 *      (>)  pvname  (char *)     The name of the EPICS variable to be read 
 *      (!)  val     (void *)     The value to be read from Channel Access.
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Channel Access return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   ca_create_channel, ca_pend_io, ca_get      Channel Access library
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
int tcsCaGet(const char *top, const char *pvname, void *val)
{
   chid chan ;
   int ca_status ;
   char dbname[MAX_STRING_SIZE] ;

   sprintf(dbname, "%s%s", top, pvname);
   if ((ca_status = ca_create_channel(dbname, NULL, NULL, CA_PRIORITY_DEFAULT, &chan)) != ECA_NORMAL) {
      print_ca_create_channel_error("tcsCaGet", dbname, CA_PRIORITY_DEFAULT, ca_status);
      return -1;
   }
   ca_status = ca_pend_io(1.0) ;
   if (ca_status == ECA_TIMEOUT)
     {
      printf("tcsCaGet : Unable to find %s \n", dbname) ;
      return(-1) ;
     }
   ca_status = ca_get(ca_field_type(chan), chan, val) ;
   if (ca_status == ECA_TIMEOUT)
     {
      printf("tcsCaGet : ca_get returns error for %s \n", dbname) ;
      return(-1) ;
     }
   return(0) ;
}

/*+
 *   Function name:
 *   tcsPutCadField
 *
 *   Purpose:
 *   Set a specified input field in a CAD record.
 *
 *   Description:
 *   Uses the supplied CAD record name and input field to derive
 *   the field name, then set using tcsCaPut.   
 *
 *   Invocation:
 *    tcsPutCadField(top, cadname, 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  top     (char *)     The top-level database name string
 *      (>)  cadname (char *)     The name of the CAD record whose input field is to be set
 *      (>)  field   (char)       The input field name in the CAD record (single upper case char)
 *      (>)  val     (void *)     The value to be set in the CAD input field
 *
 *   Function value:
 *   (<)  status  (int)  Channel Access return status, 0 = OK
 * 
 *   External functions:
 *   tcsCaPut      (local)     Put the specified value using Channel Access.
 *
 *   External variables:
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */


int tcsPutCadField(const char *top, const char *cadname, const char field, void *val)
{
   char pvname[MAX_STRING_SIZE] ;
   
   if ( isupper((int)field)
   &&  (strcmp(cadname, " ") != 0 && strlen(cadname) > 0))
     {
     sprintf(pvname, "%s.%c", cadname, field) ;
     return(tcsCaPut(top, pvname, val)) ;
     }
   else
     return(-1) ;
}
