[schematic2]
uniq 130
[tools]
[detail]
w 2274 2027 100 0 n#129 eaos.none.OUT 1888 2016 2720 2016 eaos.dzNoAo.SLNK
w 1970 683 100 0 n#129 eaos.nici.OUT 1888 672 2112 672 2112 2016 junction
w 1970 907 100 0 n#129 eaos.nifs.OUT 1888 896 2112 896 junction
w 1970 1131 100 0 n#129 eaos.f2.OUT 1888 1120 2112 1120 junction
w 1970 1355 100 0 n#129 eaos.niri.OUT 1888 1344 2112 1344 junction
w 1970 1579 100 0 n#129 eaos.nirs.OUT 1888 1568 2112 1568 junction
w 1970 1803 100 0 n#129 eaos.gmos.OUT 1888 1792 2112 1792 junction
w 1186 1675 100 0 n#128 superfout.fan.LNK7 1024 1664 1408 1664 1408 704 1632 704 eaos.nici.SLNK
w 1202 1707 100 0 n#127 eaos.nifs.SLNK 1632 928 1440 928 1440 1696 1024 1696 superfout.fan.LNK6
w 1218 1739 100 0 n#126 superfout.fan.LNK5 1024 1728 1472 1728 1472 1152 1632 1152 eaos.f2.SLNK
w 1234 1771 100 0 n#125 superfout.fan.LNK4 1024 1760 1504 1760 1504 1376 1632 1376 eaos.niri.SLNK
w 1250 1803 100 0 n#124 superfout.fan.LNK3 1024 1792 1536 1792 1536 1600 1632 1600 eaos.nirs.SLNK
w 1250 1867 100 0 n#123 superfout.fan.LNK1 1024 1856 1536 1856 1536 2048 1632 2048 eaos.none.SLNK
w 1346 1835 100 0 n#121 eaos.gmos.SLNK 1632 1824 1024 1824 superfout.fan.LNK2
w 514 1707 100 0 n#113 ecalcs.calc.VAL 496 1696 592 1696 592 1792 608 1792 superfout.fan.SELL
w 498 1739 100 0 n#112 ecalcs.calc.FLNK 496 1728 560 1728 560 1568 608 1568 superfout.fan.SLNK
w 120 1899 100 0 n#79 inhier.OIWFS.P 80 1888 208 1888 ecalcs.calc.INPA
s 128 2112 100 0 plane not direct M2 offsets.
s 128 2144 100 0 The values are offsets in the focal
s 128 2176 100 0 is not in the beam.
s 128 2208 100 0 instruments focus offset when Altair
s 128 2240 100 0 This schematic holds the values of the 
s 2481 98 100 0 Sciences Ltd.
s 2481 130 100 0 Observatory
s 2481 162 100 0 Copyright
s 2435 2351 100 0 $Id: agSeqOiwfsZoffset.sch,v 1.4 2007/05/18 22:29:24 pedro Exp $
s 2753 146 200 0 A&G Sequencer
s 2481 50 100 0 Chris Mayer
s 2769 98 100 0 Fetch OIWFS track Id
[cell use]
use eaos 1632 839 100 0 nifs
xform 0 1760 928
p 1696 1008 100 0 -1 DESC:Focus offset for NIFS
p 1600 654 100 0 0 EGU:mm
p 1376 910 100 0 0 OMSL:supervisory
p 1376 782 100 0 0 PREC:14
p 1280 960 100 0 0 def(DOL):0.0
p 1920 896 75 768 -1 palrm(OUT):MS
p 1888 896 75 768 -1 pproc(OUT):PP
use eaos 1632 1287 100 0 niri
xform 0 1760 1376
p 1696 1456 100 0 -1 DESC:Focus offset for NIRI
p 1600 1102 100 0 0 EGU:mm
p 1376 1358 100 0 0 OMSL:supervisory
p 1376 1230 100 0 0 PREC:14
p 1280 1408 100 0 0 def(DOL):0.0
p 1920 1344 75 768 -1 palrm(OUT):MS
p 1888 1344 75 768 -1 pproc(OUT):PP
use eaos 1632 1511 100 0 nirs
xform 0 1760 1600
p 1696 1680 100 0 -1 DESC:Focus offset for NIRS
p 1600 1326 100 0 0 EGU:mm
p 1376 1582 100 0 0 OMSL:supervisory
p 1376 1454 100 0 0 PREC:14
p 1280 1632 100 0 0 def(DOL):0.0
p 1920 1568 75 768 -1 palrm(OUT):MS
p 1888 1568 75 768 -1 pproc(OUT):PP
use eaos 1632 1735 100 0 gmos
xform 0 1760 1824
p 1696 1904 100 0 -1 DESC:Focus offset for GMOS
p 1600 1550 100 0 0 EGU:mm
p 1376 1806 100 0 0 OMSL:supervisory
p 1376 1678 100 0 0 PREC:14
p 1280 1856 100 0 0 def(DOL):0.0
p 1920 1792 75 768 -1 palrm(OUT):MS
p 1888 1792 75 768 -1 pproc(OUT):PP
use eaos 1632 1959 100 0 none
xform 0 1760 2048
p 1696 2128 100 0 -1 DESC:Focus offset for \"None\"
p 1600 1774 100 0 0 EGU:mm
p 1376 2030 100 0 0 OMSL:supervisory
p 1376 1902 100 0 0 PREC:14
p 1280 2080 100 0 0 def(DOL):0.0
p 1920 2016 75 768 -1 palrm(OUT):MS
p 1888 2016 75 768 -1 pproc(OUT):PP
use eaos 2720 1927 100 0 dzNoAo
xform 0 2848 2016
p 2464 1486 100 0 0 ADEL:0.0005
p 2768 2096 100 0 -1 DESC:Instrument focus offset
p 2688 1742 100 0 0 EGU:mm
p 2464 1454 100 0 0 MDEL:0.0000
p 2464 1870 100 0 0 PREC:14
p 2832 1920 100 1024 0 name:$(ag)oi:$(I)
use eaos 1632 1063 100 0 f2
xform 0 1760 1152
p 1696 1232 100 0 -1 DESC:Focus offset for Flamingos-2
p 1600 878 100 0 0 EGU:mm
p 1376 1006 100 0 0 PREC:14
p 1376 700 100 0 0 def(DOL):0.0
p 1920 1120 75 768 -1 palrm(OUT):MS
p 1888 1120 75 768 -1 pproc(OUT):PP
use eaos 1632 615 100 0 nici
xform 0 1760 704
p 1696 784 100 0 -1 DESC:Focus offset for NICI
p 1600 430 100 0 0 EGU:mm
p 1376 686 100 0 0 OMSL:supervisory
p 1376 558 100 0 0 PREC:14
p 1280 736 100 0 0 def(DOL):0.0
p 1920 672 75 768 -1 palrm(OUT):MS
p 1888 672 75 768 -1 pproc(OUT):PP
use superfout 688 1456 100 0 fan
xform 0 816 1696
use ecalcs 208 1415 100 0 calc
xform 0 352 1680
p 320 1616 100 0 1 CALC:A+1
p 384 1504 100 0 1 SCAN:.2 second
use inhier 64 1847 100 0 OIWFS
xform 0 80 1888
use bc200tr -128 -120 -100 0 frame
xform 0 1552 1184
[comments]
