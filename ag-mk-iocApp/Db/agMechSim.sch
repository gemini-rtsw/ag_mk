[schematic2]
uniq 22
[tools]
[detail]
w 1304 1323 100 0 n#21 egenSub.simulate.OUTB 1120 1312 1536 1312 elongouts.currPos.SLNK
w 1912 1291 100 0 n#20 elongouts.currPos.OUT 1792 1280 2080 1280 outhier.CURR.p
w -80 571 100 0 n#18 inhier.c#17.P -272 560 160 560 elongouts.simEnable.DOL
w 560 539 100 0 n#16 elongouts.simEnable.VAL 416 528 752 528 752 672 832 672 egenSub.simulate.SDIS
w 544 571 100 0 n#15 elongouts.simEnable.FLNK 416 560 720 560 720 704 832 704 egenSub.simulate.SLNK
w 520 811 100 0 n#11 eais.maxVel.VAL 416 800 672 800 672 1184 832 1184 egenSub.simulate.INPD
w 504 1067 100 0 n#10 eais.defPos.VAL 416 1056 640 1056 640 1248 832 1248 egenSub.simulate.INPC
w 606 1323 100 0 n#9 eais.noise.VAL 416 1312 832 1312 egenSub.simulate.INPB
w 510 1579 100 0 n#8 elongins.index.VAL 416 1568 640 1568 640 1376 832 1376 egenSub.simulate.INPA
s 1904 2128 100 0 $Id: agMechSim.sch,v 1.1 2000/12/20 13:50:09 cjm Exp $
s 1920 -64 100 0 Copyright
s 1920 -96 100 0 Observatory
s 1920 -128 100 0 Sciences Ltd.
s 1920 -176 100 0 Chris mayer
s 2208 -64 100 0 A & G
s 2144 -128 100 0 Mechanism simulator
[cell use]
use outhier 2048 1239 100 0 CURR
xform 0 2064 1280
use elongouts 1536 1223 100 0 currPos
xform 0 1664 1312
p 1504 1408 100 0 -1 DESC:Current mechanism position
p 1376 1454 100 0 0 EGU:units
use inhier -288 519 100 0 c#17
xform 0 -272 560
use elongouts 160 439 100 0 simEnable
xform 0 288 528
p 144 624 100 0 -1 DESC:Enable/disable simulator
p 0 446 100 0 0 OMSL:closed_loop
p 352 416 100 0 1 SCAN:.05 second
p -192 576 100 0 -1 def(DOL):$(ag)cc:simLevelL
use eais 160 1255 100 0 noise
xform 0 288 1328
p 224 1392 100 0 -1 DESC:Servo noise
p -96 1070 100 0 0 EGU:counts
use eais 160 999 100 0 defPos
xform 0 288 1072
p 160 1152 100 0 -1 DESC:Default start position
p -96 814 100 0 0 EGU:counts
use eais 160 743 100 0 maxVel
xform 0 288 816
p 160 896 100 0 -1 DESC:Maximum velocity
p -96 558 100 0 0 EGU:counts
use elongins 160 1511 100 0 index
xform 0 288 1584
p 192 1664 100 0 -1 DESC:Mechanism index
p -96 1582 100 0 0 EGU:units
use egenSub 832 615 100 0 simulate
xform 0 976 1040
p 675 1355 100 0 0 DESC:Mechanism simulator
p 896 464 100 0 1 DISV:0
p 609 389 100 0 0 FTA:LONG
p 609 389 100 0 0 FTVB:LONG
p 609 293 100 0 0 FTVE:LONG
p 609 229 100 0 0 FTVF:LONG
p 896 560 100 0 1 INAM:agMechSimInit
p 896 416 100 0 0 SCAN:Passive
p 896 512 100 0 1 SNAM:agMechSimulate
p 784 1386 75 0 -1 pproc(INPA):NPP
p 1120 1386 75 0 -1 pproc(OUTA):PP
p 1120 1322 75 0 -1 pproc(OUTB):PP
p 1120 1258 75 0 -1 pproc(OUTC):PP
p 1120 1194 75 0 -1 pproc(OUTD):PP
p 1120 1130 75 0 -1 pproc(OUTE):PP
p 1120 1066 75 0 -1 pproc(OUTF):PP
use bc200tr -672 -344 -100 0 frame
xform 0 1008 960
[comments]
