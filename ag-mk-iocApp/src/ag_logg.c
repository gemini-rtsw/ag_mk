/*
 *  FILENAME
 *  --------
 *  ag_logg.c
 *
 *  PURPOSE
 *  -------
 *  This file contains the source for all functions used
 *  in the A&G unit for logging
 *
 *  FUNCTION NAME(S)
 *  ----------------
 *
 *  AUTHOR
 *  ------
 *  Olaf Frischmuth (ocf)
 *
 *  HISTORY
 *  -------
 *  25-Apr-1998:	Original version			(ocf)
 *
 */

#include  <ag_define.h>

/* Attention! index seems to be predefined Keyword! Don't transfer as variable to Sub programs!
 * Note: CADlogg (ag_cad2.c) calls flushlogfile and prepare_log for preparations !
 */

/* ===================================================================== */

#define LOGBUFSIZE	(200*1024)
#define LOGSRCCNT	200
#define NRLOGSYS	2			/* we have 2 log systems now	*/
#define MAXLOGSET	30

/* ===================================================================== */
/* globals	*/

struct logsource   	logsrcs[NRLOGSYS];	

/* ===================================================================== */

#define WRITTEN		1
#define OPENERR		-1
#define CASEERR		-100

#define FLUSH_TOP	1
#define FLUSH_BOT	2
#define WRITE_TOP	3
#define WRITE_BOT	4

#define WRTYPESTRS(wrtyp)  (	wrtyp == FLUSH_TOP ? "FLUSH_TOP" :	\
				wrtyp == FLUSH_BOT ? "FLUSH_BOT" :	\
				wrtyp == WRITE_TOP ? "WRITE_TOP" :	\
				wrtyp == WRITE_BOT ? "WRITE_BOT" : "UNDEF" )

/* different logsets	*/
#define LOGSET0		0
#define P1_ENG		1
#define P2_ENG		2
#define P1_REAL		3
#define P2_REAL		4
#define P1_DEM		5					
#define P2_DEM		6					
#define P1_OFS		7					/* probe offsets*/
#define P2_OFS		8		
#define SF_ENG		9					/* incl. AO/HW	*/

/* ====================================================================	*/

struct logfiletaskargs {
	char *filename;
	char *mode;
	struct logsource *logsrc;
	int wrtype;
};

/* ====================================================================	*/

char * logsetname (int i)
{
  switch (i)
  {
    case LOGSET0:	return "tracktest";	break; 	/* empty dummy */
    case P1_ENG:	return "P1_ENG";	break;
    case P2_ENG:	return "P2_ENG";	break;
    case P1_REAL:	return "P1_REAL";	break;
    case P2_REAL:	return "P2_REAL";	break;
    case P1_DEM:	return "P1_DEM";	break;
    case P2_DEM:	return "P2_DEM";	break;
    case P1_OFS:	return "P1_OFS";	break;
    case P2_OFS:	return "P2_OFS";	break;
    case SF_ENG:	return "SF_ENG";	break;
    default:		return "\0";		break;
  }
}
/* ====================================================================	*/
/* ====================================================================	*/
/* types to be logged:				param	data	length
 * 'T':		Time from timeNow		/	DOUBLE	8 bytes
 * 't':		Time from Bancomm		/	DOUBLE	8 bytes
 * 'A':		actual pos.[0]			mech.	LONG	4 bytes  
 * 'L':		free definable VME addr		addr	LONG	4 bytes
 * 'D':		free definable VME addr		addr	DOUBLE	8 bytes
 * 'R':		last function's returnvalue	/	LONG	4 bytes
 * 'S':		string				addr	chars	x bytes
 * 'G':		gensub.G[param] array value	index	DOUBLE	8 bytes	 (P1_OFFSETS)
 * 'H':		gensub.H[param] array value	index	DOUBLE	8 bytes	 (P2_OFFSETS)
 * 'I':		gensub.I[param] array value	index	DOUBLE	8 bytes	 (P1_DEMANDS)
 * 'J':		gensub.J[param] array value	index	DOUBLE	8 bytes	 (P2_DEMANDS)
 * 'X':		recalculated real pos.		mech.	DOUBLE	8 bytes	 ( based on eng. pos. + scale/offset)
 * 'x':		recalculated x/y probe pos.	mech.	DOUBLE	8 bytes
 * 'd':		free definable PMAC addr	addr,pm	LONG	4 bytes	 (DP)
 * 'l':		free definable PMAC addr	addr,pm	LONG	4 bytes  (16 bit source)
 *
 */

