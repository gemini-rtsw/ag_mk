[schematic2]
uniq 28
[tools]
[detail]
w 2608 1611 100 0 n#27 ecars.activeC.VAL 2512 1600 2752 1600 outhier.CAR.p
w 2608 1547 100 0 n#26 ecars.activeC.OMSS 2512 1536 2752 1536 outhier.MESS.p
w 2608 1387 100 0 n#25 ecars.activeC.FLNK 2512 1376 2752 1376 outhier.FLNK.p
w 2016 1675 100 0 n#24 egenSub.combine.OUTA 1984 1664 2096 1664 2096 1536 2192 1536 ecars.activeC.IMSS
w 2064 1611 100 0 n#23 egenSub.combine.OUTB 1984 1600 2192 1600 ecars.activeC.IVAL
w 928 875 100 0 n#21 inhier.c#4.P 560 864 1344 864 1344 1344 1696 1344 egenSub.combine.INPF
w 936 1355 100 0 n#20 agSeqCarMonitor.agSeqCarMonitor#1.CSOMSS 640 1344 1280 1344 1280 1408 1696 1408 egenSub.combine.INPE
w 920 1419 100 0 n#19 agSeqCarMonitor.agSeqCarMonitor#1.ACTVAL 640 1408 1248 1408 1248 1472 1696 1472 egenSub.combine.INPD
w 904 1483 100 0 n#18 agSeqCarMonitor.agSeqCarMonitor#1.CSVAL 640 1472 1216 1472 1216 1536 1696 1536 egenSub.combine.INPC
w 1480 1643 100 0 n#16 estringouts.Name.OUT 1104 1104 1312 1104 1312 1632 1696 1632 egenSub.combine.B
w 1464 1003 100 0 n#15 estringouts.Name.FLNK 1104 1136 1280 1136 1280 992 1696 992 egenSub.combine.SLNK
w 1104 1675 100 0 n#14 inhier.LOADED.P 560 1664 1696 1664 egenSub.combine.INPA
w 720 1131 100 0 n#13 agSeqCarMonitor.agSeqCarMonitor#1.FLNK 640 1120 848 1120 estringouts.Name.SLNK
s 1152 2080 100 0 fields are blamk.
s 1152 2112 100 0 message if the overall CAR state is ERR but the input message
s 1152 2144 100 0 for a particular subsystem. The gensub will provide a default error
s 1152 2176 100 0 This schematic combines the activeC and commSentC CAR records
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqCarSubsys.sch,v 1.5 2000/07/21 11:15:32 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Combine subsys CAR values
[cell use]
use outhier 2720 1335 100 0 FLNK
xform 0 2736 1376
use outhier 2720 1495 100 0 MESS
xform 0 2736 1536
use outhier 2720 1559 100 0 CAR
xform 0 2736 1600
use estringouts 848 1047 100 0 Name
xform 0 976 1120
p 864 1216 100 0 -1 DESC:Name of subsystem
p 784 1086 100 0 0 VAL:$(instru)
use inhier 544 823 100 0 c#4
xform 0 560 864
use inhier 544 1623 100 0 LOADED
xform 0 560 1664
use ecars 2192 1319 100 0 activeC
xform 0 2352 1488
use egenSub 1696 903 100 0 combine
xform 0 1840 1328
p 1680 1776 100 0 -1 DESC:Combine A&G subsystem CAR values
p 1473 677 100 0 0 FTA:LONG
p 1473 677 100 0 0 FTB:STRING
p 1473 645 100 0 0 FTC:LONG
p 1473 613 100 0 0 FTD:LONG
p 1473 581 100 0 0 FTE:STRING
p 1473 517 100 0 0 FTF:STRING
p 1473 677 100 0 0 FTVA:STRING
p 1473 677 100 0 0 FTVB:LONG
p 1760 832 100 0 1 SNAM:agSeqSubsysCar
p 768 880 100 0 -1 def(INPF):$(prefix)$(recname).OMSS
p 1984 1610 75 0 -1 pproc(OUTB):PP
use agSeqCarMonitor 320 1063 100 0 agSeqCarMonitor#1
xform 0 480 1312
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
