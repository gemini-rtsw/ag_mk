/* 
 *  FILENAME
 *  --------
 *  convLogData.c
 *
 *  PURPOSE
 *  -------
 *  To convert logged data files, written by the A&G logging system.
 *  Routine runs on the UNIX side, not under VxWorks.
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *  convLogData();
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth (ocf)
 *
 *  HISTORY
 *  -------
 *  05-May-1998:	Original version			(ocf)
 *
 *  INVOCATION
 *  ----------
 *   From the UNIX shell:
 *     convLogData <infile> <outfile.asc>
 *   The extension "infile.asc" for the outfile name is not a constrain
 *   but preferred.
 *
 *  USAGE
 *  -----
 *   The data files must have header lines containing:
 *     	the keyword "A&G"
 *     	the keyword "types" followed by a string of type chars
 *	2 line feeds between header and first sample
 *	1 line feed  after each sample
 *   Every sample consists of data pieces, which types are given in the header
 *     (double, long, double/time, string ...).
 *   The data files may contain more than 1 header with following samples.
 *   If the output file already exists, teh new ASCII data will be appended.
 *
 *  Limitations: 
 *  ------------
 *   The file size must be less than the largest allocable memory block.
 *   2 MB (logged data of about 32 minutes) will work in most cases.
 *   This limitation could be removed by reading small blocks of a big file.
 *
 *   The necessity of a line feed char after each sample could be made 
 *     switchable by an additional input parameter, so that other data files
 *     (not by A&G) could be interpreted.
 *
 *   Strings cannot be converted, because the sample size must be constant.
 *   This could be removed by not testing for line feeds after the samples 
 *     and by testing for new keywords for a longer file length.
 *   Strings must not contain the keyword "A&G".
 *
 *   In case of missing "types" keyword or missing of 2 line feeds, there are 
 *      not enough error messages.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/* ====================================================================	*/

#define LINEBUFSIZE	1024
/* ====================================================================	*/

/* from slamac.h	*/
/* max(A,B) - larger (most +ve) of two numbers (generic) */
#define gmax(A,B) ((A)>(B)?(A):(B))
/* dint(A) - truncate to nearest whole number towards zero (double) */
#define dint(A) ((A)<0.0?ceil(A):floor(A))
/* dnint(A) - round to nearest whole number (double) */
#define dnint(A) ((A)<0.0?ceil((A)-0.5):floor((A)+0.5))
/* dmod(A,B) - A modulo B (double) */
#define dmod(A,B) ((B)!=0.0?((A)*(B)>0.0?(A)-(B)*floor((A)/(B))\
                                        :(A)+(B)*floor(-(A)/(B))):(A))

/* ====================================================================	*/

/* from file (slalib/)dd2tf.c	*/

/*  Convert an interval in days into hours, minutes, seconds. */
void slaDd2tf ( int ndp, double days, char *sign, int ihmsf[4] )
#define D2S 86400.0    /* Days to seconds */
{
   double rs, rm, rh, a, ah, am, as, af;

/* Handle sign */
   *sign = (char) ( ( days < 0.0 ) ?  '-' : '+' );

/* Field units in terms of least significant figure */
   rs = pow ( 10.0, (double) gmax ( ndp, 0 ) );
   rs = dint ( rs );
   rm = rs * 60.0;
   rh = rm * 60.0;

/* Round interval and express in smallest units required */
   a = rs * D2S * fabs ( days );
   a = dnint ( a );

/* Separate into fields */
   ah = a / rh;
   ah = dint ( ah );
   a  = a - ah * rh;
   am = a / rm;
   am = dint ( am );
   a  = a - am * rm;
   as = a / rs;
   as = dint ( as );
   af = a - as * rs;

/* Return results */
   ihmsf[0] = (int) ah;
   ihmsf[1] = (int) am;
   ihmsf[2] = (int) as;
   ihmsf[3] = (int) af;
}

/* ====================================================================	*/

