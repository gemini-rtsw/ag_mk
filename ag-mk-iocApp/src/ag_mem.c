/*
 *  FILENAME
 *  --------
 *  ag_mem.c
 *
 *  PURPOSE
 *  -------
 *  This file contains all utility routines with direct memory access
 *  (memory or array written/read with pointers) in the A&G unit
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth  (ocf)
 *  Ricardo Cardenes (rjc)
 *
 *  HISTORY
 *  -------
 *  25-Apr-1998:	Original version			(ocf)
 *  23-Feb-2018:        Fix some warnings                       (rjc)
 *
 */


#include  <ag_define.h>		/* names for mechanisms */

/* ===================================================================== */

char *strntoupper( char *str , int length)
{
	int i;

	for  (i=0; (i<length) || (str[i] == '\0'); i++)
		str[i] = toupper ((int)str[i]);

	return str;
}

/* ===================================================================== */
/* ====================================================================	*/
/* Copies srcstr to str and wraps to buf, if writeposition reaches bufend.
 * Writes up to max_size chars and always terminates the string with '\0'.
 * Returns pointer to char after copy of srcstr.
 * Bufend will be written to.
 */

char * movestring (char *buf, char *str, char *bufend, char *srcstr, int max_size)
{
  int i, help;

  if (bufend < buf) {
  	char *tmp = buf;

	buf = bufend;
	bufend = tmp;
  }

  help = (str-buf) % (bufend-buf+1);
  if (str<buf)	str = bufend+1 + help;
  else		str = buf      + help;

  for (i=0; i<max_size; i++)
  {
    if (str > bufend)  str = buf;			/* wrap		*/
    if (!(*(str++) = *(srcstr++))) break;		/* copy	but stop on NULL */

/*    *(str++) = *(srcstr++);		*/		/* copy		*/
/*    if (*(srcstr-1) == 0)  break;	*/		/* on NULL stop	*/
  }

  if (i>=max_size) *(str) = '\0';			/* terminate	*/

  return (str);
}



/* ===================================================================== */
/* ===================================================================== */

#define SYNTAX_ERROR  1
#define ALL_BLANKS    2
#define TOO_LONG      3

/*+
 *   Function name:
 *   check_numeric
 *
 *   Purpose:
 *
 *
 *   Invocation:
 *
 *   Parameters in:
 *
 *   Parameters out:
 *
 *   Return value:
 *      >=1 (true) signalizes fault
 *	  0 (false) stands for "number O.K."
 *
 *   Globals:
 *      External functions:
 *      None
 *
 *      External variables:
 *      None
 *
 *   Requirements:
 *
 *   Limitations:
 */

/* 
 *  This function checks that an argument to a CAD record is numeric
 */
long check_numeric( char *buf )
{
  char *c;
  int  len;
  int  i;
  int  ret;
  int  istart;
  int  iend;
  int  numEs;
  int  numDots;

  numEs   = 0;
  numDots = 0;
  istart  = 0;
  ret     = 0;
  len     = strlen(buf);
  c       = buf;
  while( isspace((int)*c) )
  {
    c++;
    istart++;
  }
  if( istart == len )
  {
    /* Case of all blanks */
    ret = ALL_BLANKS;
  }
  else
  { 
    /* At this point istart refers to the first non-space character */
    iend = istart;
    while( !isspace((int)*c) && iend<len )
    {
      c++;
      iend++;
    }
    /* iend is one past the last non-space character */
    /* This is necessary because we must go round the loop at least once */
    c = buf;
    for( i=istart; i<iend; i++ )
    {
      if( i == istart )
      {
        /* Allow '+' and '-' and '.' as first character */
        if( !isdigit((int)*(c+i)) && (*(c+i) != '-') && (*(c+i) != '+') && (*(c+i) != '.') )
        {
          ret = SYNTAX_ERROR;
          break;
        }
        /* Reject the case of a single '+' or '-'  or '.' with no following digits */
        if( (iend-istart == 1) && ((*(c+i) == '-') || (*(c+i) == '+') || (*(c+i) == '.')) )
        {
          ret = SYNTAX_ERROR;
          break;
        }
      }
      else
      {
        if( !isdigit((int)*(c+i)) && (*(c+i) != '.') &&
             (*(c+i) != 'E') && (*(c+i) != 'e') && 
             (*(c+i) != '+') && (*(c+i) != '-') )
        {
          ret = SYNTAX_ERROR;
          break;
        }
        else if( *(c+i) == '.' )
        {
          numDots++;
          if( numDots > 1 )
          {
            ret = SYNTAX_ERROR;
            break;
          }
        }
        else if( (*(c+i) == 'E') || (*(c+i) == 'e') )
        {
          numEs++;
          if( numEs > 1 )
          {
            ret = SYNTAX_ERROR;
            break;
          }
        }
        if( *(c+i) == '.' )
        {
          if( (*(c+i-1) != '+') && (*(c+i-1) != '-') && !isdigit((int)*(c+i-1)) )
          {
            ret = SYNTAX_ERROR;
            break;
          }
        }
        if( (*(c+i) == 'E') || (*(c+i) == 'e') )
        {
          if( (*(c+i-1) != '.') && !isdigit((int)*(c+i-1)) )
          {
            ret = SYNTAX_ERROR;
            break;
          }
        }
        if( (*(c+i) == '+') || (*(c+i) == '-') )
        {
          if( (*(c+i-1) != 'e') && (*(c+i-1) != 'E') )
          {
            ret = SYNTAX_ERROR;
            break;
          }
        }
      }
    }
  }
  return ret;
}

/* ==================================================================== */
