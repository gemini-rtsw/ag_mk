[schematic2]
uniq 54
[tools]
[detail]
w 2016 923 100 0 n#52 agSeqDummyTolCad.agSeqDummyTolCad#50.YTOL 1952 912 2128 912 outhier.YTOL.p
w 2016 987 100 0 n#51 agSeqDummyTolCad.agSeqDummyTolCad#50.XTOL 1952 976 2128 976 outhier.XTOL.p
w 600 811 100 0 n#47 eaos.probePatrolYHiLim.VAL 512 800 736 800 736 1216 864 1216 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMAX
w 584 1131 100 0 n#46 eaos.probePatrolYLoLim.VAL 512 1120 704 1120 704 1280 864 1280 agSeqDummyMoveCad.agSeqDummyMoveCad#43.YMIN
w 584 1451 100 0 n#45 eaos.probePatrolXHiLim.VAL 512 1440 704 1440 704 1344 864 1344 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMAX
w 600 1803 100 0 n#44 eaos.probePatrolXLoLim.VAL 512 1792 736 1792 736 1408 864 1408 agSeqDummyMoveCad.agSeqDummyMoveCad#43.XMIN
s 1120 2256 200 0 Commands for GMOS WFS simulator
s 2704 80 100 0 Dummy instrument CAD records
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDummyCads.sch,v 1.3 2003/02/07 16:56:06 cjm Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use agSeqDummyParkCad 928 247 100 0 agSeqDummyParkCad#53
xform 0 1088 520
p 928 240 100 0 1 seta:cad park
p 928 192 100 0 1 setb:snam agSeqGmParkCAD
use outhier 2096 871 100 0 YTOL
xform 0 2112 912
use outhier 2096 935 100 0 XTOL
xform 0 2112 976
use agSeqDummyTolCad 1632 791 100 0 agSeqDummyTolCad#50
xform 0 1792 1064
p 1632 768 100 0 1 seta:cad tolerance
p 1632 720 100 0 1 setb:snam agSeqGmToleranceCAD
use agSeqDummyCad 2240 1607 100 0 agSeqDummyCad#49
xform 0 2368 1840
p 2240 1584 100 0 1 seta:cad stop
p 2240 1552 100 0 1 setb:snam agSeqGmStopCAD
use agSeqDummyCad 1632 1607 100 0 agSeqDummyCad#48
xform 0 1760 1840
p 1632 1584 100 0 1 seta:cad follow
p 1632 1552 100 0 1 setb:snam agSeqGmFollowCAD
use agSeqDummyMoveCad 864 1127 100 0 agSeqDummyMoveCad#43
xform 0 1024 1400
p 928 1104 100 0 1 seta:cad move
p 928 1072 100 0 1 setb:snam agSeqGmMoveCAD
use eaos 256 711 100 0 probePatrolYHiLim
xform 0 384 800
p 304 896 100 0 -1 DESC:Max. Y limit
p 496 896 100 0 1 EGU:mm
p 0 654 100 0 0 PREC:3
use eaos 256 1031 100 0 probePatrolYLoLim
xform 0 384 1120
p 304 1216 100 0 -1 DESC:Min. Y limit
p 496 1216 100 0 1 EGU:mm
p 0 974 100 0 0 PREC:3
use eaos 256 1351 100 0 probePatrolXHiLim
xform 0 384 1440
p 304 1536 100 0 -1 DESC:Max. X limit
p 496 1536 100 0 1 EGU:mm
p 0 1294 100 0 0 PREC:3
use eaos 256 1703 100 0 probePatrolXLoLim
xform 0 384 1792
p 304 1888 100 0 -1 DESC:Min. X limit
p 496 1888 100 0 1 EGU:mm
p 0 1646 100 0 0 PREC:3
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
