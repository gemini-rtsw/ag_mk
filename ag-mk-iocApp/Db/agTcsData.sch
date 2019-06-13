[schematic2]
uniq 35
[tools]
[detail]
w 432 1867 100 0 n#34 elongouts.probeId.VAL 336 1856 576 1856 egenSub.calcProbeRadii.INPA
w 0 1899 100 0 n#33 hwin.hwin#30.in -32 1888 80 1888 elongouts.probeId.DOL
w 1272 1707 100 0 n#27 egenSub.calcProbeRadii.VALD 864 1696 1728 1696 1728 1600 1888 1600 eaos.Zmax.DOL
w 1224 1771 100 0 n#26 egenSub.calcProbeRadii.VALC 864 1760 1632 1760 1632 1888 1888 1888 eaos.Zmin.DOL
w 920 1835 100 0 n#25 egenSub.calcProbeRadii.VALB 864 1824 1024 1824 1024 1600 1184 1600 eaos.Rmax.DOL
w 1528 1611 100 0 n#24 eaos.Rmax.FLNK 1440 1600 1664 1600 1664 1856 1888 1856 eaos.Zmin.SLNK
w 1288 1739 100 0 n#23 eaos.Rmin.FLNK 1440 1888 1536 1888 1536 1728 1088 1728 1088 1568 1184 1568 eaos.Rmax.SLNK
w 1000 1899 100 0 n#22 egenSub.calcProbeRadii.VALA 864 1888 1184 1888 eaos.Rmin.DOL
w 936 1163 100 0 n#21 egenSub.calcProbeRadii.FLNK 864 1152 1056 1152 1056 1856 1184 1856 eaos.Rmin.SLNK
w 1992 1739 100 0 n#17 eaos.Zmin.FLNK 2144 1888 2272 1888 2272 1728 1760 1728 1760 1568 1888 1568 eaos.Zmax.SLNK
w 312 235 100 0 n#13 egenSub.calcStateFlag.FLNK 224 224 448 224 448 1184 576 1184 egenSub.calcProbeRadii.SLNK
w 296 971 100 0 n#12 egenSub.calcStateFlag.VALA 224 960 416 960 416 1152 576 1152 egenSub.calcProbeRadii.SDIS
w -224 939 100 0 n#11 inhier.c#9.P -336 928 -64 928 egenSub.calcStateFlag.INPA
s 2080 2144 100 0 $Id: agTcsData.sch,v 1.1 2000/03/25 01:18:05 cjm Exp $
s 2336 -96 100 0 Status items used by TCS
s 2080 -160 100 0 Chris Mayer
s 2080 -112 100 0 Sciences Ltd.
s 2080 -80 100 0 Observatory
s 2080 -48 100 0 Copyright 
[cell use]
use elongouts 80 1767 100 0 probeId
xform 0 208 1856
p 128 1952 100 0 -1 DESC:Index to probe
p -80 1774 100 0 0 OMSL:closed_loop
use hwin -224 1847 100 0 hwin#30
xform 0 -128 1888
p -221 1880 100 0 -1 val(in):$(sub)
use inhier -352 887 100 0 c#9
xform 0 -336 928
use eaos 1184 1767 100 0 Rmin
xform 0 1312 1856
p 1168 1952 100 0 -1 DESC:Minimum probe radius in focal plane
p 1152 1582 100 0 0 EGU:mm
p 928 1838 100 0 0 OMSL:closed_loop
p 928 1710 100 0 0 PREC:6
p 928 1436 100 0 0 def(OUT):0.0
use eaos 1184 1479 100 0 Rmax
xform 0 1312 1568
p 1168 1664 100 0 -1 DESC:Maximum probe radius in focal plane
p 1152 1294 100 0 0 EGU:mm
p 928 1550 100 0 0 OMSL:closed_loop
p 928 1422 100 0 0 PREC:6
use eaos 1888 1767 100 0 Zmin
xform 0 2016 1856
p 1872 1952 100 0 -1 DESC:Minimum physical probe focus
p 1856 1582 100 0 0 EGU:mm
p 1632 1838 100 0 0 OMSL:closed_loop
p 1632 1710 100 0 0 PREC:6
use eaos 1888 1479 100 0 Zmax
xform 0 2016 1568
p 1872 1664 100 0 -1 DESC:Maximum physical probe focus
p 1856 1294 100 0 0 EGU:mm
p 1632 1550 100 0 0 OMSL:closed_loop
p 1632 1422 100 0 0 PREC:6
use egenSub -64 167 100 0 calcStateFlag
xform 0 80 592
p -32 1024 100 0 -1 DESC:Calculate disable flag
p 16 960 100 0 1 FTA:STRING
p -287 -59 100 0 0 FTVA:LONG
p 0 32 100 0 1 SCAN:1 second
p 0 64 100 0 1 SNAM:agCalcStateFlag
p -304 960 100 0 -1 def(INPA):$(ag)cc:state
use egenSub 576 1095 100 0 calcProbeRadii
xform 0 720 1520
p 560 1968 100 0 -1 DESC:Calculate Max/Min probe radii
p 672 1152 100 0 1 DISV:0
p 656 1888 100 0 1 FTA:LONG
p 656 1888 100 0 0 NOA:1
p 288 1646 100 0 0 PREC:14
p 640 1024 100 0 1 SNAM:agCalcProbeRadii
p 160 1872 100 0 0 def(INPA):0.0
p 528 1866 75 0 -1 pproc(INPA):PP
p 864 1866 75 0 -1 pproc(OUTA):NPP
p 864 1802 75 0 -1 pproc(OUTB):NPP
use bc200tr -512 -328 -100 0 frame
xform 0 1168 976
[comments]
