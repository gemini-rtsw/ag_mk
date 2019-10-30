/* static char rcsid[]="$Id: ag_carhealth.c,v 1.4 2001/08/14 14:00:18 ajf Exp $"; */
/*
 *  FILENAME
 *  -------- 
 *  ag_carhealth.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all the functions used to
 *  combine together multiple CAR events, multiple health
 *  values or other such things through "genSub" records.
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  CarDrive	       - Combine together multiple CAR states
 *  cicsCarValCombine  - Combine together multiple CAR states and client IDs.
 *  cicsHealthCombine  - Combine together multiple health values.
 *  cicsStringAppend   - Append two string inputs together
 *  cicsStringFilter   - Pass a string as long as it differs from a given tag
 *
 *  long carInit		( struct genSubRecord *pgsub );
 *  long carDrive		( struct genSubRecord *pgsub );
 *  long HealthCombine		( struct genSubRecord *pgsub );
 *  long inposCombInit		( struct genSubRecord *pgsub ); 
 *  long inposCombine		( struct genSubRecord *pgsub ); 
 *  long cicsStringAppend	( struct genSubRecord *pgsub );
 *  long cicsStringFilter	( struct genSubRecord *pgsub );
 *  
 *  DEPENDENCIES
 *  ------------
 *
 *  LIMITATIONS
 *  -----------
 *
 *  AUTHOR
 *  ------
 *  Steven Beard  (smb@roe.ac.uk)
 *
 *  HISTORY
 *  -------
 *  24-Jan-1997: Original version based on tcsCarCombine.         (smb)
 *  18-Jul-1997: cicsStringAppend added.                          (smb)
 *  18-Aug-1997: cicsStringFilter added.                          (smb)
 *
 */

#include  <ag_define.h>		/* names for mechanisms */

/***************************************************************************/


long carInit(struct genSubRecord *pgsub)
{
	/* agprintf("setup car combining gensub record\n"); */
	return(OK);
}

/***************************************************************************/

#define OUTPUT	(*(long *)pgsub->vala)
#define OUTPUT2	(*(long *)pgsub->valb)
#define OUTPUT3	(*(long *)pgsub->valc)	/* this is a copy of OUTPUT so that a 2nd and 3d gensub link can be used */