void slaDjcl ( double djm, int *iy, int *im, int *id, double *fd, int *j)
{
  double f, d;
  long jd, n4, nd10;

/* Check if date is acceptable */
   if ( ( djm <= -2395522.0 ) || ( djm >= 1e9 ) ) {
      *j = -1;
      return;
   } else {
      *j = 0;

   /* Separate day and fraction */
      f = dmod ( djm, 1.0 );
      if ( f < 0.0 ) f += 1.0;
      d = djm - f;
      d = dnint ( d );

   /* Express day in Gregorian calendar */
      jd = (long) dnint ( d ) + 2400001;
      n4 = 4L*(jd+((6L*((4L*jd-17918L)/146097L))/4L+1L)/2L-37L);
      nd10 = 10L*(((n4-237L)%1461L)/4L)+5L;
      *iy = (int) (n4/1461L-4712L);
      *im = (int) (((nd10/306L+2L)%12L)+1L);
      *id = (int) ((nd10%306L)/10L+1L);
      *fd = f;
      *j = 0;
   }
}

/* ====================================================================	*/

/* MJD for 1970 January 1.0 */
#define UNIXEPOCH 40587.0

/* 1 second in days */
#define SEC 0.000011574074074074074074

   typedef enum {
                  TAI,      /* International Atomic Time    */
                  UTC,      /* Coordinated Universal Time   */
                  UT1,      /* Universal Time               */
                  TT,       /* Terrestrial Time             */
                  TDB,      /* Barycentric Dynamical Time   */
                  GMST,     /* Greenwich Mean Sidereal Time */
                  LAST      /* Local Apparent Sidereal Time */
                } timescale;

/* ====================================================================	*/

int timeThenD ( double tai, timescale scale, double *datemj )
{
/* Express given TAI in specified timescale. */
   switch ( scale ) {
   case TAI:
      *datemj = tai / 86400.0 + UNIXEPOCH;
      break;
   default:
      return -1;
   }
   return 0;
}
/* ====================================================================	*/
int timeThenC ( double tai, timescale scale, int ndp, int *ymdhmsf )
{
   int j;
   double t, d, f;
   char s;

	/* Express the clock time as an MJD in the specified timescale. */
   if ( (j = timeThenD ( tai, scale, &t )) ) return j;

					/* Separate days and fraction of a day. */
   d = floor ( t );
   f = t - d;
					/* Format the time of day. */
   slaDd2tf ( ndp, f, &s, ymdhmsf + 3 );

					/* If rounded past 24 hours, carry. */
   if ( ymdhmsf [ 3 ] >= 24 ) {
      ymdhmsf [ 3 ] -= 24;
      d++;
   }
					/* Format the date, and exit. */
   slaDjcl ( d, ymdhmsf, ymdhmsf + 1, ymdhmsf + 2, &f, &j );
   return j; 
}


/* ===================================================================== */
long tai2str (char* messages, double t)
{
  int date [7];

  timeThenC (t,0,3,date);		/* 3 dig in fract. (=ms)*/
  sprintf( messages, "%02d.%02d.%d %02d:%02d:%02d.%03d", 
    date[2], date[1], date[0], date[3], date[4], date[5], date[6]);

  if (t<0 || (t>0 && t<1e-3) || t>6e9) 
    sprintf( messages, "%- 19.12g", t);

  return (0);
}

/* ====================================================================	*/
/* returns -1 if nothing found!	*/
long findstr (const char * string, const char * ch, long maxlen)
{
  long i, rval=0;
  int strl = strlen (ch);

  for (i=0; i<maxlen; i++)
    if (string[i] == ch[0]) 
      if (!(rval = strncmp (string+i, ch, strl)) )			/* equal	*/
      {
  /* printf ("\ni=%d, rval=%d, strl=%d searching %d bytes for '%s' in (substring) '%s'\n\n", i, rval, strl, maxlen, ch, string+i); */
        return (i);
      }


  return (-1);						/* not found!	*/
}
/* ====================================================================	*/
/* returns -1 for not found!	*/
long findchar (const char * string, char ch, long maxlen)
{
  long i;

  for (i=0; i<maxlen; i++)
    if (string[i] == ch)
      return (i);

  return (-1);						/* not found!	*/
}

