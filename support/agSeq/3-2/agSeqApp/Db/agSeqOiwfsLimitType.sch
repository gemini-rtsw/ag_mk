[schematic2]
uniq 166
[tools]
[detail]
w 1554 619 100 0 n#165 ebos.nici.SLNK 1792 608 1376 608 1376 1952 1136 1952 superfout.fout.LNK7
w 1570 875 100 0 n#164 ebos.nifs.SLNK 1792 864 1408 864 1408 1984 1136 1984 superfout.fout.LNK6
w 1586 1131 100 0 n#163 superfout.fout.LNK5 1136 2016 1440 2016 1440 1120 1792 1120 ebos.f2.SLNK
w 1274 2059 100 0 n#162 superfout.fout.LNK4 1136 2048 1472 2048 1472 1376 1792 1376 ebos.niri.SLNK
w 1290 2091 100 0 n#161 superfout.fout.LNK3 1136 2080 1504 2080 1504 1632 1792 1632 ebos.nirs.SLNK
w 1306 2123 100 0 n#160 superfout.fout.LNK2 1136 2112 1536 2112 1536 1888 1792 1888 ebos.gmos.SLNK
w 1434 2155 100 0 n#159 superfout.fout.LNK1 1136 2144 1792 2144 ebos.none.SLNK
w 2094 843 100 0 OUT ebos.nifs.OUT 2048 832 2176 832 junction
w 2094 1099 100 0 OUT ebos.f2.OUT 2048 1088 2176 1088 junction
w 2094 1355 100 0 OUT ebos.niri.OUT 2048 1344 2176 1344 junction
w 2094 1611 100 0 OUT ebos.nirs.OUT 2048 1600 2176 1600 junction
w 2094 1867 100 0 OUT ebos.gmos.OUT 2048 1856 2176 1856 junction
w 2094 587 100 0 OUT ebos.nici.OUT 2048 576 2176 576 2176 2112 junction
w 2486 2123 100 0 OUT ebos.none.OUT 2048 2112 2960 2112 outhier.OUT.p
w 658 2091 100 0 n#156 ecalcs.calc.VAL 624 1936 656 1936 656 2080 720 2080 superfout.fout.SELL
w 626 1979 100 0 n#155 ecalcs.calc.FLNK 624 1968 688 1968 688 1856 720 1856 superfout.fout.SLNK
w 1746 1675 100 0 n#153 hwin.hwin#114.in 1760 1664 1792 1664 ebos.nirs.DOL
w 1746 651 100 0 n#152 hwin.hwin#145.in 1760 640 1792 640 ebos.nici.DOL
w 1746 1163 100 0 n#148 hwin.hwin#124.in 1760 1152 1792 1152 ebos.f2.DOL
w 1746 1419 100 0 n#147 hwin.hwin#142.in 1760 1408 1792 1408 ebos.niri.DOL
w 1746 907 100 0 n#117 hwin.hwin#130.in 1760 896 1792 896 ebos.nifs.DOL
w 1746 1931 100 0 n#111 hwin.hwin#110.in 1760 1920 1792 1920 ebos.gmos.DOL
w 240 2139 100 0 n#79 inhier.OIWFS.P 192 2128 336 2128 ecalcs.calc.INPA
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsLimitType.sch,v 1.6 2007/05/18 22:29:23 pedro Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Fetch OIWFS limit type
[cell use]
use hwin 1568 1367 100 0 hwin#142
xform 0 1664 1408
p 1571 1400 100 0 -1 val(in):0
use hwin 1568 1111 100 0 hwin#124
xform 0 1664 1152
p 1571 1144 100 0 -1 val(in):0
use hwin 1568 1623 100 0 hwin#114
xform 0 1664 1664
p 1571 1656 100 0 -1 val(in):0
use hwin 1568 1879 100 0 hwin#110
xform 0 1664 1920
p 1571 1912 100 0 -1 val(in):0
use hwin 1568 855 100 0 hwin#130
xform 0 1664 896
p 1571 888 100 0 -1 val(in):0
use hwin 1568 599 100 0 hwin#145
xform 0 1664 640
p 1571 632 100 0 -1 val(in):0
use ebos 1792 1031 100 0 f2
xform 0 1920 1120
p 1856 1200 100 0 -1 DESC:Limit type
p 1472 1070 100 0 0 OMSL:closed_loop
p 1872 1024 100 0 1 ONAM:Radial
p 2048 1024 100 0 1 ZNAM:XY
p 1472 540 100 0 0 def(DOL):0.0
p 2080 1088 75 768 -1 palrm(OUT):MS
p 2048 1088 75 768 -1 pproc(OUT):PP
use ebos 1792 1287 100 0 niri
xform 0 1920 1376
p 1856 1456 100 0 -1 DESC:Limit type
p 1472 1326 100 0 0 OMSL:closed_loop
p 1872 1280 100 0 1 ONAM:Radial
p 2048 1280 100 0 1 ZNAM:XY
p 1904 1344 100 0 0 def(DOL):0.0
p 2080 1344 75 768 -1 palrm(OUT):MS
p 2048 1344 75 768 -1 pproc(OUT):PP
use ebos 1792 1543 100 0 nirs
xform 0 1920 1632
p 1856 1712 100 0 -1 DESC:Limit type
p 1472 1582 100 0 0 OMSL:closed_loop
p 1872 1536 100 0 1 ONAM:Radial
p 2048 1536 100 0 1 ZNAM:XY
p 1904 1600 100 0 0 def(DOL):0.0
p 2080 1600 75 768 -1 palrm(OUT):MS
p 2048 1600 75 768 -1 pproc(OUT):PP
use ebos 1792 2055 100 0 none
xform 0 1920 2144
p 1856 2224 100 0 -1 DESC:Limit type
p 1472 2094 100 0 0 OMSL:closed_loop
p 1872 2048 100 0 1 ONAM:Radial
p 2032 2048 100 0 1 ZNAM:XY
p 1664 2224 100 0 -1 def(DOL):$(ag)noRecord
p 1792 2176 75 1280 -1 palrm(DOL):MS
p 2080 2112 75 768 -1 palrm(OUT):MS
p 2048 2112 75 768 -1 pproc(OUT):PP
use ebos 1792 1799 100 0 gmos
xform 0 1920 1888
p 1856 1968 100 0 -1 DESC:Limit type
p 1472 1838 100 0 0 OMSL:closed_loop
p 1872 1792 100 0 1 ONAM:Radial
p 2032 1792 100 0 1 ZNAM:XY
p 1904 1856 100 0 0 def(DOL):0.0
p 2080 1856 75 768 -1 palrm(OUT):MS
p 2048 1856 75 768 -1 pproc(OUT):PP
use ebos 1792 775 100 0 nifs
xform 0 1920 864
p 1856 944 100 0 -1 DESC:Limit type
p 1472 814 100 0 0 OMSL:closed_loop
p 1872 768 100 0 1 ONAM:Radial
p 2032 768 100 0 1 ZNAM:XY
p 1904 832 100 0 0 def(DOL):0.0
p 2080 832 75 768 -1 palrm(OUT):MS
p 2048 832 75 768 -1 pproc(OUT):PP
use ebos 1792 519 100 0 nici
xform 0 1920 608
p 1856 688 100 0 -1 DESC:Limit type
p 1472 558 100 0 0 OMSL:closed_loop
p 2048 576 75 768 -1 pproc(OUT):PP
use superfout 800 1728 100 0 fout
xform 0 928 1984
use outhier 2928 2071 100 0 OUT
xform 0 2944 2112
use ecalcs 336 1655 100 0 calc
xform 0 480 1920
p 448 1856 100 0 1 CALC:A+1
p 512 1744 100 0 1 SCAN:.2 second
use inhier 176 2087 100 0 OIWFS
xform 0 192 2128
use bc200tr -128 -152 -100 0 frame
xform 0 1552 1152
[comments]
