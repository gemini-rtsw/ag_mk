[schematic2]
uniq 272
[tools]
[detail]
w -70 1531 100 0 n#268 compSad.probe.FLNK -592 1696 -272 1696 -272 1520 192 1520 esirs.tableAngle.SLNK
w 1700 891 100 0 n#256 esirs.y.FLNK 1664 976 1696 976 1696 816 1760 816 esirs.z.SLNK
w 1864 1075 100 0 n#255 hwin.hwin#257.in 2016 1040 2016 1072 1760 1072 1760 976 esirs.z.INP
w 1130 1115 100 0 n#252 esirs.armEngPos.FLNK 2160 1680 2208 1680 2208 1104 112 1104 112 816 192 816 esirs.angle.SLNK
w 1684 1595 100 0 n#250 esirs.tableEngPos.FLNK 1648 1680 1680 1680 1680 1520 1744 1520 esirs.armEngPos.SLNK
w 1172 1595 100 0 n#247 esirs.armAngle.FLNK 1120 1680 1168 1680 1168 1520 1232 1520 esirs.tableEngPos.SLNK
w 1848 1787 100 0 n#244 hwin.hwin#245.in 2000 1744 2000 1776 1744 1776 1744 1680 esirs.armEngPos.INP
w 660 891 100 0 n#205 esirs.angle.FLNK 608 976 656 976 656 816 736 816 esirs.x.SLNK
w 296 1075 100 0 n#201 hwin.hwin#203.in 448 1040 448 1072 192 1072 192 976 esirs.angle.INP
w 1188 891 100 0 n#199 esirs.x.FLNK 1152 976 1184 976 1184 816 1248 816 esirs.y.SLNK
w 1352 1075 100 0 n#195 hwin.hwin#197.in 1504 1040 1504 1072 1248 1072 1248 976 esirs.y.INP
w 644 1595 100 0 n#192 esirs.tableAngle.FLNK 608 1680 640 1680 640 1520 704 1520 esirs.armAngle.SLNK
w 840 1075 100 0 n#189 hwin.hwin#190.in 992 1040 992 1072 736 1072 736 976 esirs.x.INP
w 296 1779 100 0 n#188 hwin.hwin#187.in 448 1744 448 1776 192 1776 192 1680 esirs.tableAngle.INP
w 808 1779 100 0 n#115 hwin.hwin#117.in 960 1744 960 1776 704 1776 704 1680 esirs.armAngle.INP
w 1336 1787 100 0 n#114 hwin.hwin#116.in 1488 1744 1488 1776 1232 1776 1232 1680 esirs.tableEngPos.INP
s 288 1168 100 0 MAJOR/MINOR settings are the same for all records (see tableAngle).
s 2192 256 500 512 pwfsSad.sch
s -608 544 100 0 usage only for engineering purposes!
s -608 592 100 0 These are the real (underlying) 1-D motors
s -784 1824 100 0 These are the top-level n-D mechanisms from the ICD
s 288 1136 100 0 The ranges for Hi and Lo (HIHI/LOLO) will be put in later by a c routine.
[cell use]
use sircomb 240 2071 100 0 sircomb#271
xform 0 328 2176
p 448 2240 100 0 1 set1:f1 $(sadtop)probeflags.VAL
p 880 2112 100 0 1 set10:s5 $(sadtop)
p 448 2080 100 0 1 set11:f6 $(sadtop)
p 880 2080 100 0 1 set12:s6 $(sadtop)
p 448 2048 100 0 1 set13:f7 $(sadtop)
p 880 2048 100 0 1 set14:s7 $(sadtop)
p 880 2240 100 0 1 set2:s1 $(sadtop)probeflags.OMSS
p 448 2208 100 0 1 set3:f2 $(sadtop)fldstopflags.VAL
p 880 2208 100 0 1 set4:s2 $(sadtop)fldstopflags.OMSS
p 448 2176 100 0 1 set5:f3 $(sadtop)filterflags.VAL
p 880 2176 100 0 1 set6:s3 $(sadtop)filterflags.OMSS
p 448 2144 100 0 1 set7:f4 $(sadtop)
p 880 2144 100 0 1 set8:s4 $(sadtop)
p 448 2112 100 0 1 set9:f5 $(sadtop)
use esirs 1856 768 100 0 z
xform 0 1968 880
p 1856 704 100 0 1 DESC:Component z position
p 2016 864 100 0 1 EGU:mm
p 1856 672 100 0 1 FDSC:real position 
p 1968 896 100 0 1 FTVL:DOUBLE
p 1696 400 100 0 0 HHSV:MAJOR
p 1696 304 100 0 0 HSV:MINOR
p 1696 240 100 0 0 LLSV:MAJOR
p 1696 144 100 0 0 LSV:MINOR
p 2016 832 100 0 1 NELM:1
p 1896 504 100 0 0 NORD:1
p 2016 800 100 0 1 PREC:3
p 1856 576 100 0 1 PV:$(sadtop)
p 1856 640 100 0 1 SCAN:Passive
p 1856 608 100 0 1 SNAM:
use esirs 288 768 100 0 angle
xform 0 400 880
p 288 704 100 0 1 DESC:Real world probe angle
p 448 864 100 0 1 EGU:deg
p 288 672 100 0 1 FDSC:probe angle 
p 400 896 100 0 1 FTVL:DOUBLE
p 128 400 100 0 0 HHSV:MAJOR
p 128 304 100 0 0 HSV:MINOR
p 128 240 100 0 0 LLSV:MAJOR
p 128 144 100 0 0 LSV:MINOR
p 448 832 100 0 1 NELM:1
p 328 504 100 0 0 NORD:1
p 448 800 100 0 1 PREC:2
p 288 576 100 0 1 PV:$(sadtop)
p 288 640 100 0 1 SCAN:Passive
p 288 608 100 0 1 SNAM:
use esirs 1344 768 100 0 y
xform 0 1456 880
p 1344 704 100 0 1 DESC:Component y position
p 1504 864 100 0 1 EGU:mm
p 1344 672 100 0 1 FDSC:real position 
p 1456 896 100 0 1 FTVL:DOUBLE
p 1184 400 100 0 0 HHSV:MAJOR
p 1184 304 100 0 0 HSV:MINOR
p 1184 240 100 0 0 LLSV:MAJOR
p 1184 144 100 0 0 LSV:MINOR
p 1504 832 100 0 1 NELM:1
p 1384 504 100 0 0 NORD:1
p 1504 800 100 0 1 PREC:3
p 1344 576 100 0 1 PV:$(sadtop)
p 1344 640 100 0 1 SCAN:Passive
p 1344 608 100 0 1 SNAM:
use esirs 832 768 100 0 x
xform 0 944 880
p 832 704 100 0 1 DESC:Component x position
p 992 880 100 0 1 EGU:mm
p 832 672 100 0 1 FDSC:real position 
p 944 912 100 0 1 FTVL:DOUBLE
p 672 400 100 0 0 HHSV:MAJOR
p 672 304 100 0 0 HSV:MINOR
p 672 240 100 0 0 LLSV:MAJOR
p 672 144 100 0 0 LSV:MINOR
p 992 848 100 0 1 NELM:1
p 872 504 100 0 0 NORD:1
p 992 816 100 0 1 PREC:3
p 832 576 100 0 1 PV:$(sadtop)
p 832 640 100 0 1 SCAN:Passive
p 832 608 100 0 1 SNAM:
use esirs 1328 1472 100 0 tableEngPos
xform 0 1440 1584
p 1328 1408 100 0 1 DESC:table eng. pos.
p 1424 1584 100 0 1 EGU:eng.units
p 1328 1376 100 0 1 FDSC:eng. position 
p 1456 1616 100 0 1 FTVL:LONG
p 1168 1104 100 0 0 HHSV:MAJOR
p 1168 1008 100 0 0 HSV:MINOR
p 1168 944 100 0 0 LLSV:MAJOR
p 1168 848 100 0 0 LSV:MINOR
p 1488 1552 100 0 1 NELM:1
p 1368 1208 100 0 0 NORD:1
p 1488 1520 100 0 1 PREC:1
p 1328 1280 100 0 1 PV:$(sadtop)
p 1328 1344 100 0 1 SCAN:Passive
p 1328 1312 100 0 1 SNAM:
use esirs 800 1472 100 0 armAngle
xform 0 912 1584
p 800 1408 100 0 1 DESC:Real world probe arm pos.
p 960 1584 100 0 1 EGU:deg
p 800 1376 100 0 1 FDSC:real world position 
p 912 1616 100 0 1 FTVL:DOUBLE
p 640 1104 100 0 0 HHSV:MAJOR
p 640 1008 100 0 0 HSV:MINOR
p 640 944 100 0 0 LLSV:MAJOR
p 640 848 100 0 0 LSV:MINOR
p 960 1552 100 0 1 NELM:1
p 840 1208 100 0 0 NORD:1
p 960 1520 100 0 1 PREC:2
p 800 1280 100 0 1 PV:$(sadtop)
p 800 1344 100 0 1 SCAN:Passive
p 800 1312 100 0 1 SNAM:
use esirs 288 1472 100 0 tableAngle
xform 0 400 1584
p 288 1408 100 0 1 DESC:Real world table pos.
p 448 1584 100 0 1 EGU:deg
p 288 1376 100 0 1 FDSC:real position 
p 400 1616 100 0 1 FTVL:DOUBLE
p 288 1248 100 0 1 HHSV:MAJOR
p 672 1248 100 0 1 HIGH:0.0
p 560 1248 100 0 1 HIHI:0.0
p 432 1248 100 0 1 HSV:MINOR
p 288 1216 100 0 1 LLSV:MAJOR
p 560 1216 100 0 1 LOLO:0.0
p 672 1216 100 0 1 LOW:0.0
p 432 1216 100 0 1 LSV:MINOR
p 448 1552 100 0 1 NELM:1
p 328 1208 100 0 0 NORD:1
p 448 1520 100 0 1 PREC:2
p 288 1344 100 0 1 PV:$(sadtop)
p 288 1280 100 0 1 SCAN:Passive
p 288 1312 100 0 1 SNAM:
use esirs 1840 1472 100 0 armEngPos
xform 0 1952 1584
p 1840 1408 100 0 1 DESC:arm eng. pos.
p 1936 1584 100 0 1 EGU:eng.units
p 1840 1376 100 0 1 FDSC:eng. position 
p 1968 1616 100 0 1 FTVL:LONG
p 1680 1104 100 0 0 HHSV:MAJOR
p 1680 1008 100 0 0 HSV:MINOR
p 1680 944 100 0 0 LLSV:MAJOR
p 1680 848 100 0 0 LSV:MINOR
p 2000 1552 100 0 1 NELM:1
p 1880 1208 100 0 0 NORD:1
p 2000 1520 100 0 1 PREC:1
p 1840 1280 100 0 1 PV:$(sadtop)
p 1840 1344 100 0 1 SCAN:Passive
p 1840 1312 100 0 1 SNAM:
use hwin 1824 999 100 0 hwin#257
xform 0 1920 1040
p 1824 976 100 0 -1 val(in):$(sadtop)probePosA.VALC
use hwin 256 999 100 0 hwin#203
xform 0 352 1040
p 256 976 100 0 -1 val(in):$(sadtop)probePosA.VALF
use hwin 1312 999 100 0 hwin#197
xform 0 1408 1040
p 1312 976 100 0 -1 val(in):$(sadtop)probePosA.VALB
use hwin 1296 1703 100 0 hwin#116
xform 0 1392 1744
p 1248 1680 100 0 -1 val(in):$(sadtop)probeEngPosA.VALA
use hwin 768 1703 100 0 hwin#117
xform 0 864 1744
p 768 1680 100 0 -1 val(in):$(sadtop)probePosA.VALH
use hwin 256 1703 100 0 hwin#187
xform 0 352 1744
p 256 1680 100 0 -1 val(in):$(sadtop)probePosA.VALG
use hwin 800 999 100 0 hwin#190
xform 0 896 1040
p 800 976 100 0 -1 val(in):$(sadtop)probePosA.VALA
use hwin 1808 1703 100 0 hwin#245
xform 0 1904 1744
p 1760 1680 100 0 -1 val(in):$(sadtop)probeEngPosA.VALB
use pwfsSysSad -272 2071 100 0 pwfsSysSad#253
xform 0 -184 2176
use compSad -768 1040 100 0 fldstop
xform 0 -672 1152
p -768 1024 100 0 1 set1:mechanism fldstop
p -768 992 100 0 1 set2:mech fldstop
p -768 960 100 0 1 set3:hindex $(trigtop).C
p -768 928 100 0 1 set4:mindex $(trigtop).D
use compSad -384 1056 100 0 ndfilter
xform 0 -288 1152
p -384 1024 100 0 1 set1:mechanism filter
p -384 992 100 0 1 set2:mech filter
p -384 960 100 0 1 set3:hindex $(trigtop).E
p -384 928 100 0 1 set4:mindex $(trigtop).F
use compSad -112 279 100 0 focus
xform 0 -16 384
p -112 256 100 0 1 set1:mechanism focus
p -112 224 100 0 1 set2:mech focus
p -112 192 100 0 1 set3:hindex
p -112 160 100 0 1 set4:mindex
use compSad -768 1543 100 0 probe
xform 0 -672 1648
p -768 1520 100 0 1 set1:mechanism probe
p -768 1488 100 0 1 set2:mech probe
p -768 1456 100 0 1 set3:hindex $(trigtop).A
p -768 1424 100 0 1 set4:mindex $(trigtop).B
p -768 1392 100 0 1 set7:possir tableAngle
p -768 1360 100 0 1 set8:engsir tableEngPos
use compSad -448 279 100 0 RT34
xform 0 -352 384
p -448 256 100 0 1 set1:mechanism RT34
p -448 224 100 0 1 set2:mech RT34
p -448 192 100 0 1 set3:hindex
p -448 160 100 0 1 set4:mindex
use compSad -800 279 100 0 PA34
xform 0 -704 384
p -800 256 100 0 1 set1:mechanism PA34
p -800 224 100 0 1 set2:mech PA34
p -800 192 100 0 1 set3:hindex
p -800 160 100 0 1 set4:mindex
use bc200tr -1024 -104 -100 0 frame
xform 0 656 1200
p 1552 64 100 0 1 author:O.Frischmuth
p 1776 48 100 0 -1 border:C
p 1552 32 100 0 1 checked:O.Frischmuth
p 1808 48 100 0 -1 date:15 May 97
p 1792 176 100 0 -1 project:A&G Control System
p 1792 112 100 0 -1 title:GBD/PWFS SAD schematic
[comments]
