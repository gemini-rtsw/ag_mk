[schematic2]
uniq 49
[tools]
[detail]
w 872 -725 100 0 c#48 ecalcs.sp.FLNK 736 -736 1056 -736 outhier.SPOUT.p
w 864 -53 100 0 c#47 ecalcs.st.FLNK 720 -64 1056 -64 outhier.STOUT.p
w 284 -277 100 0 STAT junction 288 -608 288 64 432 64 ecalcs.st.INPB
w 152 -597 100 0 STAT inhier.STAT.P -96 -608 448 -608 ecalcs.sp.INPB
w 552 -509 100 0 SPID ecalcs.sp.VAL 736 -768 768 -768 768 -512 384 -512 384 -576 448 -576 ecalcs.sp.INPA
w 888 -765 100 0 SPID junction 768 -768 1056 -768 outhier.SPID.p
w 552 171 100 0 STID ecalcs.st.VAL 720 -96 768 -96 768 160 384 160 384 96 432 96 ecalcs.st.INPA
w 888 -93 100 0 STID junction 768 -96 1056 -96 outhier.STID.p
w 152 -949 100 0 SPIN inhier.SPIN.P -96 -960 448 -960 ecalcs.sp.SLNK
w 144 -285 100 0 STIN inhier.STIN.P -96 -288 432 -288 ecalcs.st.SLNK
s 1008 -752 100 512 Stop counter
s 1008 -80 100 512 Start counter
s -48 -592 100 0 CAD status
s -48 -944 100 0 Stop input link
s -64 -272 100 0 Start input link
s 608 -1472 500 0 cadPlus.sch
n -672 -224 -320 128 100
This represents the contents
of a hierarchical symbol
"cadPlus", to be used to
count the number of START
and STOP activations of each
CAD record. 
_
[cell use]
use outhier 1024 -704 100 0 SPOUT
xform 0 1040 -736
use outhier 1024 -32 100 0 STOUT
xform 0 1040 -64
use bc200tr -1248 -1656 -100 0 frame
xform 0 432 -352
p 1328 -1488 100 0 1 author:S.M.Beard
p 1552 -1488 100 0 -1 border:C
p 1312 -1520 100 0 1 checked:B.Goodrich
p 1584 -1488 100 0 -1 date:4 Feb 97
p 1552 -1376 100 0 -1 project:Core Instrument Control System
p 1552 -1440 100 0 -1 title:CAD start and stop counter
use outhier 1024 -137 100 0 STID
xform 0 1040 -96
use outhier 1024 -809 100 0 SPID
xform 0 1040 -768
use inhier -112 -329 100 0 STIN
xform 0 -96 -288
use inhier -112 -1001 100 0 SPIN
xform 0 -96 -960
use inhier -112 -649 100 0 STAT
xform 0 -96 -608
use ecalcs 432 -377 100 0 st
xform 0 576 -112
p 496 -400 100 0 1 CALC:B=0?A+1:A
p 144 -226 100 0 0 EGU:count
p 496 -432 100 0 1 PV:$(top)$(mech)$(cad):
use ecalcs 448 -1049 100 0 sp
xform 0 592 -784
p 512 -1072 100 0 1 CALC:B=0?A+1:A
p 160 -898 100 0 0 EGU:count
p 512 -1104 100 0 1 PV:$(top)$(mech)$(cad):
[comments]