long prepare_log (char * filename, int logset, struct logsource *Plogsrc)
{
  Plogsrc->logbufpos	= 0;
  Plogsrc->logbufendpos	= 0;
  Plogsrc->logset 	= logset;
  Plogsrc->srccount	= 0;
  Plogsrc->types [0]   	= '\0';
  Plogsrc->header[0]   	= '\0';

  switch (logset)
  {
    case LOGSET0:	/* 0 / dummy	*/
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, TrEPsam+0*0x10000,	'l', "TrEPsam");	/* Pmac 1	*/
	writelogsrc (Plogsrc, TrPMsam+0*0x10000,	'l', "TrPMsam");	/* Pmac 1	*/
	writelogsrc (Plogsrc, TrPMerr+0*0x10000,	'l', "TrPMerr");	/* Pmac 1	*/
	writelogsrc (Plogsrc, TrEPtab+0*0x10000,	'l', "TrEPtab");	/* Pmac 1	*/
	/* writelogsrc (Plogsrc, (long)&"Tracking Handshake",	'S', "Comment");	*/
	break;
    case P1_ENG:	/* 1 */
	writelogsrc (Plogsrc, 0,	'T', "VxTime");		/* Vx - Time	*/
	writelogsrc (Plogsrc, 0,	'R', "retval");		/* retval Time	*/
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, 0,	'R', "retval");		/* retval Time	*/
	writelogsrc (Plogsrc, p1_RT4,	'A', "RT4eng");		/* act.pos. RT	*/
	writelogsrc (Plogsrc, p1_PA4,	'A', "PA4eng");		/* act.pos. PA	*/
	writelogsrc (Plogsrc, p1_focus,	'A', "foc4eng");	/* act.pos. Foc	*/
	break;
    case P2_ENG:	/* 2 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, p2_RT3,	'A', "RT3eng");		/* act.pos. RT	*/
	writelogsrc (Plogsrc, p2_PA3,	'A', "PA3eng");		/* act.pos. PA	*/
	writelogsrc (Plogsrc, p2_focus,	'A', "foc3eng");	/* act.pos. Foc	*/
	break;
    case P1_REAL:	/* 3 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, p1_RT4,	'X', "RT4real");	/* real pos.	*/
	writelogsrc (Plogsrc, p1_PA4,	'X', "PA4real");	/* real pos.	*/
	writelogsrc (Plogsrc, p1_focus,	'X', "foc4real");	/* real pos.	*/
	writelogsrc (Plogsrc, p1_probe,	'x', "probex/y");	/* xy   pos.-2D	*/
	break;							/* not nec.for c*/ 
    case P2_REAL:	/* 4 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, p2_RT3,	'X', "RT3real");	/* real pos.	*/
	writelogsrc (Plogsrc, p2_PA3,	'X', "PA3real");	/* real pos.	*/
	writelogsrc (Plogsrc, p2_focus,	'X', "foc3real");	/* real pos.	*/
	writelogsrc (Plogsrc, p2_probe,	'x', "probex/y");	/* xy   pos.-2D	*/
	writelogsrc (Plogsrc, (long)&"Reals of PWFS2",	'S', "Comment");
	break;
    case P1_DEM:	/* 5 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, 0,	'I', "20Hz1[0]");	/* 20Hz dem[0]	*/
	writelogsrc (Plogsrc, 1,	'I', "20Hz1[1]");	/* 20Hz dem[1]	*/
	writelogsrc (Plogsrc, 2,	'I', "20Hz1[2]");	/* 20Hz dem[2]	*/
	writelogsrc (Plogsrc, 3,	'I', "20Hz1[3]");	/* 20Hz dem[3]	*/
	writelogsrc (Plogsrc, 4,	'I', "20Hz1[4]");	/* 20Hz dem[4]	*/
	writelogsrc (Plogsrc, 5,	'I', "20Hz1[5]");	/* 20Hz dem[5]	*/
	writelogsrc (Plogsrc, (long)&"Demands of PWFS1",	'S', "Comment");
	break;
   case P2_DEM:		/* 6 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, 0,	'J', "20Hz2[0]");	/* 20Hz dem[0]	*/
	writelogsrc (Plogsrc, 1,	'J', "20Hz2[1]");	/* 20Hz dem[1]	*/
	writelogsrc (Plogsrc, 2,	'J', "20Hz2[2]");	/* 20Hz dem[2]	*/
	writelogsrc (Plogsrc, 3,	'J', "20Hz2[3]");	/* 20Hz dem[3]	*/
	writelogsrc (Plogsrc, 4,	'J', "20Hz2[4]");	/* 20Hz dem[4]	*/
	writelogsrc (Plogsrc, 5,	'J', "20Hz2[5]");	/* 20Hz dem[5]	*/
	writelogsrc (Plogsrc, (long)&"Demands of PWFS2",	'S', "Comment");
	break;
   case P1_OFS:		/* 7 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, 0,	'G', "Ofs1[0]");	/* offset[0]	*/
	writelogsrc (Plogsrc, 1,	'G', "Ofs1[1]");	/* offset[1]	*/
	writelogsrc (Plogsrc, 2,	'G', "Ofs1[2]");	/* offset[2]	*/
	writelogsrc (Plogsrc, 3,	'G', "Ofs1[3]");	/* offset[3]	*/
	writelogsrc (Plogsrc, 4,	'G', "Ofs1[4]");	/* offset[4]	*/
	writelogsrc (Plogsrc, 5,	'G', "Ofs1[5]");	/* offset[5]	*/
	writelogsrc (Plogsrc, 6,	'G', "Ofs1[6]");	/* offset[6]	*/
	writelogsrc (Plogsrc, 7,	'G', "Ofs1[7]");	/* offset[7]	*/
	writelogsrc (Plogsrc, 8,	'G', "Ofs1[8]");	/* offset[8]	*/
	break;
   case P2_OFS:		/* 8 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, 0,	'H', "Ofs2[0]");	/* offset[0]	*/
	writelogsrc (Plogsrc, 1,	'H', "Ofs2[1]");	/* offset[1]	*/
	writelogsrc (Plogsrc, 2,	'H', "Ofs2[2]");	/* offset[2]	*/
	writelogsrc (Plogsrc, 3,	'H', "Ofs2[3]");	/* offset[3]	*/
	writelogsrc (Plogsrc, 4,	'H', "Ofs2[4]");	/* offset[4]	*/
	writelogsrc (Plogsrc, 5,	'H', "Ofs2[5]");	/* offset[5]	*/
	writelogsrc (Plogsrc, 6,	'H', "Ofs2[6]");	/* offset[6]	*/
	writelogsrc (Plogsrc, 7,	'H', "Ofs2[7]");	/* offset[7]	*/
	writelogsrc (Plogsrc, 8,	'H', "Ofs2[8]");	/* offset[8]	*/
	break;
    case SF_ENG:	/* 9 */
	writelogsrc (Plogsrc, 0,	't', "BcTime");		/* Bc - Time	*/
	writelogsrc (Plogsrc, ag_RT2,	'A', "RT2eng");		/* act.pos.	*/
	writelogsrc (Plogsrc, ag_Tilt,	'A', "SFeng");		/* act.pos.	*/
	writelogsrc (Plogsrc, ag_Lin2,	'A', "Lin2eng");	/* act.pos.	*/
	writelogsrc (Plogsrc, ag_PA3AO,	'A', "PA3AOeng");	/* act.pos.	*/
	writelogsrc (Plogsrc, ag_hw,	'A', "hweng");		/* act.pos.	*/
	break;
  }

  sprintf ((char*)Plogsrc->logbuf, "\n A&G logset=%d, file=%s, types=%s, names=%s\n\n", 
		logset, filename, Plogsrc->types, Plogsrc->header);

  Plogsrc->logbufpos += strlen ((char*)(Plogsrc->logbuf + Plogsrc->logbufpos));

  return (0);
}

