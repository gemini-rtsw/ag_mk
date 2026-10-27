[schematic2]
uniq 57
[tools]
[detail]
w 1384 523 100 0 n#47 junction 1344 1168 1344 512 1472 512 agSeqOiwfsOnlyCad.agSeqOiwfsOnlyCad#53.OIWFS
w 1328 1179 100 0 n#47 inhier.OIWFS.P 48 1168 2656 1168 2656 1568 2688 1568 agSeqOiwfsOnlyCad.agSeqOiwfsOnlyCad#55.OIWFS
w 2040 1579 100 0 n#47 junction 2016 1168 2016 1568 2112 1568 agSeqOiwfsOnlyCad.agSeqOiwfsOnlyCad#54.OIWFS
w 1384 1579 100 0 n#47 junction 1344 1168 1344 1568 1472 1568 agSeqOiwfsOnlyCad.agSeqOiwfsOnlyCad#49.OIWFS
w 792 1579 100 0 n#47 junction 768 1168 768 1568 864 1568 agSeqOiwfsOnlyCad.agSeqOiwfsOnlyCad#50.OIWFS
w 2648 523 100 0 n#47 junction 2656 1168 2656 512 2688 512 agSeqOiwfsFollow.agSeqOiwfsFollow#51.OIWFS
w 2040 523 100 0 n#47 junction 2016 1168 2016 512 2112 512 agSeqOiwfsOnlyCad.agSeqOiwfsOnlyCad#52.OIWFS
w 792 523 100 0 n#47 junction 768 1168 768 512 864 512 agSeqOiwfsParkCad.agSeqOiwfsParkCad#56.OIWFS
s 2672 80 100 0 OIWFS specific commands
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqOiwfsCommands.sch,v 1.10 2007/05/18 22:29:21 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use agSeqOiwfsParkCad 864 455 100 0 agSeqOiwfsParkCad#56
xform 0 1008 752
p 928 432 100 0 1 seta:cad probePark
p 928 400 100 0 1 setb:snam agSeqCADCommon
use agSeqOiwfsOnlyCad 2688 1511 100 0 agSeqOiwfsOnlyCad#55
xform 0 2832 1808
p 2752 1488 100 0 1 seta:cad probeMove
p 2752 1456 100 0 1 setb:snam agSeqCADmove
p 2752 1424 100 0 1 setc:mask 4095
p 2752 1392 100 0 1 setd:gmsubcad move
p 2752 1360 100 0 1 sete:nirssubcad prbMove
p 2752 1328 100 0 1 setf:nirisubcad prbMove
p 2752 1296 100 0 1 setg:f2subcad move
p 2752 1264 100 0 1 seth:nifssubcad prbMove
p 2752 1232 100 0 1 seti:nicisubcad prbMove
use agSeqOiwfsOnlyCad 2112 1511 100 0 agSeqOiwfsOnlyCad#54
xform 0 2256 1808
p 2176 1488 100 0 1 seta:cad stop
p 2176 1456 100 0 1 setb:snam agSeqCADCommon
p 2176 1424 100 0 1 setc:mask 4095
p 2176 1392 100 0 1 setd:gmsubcad stop
p 2176 1360 100 0 1 sete:nirssubcad folStop
p 2176 1328 100 0 1 setf:nirisubcad folStop
p 2176 1296 100 0 1 setg:f2subcad stop
p 2176 1264 100 0 1 seth:nifssubcad folStop
p 2176 1232 100 0 1 seti:nicisubcad folStop
use agSeqOiwfsOnlyCad 1472 455 100 0 agSeqOiwfsOnlyCad#53
xform 0 1616 752
p 1536 432 100 0 1 seta:cad fldstopSel
p 1536 400 100 0 1 setb:snam agSeqCADfldStopSel
p 1536 368 100 0 1 setc:mask 4033
p 1536 336 100 0 1 setd:gmsubcad fldstopSel
p 1536 304 100 0 1 sete:nirssubcad fldstopSel
p 1536 272 100 0 1 setf:nirisubcad fldstopSel
p 1536 240 100 0 1 setg:f2subcad fldstopSel
p 1536 208 100 0 1 seth:nifssubcad fldstopSel
p 1536 176 100 0 1 seti:nicisubcad fldstopSel
use agSeqOiwfsOnlyCad 1472 1511 100 0 agSeqOiwfsOnlyCad#49
xform 0 1616 1808
p 1536 1488 100 0 1 seta:cad follow
p 1536 1456 100 0 1 setb:snam agSeqCADCommon
p 1536 1424 100 0 1 setc:mask 4095
p 1536 1392 100 0 1 setd:gmsubcad follow
p 1536 1360 100 0 1 sete:nirssubcad folFollow
p 1536 1328 100 0 1 setf:nirisubcad folFollow
p 1536 1296 100 0 1 setg:f2subcad follow
p 1536 1264 100 0 1 seth:nifssubcad folFollow
p 1536 1232 100 0 1 seti:nicisubcad folFollow
use agSeqOiwfsOnlyCad 864 1511 100 0 agSeqOiwfsOnlyCad#50
xform 0 1008 1808
p 928 1488 100 0 1 seta:cad tolerance
p 928 1456 100 0 1 setb:snam agSeqCADmove
p 928 1424 100 0 1 setc:mask 4095
p 928 1392 100 0 1 setd:gmsubcad tolerance
p 928 1360 100 0 1 sete:nirssubcad folSetTol
p 928 1328 100 0 1 setf:nirisubcad folSetTol
p 928 1296 100 0 1 setg:f2subcad tolerance
p 928 1264 100 0 1 seth:nifssubcad folSetTol
p 928 1232 100 0 1 seti:nicisubcad folSetTol
use agSeqOiwfsOnlyCad 2112 455 100 0 agSeqOiwfsOnlyCad#52
xform 0 2256 752
p 2176 432 100 0 1 seta:cad filterSel
p 2176 400 100 0 1 setb:snam agSeqCADfilterSel
p 2176 368 100 0 1 setc:mask 4095
p 2176 336 100 0 1 setd:gmsubcad filtSel
p 2176 304 100 0 1 sete:nirssubcad filtSel
p 2176 272 100 0 1 setf:nirisubcad filtSel
p 2176 240 100 0 1 setg:f2subcad filtSel
p 2176 208 100 0 1 seth:nifssubcad filtSel
p 2176 176 100 0 1 seti:nicisubcad filtSel
use agSeqOiwfsFollow 2688 455 100 0 agSeqOiwfsFollow#51
xform 0 2832 752
p 2708 428 100 0 1 seta:top $(top)follow:
use inhier 32 1127 100 0 OIWFS
xform 0 48 1168
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
