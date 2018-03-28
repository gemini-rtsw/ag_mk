[schematic2]
uniq 121
[tools]
[detail]
w 1410 -605 100 0 n#120 elongouts.PushIval.FLNK 1312 -608 1568 -608 outhier.FLNK.p
w 690 -533 100 0 n#119 ecars.C.FLNK 480 -544 960 -544 960 -384 1056 -384 elongouts.PushClid.SLNK
w 1410 -405 100 0 n#117 elongouts.PushClid.OUT 1312 -416 1568 -416 outhier.OCID.p
w 1410 -669 100 0 n#116 elongouts.PushIval.OUT 1312 -672 1568 -672 outhier.OVAL.p
w -156 -437 100 0 n#115 junction -160 -544 -160 -320 junction
w -30 -309 100 0 n#115 elongouts.ID.OUT -288 -256 -160 -256 -160 -320 160 -320 ecars.C.IVAL
w -164 -981 100 0 n#115 elongouts.BS.OUT -288 -1120 -160 -1120 -160 -832 junction
w -164 -693 100 0 n#115 elongouts.ER.OUT -288 -832 -160 -832 -160 -544 -288 -544 elongouts.PS.OUT
w 472 -221 100 0 n#115 junction 96 -320 96 -224 896 -224 896 -608 1056 -608 elongouts.PushIval.DOL
w 1128 -277 100 0 n#104 elongouts.PushClid.FLNK 1312 -352 1376 -352 1376 -288 928 -288 928 -640 1056 -640 elongouts.PushIval.SLNK
w 744 -349 100 0 n#103 ecars.C.CLID 480 -352 1056 -352 elongouts.PushClid.DOL
w -536 323 100 0 n#91 inhier.ICID.P -992 320 -32 320 -32 -352 160 -352 ecars.C.ICID
w -792 -1077 100 0 n#90 inhier.BSLK.P -992 -1088 -544 -1088 elongouts.BS.SLNK
w -792 -789 100 0 n#88 inhier.ERLK.P -992 -800 -544 -800 elongouts.ER.SLNK
w -792 -501 100 0 n#87 inhier.PSLK.P -992 -512 -544 -512 elongouts.PS.SLNK
w -792 -213 100 0 n#86 inhier.IDLK.P -992 -224 -544 -224 elongouts.ID.SLNK
w -600 -1045 100 0 n#77 hwin.hwin#79.in -608 -1056 -544 -1056 elongouts.BS.DOL
w -600 -757 100 0 n#76 hwin.hwin#74.in -608 -768 -544 -768 elongouts.ER.DOL
w -600 -469 100 0 n#71 hwin.hwin#73.in -608 -480 -544 -480 elongouts.PS.DOL
w -600 -181 100 0 n#70 hwin.hwin#68.in -608 -192 -544 -192 elongouts.ID.DOL
s -896 560 200 0 (TBD)
s -800 -1008 100 0 CAR_BUSY = 2
s -800 -720 100 0 CAR_ERROR = 3
s -800 -432 100 0 CAR_PAUSED = 1
s -800 -144 100 0 CAR_IDLE = 0
s 640 -1536 500 0 carPlus.sch
s -800 32 100 0 CAR_UNAVAILABLE removed - no longer exists
n 1584 -1344 1936 -992 100
This represents the contents
of a hierarchical symbol
"carPlus", which is used to
change the state of a CAR
record by activating one
of the input links.
_
[cell use]
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
use bc200tr -1216 -1720 -100 0 frame
xform 0 464 -416
p 1360 -1552 100 0 1 author:S.M.Beard
p 1584 -1552 100 0 -1 border:C
p 1344 -1584 100 0 1 checked:B.Goodrich
p 1616 -1552 100 0 -1 date:19 Aug 97
p 1584 -1440 100 0 -1 project:Core Instrument Control System
p 1584 -1504 100 0 -1 title:Wrap up for CAR triggered by link
use ecars 160 -601 100 0 C
xform 0 320 -432
p 224 -608 100 0 1 DESC:$(car) CAR record
p 224 -640 100 0 1 PV:$(top)$(car)
[comments]
