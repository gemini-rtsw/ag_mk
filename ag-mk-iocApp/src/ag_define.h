/*
 *  FILENAME
 *  --------
 *  ag_define.h
 *
 *  PURPOSE
 *  -------
 *  This file contains all definitions, function declarations a.s.o. 
 *  for the c files of the A&G unit.
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
 *  08-Dec-2000:        Remove all unnecessary declarations     (cjm)
 */

/* ===================================================================== */

#include  <epicsStdioRedirect.h>
#include  <registryFunction.h>
#include  <epicsExport.h>
#include  <epicsStdioRedirect.h>
#include  <epicsStdlib.h>
#include  <epicsEvent.h>
#include  <epicsPrint.h>
#include  <ctype.h>
#include  <math.h>
#include  <string.h>
#include  <time.h>
#include  <iocsh.h>
/* #include  <db_access.h> */
#include  <dbBase.h>
#include  <dbAddr.h>
#include  <recGbl.h>
#include  <shareLib.h>
#include  <dbFldTypes.h>
#include  <dbDefs.h>
#include  <dbAccessDefs.h>

#include  <unistd.h>

#include  <dbEvent.h>
#include  <dbDefs.h>
#include  <dbCommon.h>
#include  <recSup.h>
#include  <taskwd.h>

#include  <genSubRecord.h>
#include  <menuCarstates.h>
#include <subRecord.h>
#include  <cadRecord.h>
#include  <cad.h>
#include  <sirRecord.h>

#include  <cicsConst.h>
#include  <cicsLib.h>

#include  <slamac.h>
#include  <timesys.h>
#include  <bc635.h>
#include  <drvPmac.h>

/* ===================================================================== */
/* The following are compiler switches used in different a&G files to control
 *  additional debug messages for testing.
 */
#define	 	EXTRADEBUG	0

/* ===================================================================== */

#define MENUSTRSIZE	20

#define LOGBUFSIZE	(200*1024)
#define LOGSRCCNT	200
#define NRLOGSYS	2		/* we have 2 log systems now	*/
#define MAXLOGSET	30

struct	logsource {
	int	logset;
	int     srccount;
	long	logretval;	      /* store retval of last command	*/
	char	header[400];
	char	types [40]; 
	long	addr  [LOGSRCCNT][3];  /* max. LOGSRCCNT addresses*2+indicees */
	char    type  [LOGSRCCNT];

	char 	logbuf[LOGBUFSIZE];
	long 	logbufpos;    			/* = {0, 0}; */
	long 	logbufendpos; 			/* = {0, 0}; */
	long 	oldlogbufpos; 			/* = {0, 0}; */
  	FILE 	*stream;
	long 	taskretval;
	char 	logmsgbuf [100]; /* for messages & local vars of logfiletask  */
};

/* ===================================================================== */
/*
 * Declare this in advance, to be able to declare logfiletask.
 *
 * TODO: Not sure if we really need to export that function. Study...
 */
struct logfiletaskargs;

extern struct logsource   	logsrcs[NRLOGSYS];

/* ===================================================================== */
/*
 * In the next part, all defined functions from the various files are 
 * declared and made visible to each file which includes the header file.
 */

/* from ag_cad.c:	*/
long CAD_default  	( struct cadRecord  *pcad, long *pstatus);
long CADStop            ( struct cadRecord  *pcad);

/* from ag_globals.c:	*/
long init_globvars 	(void);

/* from ag_hardw.c	*/
long  	getDPvals 	(int motor, int card, long *lval, 
			double *dval1, double *dval2, double *dval3);
void  	getDPRamD2	(long pmacaddr, short card, short offset, double *Val);
void  	getDPRamD2raw 	(long adr, double *Val);
long  	setXYCOM 	(void);