/* ====================================================================	*/
long init_logglobs (void)
{
  int i, j;  

  for (j=0; j<2; j++)
    for (i=0; i<MAXLOGSET; i++)
      if (logsetname(i)[0] != 0 )
        strncpy (logmenustrs [j][i], logsetname(i), MENUSTRSIZE);
      else { logmenustrs [j][i][0] = 0; /* break; */ }

  return (0);
}

/* ====================================================================	*/
long flushlogfile (char* filename, char* mode, struct logsource *Plogsrc)
{
  return (writelogfile (filename, mode, Plogsrc, LOGBUFSIZE+1));
}

/* ====================================================================	*/
/* ====================================================================	*/
/** Writes the maximum-reduced Infos about Log-Source (address, type, how to read..)
 **   to the structure.
 ** Process of fetching the information has been made simpler/faster:
 **   getDPRam doesn't calculate address itself
 **   (everything is prepared; the "logger" just takes raw addresses)
 **/

#define IDX	logsrc->srccount

long writelogsrc (struct logsource *logsrc, long param, char type, char * header)
{
#if 0
  char   messages[80];		/* Message buffer */
  sprintf(messages, "writelogsrc called, cnt=%d, param = %d,\t type = %c, &src=%d \n", logsrc->srccount,  param, type, (long)logsrc);
   agprintf ( "%s", messages);
#endif

  switch (type)
  {
    case 'x':	logsrc->addr[IDX][1] = (long) pmac2hostaddr (getcard(param,2), 
		(FGDatBuff + FGMotOfs*(getplcn(param,2)-1) + ActPos), 0); 
		logsrc->type[IDX] = type;		/* no break!	*/
    case 'X':	
    case 'A':	logsrc->addr[IDX][0] = (long) pmac2hostaddr (getcard(param,1), 
		(FGDatBuff + FGMotOfs*(getplcn(param,1)-1) + ActPos), 0); 

		logsrc->type[IDX] = type;	
		logsrc->addr[IDX][2] = param;
		break;

    case 'd':	
    case 'l':	logsrc->addr[IDX][0] = (long) pmac2hostaddr (param>0x10000 ? 1:0, 
		(long)mod (param,0x10000), 0); 

		logsrc->type[IDX] = type;	
		break;

    case 'T':
    case 't':
    case 'R':	logsrc->addr[IDX][0] = 0;     logsrc->type[IDX] = type;	
		break;

    case 'S':
    case 'L':
    case 'D':
    default:	logsrc->addr[IDX][0] = param; logsrc->type[IDX] = type;	
		break;
  }

  switch (type)
  {
    case 'T':
    case 't':	strcat (logsrc->types, "T");				break;

    case 'S':	strcat (logsrc->types, "S");				break;

    case 'l':
    case 'd':
    case 'A':
    case 'L':
    case 'R':	strcat (logsrc->types, "L");				break;

    case 'D':
    case 'X':
    case 'G':
    case 'H':
    case 'I':
    case 'J':	strcat (logsrc->types, "D");				break;

    case 'x':	strcat (logsrc->types, "DD");				break;
  }

  strcat (logsrc->header, header); 
  strcat (logsrc->header, "\t"); 
  logsrc->srccount++;

  return (0);
}

