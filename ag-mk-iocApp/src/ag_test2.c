#include  <ag_define.h>		

int glsam;
#define TRANSFER_FILE_SIZE  512*1024  /* 0.5 MBytes */

/* char *buf; */
  char   buf[TRANSFER_FILE_SIZE];
/* ===================================================================== */

long testLanProc2( void )
{
  FILE          *fd;
  double        numSecs;
  double        transRate;
  unsigned long tickStart, tickEnd;
  unsigned long sysclk;
  char   messages[80];		/* Message buffer */

  int  len;
  int  pos;
  int  space;
  char tempBuf[64];

  pos = 0;
  for(;;)
  {
    sprintf(tempBuf, "Position in file of start of this line is: %d\n", pos);
    len   = strlen(tempBuf);
    pos  += len;
    space = TRANSFER_FILE_SIZE - pos - 1;
    if( space >= len )
      sprintf(buf+pos-len, "%s", tempBuf);
    else
      break;
  }

  fd        = fopen("adda", "w+");
  tickStart = tickGet();
  fwrite( buf, 1, TRANSFER_FILE_SIZE, fd);
  tickEnd   = tickGet();
  fclose(fd);

  sysclk = sysClkRateGet();

  numSecs   = ((double)(tickEnd - tickStart))/sysclk;
  transRate = TRANSFER_FILE_SIZE/(1024.0 * numSecs);

  sprintf(messages, "tickst=%ld, end=%ld, clk=%ld, sec=%6.3e, rate=%6.3e \n", tickStart, tickEnd, sysclk, numSecs, transRate); 
  printf ( messages);

  return (long)transRate;
}

/* ===================================================================== */
long writef (char * filename, char * mode)
{
  int    sam, ret;
  FILE  *stream;
  long   arr[500][5];
  char   messages[80];		/* Message buffer */

  for ( sam=0; sam < 500; sam++)
  {
  arr[sam][0] = 1;
  arr[sam][1] = 2;
  arr[sam][2] = 3;
  arr[sam][3] = 4;
  arr[sam][4] = sam;
  }

    if ((stream = fopen( filename, mode)) == NULL)
    {
      sprintf(messages, "cannot open file %s",filename); 
      printf ( messages);
    }
    else
    /*  for ( sam=0; sam < 50; sam++) */
        if ((ret = fprintf( stream, "Hallo, Zeile %d\n", sam)) <0)
        {
          sprintf(messages, "fprintf error %d",ret); 
	  printf( messages); 
/*          break;	*/			/* stop for loop	*/
        }

    fclose (stream);

  return (0);
}
/*
"%6.2f\t%6.2f\t%6.2f\t%6.2f\t%6.2f\t\n",	
	  (float)arr[sam][0], (float)arr[sam][1], (float)arr[sam][2], 	
	  (float)arr[sam][3], (float)arr[sam][4])) < 0)
*/


/* ===================================================================== */
/* ===================================================================== */
/** Stat LED at both CPUs lit or other crash:
 ** Array with 500 Doubles (2500=20 kB) gives access  error while writing just
 **   30*5 values at occupied memory or, also, 300*5 values without extra memory 
 **   occupation
 **   repeated calling with 201 Doubles sometimes doesn't work.
 ** Suddenly: repeated calling with 500 Doubles (after 200,201..)
 **   2500 Ints or Longs (10 kB) work, as 3*5 Doubles, as 200*5 Doubles when
 **   mem isn't very occupied
 **
 ** often occurs: (without crash): 
 **   memPartFree: invalid block 0xf81dac in partition 0x7b5b6. (both CPU)
 **   memPartFree: invalid block 0xf81164 in partition 0x7b5b6.	   "
 **
 **
 **/
long write0 (int max)
{
  volatile int    sam; 		/* doesn't change the erro	*/
  double arr[500][5];

  for ( sam=0; sam < max; sam++)
  {
  arr[sam][0] = 1.0;
  arr[sam][1] = 2.0;
  arr[sam][2] = 3.0;
  arr[sam][3] = 4.0;
  arr[sam][4] = 5.0;
  }
return (sam);
}
  double glarr[500][5];

/* ===================================================================== */
/* works til 500, not above 3000	
*/
 
long write0b (int max)
{
  volatile int    sam; 		/* doesn't change the error	*/

  for ( sam=0; sam < max; sam++)
  {
  glarr[sam][0] = 1.0;
  glarr[sam][1] = 2.0;
  glarr[sam][2] = 3.0;
  glarr[sam][3] = 4.0;
  glarr[sam][4] = 5.0;
  }
return (sam);
}

/* ===================================================================== */
/* works	*/
long write1 (int sam)
{
  double arr[5000][5];

  arr[sam][0] = 1.0;
  arr[sam][1] = 2.0;
  arr[sam][2] = 3.0;
  arr[sam][3] = 4.0;
  arr[sam][4] = 5.0;

return (sam);
}
/* ===================================================================== */
/* subprogramm - works	*/
long write2 (int max)
{
  int    sam;
/*  double arr[5000][5]; */

  for ( sam=0; sam < max; sam++)
    write1 (sam);
return (sam);
}

/* ===================================================================== */
/* global - works	*/
long write3 (int max)
{
  double arr[5000][5];

  for ( glsam=0; glsam < max; glsam++)
  {
  arr[glsam][0] = 1.0;
  arr[glsam][1] = 2.0;
  arr[glsam][2] = 3.0;
  arr[glsam][3] = 4.0;
  arr[glsam][4] = 5.0;
  }
return (glsam);
}

/* ===================================================================== */
/* works fine with up to 4500, but error again from 4990
 * at 4500 already 1* not 4500, but 20 returned
 * 4500 more than once doesn't work.
 */

long write4 (int max)
{
  volatile int    sam; 		/* doesn't change the error	*/
  unsigned char arr [5000 * 5 * 8];

  for ( sam=0; sam < max; sam++)
  {
  *(double*) &(arr [sam*5*8 + 0]) = 1.0;
  *(double*) &(arr [sam*5*8 + 1]) = 2.0;
  *(double*) &(arr [sam*5*8 + 2]) = 3.0;
  *(double*) &(arr [sam*5*8 + 3]) = 4.0;
  *(double*) &(arr [sam*5*8 + 4]) = 5.0;
  }
return (sam);
}
/* ===================================================================== */

