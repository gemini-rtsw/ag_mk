[schematic2]
uniq 37
[tools]
[detail]
w 1512 1883 100 0 n#36 hwin.hwin#35.in 1448 1872 1624 1872 estringouts.estringouts#33.DOL
w 2116 1835 100 0 n#34 estringouts.estringouts#33.OUT 1880 1824 2400 1824 esirs.health.IMSS
w 736 923 100 0 n#32 elongouts.elongouts#30.OUT 680 912 840 912 ecars.activeC.IVAL
w 332 987 100 0 n#29 hwin.hwin#20.in 288 976 424 976 elongouts.elongouts#30.DOL
w 2280 1867 100 0 n#25 hwin.hwin#24.in 2208 1856 2400 1856 esirs.health.INP
w 638 2018 100 0 n#2 ecalcs.present.VAL 832 1696 928 1696 928 2016 384 2016 384 1888 544 1888 ecalcs.present.INPA
s 2704 80 100 0 dummy AGWPS records
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDummy.sch,v 1.3 2001/10/03 10:41:44 ajf Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use hwin 2016 1815 100 0 hwin#24
xform 0 2112 1856
p 2024 1896 100 0 -1 val(in):$(top)prmHealth CP NMS
use hwin 96 935 100 0 hwin#20
xform 0 192 976
p 104 1008 100 0 -1 val(in):$(top)prmC CP NMS
use hwin 1256 1831 100 0 hwin#35
xform 0 1352 1872
p 1200 1904 100 0 -1 val(in):$(top)prmHealth.OMSS CP NMS
use estringouts 1624 1767 100 0 estringouts#33
xform 0 1752 1840
p 1656 1928 100 0 1 OMSL:closed_loop
p 1736 1760 100 1024 -1 name:$(top)so1
p 1880 1824 75 768 -1 pproc(OUT):NPP
use elongouts 424 855 100 0 elongouts#30
xform 0 552 944
p 464 1032 100 0 1 OMSL:closed_loop
p 536 848 100 1024 -1 name:$(top)lo1
p 680 912 75 768 -1 pproc(OUT):PP
use prm 1344 1207 100 0 prm#17
xform 0 1568 1384
use esirs 2416 503 100 0 inPosition
xform 0 2624 656
p 2448 832 100 0 -1 DESC:A&G subsystem in position flag
p 2352 240 100 0 0 FDSC:Overall in position status for AGWPS
p 2560 632 100 0 1 FTVL:LONG
use esirs 2424 1608 100 0 health
xform 0 2608 1760
p 2496 1920 100 0 -1 DESC:A&G subsystem health
p 2536 1744 100 0 1 FTVL:STRING
p 2352 1856 75 1024 -1 pproc(INP):NPP
use esirs 2424 1048 100 0 state
xform 0 2608 1200
p 2480 1360 100 0 -1 DESC:State of A&G subsystem
p 2544 1176 100 0 1 FTVL:STRING
use ecars 840 631 100 0 activeC
xform 0 1000 800
p 888 992 100 0 -1 DESC:Top level CAR record
use ecalcs 568 1416 100 0 present
xform 0 688 1680
p 704 1470 100 0 1 CALC:(A+1)%1000
p 528 1966 100 0 -1 DESC:Incrementing counter
p 704 1424 100 0 1 SCAN:1 second
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
