[schematic2]
uniq 136
[tools]
[detail]
w 1266 1387 100 0 n#135 superfout.fan.LNK7 1120 1376 1472 1376 1472 896 1632 896 eaos.nici.SLNK
w 1282 1419 100 0 n#134 superfout.fan.LNK6 1120 1408 1504 1408 1504 1088 1632 1088 eaos.nifs.SLNK
w 1298 1451 100 0 n#133 superfout.fan.LNK5 1120 1440 1536 1440 1536 1280 1632 1280 eaos.f2.SLNK
w 1266 1579 100 0 n#132 superfout.fan.LNK1 1120 1568 1472 1568 1472 2048 1632 2048 eaos.none.SLNK
w 1282 1547 100 0 n#131 superfout.fan.LNK2 1120 1536 1504 1536 1504 1856 1632 1856 eaos.gmos.SLNK
w 1298 1515 100 0 n#130 superfout.fan.LNK3 1120 1504 1536 1504 1536 1664 1632 1664 eaos.nirs.SLNK
w 130 1627 100 0 OIWFS inhier.OIWFS.P 64 1616 256 1616 ecalcs.calc.INPA
w 1346 1483 100 0 n#128 eaos.niri.SLNK 1632 1472 1120 1472 superfout.fan.LNK4
w 1986 1067 100 0 n#127 eaos.nifs.OUT 1888 1056 2144 1056 junction
w 1986 1259 100 0 n#127 eaos.f2.OUT 1888 1248 2144 1248 junction
w 1986 1451 100 0 n#127 eaos.niri.OUT 1888 1440 2144 1440 junction
w 1986 1643 100 0 n#127 eaos.nirs.OUT 1888 1632 2144 1632 junction
w 1986 1835 100 0 n#127 eaos.gmos.OUT 1888 1824 2144 1824 junction
w 1986 875 100 0 n#127 eaos.nici.OUT 1888 864 2144 864 2144 2016 junction
w 2234 2027 100 0 n#127 eaos.none.OUT 1888 2016 2640 2016 eaos.dzProbe.SLNK
w 578 1435 100 0 n#117 ecalcs.calc.VAL 544 1424 672 1424 672 1504 704 1504 superfout.fan.SELL
w 562 1467 100 0 n#115 ecalcs.calc.FLNK 544 1456 640 1456 640 1280 704 1280 superfout.fan.SLNK
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsProbe.sch,v 1.4 2007/05/18 22:29:23 pedro Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Fetch OIWFS track Id
s 128 2272 100 0 It is possible that the OIWFS and its instrument are
s 128 2240 100 0 not confocal. This schematic holds the offset between
s 128 2208 100 0 the OIWFS focal plane and the instrument focal plane.
[cell use]
use eaos 1632 999 100 0 nifs
xform 0 1760 1088
p 1696 1168 100 0 -1 DESC:Focus offset for NIFS
p 1600 814 100 0 0 EGU:mm
p 1376 1070 100 0 0 OMSL:supervisory
p 1376 942 100 0 0 PREC:14
p 1280 1120 100 0 0 def(DOL):0.0
p 1920 1056 75 768 -1 palrm(OUT):MS
p 1888 1056 75 768 -1 pproc(OUT):PP
use eaos 1632 1383 100 0 niri
xform 0 1760 1472
p 1696 1552 100 0 -1 DESC:Focus offset for NIRI
p 1600 1198 100 0 0 EGU:mm
p 1376 1454 100 0 0 OMSL:supervisory
p 1376 1326 100 0 0 PREC:14
p 1280 1504 100 0 0 def(DOL):0.0
p 1920 1440 75 768 -1 palrm(OUT):MS
p 1888 1440 75 768 -1 pproc(OUT):PP
use eaos 1632 1575 100 0 nirs
xform 0 1760 1664
p 1696 1744 100 0 -1 DESC:Focus offset for NIRS
p 1600 1390 100 0 0 EGU:mm
p 1376 1646 100 0 0 OMSL:supervisory
p 1376 1518 100 0 0 PREC:14
p 1280 1696 100 0 0 def(DOL):0.0
p 1920 1632 75 768 -1 palrm(OUT):MS
p 1888 1632 75 768 -1 pproc(OUT):PP
use eaos 1632 1767 100 0 gmos
xform 0 1760 1856
p 1696 1936 100 0 -1 DESC:Focus offset for GMOS
p 1600 1582 100 0 0 EGU:mm
p 1376 1838 100 0 0 OMSL:supervisory
p 1376 1710 100 0 0 PREC:14
p 1280 1888 100 0 0 def(DOL):0.0
p 1920 1824 75 768 -1 palrm(OUT):MS
p 1888 1824 75 768 -1 pproc(OUT):PP
use eaos 1632 1959 100 0 none
xform 0 1760 2048
p 1696 2128 100 0 -1 DESC:Focus offset for \"None\"
p 1600 1774 100 0 0 EGU:mm
p 1376 2030 100 0 0 OMSL:supervisory
p 1376 1902 100 0 0 PREC:14
p 1280 2080 100 0 0 def(DOL):0.0
p 1920 2016 75 768 -1 palrm(OUT):MS
p 1888 2016 75 768 -1 pproc(OUT):PP
use eaos 2640 1927 100 0 dzProbe
xform 0 2768 2016
p 2384 1486 100 0 0 ADEL:0.0005
p 2688 2096 100 0 -1 DESC:OIWFS focus offset
p 2608 1742 100 0 0 EGU:mm
p 2384 1454 100 0 0 MDEL:0.0000
p 2384 1870 100 0 0 PREC:14
p 2752 1920 100 1024 0 name:$(ag)oi:$(I)
use eaos 1632 1191 100 0 f2
xform 0 1760 1280
p 1696 1360 100 0 -1 DESC:Focus offset for Flamingos-2
p 1600 1006 100 0 0 EGU:mm
p 1376 1262 100 0 0 OMSL:supervisory
p 1376 1134 100 0 0 PREC:14
p 1376 828 100 0 0 def(DOL):0.0
p 1920 1248 75 768 -1 palrm(OUT):MS
p 1888 1248 75 768 -1 pproc(OUT):PP
use eaos 1632 807 100 0 nici
xform 0 1760 896
p 1696 976 100 0 -1 DESC:Focus offset for NICI
p 1600 622 100 0 0 EGU:mm
p 1376 878 100 0 0 OMSL:supervisory
p 1376 750 100 0 0 PREC:14
p 1280 928 100 0 0 def(DOL):0.0
p 1920 864 75 768 -1 palrm(OUT):MS
p 1888 864 75 768 -1 pproc(OUT):PP
use superfout 784 1168 100 0 fan
xform 0 912 1408
use ecalcs 256 1143 100 0 calc
xform 0 400 1408
p 368 1344 100 0 1 CALC:A+1
p 432 1232 100 0 1 SCAN:.2 second
use inhier 48 1575 100 0 OIWFS
xform 0 64 1616
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