/* from ag_logg.c:	*/
long 	prepare_log 	(char *filename, int logset, struct logsource *Plogsrc);
long 	flushlogfile 	(char *filename, char* mode, struct logsource *Plogsrc);
long	writelogsrc 	(struct logsource *logsrc, long param, char type, char * header);
long 	writelogbuf 	(struct genSubRecord *pgsub, struct logsource *logsrc);
long 	logfiletask 	(struct logfiletaskargs *args);
long 	writelogfile 	(char *filename, char* mode, struct logsource *logsrc, int oldlogbufpos);
long 	logging 	(struct genSubRecord *pgsub );

/* from ag_mem.c	*/
char *	strntoupper	(char *str , int length);
char *	movestring 	(char *buf, char *str, char *bufend, char *srcstr, int max_size);
long 	check_numeric	(char *buf );

/* from ag_utils.c	*/
long    agAb2xy         (long mechindex, double alpha, double beta, 
                         double CalParm[7], int RTPA_Orient[2], 
                         double* x, double* y) ;
long    agXy2ab         (long mechindex, long new_track_id, double x, double y, double CalParm[7],
                         double Limits[6], int RTPA_Orient[2],
                         double CurrRtAngle, double *alpha, double *beta) ;
long 	getpos 		(int mechindex, double current[3], double target[3],
                         double demand[3]);
long 	doPLCcomm 	(int mechindex, long command, long *Pos);
long 	doLowPLCcomm 	(int card, int motor, long command, long *Pos);
long 	init_DPRam 	(void);
long	getGIS		(void );
long 	setGIS		(int mechindex, int value );
long 	real2eng 	(double Scale, double Offset, double real);
double 	eng2real 	(double Scale, double Offset, long eng);
long	tai2str 	(char* messages, double t);
long 	query_cadname 	(char *string);
long 	query_sadname 	(char *string);
long 	queryLUT 	(struct cadRecord  *pcad);
long  	asklut 		( struct genSubRecord *pgsub );
char * 	mbbistr 	(int i);
char * 	limstr 		(int i);
long  	putlogmenustr 	(void);
long 	putmenustr 	(void);
long 	putsadlims 	(void);
long  	updatemenustr	(int mechindex);
long  	updatesadlims 	(int mechindex, char * namestr, double val[4]);
long  	putstr 		(int mechindex, char *recordstr, char *valuestr, int i);
long  	putlim 		(int mechindex, char *recordstr, char *valuestr);
double 	normAngle 	(double a, double pi);
long 	getdims 	(long mechindex);
long 	getplcn 	(long mechindex, long subindex);
long 	getcard 	(long mechindex, long subindex);
long 	getresponse 	(long mechindex, long subindex);
long 	getplcflags 	(long mechindex, long subindex);
long *	getrespaddr 	(long mechindex, long subindex);
long *	getflagaddr 	(long mechindex, long subindex);
short 	read_dpram  	(long  * addr);
void    encoderSwitch   (long onOff);

/* from ag_gensub.c     */
void agSetSlew (long probe) ;

/* from	drvBc635.c	*/
int bc635_event 	(double *prval);

/* from pmacvme.h	*/
extern volatile short 		*pmacRamAddr(int ctlr,int offset);		
extern long pmacRamGetH  ( volatile short * pDpram, long *pVal );
extern long pmacRamPutH  ( volatile short * pDpram, long   val );
extern long pmacRamGetX  ( volatile short * pDpram, long *pVal );
extern long pmacRamPutX  ( volatile short * pDpram, long   val );
extern long pmacRamGetDP ( volatile short * pDpram, long *pVal );
extern long pmacRamPutDP ( volatile short * pDpram, long   val );
extern long  pmacRamGetD ( volatile short * pDpram, double*pVal);


/* ===================================================================== */
/* 	long wrapsam (int sam, int maxsam)		(original)
 *	{ if (sam<0) sam = sam % maxsam + maxsam;
 *	  return (sam % maxsam); }			
 */

#define motad(mot)		(FGDatBuff + FGMotOfs*(mot-1))

#define wrapsam(VAL,MAX)     (	 (VAL)< 0    ? ((VAL)%(MAX)  + (MAX)) :	\
				((VAL)>=(MAX)? ((VAL)%(MAX)) : (VAL))	)

