#include "dbDefs.h"
#include "epicsPrint.h"
#include "alarm.h"
#include "dbAccess.h"
#include "dbEvent.h"
#include "dbFldTypes.h"
#include "devSup.h"
#include "errMdef.h"
#include "menuSimm.h"
#include "recSup.h"
#include "recGbl.h"
#include "special.h"
#include "ellLib.h"
#include "link.h"
#include "tsDefs.h"
#ifndef INCmbbiH
#define INCmbbiH
typedef struct mbbipRecord {
	char		name[29]; /*Record Name*/
	char		desc[29]; /*Descriptor*/
	char		asg[29]; /*Access Security Group*/
	unsigned short	scan;	/*Scan Mechanism*/
	unsigned short	pini;	/*Process at iocInit*/
	short		phas;	/*Scan Phase*/
	short		evnt;	/*Event Number*/
	short		tse;	/*Time Stamp Event*/
	DBLINK		tsel;	/*Time Stamp Link*/
	unsigned short	dtyp;	/*Device Type*/
	short		disv;	/*Disable Value*/
	short		disa;	/*Disable*/
	DBLINK		sdis;	/*Scanning Disable*/
	epicsMutexId	mlok;	/*Monitor fastlock*/
	ELLLIST		mlis;	/*Monitor List*/
	unsigned char	disp;	/*Disable putField*/
	unsigned char	proc;	/*Force Processing*/
	unsigned short	stat;	/*Alarm Status*/
	unsigned short	sevr;	/*Alarm Severity*/
	unsigned short	nsta;	/*New Alarm Status*/
	unsigned short	nsev;	/*New Alarm Severity*/
	unsigned short	acks;	/*Alarm Ack Severity*/
	unsigned short	ackt;	/*Alarm Ack Transient*/
	unsigned short	diss;	/*Disable Alarm Sevrty*/
	unsigned char	lcnt;	/*Lock Count*/
	unsigned char	pact;	/*Record active*/
	unsigned char	putf;	/*dbPutField process*/
	unsigned char	rpro;	/*Reprocess */
	void		*asp;	/*Access Security Pvt*/
	struct putNotify *ppn;	/*addr of PUTNOTIFY*/
	struct pnWaitNode *ppnn;	/*next record PUTNOTIFY*/
	struct scan_element *spvt;	/*Scan Private*/
	struct rset	*rset;	/*Address of RSET*/
	struct dset	*dset;	/*DSET address*/
	void		*dpvt;	/*Device Private*/
	struct dbRecordType *rdes;	/*Address of dbRecordType*/
	struct lockRecord *lset;	/*Lock Set*/
	unsigned short	prio;	/*Scheduling Priority*/
	unsigned char	tpro;	/*Trace Processing*/
	char bkpt;	/*Break Point*/
	unsigned char	udf;	/*Undefined*/
	TS_STAMP	time;	/*Time*/
	DBLINK		flnk;	/*Forward Process Link*/
	unsigned short	val;	/*Current Value*/
	short		nobt;	/*Number of Bits*/
	DBLINK		inp;	/*Input Specification*/
	unsigned long	zrvl;	/*Zero Value*/
	unsigned long	onvl;	/*One Value*/
	unsigned long	twvl;	/*Two Value*/
	unsigned long	thvl;	/*Three Value*/
	unsigned long	frvl;	/*Four Value*/
	unsigned long	fvvl;	/*Five Value*/
	unsigned long	sxvl;	/*Six Value*/
	unsigned long	svvl;	/*Seven Value*/
	unsigned long	eivl;	/*Eight Value*/
	unsigned long	nivl;	/*Nine Value*/
	unsigned long	tevl;	/*Ten Value*/
	unsigned long	elvl;	/*Eleven Value*/
	unsigned long	tvvl;	/*Twelve Value*/
	unsigned long	ttvl;	/*Thirteen Value*/
	unsigned long	ftvl;	/*Fourteen Value*/
	unsigned long	ffvl;	/*Fifteen Value*/
	unsigned long	ssvl;	/*Sixteen Value*/
	unsigned long	snvl;	/*Seventeen Value*/
	unsigned long	etvl;	/*Eightteen Value*/
	unsigned long	ntvl;	/*Nineteen Value*/
	unsigned long	wyvl;	/*Twenty Value*/
	unsigned long	wovl;	/*Twentyone Value*/
	unsigned long	wtvl;	/*Twentytwo Value*/
	unsigned long	whvl;	/*Twentythree Value*/
	char		zrst[16]; /*Zero String*/
	char		onst[16]; /*One String*/
	char		twst[16]; /*Two String*/
	char		thst[16]; /*Three String*/
	char		frst[16]; /*Four String*/
	char		fvst[16]; /*Five String*/
	char		sxst[16]; /*Six String*/
	char		svst[16]; /*Seven String*/
	char		eist[16]; /*Eight String*/
	char		nist[16]; /*Nine String*/
	char		test[16]; /*Ten String*/
	char		elst[16]; /*Eleven String*/
	char		tvst[16]; /*Twelve String*/
	char		ttst[16]; /*Thirteen String*/
	char		ftst[16]; /*Fourteen String*/
	char		ffst[16]; /*Fifteen String*/
	char		ssst[16]; /*Sixteen String*/
	char		snst[16]; /*Seventeen String*/
	char		etst[16]; /*Eighteen String*/
	char		ntst[16]; /*Nineteen String*/
	char		wyst[16]; /*Twenty String*/
	char		wost[16]; /*Twenty one String*/
	char		wtst[16]; /*Twenty two String*/
	char		whst[16]; /*Twenty three String*/
	unsigned short	zrsv;	/*State Zero Severity*/
	unsigned short	onsv;	/*State One Severity*/
	unsigned short	twsv;	/*State Two Severity*/
	unsigned short	thsv;	/*State Three Severity*/
	unsigned short	frsv;	/*State Four Severity*/
	unsigned short	fvsv;	/*State Five Severity*/
	unsigned short	sxsv;	/*State Six Severity*/
	unsigned short	svsv;	/*State Seven Severity*/
	unsigned short	eisv;	/*State Eight Severity*/
	unsigned short	nisv;	/*State Nine Severity*/
	unsigned short	tesv;	/*State Ten Severity*/
	unsigned short	elsv;	/*State Eleven Severity*/
	unsigned short	tvsv;	/*State Twelve Severity*/
	unsigned short	ttsv;	/*State Thirteen Sevr*/
	unsigned short	ftsv;	/*State Fourteen Sevr*/
	unsigned short	ffsv;	/*State Fifteen Severity*/
	unsigned short	sssv;	/*State Sixteen Severity*/
	unsigned short	snsv;	/*State Seventeen Severity*/
	unsigned short	etsv;	/*State Eighteen Severity*/
	unsigned short	ntsv;	/*State Nineteen Severity*/
	unsigned short	wysv;	/*State Twenty Severity*/
	unsigned short	wosv;	/*State Twenty one Severity*/
	unsigned short	wtsv;	/*State Twenty two Severity*/
	unsigned short	whsv;	/*State Twenty three Severity*/
	unsigned short	unsv;	/*Unknown State Severity*/
	unsigned short	cosv;	/*Change of State Svr*/
	unsigned long	rval;	/*Raw Value*/
	unsigned long	oraw;	/*Prev Raw Value*/
	unsigned long	mask;	/*Hardware Mask*/
	unsigned short	mlst;	/*Last Value Monitored*/
	unsigned short	lalm;	/*Last Value Alarmed*/
	short		sdef;	/*States Defined*/
	unsigned short	shft;	/*Shift*/
	DBLINK		siol;	/*Sim Input Specifctn*/
	unsigned short	sval;	/*Simulation Value*/
	DBLINK		siml;	/*Sim Mode Location*/
	unsigned short	simm;	/*Simulation Mode*/
	unsigned short	sims;	/*Sim mode Alarm Svrty*/
} mbbipRecord;
#define mbbipRecordNAME	0
#define mbbipRecordDESC	1
#define mbbipRecordASG	2
#define mbbipRecordSCAN	3
#define mbbipRecordPINI	4
#define mbbipRecordPHAS	5
#define mbbipRecordEVNT	6
#define mbbipRecordTSE	7
#define mbbipRecordTSEL	8
#define mbbipRecordDTYP	9
#define mbbipRecordDISV	10
#define mbbipRecordDISA	11
#define mbbipRecordSDIS	12
#define mbbipRecordMLOK	13
#define mbbipRecordMLIS	14
#define mbbipRecordDISP	15
#define mbbipRecordPROC	16
#define mbbipRecordSTAT	17
#define mbbipRecordSEVR	18
#define mbbipRecordNSTA	19
#define mbbipRecordNSEV	20
#define mbbipRecordACKS	21
#define mbbipRecordACKT	22
#define mbbipRecordDISS	23
#define mbbipRecordLCNT	24
#define mbbipRecordPACT	25
#define mbbipRecordPUTF	26
#define mbbipRecordRPRO	27
#define mbbipRecordASP	28
#define mbbipRecordPPN	29
#define mbbipRecordPPNN	30
#define mbbipRecordSPVT	31
#define mbbipRecordRSET	32
#define mbbipRecordDSET	33
#define mbbipRecordDPVT	34
#define mbbipRecordRDES	35
#define mbbipRecordLSET	36
#define mbbipRecordPRIO	37
#define mbbipRecordTPRO	38
#define mbbipRecordBKPT	39
#define mbbipRecordUDF	40
#define mbbipRecordTIME	41
#define mbbipRecordFLNK	42
#define mbbipRecordVAL	43
#define mbbipRecordNOBT	44
#define mbbipRecordINP	45
#define mbbipRecordZRVL	46
#define mbbipRecordONVL	47
#define mbbipRecordTWVL	48
#define mbbipRecordTHVL	49
#define mbbipRecordFRVL	50
#define mbbipRecordFVVL	51
#define mbbipRecordSXVL	52
#define mbbipRecordSVVL	53
#define mbbipRecordEIVL	54
#define mbbipRecordNIVL	55
#define mbbipRecordTEVL	56
#define mbbipRecordELVL	57
#define mbbipRecordTVVL	58
#define mbbipRecordTTVL	59
#define mbbipRecordFTVL	60
#define mbbipRecordFFVL	61
#define mbbipRecordSSVL	62
#define mbbipRecordSNVL	63
#define mbbipRecordETVL	64
#define mbbipRecordNTVL	65
#define mbbipRecordWYVL	66
#define mbbipRecordWOVL	67
#define mbbipRecordWTVL	68
#define mbbipRecordWHVL	69
#define mbbipRecordZRST	70
#define mbbipRecordONST	71
#define mbbipRecordTWST	72
#define mbbipRecordTHST	73
#define mbbipRecordFRST	74
#define mbbipRecordFVST	75
#define mbbipRecordSXST	76
#define mbbipRecordSVST	77
#define mbbipRecordEIST	78
#define mbbipRecordNIST	79
#define mbbipRecordTEST	80
#define mbbipRecordELST	81
#define mbbipRecordTVST	82
#define mbbipRecordTTST	83
#define mbbipRecordFTST 84
#define mbbipRecordFFST	85
#define mbbipRecordSSST	86
#define mbbipRecordSNST	87
#define mbbipRecordETST	88
#define mbbipRecordNTST	89
#define mbbipRecordWYST	90
#define mbbipRecordWOST	91
#define mbbipRecordWTST	92
#define mbbipRecordWHST	93
#define mbbipRecordZRSV	94
#define mbbipRecordONSV	95
#define mbbipRecordTWSV	96
#define mbbipRecordTHSV	97
#define mbbipRecordFRSV	98
#define mbbipRecordFVSV	99
#define mbbipRecordSXSV	100
#define mbbipRecordSVSV	101
#define mbbipRecordEISV	102
#define mbbipRecordNISV	103
#define mbbipRecordTESV	104
#define mbbipRecordELSV	105
#define mbbipRecordTVSV	106
#define mbbipRecordTTSV	107
#define mbbipRecordFTSV	108
#define mbbipRecordFFSV	109
#define mbbipRecordSTSV	110
#define mbbipRecordSNSV	111
#define mbbipRecordETSV	112
#define mbbipRecordNTSV	113
#define mbbipRecordWYSV	114
#define mbbipRecordWOSV	115
#define mbbipRecordWTSV	116
#define mbbipRecordWHSV	117
#define mbbipRecordUNSV	118
#define mbbipRecordCOSV	119
#define mbbipRecordRVAL	120
#define mbbipRecordORAW	121
#define mbbipRecordMASK	122
#define mbbipRecordMLST	123
#define mbbipRecordLALM	124
#define mbbipRecordSDEF	125
#define mbbipRecordSHFT	126
#define mbbipRecordSIOL	127
#define mbbipRecordSVAL	128
#define mbbipRecordSIML	129
#define mbbipRecordSIMM	130
#define mbbipRecordSIMS	131
#endif /*INCmbbiH*/
#ifdef GEN_SIZE_OFFSET
int mbbipRecordSizeOffset(dbRecordType *pdbRecordType)
{
  mbbipRecord *prec = 0;
  pdbRecordType->papFldDes[0]->size=sizeof(prec->name);
  pdbRecordType->papFldDes[0]->offset=(short)((char *)&prec->name - (char *)prec);
  pdbRecordType->papFldDes[1]->size=sizeof(prec->desc);
  pdbRecordType->papFldDes[1]->offset=(short)((char *)&prec->desc - (char *)prec);
  pdbRecordType->papFldDes[2]->size=sizeof(prec->asg);
  pdbRecordType->papFldDes[2]->offset=(short)((char *)&prec->asg - (char *)prec);
  pdbRecordType->papFldDes[3]->size=sizeof(prec->scan);
  pdbRecordType->papFldDes[3]->offset=(short)((char *)&prec->scan - (char *)prec);
  pdbRecordType->papFldDes[4]->size=sizeof(prec->pini);
  pdbRecordType->papFldDes[4]->offset=(short)((char *)&prec->pini - (char *)prec);
  pdbRecordType->papFldDes[5]->size=sizeof(prec->phas);
  pdbRecordType->papFldDes[5]->offset=(short)((char *)&prec->phas - (char *)prec);
  pdbRecordType->papFldDes[6]->size=sizeof(prec->evnt);
  pdbRecordType->papFldDes[6]->offset=(short)((char *)&prec->evnt - (char *)prec);
  pdbRecordType->papFldDes[7]->size=sizeof(prec->tse);
  pdbRecordType->papFldDes[7]->offset=(short)((char *)&prec->tse - (char *)prec);
  pdbRecordType->papFldDes[8]->size=sizeof(prec->tsel);
  pdbRecordType->papFldDes[8]->offset=(short)((char *)&prec->tsel - (char *)prec);
  pdbRecordType->papFldDes[9]->size=sizeof(prec->dtyp);
  pdbRecordType->papFldDes[9]->offset=(short)((char *)&prec->dtyp - (char *)prec);
  pdbRecordType->papFldDes[10]->size=sizeof(prec->disv);
  pdbRecordType->papFldDes[10]->offset=(short)((char *)&prec->disv - (char *)prec);
  pdbRecordType->papFldDes[11]->size=sizeof(prec->disa);
  pdbRecordType->papFldDes[11]->offset=(short)((char *)&prec->disa - (char *)prec);
  pdbRecordType->papFldDes[12]->size=sizeof(prec->sdis);
  pdbRecordType->papFldDes[12]->offset=(short)((char *)&prec->sdis - (char *)prec);
  pdbRecordType->papFldDes[13]->size=sizeof(prec->mlok);
  pdbRecordType->papFldDes[13]->offset=(short)((char *)&prec->mlok - (char *)prec);
  pdbRecordType->papFldDes[14]->size=sizeof(prec->mlis);
  pdbRecordType->papFldDes[14]->offset=(short)((char *)&prec->mlis - (char *)prec);
  pdbRecordType->papFldDes[15]->size=sizeof(prec->disp);
  pdbRecordType->papFldDes[15]->offset=(short)((char *)&prec->disp - (char *)prec);
  pdbRecordType->papFldDes[16]->size=sizeof(prec->proc);
  pdbRecordType->papFldDes[16]->offset=(short)((char *)&prec->proc - (char *)prec);
  pdbRecordType->papFldDes[17]->size=sizeof(prec->stat);
  pdbRecordType->papFldDes[17]->offset=(short)((char *)&prec->stat - (char *)prec);
  pdbRecordType->papFldDes[18]->size=sizeof(prec->sevr);
  pdbRecordType->papFldDes[18]->offset=(short)((char *)&prec->sevr - (char *)prec);
  pdbRecordType->papFldDes[19]->size=sizeof(prec->nsta);
  pdbRecordType->papFldDes[19]->offset=(short)((char *)&prec->nsta - (char *)prec);
  pdbRecordType->papFldDes[20]->size=sizeof(prec->nsev);
  pdbRecordType->papFldDes[20]->offset=(short)((char *)&prec->nsev - (char *)prec);
  pdbRecordType->papFldDes[21]->size=sizeof(prec->acks);
  pdbRecordType->papFldDes[21]->offset=(short)((char *)&prec->acks - (char *)prec);
  pdbRecordType->papFldDes[22]->size=sizeof(prec->ackt);
  pdbRecordType->papFldDes[22]->offset=(short)((char *)&prec->ackt - (char *)prec);
  pdbRecordType->papFldDes[23]->size=sizeof(prec->diss);
  pdbRecordType->papFldDes[23]->offset=(short)((char *)&prec->diss - (char *)prec);
  pdbRecordType->papFldDes[24]->size=sizeof(prec->lcnt);
  pdbRecordType->papFldDes[24]->offset=(short)((char *)&prec->lcnt - (char *)prec);
  pdbRecordType->papFldDes[25]->size=sizeof(prec->pact);
  pdbRecordType->papFldDes[25]->offset=(short)((char *)&prec->pact - (char *)prec);
  pdbRecordType->papFldDes[26]->size=sizeof(prec->putf);
  pdbRecordType->papFldDes[26]->offset=(short)((char *)&prec->putf - (char *)prec);
  pdbRecordType->papFldDes[27]->size=sizeof(prec->rpro);
  pdbRecordType->papFldDes[27]->offset=(short)((char *)&prec->rpro - (char *)prec);
  pdbRecordType->papFldDes[28]->size=sizeof(prec->asp);
  pdbRecordType->papFldDes[28]->offset=(short)((char *)&prec->asp - (char *)prec);
  pdbRecordType->papFldDes[29]->size=sizeof(prec->ppn);
  pdbRecordType->papFldDes[29]->offset=(short)((char *)&prec->ppn - (char *)prec);
  pdbRecordType->papFldDes[30]->size=sizeof(prec->ppnn);
  pdbRecordType->papFldDes[30]->offset=(short)((char *)&prec->ppnn - (char *)prec);
  pdbRecordType->papFldDes[31]->size=sizeof(prec->spvt);
  pdbRecordType->papFldDes[31]->offset=(short)((char *)&prec->spvt - (char *)prec);
  pdbRecordType->papFldDes[32]->size=sizeof(prec->rset);
  pdbRecordType->papFldDes[32]->offset=(short)((char *)&prec->rset - (char *)prec);
  pdbRecordType->papFldDes[33]->size=sizeof(prec->dset);
  pdbRecordType->papFldDes[33]->offset=(short)((char *)&prec->dset - (char *)prec);
  pdbRecordType->papFldDes[34]->size=sizeof(prec->dpvt);
  pdbRecordType->papFldDes[34]->offset=(short)((char *)&prec->dpvt - (char *)prec);
  pdbRecordType->papFldDes[35]->size=sizeof(prec->rdes);
  pdbRecordType->papFldDes[35]->offset=(short)((char *)&prec->rdes - (char *)prec);
  pdbRecordType->papFldDes[36]->size=sizeof(prec->lset);
  pdbRecordType->papFldDes[36]->offset=(short)((char *)&prec->lset - (char *)prec);
  pdbRecordType->papFldDes[37]->size=sizeof(prec->prio);
  pdbRecordType->papFldDes[37]->offset=(short)((char *)&prec->prio - (char *)prec);
  pdbRecordType->papFldDes[38]->size=sizeof(prec->tpro);
  pdbRecordType->papFldDes[38]->offset=(short)((char *)&prec->tpro - (char *)prec);
  pdbRecordType->papFldDes[39]->size=sizeof(prec->bkpt);
  pdbRecordType->papFldDes[39]->offset=(short)((char *)&prec->bkpt - (char *)prec);
  pdbRecordType->papFldDes[40]->size=sizeof(prec->udf);
  pdbRecordType->papFldDes[40]->offset=(short)((char *)&prec->udf - (char *)prec);
  pdbRecordType->papFldDes[41]->size=sizeof(prec->time);
  pdbRecordType->papFldDes[41]->offset=(short)((char *)&prec->time - (char *)prec);
  pdbRecordType->papFldDes[42]->size=sizeof(prec->flnk);
  pdbRecordType->papFldDes[42]->offset=(short)((char *)&prec->flnk - (char *)prec);
  pdbRecordType->papFldDes[43]->size=sizeof(prec->val);
  pdbRecordType->papFldDes[43]->offset=(short)((char *)&prec->val - (char *)prec);
  pdbRecordType->papFldDes[44]->size=sizeof(prec->nobt);
  pdbRecordType->papFldDes[44]->offset=(short)((char *)&prec->nobt - (char *)prec);
  pdbRecordType->papFldDes[45]->size=sizeof(prec->inp);
  pdbRecordType->papFldDes[45]->offset=(short)((char *)&prec->inp - (char *)prec);
  pdbRecordType->papFldDes[46]->size=sizeof(prec->zrvl);
  pdbRecordType->papFldDes[46]->offset=(short)((char *)&prec->zrvl - (char *)prec);
  pdbRecordType->papFldDes[47]->size=sizeof(prec->onvl);
  pdbRecordType->papFldDes[47]->offset=(short)((char *)&prec->onvl - (char *)prec);
  pdbRecordType->papFldDes[48]->size=sizeof(prec->twvl);
  pdbRecordType->papFldDes[48]->offset=(short)((char *)&prec->twvl - (char *)prec);
  pdbRecordType->papFldDes[49]->size=sizeof(prec->thvl);
  pdbRecordType->papFldDes[49]->offset=(short)((char *)&prec->thvl - (char *)prec);
  pdbRecordType->papFldDes[50]->size=sizeof(prec->frvl);
  pdbRecordType->papFldDes[50]->offset=(short)((char *)&prec->frvl - (char *)prec);
  pdbRecordType->papFldDes[51]->size=sizeof(prec->fvvl);
  pdbRecordType->papFldDes[51]->offset=(short)((char *)&prec->fvvl - (char *)prec);
  pdbRecordType->papFldDes[52]->size=sizeof(prec->sxvl);
  pdbRecordType->papFldDes[52]->offset=(short)((char *)&prec->sxvl - (char *)prec);
  pdbRecordType->papFldDes[53]->size=sizeof(prec->svvl);
  pdbRecordType->papFldDes[53]->offset=(short)((char *)&prec->svvl - (char *)prec);
  pdbRecordType->papFldDes[54]->size=sizeof(prec->eivl);
  pdbRecordType->papFldDes[54]->offset=(short)((char *)&prec->eivl - (char *)prec);
  pdbRecordType->papFldDes[55]->size=sizeof(prec->nivl);
  pdbRecordType->papFldDes[55]->offset=(short)((char *)&prec->nivl - (char *)prec);
  pdbRecordType->papFldDes[56]->size=sizeof(prec->tevl);
  pdbRecordType->papFldDes[56]->offset=(short)((char *)&prec->tevl - (char *)prec);
  pdbRecordType->papFldDes[57]->size=sizeof(prec->elvl);
  pdbRecordType->papFldDes[57]->offset=(short)((char *)&prec->elvl - (char *)prec);
  pdbRecordType->papFldDes[58]->size=sizeof(prec->tvvl);
  pdbRecordType->papFldDes[58]->offset=(short)((char *)&prec->tvvl - (char *)prec);
  pdbRecordType->papFldDes[59]->size=sizeof(prec->ttvl);
  pdbRecordType->papFldDes[59]->offset=(short)((char *)&prec->ttvl - (char *)prec);
  pdbRecordType->papFldDes[60]->size=sizeof(prec->ftvl);
  pdbRecordType->papFldDes[60]->offset=(short)((char *)&prec->ftvl - (char *)prec);
  pdbRecordType->papFldDes[61]->size=sizeof(prec->ffvl);
  pdbRecordType->papFldDes[61]->offset=(short)((char *)&prec->ffvl - (char *)prec);
  pdbRecordType->papFldDes[62]->size=sizeof(prec->ssvl);
  pdbRecordType->papFldDes[62]->offset=(short)((char *)&prec->ssvl - (char *)prec);
  pdbRecordType->papFldDes[63]->size=sizeof(prec->snvl);
  pdbRecordType->papFldDes[63]->offset=(short)((char *)&prec->snvl - (char *)prec);
  pdbRecordType->papFldDes[64]->size=sizeof(prec->etvl);
  pdbRecordType->papFldDes[64]->offset=(short)((char *)&prec->etvl - (char *)prec);
  pdbRecordType->papFldDes[65]->size=sizeof(prec->ntvl);
  pdbRecordType->papFldDes[65]->offset=(short)((char *)&prec->ntvl - (char *)prec);
  pdbRecordType->papFldDes[66]->size=sizeof(prec->wyvl);
  pdbRecordType->papFldDes[66]->offset=(short)((char *)&prec->wyvl - (char *)prec);
  pdbRecordType->papFldDes[67]->size=sizeof(prec->wovl);
  pdbRecordType->papFldDes[67]->offset=(short)((char *)&prec->wovl - (char *)prec);
  pdbRecordType->papFldDes[68]->size=sizeof(prec->wtvl);
  pdbRecordType->papFldDes[68]->offset=(short)((char *)&prec->wtvl - (char *)prec);
  pdbRecordType->papFldDes[69]->size=sizeof(prec->whvl);
  pdbRecordType->papFldDes[69]->offset=(short)((char *)&prec->whvl - (char *)prec);
  pdbRecordType->papFldDes[70]->size=sizeof(prec->zrst);
  pdbRecordType->papFldDes[70]->offset=(short)((char *)&prec->zrst - (char *)prec);
  pdbRecordType->papFldDes[71]->size=sizeof(prec->onst);
  pdbRecordType->papFldDes[71]->offset=(short)((char *)&prec->onst - (char *)prec);
  pdbRecordType->papFldDes[72]->size=sizeof(prec->twst);
  pdbRecordType->papFldDes[72]->offset=(short)((char *)&prec->twst - (char *)prec);
  pdbRecordType->papFldDes[73]->size=sizeof(prec->thst);
  pdbRecordType->papFldDes[73]->offset=(short)((char *)&prec->thst - (char *)prec);
  pdbRecordType->papFldDes[74]->size=sizeof(prec->frst);
  pdbRecordType->papFldDes[74]->offset=(short)((char *)&prec->frst - (char *)prec);
  pdbRecordType->papFldDes[75]->size=sizeof(prec->fvst);
  pdbRecordType->papFldDes[75]->offset=(short)((char *)&prec->fvst - (char *)prec);
  pdbRecordType->papFldDes[76]->size=sizeof(prec->sxst);
  pdbRecordType->papFldDes[76]->offset=(short)((char *)&prec->sxst - (char *)prec);
  pdbRecordType->papFldDes[77]->size=sizeof(prec->svst);
  pdbRecordType->papFldDes[77]->offset=(short)((char *)&prec->svst - (char *)prec);
  pdbRecordType->papFldDes[78]->size=sizeof(prec->eist);
  pdbRecordType->papFldDes[78]->offset=(short)((char *)&prec->eist - (char *)prec);
  pdbRecordType->papFldDes[79]->size=sizeof(prec->nist);
  pdbRecordType->papFldDes[79]->offset=(short)((char *)&prec->nist - (char *)prec);
  pdbRecordType->papFldDes[80]->size=sizeof(prec->test);
  pdbRecordType->papFldDes[80]->offset=(short)((char *)&prec->test - (char *)prec);
  pdbRecordType->papFldDes[81]->size=sizeof(prec->elst);
  pdbRecordType->papFldDes[81]->offset=(short)((char *)&prec->elst - (char *)prec);
  pdbRecordType->papFldDes[82]->size=sizeof(prec->tvst);
  pdbRecordType->papFldDes[82]->offset=(short)((char *)&prec->tvst - (char *)prec);
  pdbRecordType->papFldDes[83]->size=sizeof(prec->ttst);
  pdbRecordType->papFldDes[83]->offset=(short)((char *)&prec->ttst - (char *)prec);
  pdbRecordType->papFldDes[84]->size=sizeof(prec->ftst);
  pdbRecordType->papFldDes[84]->offset=(short)((char *)&prec->ftst - (char *)prec);
  pdbRecordType->papFldDes[85]->size=sizeof(prec->ffst);
  pdbRecordType->papFldDes[85]->offset=(short)((char *)&prec->ffst - (char *)prec);
  pdbRecordType->papFldDes[86]->size=sizeof(prec->ssst);
  pdbRecordType->papFldDes[86]->offset=(short)((char *)&prec->ssst - (char *)prec);
  pdbRecordType->papFldDes[87]->size=sizeof(prec->snst);
  pdbRecordType->papFldDes[87]->offset=(short)((char *)&prec->snst - (char *)prec);
  pdbRecordType->papFldDes[88]->size=sizeof(prec->etst);
  pdbRecordType->papFldDes[88]->offset=(short)((char *)&prec->etst - (char *)prec);
  pdbRecordType->papFldDes[89]->size=sizeof(prec->ntst);
  pdbRecordType->papFldDes[89]->offset=(short)((char *)&prec->ntst - (char *)prec);
  pdbRecordType->papFldDes[90]->size=sizeof(prec->wyst);
  pdbRecordType->papFldDes[90]->offset=(short)((char *)&prec->wyst - (char *)prec);
  pdbRecordType->papFldDes[91]->size=sizeof(prec->wost);
  pdbRecordType->papFldDes[91]->offset=(short)((char *)&prec->wost - (char *)prec);
  pdbRecordType->papFldDes[92]->size=sizeof(prec->wtst);
  pdbRecordType->papFldDes[92]->offset=(short)((char *)&prec->wtst - (char *)prec);
  pdbRecordType->papFldDes[93]->size=sizeof(prec->whst);
  pdbRecordType->papFldDes[93]->offset=(short)((char *)&prec->whst - (char *)prec);
  pdbRecordType->papFldDes[94]->size=sizeof(prec->zrsv);
  pdbRecordType->papFldDes[94]->offset=(short)((char *)&prec->zrsv - (char *)prec);
  pdbRecordType->papFldDes[95]->size=sizeof(prec->onsv);
  pdbRecordType->papFldDes[95]->offset=(short)((char *)&prec->onsv - (char *)prec);
  pdbRecordType->papFldDes[96]->size=sizeof(prec->twsv);
  pdbRecordType->papFldDes[96]->offset=(short)((char *)&prec->twsv - (char *)prec);
  pdbRecordType->papFldDes[97]->size=sizeof(prec->thsv);
  pdbRecordType->papFldDes[97]->offset=(short)((char *)&prec->thsv - (char *)prec);
  pdbRecordType->papFldDes[98]->size=sizeof(prec->frsv);
  pdbRecordType->papFldDes[98]->offset=(short)((char *)&prec->frsv - (char *)prec);
  pdbRecordType->papFldDes[99]->size=sizeof(prec->fvsv);
  pdbRecordType->papFldDes[99]->offset=(short)((char *)&prec->fvsv - (char *)prec);
  pdbRecordType->papFldDes[100]->size=sizeof(prec->sxsv);
  pdbRecordType->papFldDes[100]->offset=(short)((char *)&prec->sxsv - (char *)prec);
  pdbRecordType->papFldDes[101]->size=sizeof(prec->svsv);
  pdbRecordType->papFldDes[101]->offset=(short)((char *)&prec->svsv - (char *)prec);
  pdbRecordType->papFldDes[102]->size=sizeof(prec->eisv);
  pdbRecordType->papFldDes[102]->offset=(short)((char *)&prec->eisv - (char *)prec);
  pdbRecordType->papFldDes[103]->size=sizeof(prec->nisv);
  pdbRecordType->papFldDes[103]->offset=(short)((char *)&prec->nisv - (char *)prec);
  pdbRecordType->papFldDes[104]->size=sizeof(prec->tesv);
  pdbRecordType->papFldDes[104]->offset=(short)((char *)&prec->tesv - (char *)prec);
  pdbRecordType->papFldDes[105]->size=sizeof(prec->elsv);
  pdbRecordType->papFldDes[105]->offset=(short)((char *)&prec->elsv - (char *)prec);
  pdbRecordType->papFldDes[106]->size=sizeof(prec->tvsv);
  pdbRecordType->papFldDes[106]->offset=(short)((char *)&prec->tvsv - (char *)prec);
  pdbRecordType->papFldDes[107]->size=sizeof(prec->ttsv);
  pdbRecordType->papFldDes[107]->offset=(short)((char *)&prec->ttsv - (char *)prec);
  pdbRecordType->papFldDes[108]->size=sizeof(prec->ftsv);
  pdbRecordType->papFldDes[108]->offset=(short)((char *)&prec->ftsv - (char *)prec);
  pdbRecordType->papFldDes[109]->size=sizeof(prec->ffsv);
  pdbRecordType->papFldDes[109]->offset=(short)((char *)&prec->ffsv - (char *)prec);
  pdbRecordType->papFldDes[110]->size=sizeof(prec->sssv);
  pdbRecordType->papFldDes[110]->offset=(short)((char *)&prec->sssv - (char *)prec);
  pdbRecordType->papFldDes[111]->size=sizeof(prec->snsv);
  pdbRecordType->papFldDes[111]->offset=(short)((char *)&prec->snsv - (char *)prec);
  pdbRecordType->papFldDes[112]->size=sizeof(prec->etsv);
  pdbRecordType->papFldDes[112]->offset=(short)((char *)&prec->etsv - (char *)prec);
  pdbRecordType->papFldDes[113]->size=sizeof(prec->ntsv);
  pdbRecordType->papFldDes[113]->offset=(short)((char *)&prec->ntsv - (char *)prec);
  pdbRecordType->papFldDes[114]->size=sizeof(prec->wysv);
  pdbRecordType->papFldDes[114]->offset=(short)((char *)&prec->wysv - (char *)prec);
  pdbRecordType->papFldDes[115]->size=sizeof(prec->wosv);
  pdbRecordType->papFldDes[115]->offset=(short)((char *)&prec->wosv - (char *)prec);
  pdbRecordType->papFldDes[116]->size=sizeof(prec->wtsv);
  pdbRecordType->papFldDes[116]->offset=(short)((char *)&prec->wtsv - (char *)prec);
  pdbRecordType->papFldDes[117]->size=sizeof(prec->whsv);
  pdbRecordType->papFldDes[117]->offset=(short)((char *)&prec->whsv - (char *)prec);
  pdbRecordType->papFldDes[118]->size=sizeof(prec->unsv);
  pdbRecordType->papFldDes[118]->offset=(short)((char *)&prec->unsv - (char *)prec);
  pdbRecordType->papFldDes[119]->size=sizeof(prec->cosv);
  pdbRecordType->papFldDes[119]->offset=(short)((char *)&prec->cosv - (char *)prec);
  pdbRecordType->papFldDes[120]->size=sizeof(prec->rval);
  pdbRecordType->papFldDes[120]->offset=(short)((char *)&prec->rval - (char *)prec);
  pdbRecordType->papFldDes[121]->size=sizeof(prec->oraw);
  pdbRecordType->papFldDes[121]->offset=(short)((char *)&prec->oraw - (char *)prec);
  pdbRecordType->papFldDes[122]->size=sizeof(prec->mask);
  pdbRecordType->papFldDes[122]->offset=(short)((char *)&prec->mask - (char *)prec);
  pdbRecordType->papFldDes[123]->size=sizeof(prec->mlst);
  pdbRecordType->papFldDes[123]->offset=(short)((char *)&prec->mlst - (char *)prec);
  pdbRecordType->papFldDes[124]->size=sizeof(prec->lalm);
  pdbRecordType->papFldDes[124]->offset=(short)((char *)&prec->lalm - (char *)prec);
  pdbRecordType->papFldDes[125]->size=sizeof(prec->sdef);
  pdbRecordType->papFldDes[125]->offset=(short)((char *)&prec->sdef - (char *)prec);
  pdbRecordType->papFldDes[126]->size=sizeof(prec->shft);
  pdbRecordType->papFldDes[126]->offset=(short)((char *)&prec->shft - (char *)prec);
  pdbRecordType->papFldDes[127]->size=sizeof(prec->siol);
  pdbRecordType->papFldDes[127]->offset=(short)((char *)&prec->siol - (char *)prec);
  pdbRecordType->papFldDes[128]->size=sizeof(prec->sval);
  pdbRecordType->papFldDes[128]->offset=(short)((char *)&prec->sval - (char *)prec);
  pdbRecordType->papFldDes[129]->size=sizeof(prec->siml);
  pdbRecordType->papFldDes[129]->offset=(short)((char *)&prec->siml - (char *)prec);
  pdbRecordType->papFldDes[130]->size=sizeof(prec->simm);
  pdbRecordType->papFldDes[130]->offset=(short)((char *)&prec->simm - (char *)prec);
  pdbRecordType->papFldDes[131]->size=sizeof(prec->sims);
  pdbRecordType->papFldDes[131]->offset=(short)((char *)&prec->sims - (char *)prec);
    pdbRecordType->rec_size = sizeof(*prec);
    return(0);
}
epicsExportRegistrar(mbbipRecordSizeOffset);
#endif /*GEN_SIZE_OFFSET*/