/* ====================================================================	*/
#define P1P2MARK	(*(double*)pgsub->e)		/* am I p1 or p2? */
#define logindex	((P1P2MARK == 1) ? 0 : 1)

/* a:	filename			string
 * b:	start time in Unix sec		double
 * c:	end   time in Unix sec		double
 * e:	
 * SCAN: frequency of read		enum
 *
 * vala: act. sample			long
 * valb: flag=0: just stopped.		long
 * valc: actual relative time to start	double
 * vald: actual absolute time		double
 */

long logging ( struct genSubRecord *pgsub )
{
#if EXTRADEBUG
  char messages[80];						/* Message buffer	*/
#endif

  int  retval;
  double t;
  struct  logsource * Plogsrcs;

  bc635_read (&t);
  Plogsrcs = &(logsrcs[logindex]);

  if (t >= *(double*)pgsub->b && t <= *(double*)pgsub->c)	/* start < t < end ?	*/
  {
      *(long  *)pgsub->vala += 1;
      *(long  *)pgsub->valb  = 1;
      *(double*)pgsub->valc  = t - *(double*)pgsub->b;
      *(double*)pgsub->vald  = t;


      Plogsrcs->oldlogbufpos = Plogsrcs->logbufpos;

      writelogbuf (pgsub, Plogsrcs);

      if ((retval = writelogfile( (char *) pgsub->a, "a", 
		Plogsrcs, Plogsrcs->oldlogbufpos) ))
      { 
	#if EXTRADEBUG
        if (retval == WRITTEN)
          	sprintf(messages, "\t%s\t- file \"%s\" 'written' returned, m=%d", 
				pgsub->name, (char*)pgsub->a, (long)P1P2MARK);     
        else	sprintf(messages, "\t%s\t- cannot open file \"%s\"", 	 
				pgsub->name, (char*)pgsub->a); 
        agLogMessage( ag_cc, DEB_FULL, messages);
	#endif
      }
  }
  else
  {
    if (*(long*)pgsub->valb == 1)
    {   *(long*)pgsub->valb  = 0;

      if ((retval = flushlogfile( (char *) pgsub->a, "a", Plogsrcs) ))
      { 
	#if EXTRADEBUG
        if (retval == WRITTEN)
          	sprintf(messages, "\t%s\t- file \"%s\" 'flushed' returned, m=%d", 	
			pgsub->name, (char*)pgsub->a, (long)P1P2MARK);     
        else	sprintf(messages, "\t%s\t- cannot open file \"%s\"", 		
			pgsub->name, (char*)pgsub->a); 
        agLogMessage( ag_cc, DEB_FULL, messages);
	#endif
      }
    }
  }

  #if EXTRADEBUG
  if (pgsub->scan <= SCAN1s) 
  {
    sprintf(messages, "%s - called, sam=%d, pos=%d, t=%f", 
		pgsub->name, *(long*)pgsub->vala, Plogsrcs->logbufpos, t); 
    agLogMessage( ag_cc, DEB_FULL, messages);
  }
  #endif

  return (0);
}