/* ====================================================================	*/
double getD (const char * string)
{
  double d;
  int i;

/*  d = *(double*)string;	*/

  for (i=0; i<sizeof(double); i++)
    ((char*)&d)[i] = string [i];

/*  for (i=0; i<sizeof(double); i++)
    ((char*)&d)[i] = string [sizeof(double)-1-i];
*/
  return (d);
}
/* ====================================================================	*/
long getL (const char * string)
{
  long d;
  int i;
  
/*  d = *(long*)string; */

  for (i=0; i<sizeof(long); i++)
    ((char*)&d)[i] = string [i];

/*  for (i=0; i<sizeof(long); i++)
    ((char*)&d)[i] = string [sizeof(long)-1-i];
*/
  return (d);
}

/* ====================================================================	*/
#define IFD	  if ((buf+numRead) >= (str+sizeof (double)))
#define IFL	  if ((buf+numRead) >= (str+sizeof (long)))


int main(int argc, char *argv[])
{
  FILE   *fd, *fd2;
  char   *buf;
  char   *str, str2, *strsic=NULL, *test, *test2;
  long   numRead;
  int    i,j;
  int    size, samplesize;
  char   srcType[25];
  char   messages[80];

  if( argc < 3 )
  {
    printf("Program will use header lines to convert a file of raw data, written by A&G system logging \n");
    printf("Usage: %s <infile> <outfile> \n", argv[0]);
    if (argc >= 2)
      printf("Now: <infile>='%s' <outfile>=not specified \n", argv[1]);
    exit(0);
  }

  fd  = fopen(argv[1], "r");
  fd2 = fopen(argv[2], "a");

  if (fd && fd2)
  {
    fseek(fd, 0, SEEK_END);				/* point to EOF		*/
    size = ftell(fd);					/* get file size	*/
    rewind(fd);
    str = buf = malloc(size+1);				/* allocate file buffer	*/
    numRead = fread( buf, 1, size, fd );		/* read whole file	*/
    buf[size] = '\0';					/* last+1 is always 0 !	*/
							/*  (string convertion)	*/
    j = 0;						/* sample counter	*/
    samplesize = size;					/* first header search	*/

    while ((buf+numRead) > (str+1) && (strsic<str))	/*&& j<10)*/	/* read samples		*/
    {
      strsic = str;
      str2 = findstr (str, "A&G", samplesize+strlen("A&G"));     
      if (str2 != -1)
      {
	fprintf (fd2, "\nInput file (size=%ld)=\"%s\", output file=\"%s\". \n", numRead, argv[1],argv[2]);
	if (j != 0)
	{
	  printf (     "%d samples written \n",j);
	  fprintf(fd2, "%d samples written \n",j);
	}
	
	str += str2;
	strsic = str;

        str2 = findstr (str, "types=", 200);     
	str += (str2 + strlen ("types="));
	printf("fsize=%ld, 'types=' found before offset %d, str2=%d \n", numRead, str-buf, str2);
    
	samplesize = 0;
    
	for (i=0; i<25; i++)
	  if (islower((int)str[i]) || isupper((int)str[i]) || isdigit((int)str[i]))
	  {
	    srcType[i] = str[i];
	    switch (srcType[i])
	    {
	      case 'T': samplesize+=sizeof (double);  break;
	      case 'D': samplesize+=sizeof (double);  break;
	      case 'L': samplesize+=sizeof (long);    break;  
	      case 'S': samplesize+=1;    	      break;  /* string size cannot be predicted  */
	    }
	  }
	  else break;

	srcType[i] = 0;
    
	test2 = str;
	str2 = (findchar (str, '\n', buf+numRead-str));			/* 1st LF after header	*/
	str += str2 + 1;
	*(str-1) = '\0';						/* terminate header	*/

	test = str;
	str2 = (findchar (str, '\n', buf+numRead-str));			/* 2nd LF after header	*/
	str += str2 + 1;
    
	printf("2*LF found (%d) after (%d)%d/%d, %d Types found, Samplesize=%d, cnt=%d \n", str2, test2-buf, test-buf, str-buf,i, samplesize, buf+numRead-str);
    	
	fprintf (fd2, "header: %s\n\n", strsic);			/* write header		*/
    	 printf (     "header: %s\n\n", strsic);			/* write header		*/
      }
      else
      {				/* no header found in next sample - search next LF for synchr.	*/	
	test = str;
        str +=   findchar (str, '\n', buf+numRead-str) + 1;		/* search next LF	*/
	/* fprintf (fd2,"sw. %d to %d\t", test-buf, str-buf);		*/
      }

      fprintf(fd2, "sample %3d at %4d: \t",j, str-buf);

      for (i=0; (i<25) && srcType[i]; i++)				/* read values		*/
      {
        switch (srcType[i])
        {
	  case 'T': IFD  { tai2str (messages, getD(str)); 
			 fprintf (fd2, "%s\t", messages); }	   str+=sizeof (double);  break;
	  case 'D': IFD  fprintf (fd2, "%- 19.12g\t", getD(str));  str+=sizeof (double);  break;
	  case 'L': IFL  fprintf (fd2, "% ld\t",      getL(str));  str+=sizeof (long);    break;
	  case 'S': fprintf (fd2, "\"%s\"\t", str); 		   str+=strlen (str) + 1; break;
	  default:  printf("Should never see this!\n");					  break;
        }
      }
      j++;

      fprintf (fd2, "\n");						/* LF after each sample	*/

      if (buf+numRead > str)
      {
        if (*str != '\n')							/* next = LF ?		*/
        {	fprintf (fd2,"Char %d after sample %d is not LF, but %#x !!\n", str-buf, j-1, (unsigned char)*str);
		 printf (    "Char %d after sample %d is not LF, but %#x !!\n", str-buf, j-1, (unsigned char)*str);
        }
        /* else	fprintf (fd2,"Char %d after sample %d is LF.\t", (long)str-(long)buf, j-1);	*/
      }
      else  break;
   }

     printf (     "File completely read.\n");
    fprintf (fd2, "File completely read.\n");
     printf (     "%d samples written \n",j);
    fprintf (fd2, "%d samples written \n",j);

  }
  else		
  {	
    printf("Error opening file: %s \n", (fd==0)? argv[1]: argv[2]);
    if (fd2) fprintf (fd2, "Error opening file: \"%s\" (due to incorrect working directory?). \n", (fd==0)? argv[1]: argv[2]);
  }

  fclose(fd2);
  fclose(fd);

  return(0);
}

