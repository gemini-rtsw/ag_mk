[schematic2]
uniq 160
[tools]
[detail]
w 2130 379 100 0 FLNK ebis.gpi.FLNK 1984 368 2336 368 outhier.FLNK.p
w 1570 619 100 0 n#158 ebis.nici.FLNK 1952 944 1984 944 1984 608 1216 608 1216 160 1312 160 ecalcs.calcGpi.SLNK
w 1634 395 100 0 n#157 ecalcs.calcGpi.FLNK 1600 384 1728 384 ebis.gpi.SLNK
w 1634 363 100 0 n#156 ecalcs.calcGpi.VAL 1600 352 1728 352 ebis.gpi.INP
w 1218 1707 -100 0 OIWFS junction 1184 1696 1312 1696 ecalcs.calcNifs.INPA
w 1218 1131 -100 0 OIWFS ecalcs.calcNici.INPA 1312 1120 1184 1120 1184 2272 junction
w 674 2331 100 0 OIWFS junction 224 2272 224 2320 1184 2320 1184 2272 1312 2272 ecalcs.calcF2.INPA
w 290 1707 -100 0 OIWFS junction 224 1696 416 1696 ecalcs.calcGmos.INPA
w 290 1131 -100 0 OIWFS ecalcs.calcNirs.INPA 416 1120 224 1120 junction
w 290 555 -100 0 OIWFS junction 224 2272 224 544 416 544 ecalcs.calcNiri.INPA
w 226 2283 -100 0 OIWFS inhier.OIWFS.P 96 2272 416 2272 ecalcs.calcNone.INPA
w 1218 555 100 0 OIWFS junction 1184 1120 1184 544 1312 544 ecalcs.calcGpi.INPA
w 226 1899 -100 0 SLNK ecalcs.calcNone.SLNK 416 1888 96 1888 inhier.SLNK.P
w 1202 1899 100 0 n#151 ebis.niri.FLNK 1056 368 1152 368 1152 1888 1312 1888 ecalcs.calcF2.SLNK
w 1570 1195 100 0 n#149 ebis.nifs.FLNK 1952 1520 1984 1520 1984 1184 1216 1184 1216 736 1312 736 ecalcs.calcNici.SLNK
w 674 619 100 0 n#148 ebis.nirs.FLNK 1056 944 1088 944 1088 608 320 608 320 160 416 160 ecalcs.calcNiri.SLNK
w 674 1211 100 0 n#147 ebis.gmos.FLNK 1056 1520 1088 1520 1088 1200 320 1200 320 736 416 736 ecalcs.calcNirs.SLNK
w 674 1787 100 0 n#146 ebis.none.FLNK 1056 2096 1088 2096 1088 1776 320 1776 320 1312 416 1312 ecalcs.calcGmos.SLNK
w 1570 1771 100 0 n#145 ebis.f2.FLNK 1952 2096 1984 2096 1984 1760 1216 1760 1216 1312 1312 1312 ecalcs.calcNifs.SLNK
w 1618 939 100 0 n#140 ecalcs.calcNici.VAL 1600 928 1696 928 ebis.nici.INP
w 1618 971 100 0 n#139 ecalcs.calcNici.FLNK 1600 960 1696 960 ebis.nici.SLNK
w 1618 1515 100 0 n#138 ecalcs.calcNifs.VAL 1600 1504 1696 1504 ebis.nifs.INP
w 1618 1547 100 0 n#137 ecalcs.calcNifs.FLNK 1600 1536 1696 1536 ebis.nifs.SLNK
w 1618 2123 100 0 n#133 ecalcs.calcF2.FLNK 1600 2112 1696 2112 ebis.f2.SLNK
w 1618 2091 100 0 n#132 ecalcs.calcF2.VAL 1600 2080 1696 2080 ebis.f2.INP
w 722 395 100 0 n#125 ecalcs.calcNiri.FLNK 704 384 800 384 ebis.niri.SLNK
w 722 363 100 0 n#124 ecalcs.calcNiri.VAL 704 352 800 352 ebis.niri.INP
w 722 971 100 0 n#123 ecalcs.calcNirs.FLNK 704 960 800 960 ebis.nirs.SLNK
w 722 939 100 0 n#122 ecalcs.calcNirs.VAL 704 928 800 928 ebis.nirs.INP
w 722 1515 100 0 n#121 ecalcs.calcGmos.VAL 704 1504 800 1504 ebis.gmos.INP
w 722 1547 100 0 n#120 ecalcs.calcGmos.FLNK 704 1536 800 1536 ebis.gmos.SLNK
w 722 2123 100 0 n#118 ecalcs.calcNone.FLNK 704 2112 800 2112 ebis.none.SLNK
w 722 2091 100 0 n#117 ecalcs.calcNone.VAL 704 2080 800 2080 ebis.none.INP
s 2432 2352 70 0 $Id: agSeqOiwfsInUse.sch,v 1.5 2013/11/12 18:00:06 gemvx Exp $
s 2448 96 100 0 Sciences Ltd.
s 2448 128 100 0 Observatory
s 2448 160 100 0 Copyright
s 2720 144 200 0 A&G Sequencer
s 2448 48 100 0 Chris Mayer
[cell use]
use ebis 1696 1033 100 0 nici
xform 6 1824 960
p 1472 1122 100 0 0 ONAM:Included
p 1472 1090 100 0 0 ZNAM:Ignored
use ebis 1696 2185 100 0 f2
xform 6 1824 2112
p 1472 2274 100 0 0 ONAM:Included
p 1472 2242 100 0 0 ZNAM:Ignored
use ebis 800 457 100 0 niri
xform 6 928 384
p 576 546 100 0 0 ONAM:Included
p 576 514 100 0 0 ZNAM:Ignored
use ebis 800 1033 100 0 nirs
xform 6 928 960
p 576 1122 100 0 0 ONAM:Included
p 576 1090 100 0 0 ZNAM:Ignored
use ebis 800 1609 100 0 gmos
xform 6 928 1536
p 576 1698 100 0 0 ONAM:Included
p 576 1666 100 0 0 ZNAM:Ignored
use ebis 800 2185 100 0 none
xform 6 928 2112
p 576 2274 100 0 0 ONAM:Included
p 576 2242 100 0 0 ZNAM:Ignored
use ebis 1696 1609 100 0 nifs
xform 6 1824 1536
p 1472 1698 100 0 0 ONAM:Included
p 1472 1666 100 0 0 ZNAM:Ignored
use ebis 1728 457 100 0 gpi
xform 6 1856 384
p 1504 546 100 0 0 ONAM:Included
p 1504 514 100 0 0 ZNAM:Ignored
use ecalcs 1312 647 100 0 calcNici
xform 0 1456 912
p 1504 720 100 0 1 CALC:A=5?1:0
use ecalcs 1312 1799 100 0 calcF2
xform 0 1456 2064
p 1520 1888 100 0 1 CALC:A=4?1:0
use ecalcs 416 1799 100 0 calcNone
xform 0 560 2064
p 576 1856 100 0 1 CALC:A=0?1:0
p 624 1888 100 0 1 PINI:YES
use ecalcs 416 1223 100 0 calcGmos
xform 0 560 1488
p 576 1280 100 0 1 CALC:A=1?1:0
use ecalcs 416 647 100 0 calcNirs
xform 0 560 912
p 576 704 100 0 1 CALC:A=2?1:0
use ecalcs 416 71 100 0 calcNiri
xform 0 560 336
p 576 128 100 0 1 CALC:A=3?1:0
use ecalcs 1312 1223 100 0 calcNifs
xform 0 1456 1488
p 1504 1296 100 0 1 CALC:A=5?1:0
use ecalcs 1312 71 100 0 calcGpi
xform 0 1456 336
p 1504 144 100 0 1 CALC:A=8?1:0
use outhier 2304 327 100 0 FLNK
xform 0 2320 368
use inhier 80 1847 100 0 SLNK
xform 0 96 1888
use inhier 80 2231 100 0 OIWFS
xform 0 96 2272
use bc200tr -160 -120 -100 0 frame
xform 0 1520 1184
[comments]
