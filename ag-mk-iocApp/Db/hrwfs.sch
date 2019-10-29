[schematic2]
uniq 132
[tools]
[detail]
s 1808 1488 100 0 All components are
s 1808 1456 100 0 of the discrete type
s 1920 1344 100 0 .
s 1920 1360 100 0 .
s 1920 1376 100 0 .
s 2256 400 500 512 hrwfs.sch
s -352 1456 100 0 (B)
s 128 1456 100 0 (C)
s 560 1456 100 0 (D)
s 992 1440 100 0 (E)
s 384 832 100 0 (F)
s 816 816 100 0 (G)
s 1344 1344 100 0 These are the top-level n-D mechanisms from the ICD
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
use combCar 320 1927 100 0 combCar#124
xform 0 400 2032
p 336 1920 100 0 1 set1:top $(systop)
use ccSysCad -384 1943 100 0 ccSysCad#122
xform 0 -304 2064
p -384 1936 100 0 1 set1:top $(systop)
p -384 1904 100 0 1 set2:mech sys
use comp1 -96 695 100 0 focus
xform 0 -8 832
p -80 672 100 0 1 set1:mechanism Focus
p -80 640 100 0 1 set2:mech focus
p -80 608 100 0 1 set5:cindex $(systop)CCar.E
use comp1 736 704 100 0 pimg
xform 0 824 832
p 736 672 100 0 1 set1:mechanism pupil imager
p 736 640 100 0 1 set2:mech pimg
p 736 608 100 0 1 set5:cindex $(systop)CCar.G
use comp1 304 704 100 0 lens
xform 0 392 832
p 304 672 100 0 1 set1:mechanism lens
p 304 640 100 0 1 set2:mech lens
p 304 608 100 0 1 set5:cindex $(systop)CCar.F
use comp1 928 1328 100 0 clfilt
xform 0 1016 1456
p 944 1296 100 0 1 set1:mechanism colour filter
p 944 1264 100 0 1 set2:mech clfilter
p 944 1232 100 0 1 set5:cindex $(systop)CCar.D
use comp1 496 1328 100 0 ndfilt
xform 0 584 1456
p 512 1312 100 0 1 set1:mechanism neutral filter
p 512 1280 100 0 1 set2:mech ndfilter
p 512 1248 100 0 1 set5:cindex $(systop)CCar.C
use comp1 -416 1328 100 0 cal
xform 0 -328 1456
p -400 1312 100 0 1 set1:mechanism calibration source
p -400 1280 100 0 1 set2:mech cal
p -400 1248 100 0 1 set5:cindex $(systop)CCar.A
use comp1 48 1328 100 0 fldstop
xform 0 136 1456
p 64 1312 100 0 1 set1:mechanism field stop
p 64 1280 100 0 1 set2:mech fldstop
p 64 1248 100 0 1 set5:cindex $(systop)CCar.B
use bc200tr -928 8 -100 0 frame
xform 0 752 1312
p 1648 176 100 0 1 author:O.Frischmuth
p 1872 176 100 0 -1 border:C
p 1648 128 100 0 1 checked:O.Frischmuth
p 1904 160 100 0 -1 date:12 May 97
p 2128 160 100 1792 -1 page: 
p 2240 176 100 0 -1 pagenum:
p 1888 288 100 0 -1 project:A&G unit
p 1888 224 100 0 -1 title:hrwfs CC
[comments]
