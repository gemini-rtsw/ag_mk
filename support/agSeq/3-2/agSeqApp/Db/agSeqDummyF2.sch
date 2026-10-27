[schematic2]
uniq 14
[tools]
[detail]
w 614 1243 100 0 n#9 agSeqDummyF2Cads.agSeqDummyF2Cads#11.XTOL 544 1232 720 1232 agSeqDummyF2Wfs.agSeqDummyF2Wfs#12.XTOL
w 1918 2210 100 0 n#2 ecalcs.present.VAL 2112 1888 2208 1888 2208 2208 1664 2208 1664 2080 1824 2080 ecalcs.present.INPA
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqDummyF2.sch,v 1.1 2005/06/28 16:00:41 anunez Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2704 80 100 0 dummy AGWPS records
[cell use]
use agSeqDummyF2CarTree 448 647 100 0 agSeqDummyF2CarTree#13
xform 0 768 832
use agSeqDummyF2Wfs 720 1079 100 0 agSeqDummyF2Wfs#12
xform 0 944 1320
use agSeqDummyF2Cads 96 1079 100 0 agSeqDummyF2Cads#11
xform 0 320 1320
use esirs 1760 423 100 0 probePark
xform 0 1968 576
p 1792 752 100 0 -1 DESC:A&G subsystem parked flag
p 1696 160 100 0 0 FDSC:Parked flag
p 1696 128 100 0 0 FTVL:LONG
p 1856 464 100 0 1 SCAN:1 second
p 1408 672 100 0 -1 def(INP):$(top)parkState.VALA
use esirs 2536 968 100 0 state
xform 0 2720 1120
p 2592 1280 100 0 -1 DESC:State of A&G subsystem
use esirs 2536 1528 100 0 health
xform 0 2720 1680
p 2608 1840 100 0 -1 DESC:A&G subsystem health
use esirs 2528 423 100 0 inPosition
xform 0 2736 576
p 2560 752 100 0 -1 DESC:A&G subsystem in position flag
p 2464 160 100 0 0 FDSC:Overall in position status for AGWPS
p 2464 128 100 0 0 FTVL:LONG
use ecalcs 1848 1608 100 0 present
xform 0 1968 1872
p 1984 1662 100 0 1 CALC:(A+1)%1000
p 1808 2158 100 0 -1 DESC:Incrementing counter
p 1984 1616 100 0 1 SCAN:1 second
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
