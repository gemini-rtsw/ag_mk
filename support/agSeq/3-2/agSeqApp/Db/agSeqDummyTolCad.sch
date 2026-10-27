[schematic2]
uniq 47
[tools]
[detail]
w 2056 1995 100 0 n#46 eaos.xtol.VAL 1824 1984 2336 1984 outhier.XTOL.p
w 2056 1579 100 0 n#45 eaos.ytol.VAL 1824 1568 2336 1568 outhier.YTOL.p
w 1352 1579 100 0 n#44 ecad8.ecad8#38.OUTB 864 1456 1184 1456 1184 1568 1568 1568 eaos.ytol.SLNK
w 1336 1995 100 0 n#43 ecad8.ecad8#38.OUTA 864 1520 1152 1520 1152 1984 1568 1984 eaos.xtol.SLNK
w 1208 891 100 0 n#42 ecad8.ecad8#38.STLK 864 880 1600 880 eseqs.Delay.SLNK
w 1512 1179 100 0 n#37 hwin.hwin#36.in 1440 1072 1472 1072 1472 1168 1600 1168 eseqs.Delay.DOL2
w 1512 1211 100 0 n#35 hwin.hwin#34.in 1440 1264 1472 1264 1472 1200 1600 1200 eseqs.Delay.DOL1
s 1120 2256 200 0 Tolerance Command for GMOS WFS simulator
s 2704 80 100 0 Dummy instrument CAD record
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqDummyTolCad.sch,v 1.2 2007/05/18 22:29:20 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use outhier 2304 1943 100 0 XTOL
xform 0 2320 1984
use outhier 2304 1527 100 0 YTOL
xform 0 2320 1568
use eaos 1568 1895 100 0 xtol
xform 0 1696 1984
p 1632 2112 100 0 -1 DESC:X tolerance
p 1808 2112 100 0 1 EGU:mm
use eaos 1568 1479 100 0 ytol
xform 0 1696 1568
p 1632 1696 100 0 -1 DESC:Y tolerance
p 1808 1696 100 0 1 EGU:mm
use ecad8 544 791 100 0 ecad8#38
xform 0 704 1296
p 640 1824 100 0 -1 DESC:GMOS simulation command
p 640 1488 100 0 0 FTVA:DOUBLE
p 640 1456 100 0 0 FTVB:DOUBLE
p 608 704 100 0 1 SNAM:$(snam)
p 656 784 100 1024 0 name:$(top)$(cad)
p 864 1520 75 768 -1 pproc(OUTA):PP
p 864 1456 75 768 -1 pproc(OUTB):PP
use hwin 1248 1223 100 0 hwin#34
xform 0 1344 1264
p 1251 1256 100 0 -1 val(in):$(CAR_BUSY)
use hwin 1248 1031 100 0 hwin#36
xform 0 1344 1072
p 1251 1064 100 0 -1 val(in):$(CAR_IDLE)
use eseqs 1600 791 100 0 Delay
xform 0 1760 1040
p 1728 1104 100 0 1 DLY1:0.0
p 1728 1072 100 0 1 DLY2:1.0
p 2112 1200 100 0 -1 def(LNK1):$(top)softC.IVAL
p 2112 1168 100 0 -1 def(LNK2):$(top)softC.IVAL
p 1712 784 100 1024 0 name:$(top)$(cad)$(I)
p 1936 1200 75 1024 -1 pproc(LNK1):PP
p 1936 1168 75 1024 -1 pproc(LNK2):PP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
