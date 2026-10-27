[schematic2]
uniq 11
[tools]
[detail]
w 368 1227 -100 0 c#9 inhier.c#9.P 112 1216 672 1216 672 1344 768 1344 egenSub.probeOffset.INPC
w 1310 939 100 0 n#8 egenSub.probeOffset.VALJ 1056 928 1600 928 outhier.c#3.p
w 358 1339 100 0 n#6 inhier.c#5.P 112 1328 640 1328 640 1408 768 1408 egenSub.probeOffset.INPB
w 502 1483 100 0 n#2 inhier.OIWFS.P 272 1472 768 1472 egenSub.probeOffset.INPA
s 832 2064 200 0 of the current index.
s 832 2128 200 0 relevant OIWFS and then selects the output on the basis
s 832 2176 200 0 This schematic pulls in the probe offset data from all the
s 2688 80 100 0 Probe offsets
s 2416 80 100 0 Sciences Ltd.
s 2416 112 100 0 Observatory
s 2416 144 100 0 Copyright
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqProbeOffset.sch,v 1.6 2009/12/03 22:18:50 gemvx Exp $
[cell use]
use inhier 96 1175 100 0 c#9
xform 0 112 1216
use inhier 96 1287 100 0 c#5
xform 0 112 1328
use inhier 256 1431 100 0 OIWFS
xform 0 272 1472
use outhier 1568 887 100 0 c#3
xform 0 1584 928
use egenSub 768 711 100 0 probeOffset
xform 0 912 1136
p 784 1584 100 0 -1 DESC:Select probe offset data
p 545 485 100 0 0 FTA:LONG
p 848 1408 100 0 1 NOB:9
p 848 1328 100 0 1 NOC:9
p 545 133 100 0 0 NOVA:1
p 545 101 100 0 0 NOVB:1
p 545 -155 100 0 0 NOVJ:9
p 480 1262 100 0 0 PREC:14
p 832 608 100 0 1 SCAN:.1 second
p 832 640 100 0 1 SNAM:agSeqProbeOffset
p 208 1344 100 0 -1 def(INPB):$(gmos)wfs:probeOffset.VALJ
p 208 1232 100 0 -1 def(INPC):$(f2)wfs:probeOffset.VALJ
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
