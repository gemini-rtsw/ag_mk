[schematic2]
uniq 5
[tools]
[detail]
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqSiteDepGN.sch,v 1.1 2013/05/29 16:34:16 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
s 848 896 200 0 include simulation databases for GS instruments
[cell use]
use agSeqNiciSim 1152 487 100 0 agSeqNiciSim#4
xform 0 1472 672
p 1168 464 100 0 -1 seta:top niciSim:wfs:
use agSeqNirsSim 1920 487 100 0 agSeqNirsSim#3
xform 0 2240 672
p 1940 460 100 0 -1 seta:top nirsSim:wfs:
use agSeqF2Sim 384 487 100 0 agSeqF2Sim#2
xform 0 704 672
p 404 460 100 0 -1 seta:top f2Sim:wfs:
use agSeq 1240 1208 100 0 agSeq#0
xform 0 1584 1408
p 1280 1424 100 0 -1 setoiwfs01:gmos gm:
p 1712 1424 100 0 -1 setoiwfs02:nirs nirsSim:
p 1504 1424 100 0 -1 setoiwfs03:niri niri:
p 1936 1424 100 0 -1 setoiwfs04:f2 f2Sim:
p 1056 1296 100 0 -1 setoiwfs05:nifs nifs:
p 1488 1296 100 0 -1 setoiwfs06:gsaoi gsaoiSim:
p 1280 1296 100 0 -1 setoiwfs07:nici niciSim:
p 1728 1296 100 0 -1 setoiwfs08:gpi gpiSim:
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
