[schematic2]
uniq 63
[tools]
[detail]
w 2880 1755 100 0 n#52 agSeqDummyTolCad.agSeqDummyTolCad#50.YTOL 2816 1744 2992 1744 outhier.YTOL.p
w 2880 1819 100 0 n#51 agSeqDummyTolCad.agSeqDummyTolCad#50.XTOL 2816 1808 2992 1808 outhier.XTOL.p
w 408 1211 100 0 n#47 eaos.prbyMaxmm.VAL 320 1200 544 1200 544 1616 672 1616 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMAX
w 392 1531 100 0 n#46 eaos.prbyMinmm.VAL 320 1520 512 1520 512 1680 672 1680 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMIN
w 392 1851 100 0 n#45 eaos.prbxMax.VAL 320 1840 512 1840 512 1744 672 1744 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMAX
w 408 2203 100 0 n#44 eaos.prbxMin.VAL 320 2192 544 2192 544 1808 672 1808 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMIN
s 1120 2256 200 0 Commands for NICI WFS simulator
s 2704 80 100 0 Dummy instrument CAD records
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDummyNiciCads.sch,v 1.2 2010/01/12 02:27:03 gemvx Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use agSeqDummyCad 1472 1703 100 0 agSeqDummyCad#49
xform 0 1600 1936
p 1472 1680 100 0 1 seta:cad folStop
p 1472 1648 100 0 1 setb:snam agSeqNiciStopCAD
use agSeqDummyCad 1088 1703 100 0 agSeqDummyCad#48
xform 0 1216 1936
p 1088 1680 100 0 1 seta:cad folFollow
p 1088 1648 100 0 1 setb:snam agSeqNiciFollowCAD
use agSeqDummyCad 1872 263 100 0 agSeqDummyCad#54
xform 0 2000 496
p 1892 236 100 0 1 seta:cad verify
p 1824 208 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 2224 263 100 0 agSeqDummyCad#55
xform 0 2352 496
p 2244 236 100 0 1 seta:cad endVerify
p 2208 208 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 1136 199 100 0 agSeqDummyCad#56
xform 0 1264 432
p 1156 172 100 0 1 seta:cad debug
p 1088 144 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 1488 199 100 0 agSeqDummyCad#57
xform 0 1616 432
p 1508 172 100 0 1 seta:cad reboot
p 1440 144 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 432 199 100 0 agSeqDummyCad#58
xform 0 560 432
p 452 172 100 0 1 seta:cad test
p 384 144 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 784 199 100 0 agSeqDummyCad#59
xform 0 912 432
p 804 172 100 0 1 seta:cad datum
p 736 144 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 64 199 100 0 agSeqDummyCad#60
xform 0 192 432
p 84 172 100 0 1 seta:cad init
p 16 144 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 2592 263 100 0 agSeqDummyCad#61
xform 0 2720 496
p 2612 236 100 0 1 seta:cad fldstopSel
p 2544 208 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyCad 640 727 100 0 agSeqDummyCad#62
xform 0 768 960
p 660 700 100 0 1 seta:cad filtSel
p 592 672 100 0 1 setb:snam agSeqNiciGenericCAD
use agSeqDummyParkCad 1968 1639 100 0 agSeqDummyParkCad#53
xform 0 2128 1912
p 1968 1632 100 0 1 seta:cad park
p 1968 1584 100 0 1 setb:snam agSeqNiciParkCAD
use outhier 2960 1703 100 0 YTOL
xform 0 2976 1744
use outhier 2960 1767 100 0 XTOL
xform 0 2976 1808
use agSeqDummyTolCad 2496 1623 100 0 agSeqDummyTolCad#50
xform 0 2656 1896
p 2496 1600 100 0 1 seta:cad folSetTol
p 2496 1552 100 0 1 setb:snam agSeqNiciToleranceCAD
use agSeqDummyMoveCad 672 1527 100 0 agSeqDummyMoveCad#43
xform 0 832 1800
p 736 1504 100 0 1 seta:cad prbMove
p 736 1472 100 0 1 setb:snam agSeqNiciMoveCAD
use eaos 64 1111 100 0 prbyMaxmm
xform 0 192 1200
p 112 1296 100 0 -1 DESC:Max. Y limit
p 304 1296 100 0 1 EGU:mm
p -192 1054 100 0 0 PREC:3
use eaos 64 1431 100 0 prbyMinmm
xform 0 192 1520
p 112 1616 100 0 -1 DESC:Min. Y limit
p 304 1616 100 0 1 EGU:mm
p -192 1374 100 0 0 PREC:3
use eaos 64 1751 100 0 prbxMax
xform 0 192 1840
p 112 1936 100 0 -1 DESC:Max. X limit
p 304 1936 100 0 1 EGU:mm
p -192 1694 100 0 0 PREC:3
use eaos 64 2103 100 0 prbxMin
xform 0 192 2192
p 112 2288 100 0 -1 DESC:Min. X limit
p 304 2288 100 0 1 EGU:mm
p -192 2046 100 0 0 PREC:3
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
