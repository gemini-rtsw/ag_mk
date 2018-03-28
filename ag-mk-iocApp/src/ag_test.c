
#include  <ag_define.h>
/* #include  <usrLib.h> */
/* #include  <dbgLib.h> */

extern PMAC_LOCAL long pmacRamGetD
(
	PMAC_DPRAM *	pDpram,
	double *	pVal
);

void writeMbox (long card, char *str)
{

 char response[MAX_STRING_SIZE];
 char errmsg[MAX_STRING_SIZE];
 long terminator ;

 if (card < 0 || card > 1) {
   printf ("Card must be 0 or 1\n");
   return ;
 } else {
   terminator = drvPmacMbxWriteRead (card, str, response, errmsg);
   if (errmsg[0]) {
     printf ("Write failed: response was %s\n", errmsg);
   } else {
     printf ("Write succeeded: response was %s\n", response);
   }
 }

}

/* ====================================================================	*/

long getaddr (long card, long pmacaddr)
{

  return ((long) pmac2hostaddr(card,pmacaddr,0));

  /*
printf ("\n==== show (Id,1); __

  return (0);
*/
}
/* ====================================================================	*/

  #define CNTFAC		3072				/* (32*96) */

/* ====================================================================	*/
long getall (void)
{
  char messages[180];     		/* Message buffer */
  int i;
  double current[3], target[3], demand[3];
  double pos[11];
  long addr;


  for (i=0; i<MAX_INDEX; i++)
  {
    addr = getaddr (getcard(i,0 ),FGDatBuff+ActPos+ getplcn(i,0)*FGMotOfs);
    getpos (i, current, target, demand);
    getDPRamD2    (FGDatBuff+ActPos+ getplcn(i,0)*FGMotOfs,  getcard(i,0), 0, &(pos[0]));
    getDPRamD2raw (addr, &(pos[1]));
    pmacRamGetD	((PMAC_DPRAM *)addr, &(pos[2]));	
    pos[2]/=CNTFAC;

    sprintf (messages, "mi:%2d plc:%2ld/%1ld, sw:%5lx, resp:%5ld, pos=%f, (add=%5lx) = %5f/%5f/%5f \n",
	i, getplcn(i, 0), getcard(i, 0), getswitch(i), getresponse(i,0), current[0], addr, pos[0],pos[1],pos[2]);
    printf (messages);
  }

  return 0;
}

/* ====================================================================	*/
long getstr (void)
{
  char messages[80];     		/* Message buffer */
  int i;

  for (i=0; i<MAX_INDEX; i++)
  {
    sprintf (messages, "mi:%2d plc:%2ld/%1ld, mech=%s\n",
	i, getplcn(i, 0), getcard(i, 0), mechstrs[i]);
    printf (messages);
  }

  return 0;
}

/* ====================================================================	*/

long getmenustr (void)
{
  char messages[80];     		/* Message buffer */
  int i, j;

  for (i=0; i<MAX_INDEX; i++)
  {
    sprintf (messages, "\tmi:%2d plc:%2ld/%1ld, mech=%s\n",
	i, getplcn(i, 0), getcard(i, 0), mechstrs[i]);
    printf (messages);

    for (j=0; j<MAXMENUSTR; j++)
    {
      sprintf (messages, "%2d: %s\n",j, menustrs[i][j]);
      printf  (messages);
    }
    for (j=0; j<MAX_LUTpcnt; j++)
    {
      sprintf (messages, "%2d: %s\n",j, LUTplus[i][j]);
      printf  (messages);
    }
  }

  return 0;
}

/* ====================================================================	*/

long getsw (void)
{
  char messages[80];     		/* Message buffer */
  int i;

  for (i=0; i<MAX_INDEX; i++)
  {
    sprintf (messages, "mi:%2d plc:%3ld, card:%2ld, glob:%5lx, sw:%5lx, resp:%5ld \n",
	i, getplcn(i, 0), getcard(i, 0), plcflag[i][0], getswitch(i), getresponse(i,0));
    printf (messages);
  }

  return 0;
}

/* ====================================================================	*/
/* ====================================================================	*/


long checktask (long Id, long Pc)
{
printf ("\n==== show (Id,1); ______________________________________________________________________\n\n");

  show (Id, 1);

printf ("\n==== lkAddr (Pc); ______________________________________________________________________\n\n");

  lkAddr (Pc);				/* find name to Address	*/
/*  i    (Id);
 *  ti   (Id);
*/  
printf ("\n==== checkStack (Id); ______________________________________________________________________\n\n");

   checkStack (Id);
/* checkStack ((long)"scan0.2000");
 */
printf ("\n===== (d) display mem (Pc-16) ______________________________________________________________________\n\n");

   d ((byte*) Pc - 0x10, 0x10, 2);

/*  pwd();	*/

printf ("\n===== disassemble mem (Pc-16): l (%x, 0x10) ______________________________________________________________________\n\n",
(unsigned int) Pc-0x08);

   l ( (INSTR *) Pc - 0x08, 0x10);


printf ("\n===== ti (Id); ______________________________________________________________________\n\n");

  ti (Id);

printf ("\n===== tt (Id); ______________________________________________________________________\n\n");

  tt (Id);

printf ("\n===== End of checktask ______________________________________________________________________\n\n");

  return (0);
}

/* ====================================================================	*/