#define limit(VAL,MIN,MAX)   (	 (VAL)<(MIN)? (MIN) :			\
				((VAL)>(MAX)? (MAX) : (VAL))		)

#define lim(VAL,MIN,MAX)	limit((VAL),(MIN),(MAX))

#define get_tai(t)		(timeNow(t) ? (bc635_read (t)) : 0 )

#define getsimu(mechindex)    (	 ( ((mechindex) >= HRWFS_NAMES_START) && ((mechindex) <= HRWFS_NAMES_END) ) \
				|| ((mechindex) == hrwfs_cc)	?	simuMode[HRWFS]  :  simuMode[AG] )

#define getdebug(mechindex)   (	 ( ((mechindex) >= HRWFS_NAMES_START) && ((mechindex) <= HRWFS_NAMES_END) ) \
 				|| ((mechindex) == hrwfs_cc)	? 	debugMode[HRWFS] : debugMode[AG] )

#define agLogMessage(mechindex,debuglevel,message)	\
          if ((getdebug (mechindex) >= debuglevel) && 	\
	     (getdebug (mechindex) >  DEB_ERROR))  cicsLogMessage (message)

#define agprintf(formstr,message)			\
      if (getdebug (ag_cc) > DEB_ERROR)  printf (formstr,message)


#define mod(a,b)		dmod ((a),(b))


#define pmac2hostaddr(card,pmacaddr,offset) \
          (pmacRamAddr ((card),	\
	  limit( (((pmacaddr)-0xd000)<<2) + (offset), 0, 0x3FFF) ))

/*
#define pmacRamGetX  				pmacRamGetXree  
#define pmacRamGetDP  				pmacRamGetDPree  
#define pmacRamPutH  				pmacRamPutHree  
#define pmacRamPutX  				pmacRamPutXree  
#d#efine pmacRamPutDP  				pmacRamPutDPree  
*/

#define getDPRam(pmacaddr,card,offset) \
  (((long)*(short*)pmac2hostaddr (card, pmacaddr, offset)) & 0xffff)
#define getDPRamraw(addr)	(((long)*(short*)(addr)) & 0xffff)

#define get2DPRam(pmacaddr,card,offset,Val) \
   *Val=getDPRam(pmacaddr,card,offset)
#define get2DPRamXY(pmacaddr,card,offset,Val) \
   pmacRamGetX  (pmac2hostaddr (card, pmacaddr, offset), Val)
#define get2DPRamDP(pmacaddr,card,offset,Val) \
   pmacRamGetDP (pmac2hostaddr (card, pmacaddr, offset), Val)

#define putDPRam(pmacaddr,Val,card,offset) \
   pmacRamPutH  (pmac2hostaddr (card, pmacaddr, offset), Val)
#define putDPRamXY(pmacaddr,Val,card,offset) \
   pmacRamPutX  (pmac2hostaddr (card, pmacaddr, offset), Val)
#define putDPRamDP(pmacaddr,Val,card,offset) \
   pmacRamPutDP (pmac2hostaddr (card, pmacaddr, offset), Val)

