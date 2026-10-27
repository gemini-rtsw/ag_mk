[schematic2]
uniq 63
[tools]
[detail]
w 2816 1739 100 0 n#52 agSeqDummyTolCad.agSeqDummyTolCad#50.YTOL 2752 1728 2928 1728 outhier.YTOL.p
w 2816 1803 100 0 n#51 agSeqDummyTolCad.agSeqDummyTolCad#50.XTOL 2752 1792 2928 1792 outhier.XTOL.p
w 440 1195 100 0 n#47 eaos.prbyMax.VAL 352 1184 576 1184 576 1600 704 1600 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMAX
w 424 1515 100 0 n#46 eaos.prbyMin.VAL 352 1504 544 1504 544 1664 704 1664 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMIN
w 424 1835 100 0 n#45 eaos.prbxMax.VAL 352 1824 544 1824 544 1728 704 1728 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMAX
w 440 2187 100 0 n#44 eaos.prbxMin.VAL 352 2176 576 2176 576 1792 704 1792 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMIN
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqDummyNirsCads.sch,v 1.2 2010/01/12 02:27:03 gemvx Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2704 80 100 0 Dummy instrument CAD records
s 1120 2256 200 0 Commands for NIRS WFS simulator
[cell use]
use agSeqDummyCad 736 871 100 0 agSeqDummyCad#62
xform 0 864 1104
p 736 864 100 0 -1 seta:cad filtSel
p 736 832 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 2512 327 100 0 agSeqDummyCad#61
xform 0 2640 560
p 2512 320 100 0 -1 seta:cad fldstopSel
p 2512 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 2144 327 100 0 agSeqDummyCad#60
xform 0 2272 560
p 2144 320 100 0 -1 seta:cad endVerify
p 2144 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 1792 327 100 0 agSeqDummyCad#59
xform 0 1920 560
p 1792 320 100 0 -1 seta:cad verify
p 1792 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 1440 327 100 0 agSeqDummyCad#58
xform 0 1568 560
p 1440 320 100 0 -1 seta:cad reboot
p 1440 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 1088 327 100 0 agSeqDummyCad#57
xform 0 1216 560
p 1088 320 100 0 -1 seta:cad debug
p 1088 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 736 327 100 0 agSeqDummyCad#56
xform 0 864 560
p 736 320 100 0 -1 seta:cad datum
p 736 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 384 327 100 0 agSeqDummyCad#55
xform 0 512 560
p 384 320 100 0 -1 seta:cad test
p 384 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 32 327 100 0 agSeqDummyCad#54
xform 0 160 560
p 32 320 100 0 -1 seta:cad init
p 32 288 100 0 -1 setb:snam agSeqNirsGenericCAD
use agSeqDummyCad 1152 1671 100 0 agSeqDummyCad#48
xform 0 1280 1904
p 1152 1648 100 0 1 seta:cad folFollow
p 1152 1616 100 0 1 setb:snam agSeqNirsFollowCAD
use agSeqDummyCad 1536 1671 100 0 agSeqDummyCad#49
xform 0 1664 1904
p 1536 1648 100 0 1 seta:cad folStop
p 1536 1616 100 0 1 setb:snam agSeqNirsStopCAD
use agSeqDummyParkCad 1952 1607 100 0 agSeqDummyParkCad#53
xform 0 2112 1880
p 1952 1600 100 0 1 seta:cad park
p 1952 1552 100 0 1 setb:snam agSeqNirsParkCAD
use outhier 2896 1751 100 0 XTOL
xform 0 2912 1792
use outhier 2896 1687 100 0 YTOL
xform 0 2912 1728
use agSeqDummyTolCad 2432 1607 100 0 agSeqDummyTolCad#50
xform 0 2592 1880
p 2432 1584 100 0 1 seta:cad folSetTol
p 2432 1536 100 0 1 setb:snam agSeqNirsToleranceCAD
use agSeqDummyMoveCad 704 1511 100 0 agSeqDummyMoveCad#43
xform 0 864 1784
p 768 1488 100 0 1 seta:cad prbMove
p 768 1456 100 0 1 setb:snam agSeqNirsMoveCAD
use eaos 96 2087 100 0 prbxMin
xform 0 224 2176
p 144 2272 100 0 -1 DESC:Min. X limit
p 336 2272 100 0 1 EGU:mm
p -160 2030 100 0 0 PREC:3
use eaos 96 1735 100 0 prbxMax
xform 0 224 1824
p 144 1920 100 0 -1 DESC:Max. X limit
p 336 1920 100 0 1 EGU:mm
p -160 1678 100 0 0 PREC:3
use eaos 96 1415 100 0 prbyMin
xform 0 224 1504
p 144 1600 100 0 -1 DESC:Min. Y limit
p 336 1600 100 0 1 EGU:mm
p -160 1358 100 0 0 PREC:3
use eaos 96 1095 100 0 prbyMax
xform 0 224 1184
p 144 1280 100 0 -1 DESC:Max. Y limit
p 336 1280 100 0 1 EGU:mm
p -160 1038 100 0 0 PREC:3
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
