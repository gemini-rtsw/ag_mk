/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsCadSupport.c
*
*   FUNCTION NAME(S)
*   tcsCsAppendMessage - Appends a string to the message field.
*   tcsCsAppendMessageN - Appends strings to the message field.
*   tcsCsCadName - Returns a pointer to the cad record name.
*   tcsCsFrame - Returns a pointer to a frame name
*   tcsCsOffCoord - Returns a pointer to a offset coordinate name
*   tcsCsSetMessage - Sets the message field of a Cad structure to a string.
*   tcsCsSetMessageN - Sets the message field of a Cad structure.
*   tcsCsSetOutputString - Copies a string to a Cad output.
*
*/
/*
 * $Log:
 */
/* *INDENT-ON* */

#include <string.h>
#include <stdarg.h>
#include <dbDefs.h>
#include <cadRecord.h>
#include <astLib.h>
#include "tcsCadSupport.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsCadName
 *
 *   Purpose:
 *   Get the name of a Cad record.
 *
 *   Description:
 *   Returns a pointer to the last component of the record name. The
 *   last component is that part of the name following the final ":".
 *   If the record name contains no ":" then the whole name is returned.
 *
 *   Invocation:
 *   name = tcsCadName( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    pcad     (struct cadRecord *)   Cad record
 *
 *   Function value:
 *   (<)  pname  (char*)  Pointer to CAD name
 * 
 *-
 */
/* *INDENT-ON* */

char* tcsCsCadName( struct cadRecord* pcad)
{
   char *pname;           /* Pointer to CAD name */
   char *p;               /* Temporary pointer */

   /* Initialise the pointer to the start of the record name */
   pname = pcad->name;

   /* Move the pointer to the last component deliminator in the name */
   for ( p = pname; *p; p++ ) {
      if ( *p == ':' ) pname = p;
   }

   /* If a delimiter was found then move the pointer to the next character */
   if ( pname != pcad->name ) pname++;

   return pname;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsSetMessage
 *
 *   Purpose:
 *   Set the message field of a cad routine to a string
 *
 *   Description:
 *   The input string is copied to the message field of the cad record with
 *   due regard to the maximum allowed message length. Any message
 *   already in the messsage field is overwritten.
 *
 *   Invocation:
 *   tcsCsSetMessage( pcad, string)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    pcad     (struct cadRecord*)   Cad record
 *      (>)    string   (char *)              String to be written
 *
 *-
 */
/* *INDENT-ON* */

void tcsCsSetMessage( struct cadRecord* pcad, char* string)
{
   /* Set the message field to an empty string */
   pcad->mess[ 0 ] = '\0';

   /* Append the string */
   tcsCsAppendMessage( pcad, string);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsAppendMessage
 *
 *   Purpose:
 *   Append a string to the message field of a cad record
 *
 *   Description:
 *   The input string is appended to the message field of the cad record with
 *   due regard to the maximum allowed message length. If the input string
 *   is too long then the last two characters of the message are set to dots.
 *
 *   Invocation:
 *   tcsCsAppendMessage( pcad, string)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    pcad     (struct cadRecord*)   Cad record
 *      (>)    string   (char *)              String to be appended
 *
 *-
 */
void tcsCsAppendMessage( struct cadRecord* pcad, char* string)
{
   int nleft = MAX_STRING_SIZE - strlen(pcad->mess) - 1;    /* space left */

   /* Copy input string characters up to end of the message field 
      (not forgetting space for the terminating NULL */
   strncat( pcad->mess, string, nleft);

   /* If there wasn't enough space left for the string then set the last
      two characters to dots to indicate that the message was truncated */
   if ( nleft < strlen(string) ) {
      pcad->mess[ MAX_STRING_SIZE - 2 ] = '.';
      pcad->mess[ MAX_STRING_SIZE - 3 ] = '.';
   }
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsSetMessageN
 *
 *   Purpose:
 *   Sets a CAD message field to a list of strings.
 *
 *   Description:
 *   The CAD record message field is cleared and the input strings then
 *   appended to it.
 *
 *   Invocation:
 *   tcsCsSetMessageN( pcad, string1, string2, (char*)NULL)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    pcad     (struct cadRecord*)   Cad record
 *      (>)    strings (char *)             Strings to be appended
 *
 *-
 */
/* *INDENT-ON* */
void tcsCsSetMessageN( struct cadRecord* pcad, ...)
{
   va_list ap;         /* argument pointer */
   char* string;       /* pointer to input strings */

   /* Clear the message field */
   pcad->mess[ 0 ] = '\0';

   /* Initialise the argument pointer */
   va_start(ap, pcad);

   /* Append each string argument until a null pointer is found */
   while ( (string = va_arg( ap, char*)) ) {
      tcsCsAppendMessage( pcad, string);
   }

   /* clean up argument list traversal */
   va_end( ap );
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsAppendMessageN
 *
 *   Purpose:
 *   Appends a list of strings to a CAD message field.
 *
 *   Description:
 *   The input strings are appended to the CAD record message field by
 *   repeated calls to tcsCsAppendMessage until a null is encountered.
 *
 *   Invocation:
 *   tcsCsAppendMessageN( pcad, string1, string2, (char*)NULL)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    pcad     (struct cadRecord*)   Cad record
 *      (>)    strings  (char *)             Strings to be appended
 *
 *-
 */
/* *INDENT-ON* */
void tcsCsAppendMessageN( struct cadRecord* pcad, ...)
{
   va_list ap;         /* argument pointer */
   char* string;       /* pointer to input strings */

   /* Initialise the argument pointer */
   va_start(ap, pcad);

   /* Append each string argument until a null pointer is found */
   while ( (string = va_arg( ap, char*)) ) {
      tcsCsAppendMessage( pcad, string);
   }

   /* clean up argument list traversal */
   va_end( ap );
}


/*+
 *   Function name:
 *   tcsCsSetOutputString
 *
 *   Purpose:
 *   Sets the value of an STRING CAD output field
 *
 *   Description:
 *   Copies a string to a CAD output field with due regard for the 
 *   maximum length and ensures that the string in null terminated.
 *
 *   Invocation:
 *   tcsCsSetOutputString( string, field)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    string   (char*)    String to be written
 *      (<)    field    (char*)    Pointer to CAD output field
 *
 *-
 */
void tcsCsSetOutputField( char* string, char* field)
{
    strncpy( field, string, MAX_STRING_SIZE - 1);
    field[ MAX_STRING_SIZE - 1 ] = '\0';
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsFrame
 *
 *   Purpose:
 *   Returns a pointer to the name of a coordinate frame.
 *
 *   Description:
 *   The different coordinate frames that the TCS supports are encoded as 
 *   an enumerated type FRAMETYPE. This routine returns a corresponding
 *   name for the frame as a string. 
 *   
 *
 *   Invocation:
 *   pFrame = tcsCsFrame( frameType );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    frame    (FRAMETYPE)      Coordinate frame id.
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  pFrame  (char*))  Pointer to frame name
 * 
 *-
 */
/* *INDENT-ON* */

char* tcsCsFrame( FRAMETYPE frameType )
{
   static char *frames[] = {
      "AZEL_MOUNT", "AZEL_TOPO", "APPT", "FK5", "FK4"
   };

   return frames[frameType];
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCsOffCoord
 *
 *   Purpose:
 *   Returns a pointer to the name of an offset coordinate frame.
 *
 *   Description:
 *   Offsets in the TCS can be of a number of types e.g. RA/Dec or 
 *   Tangent Plane. These are encoded as an enumerated type OFFCOORD.
 *   This routine translates this type into a string name.
 *
 *   Invocation:
 *   pOffCoord = tcsCsOffCoord( offCoord );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    frame    (OFFCOORD)      Offset coordinate frame id.
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  pFrame  (char*))  Pointer to frame name
 * 
 *-
 */
/* *INDENT-ON* */

char* tcsCsOffCoord( OFFCOORD frameType )
{
   static char *frames[] = {
      "RADEC", "TANGENT PLANE" 
   };

   return frames[frameType];
}