#define getswitchhw(PLCn)  \
   (((long)((unsigned short) getDPRam (PLCflagsStart+ 	\
   ((PLCn)>16)?(PLCn)-16:(PLCn), ((PLCn)>16)?1:0, 0))	)

#define getswitch(mechindex) \
   ((getsimu(mechindex) == SIM_NONE) ?			\
   (long) ((unsigned short) getDPRam (PLCflagsStart+ 	\
   getplcn(mechindex, 0), getcard(mechindex, 0), 0)) :	\
   (plcflag[mechindex][0])		)

#define getresponse(mechindex,subindex)	 \
   ((getsimu(mechindex) == SIM_NONE) ?			\
   (long) ((unsigned short) getDPRam (FlagStart+ 	\
   getplcn(mechindex, subindex), getcard(mechindex, subindex), 0)) :	\
   (plcflag[mechindex][0])		)

/* ====================================================================	*/

#define word unsigned short
#define byte unsigned char

/* ===================================================================== */
#define FGDatBuff	0xD012		/* follow. Offsets for Motor 1:	*/
  #define CommPos	0		/* Mot. Commanded Position 64b	*/
  #define ActPos	2		/* Mot. Actual Position	   64b	*/
  #define StatWor1	9		/* Mot. Status word 1      24b	*/
  #define ActVel	10		/* Actual velocity         24b	*/
  #define FGMotOfs	15		/* max 8 motors with 15 words	*/

#define BGDatBuff	0xD093		/* follow. Offsets for Motor 1:	*/
  #define TargPos	0		/* Target Position	   64b	*/
  #define StatWor2	4		/* Mot. Status word 2    Y 24b	*/
  #define AveVel	30		/* Average velocity      X 24b	*/
  #define BGMotOfs	31		/* max 8 motors with 31 words	*/

#define PosStart	0xDB20 		/* Mot 1 starts at addr. 1 	*/
  #define P_BigPLC	1		/* 1st mode of CC PLC (Param)	*/
  #define P_SmallPLC	0		/* 2nd mode of CC PLC (Param)	*/
#define FlagStart	0xDB00		/* Mot 1 starts at addr. 1 	*/
  #define C_Datum	1		/* Datum-Command 		*/
  #define C_Park	2		/* Park-Command 		*/
  #define C_Stop	3		/* Stop-Command 		*/
  #define C_Move	4		/* Move-Command 		*/
  #define C_Foll	5		/* Follow-Command 		*/
  #define C_Crude	9		/* Crude-Follow-Cmd 		*/
  #define C_SoftStop	10		/* Soft-Stop-Command 		*/
  #define FOLLOW_ON 	205		/* RT, PA, focus, probe		*/
  #define FOLLOW_ON2 	209		/* crude tracking		*/

#define LinSkewOffset	0xDB3F		/* Offset to linear stage skew	*/
#define CalcTargStart	0xDBC0		/* calc. target pos. from PLC 28 */
#define CalcDemStart	0xDC30		/* calc. demand pos. from PLC 28 */
#define CalcMSWStart	0xDB60		/* freezed MSW1/2 from PLC 28; Y:MSW1, X:MSW2  */
#define CalcPosStart	0xDB70		/* calc. pos. from PLC 28	*/
  #define Ch5_Src_Ofs	0x11		/* Addr offset in PDRAM,	*/
  #define Ch7_Src_Ofs	0x12		/*  where the switched source	*/
  #define Ch8_Src_Ofs	0x13		/*  on ch. 5/7/8 stands		*/

#define ToleranceStart	0xDC40		/* inPos -tolerances for PLC 28	*/

#define PLC30		30
#define TRACKMODE	105
#define CRUDEMODE	109
#define TRACK_ON	205
#define CRUDE_ON	209

#define PLCflagsStart	0xDB90		/* flags like Datumed, Parked.. */
  #define DATUFLAG	(1<< 0)
  #define PARKFLAG	(1<< 1)
  #define POSMFLAG	(1<< 2)		/* inPos-Mode; 1=based on actual*/
  #define BRONFLAG      (1<< 4)         /* Brake on flag */
  #define IPOSFLAG	(1<< 5)		/* inPosition (PLC28)		*/
  #define AENAFLAG	(1<< 6)		/* Amp enable			*/
  #define FDISFLAG	(1<< 7)		/* DelayFilterDisable		*/
  #define CPEQFLAG	(1<< 8)		/* Compare- equal		*/
  #define CAPTFLAG	(1<< 9)		/* position captured		*/
  #define CERRFLAG	(1<<10)		/* Count error			*/
  #define ZSTAFLAG	(1<<11)		/* z-Channel state		*/
  #define HOMEFLAG	(1<<12)		/* Interlocking/Home switch	*/
  #define PLIMFLAG	(1<<13)		/* EOR at pos. side		*/
  #define NLIMFLAG	(1<<14)		/* EOR at neg. side		*/
  #define FAULFLAG	(1<<15)		/* Amp.Fault			*/

#define TorqValStart	0xDBB1          /* Demanded trorque ( -> PLC27) */
#define TorqEnStart	0xDBB6		/* 3 Values for 5 motors	*/
#define TorqActStart	0xDBBB          /* Applied torque ( <- PLC27)  */
#define GIS_Ofs		3		/* GIS flag stored hier		*/
#define Fault_Ofs	4		/* MAC faults stored hier	*/

#define TrPosStart	0xDF00		/* Tracking sample array [20]	*/
#define TrVelStart	0xDF40		/* velocities [20]		*/
#define TrEPsam		0xDF7C		/* EPICS: last written sample	*/
#define TrPMsam		0xDF7D		/* PMAC:  next used sample	*/
#define TrPMerr		0xDF7E		/* PMAC:  error count (to log)	*/
#define TrEPtab		0xDF7F		/* EPICS: last written table #	*/
#define MAXSAM		20		/* size of sample array in DPRam */

#define DPRamStart	0xDB00		/* used for erasing the DPRam	*/
#define DPRamLen	(0x100-2)	/* Start=D000 - access fault!	*/


/* ===================================================================== */
/*  The next string constants serve multiple purposes: "datum-pos." and
 *  "park-pos." are defined for some of the mechanisms which go to a predefined
 *  position after datum and park commands rather than goiung just to a limit 
 *  or home switch.
 *  
 *  putmenustr and updatemenustr from ag_utils.c don't display them if found 
 *  in a lut file. The "hidden" string is the last entry in each lut file and 
 *  covers all possible position which are not defined before it. This is to 
 *  get rid of the default "invalid" string of the lutin record without 
 *  changing Epics.  
 */

#define datumstr	"datum-pos."	/* named position in LUT	*/
#define parkstr		"park-pos."	/*  (was park/datum for Unit1)	*/
#define hiddenstr	"undefined"

/* ===================================================================== */

#define PI 		DPI
/* (3.1415926535897932384626433832795028841971693993751)	*/

/* ===================================================================== */

/* indices for mechanisms in the "currentpos" and "demandpos" arrays */
#define HRWFS_NAMES_START	0
#define pimg  		0
#define lens 		1
#define clfilter 	2
#define ndfilter 	3
#define fldstop		4
#define cal		5
#define focus		6

#define HRWFS_NAMES_END	6
#define AG_NAMES_START	7

#define ag_sf		7
#define ag_hw		8
#define ag_ao		9

#define p1_probe	10
#define p1_focus	11
#define p1_filter	12
#define p1_fldstop	13

#define p2_probe	14
#define p2_focus	15
#define p2_filter	16
#define p2_fldstop	17

					/* indices for the low-level motors */
#define p1_RT4		18
#define p1_PA4		19
#define p2_RT3		20
#define p2_PA3		21

#define ag_RT2		22
#define ag_Tilt		23
#define ag_Lin2		24

#define ag_PA3AO	25
#define AG_NAMES_END	25
#define MAX_MECH_INDEX	AG_NAMES_END

#define hrwfs_cc	26		/* both Component Controllers	*/
#define ag_cc		27
#define MAX_INDEX	28
/* if max. number is changed, change MAX_INDEX too : to Index+1 ! */
		
/* ===================================================================== */

#define HRWFS	0		/* used for indexing of simu- and debugMode */
#define AG	1

/* ===================================================================== */

/*
 * Stringfy TOP_AG and TOP_HRWFS and Concatenate them to strings
 * to get the right ${top}
 */
#define STRINGIFY(s) #s
#define CONCAT_TOP(top, field) (STRINGIFY(top) field)

#define AG_TOP(field)  CONCAT_TOP(TOP_AG, field)
#define HRWFS_TOP(field) CONCAT_TOP(TOP_HRWFS, field)

#define pimg_str		HRWFS_TOP(":pimg")
#define lens_str 		HRWFS_TOP(":lens")
#define clfilter_str 		HRWFS_TOP(":clfilter")
#define ndfilter_str 		HRWFS_TOP(":ndfilter")
#define fldstop_str		HRWFS_TOP(":fldstop")
#define cal_str			HRWFS_TOP(":cal")
#define focus_str		HRWFS_TOP(":focus")

#define ag_sf_str		AG_TOP(":sf")
#define ag_hw_str		AG_TOP(":hw")
#define ag_ao_str		AG_TOP(":ao")

#define p1_probe_str		AG_TOP(":p1:probe")
#define p1_focus_str		AG_TOP(":p1:focus")
#define p1_filter_str		AG_TOP(":p1:filter")
#define p1_fldstop_str		AG_TOP(":p1:fldstop")

#define p2_probe_str		AG_TOP(":p2:probe")
#define p2_focus_str		AG_TOP(":p2:focus")
#define p2_filter_str		AG_TOP(":p2:filter")
#define p2_fldstop_str		AG_TOP(":p2:fldstop")

#define hrwfs_cc_str		HRWFS_TOP(":cc:")
#define ag_cc_str		AG_TOP(":cc:")

#define ag_p1_str		AG_TOP(":p1:")
#define ag_p2_str		AG_TOP(":p2:")


#define pimg_sadstr		HRWFS_TOP(":pimg")
#define lens_sadstr 		HRWFS_TOP(":lens")
#define clfilter_sadstr 	HRWFS_TOP(":clfilter")
#define ndfilter_sadstr 	HRWFS_TOP(":ndfilter")
#define fldstop_sadstr		HRWFS_TOP(":fldstop")
#define cal_sadstr		HRWFS_TOP(":cal")
#define focus_sadstr		HRWFS_TOP(":focus")

#define ag_sf_sadstr		AG_TOP(":sf")
#define ag_hw_sadstr		AG_TOP(":hw")
#define ag_ao_sadstr		AG_TOP(":ao")

#define p1_probe_sadstr		AG_TOP(":p1:probe")
#define p1_focus_sadstr		AG_TOP(":p1:focus")
#define p1_filter_sadstr	AG_TOP(":p1:filter")
#define p1_fldstop_sadstr	AG_TOP(":p1:fldstop")

#define p2_probe_sadstr		AG_TOP(":p2:probe")
#define p2_focus_sadstr		AG_TOP(":p2:focus")
#define p2_filter_sadstr	AG_TOP(":p2:filter")
#define p2_fldstop_sadstr	AG_TOP(":p2:fldstop")

#define hrwfs_cc_sadstr		HRWFS_TOP(":cc:")
#define ag_cc_sadstr		AG_TOP(":cc:")

#define ag_p1_sadstr		AG_TOP(":p1:")
#define ag_p2_sadstr		AG_TOP(":p2:")


/* definitions for recognizing of the motor names (low level mechanisms)  */

#define p1_RT4_str		AG_TOP(":p1:RT34")
#define p1_PA4_str		AG_TOP(":p1:PA34")

#define p2_RT3_str		AG_TOP(":p2:RT34")
#define p2_PA3_str		AG_TOP(":p2:PA34")

#define ag_RT2_str		AG_TOP(":RT2")
#define ag_Tilt_str		AG_TOP(":Tilt")
#define ag_Lin2_str		AG_TOP(":Lin2")

#define ag_PA3AO_str		AG_TOP(":PA3AO")


#define p1_RT4_sadstr		AG_TOP(":p1:RT34")
#define p1_PA4_sadstr		AG_TOP(":p1:PA34")

#define p2_RT3_sadstr		AG_TOP(":p2:RT34")
#define p2_PA3_sadstr		AG_TOP(":p2:PA34")

#define ag_RT2_sadstr		AG_TOP(":RT2")
#define ag_Tilt_sadstr		AG_TOP(":Tilt")
#define ag_Lin2_sadstr		AG_TOP(":Lin2")

#define ag_PA3AO_sadstr		AG_TOP(":PA3AO")

#define dummy_str		"dummy"


/* ===================================================================== */
/* SCAN-field does not need to be casted. Cannot be written from inside a 
 * record. PVPuts from SNL don't trigger a record.
 * From epics/base/src/ascii/choiceGbl.ascii:
 */

#define SCANPass	0
#define SCANEvent	1
#define SCANIO		2
#define SCAN10s		3
#define SCAN5s		4
#define SCAN2s		5
#define SCAN1s		6
#define SCAN2hz		7
#define SCAN5hz		8
#define SCAN10hz	9
#define SCAN20hz	10
#define SCAN100hz	11
#define SCAN80hz	12
#define SCAN60hz	13
#define SCAN200hz	14

/* ===================================================================== */

/* simulation level: 	0, 1, 2, 3	*/
#define SIM_NONE	menuSimulationNONE
#define SIM_VSM		menuSimulationVSM
#define SIM_FAST	menuSimulationFAST
#define SIM_FULL	menuSimulationFULL

#define SIM_NONE_str	"NONE"
#define SIM_VSM_str	"VSM"
#define SIM_FAST_str	"FAST"
#define SIM_FULL_str	"FULL"
#define SIM_str(SIM)	((SIM==SIM_NONE) ?  SIM_NONE_str : 		\
			((SIM==SIM_VSM)  ?  SIM_VSM_str  : 		\
			((SIM==SIM_FAST) ?  SIM_FAST_str : SIM_FULL_str)))

