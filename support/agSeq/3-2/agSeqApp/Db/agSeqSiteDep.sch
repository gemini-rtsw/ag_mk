[schematic2]
uniq 1
[tools]
[detail]
s 2720 80 100 0 Top level schematic
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqSiteDep.sch,v 1.1 2013/05/29 16:34:16 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
s 752 928 200 0 include simulation databases for GN instruments
[cell use]
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use agSeqNirsSim 1888 519 100 0 agSeqNirsSim#1
xform 0 2208 704
p 1908 492 100 0 -1 seta:top nirsSim:wfs:
use agSeqNiriSim 1120 519 100 0 agSeqNiriSim#1
xform 0 1440 704
p 1140 492 100 0 -1 seta:top niriSim:wfs:
use agSeqNifsSim 352 519 100 0 agSeqNifsSim#1
xform 0 672 704
p 372 492 100 0 -1 seta:top nifsSim:wfs:
p 368 448 100 0 -1 setf:sadtop nifsSim:sad:wfs:
use agSeq 1240 1272 100 0 agSeq#0
xform 0 1584 1472
p 1264 1488 100 0 -1 setoiwfs01:gmos gm:
p 1712 1488 100 0 -1 setoiwfs02:nirs nirsSim:
p 1488 1488 100 0 -1 setoiwfs03:niri niriSim:
p 1936 1488 100 0 -1 setoiwfs04:f2 f2Sim:
p 1056 1360 100 0 -1 setoiwfs05:nifs nifsSim:
p 1488 1360 100 0 -1 setoiwfs06:gsaoi gsaoi:
p 1264 1360 100 0 -1 setoiwfs07:nici nici:
p 1728 1360 100 0 -1 setoiwfs08:gpi gpi:
use agSeqF2Sim 2336 1128 100 0 agSeqF2Sim#2
xform 0 2656 1288
p 2540 1091 100 0 1 set0:top f2Sim:wfs:
[comments]
