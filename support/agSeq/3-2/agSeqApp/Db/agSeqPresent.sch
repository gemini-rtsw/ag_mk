[schematic2]
uniq 68
[tools]
[detail]
w 256 875 100 0 n#67 inhier.PWFS2.P 208 864 352 864 agSeqSubsysPresent.agSeqSubsysPresent#46.LOADED
w 256 1323 100 0 n#66 inhier.PWFS1.P 208 1312 352 1312 agSeqSubsysPresent.agSeqSubsysPresent#45.LOADED
w 256 1771 100 0 n#65 inhier.OIDC.P 208 1760 352 1760 agSeqSubsysPresent.agSeqSubsysPresent#34.LOADED
w 248 2219 100 0 n#64 inhier.CC.P 192 2208 352 2208 agSeqSubsysPresent.agSeqSubsysPresent#33.LOADED
w 256 427 100 0 n#62 inhier.OIWFS.P 208 416 352 416 agSeqOiPresent.agSeqOiPresent#51.OIWFS
w 1112 299 100 0 n#60 agSeqOiPresent.agSeqOiPresent#51.DISV 992 288 1280 288 1280 1328 1504 1328 esels.disablePresent.INPE
w 1096 747 100 0 n#59 agSeqSubsysPresent.agSeqSubsysPresent#46.DISV 992 736 1248 736 1248 1360 1504 1360 esels.disablePresent.INPD
w 1096 2091 100 0 n#58 agSeqSubsysPresent.agSeqSubsysPresent#33.DISV 992 2080 1248 2080 1248 1456 1504 1456 esels.disablePresent.INPA
w 1336 1435 100 0 n#57 agSeqSubsysPresent.agSeqSubsysPresent#34.DISV 992 1632 1216 1632 1216 1424 1504 1424 esels.disablePresent.INPB
w 1336 1403 100 0 n#56 agSeqSubsysPresent.agSeqSubsysPresent#45.DISV 992 1184 1216 1184 1216 1392 1504 1392 esels.disablePresent.INPC
w 1856 1291 100 0 n#55 esels.disablePresent.VAL 1792 1280 1968 1280 1968 1056 2096 1056 ecalcs.present.SDIS
w 1992 1099 100 0 n#54 esels.disablePresent.FLNK 1792 1312 1936 1312 1936 1088 2096 1088 ecalcs.present.SLNK
w 2190 1602 100 0 n#1 ecalcs.present.VAL 2384 1280 2480 1280 2480 1600 1936 1600 1936 1472 2096 1472 ecalcs.present.INPA
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2672 80 100 0 Handle presence of A&G subsystems
s 2432 2336 100 0 $Id: agSeqPresent.sch,v 1.5 2000/06/12 03:00:05 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
[cell use]
use esels 1504 999 100 0 disablePresent
xform 0 1648 1264
p 1440 1552 100 0 -1 DESC:Disable/enable present record
p 1696 1056 100 0 1 SCAN:1 second
p 1696 1104 100 0 1 SELM:High Signal
use inhier 192 375 100 0 OIWFS
xform 0 208 416
use inhier 200 2168 100 0 CC
xform 0 192 2208
use inhier 216 1720 100 0 OIDC
xform 0 208 1760
use inhier 192 1271 100 0 PWFS1
xform 0 208 1312
use inhier 192 823 100 0 PWFS2
xform 0 208 864
use agSeqOiPresent 352 231 100 0 agSeqOiPresent#51
xform 0 672 368
use agSeqSubsysPresent 312 616 100 0 agSeqSubsysPresent#46
xform 0 672 816
p 416 656 100 0 1 seta:subnam pwfs2
p 416 608 100 0 1 setb:top $(top)$(subnam)
p 416 560 100 0 1 setc:subsys $(pwfs2)
p 416 528 100 0 1 setd:present $(subsys)present
use agSeqSubsysPresent 312 1064 100 0 agSeqSubsysPresent#45
xform 0 672 1264
p 416 1104 100 0 1 seta:subnam pwfs1
p 416 1056 100 0 1 setb:top $(top)$(subnam)
p 416 1008 100 0 1 setc:subsys $(pwfs1)
p 416 976 100 0 1 setd:present $(subsys)present
use agSeqSubsysPresent 312 1960 100 0 agSeqSubsysPresent#33
xform 0 672 2160
p 416 2016 100 0 1 seta:subnam cc
p 416 1968 100 0 1 setb:top $(top)$(subnam)
p 416 1920 100 0 1 setc:subsys $(ag)$(subnam):
p 416 1888 100 0 1 setd:present $(subsys)present
use agSeqSubsysPresent 312 1512 100 0 agSeqSubsysPresent#34
xform 0 672 1712
p 416 1552 100 0 1 seta:subnam oiwfs
p 416 1504 100 0 1 setb:top $(top)$(subnam)
p 416 1456 100 0 1 setc:subsys $(oiwfs)
p 436 1436 100 0 1 setd:present $(oiwfs)present
use ecalcs 2120 1000 100 0 present
xform 0 2240 1264
p 2288 1102 100 0 1 CALC:(A+1)%1000
p 2080 1534 100 0 -1 DESC:Heartbeat record for TCS
p 2288 1056 100 0 1 DISV:1
p 2288 1070 100 0 0 SCAN:Passive
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