/* ====================================================================	*/
long showstack (long addr)
{
int i;
 
printf ("Address %#x: values= ", (unsigned int) addr); 
for (i=0; i<10; i++) 
  printf ("%#x ", (unsigned int) *(long *) (addr - 4*i));
printf ("\n");

for (i=0; i<10; i++)
{
  printf ("StackAddress %#x: value = %#x = Pointer to: ", (unsigned int) addr-4*i, (unsigned int) *(long*)(addr-4*i)); 
  lkAddr (*(long*)(addr-4*i));			/* find name to Address	*/
  printf ("\n");
}

  return (0);
}

/* ====================================================================	*/

long testwrap (long testint)
{
  char messages[80];     		/* Message buffer */
  int i;

  for (i=-6; i<26; i++)
  {
    sprintf (messages, "i:%3d, wrap(20):%2d \n", i, wrapsam (i,20));
    printf  (messages);
  }

  sprintf (messages, "testint:%3ld, wrap(20):%2ld \n", testint, wrapsam (testint,20));
  printf  (messages);

  return 0;
}

/* ====================================================================	*/
/* lines for the vxworks shell:
ld < ./bin/mv167/ag_test
test_xyab
*/

#define PRINT										    \
  printf ("\n %7.1f, %7.1f ->\t %8.3f, %8.3f \t (%8.3f, %8.3f); %7.1f;\t %3s, %3s -> %3s, %3s", \
		x,y,x2,y2,al,be,RT,								\
		ORI_str(Ori[0]),ORI_str(Ori[1]),ORI_str(Ori2[0]),ORI_str(Ori2[1]));

#define CHECK                                             \
  agXy2ab (mechindex, new_track_id, x, y, Par, Lim, Ori, RT, &al, &be); \
  agAb2xy (mechindex, al, be, Par, Ori2, &x2, &y2 );      \
  PRINT;

long test_xyab (void)
{
  double  x2,y2,x,y,al,be,Par[7],Lim[6],RT;
  int	  Ori2[2], Ori[2], i;
  long mechindex ;
  long new_track_id = 0;

  al=0;				/* RT_Curr	*/
  mechindex = p1_probe ;

  printf ("\n Params: ");
  for   (i=0; i<7; i++)
  { Par [i] = ForPar [mechindex][i]; printf ("%6.1f,\t", Par[i]);
  }

  printf ("\n Limits: ");
  for   (i=0; i<6; i++)
  { Lim [i] = Limits [mechindex][i]; printf ("%6.1f,\t", Lim[i]);
  }
  printf ("\n RT/PA Orientations: CW=0, CCW=1, don't care=2\n");

/* _____________________________________________________________________*/

  x= 0;	   y= 0;  	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  printf ("\n");
  x= 300;  y= 300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-300;  y= 300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-300;  y=-300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x= 300;  y=-300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  printf ("\n");
  x= 100;  y= 100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-100;  y= 100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-100;  y=-100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x= 100;  y=-100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  printf ("\n");
  x= 100;  y= 300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-100;  y= 300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-100;  y=-300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x= 100;  y=-300;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  printf ("\n");
  x= 300;  y= 100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-300;  y= 100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x=-300;  y=-100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  x= 300;  y=-100;	Ori[0]=CWCCW;	Ori[1]=CWCCW;  RT=al; CHECK;
  printf ("\n");
  x= 100;  y= 100;	Ori[0]=CW;	Ori[1]=CW;	RT=0; CHECK;
  x= 100;  y= 100;	Ori[0]=CW;	Ori[1]=CCW;	RT=0; CHECK;
  x= 100;  y= 100;	Ori[0]=CCW;	Ori[1]=CW;	RT=0; CHECK;
  x= 100;  y= 100;	Ori[0]=CCW;	Ori[1]=CCW;	RT=0; CHECK;
  printf ("\n");
  x= 100;  y=-100;	Ori[0]=CW;	Ori[1]=CW;	RT=0; CHECK;
  x= 100;  y=-100;	Ori[0]=CW;	Ori[1]=CCW;	RT=0; CHECK;
  x= 100;  y=-100;	Ori[0]=CCW;	Ori[1]=CW;	RT=0; CHECK;
  x= 100;  y=-100;	Ori[0]=CCW;	Ori[1]=CCW;	RT=0; CHECK;

/* define a point in the overlap space (15/-200 or 50/-200) to test the RT orientation choice	*/
  printf ("\n");
  x= 50;  y=-200;	Ori[0]=CW;	Ori[1]=CW;	RT=0; CHECK;
  x= 50;  y=-200;	Ori[0]=CW;	Ori[1]=CCW;	RT=0; CHECK;
  x= 50;  y=-200;	Ori[0]=CCW;	Ori[1]=CW;	RT=0; CHECK;
  x= 50;  y=-200;	Ori[0]=CCW;	Ori[1]=CCW;	RT=0; CHECK;
  printf ("\n");
  x= 50;  y=-200;	Ori[0]=CW;	Ori[1]=CW;     RT=al; CHECK;
  x= 50;  y=-200;	Ori[0]=CW;	Ori[1]=CCW;    RT=al; CHECK;
  x= 50;  y=-200;	Ori[0]=CCW;	Ori[1]=CW;     RT=al; CHECK;
  x= 50;  y=-200;	Ori[0]=CCW;	Ori[1]=CCW;    RT=al; CHECK;

  printf ("\n");
  return 0;
}

/* ====================================================================	*/

