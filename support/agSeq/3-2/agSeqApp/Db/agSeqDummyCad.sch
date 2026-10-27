[schematic2]
uniq 40
[tools]
[detail]
w 1032 891 100 0 n#39 ecad8.ecad8#38.STLK 864 880 1248 880 1248 1104 1584 1104 eseqs.Delay.SLNK
w 1496 1403 100 0 n#37 hwin.hwin#36.in 1424 1296 1456 1296 1456 1392 1584 1392 eseqs.Delay.DOL2
w 1496 1435 100 0 n#35 hwin.hwin#34.in 1424 1488 1456 1488 1456 1424 1584 1424 eseqs.Delay.DOL1
s 1120 2256 200 0 Command for GMOS WFS simulator
s 2704 80 100 0 Dummy instrument CAD record
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDummyCad.sch,v 1.1 1999/10/14 14:58:31 cjm Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use ecad8 544 791 100 0 ecad8#38
xform 0 704 1296
p 640 1824 100 0 -1 DESC:GMOS simulation command
p 608 704 100 0 1 SNAM:$(snam)
p 656 784 100 1024 0 name:$(top)$(cad)
use hwin 1232 1447 100 0 hwin#34
xform 0 1328 1488
p 1235 1480 100 0 -1 val(in):$(CAR_BUSY)
use hwin 1232 1255 100 0 hwin#36
xform 0 1328 1296
p 1235 1288 100 0 -1 val(in):$(CAR_IDLE)
use eseqs 1584 1015 100 0 Delay
xform 0 1744 1264
p 1712 1328 100 0 1 DLY1:0.0
p 1712 1296 100 0 1 DLY2:1.0
p 2096 1424 100 0 -1 def(LNK1):$(top)softC.IVAL
p 2096 1392 100 0 -1 def(LNK2):$(top)softC.IVAL
p 1696 1008 100 1024 0 name:$(top)$(cad)$(I)
p 1920 1424 75 1024 -1 pproc(LNK1):PP
p 1920 1392 75 1024 -1 pproc(LNK2):PP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
