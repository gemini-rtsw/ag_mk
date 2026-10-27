[schematic2]
uniq 98
[tools]
[detail]
w 1432 75 100 0 n#93 egenSub.parkState.FLNK 1344 64 1568 64 1568 848 1712 848 efanouts.simFam.SLNK
w 1192 875 100 0 n#92 egenSub.followA.FLNK 1344 992 1472 992 1472 864 960 864 960 96 1056 96 egenSub.parkState.SLNK
w 624 987 100 0 n#91 inhier.XTOL.P 432 976 864 976 864 1504 1056 1504 egenSub.followA.INPD
w 1880 1995 100 0 n#89 egenSub.followA.OUTF 1344 1376 1536 1376 1536 1984 2272 1984 2272 2112 2432 2112 elongouts.folIsFollow.SLNK
w 1632 2139 100 0 n#87 egenSub.followA.OUTE 1344 1440 1504 1440 1504 2128 1808 2128 estringouts.probeState.SLNK
w 1608 939 100 0 n#84 egenSub.followA.VALJ 1344 1152 1504 1152 1504 928 1760 928 efanouts.simFam.SELL
w 1960 523 100 0 n#83 egenSub.followA.VALI 1344 1216 1536 1216 1536 512 2432 512 elongouts.probeCarVal.DOL
w 1880 1035 100 0 n#82 egenSub.followA.VALH 1344 1280 1568 1280 1568 1024 2240 1024 2240 800 2432 800 eaos.trackId.DOL
w 2280 491 100 0 n#81 efanouts.simFam.LNK3 1952 864 2176 864 2176 480 2432 480 elongouts.probeCarVal.SLNK
w 2056 907 100 0 n#80 efanouts.simFam.LNK2 1952 896 2208 896 2208 768 2432 768 eaos.trackId.SLNK
w 1992 1099 100 0 n#79 egenSub.followA.VALG 1344 1344 1600 1344 1600 1088 2432 1088 elongouts.probeInPos.DOL
w 2056 939 100 0 n#78 efanouts.simFam.LNK1 1952 928 2208 928 2208 1056 2432 1056 elongouts.probeInPos.SLNK
w 1480 1707 100 0 n#71 egenSub.followA.OUTA 1344 1696 1664 1696 1664 1824 1824 1824 eaos.prbxPos.SLNK
w 1928 1323 100 0 n#70 egenSub.followA.OUTD 1344 1504 1632 1504 1632 1312 2272 1312 2272 1440 2432 1440 eaos.probeYErr.SLNK
w 1480 1579 100 0 n#69 egenSub.followA.OUTC 1344 1568 1664 1568 1664 1440 1824 1440 eaos.probeXErr.SLNK
w 1784 1643 100 0 n#66 egenSub.followA.OUTB 1344 1632 2272 1632 2272 1824 2432 1824 eaos.prbyPos.SLNK
w 696 1131 100 0 n#63 eaos.probeMaxVel.VAL 608 1120 832 1120 832 1568 1056 1568 egenSub.followA.INPC
w 904 1643 100 0 n#62 eaos.probeYdef.VAL 608 1408 800 1408 800 1632 1056 1632 egenSub.followA.INPB
w 904 1707 100 0 n#61 eaos.probeXdef.VAL 608 1712 800 1712 800 1696 1056 1696 egenSub.followA.INPA
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqDummyNirsWfs.sch,v 1.3 2010/01/12 02:27:03 gemvx Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2704 80 100 0 Simulation of WFS probe
s 1328 2288 200 0 NIRS WFS simulator
s 1024 1952 100 0 The simulation scan rate is set
s 1024 1920 100 0 to .1 second by pvload. This allows
s 1024 1888 100 0 time to set the default values.
[cell use]
use estringouts 32 135 100 0 filtName
xform 0 160 208
use eaos 32 295 100 0 focPos
xform 0 160 384
use eaos 32 487 100 0 focMin
xform 0 160 576
use eaos 32 679 100 0 focMax
xform 0 160 768
use egenSub 1056 7 100 0 parkState
xform 0 1200 432
p 899 747 100 0 0 DESC:Display parked state
p 1152 800 100 0 1 FTVA:LONG
p 1184 -16 100 0 1 SNAM:agSeqNirsParkState
use egenSub 1056 935 100 0 followA
xform 0 1200 1360
p 1104 1808 100 0 -1 DESC:Simulate GMOS WFS
p 833 613 100 0 0 FTVE:STRING
p 833 549 100 0 0 FTVF:LONG
p 833 549 100 0 0 FTVG:LONG
p 833 517 100 0 0 FTVH:DOUBLE
p 833 485 100 0 0 FTVI:LONG
p 833 453 100 0 0 FTVJ:LONG
p 1152 1184 100 0 1 NOJ:6
p 768 1486 100 0 0 PREC:14
p 1120 784 100 0 0 SCAN:Passive
p 1184 912 100 0 1 SNAM:agSeqNirsSimulate
p 1344 1706 75 0 -1 pproc(OUTA):PP
p 1344 1642 75 0 -1 pproc(OUTB):PP
p 1344 1578 75 0 -1 pproc(OUTC):PP
p 1344 1514 75 0 -1 pproc(OUTD):PP
p 1344 1450 75 0 -1 pproc(OUTE):PP
p 1344 1392 75 0 -1 pproc(OUTF):PP
use elongouts 2432 967 100 0 probeInPos
xform 0 2560 1056
p 2448 1152 100 0 -1 DESC:In Position status
p 2272 974 100 0 0 OMSL:closed_loop
p 2784 1024 100 0 -1 def(OUT):$(ag)inPos:nirsInpos
p 2688 1024 75 768 -1 pproc(OUT):PP
use elongouts 2432 391 100 0 probeCarVal
xform 0 2560 480
p 2448 576 100 0 -1 DESC:Simulation CAR value
p 2272 398 100 0 0 OMSL:closed_loop
p 2800 432 100 0 -1 def(OUT):$(top)simC.IVAL
p 2688 448 75 768 -1 pproc(OUT):PP
use elongouts 2432 2023 100 0 folIsFollow
xform 0 2560 2112
p 2480 2192 100 0 -1 DESC:Follow state
p 2272 2254 100 0 0 EGU:None
use estringouts 1808 2055 100 0 probeState
xform 0 1936 2128
p 1856 2208 100 0 -1 DESC:State of probe
p 1744 2094 100 0 0 VAL:IDLE
use eaos 352 1319 100 0 probeYdef
xform 0 480 1408
p 368 1504 100 0 -1 DESC:Default Y position
p 624 1504 100 0 1 EGU:mm
p 96 1262 100 0 0 PREC:3
use eaos 352 1623 100 0 probeXdef
xform 0 480 1712
p 368 1808 100 0 -1 DESC:Default X position
p 624 1808 100 0 1 EGU:mm
p 96 1566 100 0 0 PREC:3
use eaos 1824 1735 100 0 prbxPos
xform 0 1952 1824
p 1568 1294 100 0 0 ADEL:0.0005
p 1840 1920 100 0 -1 DESC:Current X position
p 2096 1920 100 0 1 EGU:mm
p 1568 1262 100 0 0 MDEL:0.0005
p 1568 1678 100 0 0 PREC:3
use eaos 2432 1735 100 0 prbyPos
xform 0 2560 1824
p 2176 1294 100 0 0 ADEL:0.0005
p 2448 1920 100 0 -1 DESC:Current Y position
p 2704 1920 100 0 1 EGU:mm
p 2176 1262 100 0 0 MDEL:0.0005
p 2176 1678 100 0 0 PREC:3
use eaos 1824 1351 100 0 probeXErr
xform 0 1952 1440
p 1568 910 100 0 0 ADEL:0.0005
p 1792 1536 100 0 -1 DESC:Current X position error
p 2096 1536 100 0 1 EGU:mm
p 1568 878 100 0 0 MDEL:0.0005
p 1568 1294 100 0 0 PREC:3
use eaos 2432 1351 100 0 probeYErr
xform 0 2560 1440
p 2176 910 100 0 0 ADEL:0.0005
p 2400 1536 100 0 -1 DESC:Current Y position error
p 2704 1536 100 0 1 EGU:mm
p 2176 878 100 0 0 MDEL:0.0005
p 2176 1294 100 0 0 PREC:3
use eaos 352 1031 100 0 probeMaxVel
xform 0 480 1120
p 368 1216 100 0 -1 DESC:Probe Maximum velocity
p 624 1216 100 0 1 EGU:mm/s
p 96 974 100 0 0 PREC:3
use eaos 2432 679 100 0 trackId
xform 0 2560 768
p 2464 864 100 0 -1 DESC:Track identifier
p 2400 494 100 0 0 EGU:none
p 2176 750 100 0 0 OMSL:closed_loop
use efanouts 1712 711 100 0 simFam
xform 0 1832 864
p 1840 688 100 0 1 SELM:Mask
use inhier 416 935 100 0 XTOL
xform 0 432 976
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