long carDrive(struct genSubRecord *pgsub)
{
	long	output = menuCarstatesIDLE;
#if 0
	char messages[80];     /* Message buffer */
	sprintf( messages, "%s - cardrive triggered!", pgsub->name );
	agLogMessage( mechindex, DEB_FULL, messages);
#endif

	/* if any of the contributing cars are busy
	 * then set the output to busy
	 */

	     if(*(long *)pgsub->a == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->b == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->c == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->d == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->e == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->f == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->g == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->h == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->i == menuCarstatesBUSY)		output = menuCarstatesBUSY;
	else if(*(long *)pgsub->j == menuCarstatesBUSY)		output = menuCarstatesBUSY;

	else if(*(long *)pgsub->a == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->b == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->c == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->d == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->e == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->f == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->g == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->h == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->i == menuCarstatesERROR)		output = menuCarstatesERROR;
	else if(*(long *)pgsub->j == menuCarstatesERROR)		output = menuCarstatesERROR;

	else if(*(long *)pgsub->a == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->b == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->c == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->d == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->e == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->f == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->g == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->h == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->i == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;
	else if(*(long *)pgsub->j == menuCarstatesPAUSED)	output = menuCarstatesPAUSED;

	else 	/* find maximum */
	{
	  if(*(long *)pgsub->a >= output)	output = *(long *)pgsub->a ;
	  if(*(long *)pgsub->b >= output)	output = *(long *)pgsub->b ;
	  if(*(long *)pgsub->c >= output)	output = *(long *)pgsub->c ;
	  if(*(long *)pgsub->d >= output)	output = *(long *)pgsub->d ;
	  if(*(long *)pgsub->e >= output)	output = *(long *)pgsub->e ;
	  if(*(long *)pgsub->f >= output)	output = *(long *)pgsub->f ;
	  if(*(long *)pgsub->g >= output)	output = *(long *)pgsub->g ;
	  if(*(long *)pgsub->h >= output)	output = *(long *)pgsub->h ;
	  if(*(long *)pgsub->i >= output)	output = *(long *)pgsub->i ;
	  if(*(long *)pgsub->j >= output)	output = *(long *)pgsub->j ;
	}

	OUTPUT3 = OUTPUT2 = OUTPUT = output;

	return(OK);
}

/* ===================================================================== */
/*+
 *   Function name:
 *    Healthcombine -  Combine together multiple health states.
 *
 *   Purpose:
 *   This function reads the states of up to five health records
 *   and generates a combined health.
 *
 *   - The result will be GOOD if none of the inputs are WARNING or BAD.
 *   - The result will be WARNING if any of the inputs are WARNING
 *     but none of the inputs are BAD.
 *   - The result will be BAD if any of the inputs are BAD.
 *
 *   The message contained in the winning health record is passed to
 *   the output.
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = cicsHealthCombine( struct genSubRecord *pgsub );
 *
 *   Parameters in:
 *      > pgsub->a    string*  Value of health record 1
 *      > pgsub->b    string*  Message contained in health record 1
 *      > pgsub->c    string*  Value of health record 2
 *      > pgsub->d    string*  Message contained in health record 2
 *      > pgsub->e    string*  Value of health record 3
 *      > pgsub->f    string*  Message contained in health record 3
 *      > pgsub->g    string*  Value of health record 4
 *      > pgsub->h    string*  Message contained in health record 4
 *      > pgsub->i    string*  Value of health record 5
 *      > pgsub->j    string*  Message contained in health record 5
 *	.. and so on up to record 10
 *	
 *
 *   Parameters out:
 *      < pgsub->vala string*  Resulting health
 *      < pgsub->valb string*  Winning message
 *      < pgsub->valc long     Index of winning health input
 *
 *   Return value:
 *      < status      long        Status value
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
 *   If any or all the input health values are silly the result is still
 *   GOOD. Only the strings "WARNING" and "BAD" are recognised.
 *
 *   I expect this function will be very inefficient, since it deals with
 *   lots of character strings. It would be much more efficient to combine
 *   health values as integers by taking the maximum. It should be ok if
 *   the function is executed only when the health changes and is not
 *   executed continuously.
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   24-Jan-1997: Original version.                                (smb)
 *   25-Jan-1997: Generate index of winning health input.          (smb)
 *   20-Jan-1998: restructured. Propagation of "unknown" values.   (ocf)
 *-
 */

long HealthCombine( struct genSubRecord *pgsub ) 
{
  long status;                       /* return status */
  long outIndex, outIndexM;          /* Indices of winning health/message inputs */
  char *PoutMess;
  char outHealth[MAX_STRING_SIZE];
  char outMess[MAX_STRING_SIZE];     /* Output message */

/*  char messages[80];      Message buffer */
/*  char messages2[80];     Message buffer */
  char teststr[80];      /* String to be tested */

  status = PASS;	/* Initialise the status */

/*
 * The default output value is GOOD and the default message is the first
 * non-null and non-blank message (or a null message if there are no non-null
 * and non-blank messages). The default index corresponds to the message
 * chosen (or is 1 if there are no messages found).
 **
 * If any health value is WARNING this will override the GOOD value and result 
 * in a WARNING output value. If the message associated with this WARNING
 * value is non-null and non-blank it will override the default message.
 **
 * If any health value is BAD this will override any GOOD or WARNING values
 * and result in a BAD output value. If the message associated with this BAD
 * value is non-null and non-blank it will override the default message.
 * (strspn= length until first non-matching char)
*/

 outIndex  = 0;
 outIndexM = 0;

 strncpy( teststr, "BAD", MAX_STRING_SIZE );
  	if (strcmp( strntoupper((char*)pgsub->a, MAX_STRING_SIZE), teststr) == 0)    outIndex = 1;
 else	if (strcmp( strntoupper((char*)pgsub->c, MAX_STRING_SIZE), teststr) == 0)    outIndex = 2;
 else	if (strcmp( strntoupper((char*)pgsub->e, MAX_STRING_SIZE), teststr) == 0)    outIndex = 3;
 else	if (strcmp( strntoupper((char*)pgsub->g, MAX_STRING_SIZE), teststr) == 0)    outIndex = 4;
 else	if (strcmp( strntoupper((char*)pgsub->i, MAX_STRING_SIZE), teststr) == 0)    outIndex = 5;
 else	if (strcmp( strntoupper((char*)pgsub->k, MAX_STRING_SIZE), teststr) == 0)    outIndex = 6;
 else	if (strcmp( strntoupper((char*)pgsub->m, MAX_STRING_SIZE), teststr) == 0)    outIndex = 7;
 else	if (strcmp( strntoupper((char*)pgsub->o, MAX_STRING_SIZE), teststr) == 0)    outIndex = 8;
 else	if (strcmp( strntoupper((char*)pgsub->q, MAX_STRING_SIZE), teststr) == 0)    outIndex = 9;
 else	if (strcmp( strntoupper((char*)pgsub->s, MAX_STRING_SIZE), teststr) == 0)    outIndex = 10;
 else  outIndex = 0;

 if (outIndex != 0)					/* bad found    */
 { strncpy( outHealth, teststr, MAX_STRING_SIZE );
   outIndexM = outIndex;
 }
 else							/* no bad found: check for warn */
 {
   strncpy( teststr, "WARNING", MAX_STRING_SIZE );
  	if (strcmp( strntoupper((char*)pgsub->a, MAX_STRING_SIZE), teststr) == 0)    outIndex = 1;
   else	if (strcmp( strntoupper((char*)pgsub->c, MAX_STRING_SIZE), teststr) == 0)    outIndex = 2;
   else	if (strcmp( strntoupper((char*)pgsub->e, MAX_STRING_SIZE), teststr) == 0)    outIndex = 3;
   else	if (strcmp( strntoupper((char*)pgsub->g, MAX_STRING_SIZE), teststr) == 0)    outIndex = 4;
   else	if (strcmp( strntoupper((char*)pgsub->i, MAX_STRING_SIZE), teststr) == 0)    outIndex = 5;
   else	if (strcmp( strntoupper((char*)pgsub->k, MAX_STRING_SIZE), teststr) == 0)    outIndex = 6;
   else	if (strcmp( strntoupper((char*)pgsub->m, MAX_STRING_SIZE), teststr) == 0)    outIndex = 7;
   else	if (strcmp( strntoupper((char*)pgsub->o, MAX_STRING_SIZE), teststr) == 0)    outIndex = 8;
   else	if (strcmp( strntoupper((char*)pgsub->q, MAX_STRING_SIZE), teststr) == 0)    outIndex = 9;
   else	if (strcmp( strntoupper((char*)pgsub->s, MAX_STRING_SIZE), teststr) == 0)    outIndex = 10;
   else  outIndex = 0;

  if (outIndex != 0)					/* warning found    */
  { strncpy( outHealth, teststr, MAX_STRING_SIZE );
    outIndexM = outIndex;
  }
  else							/* no bad nor warn found: check for something not-empty and unknown*/
  {
   strncpy( teststr, "GOOD", MAX_STRING_SIZE );
	if ( 	(strlen((char*)pgsub->a) != 0) && (strcmp( strntoupper((char*)pgsub->a, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->a," /s/t") != strlen((char*)pgsub->a)) )
			{  outIndex = 1;  strncpy( outHealth, (char*)pgsub->a, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->c) != 0) && (strcmp( strntoupper((char*)pgsub->c, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->c," /s/t") != strlen((char*)pgsub->c)) )	
			{  outIndex = 2;  strncpy( outHealth, (char*)pgsub->c, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->e) != 0) && (strcmp( strntoupper((char*)pgsub->e, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->e," /s/t") != strlen((char*)pgsub->e)) )	
			{  outIndex = 3;  strncpy( outHealth, (char*)pgsub->e, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->g) != 0) && (strcmp( strntoupper((char*)pgsub->g, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->g," /s/t") != strlen((char*)pgsub->g)) )	
			{  outIndex = 4;  strncpy( outHealth, (char*)pgsub->g, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->i) != 0) && (strcmp( strntoupper((char*)pgsub->i, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->i," /s/t") != strlen((char*)pgsub->i)) )	
			{  outIndex = 5;  strncpy( outHealth, (char*)pgsub->i, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->k) != 0) && (strcmp( strntoupper((char*)pgsub->k, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->k," /s/t") != strlen((char*)pgsub->k)) )	
			{  outIndex = 6;  strncpy( outHealth, (char*)pgsub->k, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->m) != 0) && (strcmp( strntoupper((char*)pgsub->m, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->m," /s/t") != strlen((char*)pgsub->m)) )	
			{  outIndex = 7;  strncpy( outHealth, (char*)pgsub->m, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->o) != 0) && (strcmp( strntoupper((char*)pgsub->o, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->o," /s/t") != strlen((char*)pgsub->o)) )	
			{  outIndex = 8;  strncpy( outHealth, (char*)pgsub->o, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->q) != 0) && (strcmp( strntoupper((char*)pgsub->q, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->q," /s/t") != strlen((char*)pgsub->q)) )	
			{  outIndex = 9;  strncpy( outHealth, (char*)pgsub->q, MAX_STRING_SIZE ); }
   else	if ( 	(strlen((char*)pgsub->s) != 0) && (strcmp( strntoupper((char*)pgsub->s, MAX_STRING_SIZE), teststr) != 0) &&
		(strspn((char*)pgsub->s," /s/t") != strlen((char*)pgsub->s)) )	
			{  outIndex =10;  strncpy( outHealth, (char*)pgsub->s, MAX_STRING_SIZE ); }
   else 
   { 
     outIndex = 0;
     strncpy( outHealth, "GOOD", MAX_STRING_SIZE );
   } 

 	if ( (strlen((char*)pgsub->b) != 0) && (strspn((char*)pgsub->b," /s/t") != strlen((char*)pgsub->b)) )	outIndexM = 1;
   else	if ( (strlen((char*)pgsub->d) != 0) && (strspn((char*)pgsub->d," /s/t") != strlen((char*)pgsub->d)) )	outIndexM = 2;
   else	if ( (strlen((char*)pgsub->f) != 0) && (strspn((char*)pgsub->f," /s/t") != strlen((char*)pgsub->f)) )	outIndexM = 3;
   else	if ( (strlen((char*)pgsub->g) != 0) && (strspn((char*)pgsub->g," /s/t") != strlen((char*)pgsub->h)) )	outIndexM = 4;
   else	if ( (strlen((char*)pgsub->j) != 0) && (strspn((char*)pgsub->j," /s/t") != strlen((char*)pgsub->j)) )	outIndexM = 5;
   else	if ( (strlen((char*)pgsub->l) != 0) && (strspn((char*)pgsub->l," /s/t") != strlen((char*)pgsub->l)) )	outIndexM = 6;
   else	if ( (strlen((char*)pgsub->n) != 0) && (strspn((char*)pgsub->n," /s/t") != strlen((char*)pgsub->n)) )	outIndexM = 7;
   else	if ( (strlen((char*)pgsub->p) != 0) && (strspn((char*)pgsub->p," /s/t") != strlen((char*)pgsub->p)) )	outIndexM = 8;
   else	if ( (strlen((char*)pgsub->r) != 0) && (strspn((char*)pgsub->r," /s/t") != strlen((char*)pgsub->r)) )	outIndexM = 9;
   else	if ( (strlen((char*)pgsub->t) != 0) && (strspn((char*)pgsub->t," /s/t") != strlen((char*)pgsub->t)) )	outIndexM = 10;
   else  outIndexM = 0;

  }  /* no warn found */
 }   /* no bad  found */

  switch (outIndexM)
  {
    case 1:	PoutMess = (char*)pgsub->b;    break;
    case 2:	PoutMess = (char*)pgsub->d;    break;
    case 3:	PoutMess = (char*)pgsub->f;    break;
    case 4:	PoutMess = (char*)pgsub->h;    break;
    case 5:	PoutMess = (char*)pgsub->j;    break;
    case 6:	PoutMess = (char*)pgsub->l;    break;
    case 7:	PoutMess = (char*)pgsub->n;    break;
    case 8:	PoutMess = (char*)pgsub->p;    break;
    case 9:	PoutMess = (char*)pgsub->r;    break;
    case 10:	PoutMess = (char*)pgsub->t;    break;
    default:	PoutMess = & outMess[0]; strcpy(outMess, "");	 break; 
  }

/* Output the resulting health value, message and index. */
 
   strncpy( (char*)pgsub->vala, outHealth, MAX_STRING_SIZE );
   strncpy( (char*)pgsub->valb, PoutMess,   MAX_STRING_SIZE );
   *(long *)pgsub->valc = outIndex;
   *(long *)pgsub->vald = outIndexM;

#if 0
	sprintf( messages, "%s - HealthComb. triggered! Result=%s, I1=%d, I2=%d", pgsub->name,  (char*)pgsub->vala, outIndex, outIndexM); 
	agLogMessage( mechindex, DEB_FULL, messages);

	sprintf( messages2, "8 Inp: :%s:%s:%s:%s:%s:%s:%s:%s", 
	(char *)pgsub->a, (char *)pgsub->c, (char *)pgsub->e, (char *)pgsub->g, 
	(char *)pgsub->i, (char *)pgsub->k, (char *)pgsub->m, (char *)pgsub->o ); 

	sprintf( messages, "%s - %s", pgsub->name, messages2); 
	agLogMessage( mechindex, DEB_FULL, messages);
#endif

  return status;
}			/* new health combine */

long HealthCombInit( struct genSubRecord *pgsub )
{
  return (0);
}

/* ===================================================================== */
/* switches all unused inputs to inPos. by default	*/

long inposCombInit( struct genSubRecord *pgsub ) 
{
  int i;

  for (i=0; i<10; i++)
  {
    switch (i)
    { case 0:  *(long*)pgsub->a = 131071;  break; /* This is to set every bit */
      case 1:  *(long*)pgsub->c = 131071;  break; /* so that "and" works well */
      case 2:  *(long*)pgsub->e = 131071;  break;
      case 3:  *(long*)pgsub->g = 131071;  break;
      case 4:  *(long*)pgsub->i = 131071;  break;
      case 5:  *(long*)pgsub->k = 131071;  break;
      case 6:  *(long*)pgsub->m = 131071;  break;
      case 7:  *(long*)pgsub->o = 131071;  break;
      case 8:  *(long*)pgsub->q = 131071;  break;
      case 9:  *(long*)pgsub->s = 131071;  break;
    }
  }
  return (0);
}

/* ===================================================================== */
/* VALA ...: value 		(long)
 * VALB ...: user message 	(string)
 **
 * VALA/B  : Sum of all FLAGs
 * VALC/D  : IPOSFLAG
 * VALE/F  : DATUFLAG
 * VALG/H  : PARKFLAG
 * VALI/J  : POSMFLAG
 **
 * VALU: winning input-index	(long)	
 **
 * routuine combines ('and's) all flags of underlying mechs
 * and gives out the singled flags - inPos etc.
 */

/* #define debug	*/

long inposCombine( struct genSubRecord *pgsub ) 
{
  long  status = PASS;                 			/* return status */
  short stop;			
  long  outVal, i;
  char *(PoutMess[4]);

  #ifdef debug
    char messages[80];      				/* Message buffer */
  #endif


#if 0
  long test;
  char dummy [2];

  dummy[0] = '\0';
  outIndex =  0;
  outVal   = DATUFLAG | PARKFLAG | POSMFLAG | IPOSFLAG;	/* prepare initial mask	*/

  for (i=0; i<10; i++)
  {
    switch (i)
    { case 0: test = *(long*)pgsub->a;	break;
      case 1: test = *(long*)pgsub->c;	break;
      case 2: test = *(long*)pgsub->e;	break;
      case 3: test = *(long*)pgsub->g;	break;
      case 4: test = *(long*)pgsub->i;	break;
      case 5: test = *(long*)pgsub->k;	break;
      case 6: test = *(long*)pgsub->m;	break;
      case 7: test = *(long*)pgsub->o;	break;
      case 8: test = *(long*)pgsub->q;	break;
      case 9: test = *(long*)pgsub->s;	break;
    }

    if (!(outVal &= test))
    {
      outIndex = i+1;
      break;				/* stop for loop	*/
    }
  }
#endif


   /* 'and'ing  all flag values	*/
   outVal  = (*(long*)pgsub->a);
   outVal &= (*(long*)pgsub->c)  &  (*(long*)pgsub->e)  &  (*(long*)pgsub->g);
   outVal &= (*(long*)pgsub->i)  &  (*(long*)pgsub->k)  &  (*(long*)pgsub->m);
   outVal &= (*(long*)pgsub->o)  &  (*(long*)pgsub->q)  &  (*(long*)pgsub->s);

  *(long*)pgsub->vala = outVal;		/* output "and"ed flags	*/
  *(long*)pgsub->valc = (outVal & IPOSFLAG)? 1:0;
  *(long*)pgsub->vale = (outVal & DATUFLAG)? 1:0;
  *(long*)pgsub->valg = (outVal & PARKFLAG)? 1:0;
  *(long*)pgsub->vali = (outVal & POSMFLAG)? 1:0;
  strncpy( (char*)pgsub->valb, (char*)pgsub->b,   MAX_STRING_SIZE );	/* Mess. for FLAGS	*/

  stop = 0;					  PoutMess[0] = (char*)pgsub->b;
  for (i=0; i<10; i++)
  { switch (i)
    { case 0: if (!(*(long*)pgsub->a & IPOSFLAG)) PoutMess[0] = (char*)pgsub->b; stop=1; break;
      case 1: if (!(*(long*)pgsub->c & IPOSFLAG)) PoutMess[0] = (char*)pgsub->d; stop=1; break;
      case 2: if (!(*(long*)pgsub->e & IPOSFLAG)) PoutMess[0] = (char*)pgsub->f; stop=1; break;
      case 3: if (!(*(long*)pgsub->g & IPOSFLAG)) PoutMess[0] = (char*)pgsub->h; stop=1; break;
      case 4: if (!(*(long*)pgsub->i & IPOSFLAG)) PoutMess[0] = (char*)pgsub->j; stop=1; break;
      case 5: if (!(*(long*)pgsub->k & IPOSFLAG)) PoutMess[0] = (char*)pgsub->l; stop=1; break;
      case 6: if (!(*(long*)pgsub->m & IPOSFLAG)) PoutMess[0] = (char*)pgsub->n; stop=1; break;
      case 7: if (!(*(long*)pgsub->o & IPOSFLAG)) PoutMess[0] = (char*)pgsub->p; stop=1; break;
      case 8: if (!(*(long*)pgsub->q & IPOSFLAG)) PoutMess[0] = (char*)pgsub->r; stop=1; break;
      case 9: if (!(*(long*)pgsub->s & IPOSFLAG)) PoutMess[0] = (char*)pgsub->t; stop=1; break;
    } if (stop) break;		/* stop for-loop	*/
  }
  stop = 0;					  PoutMess[1] = (char*)pgsub->b;
  for (i=0; i<10; i++)
  { switch (i)
    { case 0: if (!(*(long*)pgsub->a & DATUFLAG)) PoutMess[1] = (char*)pgsub->b; stop=1; break;
      case 1: if (!(*(long*)pgsub->c & DATUFLAG)) PoutMess[1] = (char*)pgsub->d; stop=1; break;
      case 2: if (!(*(long*)pgsub->e & DATUFLAG)) PoutMess[1] = (char*)pgsub->f; stop=1; break;
      case 3: if (!(*(long*)pgsub->g & DATUFLAG)) PoutMess[1] = (char*)pgsub->h; stop=1; break;
      case 4: if (!(*(long*)pgsub->i & DATUFLAG)) PoutMess[1] = (char*)pgsub->j; stop=1; break;
      case 5: if (!(*(long*)pgsub->k & DATUFLAG)) PoutMess[1] = (char*)pgsub->l; stop=1; break;
      case 6: if (!(*(long*)pgsub->m & DATUFLAG)) PoutMess[1] = (char*)pgsub->n; stop=1; break;
      case 7: if (!(*(long*)pgsub->o & DATUFLAG)) PoutMess[1] = (char*)pgsub->p; stop=1; break;
      case 8: if (!(*(long*)pgsub->q & DATUFLAG)) PoutMess[1] = (char*)pgsub->r; stop=1; break;
      case 9: if (!(*(long*)pgsub->s & DATUFLAG)) PoutMess[1] = (char*)pgsub->t; stop=1; break;
    } if (stop) break;		/* stop for-loop	*/
  }
  stop = 0;					  PoutMess[2] = (char*)pgsub->b;
  for (i=0; i<10; i++)
  { switch (i)
    { case 0: if (!(*(long*)pgsub->a & PARKFLAG)) PoutMess[2] = (char*)pgsub->b; stop=1; break;
      case 1: if (!(*(long*)pgsub->c & PARKFLAG)) PoutMess[2] = (char*)pgsub->d; stop=1; break;
      case 2: if (!(*(long*)pgsub->e & PARKFLAG)) PoutMess[2] = (char*)pgsub->f; stop=1; break;
      case 3: if (!(*(long*)pgsub->g & PARKFLAG)) PoutMess[2] = (char*)pgsub->h; stop=1; break;
      case 4: if (!(*(long*)pgsub->i & PARKFLAG)) PoutMess[2] = (char*)pgsub->j; stop=1; break;
      case 5: if (!(*(long*)pgsub->k & PARKFLAG)) PoutMess[2] = (char*)pgsub->l; stop=1; break;
      case 6: if (!(*(long*)pgsub->m & PARKFLAG)) PoutMess[2] = (char*)pgsub->n; stop=1; break;
      case 7: if (!(*(long*)pgsub->o & PARKFLAG)) PoutMess[2] = (char*)pgsub->p; stop=1; break;
      case 8: if (!(*(long*)pgsub->q & PARKFLAG)) PoutMess[2] = (char*)pgsub->r; stop=1; break;
      case 9: if (!(*(long*)pgsub->s & PARKFLAG)) PoutMess[2] = (char*)pgsub->t; stop=1; break;
    } if (stop) break;		/* stop for-loop	*/
  }
  stop = 0;					  PoutMess[3] = (char*)pgsub->b;
  for (i=0; i<10; i++)
  { switch (i)
    { case 0: if (!(*(long*)pgsub->a & POSMFLAG)) PoutMess[3] = (char*)pgsub->b; stop=1; break;
      case 1: if (!(*(long*)pgsub->c & POSMFLAG)) PoutMess[3] = (char*)pgsub->d; stop=1; break;
      case 2: if (!(*(long*)pgsub->e & POSMFLAG)) PoutMess[3] = (char*)pgsub->f; stop=1; break;
      case 3: if (!(*(long*)pgsub->g & POSMFLAG)) PoutMess[3] = (char*)pgsub->h; stop=1; break;
      case 4: if (!(*(long*)pgsub->i & POSMFLAG)) PoutMess[3] = (char*)pgsub->j; stop=1; break;
      case 5: if (!(*(long*)pgsub->k & POSMFLAG)) PoutMess[3] = (char*)pgsub->l; stop=1; break;
      case 6: if (!(*(long*)pgsub->m & POSMFLAG)) PoutMess[3] = (char*)pgsub->n; stop=1; break;
      case 7: if (!(*(long*)pgsub->o & POSMFLAG)) PoutMess[3] = (char*)pgsub->p; stop=1; break;
      case 8: if (!(*(long*)pgsub->q & POSMFLAG)) PoutMess[3] = (char*)pgsub->r; stop=1; break;
      case 9: if (!(*(long*)pgsub->s & POSMFLAG)) PoutMess[3] = (char*)pgsub->t; stop=1; break;
    } if (stop) break;		/* stop for-loop	*/
  }

  strncpy( (char*)pgsub->vald, PoutMess[0],   MAX_STRING_SIZE );	/* Mess. for IPOSFLAG	*/
  strncpy( (char*)pgsub->valf, PoutMess[1],   MAX_STRING_SIZE );	/* Mess. for DATUFLAG	*/
  strncpy( (char*)pgsub->valh, PoutMess[2],   MAX_STRING_SIZE );	/* Mess. for PARKFLAG	*/
  strncpy( (char*)pgsub->valj, PoutMess[3],   MAX_STRING_SIZE );	/* Mess. for POSMFLAG	*/


#if 0
  for (i=0; i<10; i++)
  {
    switch (i)
    { case 0: test = *(long*)pgsub->a;	break;
      case 1: test = *(long*)pgsub->c;	break;
      case 2: test = *(long*)pgsub->e;	break;
      case 3: test = *(long*)pgsub->g;	break;
      case 4: test = *(long*)pgsub->i;	break;
      case 5: test = *(long*)pgsub->k;	break;
      case 6: test = *(long*)pgsub->m;	break;
      case 7: test = *(long*)pgsub->o;	break;
      case 8: test = *(long*)pgsub->q;	break;
      case 9: test = *(long*)pgsub->s;	break;
    }

  switch (outIndex)
  { /* preparing a pointer from which the message is copied later	*/
    case 1:	PoutMess = (char*)pgsub->b;    break;
    case 2:	PoutMess = (char*)pgsub->d;    break;
    case 3:	PoutMess = (char*)pgsub->f;    break;
    case 4:	PoutMess = (char*)pgsub->h;    break;
    case 5:	PoutMess = (char*)pgsub->j;    break;
    case 6:	PoutMess = (char*)pgsub->l;    break;
    case 7:	PoutMess = (char*)pgsub->n;    break;
    case 8:	PoutMess = (char*)pgsub->p;    break;
    case 9:	PoutMess = (char*)pgsub->r;    break;
    case 10:	PoutMess = (char*)pgsub->t;    break;
    default:	PoutMess = dummy;	       break; 
  }
  strncpy( (char*)pgsub->valb, PoutMess,   MAX_STRING_SIZE );
  *(long *)pgsub->valu = outIndex;
#endif


  #ifdef debug
  sprintf( messages, "%s - inPosComb. triggered! Result=%d", pgsub->name,  outVal); 
  agLogMessage( ag_cc, DEB_FULL, messages);

  sprintf( messages, "%s - 8 Inp: %d:%d:%d:%d:%d:%d:%d:%d", pgsub->name,
  *(long*)pgsub->a, *(long*)pgsub->c, *(long*)pgsub->e, *(long*)pgsub->g, 
  *(long*)pgsub->i, *(long*)pgsub->k, *(long*)pgsub->m, *(long*)pgsub->o ); 
  agLogMessage( ag_cc, DEB_FULL, messages);
  /* since we are rarely debugging here, the gbd debug level was taken instead of hrwfs or gbd	*/
  #endif

  return status;
}

#undef debug
/* ===================================================================== */

/*+
 *   Function name:
 *    cicsStringAppend -  Append two strings together.
 *
 *   Purpose:
 *   This function appends two input strings together to make one
 *   output string.
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = cicsStringAppend( struct genSubRecord *pgsub );
 *
 *   Parameters in:
 *      > pgsub->a    string*  Input string 1
 *      > pgsub->b    string*  Input string 2
 *
 *   Parameters out:
 *      < pgsub->vala string*  Resulting output string
 *
 *   Return value:
 *      < status      long        Status value
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
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   18-Jul-1997: Original version.                                (smb)
 *-
 */

long cicsStringAppend( struct genSubRecord *pgsub ) 
{
  long status;                         /* return status */
  char string[MAX_STRING_SIZE * 2];    /* Resulting string */

/* Initialise the status */

  status = PASS;

/* Build up the output string */

  sprintf( string, "%s + %s", (char *)pgsub->a, (char *)pgsub->b );

/* Copy as much of the string as possible to the output, truncating it
 * if it is longer than MAX_STRING_SIZE.
 */

  strncpy( (char *)pgsub->vala, string, MAX_STRING_SIZE );

  return status;
}


/* ===================================================================== */

/*+
 *   Function name:
 *    cicsStringFilter -  Filter out any string matching a given tag.
 *
 *   Purpose:
 *   This function passes a string from input A to output A, but only if
 *   it does not match a tag provided in input B.
 *
 *   The function is designed to be used with the EPICS "genSub" record.
 *
 *   Invocation:
 *   status = cicsStringFilter( struct genSubRecord *pgsub );
 *
 *   Parameters in:
 *      > pgsub->a    string*  Input string
 *      > pgsub->b    string*  Tag to be filtered out
 *
 *   Parameters out:
 *      < pgsub->vala string*  Output string
 *
 *   Return value:
 *      < status      long        Status value
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
 *
 *   Author:
 *   Steven Beard  (smb@roe.ac.uk)
 *
 *   History:
 *   18-Aug-1997: Original version.                                (smb)
 *-
 */

long cicsStringFilter( struct genSubRecord *pgsub ) 
{
  long status;                         /* return status */

/* Initialise the status */

  status = PASS;

/* Test the string against the tag provided, and only copy it to the output
 * if the string is non blank and does not match the tag. */

  if ( (strlen((char *)pgsub->a) != 0) &&
       (strspn((char *)pgsub->a," ") != strlen((char *)pgsub->a)) )
  {

    if ( strncmp((char *)pgsub->a, (char *)pgsub->b, MAX_STRING_SIZE) != 0 )
    {

/* Match with tag not found. Copy the input to the output. */

      strncpy( (char *)pgsub->vala, (char *)pgsub->a, MAX_STRING_SIZE );
    }
  }
  return status;
}


/* ===================================================================== */

epicsRegisterFunction(carDrive);
epicsRegisterFunction(carInit);
epicsRegisterFunction(inposCombine);
epicsRegisterFunction(inposCombInit);
epicsRegisterFunction(HealthCombine);
epicsRegisterFunction(HealthCombInit);