/* debug level		*/
#define DEB_ERROR	0
#define DEB_NONE	0
#define DEB_MIN		1
#define DEB_FULL	2

#define DEB_NONE_str	"NONE"
#define DEB_MIN_str	"MIN"
#define DEB_FULL_str	"FULL"
#define DEB_str(DEB)	((DEB==DEB_NONE)  ?  DEB_NONE_str  : 		\
			((DEB==DEB_MIN)   ?  DEB_MIN_str   : DEB_FULL_str))

/* PA- and RT-Orientation flags	*/
#define CW		0
#define CCW		1
#define CWCCW		2		/* don't care	*/

#define CW_str		"CW"
#define CCW_str		"CCW"
#define CWCCW_str	"X"
#define ORI_str(ORI)	((ORI==CW)? CW_str : ((ORI==CCW)? CCW_str : CWCCW_str))

/* ===================================================================== */
/* XYCOM base address is set to ffffd000, and the interrupt vector register
 * is at offset 85.  In addition, the status & control register is at offset
 * 81. */

#if (CPU_FAMILY == PPC)
  #define xycomBase	0xfbffd000	/* base	address for MVE2700 */
#else 					/* MC680X0 */
  #define xycomBase	0xffffd000	/* base	address	for MVME167 */
#endif

#define portDirRegAddr	(*(byte*)(xycomBase+0x0087))	/* port dir reg	*/
#define port6addr 	(*(byte*)(xycomBase+0x008e))	/* I/O port 6	*/
#define port7addr 	(*(byte*)(xycomBase+0x008f))	/* I/O port 7	*/

