[schematic2]
uniq 1
[tools]
[detail]
s 1488 80 500 512 ag_sadtop.sch
s -304 2144 500 0 Top level A&G Components Controller
s -304 2000 500 0 Status/Alarm Database schematic.
n 1536 432 1913 768 100
This is the top level schematic for the
A&G Control System
Components Controller Status/Alarm
Database.
.
It contains no srcbase records, but
defines the following macro variables
and includes the schematic:
.
top    = Top level record name prefix.
.
sadtop = Status/Alarm Database prefix.
.
.
_
[cell use]
use bc200tr -1024 -104 -100 0 frame
xform 0 656 1200
p 1552 64 100 0 1 author:O.Frischmuth
p 1776 48 100 0 -1 border:C
p 1552 32 100 0 1 checked:O.Frischmuth
p 1808 48 100 0 -1 date:15 May 97
p 1792 176 100 0 -1 project:A&G Control System
p 1792 112 100 0 -1 title:Top level SAD schematic
use gbdSad 336 1072 100 0 gbdSad
xform 0 800 1280
p 320 992 100 0 1 set1:top ${ag}
p 1056 992 100 0 1 set10:possir Pos
p 1056 960 100 0 1 set11:engsir EngPos
p 1056 928 100 0 1 set12:axis X
p 1056 896 100 0 1 set13:motor 1
p 1056 864 100 0 1 set14:units mm
p 320 960 100 0 1 set2:sadtop ${ag}
p 320 928 100 0 1 set3:sadtop2 ${ag}
p 320 896 100 0 1 set4:trigtop ${ag}cc:CHlt
p 320 864 100 0 1 set5:trgtop2 ${ag}cc:CHlt
p 320 832 100 0 1 set6:ftop ag_
p 704 992 100 0 1 seta:sad ${ag}sad:
use hrwfsSad -752 1072 100 0 hrwfsSad
xform 0 -272 1280
p -752 992 100 0 1 set1:top ${hrwfs}
p -48 992 100 0 1 set10:possir Pos
p -48 960 100 0 1 set11:engsir EngPos
p -48 928 100 0 1 set12:axis X
p -48 896 100 0 1 set13:motor 1
p -48 864 100 0 1 set14:units mm
p -752 960 100 0 1 set2:sadtop ${hrwfs}
p -752 928 100 0 1 set3:sadtop2 ${hrwfs}
p -752 896 100 0 1 set4:trigtop ${hrwfs}cc:CHlt
p -752 864 100 0 1 set5:ftop hrwfs_
p -747 838 100 0 1 set15:trgtop2 ${hrwfs}cc:CHlt
[comments]
