[schematic2]
uniq 87
[tools]
[detail]
w 176 -637 100 0 FLNK eseq.Seq.FLNK 0 -640 400 -640 outhier.FLNK.p
w 168 -317 100 0 OVAL eseq.Seq.LNK1 0 -320 384 -320 outhier.OVAL.p
w -700 -261 100 0 n#54 hwin.hwin#51.in -768 -192 -704 -192 -704 -320 -576 -320 eseq.Seq.DOL1
w -808 -637 100 0 n#46 inhier.SLNK.P -992 -640 -576 -640 eseq.Seq.SLNK
s -528 -80 100 0 This sequence record sets the CAR record to "BUSY"
s -960 -304 100 0 CAR_IDLE = 0
s -960 -144 100 0 CAR_BUSY = 2
s 608 -1472 500 0 cad2car2.sch
n -1008 -1408 -656 -1056 100
This represents the contents
of a hierarchical symbol
"cad2car2", which is used in
trivial commands to toggle
the CAR record to "busy" and
back to "idle".
_
[cell use]
use eseq -576 -729 100 0 Seq
xform 0 -288 -432
p -256 -322 100 0 1 DLY2:0
p -480 -768 100 0 1 PV:$(top)$(mech)$(cad)
p 0 -320 75 768 -1 pproc(LNK1):PP
p 0 -352 75 768 -1 pproc(LNK2):PP
use outhier 368 -681 100 0 FLNK
xform 0 384 -640
use outhier 352 -361 100 0 OVAL
xform 0 368 -320
use hwin -960 -393 100 0 hwin#53
xform 0 -864 -352
p -957 -360 100 0 -1 val(in):0
use hwin -960 -233 100 0 hwin#51
xform 0 -864 -192
p -957 -200 100 0 -1 val(in):2
use inhier -1008 -681 100 0 SLNK
xform 0 -992 -640
use bc200tr -1248 -1656 -100 0 frame
xform 0 432 -352
p 1328 -1488 100 0 1 author:O.Frischmuth
p 1552 -1488 100 0 -1 border:C
p 1312 -1520 100 0 1 checked:
p 1584 -1488 100 0 -1 date:14 May 98
p 1552 -1376 100 0 -1 project:A&G System
p 1552 -1440 100 0 -1 title:Wrap up for CAR "busy then idle"
[comments]
