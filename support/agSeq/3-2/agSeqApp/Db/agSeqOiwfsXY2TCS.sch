[schematic2]
uniq 301
[tools]
[detail]
w 3106 1643 100 0 YRAW egenSub.egenSub#274.OUTD 2912 1632 3360 1632 outhier.YRAW.p
w 3042 1707 100 0 XRAW egenSub.egenSub#274.OUTC 2912 1696 3232 1696 outhier.XRAW.p
w 3106 1771 100 0 Y egenSub.egenSub#274.OUTB 2912 1760 3360 1760 outhier.Y.p
w 3042 1835 100 0 X egenSub.egenSub#274.OUTA 2912 1824 3232 1824 outhier.X.p
w 3202 1323 100 0 FLNK egenSub.egenSub#274.FLNK 2912 1120 3072 1120 3072 1312 3392 1312 outhier.FLNK.p
w 1850 1819 100 0 SLNK inhier.SLNK.P 1744 1808 2016 1808 eais.eais#272.SLNK
w 2338 1451 100 0 n#288 eais.eais#273.FLNK 2272 1440 2464 1440 2464 1152 2624 1152 egenSub.egenSub#274.SLNK
w 2106 1275 100 0 OIWFS inhier.OIWFS.P 1744 1264 2528 1264 2528 1568 2624 1568 egenSub.egenSub#274.INPE
w 2082 1675 100 0 n#280 eais.eais#272.FLNK 2272 1792 2304 1792 2304 1664 1920 1664 1920 1456 2016 1456 eais.eais#273.SLNK
w 2338 1483 100 0 n#276 eais.eais#273.VAL 2272 1472 2464 1472 2464 1760 2624 1760 egenSub.egenSub#274.INPB
w 2418 1835 100 0 n#275 eais.eais#272.VAL 2272 1824 2624 1824 egenSub.egenSub#274.INPA
s 1632 1952 100 0 DOL field does not work between IOC's
s 1632 1984 100 0 The ai records are included only because the
s 2528 2016 100 0 the alarm severities can be set when an OIWFS is not connected.
s 2528 2048 100 0 Each OIWFS must have a separate gensub so
s 3472 864 100 0 Fetch OIWFS prove positions
s 3568 928 100 0 A&G Sequencer
s 3200 816 100 0 Pedro Gigoux
s 1728 1136 100 0 The OIWFS name currently selected is only needed by the GMOS
s 1728 1104 100 0 routine in to convert bHROS into GMOS. The other instruments
s 1728 1072 100 0 so far don't need it. INPC & INPD are reserved by the GMOS routine
s 1728 1040 100 0 for the bHROS offsets, which are not used anymore.
s 3232 1088 100 0 This schematic was added to avoid the duplication
s 3232 1056 100 0 of records in the agSeqOiwfsXY, and also to make
s 3232 1024 100 0 room for more instruments. The original record
s 3232 992 100 0 structure was preserved as much as possible
[cell use]
use outhier 3200 1783 100 0 X
xform 0 3216 1824
use outhier 3328 1719 100 0 Y
xform 0 3344 1760
use outhier 3200 1655 100 0 XRAW
xform 0 3216 1696
use outhier 3328 1591 100 0 YRAW
xform 0 3344 1632
use outhier 3360 1271 100 0 FLNK
xform 0 3376 1312
use inhier 1728 1223 100 0 OIWFS
xform 0 1744 1264
use inhier 1728 1767 100 0 SLNK
xform 0 1744 1808
use bb200tr 1408 648 -100 0 frame
xform 0 2688 1472
use eais 2016 1881 100 0 eais#272
xform 6 2144 1808
p 1760 2258 100 0 0 ADEL:0.0005
p 2048 1888 100 0 -1 DESC:X position of $(subsys) OIWFS
p 1760 2066 100 0 0 EGU:mm
p 1760 2290 100 0 0 MDEL:0.0005
p 1888 1760 100 0 -1 def(INP):$(xchan)
p 2128 1728 100 1024 -1 name:$(top)$(subsys)XIn
p 2016 1776 75 1280 -1 palrm(INP):MS
use eais 2016 1529 100 0 eais#273
xform 6 2144 1456
p 1760 1906 100 0 0 ADEL:0.0005
p 2048 1536 100 0 -1 DESC:Y position of $(subsys) OIWFS
p 1760 1714 100 0 0 EGU:mm
p 1760 1938 100 0 0 MDEL:0.0005
p 1840 1424 100 0 -1 def(INP):$(ychan)
p 2128 1376 100 1024 -1 name:$(top)$(subsys)YIn
p 2016 1424 75 1280 -1 palrm(INP):MS
use egenSub 2624 1063 100 0 egenSub#274
xform 0 2768 1488
p 2784 1616 100 0 0 DESC:Convert $(subsys) coords into TCS ones
p 2704 1568 100 0 1 FTE:STRING
p 2336 1614 100 0 0 PREC:14
p 2656 1024 100 0 1 SNAM:$(snam)
p 2768 1056 100 1024 -1 name:$(top)$(subsys)Xy2xy
p 2608 1834 75 0 -1 palrm(INPA):NMS
p 2608 1770 75 0 -1 palrm(INPB):NMS
p 2944 1834 75 0 -1 palrm(OUTA):NMS
p 2944 1770 75 0 -1 palrm(OUTB):NMS
p 2944 1706 75 0 -1 palrm(OUTC):NMS
p 2944 1642 75 0 -1 palrm(OUTD):NMS
p 2912 1834 75 0 -1 pproc(OUTA):PP
p 2912 1770 75 0 -1 pproc(OUTB):PP
p 2912 1706 75 0 -1 pproc(OUTC):PP
p 2912 1642 75 0 -1 pproc(OUTD):PP
[comments]
