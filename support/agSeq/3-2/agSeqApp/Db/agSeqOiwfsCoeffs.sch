[schematic2]
uniq 3
[tools]
[detail]
w 1310 939 100 0 n#1 egenSub.oiwfsCoeffs.VALJ 1056 928 1600 928 outhier.c#3.p
w 502 1483 100 0 n#2 inhier.OIWFS.P 272 1472 768 1472 egenSub.oiwfsCoeffs.INPA
s 2432 2336 100 0 $Id: agSeqOiwfsCoeffs.sch,v 1.1 2001/10/04 09:05:43 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2416 144 100 0 Copyright
s 2416 112 100 0 Observatory
s 2416 80 100 0 Sciences Ltd.
s 2688 80 100 0 Probe offsets
s 832 2176 200 0 This schematic simply provides the current set of
s 832 2128 200 0 transformation coefficients for the currently selected OIWFS.
s 832 2064 200 0 This information is used by the TCS to check probe limits.
[cell use]
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use inhier 256 1431 100 0 OIWFS
xform 0 272 1472
use outhier 1568 887 100 0 c#3
xform 0 1584 928
use egenSub 768 711 100 0 oiwfsCoeffs
xform 0 912 1136
p 784 1584 100 0 -1 DESC:Select transformation coefficients
p 545 485 100 0 0 FTA:LONG
p 545 101 100 0 0 NOB:1
p 545 133 100 0 0 NOVA:1
p 545 101 100 0 0 NOVB:1
p 896 912 100 0 1 NOVJ:6
p 480 1262 100 0 0 PREC:14
p 832 608 100 0 1 SCAN:1 second
p 832 640 100 0 1 SNAM:agSeqOiwfsCoeffs
p 208 1344 100 0 0 def(INPB):0.0
p 880 704 100 1024 0 name:$(ag)oi:$(I)
p 480 1118 100 0 1 INAM:agSeqInitTransform
[comments]