/** to do: 
 **   Message/CAR/health, if duration is over or file system full
 **   stop logging on file system full
 **/

/* ====================================================================	*/
/** After Overwriting the buffer's half or after Pointer-Reset:
 **  Filewriting will be triggere in the calling program (via task)
 **
 ** subroutine to "logging" gensub
 **/
#define POS		(Plogsrc->logbuf + Plogsrc->logbufpos)	
#define P1P2MARK	(*(double*)pgsub->e)		/* am I p1 or p2? */

long writelogbuf (struct genSubRecord *pgsub, struct logsource *Plogsrc)
{  
  double t, t2;
  int  samplesize;
  int  i, mechindex, ori[2];

  mechindex = (P1P2MARK == 1) ? p1_probe : p2_probe;

  Plogsrc->oldlogbufpos = Plogsrc->logbufpos;

  for (i=0; i<Plogsrc->srccount; i++)
  {
    switch ((Plogsrc->type)[i])
    {
      case 'T': Plogsrc->logretval = get_tai (&t);  
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;

      case 't': Plogsrc->logretval = bc635_read (&t);  
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;

      case 'R': *(long*)POS = Plogsrc->logretval;			/* last error	*/
		Plogsrc->logbufpos += sizeof(long); break;

      case 'S': Plogsrc->logbufpos = movestring ( Plogsrc->logbuf, (Plogsrc->logbuf+Plogsrc->logbufpos), 
			  Plogsrc->logbuf+LOGBUFSIZE-1, (char *)((Plogsrc->addr)[i][0]), 200) 
			- Plogsrc->logbuf;	break;			/* * string 	*/

      case 'G': t = ((double*)pgsub->g)[lim((Plogsrc->addr)[i][0], 0, 5)];  
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;
      case 'H': t = ((double*)pgsub->h)[lim((Plogsrc->addr)[i][0], 0, 5)];  
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;
      case 'I': t = ((double*)pgsub->i)[lim((Plogsrc->addr)[i][0], 0, 5)];  
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;
      case 'J': t = ((double*)pgsub->j)[lim((Plogsrc->addr)[i][0], 0, 5)];  
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;

      case 'A': if (getsimu (mechindex) == SIM_NONE)
		  getDPRamD2raw ((Plogsrc->addr)[i][0], &t);
		*(long*)POS = (long)t;  Plogsrc->logbufpos += sizeof(long); break;

      case 'X': mechindex = lim ((Plogsrc->addr) [i][2], 0, MAX_MECH_INDEX);
		if (getsimu (mechindex) == SIM_NONE)
		  getDPRamD2raw   ((Plogsrc->addr) [i][0], &t);
		t = eng2real (Scale[mechindex] [0], Offset[mechindex][0], (long)t); 
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double); break;

      case 'x': mechindex = lim ((Plogsrc->addr) [i][2], 0, MAX_MECH_INDEX);
		if (getsimu (mechindex) == SIM_NONE)
		{
		  getDPRamD2raw   ((Plogsrc->addr) [i][0], &t);
		  getDPRamD2raw   ((Plogsrc->addr) [i][1], &t2);
		}
		t = eng2real (Scale[mechindex] [0], Offset[mechindex] [0], 
                              (long)t); 
		t2= eng2real (Scale[mechindex] [1], Offset[mechindex] [1], 
                              (long)t2);
                agAb2xy (mechindex, t, t2, ForPar[mechindex], ori, &t, &t2) ;
		*(double*)POS = t;  Plogsrc->logbufpos += sizeof(double);
		*(double*)POS = t2; Plogsrc->logbufpos += sizeof(double); break;

      case 'd':
      case 'l':
		if (getsimu (mechindex) == SIM_NONE)
		  *(long*)POS = getDPRamraw   ((Plogsrc->addr) [i][0]);
		Plogsrc->logbufpos += sizeof(long); break;

      case 'L': if (getsimu (mechindex) == SIM_NONE)
		  *(long*)POS = *(long*)((Plogsrc->addr) [i][0]);	/* free def.long*/
		Plogsrc->logbufpos += sizeof(long); break;

      case 'D': if (getsimu (mechindex) == SIM_NONE)
		  *(double*)POS = *(double*)((Plogsrc->addr) [i][0]);	/* free def.DBL	*/
		Plogsrc->logbufpos += sizeof(double); break;
    }
  }

  *(char*)POS = '\n';  Plogsrc->logbufpos += sizeof(char);   /* append \n to each sample	*/

  samplesize = (Plogsrc->logbufpos) - (Plogsrc->oldlogbufpos);

  if (Plogsrc->logbufpos > (LOGBUFSIZE - samplesize))
  {   Plogsrc->logbufendpos = Plogsrc->logbufpos;	/* store fillpoint */
      Plogsrc->logbufpos = 0;				/* reset pointer   */
  }

  return (0);
}

