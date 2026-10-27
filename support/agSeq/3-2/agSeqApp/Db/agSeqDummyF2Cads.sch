[schematic2]
uniq 63
[tools]
[detail]
w 2800 1659 100 0 n#52 agSeqDummyTolCad.agSeqDummyTolCad#50.YTOL 2736 1648 2912 1648 outhier.YTOL.p
w 2800 1723 100 0 n#51 agSeqDummyTolCad.agSeqDummyTolCad#50.XTOL 2736 1712 2912 1712 outhier.XTOL.p
w 504 1195 100 0 n#47 eaos.probePatrolYHiLim.VAL 416 1184 640 1184 640 1600 768 1600 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMAX
w 488 1515 100 0 n#46 eaos.probePatrolYLoLim.VAL 416 1504 608 1504 608 1664 768 1664 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMIN
w 488 1835 100 0 n#45 eaos.probePatrolXHiLim.VAL 416 1824 608 1824 608 1728 768 1728 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMAX
w 504 2187 100 0 n#44 eaos.probePatrolXLoLim.VAL 416 2176 640 2176 640 1792 768 1792 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMIN
s 1120 2256 200 0 Commands for F2 WFS simulator
s 2704 80 100 0 Dummy instrument CAD records
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDummyF2Cads.sch,v 1.2 2010/01/12 02:27:03 gemvx Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use agSeqDummyCad 800 839 100 0 agSeqDummyCad#62
xform 0 928 1072
p 816 832 100 0 -1 seta:cad filtSel
p 816 800 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 2496 263 100 0 agSeqDummyCad#61
xform 0 2624 496
p 2512 256 100 0 -1 seta:cad fldstopSel
p 2512 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 2144 263 100 0 agSeqDummyCad#60
xform 0 2272 496
p 2160 256 100 0 -1 seta:cad endVerify
p 2160 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 1792 263 100 0 agSeqDummyCad#59
xform 0 1920 496
p 1808 256 100 0 -1 seta:cad verify
p 1808 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 1440 263 100 0 agSeqDummyCad#58
xform 0 1568 496
p 1456 256 100 0 -1 seta:cad reboot
p 1456 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 1088 263 100 0 agSeqDummyCad#57
xform 0 1216 496
p 1104 256 100 0 -1 seta:cad debug
p 1104 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 736 263 100 0 agSeqDummyCad#56
xform 0 864 496
p 752 256 100 0 -1 seta:cad datum
p 752 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 384 263 100 0 agSeqDummyCad#55
xform 0 512 496
p 400 256 100 0 -1 seta:cad test
p 400 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 32 263 100 0 agSeqDummyCad#54
xform 0 160 496
p 48 256 100 0 -1 seta:cad init
p 48 224 100 0 -1 setb:snam agSeqF2GenericCAD
use agSeqDummyCad 1536 1575 100 0 agSeqDummyCad#49
xform 0 1664 1808
p 1536 1552 100 0 1 seta:cad stop
p 1536 1520 100 0 1 setb:snam agSeqF2StopCAD
use agSeqDummyCad 1184 1575 100 0 agSeqDummyCad#48
xform 0 1312 1808
p 1184 1552 100 0 1 seta:cad follow
p 1184 1520 100 0 1 setb:snam agSeqF2FollowCAD
use agSeqDummyParkCad 1920 1527 100 0 agSeqDummyParkCad#53
xform 0 2080 1800
p 1920 1520 100 0 1 seta:cad park
p 1920 1472 100 0 1 setb:snam agSeqF2ParkCAD
use outhier 2880 1607 100 0 YTOL
xform 0 2896 1648
use outhier 2880 1671 100 0 XTOL
xform 0 2896 1712
use agSeqDummyTolCad 2416 1527 100 0 agSeqDummyTolCad#50
xform 0 2576 1800
p 2416 1504 100 0 1 seta:cad tolerance
p 2416 1456 100 0 1 setb:snam agSeqF2ToleranceCAD
use agSeqDummyMoveCad 768 1511 100 0 agSeqDummyMoveCad#43
xform 0 928 1784
p 832 1488 100 0 1 seta:cad move
p 832 1456 100 0 1 setb:snam agSeqF2MoveCAD
use eaos 160 1095 100 0 probePatrolYHiLim
xform 0 288 1184
p 208 1280 100 0 -1 DESC:Max. Y limit
p 400 1280 100 0 1 EGU:mm
p -96 1038 100 0 0 PREC:3
use eaos 160 1415 100 0 probePatrolYLoLim
xform 0 288 1504
p 208 1600 100 0 -1 DESC:Min. Y limit
p 400 1600 100 0 1 EGU:mm
p -96 1358 100 0 0 PREC:3
use eaos 160 1735 100 0 probePatrolXHiLim
xform 0 288 1824
p 208 1920 100 0 -1 DESC:Max. X limit
p 400 1920 100 0 1 EGU:mm
p -96 1678 100 0 0 PREC:3
use eaos 160 2087 100 0 probePatrolXLoLim
xform 0 288 2176
p 208 2272 100 0 -1 DESC:Min. X limit
p 400 2272 100 0 1 EGU:mm
p -96 2030 100 0 0 PREC:3
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
