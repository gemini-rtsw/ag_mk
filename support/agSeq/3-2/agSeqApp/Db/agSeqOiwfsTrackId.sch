[schematic2]
uniq 128
[tools]
[detail]
w 2098 491 100 0 n#115 eaos.nici.OUT 1888 480 2368 480 2368 736 junction
w 1378 523 100 0 n#127 eaos.nici.SLNK 1632 512 1184 512 1184 1472 1008 1472 superfout.fan.LNK7
w 1330 2091 100 0 n#125 superfout.fan.LNK1 1008 1664 1088 1664 1088 2080 1632 2080 eaos.none.SLNK
w 2098 2059 100 0 n#115 eaos.none.OUT 1888 2048 2368 2048 2368 1792 junction
w 2226 1803 100 0 n#115 eaos.gmos.OUT 1888 1792 2624 1792 eaos.trackId.SLNK
w 2098 1003 100 0 n#115 eaos.f2.OUT 1888 992 2368 992 junction
w 2098 1275 100 0 n#115 eaos.niri.OUT 1888 1264 2368 1264 junction
w 2098 1563 100 0 n#115 eaos.nirs.OUT 1888 1552 2368 1552 junction
w 2098 747 100 0 n#115 eaos.nifs.OUT 1888 736 2368 736 2368 1792 junction
w 1394 779 100 0 n#123 superfout.fan.LNK6 1008 1504 1216 1504 1216 768 1632 768 eaos.nifs.SLNK
w 1410 1035 100 0 n#122 superfout.fan.LNK5 1008 1536 1248 1536 1248 1024 1632 1024 eaos.f2.SLNK
w 1426 1307 100 0 n#121 superfout.fan.LNK4 1008 1568 1280 1568 1280 1296 1632 1296 eaos.niri.SLNK
w 1218 1611 100 0 n#120 superfout.fan.LNK3 1008 1600 1488 1600 1488 1584 1632 1584 eaos.nirs.SLNK
w 546 1515 100 0 n#119 ecalcs.calc.FLNK 560 1504 592 1504 592 1376 superfout.fan.SLNK
w 538 1483 100 0 n#118 ecalcs.calc.VAL 560 1472 576 1472 576 1600 592 1600 superfout.fan.SELL
w 1352 1835 100 0 n#95 superfout.fan.LNK2 1008 1632 1120 1632 1120 1824 1632 1824 eaos.gmos.SLNK
w 136 1675 100 0 n#79 inhier.OIWFS.P 48 1664 272 1664 ecalcs.calc.INPA
s 2720 80 100 0 Fetch OIWFS track Id
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqOiwfsTrackId.sch,v 1.6 2007/05/18 22:29:24 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use eaos 1632 423 100 0 nici
xform 0 1760 512
p 1632 608 100 0 -1 DESC:Track Id of NICI OIWFS
p 1376 494 100 0 0 OMSL:closed_loop
p 1888 480 75 768 -1 pproc(OUT):PP
use superfout 672 1264 100 0 fan
xform 0 800 1504
use eaos 1632 679 100 0 nifs
xform 0 1760 768
p 1632 864 100 0 -1 DESC:Track Id of NIFS OIWFS
p 1600 494 100 0 0 EGU:secs
p 1376 750 100 0 0 OMSL:closed_loop
p 1376 622 100 0 0 PREC:14
p 1328 800 100 0 -1 def(DOL):$(ag)noRecord
p 1920 736 75 768 -1 palrm(OUT):MS
p 1888 736 75 768 -1 pproc(OUT):PP
use eaos 1632 1495 100 0 nirs
xform 0 1760 1584
p 1632 1680 100 0 -1 DESC:Track Id of NIRS OIWFS
p 1600 1310 100 0 0 EGU:secs
p 1376 1566 100 0 0 OMSL:closed_loop
p 1376 1438 100 0 0 PREC:14
p 1328 1616 100 0 -1 def(DOL):$(nirs)wfs:trackId
p 1920 1552 75 768 -1 palrm(OUT):MS
p 1888 1552 75 768 -1 pproc(OUT):PP
use eaos 1632 1735 100 0 gmos
xform 0 1760 1824
p 1632 1920 100 0 -1 DESC:Track Id of GMOS OIWFS
p 1600 1550 100 0 0 EGU:secs
p 1376 1806 100 0 0 OMSL:closed_loop
p 1376 1678 100 0 0 PREC:14
p 1328 1856 100 0 -1 def(DOL):$(gmos)wfs:trackId
p 1920 1792 75 768 -1 palrm(OUT):MS
p 1888 1792 75 768 -1 pproc(OUT):PP
use eaos 2624 1703 100 0 trackId
xform 0 2752 1792
p 2368 1262 100 0 0 ADEL:0.0005
p 2672 1872 100 0 -1 DESC:OIWFS track Id
p 2592 1518 100 0 0 EGU:mm
p 2368 1230 100 0 0 MDEL:0.0000
p 2368 1646 100 0 0 PREC:14
p 2736 1696 100 1024 0 name:$(ag)oi:$(I)
use eaos 1632 1991 100 0 none
xform 0 1760 2080
p 1632 2176 100 0 -1 DESC:Track id for OIWFS \"None\"
p 1600 1806 100 0 0 EGU:secs
p 1376 2062 100 0 0 OMSL:closed_loop
p 1376 1934 100 0 0 PREC:14
p 1280 2112 100 0 -1 def(DOL):$(ag)none:wfs:trackId
p 1920 2048 75 768 -1 palrm(OUT):MS
p 1888 2048 75 768 -1 pproc(OUT):PP
use eaos 1632 1207 100 0 niri
xform 0 1760 1296
p 1632 1392 100 0 -1 DESC:Track Id of NIRI OIWFS
p 1600 1022 100 0 0 EGU:secs
p 1376 1278 100 0 0 OMSL:closed_loop
p 1376 1150 100 0 0 PREC:14
p 1328 1328 100 0 -1 def(DOL):$(niri)wfs:trackId
p 1920 1264 75 768 -1 palrm(OUT):MS
p 1888 1264 75 768 -1 pproc(OUT):PP
use eaos 1632 935 100 0 f2
xform 0 1760 1024
p 1632 1136 100 0 -1 DESC:Track Id of Flamingos-2 OIWFS
p 1600 750 100 0 0 EGU:secs
p 1376 1006 100 0 0 OMSL:closed_loop
p 1376 878 100 0 0 PREC:14
p 1360 1072 100 0 -1 def(DOL):$(f2)wfs:trackId
p 1920 992 75 768 -1 palrm(OUT):MS
p 1888 992 75 768 -1 pproc(OUT):PP
use ecalcs 272 1191 100 0 calc
xform 0 416 1456
p 384 1392 100 0 1 CALC:A+1
p 448 1280 100 0 1 SCAN:.2 second
use inhier 32 1623 100 0 OIWFS
xform 0 48 1664
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