/* ====================================================================	*/
/* After writing the file: search the file first for "\n", then the area before "\n" for "=".
 ** The char after "=" decides about formatting as Long, Double or String.
 **
 ** For necessary resynchr.: Every sample sends in "\n".
 **   After each found sample we look first for the next "\n".
 **   If it's no immediately after the sample,we note an error.
 **
 ** In case the reserved words "\nA&G logset" are found 
 **   (we look for this after each sample for a short distance),
 **   a new file structur is read in and used. 
 **
 ** A file which is constructed from different logsets can also be separated by 
 ** hand prior to interpretation.
 **
 ** To distinct it from the uninterpreted, raw data file,
 **   an interpreted file always get the addtional ending ".asc" or ".txt".
 **/

/* ====================================================================	*/
long logfiletask (struct logfiletaskargs *args)
{
  char *filename           = args->filename;
  char *mode               = args->mode;
  struct logsource *logsrc = args->logsrc;
  int wrtype               = args->wrtype;

  logsrc->taskretval = WRITTEN;

  if ((logsrc->stream = fopen(filename, mode)) != NULL)
    switch (wrtype)
    {
      case FLUSH_TOP: fwrite((logsrc->logbuf)+(LOGBUFSIZE>>1), 1, (logsrc->logbufpos)   - (LOGBUFSIZE>>1), logsrc->stream ); break;
      case FLUSH_BOT: fwrite( logsrc->logbuf		     , 1,  logsrc->logbufpos			 , logsrc->stream ); break;
      case WRITE_TOP: fwrite((logsrc->logbuf)+(LOGBUFSIZE>>1), 1, (logsrc->logbufendpos)- (LOGBUFSIZE>>1), logsrc->stream ); break;
      case WRITE_BOT: fwrite( logsrc->logbuf		     , 1,  LOGBUFSIZE>>1		 	 , logsrc->stream ); break;
      default: 	      logsrc->taskretval = CASEERR;									     break;
    }
  else logsrc->taskretval = OPENERR;

  fclose (logsrc->stream);

  #if EXTRADEBUG
  if (logsrc->taskretval == WRITTEN)
        sprintf(logsrc->logmsgbuf, "\t%s\t- file \"%s\" written (%s). ", "logfiletask", filename, WRTYPESTRS(wrtype));     
  else	sprintf(logsrc->logmsgbuf, "\t%s\t- cannot open file \"%s\"",    "logfiletask", filename); 
  agLogMessage( ag_cc, DEB_FULL, logsrc->logmsgbuf);
  #endif

  // Make sure to deallocate the memory taken to keep the arguments
  free(args->filename);
  free(args);

  return (logsrc->taskretval);
}

/* ====================================================================	*/

