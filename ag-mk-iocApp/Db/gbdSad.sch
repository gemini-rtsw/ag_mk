[schematic2]
uniq 13
[tools]
[detail]
w 2114 1851 100 0 n#1 esirs.sfEngTilt.FLNK 1968 2000 2064 2000 2064 1840 2224 1840 esirs.sfEngLin.SLNK
w 2762 1851 100 0 n#2 esirs.sfEngLin.FLNK 2640 2000 2720 2000 2720 1840 2864 1840 esirs.sfTilt.SLNK
w 3426 1851 100 0 n#3 esirs.sfTilt.FLNK 3280 2000 3392 2000 3392 1840 3520 1840 esirs.sfLin.SLNK
w 1002 1571 100 0 n#4 compSad.ao.FLNK 192 1984 560 1984 560 1568 1504 1568 1504 1088 1600 1088 esirs.aoEngTilt.SLNK
w 1058 1987 100 0 n#5 compSad.sf.FLNK 864 1984 1312 1984 1312 1840 1552 1840 esirs.sfEngTilt.SLNK
w 2100 1171 100 0 n#6 esirs.aoEngTilt.FLNK 2016 1248 2096 1248 2096 1104 2224 1104 esirs.aoTilt.SLNK
w 2328 2107 100 0 n#7 hwin.hwin#115.in 2480 2064 2480 2096 2224 2096 2224 2000 esirs.sfEngLin.INP
w 3624 2099 100 0 n#8 hwin.hwin#116.in 3776 2064 3776 2096 3520 2096 3520 2000 esirs.sfLin.INP
w 1656 2107 100 0 n#9 hwin.hwin#109.in 1808 2064 1808 2096 1552 2096 1552 2000 esirs.sfEngTilt.INP
w 2968 2099 100 0 n#10 hwin.hwin#110.in 3120 2064 3120 2096 2864 2096 2864 2000 esirs.sfTilt.INP
w 1704 1355 100 0 n#11 hwin.hwin#96.in 1856 1312 1856 1344 1600 1344 1600 1248 esirs.aoEngTilt.INP
w 2328 1363 100 0 n#12 hwin.hwin#97.in 2480 1328 2480 1360 2224 1360 2224 1264 esirs.aoTilt.INP
s 2464 3088 100 0 $Id: gbdSad.sch,v 1.4 2001/05/05 22:41:17 cjm Exp $
s 224 2320 100 0 This is to dump the results of the combination
s 224 2288 100 0 to an unexisting record /$(sadtop)
s -288 1200 100 0 K,L maybe not valid!
s -304 2096 100 0 These are the top-level n-D mechanisms from the ICD
s -528 1472 100 0 These are the real (underlying) 1-D motors
s -528 1424 100 0 usage only for engineering purposes!
s 3952 464 500 512 gbdSad.sch
n 3424 672 3904 1024 100
The following additional variables are
defined in this schematic:
.
mechanism = Full name of mechanism.
.
mech      = Brief name of mechanism.
.
.
New components can be added by adding
more instances of the "component"
schematic with different values for
"mech" (e.g. "filt", "slit", "grat",
"mask", etc...).
_
n 2880 672 3360 1024 100
This is the under top level schematic
for the A&G Control
System Components Controller
Status/Alarm Database. On this
schematic will be placed a symbol
pointing to the Status/Alarm Databases
for each of the mechanisms.
.
There are the following symbols:
.
system = systemwide srcbase
.
Plus a symbol for each component.
in the srcbase.
_
[cell use]
use sircomb 16 2423 100 0 sircomb
xform 0 104 2528
p 16 2384 100 0 1 set1:sadtop $(sadtop)cc:
p 368 2496 100 0 1 set10:f4 $(sadtop2)aoflags.VAL
p 784 2496 100 0 1 set11:s4 $(sadtop2)aoflags.OMSS
p 368 2464 100 0 1 set12:f5 $(sadtop2)hwflags.VAL
p 784 2464 100 0 1 set13:s5 $(sadtop2)hwflags.OMSS
p 368 2432 100 0 1 set14:f6 
p 784 2432 100 0 1 set15:s6 
p 368 2400 100 0 1 set16:f7
p 784 2400 100 0 1 set17:s7 
p 16 2288 100 0 1 set18:trgtop2
p 16 2352 100 0 1 set2:hindex2
p 16 2320 100 0 1 set3:mindex2
p 368 2592 100 0 1 set4:f1 $(sadtop2)p1:flags.VAL
p 784 2592 100 0 1 set5:s1 $(sadtop2)p1:flags.OMSS
p 368 2560 100 0 1 set6:f2 $(sadtop2)p2:flags.VAL
p 784 2560 100 0 1 set7:s2 $(sadtop2)p2:flags.OMSS
p 368 2528 100 0 1 set8:f3 $(sadtop2)sfflags.VAL
p 784 2528 100 0 1 set9:s3 $(sadtop2)sfflags.OMSS
use hwin 3584 2023 100 0 hwin#116
xform 0 3680 2064
p 3600 2000 100 0 -1 val(in):$(sadtop)sfPosA.VALC
use hwin 2288 2023 100 0 hwin#115
xform 0 2384 2064
p 2304 2000 100 0 -1 val(in):$(sadtop)sfEngPosA.VALC
use hwin 2928 2023 100 0 hwin#110
xform 0 3024 2064
p 2944 2000 100 0 -1 val(in):$(sadtop)sfPosA.VALB
use hwin 1616 2023 100 0 hwin#109
xform 0 1712 2064
p 1632 2000 100 0 -1 val(in):$(sadtop)sfEngPosA.VALB
use hwin 2288 1287 100 0 hwin#97
xform 0 2384 1328
p 2304 1264 100 0 -1 val(in):$(sadtop)aoPosA.VALB
use hwin 1664 1271 100 0 hwin#96
xform 0 1760 1312
p 1680 1248 100 0 -1 val(in):$(sadtop)aoEngPosA.VALB
use esirs 3616 1792 100 0 sfLin
xform 0 3728 1904
p 3616 1728 100 0 1 DESC:Mechs real world pos.
p 3744 1888 100 0 1 EGU:mm
p 3616 1696 100 0 1 FDSC:real world position
p 3728 1920 100 0 1 FTVL:DOUBLE
p 3456 1424 100 0 0 HHSV:MAJOR
p 3456 1328 100 0 0 HSV:MINOR
p 3456 1264 100 0 0 LLSV:MAJOR
p 3456 1168 100 0 0 LSV:MINOR
p 3760 1856 100 0 1 NELM:1
p 3656 1528 100 0 0 NORD:1
p 3712 1680 100 0 0 PREC:2
p 3616 1600 100 0 1 PV:$(sadtop)
p 3616 1664 100 0 1 SCAN:Passive
p 3616 1632 100 0 1 SNAM:
use esirs 2320 1792 100 0 sfEngLin
xform 0 2432 1904
p 2320 1728 100 0 1 DESC:Mechs eng. pos.
p 2400 1904 100 0 1 EGU:eng.units
p 2320 1696 100 0 1 FDSC:eng. position
p 2448 1936 100 0 1 FTVL:LONG
p 2160 1424 100 0 0 HHSV:MAJOR
p 2160 1328 100 0 0 HSV:MINOR
p 2160 1264 100 0 0 LLSV:MAJOR
p 2160 1168 100 0 0 LSV:MINOR
p 2480 1872 100 0 1 NELM:1
p 2360 1528 100 0 0 NORD:1
p 2320 1600 100 0 1 PV:$(sadtop)
p 2320 1664 100 0 1 SCAN:Passive
p 2320 1632 100 0 1 SNAM:
use esirs 2960 1792 100 0 sfTilt
xform 0 3072 1904
p 2960 1728 100 0 1 DESC:Mechs real world pos.
p 3104 1888 100 0 1 EGU:deg
p 2960 1696 100 0 1 FDSC:real world position
p 3072 1920 100 0 1 FTVL:DOUBLE
p 2800 1424 100 0 0 HHSV:MAJOR
p 2800 1328 100 0 0 HSV:MINOR
p 2800 1264 100 0 0 LLSV:MAJOR
p 2800 1168 100 0 0 LSV:MINOR
p 3104 1856 100 0 1 NELM:1
p 3000 1528 100 0 0 NORD:1
p 3056 1680 100 0 0 PREC:2
p 2960 1600 100 0 1 PV:$(sadtop)
p 2960 1664 100 0 1 SCAN:Passive
p 2960 1632 100 0 1 SNAM:
use esirs 1648 1792 100 0 sfEngTilt
xform 0 1760 1904
p 1648 1728 100 0 1 DESC:Mechs eng. pos.
p 1728 1904 100 0 1 EGU:eng.units
p 1648 1696 100 0 1 FDSC:eng. position
p 1776 1936 100 0 1 FTVL:LONG
p 1648 1568 100 0 1 HHSV:MAJOR
p 1920 1568 100 0 1 HIGH:0.0
p 1920 1536 100 0 1 HIHI:0.0
p 1792 1568 100 0 1 HSV:MINOR
p 1488 1392 100 0 0 HYST:0.0
p 1648 1536 100 0 1 LLSV:MAJOR
p 2032 1568 100 0 1 LOLO:0.0
p 2032 1536 100 0 1 LOW:0.0
p 1792 1536 100 0 1 LSV:MINOR
p 1808 1872 100 0 1 NELM:1
p 1688 1528 100 0 0 NORD:1
p 1648 1600 100 0 1 PV:$(sadtop)
p 1648 1664 100 0 1 SCAN:Passive
p 1648 1632 100 0 1 SNAM:
use esirs 2320 1056 100 0 aoTilt
xform 0 2432 1168
p 2320 992 100 0 1 DESC:Mechs real world pos.
p 2464 1168 100 0 1 EGU:deg
p 2320 960 100 0 1 FDSC:real world position
p 2432 1200 100 0 1 FTVL:DOUBLE
p 2160 688 100 0 0 HHSV:MAJOR
p 2160 592 100 0 0 HSV:MINOR
p 2160 528 100 0 0 LLSV:MAJOR
p 2160 432 100 0 0 LSV:MINOR
p 2480 1136 100 0 1 NELM:1
p 2360 792 100 0 0 NORD:1
p 2320 864 100 0 1 PV:$(sadtop)
p 2320 928 100 0 1 SCAN:Passive
p 2320 896 100 0 1 SNAM:
use esirs 1696 1040 100 0 aoEngTilt
xform 0 1808 1152
p 1696 976 100 0 1 DESC:Mechs eng. pos.
p 1776 1152 100 0 1 EGU:eng.units
p 1696 944 100 0 1 FDSC:eng. position
p 1808 1184 100 0 1 FTVL:LONG
p 1536 672 100 0 0 HHSV:MAJOR
p 1536 576 100 0 0 HSV:MINOR
p 1536 512 100 0 0 LLSV:MAJOR
p 1536 416 100 0 0 LSV:MINOR
p 1840 1120 100 0 1 NELM:1
p 1736 776 100 0 0 NORD:1
p 1696 848 100 0 1 PV:$(sadtop)
p 1696 912 100 0 1 SCAN:Passive
p 1696 880 100 0 1 SNAM:
use eborderD -1184 -153 100 0 eborderD#106
xform 0 1456 1552
p 2432 64 100 768 -1 author:O.Frischmuth
p -1164 -180 100 0 0 checked:O.Frischmuth
p 2432 0 100 768 -1 date:15 May 97
p 2944 320 200 768 0 file:$RCSfile: gbdSad.sch,v $
p -1144 -200 100 0 0 id:frame
p -1124 -220 100 0 0 model:frame
p 3440 48 100 0 -1 page:
p 2976 352 100 0 -1 project:A&G Control System
p 3040 64 100 0 -1 revision:2.2
p 2944 208 100 0 -1 title:GBD SAD schematic
use compSad 16 1351 100 0 PA3AO
xform 0 112 1456
p 16 1328 100 0 1 set1:mechanism PA3AO
p 16 1296 100 0 1 set2:mech PA3AO
p 16 1264 100 0 1 set3:units deg
p 16 1232 100 0 1 set4:hindex
p 16 1200 100 0 1 set5:mindex
use compSad 688 1351 100 0 Tilt2
xform 0 784 1456
p 688 1328 100 0 1 set1:mechanism Tilt
p 688 1296 100 0 1 set2:mech Tilt
p 688 1264 100 0 1 set3:units deg
p 688 1232 100 0 1 set4:hindex
p 688 1200 100 0 1 set5:mindex
use compSad 688 1831 100 0 sf
xform 0 784 1936
p 688 1808 100 0 1 set1:mechanism ScFold
p 688 1776 100 0 1 set2:mech sf
p 688 1744 100 0 1 set3:hindex $(trigtop).A
p 688 1712 100 0 1 set4:mindex $(trigtop).B
p 688 1680 100 0 1 set5:possir Rot
p 688 1648 100 0 1 set6:engsir EngRot
use compSad -392 1831 100 0 hw
xform 0 -304 1936
p -400 1808 100 0 1 set1:mechanism HRWFS probe
p -400 1776 100 0 1 set2:mech hw
p -400 1744 100 0 1 set3:hindex $(trigtop).E
p -400 1712 100 0 1 set4:mindex $(trigtop).F
use compSad 24 1831 100 0 ao
xform 0 112 1936
p 16 1808 100 0 1 set1:mechanism AO Fold
p 16 1776 100 0 1 set2:mech ao
p 16 1744 100 0 1 set3:hindex $(trigtop).C
p 16 1712 100 0 1 set4:mindex $(trigtop).D
p 16 1680 100 0 1 set5:possir Rot
p 16 1648 100 0 1 set6:engsir EngRot
use compSad 352 1351 100 0 RT2
xform 0 448 1456
p 352 1328 100 0 1 set1:mechanism RT2
p 352 1296 100 0 1 set2:mech RT2
p 352 1264 100 0 1 set3:units deg
p 352 1232 100 0 1 set4:hindex
p 352 1200 100 0 1 set5:mindex
use compSad 1024 1351 100 0 Lin2
xform 0 1120 1456
p 1024 1328 100 0 1 set1:mechanism Lin2
p 1024 1296 100 0 1 set2:mech Lin2
p 1024 1264 100 0 1 set3:units mm
p 1024 1232 100 0 1 set4:hindex
p 1024 1200 100 0 1 set5:mindex
use pwfsSad 464 448 100 0 pwfs2
xform 0 944 656
p 464 384 100 0 1 set1:sub 2
p 464 352 100 0 1 set2:top $(top)p2:
p 464 320 100 0 1 set3:sadtop $(sadtop)p2:
p 464 288 100 0 1 set4:trigtop $(sadtop)CHlt
p 848 384 100 0 1 set5:hindex2 $(trgtop2).I
p 848 352 100 0 1 set6:mindex2 $(trgtop2).J
p 848 320 100 0 1 set7:ftop $(ftop)p2_
p 848 288 100 0 1 seta:sad $(sad)p2:
use pwfsSad -608 448 100 0 pwfs1
xform 0 -128 656
p -608 384 100 0 1 set1:sub 1
p -608 352 100 0 1 set2:top $(top)p1:
p -608 320 100 0 1 set3:sadtop $(sadtop)p1:
p -608 288 100 0 1 set4:trigtop $(sadtop)CHlt
p -192 384 100 0 1 set5:hindex2 $(trgtop2).G
p -192 352 100 0 1 set6:mindex2 $(trgtop2).H
p -192 320 100 0 1 set7:ftop $(ftop)p1_
p -192 288 100 0 1 seta:sad $(sad)p1:
use ccSysSad -392 2423 100 0 system
xform 0 -312 2528
p -400 2400 100 0 1 set1:sadtop $(sadtop)cc:
[comments]