/* define interlock port masks and actual hardware access codes */
#define	GIS_MASK	3			/* 11b: Bits 0+1 used	*/
#define	GIS_CLEAR	2			/* 10b: 2	*/
#define GIS_SET		1			/* 01b: 1	*/

/* logical GIS demands / events	*/
#define GIS_OFF		0
#define GIS_ON		1
#define GIS_UNDEFINED	2		/* undefined acts as ON (wire broken). */

#define GISOFF_str		"GIS_OFF"
#define GISON_str		"GIS_ON"
#define GISUNDEF_str		"UNDEFINED"
#define GIS_str(state)		((state==GIS_OFF)? GISOFF_str : ((state==GIS_ON)? GISON_str : GISUNDEF_str))

/* ===================================================================== */
// #if (CPU_FAMILY == PPC)
//   #define bcBase	0xfbff4000	/* bancomm base address 	*/
// #else 					/* MC680X0 */
//   #define bcBase	0xffff4000	
// #endif
// 
// #define	bcstr1	(*(word*)(bcBase+0x18))	/* strobe reg 1	*/
// #define	bcstr2	(*(word*)(bcBase+0x1A))	/* strobe reg 2	*/
// #define	bcstr3	(*(word*)(bcBase+0x1C))	/* strobe reg 3	*/
// #define	bcmask	(*(word*)(bcBase+0x28))	/* interr. mask	*/
// #define	bcstat	(*(word*)(bcBase+0x2A))	/* interr. stat	*/


