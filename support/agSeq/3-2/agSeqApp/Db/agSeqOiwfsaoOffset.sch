[schematic2]
uniq 137
[tools]
[detail]
w 2274 2027 100 0 n#133 eaos.none.OUT 1952 2016 2656 2016 eaos.dzAo.SLNK
w 2034 683 100 0 n#133 eaos.nici.OUT 1952 672 2176 672 2176 2016 junction
w 2034 1803 100 0 n#133 eaos.gmos.OUT 1952 1792 2176 1792 junction
w 2034 1579 100 0 n#133 eaos.nirs.OUT 1952 1568 2176 1568 junction
w 2034 1355 100 0 n#133 eaos.niri.OUT 1952 1344 2176 1344 junction
w 2034 1131 100 0 n#133 eaos.f2.OUT 1952 1120 2176 1120 junction
w 2034 907 100 0 n#133 eaos.nifs.OUT 1952 896 2176 896 junction
w 1250 1675 100 0 n#136 superfout.fan.LNK7 1088 1664 1472 1664 1472 704 1696 704 eaos.nici.SLNK
w 1266 1707 100 0 n#135 eaos.nifs.SLNK 1696 928 1504 928 1504 1696 1088 1696 superfout.fan.LNK6
w 1282 1739 100 0 n#131 superfout.fan.LNK5 1088 1728 1536 1728 1536 1152 1696 1152 eaos.f2.SLNK
w 1298 1771 100 0 n#130 superfout.fan.LNK4 1088 1760 1568 1760 1568 1376 1696 1376 eaos.niri.SLNK
w 1314 1803 100 0 n#129 superfout.fan.LNK3 1088 1792 1600 1792 1600 1600 1696 1600 eaos.nirs.SLNK
w 1314 1867 100 0 n#128 superfout.fan.LNK1 1088 1856 1600 1856 1600 2048 1696 2048 eaos.none.SLNK
w 1362 1835 100 0 n#127 superfout.fan.LNK2 1088 1824 1696 1824 eaos.gmos.SLNK
w 586 1739 100 0 n#113 ecalcs.calc.FLNK 576 1728 656 1728 656 1568 672 1568 superfout.fan.SLNK
w 570 1707 100 0 n#112 ecalcs.calc.VAL 576 1696 624 1696 624 1792 672 1792 superfout.fan.SELL
w 184 1899 100 0 n#79 inhier.OIWFS.P 128 1888 288 1888 ecalcs.calc.INPA
s 128 2112 100 0 plane not direct M2 offsets.
s 128 2144 100 0 The values are offsets in the focal
s 128 2176 100 0 is in the beam.
s 128 2208 100 0 instruments focus offset when Altair
s 128 2240 100 0 This schematic holds the values of the 
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsaoOffset.sch,v 1.4 2007/05/18 22:29:24 pedro Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Fetch OIWFS track Id
[cell use]
use eaos 1696 839 100 0 nifs
xform 0 1824 928
p 1760 1008 100 0 -1 DESC:Focus offset for NIFS
p 1664 654 100 0 0 EGU:mm
p 1440 910 100 0 0 OMSL:supervisory
p 1440 782 100 0 0 PREC:14
p 1344 960 100 0 0 def(DOL):0.0
p 1984 896 75 768 -1 palrm(OUT):MS
p 1952 896 75 768 -1 pproc(OUT):PP
use eaos 1696 1063 100 0 f2
xform 0 1824 1152
p 1760 1232 100 0 -1 DESC:Focus offset for Flamingos-2
p 1664 878 100 0 0 EGU:mm
p 1440 1134 100 0 0 OMSL:supervisory
p 1440 1006 100 0 0 PREC:14
p 1440 700 100 0 0 def(DOL):0.0
p 1984 1120 75 768 -1 palrm(OUT):MS
p 1952 1120 75 768 -1 pproc(OUT):PP
use eaos 1696 1287 100 0 niri
xform 0 1824 1376
p 1760 1456 100 0 -1 DESC:Focus offset for NIRI
p 1664 1102 100 0 0 EGU:mm
p 1440 1358 100 0 0 OMSL:supervisory
p 1440 1230 100 0 0 PREC:14
p 1344 1408 100 0 0 def(DOL):0.0
p 1984 1344 75 768 -1 palrm(OUT):MS
p 1952 1344 75 768 -1 pproc(OUT):PP
use eaos 1696 1511 100 0 nirs
xform 0 1824 1600
p 1760 1680 100 0 -1 DESC:Focus offset for NIRS
p 1664 1326 100 0 0 EGU:mm
p 1440 1582 100 0 0 OMSL:supervisory
p 1440 1454 100 0 0 PREC:14
p 1344 1632 100 0 0 def(DOL):0.0
p 1984 1568 75 768 -1 palrm(OUT):MS
p 1952 1568 75 768 -1 pproc(OUT):PP
use eaos 1696 1735 100 0 gmos
xform 0 1824 1824
p 1760 1904 100 0 -1 DESC:Focus offset for GMOS
p 1664 1550 100 0 0 EGU:mm
p 1440 1806 100 0 0 OMSL:supervisory
p 1440 1678 100 0 0 PREC:14
p 1344 1856 100 0 0 def(DOL):0.0
p 1984 1792 75 768 -1 palrm(OUT):MS
p 1952 1792 75 768 -1 pproc(OUT):PP
use eaos 1696 1959 100 0 none
xform 0 1824 2048
p 1760 2128 100 0 -1 DESC:Focus offset for \"None\"
p 1664 1774 100 0 0 EGU:mm
p 1440 2030 100 0 0 OMSL:supervisory
p 1440 1902 100 0 0 PREC:14
p 1344 2080 100 0 0 def(DOL):0.0
p 1984 2016 75 768 -1 palrm(OUT):MS
p 1952 2016 75 768 -1 pproc(OUT):PP
use eaos 2656 1927 100 0 dzAo
xform 0 2784 2016
p 2400 1486 100 0 0 ADEL:0.0005
p 2704 2096 100 0 -1 DESC:Instrument focus offset
p 2624 1742 100 0 0 EGU:mm
p 2400 1454 100 0 0 MDEL:0.0000
p 2400 1870 100 0 0 PREC:14
p 2768 1920 100 1024 0 name:$(ag)oi:$(I)
use eaos 1696 615 100 0 nici
xform 0 1824 704
p 1760 784 100 0 -1 DESC:Focus offset for NICI
p 1664 430 100 0 0 EGU:mm
p 1440 686 100 0 0 OMSL:supervisory
p 1440 558 100 0 0 PREC:14
p 1344 736 100 0 0 def(DOL):0.0
p 1984 672 75 768 -1 palrm(OUT):MS
p 1952 672 75 768 -1 pproc(OUT):PP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use superfout 752 1456 100 0 fan
xform 0 880 1696
use ecalcs 288 1415 100 0 calc
xform 0 432 1680
p 400 1616 100 0 1 CALC:A+1
p 464 1504 100 0 1 SCAN:.2 second
use inhier 112 1847 100 0 OIWFS
xform 0 128 1888
[comments]
