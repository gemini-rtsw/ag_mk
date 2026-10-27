[schematic2]
uniq 89
[tools]
[detail]
w 1752 2027 100 0 n#68 ecars.oiwfsC.FLNK 1760 2016 1792 2016 1792 768 junction
w 840 347 100 0 n#68 agSeqCarOiwfs.agSeqCarOiwfs#84.FLNK 832 336 896 336 896 768 junction
w 840 1195 100 0 n#68 agSeqCarSubsys.agSeqCarSubsys#58.FLNK 832 1184 896 1184 junction
w 840 1611 100 0 n#68 agSeqCarSubsys.agSeqCarSubsys#57.FLNK 832 1600 896 1600 junction
w 840 2027 100 0 n#68 agSeqCarSubsys.agSeqCarSubsys#39.FLNK 832 2016 896 2016 896 768 junction
w 1440 779 100 0 n#68 agSeqCarSubsys.agSeqCarSubsys#59.FLNK 832 768 2096 768 egenSubD.combineCar.SLNK
w 1952 1323 100 0 n#88 ecars.oiwfsC.VAL 1760 2240 1856 2240 1856 1312 2096 1312 egenSubD.combineCar.INPF
w 1936 1003 100 0 n#87 ecars.oiwfsC.OMSS 1760 2176 1824 2176 1824 992 2096 992 egenSubD.combineCar.INPP
w 224 539 100 0 n#86 inhier.OIWFS.P 176 528 320 528 agSeqCarOiwfs.agSeqCarOiwfs#84.OIWFS
w 2416 1451 100 0 n#83 egenSubD.combineCar.OUTA 2384 1440 2496 1440 2496 1312 2608 1312 ecars.activeC.IMSS
w 2472 1387 100 0 n#82 egenSubD.combineCar.OUTB 2384 1376 2608 1376 ecars.activeC.IVAL
w 1664 1355 100 0 n#79 agSeqCarOiwfs.agSeqCarOiwfs#84.CAR 832 528 1280 528 1280 1344 2096 1344 egenSubD.combineCar.INPE
w 1648 1387 100 0 n#78 agSeqCarSubsys.agSeqCarSubsys#59.CAR 832 960 1248 960 1248 1376 2096 1376 egenSubD.combineCar.INPD
w 1632 1419 100 0 n#77 agSeqCarSubsys.agSeqCarSubsys#58.CAR 832 1376 1216 1376 1216 1408 2096 1408 egenSubD.combineCar.INPC
w 1632 1451 100 0 n#76 agSeqCarSubsys.agSeqCarSubsys#57.CAR 832 1792 1216 1792 1216 1440 2096 1440 egenSubD.combineCar.INPB
w 1616 1483 100 0 n#75 agSeqCarSubsys.agSeqCarSubsys#39.CAR 832 2208 1184 2208 1184 1472 2096 1472 egenSubD.combineCar.INPA
w 1536 1035 100 0 n#74 agSeqCarOiwfs.agSeqCarOiwfs#84.MESS 832 464 1024 464 1024 1024 2096 1024 egenSubD.combineCar.INPO
w 1520 1067 100 0 n#73 agSeqCarSubsys.agSeqCarSubsys#59.MESS 832 896 992 896 992 1056 2096 1056 egenSubD.combineCar.INPN
w 1520 1099 100 0 n#71 agSeqCarSubsys.agSeqCarSubsys#58.MESS 832 1312 992 1312 992 1088 2096 1088 egenSubD.combineCar.INPM
w 1504 1131 100 0 n#70 agSeqCarSubsys.agSeqCarSubsys#57.MESS 832 1728 960 1728 960 1120 2096 1120 egenSubD.combineCar.INPL
w 1488 1163 100 0 n#69 agSeqCarSubsys.agSeqCarSubsys#39.MESS 832 2144 928 2144 928 1152 2096 1152 egenSubD.combineCar.INPK
w 224 971 100 0 n#65 inhier.PWFS2.P 176 960 320 960 agSeqCarSubsys.agSeqCarSubsys#59.LOADED
w 224 1387 100 0 n#64 inhier.PWFS1.P 176 1376 320 1376 agSeqCarSubsys.agSeqCarSubsys#58.LOADED
w 224 1803 100 0 n#63 inhier.OIDC.P 176 1792 320 1792 agSeqCarSubsys.agSeqCarSubsys#57.LOADED
w 224 2219 100 0 n#62 inhier.CC.P 176 2208 320 2208 agSeqCarSubsys.agSeqCarSubsys#39.LOADED
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2656 80 100 0 Combine CC and WFS activeC status
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqCarCombine.sch,v 1.5 2000/07/21 11:14:42 cjm Exp $
s 2272 2144 100 0 If any of the CAR records are processed then this causes 
s 2272 2112 100 0 the record "combine" to process. It combines the CAR status
s 2272 2080 100 0 and messages of the input CARs to generate a single overall
s 2272 2048 100 0 activeC CAR status for the A&G.
[cell use]
use agSeqCarOiwfs 320 279 100 0 agSeqCarOiwfs#84
xform 0 576 432
p 384 256 100 0 1 seta:subsys oi
p 384 224 100 0 1 setb:top $(top)$(subsys)
use ecars 1440 1959 100 0 oiwfsC
xform 0 1600 2128
p 1472 2304 100 0 -1 DESC:CAR record for oiwfsSel
p 1552 1952 100 1024 0 name:$(ag)$(I)
use ecars 2632 1096 100 0 activeC
xform 0 2768 1264
p 2672 1438 100 0 -1 DESC:A&G activeC record
p 2720 1088 100 1024 0 name:$(ag)$(I)
use agSeqCarSubsys 440 616 100 0 agSeqCarSubsys#59
xform 0 576 864
p 384 704 100 0 1 seta:subsys pwfs2
p 384 672 100 0 1 setb:top $(top)$(subsys)
p 384 640 100 0 1 setc:prefix $(subsys):
p 340 589 100 0 0 setd:instru PWFS2
p 384 608 100 0 1 sete:recname activeC
use agSeqCarSubsys 440 1032 100 0 agSeqCarSubsys#58
xform 0 576 1280
p 384 1120 100 0 1 seta:subsys pwfs1
p 384 1088 100 0 1 setb:top $(top)$(subsys)
p 384 1056 100 0 1 setc:prefix $(subsys):
p 384 1024 100 0 0 setd:instru PWFS1
p 384 1024 100 0 1 sete:recname activeC
use agSeqCarSubsys 440 1448 100 0 agSeqCarSubsys#57
xform 0 576 1696
p 384 1536 100 0 1 seta:subsys oiwfs
p 384 1504 100 0 1 setb:top $(top)$(subsys)
p 384 1472 100 0 1 setc:prefix $(subsys):
p 384 1440 100 0 0 setd:instru OIWFSDC
p 384 1440 100 0 1 sete:recname activeC
use agSeqCarSubsys 440 1864 100 0 agSeqCarSubsys#39
xform 0 576 2112
p 384 1952 100 0 1 seta:subsys cc
p 384 1920 100 0 1 setb:top $(top)$(subsys)
p 384 1888 100 0 1 setc:prefix $(ag)$(subsys):
p 340 1837 100 0 0 setd:instru CC
p 384 1856 100 0 1 sete:recname activeC
use inhier 160 487 100 0 OIWFS
xform 0 176 528
use inhier 184 2168 100 0 CC
xform 0 176 2208
use inhier 184 1752 100 0 OIDC
xform 0 176 1792
use inhier 184 920 100 0 PWFS2
xform 0 176 960
use inhier 184 1336 100 0 PWFS1
xform 0 176 1376
use egenSubD 2096 679 100 0 combineCar
xform 0 2240 1104
p 2128 1536 100 0 -1 DESC:Combine all CAR values
p 1873 453 100 0 0 FTA:LONG
p 1873 453 100 0 0 FTB:LONG
p 1873 421 100 0 0 FTC:LONG
p 1873 389 100 0 0 FTD:LONG
p 1873 357 100 0 0 FTE:LONG
p 1873 293 100 0 0 FTF:LONG
p 1873 453 100 0 0 FTK:STRING
p 1873 453 100 0 0 FTL:STRING
p 1873 421 100 0 0 FTM:STRING
p 1873 389 100 0 0 FTN:STRING
p 1873 357 100 0 0 FTO:STRING
p 1873 293 100 0 0 FTP:STRING
p 2240 1472 100 0 -1 FTVA:STRING
p 2240 1408 100 0 -1 FTVB:LONG
p 2160 608 100 0 1 SNAM:agSeqCombineCar
p 2384 1386 75 0 -1 pproc(OUTB):PP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
