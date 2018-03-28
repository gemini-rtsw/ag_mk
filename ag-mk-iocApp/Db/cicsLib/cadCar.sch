[schematic2]
uniq 91
[tools]
[detail]
w 1072 -373 100 0 FLNK car2link.car2link#85.FLNK 1008 -384 1184 -384 outhier.FLNK.p
w 1072 -341 100 0 OCID outhier.OCID.p 1184 -352 1008 -352 car2link.car2link#85.OUTB
w 1072 -309 100 0 OVAL car2link.car2link#85.OUTA 1008 -320 1184 -320 outhier.OVAL.p
w 748 -469 100 0 n#87 ecars.C.FLNK 704 -544 752 -544 752 -384 848 -384 car2link.car2link#85.SLNK
w 56 -349 100 0 n#75 eseq.Seq.LNK2 0 -352 160 -352 160 -320 junction
w 168 -317 100 0 n#75 eseq.Seq.LNK1 0 -320 384 -320 ecars.C.IVAL
w 552 -253 100 0 n#75 car2link.car2link#85.VALA 848 -320 816 -320 816 -256 336 -256 336 -320 junction
w 752 -349 100 0 n#86 ecars.C.CLID 704 -352 848 -352 car2link.car2link#85.VALB
w -696 -341 100 0 n#55 hwin.hwin#53.in -768 -352 -576 -352 eseq.Seq.DOL2
w -700 -261 100 0 n#54 hwin.hwin#51.in -768 -192 -704 -192 -704 -320 -576 -320 eseq.Seq.DOL1
w -392 -29 100 0 n#50 inhier.ICID.P -992 -32 256 -32 256 -352 384 -352 ecars.C.ICID
w -808 -637 100 0 n#46 inhier.SLNK.P -992 -640 -576 -640 eseq.Seq.SLNK
s -528 -112 100 0 and then after a delay sets it back to "IDLE".
s -528 -80 100 0 This sequence record sets the CAR record to "BUSY"
s -960 -304 100 0 CAR_IDLE = 0
s -960 -144 100 0 CAR_BUSY = 2
s 608 -1472 500 0 cadCar.sch
s -896 208 200 0 (TBD)
n -1008 -1408 -656 -1056 100
This represents the contents
of a hierarchical symbol
"cadCar", which is used in
trivial commands to toggle
the CAR record to "busy" and
back to "idle".
_
[cell use]
use car2link 848 -473 100 0 car2link#85
xform 0 928 -368
p 848 -496 100 0 1 set1:car $(cad)
p 848 -528 100 0 1 set2:mech car
use outhier 1216 -400 100 0 FLNK
xform 0 1168 -384
use outhier 1216 -368 100 0 OCID
xform 0 1168 -352
use outhier 1216 -336 100 0 OVAL
xform 0 1168 -320
use eseq -576 -729 100 0 Seq
xform 0 -288 -432
p -256 -322 100 0 1 DLY2:$(delay)
p -480 -768 100 0 1 PV:$(top)$(cad)
p 0 -320 75 768 -1 pproc(LNK1):PP
p 0 -352 75 768 -1 pproc(LNK2):PP
use hwin -960 -393 100 0 hwin#53
xform 0 -864 -352
p -957 -360 100 0 -1 val(in):0
use hwin -960 -233 100 0 hwin#51
xform 0 -864 -192
p -957 -200 100 0 -1 val(in):2
use inhier -1008 -73 100 0 ICID
xform 0 -992 -32
use inhier -1008 -681 100 0 SLNK
xform 0 -992 -640
use inhier -1008 183 100 0 STAT
xform 0 -992 224
use ecars 480 -560 100 0 C
xform 0 544 -432
p 448 -608 100 0 1 DESC:$(cad) CAR record
p 448 -640 100 0 1 PV:$(top)$(cad)
use bc200tr -1248 -1656 -100 0 frame
xform 0 432 -352
p 1328 -1488 100 0 1 author:S.M.Beard
p 1552 -1488 100 0 -1 border:C
p 1312 -1520 100 0 1 checked:B.Goodrich
p 1584 -1488 100 0 -1 date:14 Jul 97
p 1552 -1376 100 0 -1 project:Core Instrument Control System
p 1552 -1440 100 0 -1 title:Wrap up for CAR "busy then idle"
[comments]
