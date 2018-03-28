[schematic2]
uniq 139
[tools]
[detail]
s 160 1216 100 0 global CC command
s 160 1248 100 0 from being triggered from
s 160 1280 100 0 evnr 0 prevents sublevel mechs
s -672 1184 100 0 usage only for engineering purposes!
s -736 1680 100 0 These are the top-level n-D mechanisms from the ICD
s -672 1232 100 0 These are the real (underlying) 1-D motors
s -112 2272 100 0 System CAD records
s 1808 1488 100 0 All components are
s 1808 1456 100 0 of the discrete type
s 2256 400 500 512 gbd.sch
s 896 832 100 0 (E)
s -144 848 100 0 (F)
s -512 208 100 0 Attention! Redefinition of "top" occurs always first!
s 544 208 100 0 Attention! Redefinition of "top" occurs always first!
s 464 1376 100 0 sublevel mech don't point to cindex CCar, because there are not enough inputs.
n 1760 1984 2240 2336 100
This is the under top level schematic
for the Acquisition and Guidance
System Components Controller HRWFS.
On this schematic will be placed a
symbol pointing to the srcbases for
each of the mechanisms.
.
There are the following symbols:
.
system = systemwide srcbase
Plus a symbol for each component.
in the srcbase.
The components are sequenced by
the top-level "apply" record.
_
n 1760 1568 2240 1920 100
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
use combCar 864 1991 100 0 combCar#118
xform 0 944 2096
p 880 1968 100 0 1 set1:top $(systop)
use comp2 -80 1559 100 0 ao
xform 0 8 1696
p -80 1536 100 0 1 set1:mechanism AO fold mirror
p -80 1504 100 0 1 set2:mech ao
p -80 1472 100 0 1 set3:cindex $(systop)CCar.A
use comp3 864 1559 100 0 sf
xform 0 952 1696
p 864 1536 100 0 1 set1:mechanism Science Fold Mirror
p 864 1504 100 0 1 set2:mech sf
p 864 1472 100 0 1 set3:cindex $(systop)CCar.C
use comp1 1184 1111 100 0 Lin2
xform 0 1272 1248
p 1184 1088 100 0 1 set1:mechanism Lin2
p 1184 1056 100 0 1 set2:mech Lin2
p 1184 1024 100 0 1 set3:cindex $(systop)
p 1184 992 100 0 1 set4:parkevnr 0
p 1184 960 100 0 1 set5:datmevnr 0
p 1184 928 100 0 1 set6:testevnr 0
p 1184 896 100 0 1 set7:car2evnr 0
use comp1 544 1111 100 0 Tilt2
xform 0 632 1248
p 544 1088 100 0 1 set1:mechanism Tilt2
p 544 1056 100 0 1 set2:mech Tilt
p 544 1024 100 0 1 set3:cindex $(systop)
p 544 992 100 0 1 set4:parkevnr 0
p 544 960 100 0 1 set5:datmevnr 0
p 544 928 100 0 1 set6:testevnr 0
p 544 896 100 0 1 set7:car2evnr 0
use comp1 864 1111 100 0 RT2
xform 0 952 1248
p 864 1088 100 0 1 set1:mechanism RT2
p 864 1056 100 0 1 set2:mech RT2
p 864 1024 100 0 1 set3:cindex $(systop)
p 864 992 100 0 1 set4:parkevnr 0
p 864 960 100 0 1 set5:datmevnr 0
p 864 928 100 0 1 set6:testevnr 0
p 864 896 100 0 1 set7:car2evnr 0
use comp1 -80 1111 100 0 PA3AO
xform 0 8 1248
p -80 1088 100 0 1 set1:mechanism AO PA
p -80 1056 100 0 1 set2:mech PA3AO
p -80 1024 100 0 1 set3:cindex $(systop)
p -80 992 100 0 1 set4:parkevnr 0
p -80 960 100 0 1 set5:datmevnr 0
p -80 928 100 0 1 set6:testevnr 0
p -80 896 100 0 1 set7:car2evnr 0
use comp1 288 1568 100 0 hw
xform 0 376 1696
p 288 1536 100 0 1 set1:mechanism HRWFS probe
p 288 1504 100 0 1 set2:mech hw
p 288 1472 100 0 1 set3:cindex $(systop)CCar.B
use ccSysCad -80 2016 100 0 ccSysCad#116
xform 0 0 2144
p -80 2016 100 0 1 set1:top $(systop)
p -80 1984 100 0 1 set2:mech sys
use pwfs -496 400 100 0 pwfs1
xform 0 -128 624
p -512 336 100 0 1 set1:cindex D
p -512 304 100 0 1 set2:top $(top)p1:
p -512 272 100 0 1 set3:sadtop $(sadtop)p1:
p -512 240 100 0 1 set4:sub 1
p -16 336 100 0 1 set5:systop $(top)
p -16 304 100 0 1 set6:sindex G
p -16 272 100 0 1 set7:ftop $(ftop)p1_
p -16 240 100 0 1 set8:cadtop $(cadtop)p1:
use pwfs 544 384 100 0 pwfs2
xform 0 912 624
p 544 336 100 0 1 set1:cindex E
p 544 304 100 0 1 set2:top $(top)p2:
p 544 272 100 0 1 set3:sadtop $(sadtop)p2:
p 544 240 100 0 1 set4:sub 2
p 1024 336 100 0 1 set5:systop $(top)
p 1024 304 100 0 1 set6:sindex H
p 1024 272 100 0 1 set7:ftop $(ftop)p2_
p 1024 240 100 0 1 set8:cadtop $(cadtop)p2:
use bc200tr -928 8 -100 0 frame
xform 0 752 1312
p 1648 176 100 0 1 author:O.Frischmuth
p 1872 176 100 0 -1 border:C
p 1648 128 100 0 1 checked:O.Frischmuth
p 1904 160 100 0 -1 date:12 May 97
p 2128 160 100 1792 -1 page: 
p 2240 176 100 0 -1 pagenum:
p 1888 288 100 0 -1 project:A&G unit
p 1888 224 100 0 -1 title:gbd CC
[comments]
