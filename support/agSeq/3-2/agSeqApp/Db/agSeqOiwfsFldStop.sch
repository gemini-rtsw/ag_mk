[schematic2]
uniq 142
[tools]
[detail]
w 1858 1915 100 0 n#124 estringouts.gmos.OUT 1824 1904 1952 1904 junction
w 1858 1723 100 0 n#124 estringouts.nirs.OUT 1824 1712 1952 1712 junction
w 1858 1531 100 0 n#124 estringouts.niri.OUT 1824 1520 1952 1520 junction
w 1858 1339 100 0 n#124 estringouts.f2.OUT 1824 1328 1952 1328 junction
w 1858 1147 100 0 n#124 estringouts.nifs.OUT 1824 1136 1952 1136 junction
w 1858 955 100 0 n#124 estringouts.nici.OUT 1824 944 1952 944 1952 2128 junction
w 1394 971 100 0 n#141 superfout.fan.LNK7 1008 1600 1280 1600 1280 960 1568 960 estringouts.nici.SLNK
w 1130 1643 100 0 n#140 superfout.fan.LNK6 1008 1632 1312 1632 1312 1152 1568 1152 estringouts.nifs.SLNK
w 1146 1675 100 0 n#137 superfout.fan.LNK5 1008 1664 1344 1664 1344 1344 1568 1344 estringouts.f2.SLNK
w 1162 1707 100 0 n#136 superfout.fan.LNK4 1008 1696 1376 1696 1376 1536 1568 1536 estringouts.niri.SLNK
w 1258 1739 100 0 n#135 superfout.fan.LNK3 1008 1728 1568 1728 estringouts.nirs.SLNK
w 1298 1931 100 0 n#127 superfout.fan.LNK2 1008 1760 1088 1760 1088 1920 1568 1920 estringouts.gmos.SLNK
w 1146 2155 100 0 n#126 superfout.fan.LNK1 1008 1792 1056 1792 1056 2144 1296 2144 estringouts.none.SLNK
w 1994 2139 100 0 n#124 estringouts.none.OUT 1552 2128 2496 2128 estringouts.oiFldStopName.SLNK
w 546 1643 100 0 n#120 ecalcs.calc.VAL 560 1632 592 1632 592 1728 superfout.fan.SELL
w 538 1675 100 0 n#119 ecalcs.calc.FLNK 560 1664 576 1664 576 1504 592 1504 superfout.fan.SLNK
w 136 1835 100 0 n#79 inhier.OIWFS.P 48 1824 272 1824 ecalcs.calc.INPA
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsFldStop.sch,v 1.5 2007/05/18 22:29:22 pedro Exp $
s 2752 144 150 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Fetch OIWFS field stop
[cell use]
use estringouts 1568 887 100 0 nici
xform 0 1696 960
p 1632 1024 100 0 -1 DESC:Name of oiwfs filter
p 1504 766 100 0 0 OMSL:closed_loop
p 1504 926 100 0 0 VAL:
p 1408 1024 100 0 -1 def(DOL):$(ag)noRecord
p 1568 992 75 1280 -1 palrm(DOL):MS
p 1856 944 75 768 -1 palrm(OUT):MS
p 1824 944 75 768 -1 pproc(OUT):PP
use estringouts 1568 1271 100 0 f2
xform 0 1696 1344
p 1632 1408 100 0 -1 DESC:Name of oiwfs filter
p 1504 1150 100 0 0 OMSL:closed_loop
p 1504 1310 100 0 0 VAL:
p 1408 1408 100 0 -1 def(DOL):$(ag)noRecord
p 1568 1376 75 1280 -1 palrm(DOL):MS
p 1856 1328 75 768 -1 palrm(OUT):MS
p 1824 1328 75 768 -1 pproc(OUT):PP
use estringouts 2496 2055 100 0 oiFldStopName
xform 0 2624 2128
p 2528 2208 100 0 -1 DESC:Current OIWFS field stop
p 2432 2094 100 0 0 VAL:
p 2720 2080 100 0 -1 def(OUT):$(sad)oi:fldstopName
p 2608 2048 100 1024 0 name:$(ag)$(I)
p 2784 2112 75 768 -1 palrm(OUT):MS
p 2752 2112 75 768 -1 pproc(OUT):PP
use estringouts 1568 1463 100 0 niri
xform 0 1696 1536
p 1632 1600 100 0 -1 DESC:Name of oiwfs filter
p 1504 1342 100 0 0 OMSL:closed_loop
p 1504 1502 100 0 0 VAL:
p 1408 1600 100 0 -1 def(DOL):$(ag)noRecord
p 1568 1568 75 1280 -1 palrm(DOL):MS
p 1856 1520 75 768 -1 palrm(OUT):MS
p 1824 1520 75 768 -1 pproc(OUT):PP
use estringouts 1568 1655 100 0 nirs
xform 0 1696 1728
p 1632 1792 100 0 -1 DESC:Name of oiwfs filter
p 1504 1534 100 0 0 OMSL:closed_loop
p 1504 1694 100 0 0 VAL:
p 1408 1792 100 0 -1 def(DOL):$(ag)noRecord
p 1568 1760 75 1280 -1 palrm(DOL):MS
p 1856 1712 75 768 -1 palrm(OUT):MS
p 1824 1712 75 768 -1 pproc(OUT):PP
use estringouts 1568 1847 100 0 gmos
xform 0 1696 1920
p 1632 1984 100 0 -1 DESC:Name of oiwfs filter
p 1504 1726 100 0 0 OMSL:closed_loop
p 1504 1886 100 0 0 VAL:
p 1408 1984 100 0 -1 def(DOL):$(ag)noRecord
p 1568 1952 75 1280 -1 palrm(DOL):MS
p 1856 1904 75 768 -1 palrm(OUT):MS
p 1824 1904 75 768 -1 pproc(OUT):PP
use estringouts 1296 2071 100 0 none
xform 0 1424 2144
p 1328 2224 100 0 -1 DESC:Name of oiwfs filter
p 1232 1950 100 0 0 OMSL:closed_loop
p 1232 2110 100 0 0 VAL:
p 1040 2176 100 0 -1 def(DOL):$(ag)noRecord
p 1296 2176 75 1280 -1 palrm(DOL):MS
p 1584 2128 75 768 -1 palrm(OUT):MS
p 1552 2128 75 768 -1 pproc(OUT):PP
use estringouts 1568 1079 100 0 nifs
xform 0 1696 1152
p 1632 1216 100 0 -1 DESC:Name of oiwfs filter
p 1504 958 100 0 0 OMSL:closed_loop
p 1504 1118 100 0 0 VAL:
p 1408 1216 100 0 -1 def(DOL):$(ag)noRecord
p 1568 1184 75 1280 -1 palrm(DOL):MS
p 1856 1136 75 768 -1 palrm(OUT):MS
p 1824 1136 75 768 -1 pproc(OUT):PP
use superfout 672 1376 100 0 fan
xform 0 800 1632
use ecalcs 272 1351 100 0 calc
xform 0 416 1616
p 384 1552 100 0 1 CALC:A+1
p 448 1440 100 0 1 SCAN:.2 second
use inhier 32 1783 100 0 OIWFS
xform 0 48 1824
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
