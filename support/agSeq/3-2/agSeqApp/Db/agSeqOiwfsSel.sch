[schematic2]
uniq 21
[tools]
[detail]
w 275 1496 100 0 n#1 junction 272 1648 272 1344 432 1344 ecalcs.calcMask.INPA
w 1184 1651 100 0 n#1 ecad8.oiwfsSel.VALA 96 1648 2272 1648 outhier.OIWFS.p
w 243 808 100 0 n#1 junction 240 1648 240 -32 352 -32 agSeqOiwfsDcOnlyCad.agSeqOiwfsDcOnlyCad#65.OIWFS
w 293 1260 100 0 n#1 junction 288 1648 288 872 -336 872 -336 448 -288 448 agSeqOiwfsInUse.agSeqOiwfsInUse#68.OIWFS
w 184 355 100 0 n#2 agSeqOiwfsInUse.agSeqOiwfsInUse#68.FLNK 64 352 304 352 304 960 432 960 ecalcs.calcMask.SLNK
w 132 981 100 0 n#3 ecad8.oiwfsSel.STLK 96 976 168 976 168 888 -368 888 -368 352 -288 352 agSeqOiwfsInUse.agSeqOiwfsInUse#68.SLNK
w 152 1459 100 0 n#4 ecad8.oiwfsSel.VALD 96 1456 208 1456 208 -96 352 -96 agSeqOiwfsDcOnlyCad.agSeqOiwfsDcOnlyCad#65.INPA
w 528 1523 100 0 n#5 ecad8.oiwfsSel.VALC 96 1520 960 1520 960 1392 1664 1392 agSeqDriveSubCad.agSeqDriveSubCad#51.INPB
w 552 1587 100 0 n#6 ecad8.oiwfsSel.VALB 96 1584 1008 1584 1008 1456 1664 1456 agSeqDriveSubCad.agSeqDriveSubCad#51.INPA
w 1136 1299 100 0 n#7 efanouts.fan.FLNK 1056 1296 1216 1296 1216 816 272 816 272 -224 352 -224 agSeqOiwfsDcOnlyCad.agSeqOiwfsDcOnlyCad#65.SLNK
w 1608 1523 100 0 n#8 inhier.OIDC.P 1552 1520 1664 1520 agSeqDriveSubCad.agSeqDriveSubCad#51.SDIS
w 1120 1235 100 0 n#9 efanouts.fan.LNK2 1056 1232 1184 1232 1184 848 736 848 736 400 976 400 eseqs.delay.SLNK
w 1360 1267 100 0 n#10 efanouts.fan.LNK1 1056 1264 1664 1264 agSeqDriveSubCad.agSeqDriveSubCad#51.SLNK
w 736 1155 100 0 n#11 ecalcs.calcMask.VAL 720 1152 752 1152 752 1264 864 1264 efanouts.fan.SELL
w 768 1187 100 0 n#12 ecalcs.calcMask.FLNK 720 1184 816 1184 efanouts.fan.SLNK
w 768 659 100 0 n#13 hwin.hwin#4.in 720 656 816 656 816 688 976 688 eseqs.delay.DOL2
w 1352 691 100 0 n#14 eseqs.delay.LNK2 1296 688 1408 688 1408 496 2480 496 outhier.c#26.p
w 1840 755 100 0 n#15 elongouts.busyVal.FLNK 1776 752 1904 752 1904 336 1424 336 1424 64 1520 64 elongouts.trigger.SLNK
w 2128 35 100 0 n#16 elongouts.trigger.OUT 1776 32 2480 32 outhier.c#32.p
w 1456 99 100 0 n#17 hwin.hwin#45.in 1392 96 1520 96 elongouts.trigger.DOL
w 2128 691 100 0 n#18 elongouts.busyVal.OUT 1776 688 2480 688 outhier.c#28.p
w 1408 723 100 0 n#19 eseqs.delay.LNK1 1296 720 1520 720 elongouts.busyVal.SLNK
w 848 723 100 0 n#20 hwin.hwin#16.in 720 720 976 720 eseqs.delay.DOL1
s 160 1808 100 0 Stores the name of the validated WFS
s 1728 1056 100 0 This symbol is triggerred when the selected OIWFS is not NONE
s 672 1696 100 0 The value of OIWFS starts from 0 ( = NONE)
s 2016 2016 100 0 $Id: agSeqOiwfsSel.sch,v 1.12 2013/11/12 18:00:07 gemvx Exp $
s 2032 -176 100 0 Copyright
s 2032 -208 100 0 Observatory
s 2032 -240 100 0 Sciences Ltd.
s 2048 -288 100 0 Chris Mayer
s 2352 -176 150 0 A&G Sequencer
s 2336 -240 100 0 Command to select OIWS
s 672 1968 100 0 The main purpose of this schematic is to provide an index
s 672 1936 100 0 to the OIWFS that is selected. This index is then used
s 672 1904 100 0 by the remainder of the database to select to which
s 672 1872 100 0 instrument to send commands directed at the OIWFS and from which
s 672 1840 100 0 to fetch status.
[cell use]
use bc200tr -560 -456 -100 0 frame
xform 0 1120 848
use agSeqOiwfsInUse -256 295 100 0 agSeqOiwfsInUse#68
xform 0 -112 592
p -208 272 100 0 1 seta:top $(top)inUse:
use agSeqOiwfsDcOnlyCad 352 -281 100 0 agSeqOiwfsDcOnlyCad#65
xform 0 496 16
p 672 -96 100 0 1 seta:cad SO
p 672 -128 100 0 1 setb:snam None
p 672 -160 100 0 1 setc:mask 4095
p 672 -192 100 0 1 setd:gmsubcad detSigOutput
p 672 -224 100 0 1 sete:nirssubcad detSigOutput
p 672 -256 100 0 1 setf:nirisubcad detSigOutput
p 672 -288 100 0 1 setg:f2subcad detSigOutput
p 672 -320 100 0 1 seth:nifssubcad detSigOutput
p 672 -352 100 0 1 seti:nicisubcad detSigOutput
p 672 -384 100 0 1 setj:gpisubcad detSigOutput
use efanouts 816 1047 100 0 fan
xform 0 936 1200
p 816 1120 100 0 1 SELM:Mask
use ecalcs 432 871 100 0 calcMask
xform 0 576 1136
p 592 944 100 0 1 CALC:A=0?2:3
p 336 1392 100 0 -1 DESC:Mask for downstream processing
p 144 1022 100 0 0 EGU:units
use inhier 1536 1479 100 0 OIDC
xform 0 1552 1520
use agSeqDriveSubCad 1664 1207 100 0 agSeqDriveSubCad#51
xform 0 1968 1408
p 1728 1200 100 0 1 seta:top $(top)
p 1728 1168 100 0 1 setb:subsys oiwfs
p 1728 1136 100 0 1 setc:prefix $(oiwfs)
p 1728 1104 100 0 1 setd:outa $(prefix)$(subcad).A
p 2120 1200 100 0 1 sete:outb $(prefix)$(subcad).B
p 2120 1168 100 0 1 setf:instru OIWFSDC
p 2120 1136 100 0 1 setg:subcad oiwfs:prmSelect
use hwin 1200 55 100 0 hwin#45
xform 0 1296 96
p 1203 88 100 0 -1 val(in):1
use hwin 528 679 100 0 hwin#16
xform 0 624 720
p 531 712 100 0 -1 val(in):$(CAR_BUSY)
use hwin 528 615 100 0 hwin#4
xform 0 624 656
p 531 648 100 0 -1 val(in):$(CAR_IDLE)
use elongouts 1520 -25 100 0 trigger
xform 0 1648 64
p 1664 16 100 0 0 OMSL:closed_loop
p 1856 48 100 0 -1 def(OUT):$(ag)car:oiFan.PROC
p 1776 32 75 768 -1 pproc(OUT):PP
use elongouts 1520 631 100 0 busyVal
xform 0 1648 720
p 2048 704 100 0 -1 def(OUT):$(ag)oiwfsC.IVAL
p 1776 688 75 768 -1 pproc(OUT):PP
use outhier 2448 -9 100 0 c#32
xform 0 2464 32
use outhier 2240 1607 100 0 OIWFS
xform 0 2256 1648
use outhier 2448 455 100 0 c#26
xform 0 2464 496
use outhier 2448 647 100 0 c#28
xform 0 2464 688
use eseqs 976 311 100 0 delay
xform 0 1136 560
p 1088 608 100 0 1 DLY1:0.0
p 1088 576 100 0 1 DLY2:1.0
p 592 -1652 100 0 0 DLY3:0.0
p 592 -1684 100 0 0 DLY4:0.0
p 1616 736 100 0 0 def(LNK1):0.0
p 2048 512 100 0 -1 def(LNK2):$(ag)oiwfsC.IVAL
p 1616 608 100 0 0 def(LNK3):0.0
p 1568 544 100 0 0 def(LNK4):0.0
p 1312 720 75 1024 -1 pproc(LNK1):PP
p 1312 688 75 1024 -1 pproc(LNK2):PP
p 1312 656 75 1024 -1 pproc(LNK3):PP
p 1312 624 75 1024 -1 pproc(LNK4):PP
use ecad8 -224 912 100 0 oiwfsSel
xform 0 -64 1392
p -128 1584 100 0 1 FTVA:LONG
p -128 1104 100 0 1 SNAM:agSeqCADoiwfsSel
p -112 880 100 1024 1 name:$(ag)$(I)
[comments]