#define GPS_TO_TAI	19		/* TAI = GPS + 19 Sec.	*/

/* enumerated time scales used in BC-Library:
 * 0 = TAI	1 = UTC		2 = UT1
 * 3 = TT	4 = TDB
 */

/* ===================================================================== */
#define MAX_LUTpcnt 	10
/* ===================================================================== */

/* Constants that define the field scales of the probes */
#define M2TOFPLANE   16539.326
#define M1TOFPLANE   18335.5393
#define P1TOFPLANE   1995.0
#define P2TOFPLANE   1610.0

extern long   plcflag	[MAX_INDEX][4];	/* ..., Home, +Lim, -Lim, ...	*/
extern long   currpos	[MAX_INDEX][3];	/* [0]:X, [1]:Y, [2]:z		*/
extern long   targpos	[MAX_INDEX][3];
extern long   demapos	[MAX_INDEX][3];	

extern double Offset    [MAX_INDEX][3];	/* [0]:X, [1]:Y, [2]:z		*/
extern double Scale     [MAX_INDEX][3];
extern double ForPar	[MAX_INDEX][7];	/* Frame-of-reference params	*/
extern double Limits	[MAX_INDEX][6];	/* [0]:posX, [1]:negX, [2]:Y.. 	*/

extern int    PlcNr     [MAX_INDEX][4];	/* used Pmac PLC progs		*/