/* ====================================================================	*/
/* was used in case of "no header found" after searching for next LF	*/

	#if 0 
	test = str;
        if (*(str+samplesize) != '\n' )
           str += findchar (str, '\n', buf+numRead-str) + 1;		/* search next LF	*/
        if (*(str+samplesize) != '\n' )
           str += findchar (str, '\n', buf+numRead-str) + 1;		/* search next LF	*/
	fprintf (fd2,"sw. %d to %d\t", test-buf, str-buf);
	#endif


/* ====================================================================	*/

long pmacRamGetY( char *, long *   );
long pmacRamGetL( char *, double * );
long pmacRamGetD( char *, double * );
long pmacRamGetF( char *, double * );
long pmacRamGetP( char *, long * );

/* ====================================================================	*/


long pmacRamGetY( char *buf, long *val )
{
  short ram0;
  short ram1;
  long  val0;

  ram0 = (buf[0]<<8) + (buf[1] & 0xFF);
  ram1 = (buf[2]<<8) + (buf[3] & 0xFF);

/*
  printf("ram0 = 0x%x  ram1 = 0x%x  ", ram0, ram1);
*/

  val0 = ((0x000000ff & (long) ram1) << 16) | (0x0000ffff & (long) ram0);

  *val = val0;

  return(0);
}

/* ====================================================================	*/


