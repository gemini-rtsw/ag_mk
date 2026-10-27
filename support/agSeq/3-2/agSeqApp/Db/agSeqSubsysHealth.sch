[schematic2]
uniq 73
[tools]
[detail]
w 1408 1371 100 0 n#72 efanouts.fan.LNK1 1360 1360 1504 1360 1504 1264 1600 1264 estringouts.goodMess.SLNK
w 1512 1883 100 0 n#71 efanouts.fan.LNK2 1360 1328 1472 1328 1472 1872 1600 1872 estringouts.healthMess.SLNK
w 2072 1579 100 0 n#68 estringouts.health.OUT 1856 1568 2336 1568 2336 1344 2560 1344 outhier.HEALTH.p
w 2072 1035 100 0 n#68 estringouts.goodHealth.OUT 1856 1024 2336 1024 2336 1344 junction
w 1752 1163 100 0 n#70 estringouts.goodMess.FLNK 1856 1280 2016 1280 2016 1152 1536 1152 1536 1040 1600 1040 estringouts.goodHealth.SLNK
w 2040 1867 100 0 n#67 estringouts.healthMess.OUT 1856 1856 2272 1856 2272 1424 2560 1424 outhier.MESS.p
w 2040 1259 100 0 n#67 estringouts.goodMess.OUT 1856 1248 2272 1248 2272 1424 junction
w 1768 1707 100 0 n#66 estringouts.healthMess.FLNK 1856 1888 2048 1888 2048 1696 1536 1696 1536 1584 1600 1584 estringouts.health.SLNK
w 1976 923 100 0 n#64 efanouts.fan.FLNK 1360 1392 1440 1392 1440 912 2560 912 outhier.FLNK.p
w 984 1291 100 0 n#63 ecalcs.inc.FLNK 864 1344 896 1344 896 1280 1120 1280 efanouts.fan.SLNK
w 400 1131 100 0 n#62 inhier.SLNK.P 272 1120 576 1120 ecalcs.inc.SLNK
w 1392 1906 100 0 n#37 inhier.c#36.P 1232 1904 1600 1904 estringouts.healthMess.DOL
w 1040 1362 100 0 n#22 ecalcs.inc.VAL 864 1312 960 1312 960 1360 1168 1360 efanouts.fan.SELL
w 1392 1627 100 0 n#14 inhier.c#12.P 1232 1616 1600 1616 estringouts.health.DOL
w 406 1506 100 0 n#6 inhier.LOADED.P 272 1504 576 1504 ecalcs.inc.INPA
s 1264 2240 100 0 message from an A&G subsystem.
s 1264 2272 100 0 This schematic fetches the health value and 
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 992 624 100 0 is copied through.
s 992 656 100 0 Similarly, if a subsystem has a health message then this
s 2432 2336 100 0 $Id: agSeqSubsysHealth.sch,v 1.3 2001/09/25 10:43:21 ajf Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2672 96 100 0 Generate a subsystem health state
s 2784 64 100 0 for the A&G
s 992 752 100 0 If a subsystem is deliberately configured not to be present
s 992 720 100 0 then the health value generated is GOOD, otherwise the
s 992 688 100 0 health value from the subsystem is used.
s 2528 1568 100 0 N.B. The message is written first
s 2528 1536 100 0 and then the health value
[cell use]
use outhier 2528 871 100 0 FLNK
xform 0 2544 912
use outhier 2552 1384 100 0 MESS
xform 0 2544 1424
use outhier 2552 1304 100 0 HEALTH
xform 0 2544 1344
use inhier 256 1079 100 0 SLNK
xform 0 272 1120
use inhier 280 1464 100 0 LOADED
xform 0 272 1504
use inhier 1240 1576 100 0 c#12
xform 0 1232 1616
use inhier 1240 1864 100 0 c#36
xform 0 1232 1904
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use estringouts 1624 1512 100 0 health
xform 0 1728 1584
p 1632 1662 100 0 -1 DESC:Current subsys health
p 1632 1470 100 0 1 IVOA:Set output to IVOV
p 1632 1438 100 0 1 IVOV:BAD
p 1536 1390 100 0 0 OMSL:closed_loop
p 1536 1550 100 0 0 VAL:
p 1328 1630 100 0 -1 def(DOL):$(prefix)health
p 1600 1616 75 1280 -1 palrm(DOL):MS
p 1856 1568 75 768 -1 pproc(OUT):NPP
use estringouts 1624 968 100 0 goodHealth
xform 0 1728 1040
p 1648 1118 100 0 -1 DESC:Good health
p 1536 846 100 0 0 OMSL:closed_loop
p 1536 1006 100 0 0 VAL:GOOD
p 1856 1024 75 768 -1 pproc(OUT):NPP
use estringouts 1624 1800 100 0 healthMess
xform 0 1728 1872
p 1632 1950 100 0 -1 DESC:Subsys health message
p 1632 1758 100 0 1 IVOA:Set output to IVOV
p 1632 1726 100 0 1 IVOV:Invalid health from $(instru)
p 1536 1678 100 0 0 OMSL:closed_loop
p 1536 1838 100 0 0 VAL:
p 1264 1934 100 0 -1 def(DOL):$(prefix)health.OMSS
p 1600 1904 75 1280 -1 palrm(DOL):MS
p 1856 1856 75 768 -1 pproc(OUT):NPP
use estringouts 1624 1192 100 0 goodMess
xform 0 1728 1264
p 1648 1342 100 0 -1 DESC:Empty message
p 1536 1070 100 0 0 OMSL:closed_loop
p 1536 1230 100 0 0 VAL:
p 1856 1248 75 768 -1 pproc(OUT):NPP
use efanouts 1144 1144 100 0 fan
xform 0 1240 1296
p 976 1262 100 0 0 SELM:Specified
use ecalcs 600 1032 100 0 inc
xform 0 720 1296
p 672 1246 100 0 1 CALC:A+1
p 544 1566 100 0 -1 DESC:Increment not loaded flag
p 288 1182 100 0 0 EGU:none
p 704 1070 100 0 0 SCAN:Passive
[comments]