extern int    RTPA_OriFlag[2][2];	/* Orientations:		*/
					/* [0][0]=P1RT, [0][1]=P1PA	*/
					/* [1][0]=P2RT, [1][1]=P2PA	*/


extern double Rad_Toler	  [2];		/* Radial/Focus tolerance P1/P2	*/
extern double Foc_Toler	  [2];
/* extern long   follow	  [2];	*/	/* follow on/off for PWFS1/2	*/
extern double corrparam   [10][4];	/* parameters for torque and tilt correction formulas */

extern long gis_events [MAX_INDEX];
extern long gis_event;			/* outgoing GIS call, coded	*/
extern long gis_demand;			/* incoming GIS call, coded	*/
extern long gis_demand_hw;		/* hardware bits, not coded	*/

extern long debugMode[2];		/* gbd/hrwfs CC			*/
extern long simuMode [2];

extern char mechstrs  [MAX_INDEX][MAX_STRING_SIZE];
extern char sadstrs   [MAX_INDEX][MAX_STRING_SIZE];
#define MAXMENUSTR	33		/* mbbip has 24 fields	*/
extern char menustrs  [MAX_INDEX][MAXMENUSTR][20];	/* max. 17 strs a' 20 chars in menu */

			/* max. MAX_LUTpcnt additional LUT strings */
extern char   LUTplus     [MAX_INDEX][MAX_LUTpcnt][MAX_STRING_SIZE]; 
extern long   LUTplusPos  [MAX_INDEX][MAX_LUTpcnt][3];	/* up to 3 dims	*/
extern long   LUTpluscount[MAX_INDEX];

extern char   logmenustrs [2][MAXLOGSET][MENUSTRSIZE];	/* max.30 strs a'20 per logger */

extern long lastPLCcomm[MAX_INDEX] ;

/* ===================================================================== */
