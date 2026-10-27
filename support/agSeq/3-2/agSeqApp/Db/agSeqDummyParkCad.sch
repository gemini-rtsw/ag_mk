[schematic2]
uniq 60
[tools]
[detail]
w 1600 923 100 0 n#58 hwin.hwin#57.in 1440 960 1536 960 1536 912 1712 912 elongouts.moveTrigger.DOL
w 1264 891 100 0 n#56 ecad8.ecad8#38.STLK 864 880 1712 880 elongouts.moveTrigger.SLNK
w 1224 1755 100 0 n#54 ecad8.ecad8#38.VALB 864 1488 1024 1488 1024 1744 1472 1744 outhier.YPARK.p
w 1208 1819 100 0 n#53 ecad8.ecad8#38.VALA 864 1552 992 1552 992 1808 1472 1808 outhier.XPARK.p
w 1144 1531 100 0 n#52 ecad8.ecad8#38.OUTA 864 1520 1472 1520 outhier.c#49.p
w 1144 1467 100 0 n#51 ecad8.ecad8#38.OUTB 864 1456 1472 1456 outhier.c#50.p
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqDummyParkCad.sch,v 1.2 2010/01/12 02:27:03 gemvx Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2704 80 100 0 Dummy instrument CAD record
s 1120 2256 200 0 Tolerance Command for GMOS WFS simulator
[cell use]
use hwin 1248 919 100 0 hwin#57
xform 0 1344 960
p 1251 952 100 0 -1 val(in):$(CAD_START)
use elongouts 1712 791 100 0 moveTrigger
xform 0 1840 880
p 1597 1225 100 0 0 DESC:Trigger a move
p 1552 798 100 0 0 OMSL:closed_loop
p 2064 848 100 0 -1 def(OUT):$(top)prbMove.DIR
p 1968 848 75 768 -1 pproc(OUT):PP
use outhier 1440 1703 100 0 YPARK
xform 0 1456 1744
use outhier 1440 1767 100 0 XPARK
xform 0 1456 1808
use outhier 1440 1479 100 0 c#49
xform 0 1456 1520
use outhier 1440 1415 100 0 c#50
xform 0 1456 1456
use ecad8 544 791 100 0 ecad8#38
xform 0 704 1296
p 640 1824 100 0 -1 DESC:GMOS simulation command
p 608 704 100 0 1 SNAM:$(snam)
p 240 1536 100 0 -1 def(INPA):$(top)probeXdef
p 240 1456 100 0 -1 def(INPB):$(top)probeYdef
p 1040 1536 100 0 -1 def(OUTA):$(top)prbMove.A
p 1040 1472 100 0 -1 def(OUTB):$(top)prbMove.B
p 656 784 100 1024 0 name:$(top)$(cad)
p 864 1520 75 768 -1 pproc(OUTA):NPP
p 864 1456 75 768 -1 pproc(OUTB):NPP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
