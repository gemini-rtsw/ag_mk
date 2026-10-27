[schematic2]
uniq 76
[tools]
[detail]
w 1416 1163 100 0 n#75 elongouts.mark.FLNK 1568 1280 1664 1280 1664 1152 1216 1152 1216 1024 1312 1024 elongouts.start.SLNK
w 856 1259 100 0 n#74 estringouts.cadB.FLNK 448 1248 1312 1248 elongouts.mark.SLNK
w 1232 1058 100 0 n#69 hwin.hwin#71.in 1200 1056 1312 1056 elongouts.start.DOL
w 64 1266 100 0 n#65 inhier.INPB.P -16 1264 192 1264 estringouts.cadB.DOL
w 64 1522 100 0 n#64 inhier.INPA.P -16 1520 192 1520 estringouts.cadA.DOL
w 744 1634 100 0 n#61 efanouts.fan1.LNK3 1328 1872 1440 1872 1440 1632 96 1632 96 1488 192 1488 estringouts.cadA.SLNK
w 296 1346 100 0 n#60 estringouts.cadA.FLNK 448 1504 544 1504 544 1344 96 1344 96 1232 192 1232 estringouts.cadB.SLNK
w 2882 1608 100 0 n#57 eaos.errVal.FLNK 2688 1824 2880 1824 2880 1344 2560 1344 2560 1168 2624 1168 eaos.stopTrig.SLNK
w 2576 1202 100 0 n#54 hwin.hwin#56.in 2576 1200 2624 1200 eaos.stopTrig.DOL
w 2552 1666 100 0 n#53 estringouts.errMess.FLNK 2688 1536 2752 1536 2752 1664 2400 1664 2400 1792 junction
w 2552 1922 100 0 n#53 estringouts.noResp.FLNK 2688 2032 2752 2032 2752 1920 2400 1920 2400 1792 2432 1792 eaos.errVal.SLNK
w 2146 1088 100 0 n#52 efanouts.fan2.FLNK 2032 656 2144 656 2144 1472 1504 1472 1504 1856 1600 1856 agSeqTimeOut.agSeqTimeOut#17.STOP
w 2274 1096 100 0 n#51 efanouts.fan2.LNK1 2032 624 2272 624 2272 1520 2432 1520 estringouts.errMess.SLNK
w 1762 592 100 0 n#50 ecalcs.ecalcs#45.VAL 1696 512 1760 512 1760 624 1840 624 efanouts.fan2.SELL
w 1720 546 100 0 n#49 ecalcs.ecalcs#45.FLNK 1696 544 1792 544 efanouts.fan2.SLNK
w 1256 715 100 0 n#44 inhier.c#43.P 1152 704 1408 704 ecalcs.ecalcs#45.INPA
w 2120 2050 100 0 n#40 agSeqTimeOut.agSeqTimeOut#17.EXPIRED 2048 2048 2240 2048 2240 2016 2432 2016 estringouts.noResp.SLNK
w 1760 1666 100 0 n#38 hwin.hwin#21.in 1760 1664 1808 1664 eaos.startTrig.DOL
w 2856 1506 100 0 n#36 estringouts.errMess.OUT 2688 1504 3072 1504 outhier.c#35.p
w 2856 1762 100 0 n#33 eaos.errVal.OUT 2688 1760 3072 1760 outhier.c#31.p
w 2856 2002 100 0 n#32 estringouts.noResp.OUT 2688 2000 3072 2000 outhier.c#30.p
w 2376 1826 100 0 n#29 hwin.hwin#28.in 2368 1824 2432 1824 eaos.errVal.DOL
w 1616 1634 100 0 n#24 efanouts.fan1.LNK2 1328 1904 1472 1904 1472 1632 1808 1632 eaos.startTrig.SLNK
w 1392 1938 100 0 n#23 efanouts.fan1.LNK1 1328 1936 1504 1936 1504 2048 1600 2048 agSeqTimeOut.agSeqTimeOut#17.START
w 824 1858 100 0 n#19 elongouts.busy.FLNK 608 1856 1088 1856 efanouts.fan1.SLNK
w 456 1954 100 0 n#14 estringouts.null.FLNK 608 2112 704 2112 704 1952 256 1952 256 1824 352 1824 elongouts.busy.SLNK
w 1232 1282 100 0 n#12 hwin.hwin#11.in 1200 1280 1312 1280 elongouts.mark.DOL
w 86 2130 100 0 n#7 inhier.SLNK.P 16 2128 192 2128 192 2096 352 2096 estringouts.null.SLNK
w 278 1858 100 0 n#5 hwin.hwin#4.in 240 1856 352 1856 elongouts.busy.DOL
w 166 2066 100 0 n#2 inhier.SDIS.P 16 2064 352 2064 estringouts.null.SDIS
s 96 928 100 0 in the case where the subsystem command takes no parameters.
s 96 960 100 0 This means that a dummy parameter must be sent with outa or outb
s 96 992 100 0 Note also that an explicit mark directive is not sent
s 96 1024 100 0 so that 0.0 can be substituted when there are no parameters.
s 96 1056 100 0 N.B. the output links must be expressed as a single macro
s 2656 80 100 0 Drive a subsystem CAD
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDriveSubCad.sch,v 1.13 2001/10/30 11:01:12 ajf Exp $
[cell use]
use hwin 1032 1240 100 0 hwin#11
xform 0 1104 1280
p 1011 1272 100 0 -1 val(in):$(CAD_MARK)
use hwin 72 1816 100 0 hwin#4
xform 0 144 1856
p 51 1848 100 0 -1 val(in):$(CAR_BUSY)
use hwin 1592 1624 100 0 hwin#21
xform 0 1664 1664
p 1571 1656 100 0 -1 val(in):1
use hwin 2200 1784 100 0 hwin#28
xform 0 2272 1824
p 2179 1816 100 0 -1 val(in):$(CAR_ERROR)
use hwin 2408 1160 100 0 hwin#56
xform 0 2480 1200
p 2387 1192 100 0 -1 val(in):1
use hwin 1032 1016 100 0 hwin#71
xform 0 1104 1056
p 1011 1048 100 0 -1 val(in):$(CAD_START)
use elongouts 1336 1160 100 0 mark
xform 0 1440 1248
p 1344 1342 100 0 -1 DESC:Mark directive
p 1152 1166 100 0 0 OMSL:closed_loop
p 1680 1214 100 0 -1 def(OUT):$(subcad).DIR
p 1568 1216 75 768 -1 pproc(OUT):CA
use elongouts 376 1736 100 0 busy
xform 0 480 1824
p 384 1918 100 0 -1 DESC:Output BUSY value
p 192 1742 100 0 0 OMSL:closed_loop
p 720 1790 100 0 -1 def(OUT):$(ag)$(subsys)CommSentC.IVAL
p 608 1792 75 768 -1 pproc(OUT):PP
use elongouts 1336 936 100 0 start
xform 0 1440 1024
p 1344 1118 100 0 -1 DESC:Start directive
p 1152 942 100 0 0 OMSL:closed_loop
p 1680 990 100 0 -1 def(OUT):$(subcad).DIR
p 1568 992 75 768 -1 pproc(OUT):CA
use bc200tr -168 -200 -100 0 frame
xform 0 1512 1104
use inhier -8 1224 100 0 INPB
xform 0 -16 1264
use inhier -8 1480 100 0 INPA
xform 0 -16 1520
use inhier 1160 664 100 0 c#43
xform 0 1152 704
use inhier 24 2088 100 0 SLNK
xform 0 16 2128
use inhier 24 2024 100 0 SDIS
xform 0 16 2064
use estringouts 216 1160 100 0 cadB
xform 0 320 1232
p 224 1310 100 0 -1 DESC:CAD B parameter
p 128 1038 100 0 0 OMSL:closed_loop
p 128 1198 100 0 0 VAL:
p 560 1214 100 0 -1 def(OUT):$(subcad).B
use estringouts 216 1416 100 0 cadA
xform 0 320 1488
p 224 1566 100 0 -1 DESC:CAD A parameter
p 128 1294 100 0 0 OMSL:closed_loop
p 128 1454 100 0 0 VAL:
p 560 1470 100 0 -1 def(OUT):$(subcad).A
use estringouts 376 2024 100 0 null
xform 0 480 2096
p 416 2174 100 0 -1 DESC:Empty string
p 512 1934 100 0 0 DISV:0
p 288 1902 100 0 0 OMSL:closed_loop
p 288 2062 100 0 0 VAL:
p 736 2078 100 0 -1 def(OUT):$(ag)$(subsys)CommSentC.IMSS
use estringouts 2456 1944 100 0 noResp
xform 0 2560 2016
p 2448 2094 100 0 -1 DESC:No response string
p 2368 1822 100 0 0 OMSL:closed_loop
p 2368 1982 100 0 0 VAL:No response from $(instru)
p 2768 2030 100 0 -1 def(OUT):$(ag)$(subsys)CommSentC.IMSS
use estringouts 2456 1448 100 0 errMess
xform 0 2560 1520
p 2448 1598 100 0 -1 DESC:Subsys error message
p 2368 1326 100 0 0 OMSL:closed_loop
p 2368 1486 100 0 0 VAL:
p 2400 956 100 0 0 def(DOL):$(subcad).MESS
p 2752 1534 100 0 -1 def(OUT):$(ag)$(subsys)CommSentC.IMSS
use eaos 1832 1544 100 0 startTrig
xform 0 1936 1632
p 1856 1726 100 0 -1 DESC:Trigger timer
p 1552 1614 100 0 0 OMSL:closed_loop
p 1712 1518 100 0 1 def(OUT):$(ag)car:$(subsys)StartTimer.PROC
p 2064 1600 75 768 -1 pproc(OUT):PP
use eaos 2456 1704 100 0 errVal
xform 0 2560 1792
p 2464 1870 100 0 -1 DESC:Write error status
p 2176 1774 100 0 0 OMSL:closed_loop
p 2720 1790 100 0 -1 def(OUT):$(ag)$(subsys)CommSentC.IVAL
p 2688 1760 75 768 -1 pproc(OUT):PP
use eaos 2648 1080 100 0 stopTrig
xform 0 2752 1168
p 2672 1262 100 0 -1 DESC:Trigger timer
p 2368 1150 100 0 0 OMSL:closed_loop
p 2528 1054 100 0 1 def(OUT):$(ag)car:$(subsys)StopTimer.PROC
p 2880 1136 75 768 -1 pproc(OUT):PP
use efanouts 1816 408 100 0 fan2
xform 0 1912 560
p 1856 704 100 0 1 SELM:Specified
use efanouts 1112 1720 100 0 fan1
xform 0 1208 1872
use ecalcs 1432 232 100 0 ecalcs#45
xform 0 1552 496
p 1488 446 100 0 1 CALC:A<0?1:0
p 1176 728 100 0 -1 def(INPA):$(subcad).VAL
p 1520 224 100 1024 -1 name:$(top)calc
p 1376 704 75 1280 -1 pproc(INPA):CPP
use outhier 3064 1960 100 0 c#30
xform 0 3056 2000
use outhier 3064 1720 100 0 c#31
xform 0 3056 1760
use outhier 3064 1464 100 0 c#35
xform 0 3056 1504
use agSeqTimeOut 1624 1800 100 0 agSeqTimeOut#17
xform 0 1824 1952
p 1824 1854 100 0 -1 seta:timeout 3.0
[comments]
