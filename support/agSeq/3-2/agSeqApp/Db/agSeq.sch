[schematic2]
uniq 15
[tools]
[detail]
w 2520 1051 100 0 n#1 agSeqPorts.agSeqPorts#42.GPI 2464 1040 2624 1040 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.GPIPORT
w 1992 1995 100 0 n#2 agSeqStatus.agSeqStatus#28.CC 2032 704 1984 704 1984 1984 2048 1984 agSeqCommands.agSeqCommands#29.CC
w 1176 1947 100 0 n#2 ebos.ccLoaded.VAL 416 1936 1984 1936 junction
w 1960 1899 100 0 n#3 agSeqStatus.agSeqStatus#28.OIDC 2032 608 1920 608 1920 1888 2048 1888 agSeqCommands.agSeqCommands#29.OIDC
w 1144 1579 100 0 n#3 ebos.oiwfsdcLoaded.VAL 416 1568 1920 1568 junction
w 1032 1483 100 0 n#3 junction 992 1568 992 1472 1120 1472 agSeqOiwfsSel.agSeqOiwfsSel#31.OIDC
w 1832 1643 100 0 n#4 agSeqStatus.agSeqStatus#28.OIWFS 2032 352 1664 352 1664 1632 2048 1632 agSeqCommands.agSeqCommands#29.OIWFS
w 1544 1483 100 0 n#4 agSeqOiwfsSel.agSeqOiwfsSel#31.OIWFS 1472 1472 1664 1472 junction
w 2104 1477 100 0 n#4 junction 1664 1472 2544 1472 2544 1600 2608 1600 agSeqOiwfsCommands.agSeqOiwfsCommands#38.OIWFS
w 1080 875 100 0 n#5 ebos.pwfs2Loaded.VAL 416 864 1792 864 junction
w 1896 1771 100 0 n#5 agSeqStatus.agSeqStatus#28.PWFS2 2032 480 1792 480 1792 1760 2048 1760 agSeqCommands.agSeqCommands#29.PWFS2
w 1112 1227 100 0 n#6 ebos.pwfs1Loaded.VAL 416 1216 1856 1216 junction
w 1928 1835 100 0 n#6 agSeqStatus.agSeqStatus#28.PWFS1 2032 544 1856 544 1856 1824 2048 1824 agSeqCommands.agSeqCommands#29.PWFS1
w 2520 1083 100 0 n#7 agSeqPorts.agSeqPorts#42.GSOAI 2464 1072 2624 1072 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.GSAOIPORT
w 2520 1115 100 0 n#8 agSeqPorts.agSeqPorts#42.NICI 2464 1104 2624 1104 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.NICIPORT
w 2520 1147 100 0 n#9 agSeqPorts.agSeqPorts#42.NIFS 2464 1136 2624 1136 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.NIFSPORT
w 2520 1179 100 0 n#10 agSeqPorts.agSeqPorts#42.F2 2464 1168 2624 1168 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.F2PORT
w 2520 1211 100 0 n#11 agSeqPorts.agSeqPorts#42.NIRI 2464 1200 2624 1200 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.NIRIPORT
w 2520 1243 100 0 n#12 agSeqPorts.agSeqPorts#42.GMOS 2464 1232 2624 1232 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.GMOSPORT
w 2520 1275 100 0 n#13 agSeqPorts.agSeqPorts#42.NIRS 2464 1264 2624 1264 agSeqOiwfsSpecific.agSeqOiwfsSpecific#41.NIRSPORT
w 744 517 100 0 n#14 ebos.hrwfsLoaded.VAL 416 512 1072 512 1072 416 2032 416 agSeqStatus.agSeqStatus#28.HRWFS
s 864 2112 100 0 if any OIWFS is in use.
s 864 2160 100 0 values are used to form the overall A&G status and it selects which
s 864 2208 100 0 subsystems receive commands. It controls which subsystem's status
s 864 2240 100 0 This schematic has three main functions. It controls which A&G
s 2464 80 100 0 Sciences Ltd.
s 2464 112 100 0 Observatory
s 2480 144 100 0 Copyright
s 2672 80 100 0 Root schematic for A&G sequencer
s 2448 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeq.sch,v 1.19 2013/05/29 16:36:37 pedro Exp $
s 560 240 100 0 Each of the xxLoaded records above causes the
s 560 208 100 0 CAR combine records to process. This is done
s 560 176 100 0 to ensure that the CAR values are recalculated whenever a system
s 560 144 100 0 is ignored/included. This is necessary as unlike the other
s 560 112 100 0 status records, the CAR records aren't scanned periodically.
[cell use]
use bc200tr -160 -120 -100 0 frame
xform 0 1520 1184
use ebos 184 776 100 0 pwfs2Loaded
xform 0 288 864
p 192 944 100 0 -1 DESC:Configure for PWFS2
p 224 704 100 0 1 ONAM:Included
p 224 736 100 0 1 ZNAM:Ignored
p 480 816 100 0 -1 def(OUT):$(ag)car:pwfs2combine.PROC
p 416 832 75 768 -1 pproc(OUT):PP
use ebos 184 1128 100 0 pwfs1Loaded
xform 0 288 1216
p 192 1296 100 0 -1 DESC:Configure for PWFS1
p 224 1056 100 0 1 ONAM:Included
p 224 1088 100 0 1 ZNAM:Ignored
p 448 1152 100 0 -1 def(OUT):$(ag)car:pwfs1combine.PROC
p 416 1184 75 768 -1 pproc(OUT):PP
use ebos 184 1848 100 0 ccLoaded
xform 0 288 1936
p 208 2016 100 0 -1 DESC:Configure for CC
p 224 1776 100 0 1 ONAM:Included
p 224 1808 100 0 1 ZNAM:Ignored
p 480 1872 100 0 -1 def(OUT):$(ag)car:cccombine.PROC
p 416 1904 75 768 -1 pproc(OUT):PP
use ebos 184 1480 100 0 oiwfsdcLoaded
xform 0 288 1568
p 128 1648 100 0 -1 DESC:Configure for OIWFS detector controller
p 224 1408 100 0 1 ONAM:Included
p 224 1440 100 0 1 ZNAM:Ignored
p 432 1504 100 0 -1 def(OUT):$(ag)car:oiwfscombine.PROC
p 416 1536 75 768 -1 pproc(OUT):PP
use ebos 160 423 100 0 hrwfsLoaded
xform 0 288 512
p 192 592 100 0 -1 DESC:Configure for HRWFS
p 224 352 100 0 1 ONAM:Included
p 224 384 100 0 1 ZNAM:Ignored
use agSeqTweakOffsets 2624 303 100 0 agSeqTweakOffsets#48
xform 0 2840 552
use agSeqPorts 2112 903 100 0 agSeqPorts#42
xform 0 2288 1120
p 2144 848 100 0 1 seta:top $(top)port:
use agSeqOiwfsSpecific 2616 903 100 0 agSeqOiwfsSpecific#41
xform 0 2832 1168
use agSeqOiwfsCommands 2608 1543 100 0 agSeqOiwfsCommands#38
xform 0 2824 1808
use agSeqOiwfsSel 1152 1223 100 0 agSeqOiwfsSel#31
xform 0 1296 1408
p 1168 1280 100 0 1 seta:top $(top)oiSel:
use agSeqCommands 2048 1575 100 0 agSeqCommands#29
xform 0 2264 1808
use agSeqStatus 2032 295 100 0 agSeqStatus#28
xform 0 2248 528
[comments]