long pmacRamGetL( char *buf, double *pVal )
{
  short	   ram0;
  short	   ram1;
  short    ram2;
  short	   ram3;
  long	   val0;
  long	   val1;
  double   mantissa = 0.0;
  long int exponent = 0;
  double   valD;

  ram0 = (buf[0]<<8) + (buf[1] & 0xFF);
  ram1 = buf[3];
  ram2 = (buf[4]<<8) + (buf[5] & 0xFF);
  ram3 = buf[7]; 

/*
  printf("ram0 = 0x%x, ram1 = 0x%x, ram2 = 0x%x, ram3 = 0x%x  ", 
          ram0, ram1, ram2, ram3);
*/
	
  /* Convert 48 bit floating point format */

  val0     = (((long) ram1) << 16) | (0x0000ffff & (long) ram0);
  val1     = (((long) ram3) << 16) | (0x0000ffff & (long) ram2);
  mantissa = ((double) val1) * 4096.0 + (double) ((val0 >> 12) & 0x00000fff);
  exponent = (val0 & 0x00000fff) - 2082;  /* 0x7ff + 35 */
	
  if(mantissa == 0.0)
    valD = 0.0;
  else
    valD = mantissa * pow(2.0, (double) exponent);

  /* Return value */

  *pVal = valD;

  return(0);
}


/* ====================================================================	*/

long pmacRamGetD( char *buf,  double *pVal )
{
  short  ram0;
  short  ram1;
  short  ram2;
  short  ram3;
  long   val0;
  long   val1;
  double valD;

  ram0 = (buf[0]<<8) + (buf[1] & 0xFF);
  ram1 = buf[3];
  ram2 = (buf[4]<<8) + (buf[5] & 0xFF);
  ram3 = buf[7];
	
/*
  printf("ram0 = 0x%x, ram1 = 0x%x, ram2 = 0x%x, ram3 = 0x%x\n", 
          ram0, ram1, ram2, ram3);
*/

  /* Convert 48 bit fixed-point format */

  val0 = ((0x000000ff & (long) ram1) << 16) | (0x0000ffff & (long) ram0);
  val1 =              (((long) ram3) << 16) | (0x0000ffff & (long) ram2);
  valD = (double) val1 * 16777216.0 + (double) val0;

  *pVal = valD;

  return(0);
}


/* ====================================================================	*/

long pmacRamGetF( char *buf, double *pVal )
{
  short  ram0;
  short  ram1;
  double valD;
  union
  {
    long  val0;		
    float valF;
  }valU;

  ram0 = (buf[0]<<8) + (buf[1] & 0xFF);
  ram1 = (buf[4]<<8) + (buf[5] & 0xFF);

/*
  printf("pmacRamGetF: ram0 = 0x%x, buf[0] = 0x%x, buf[1] = 0x%x, buf[2] = 0x%x, buf[3] = 0x%x, buf[4] = 0x%x, buf[5] = 0x%x, buf[6] = 0x%x, buf[7] = 0x%x\n", ram0, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
*/

  /* Convert 32 bit floating point format */
  valU.val0 = (((long)ram1) << 16) | (0x0000ffff & (long)ram0);
  valD      = (double) valU.valF;
	
  /* Return value */
  *pVal = valD;

  return(0);
}


/* ====================================================================	*/

long pmacRamGetP( char *buf, long *pVal )
{
  short ram0;
  short ram1;
  long  val0;

  /* Read PMAC DPRAM */

  ram0 = (buf[0]<<8) + (buf[1] & 0xFF);
  ram1 = (buf[4]<<8) + (buf[5] & 0xFF);

/*
  printf("pmacRamGetP: buf[0] = 0x%x, buf[1] = 0x%x, buf[2] = 0x%x, buf[3] = 0x%x, buf[4] = 0x%x, buf[5] = 0x%x, buf[6] = 0x%x, buf[7] = 0x%x\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
  printf("pmacRamGetP: ram0 = 0x%x, ram1 = 0x%x\n", ram0, ram1);
*/

  /* Convert 32 bit fixed-point format */
  val0 = (((long) ram1) << 16) | (0x0000ffff & (long) ram0);
	
  /* Return value */
  *pVal = val0;

  return (0);
}

/* ====================================================================	*/

/* ====================================================================	*/
