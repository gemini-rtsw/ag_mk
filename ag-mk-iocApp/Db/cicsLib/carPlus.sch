[schematic2]
uniq 18
[tools]
[detail]
w 1440 -605 100 0 n#1 elongouts.PushIval.FLNK 1312 -608 1568 -608 outhier.FLNK.p
w 720 -541 100 0 n#2 ecars.C.FLNK 480 -544 960 -544 960 -384 1056 -384 elongouts.PushClid.SLNK
w 1440 -413 100 0 n#3 elongouts.PushClid.OUT 1312 -416 1568 -416 outhier.OCID.p
w 1440 -669 100 0 n#4 elongouts.PushIval.OUT 1312 -672 1568 -672 outhier.OVAL.p
w 1344 -349 100 0 n#5 elongouts.PushClid.FLNK 1312 -352 1376 -352 1376 -288 928 -288 928 -640 1056 -640 elongouts.PushIval.SLNK
w 768 -349 100 0 n#6 ecars.C.CLID 480 -352 1056 -352 elongouts.PushClid.DOL
w -512 323 100 0 n#7 inhier.ICID.P -992 320 -32 320 -32 -352 160 -352 ecars.C.ICID
w -768 -1085 100 0 n#8 inhier.BSLK.P -992 -1088 -544 -1088 elongouts.BS.SLNK
w -768 -797 100 0 n#9 inhier.ERLK.P -992 -800 -544 -800 elongouts.ER.SLNK
w -768 -509 100 0 n#10 inhier.PSLK.P -992 -512 -544 -512 elongouts.PS.SLNK
w -768 -221 100 0 n#11 inhier.IDLK.P -992 -224 -544 -224 elongouts.ID.SLNK
w -576 -1053 100 0 n#12 hwin.hwin#79.in -608 -1056 -544 -1056 elongouts.BS.DOL
w -576 -765 100 0 n#13 hwin.hwin#74.in -608 -768 -544 -768 elongouts.ER.DOL
w -576 -477 100 0 n#14 hwin.hwin#73.in -608 -480 -544 -480 elongouts.PS.DOL
w -576 -189 100 0 n#15 hwin.hwin#68.in -608 -192 -544 -192 elongouts.ID.DOL
w 580 -317 100 0 n#16 ecars.C.VAL 480 -320 680 -320 680 -608 1056 -608 elongouts.PushIval.DOL
w -64 -189 100 0 n#17 elongouts.ID.FLNK -288 -192 160 -192 hwoutm.hwoutm#80.outp
w -200 -477 100 0 n#17 elongouts.PS.FLNK -288 -480 -112 -480 -112 -192 junction
w -200 -765 100 0 n#17 elongouts.ER.FLNK -288 -768 -112 -768 -112 -480 junction
w -200 -1053 100 0 n#17 elongouts.BS.FLNK -288 -1056 -112 -1056 -112 -768 junction
s -840 632 200 0 (TBD)
s -800 -1008 100 0 CAR_BUSY = 2
s -800 -720 100 0 CAR_ERROR = 3
s -800 -432 100 0 CAR_PAUSED = 1
s -800 -144 100 0 CAR_IDLE = 0
s 640 -1536 500 0 carPlus.sch
s -800 32 100 0 CAR_UNAVAILABLE removed - no longer exists
n 1584 -1136 1838 -992 100
This represents the contents
of a hierarchical symbol
"carPlus", which is used to
change the state of a CAR
record by activating one
of the input links.
_
[cell use]
use bc200tr -1216 -1720 -100 0 frame
xform 0 464 -416
p 1360 -1552 100 0 1 author:S.M.Beard
p 1584 -1552 100 0 -1 border:C
p 1344 -1584 100 0 1 checked:B.Goodrich
p 1616 -1552 100 0 -1 date:19 Aug 97
p 1584 -1440 100 0 -1 project:Core Instrument Control System
p 1584 -1504 100 0 -1 title:Wrap up for CAR triggered by link
use outhier 1536 -457 100 0 OCID
xform 0 1552 -416
use outhier 1536 -713 100 0 OVAL
xform 0 1552 -672
use outhier 1536 -649 100 0 FLNK
xform 0 1552 -608
use elongouts -544 -1177 100 0 BS
xform 0 -416 -1088
p -480 -1216 100 0 1 EGU:CAR event
p -480 -1184 100 0 1 OMSL:supervisory
p -480 -1248 100 0 1 PV:$(top)$(car)
p -288 -1120 75 768 -1 pproc(OUT):PP
use elongouts -544 -889 100 0 ER
xform 0 -416 -800
p -480 -928 100 0 1 EGU:CAR event
p -480 -896 100 0 1 OMSL:supervisory
p -480 -960 100 0 1 PV:$(top)$(car)
p -288 -832 75 768 -1 pproc(OUT):PP
use elongouts -544 -601 100 0 PS
xform 0 -416 -512
p -480 -640 100 0 1 EGU:CAR event
p -480 -608 100 0 1 OMSL:supervisory
p -480 -672 100 0 1 PV:$(top)$(car)
p -288 -544 75 768 -1 pproc(OUT):PP
use elongouts -544 -313 100 0 ID
xform 0 -416 -224
p -480 -352 100 0 1 EGU:CAR event
p -480 -320 100 0 1 OMSL:supervisory
p -480 -384 100 0 1 PV:$(top)$(car)
p -288 -256 75 768 -1 pproc(OUT):PP
use elongouts 1056 -729 100 0 PushIval
xform 0 1184 -640
p 896 -498 100 0 0 EGU:CAR event
p 1120 -752 100 0 1 OMSL:closed_loop
p 1120 -784 100 0 1 PV:$(top)$(car)
p 1312 -672 75 768 -1 pproc(OUT):PP
use elongouts 1056 -473 100 0 PushClid
xform 0 1184 -384
p 896 -242 100 0 0 EGU:client ID
p 1120 -496 100 0 1 OMSL:closed_loop
p 1120 -528 100 0 1 PV:$(top)$(car)
use hwin -800 -1097 100 0 hwin#79
xform 0 -704 -1056
p -797 -1064 100 0 -1 val(in):2
use hwin -800 -809 100 0 hwin#74
xform 0 -704 -768
p -797 -776 100 0 -1 val(in):3
use hwin -800 -521 100 0 hwin#73
xform 0 -704 -480
p -797 -488 100 0 -1 val(in):1
use hwin -800 -233 100 0 hwin#68
xform 0 -704 -192
p -797 -200 100 0 -1 val(in):0
use inhier -1008 -1129 100 0 BSLK
xform 0 -992 -1088
use inhier -1008 -265 100 0 IDLK
xform 0 -992 -224
use inhier -1008 -553 100 0 PSLK
xform 0 -992 -512
use inhier -1008 535 100 0 STAT
xform 0 -992 576
use inhier -1008 -841 100 0 ERLK
xform 0 -992 -800
use inhier -1008 279 100 0 ICID
xform 0 -992 320
use ecars 160 -601 100 0 C
xform 0 320 -432
p 224 -608 100 0 1 DESC:$(car) CAR record
p 224 -640 100 0 1 PV:$(top)$(car)
use hwoutm 160 -264 100 0 hwoutm#80
xform 0 304 -216
p 258 -201 100 0 -1 val(outp):$(car).IVAL
[comments]
