[schematic2]
uniq 51
[tools]
[detail]
w 1952 875 100 0 n#50 elongouts.InPosTrue.OUT 1792 864 2160 864 2160 1280 junction
w 2192 1291 100 0 n#50 elongouts.InPosition.OUT 2080 1632 2160 1632 2160 1280 2272 1280 elongouts.InPos.SLNK
w 1752 1707 100 0 n#49 elongins.RawInPos.VAL 1664 1632 1728 1632 1728 1696 1824 1696 elongouts.InPosition.DOL
w 1720 1675 100 0 n#48 elongins.RawInPos.FLNK 1664 1664 1824 1664 elongouts.InPosition.SLNK
w 1280 1259 100 0 n#47 efanouts.fan.LNK2 1264 1248 1344 1248 1344 1648 1408 1648 elongins.RawInPos.SLNK
w 1232 1691 100 0 n#46 inhier.c#22.P 1104 1680 1408 1680 elongins.RawInPos.INP
w 1320 1291 100 0 n#43 efanouts.fan.LNK1 1264 1280 1424 1280 1424 896 1536 896 elongouts.InPosTrue.SLNK
w 2856 1083 100 0 n#41 elongouts.InPos.FLNK 2528 1312 2752 1312 2752 1072 3008 1072 outhier.FLNK.p
w 2744 1291 100 0 n#40 elongouts.InPos.VAL 2528 1280 3008 1280 outhier.INPOSN.p
w 904 1323 100 0 n#39 ecalcs.inc.FLNK 896 1312 960 1312 960 1200 1024 1200 efanouts.fan.SLNK
w 432 1099 100 0 n#38 inhier.SLNK.P 304 1088 608 1088 ecalcs.inc.SLNK
w 960 1291 100 0 n#20 ecalcs.inc.VAL 896 1280 1072 1280 efanouts.fan.SELL
w 1448 939 100 0 n#11 hwin.hwin#10.in 1408 928 1536 928 elongouts.InPosTrue.DOL
w 438 1483 -100 0 CC inhier.LOADED.P 304 1472 608 1472 ecalcs.inc.INPA
s 2432 2336 100 0 $Id: agSeqSubsysInPosn.sch,v 1.3 2000/07/21 15:50:51 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2656 96 100 0 Generate overall "in position"
s 2768 64 100 0 flag for A&G
s 1280 2240 200 0 Generate A&G Subsystem "inPosition" flag
[cell use]
use elongins 1408 1575 100 0 RawInPos
xform 0 1536 1648
p 1424 1728 100 0 -1 DESC:In position status
p 1152 1646 100 0 0 EGU:none
p 1184 1696 100 0 -1 def(INP):$(recname)
use outhier 2976 1031 100 0 FLNK
xform 0 2992 1072
use outhier 2976 1239 100 0 INPOSN
xform 0 2992 1280
use inhier 288 1431 100 0 LOADED
xform 0 304 1472
use inhier 288 1040 100 0 SLNK
xform 0 304 1088
use inhier 1088 1639 100 0 c#22
xform 0 1104 1680
use elongouts 1824 1575 100 0 InPosition
xform 0 1952 1664
p 1824 1776 100 0 -1 DESC:In position status
p 1664 1550 100 0 0 IVOA:Set output to IVOV
p 1664 1582 100 0 0 OMSL:closed_loop
p 1520 1728 100 0 0 def(DOL):0.0
p 2080 1632 75 768 -1 pproc(OUT):PP
use elongouts 1536 807 100 0 InPosTrue
xform 0 1664 896
p 1536 1008 100 0 -1 DESC:Default GBDCC in position flag
p 1376 782 100 0 0 IVOA:Set output to IVOV
p 1376 814 100 0 0 OMSL:closed_loop
p 1232 960 100 0 0 def(DOL):0.0
p 1664 848 75 768 -1 pproc(OUT):PP
use elongouts 2272 1191 100 0 InPos
xform 0 2400 1280
p 2272 1392 100 0 -1 DESC:Resultant GBDCC in position flag
p 2112 1166 100 0 0 IVOA:Set output to IVOV
p 2112 1198 100 0 0 OMSL:supervisory
p 1968 1344 100 0 0 def(DOL):0.0
use ecalcs 608 999 100 0 inc
xform 0 752 1264
p 720 1216 100 0 1 CALC:A+1
p 592 1568 100 0 -1 DESC:Increment not loaded falg
p 752 1008 100 0 1 SCAN:1 second
use hwin 1216 887 100 0 hwin#10
xform 0 1312 928
p 1219 920 100 0 -1 val(in):1
use efanouts 1024 1063 100 0 fan
xform 0 1144 1216
p 910 1481 100 0 0 DESC:Select real or internal data
p 880 1182 100 0 0 SELM:Specified
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
