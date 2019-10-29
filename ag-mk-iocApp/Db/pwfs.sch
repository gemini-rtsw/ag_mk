[schematic2]
uniq 214
[tools]
[detail]
w 1250 1131 100 0 n#213 comp1.RT34.FLNK 1248 1120 1312 1120 comp1.focus.SLNK
w 934 1131 100 0 n#212 comp1.PA34.FLNK 936 1120 992 1120 comp1.RT34.SLNK
w 946 1339 100 0 n#211 comp3.probe.FLNK 1232 1584 1344 1584 1344 1328 608 1328 608 1120 680 1120 comp1.PA34.SLNK
w -62 363 100 0 n#209 hwout.hwout#190.outp -32 352 -32 352 combCar.combCar#188.OUTA
w -62 331 100 0 n#208 hwout.hwout#189.outp -32 320 -32 320 combCar.combCar#188.FLNK
s 1632 2416 100 0 $Id: pwfs.sch,v 1.4 2001/05/05 22:45:44 cjm Exp $
s 0 240 100 0 Triggering is not possible if the record is not passive.
s 0 272 100 0 triggering is not necessary since the Top combination runs on 2Hz.
s 1296 1616 100 0 These are the top-level n-D mechanisms from the ICD
s 2288 304 500 512 pwfs.sch
s 1624 1136 100 0 usage only for engineering purposes!
s 1624 1184 100 0 These are the real (underlying) 1-D motors
n 1104 2048 1584 2400 100
The following additional variables are
defined in this schematic:
.
mechanism = Full name of mechanism.
.
mech      = Brief name of mechanism.
.
.
.
New components can be added by adding
more instances of the "component"
schematic with different values for
"mech" (e.g. "ndfilt", "cal", "pimg",
"lens", etc...).
_
[cell use]
use agTcsData -64 1063 100 0 agTcsData#210
xform 0 16 1184
use comp3 976 1504 100 0 probe
xform 0 1072 1664
p 976 1472 100 0 1 set1:mechanism probe
p 976 1440 100 0 1 set2:mech probe
p 976 1408 100 0 1 set3:cindex $(top)CCar.A
p 976 1376 100 0 1 set4:cartop $(top)
use comp1 288 1504 100 0 ndfilter
xform 0 376 1632
p 288 1472 100 0 1 set1:mechanism filter
p 288 1440 100 0 1 set2:mech filter
p 288 1408 100 0 1 set5:cindex $(top)CCar.C
p 288 1376 100 0 1 set6:cartop $(top)
use comp1 -64 1504 100 0 fldstop
xform 0 24 1632
p -64 1472 100 0 1 set1:mechanism field stop
p -64 1440 100 0 1 set2:mech fldstop
p -64 1408 100 0 1 set5:cindex $(top)CCar.B
p -64 1376 100 0 1 set6:cartop $(top)
use comp1 1352 1031 100 0 focus
xform 0 1440 1168
p 1352 1008 100 0 1 set1:mechanism focus
p 1352 976 100 0 1 set2:mech focus
p 1352 944 100 0 1 set3:cindex $(top)
p 1352 912 100 0 1 set4:cartop $(top)
p 1352 880 100 0 1 set5:parkevnr 0
p 1352 848 100 0 1 set6:datmevnr 0
p 1352 816 100 0 1 set7:testevnr 0
p 1352 784 100 0 1 set8:car2evnr 0
use comp1 720 1031 100 0 PA34
xform 0 808 1168
p 720 1008 100 0 1 set1:mechanism PA 3/4
p 720 976 100 0 1 set2:mech PA34
p 720 944 100 0 1 set3:cindex $(top)
p 720 912 100 0 1 set4:cartop $(top)
p 720 880 100 0 1 set5:parkevnr 0
p 720 848 100 0 1 set6:datmevnr 0
p 720 816 100 0 1 set7:testevnr 0
p 720 784 100 0 1 set8:car2evnr 0
use comp1 1032 1031 100 0 RT34
xform 0 1120 1168
p 1032 1008 100 0 1 set1:mechanism RT 3/4
p 1032 976 100 0 1 set2:mech RT34
p 1032 944 100 0 1 set3:cindex $(top)
p 1032 912 100 0 1 set4:cartop $(top)
p 1032 880 100 0 1 set5:parkevnr 0
p 1032 848 100 0 1 set6:datmevnr 0
p 1032 816 100 0 1 set7:testevnr 0
p 1032 784 100 0 1 set8:car2evnr 0
use hwout -32 311 100 0 hwout#190
xform 0 64 352
p 64 343 100 0 -1 val(outp):$(cartop)CCar.$(cindex)
use hwout -32 279 100 0 hwout#189
xform 0 64 320
p 64 311 100 0 -1 val(outp):$(cartop)CCar.VAL PP NMS
use combCar -176 199 100 0 combCar#188
xform 0 -96 304
use tracking -672 199 100 0 tracking
xform 0 -584 336
use pwfsSys -416 199 100 0 pwfsSys
xform 0 -328 336
p -416 176 100 0 1 set1:sindex $(sindex)
p -416 144 100 0 1 set2:mech probe
use bc200tr -944 -56 -100 0 frame
xform 0 736 1248
p 1616 112 100 0 1 author:O.Frischmuth
p 1856 96 100 0 -1 border:C
p 1616 80 100 0 1 checked:O.Frischmuth
p 1888 112 100 0 -1 date:12 May 97
p -944 -56 100 0 0 id:frame
p -944 -32 100 0 0 model:frame
p 2140 100 100 1792 -1 page: 
p 1984 64 100 0 1 pagenum:
p 1888 224 100 0 1 project:A&G unit
p -944 -8 100 0 0 revision:2.2
p 1872 160 100 0 1 title:GBD CC - PWFS1/2
[comments]
