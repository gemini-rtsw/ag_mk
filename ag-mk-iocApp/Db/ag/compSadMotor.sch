[schematic2]
uniq 242
[tools]
[detail]
w -350 915 100 0 n#233 sir2link.ESirL.OUTA -336 912 -304 912 hwout.hwout#190.outp
w -870 259 100 0 n#222 hwin.hwin#228.in -704 320 -688 320 -688 256 -992 256 -992 176 esirs.Pos.INP
w -550 891 100 0 n#209 esirs.Eng.OMSS -544 880 -496 880 sir2link.ESirL.VALB
w -550 923 100 0 n#198 sir2link.ESirL.VALA -496 912 -544 912 esirs.Eng.VAL
w -550 955 100 0 n#197 esirs.Eng.FLNK -544 944 -496 944 sir2link.ESirL.FLNK
w -838 1027 100 0 n#193 hwin.hwin#125.in -672 1088 -656 1088 -656 1024 -960 1024 -960 944 esirs.Eng.INP
w 408 1090 100 0 n#20 hwin.hwin#19.in 416 1088 448 1088 esirs.Datumed.INP
s -624 592 100 0 holds eng. pos. of this special axis
s 224 992 100 0 1=Not datumed
s 224 1024 100 0 0=Datumed
s 368 -1008 500 512 compSadMotor.sch
s 368 1184 100 0 (1)
s 432 1216 100 0 The "Datumed", "Parked", "State" and "Health"
s 432 1184 100 0 SIR records are updated by channel
s 432 1152 100 0 access from the state notation code.
s -1008 1136 100 0 pulls current eng. pos from the mech's motor srcbase
s -272 992 100 0 puts eng. pos. into mech's SAD
n -1344 -1008 -764 -656 100
This schematic contains the Status/Alarm
Database for an A&G mechanism.
The records are updated by channel access writes
from the state notation code or other srcbases,
which is why there are very few links.
.
SIR records are linked together in situations
where the same quantity is stored in two or
more different forms (e.g. engineering position
can be translated automatically into name).
.
The values of all the "Health" records in the
A&G are combined into one overall instrument
health record - hence the OHLT output link.
_
[cell use]
use sir2link -496 791 100 0 ESirL
xform 0 -416 896
p -496 768 100 0 1 set1:sir $(motor)Eng
use hwout -304 871 100 0 hwout#190
xform 0 -208 912
p -208 903 100 0 -1 val(outp):$(eindex) PP NMS
use notes -528 -41 100 0 notes#231
xform 0 -272 144
p -500 270 100 0 -1 COMMENT1:This SIR pulls in the calculated
p -500 238 100 0 -1 COMMENT2:real world position and holds it 
p -500 208 100 0 -1 COMMENT3:This could be done in the Poscalc
p -500 176 100 0 -1 COMMENT4:record instead, but this is only
p -500 144 100 0 -1 COMMENT5:a Gensub, not a SIR
p -500 80 100 0 -1 COMMENT7:Pulling is done fast, because both
p -500 48 100 0 -1 COMMENT8:records are situated in
p -500 16 100 0 -1 COMMENT9:the same srcbase
use hwin 248 1048 100 0 hwin#19
xform 0 320 1088
p 227 1080 100 0 -1 val(in):1
use hwin -864 1047 100 0 hwin#125
xform 0 -768 1088
p -861 1080 100 0 -1 val(in):$(top)$(mech)$(motor):current.VAL
use hwin -896 279 100 0 hwin#228
xform 0 -800 320
p -893 312 100 0 -1 val(in):$(pindex)
use esirs -960 695 100 0 Eng
xform 0 -752 848
p -864 672 100 0 1 DESC:Component engineering position
p -864 480 100 0 1 EGU:steps
p -864 640 100 0 1 FDSC:Position of $(mechanism) $(axis) axis in engineering units
p -864 608 100 0 1 FTVL:DOUBLE
p -844 460 100 0 0 NELM:1
p -824 440 100 0 0 NORD:1
p -864 544 100 0 1 SCAN:1 second
p -864 576 100 0 1 SNAM:
p -832 688 100 1024 0 name:$(sadtop)$(mech)$(motor)Eng
use esirs 448 327 100 0 Parked
xform 0 656 480
p 544 304 100 0 1 DESC:Component parked?
p 399 -96 100 0 0 EGU:0/1
p 544 272 100 0 1 FDSC:Is $(mechanism) $(axis) axis parked? [YES=0|NO=1]
p 544 240 100 0 1 FTVL:LONG
p 419 -116 100 0 0 NELM:1
p 439 -136 100 0 0 NORD:1
p 544 176 100 0 1 PV:$(sadtop)$(mech)$(motor)
p 544 208 100 0 1 SNAM:
use esirs 448 839 100 0 Datumed
xform 0 656 992
p 544 816 100 0 1 DESC:Component datumed? 
p 399 416 100 0 0 EGU:0/1
p 544 784 100 0 1 FDSC:Is $(mechanism) $(axis) axis datumed? [YES=0|NO=1]
p 544 752 100 0 1 FTVL:LONG
p 419 396 100 0 0 NELM:1
p 439 376 100 0 0 NORD:1
p 544 688 100 0 1 PV:$(sadtop)$(mech)$(motor)
p 544 720 100 0 1 SNAM:
use esirs -992 -73 100 0 Pos
xform 0 -784 80
p -896 -96 100 0 1 DESC:Component real position
p -896 -288 100 0 1 EGU:$(units)
p -896 -128 100 0 1 FDSC:Position of $(mechanism) $(axis) axis in real units
p -896 -160 100 0 1 FTVL:DOUBLE
p -1016 -760 100 0 0 NELM:1
p -1036 -740 100 0 0 NORD:1
p -896 -256 100 0 1 PV:$(sadtop)$(mech)$(motor)
p -896 -224 100 0 1 SCAN:.1 second
p -896 -192 100 0 1 SNAM:
use bc200tr -1504 -1192 -100 0 frame
xform 0 176 112
p 1072 -1024 100 0 1 author:O.Frischmuth
p 1296 -1040 100 0 -1 border:C
p 1072 -1056 100 0 1 checked:O.Frischmuth
p 1328 -1040 100 0 -1 date:18 Mar 97
p 1312 -912 100 0 -1 project:A&G unit
p 1312 -976 100 0 -1 title:Motor dependent SAD
[comments]
