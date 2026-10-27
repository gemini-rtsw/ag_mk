[schematic2]
uniq 59
[tools]
[detail]
w 1232 2155 100 0 n#58 inhier.c#56.P 976 2144 1536 2144 ecalcs.ecalcs#51.INPA
w 1752 1707 100 0 n#55 ecalcs.ecalcs#51.VAL 1824 1952 1920 1952 1920 1696 1632 1696 1632 1536 1696 1536 elongouts.InPosition.DOL
w 1448 1675 100 0 n#54 elongins.RawInPos.VAL 1536 1472 1600 1472 1600 1664 1344 1664 1344 2112 1536 2112 ecalcs.ecalcs#51.INPB
w 1784 1675 100 0 n#53 ecalcs.ecalcs#51.FLNK 1824 1984 1952 1984 1952 1664 1664 1664 1664 1504 1696 1504 elongouts.InPosition.SLNK
w 1448 1643 100 0 n#52 elongins.RawInPos.FLNK 1536 1504 1568 1504 1568 1632 1376 1632 1376 1760 1536 1760 ecalcs.ecalcs#51.SLNK
w 2064 1131 100 0 n#50 elongouts.InPosition.OUT 1952 1472 2032 1472 2032 1120 2144 1120 elongouts.InPos.SLNK
w 1824 715 100 0 n#50 elongouts.InPosTrue.OUT 1664 704 2032 704 2032 1120 junction
w 1152 1099 100 0 n#47 efanouts.fan.LNK2 1136 1088 1216 1088 1216 1488 1280 1488 elongins.RawInPos.SLNK
w 1104 1531 100 0 n#46 inhier.c#22.P 976 1520 1280 1520 elongins.RawInPos.INP
w 1192 1131 100 0 n#43 efanouts.fan.LNK1 1136 1120 1296 1120 1296 736 1408 736 elongouts.InPosTrue.SLNK
w 2728 923 100 0 n#41 elongouts.InPos.FLNK 2400 1152 2624 1152 2624 912 2880 912 outhier.FLNK.p
w 2616 1131 100 0 n#40 elongouts.InPos.VAL 2400 1120 2880 1120 outhier.INPOSN.p
w 776 1163 100 0 n#39 ecalcs.inc.FLNK 768 1152 832 1152 832 1040 896 1040 efanouts.fan.SLNK
w 304 939 100 0 n#38 inhier.SLNK.P 176 928 480 928 ecalcs.inc.SLNK
w 832 1131 100 0 n#20 ecalcs.inc.VAL 768 1120 944 1120 efanouts.fan.SELL
w 1320 779 100 0 n#11 hwin.hwin#10.in 1280 768 1408 768 elongouts.InPosTrue.DOL
w 310 1323 -100 0 CC inhier.LOADED.P 176 1312 480 1312 ecalcs.inc.INPA
s 96 2048 100 0 when GMOS is modified.
s 96 2080 100 0 This schematic can be replaced by the standard agSeqSubsysInPosn
s 96 2144 100 0 when the probe is parked.
s 96 2176 100 0 overides the in position status returned by GMOS
s 96 2208 100 0 flag really means "ready to guide". This schematic 
s 96 2240 100 0 GMOS needs a special schematic as its "in posiiton"
s 1280 2240 200 0 Generate GMOS "inPosition" flag
s 2768 64 100 0 flag for A&G
s 2656 96 100 0 Generate overall "in position"
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqGmosInPosn.sch,v 1.1 2003/03/13 00:20:30 cjm Exp $
[cell use]
use inhier 960 2103 100 0 c#56
xform 0 976 2144
use ecalcs 1536 1671 100 0 ecalcs#51
xform 0 1680 1936
p 1712 1744 100 0 1 CALC:A=1?A:B
p 1056 2160 100 0 -1 def(INPA):$(ag)oiPark:gmos
use elongins 1280 1415 100 0 RawInPos
xform 0 1408 1488
p 1296 1568 100 0 -1 DESC:In position status
p 1024 1486 100 0 0 EGU:none
p 1056 1536 100 0 -1 def(INP):$(recname)
use outhier 2848 1079 100 0 INPOSN
xform 0 2864 1120
use outhier 2848 871 100 0 FLNK
xform 0 2864 912
use inhier 960 1479 100 0 c#22
xform 0 976 1520
use inhier 160 880 100 0 SLNK
xform 0 176 928
use inhier 160 1271 100 0 LOADED
xform 0 176 1312
use elongouts 2144 1031 100 0 InPos
xform 0 2272 1120
p 2144 1232 100 0 -1 DESC:Resultant GBDCC in position flag
p 1984 1006 100 0 0 IVOA:Set output to IVOV
p 1984 1038 100 0 0 OMSL:supervisory
p 1840 1184 100 0 0 def(DOL):0.0
use elongouts 1408 647 100 0 InPosTrue
xform 0 1536 736
p 1408 848 100 0 -1 DESC:Default GBDCC in position flag
p 1248 622 100 0 0 IVOA:Set output to IVOV
p 1248 654 100 0 0 OMSL:closed_loop
p 1104 800 100 0 0 def(DOL):0.0
p 1536 688 75 768 -1 pproc(OUT):PP
use elongouts 1696 1415 100 0 InPosition
xform 0 1824 1504
p 1696 1616 100 0 -1 DESC:In position status
p 1536 1390 100 0 0 IVOA:Set output to IVOV
p 1536 1422 100 0 0 OMSL:closed_loop
p 1392 1568 100 0 0 def(DOL):0.0
p 1952 1472 75 768 -1 pproc(OUT):PP
use ecalcs 480 839 100 0 inc
xform 0 624 1104
p 592 1056 100 0 1 CALC:A+1
p 464 1408 100 0 -1 DESC:Increment not loaded falg
p 624 848 100 0 1 SCAN:1 second
use hwin 1088 727 100 0 hwin#10
xform 0 1184 768
p 1091 760 100 0 -1 val(in):1
use efanouts 896 903 100 0 fan
xform 0 1016 1056
p 782 1321 100 0 0 DESC:Select real or internal data
p 752 1022 100 0 0 SELM:Specified
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
