[schematic2]
uniq 160
[tools]
[detail]
w 1066 1579 100 0 n#159 superfout.fan.LNK7 944 1568 1248 1568 1248 768 1440 768 estringins.niciIn.SLNK
w 1730 779 100 0 n#158 estringins.niciIn.FLNK 1696 768 1824 768 estringouts.nici.SLNK
w 2290 2139 100 0 n#141 estringouts.none.OUT 2080 2128 2560 2128 estringouts.oiFilterName.SLNK
w 2114 763 100 0 n#141 estringouts.nici.OUT 2080 752 2208 752 2208 2128 junction
w 2114 987 100 0 n#141 estringouts.nifs.OUT 2080 976 2208 976 junction
w 2114 1211 100 0 n#141 estringouts.f2.OUT 2080 1200 2208 1200 junction
w 2114 1467 100 0 n#141 estringouts.niri.OUT 2080 1456 2208 1456 junction
w 2114 1691 100 0 n#141 estringouts.nirs.OUT 2080 1680 2208 1680 junction
w 2114 1915 100 0 n#141 estringouts.gmos.OUT 2080 1904 2208 1904 junction
w 1082 1611 100 0 n#155 superfout.fan.LNK6 944 1600 1280 1600 1280 992 1440 992 estringins.nifsIn.SLNK
w 1538 1227 100 0 n#154 superfout.fan.LNK5 944 1632 1312 1632 1312 1216 1824 1216 estringouts.f2.SLNK
w 1538 2155 100 0 n#153 estringouts.none.SLNK 1824 2144 1312 2144 1312 1760 944 1760 superfout.fan.LNK1
w 1554 1931 100 0 n#152 superfout.fan.LNK2 944 1728 1344 1728 1344 1920 1824 1920 estringouts.gmos.SLNK
w 1114 1675 100 0 n#148 superfout.fan.LNK4 944 1664 1344 1664 1344 1472 1440 1472 estringins.niriIn.SLNK
w 1162 1707 100 0 n#143 superfout.fan.LNK3 944 1696 1440 1696 estringins.nirsIn.SLNK
w 1730 1483 100 0 n#137 estringins.niriIn.FLNK 1696 1472 1824 1472 estringouts.niri.SLNK
w 1730 1003 100 0 n#125 estringins.nifsIn.FLNK 1696 992 1824 992 estringouts.nifs.SLNK
w 482 1611 100 0 n#132 ecalcs.calc.VAL 496 1600 528 1600 528 1696 superfout.fan.SELL
w 474 1643 100 0 n#130 ecalcs.calc.FLNK 496 1632 512 1632 512 1472 528 1472 superfout.fan.SLNK
w 1730 1707 100 0 n#124 estringins.nirsIn.FLNK 1696 1696 1824 1696 estringouts.nirs.SLNK
w 96 1803 100 0 n#79 inhier.OIWFS.P 32 1792 208 1792 ecalcs.calc.INPA
s 2720 80 100 0 Fetch OIWFS filter name
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqOiwfsFilter.sch,v 1.8 2007/05/18 22:29:22 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
s 16 96 100 0 The stringin records are to get around the bug in the DOL
s 16 64 100 0 link between crates. 
[cell use]
use estringins 1440 695 100 0 niciIn
xform 0 1568 768
p 1376 848 100 0 -1 def(INP):$(nici)wfs:filtName
use estringouts 1824 919 100 0 nifs
xform 0 1952 992
p 1888 1056 100 0 -1 DESC:Name of oiwfs filter
p 1760 798 100 0 0 OMSL:closed_loop
p 1760 958 100 0 0 VAL:
p 1680 1072 100 0 -1 def(DOL):$(top)nifsIn
p 1824 1024 75 1280 -1 palrm(DOL):MS
p 2112 976 75 768 -1 palrm(OUT):MS
p 2080 976 75 768 -1 pproc(OUT):PP
use estringouts 1824 1143 100 0 f2
xform 0 1952 1216
p 1888 1280 100 0 -1 DESC:Name of oiwfs filter
p 1760 1022 100 0 0 OMSL:closed_loop
p 1901 1211 100 0 -1 Type:stringout
p 1760 1182 100 0 0 VAL:
p 1680 1296 100 0 -1 def(DOL):$(ag)noRecord
p 1824 1248 75 1280 -1 palrm(DOL):MS
p 2112 1200 75 768 -1 palrm(OUT):MS
p 2080 1200 75 768 -1 pproc(OUT):PP
use estringouts 1824 2071 100 0 none
xform 0 1952 2144
p 1888 2208 100 0 -1 DESC:Name of oiwfs filter
p 1760 1950 100 0 0 OMSL:closed_loop
p 1760 2110 100 0 0 VAL:
p 1680 2224 100 0 -1 def(DOL):$(ag)noRecord
p 1824 2176 75 1280 -1 palrm(DOL):MS
p 2112 2128 75 768 -1 palrm(OUT):MS
p 2080 2128 75 768 -1 pproc(OUT):PP
use estringouts 1824 1847 100 0 gmos
xform 0 1952 1920
p 1888 1984 100 0 -1 DESC:Name of oiwfs filter
p 1760 1726 100 0 0 OMSL:closed_loop
p 1760 1886 100 0 0 VAL:
p 1664 2000 100 0 -1 def(DOL):$(ag)noRecord
p 1824 1952 75 1280 -1 palrm(DOL):MS
p 2112 1904 75 768 -1 palrm(OUT):MS
p 2080 1904 75 768 -1 pproc(OUT):PP
use estringouts 1824 1623 100 0 nirs
xform 0 1952 1696
p 1888 1760 100 0 -1 DESC:Name of oiwfs filter
p 1760 1502 100 0 0 OMSL:closed_loop
p 1760 1662 100 0 0 VAL:
p 1680 1776 100 0 -1 def(DOL):$(top)nirsIn
p 1824 1728 75 1280 -1 palrm(DOL):MS
p 2112 1680 75 768 -1 palrm(OUT):MS
p 2080 1680 75 768 -1 pproc(OUT):PP
use estringouts 1824 1399 100 0 niri
xform 0 1952 1472
p 1888 1536 100 0 -1 DESC:Name of oiwfs filter
p 1760 1278 100 0 0 OMSL:closed_loop
p 1760 1438 100 0 0 VAL:
p 1680 1552 100 0 -1 def(DOL):$(top)niriIn
p 1824 1504 75 1280 -1 palrm(DOL):MS
p 2112 1456 75 768 -1 palrm(OUT):MS
p 2080 1456 75 768 -1 pproc(OUT):PP
use estringouts 2560 2055 100 0 oiFilterName
xform 0 2688 2128
p 2592 2208 100 0 -1 DESC:Current OIWFS filter
p 2496 2094 100 0 0 VAL:
p 2784 2080 100 0 -1 def(OUT):$(sad)oi:filterName
p 2672 2048 100 1024 0 name:$(ag)$(I)
p 2848 2112 75 768 -1 palrm(OUT):MS
p 2816 2112 75 768 -1 pproc(OUT):PP
use estringouts 1824 695 100 0 nici
xform 0 1952 768
p 1888 832 100 0 -1 DESC:Name of oiwfs filter
p 1760 574 100 0 0 OMSL:closed_loop
p 1901 763 100 0 -1 Type:stringout
p 1760 734 100 0 0 VAL:
p 1680 848 100 0 -1 def(DOL):$(top)niciIn
p 1824 800 75 1280 -1 palrm(DOL):MS
p 2112 752 75 768 -1 palrm(OUT):MS
p 2080 752 75 768 -1 pproc(OUT):PP
use estringins 1440 919 100 0 nifsIn
xform 0 1568 992
p 1440 1086 100 0 0 VAL:
p 1360 1072 100 0 -1 def(INP):$(nifs)sad:wfs:filtName
use estringins 1440 1623 100 0 nirsIn
xform 0 1568 1696
p 1440 1790 100 0 0 VAL:
p 1392 1776 100 0 -1 def(INP):$(nirs)wfs:filtName
use estringins 1440 1399 100 0 niriIn
xform 0 1568 1472
p 1440 1566 100 0 0 VAL:
p 1376 1552 100 0 -1 def(INP):$(niri)wfs:filtName
use superfout 624 1344 100 0 fan
xform 0 736 1600
use ecalcs 208 1319 100 0 calc
xform 0 352 1584
p 320 1520 100 0 1 CALC:A+1
p 384 1408 100 0 1 SCAN:.2 second
use inhier 16 1751 100 0 OIWFS
xform 0 32 1792
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
