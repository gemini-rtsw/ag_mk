[schematic2]
uniq 80
[tools]
[detail]
s -224 1463 100 0 This is to dump the results of the combination 
s -224 1431 100 0 to an unexisting record /$(sadtop)
s 1392 80 500 512 hrwfsSad.sch
n 1728 1040 2208 1392 100
This is the under top level schematic
for the A&G Control
System Components Controller
Status/Alarm Database. On this
schematic will be placed a symbol
pointing to the Status/Alarm Databases
for each of the mechanisms.
.
There are the following symbols:
.
system = systemwide srcbase
.
Plus a symbol for each component.
in the srcbase.
_
n 1728 624 2208 976 100
The following additional variables are
defined in this schematic:
.
mechanism = Full name of mechanism.
.
mech      = Brief name of mechanism.
.
.
New components can be added by adding
more instances of the "component"
schematic with different values for
"mech" (e.g. "filt", "slit", "grat",
"mask", etc...).
_
[cell use]
use sircomb 192 1655 100 0 sircomb
xform 0 280 1760
p 192 1616 100 0 1 set1:sadtop $(sadtop)cc:
p 512 1696 100 0 1 set10:f5 $(sadtop2)lensflags.VAL
p 960 1696 100 0 1 set11:s5 $(sadtop2)lensflags.OMSS
p 512 1664 100 0 1 set12:f6 $(sadtop2)pimgflags.VAL
p 960 1664 100 0 1 set13:s6 $(sadtop2)pimgflags.OMSS
p 512 1632 100 0 1 set14:f7 $(sadtop2)focusflags.VAL
p 960 1632 100 0 1 set15:s7 $(sadtop2)focusflags.OMSS
p 192 1584 100 0 1 set17:hindex2
p 192 1552 100 0 1 set18:mindex2
p 192 1520 100 0 1 set19:trgtop2
p 512 1824 100 0 1 set2:f1 $(sadtop2)calflags.VAL
p 960 1824 100 0 1 set3:s1 $(sadtop2)calflags.OMSS
p 512 1792 100 0 1 set4:f2 $(sadtop2)fldstopflags.VAL
p 960 1792 100 0 1 set5:s2 $(sadtop2)fldstopflags.OMSS
p 512 1760 100 0 1 set6:f3 $(sadtop2)ndfilterflags.VAL
p 960 1760 100 0 1 set7:s3 $(sadtop2)ndfilterflags.OMSS
p 512 1728 100 0 1 set8:f4 $(sadtop2)clfilterflags.VAL
p 960 1728 100 0 1 set9:s4 $(sadtop2)clfilterflags.OMSS
use compSad 1008 711 100 0 focus
xform 0 1104 816
p 1008 672 100 0 1 set1:mechanism Focus
p 1008 640 100 0 1 set2:mech focus
p 1008 608 100 0 1 set3:hindex $(trigtop).M
p 1008 576 100 0 1 set4:mindex $(trigtop).N
use compSad -216 711 100 0 clfilter
xform 0 -128 816
p -216 688 100 0 1 set1:mechanism clfilter
p -216 656 100 0 1 set2:mech clfilter
p -216 624 100 0 1 set3:hindex $(trigtop).G
p -216 592 100 0 1 set4:mindex $(trigtop).H
use compSad 184 711 100 0 lens
xform 0 272 816
p 184 688 100 0 1 set1:mechanism lenslet array
p 184 656 100 0 1 set2:mech lens
p 184 624 100 0 1 set3:hindex $(trigtop).I
p 184 592 100 0 1 set4:mindex $(trigtop).J
use compSad 584 711 100 0 pimg
xform 0 672 816
p 584 672 100 0 1 set1:mechanism Pupil imager
p 584 640 100 0 1 set2:mech pimg
p 584 608 100 0 1 set3:hindex $(trigtop).K
p 584 576 100 0 1 set4:mindex $(trigtop).L
use compSad -216 1159 100 0 cal
xform 0 -128 1264
p -224 1136 100 0 1 set1:mechanism calibration source
p -224 1104 100 0 1 set2:mech cal
p -224 1072 100 0 1 set3:hindex $(trigtop).A
p -224 1040 100 0 1 set4:mindex $(trigtop).B
use compSad 200 1159 100 0 fldstop
xform 0 288 1264
p 192 1136 100 0 1 set1:mechanism fieldstop
p 192 1104 100 0 1 set2:mech fldstop
p 192 1072 100 0 1 set3:hindex $(trigtop).C
p 192 1040 100 0 1 set4:mindex $(trigtop).D
use compSad 584 1159 100 0 ndfilter
xform 0 672 1264
p 576 1136 100 0 1 set1:mechanism ndfilter
p 576 1104 100 0 1 set2:mech ndfilter
p 576 1072 100 0 1 set3:hindex $(trigtop).E
p 576 1040 100 0 1 set4:mindex $(trigtop).F
use ccSysSad -216 1655 100 0 system
xform 0 -136 1760
p -224 1600 100 0 1 set1:sadtop $(sadtop)cc:
use bc200tr -1024 -104 -100 0 frame
xform 0 656 1200
p 1552 64 100 0 1 author:O.Frischmuth
p 1776 48 100 0 -1 border:C
p 1552 32 100 0 1 checked:O.Frischmuth
p 1808 48 100 0 -1 date:15 May 97
p 1792 176 100 0 -1 project:A&G Control System
p 1792 112 100 0 -1 title:HRWFS SAD schematic
[comments]