long writelogfile (char* filename, char* mode, struct logsource *logsrc,
                   int oldlogbufpos)
{
  int  retval = 0;
  struct logfiletaskargs *args;
  char taskname[30];
#if EXTRADEBUG
  char messages[80];
#endif
  int  wrtype;
  epicsThreadId taskId;

  if (((logsrc->logbufpos >= LOGBUFSIZE>>1) && (oldlogbufpos < LOGBUFSIZE>>1)) ||
       (logsrc->logbufpos <  oldlogbufpos))		/* wrapped	 */
  {
    if (     logsrc->logbufpos < oldlogbufpos)		/* wrapped or flush! */
      if (        oldlogbufpos >= LOGBUFSIZE)		/* flush!            */
	if (logsrc->logbufpos  >= LOGBUFSIZE>>1)	/* flush (write) top */
		wrtype = FLUSH_TOP;
	else	wrtype = FLUSH_BOT;		/* flush (write) bottom	*/
      else	wrtype = WRITE_TOP;		/* wrapped to bottom, write top	*/          
    else	wrtype = WRITE_BOT;		/* half filled, write bottom */

    sprintf (taskname, "write_%s", filename);

    args = (struct logfiletaskargs*)malloc(sizeof(struct logfiletaskargs));
    if (!args) {
	    fputs("writelogfile: Can't initialize args struct to create a logfiletask thread!", stderr);
	    return retval;
    }
    args->filename = strdup(filename);
    args->mode = mode;
    args->logsrc = logsrc;
    args->wrtype = wrtype;

    taskId = epicsThreadMustCreate(
		    taskname,
		    priorityLow, // In vxWorks this was 75, and they intend it as a background task
		    epicsThreadGetStackSize(epicsThreadStackSmall),
		    (EPICSTHREADFUNC)logfiletask,
		    args);


    retval = WRITTEN;

    #if EXTRADEBUG
    sprintf (messages, "\t%s\t- %s \"%s\" commanded, task=%d", "writelogfile", WRTYPESTRS(wrtype), filename, taskId);
    agLogMessage( ag_cc, DEB_FULL, messages);
    #endif
  }
  return (retval);
}

/* ====================================================================	*/
/* ====================================================================	*/

long testlog (int system)
{
  char   messages[380];		/* Message buffer */
  int i;

  if (system != 1) system = 0;

  sprintf( messages, "count = %d, logset= %d, retval= %ld\n", logsrcs[system].srccount, 
			     logsrcs[system].logset, logsrcs[system].logretval);
  agprintf ( "%s", messages );
  sprintf( messages, "header= %s, types = %s\n", logsrcs[system].header, logsrcs[system].types);
  agprintf ( "%s", messages );

  for (i=0; i<logsrcs[system].srccount; i++)
  {
    sprintf(messages, "addr0= %#10x, addr1= %#10x, addr2= %2ld (%s), \t type=%2c \n", 
	(unsigned int) logsrcs[system].addr[i][0], (unsigned int) logsrcs[system].addr[i][1], logsrcs[system].addr[i][2], 
	((logsrcs[system].addr[i][2]<MAX_INDEX-1) ? mechstrs[logsrcs[system].addr[i][2]] : 
	">MAX_INDEX!"), logsrcs[system].type[i]);
    agprintf ( "%s", messages);
    if  (logsrcs[system].type[i] == 'S')
      agprintf ("String = \"%s\"\n", ((char*)(logsrcs[system].addr[i][0])));
  }

  return (0);
}
/*
      agprintf ("%s", globstr);
      sprintf(globstr, "was changed just now\n");
      agprintf ("%s", globstr);
      agprintf ("       globstr = '%s' \n",  globstr);
      agprintf (" (long)globstr = %d (%x) \n", (long)globstr, (long)globstr);
      agprintf ("      &globstr = %d (%x) \n", (long)&globstr, (long)&globstr);
*/
/* ====================================================================	*/
epicsRegisterFunction(logging);

static const iocshArg *agInitLogglobsArgs[] = { NULL };
static const iocshFuncDef agInitLogglobsFuncDef = 
         {"init_logglobs", 0, agInitLogglobsArgs};
static void agInitLogglobsCallFunc(const iocshArgBuf *args)
{
   init_logglobs();
}

static void agRegisterInitLogglobsCommands(void)
{
   static int firstTime = 1;
   if(firstTime) {
      iocshRegister(&agInitLogglobsFuncDef, agInitLogglobsCallFunc);
   }
}
epicsExportRegistrar(agRegisterInitLogglobsCommands);

