[schematic2]
uniq 65
[tools]
[detail]
w 400 -469 100 0 n#64 elongouts.PID.FLNK 336 -480 512 -480 outhier.FLNK.p
w 400 -533 100 0 n#62 elongouts.PID.OUT 336 -544 512 -544 outhier.OUTB.p
w 400 -309 100 0 n#61 outhier.OUTA.p 512 -320 336 -320 elongouts.PIV.OUT
w -104 -341 100 0 n#57 inhier.VALB.P -176 -352 16 -352 16 -480 80 -480 elongouts.PID.DOL
w -104 -309 100 0 n#56 inhier.VALA.P -176 -320 16 -320 16 -256 80 -256 elongouts.PIV.DOL
w 168 -189 100 0 n#55 elongouts.PIV.FLNK 336 -256 400 -256 400 -192 -16 -192 -16 -512 80 -512 elongouts.PID.SLNK
w -72 -285 100 0 FLNK inhier.SLNK.P -176 -288 80 -288 elongouts.PIV.SLNK
s -32 -160 100 0 approriate "genSub" record fields for this component.
s -32 -128 100 0 Variables "mindex" and "hindex" direct the output to the
s -32 -96 100 0 into link fields, which can use a channel access put.
s -32 -64 100 0 They are necessary to convert the value fields of the SIR record
s -32 -32 100 0 which determines the overall health of the instrument.
s -32 0 100 0 These "stringout" records update the "genSub" record combHlt,
s 608 -704 100 0 BUG WORK AROUND: e2sr does not
s 608 -736 100 0 translate the PP property of OUT
s 608 -768 100 0 properly, so "PP NMS" has to be
s 608 -800 100 0 added after $(hindex).
s 576 -1456 500 0 car2link.sch
[cell use]
use outhier 528 -480 100 0 FLNK
xform 0 496 -480
use elongouts 80 -377 100 0 PIV
xform 0 208 -288
p 128 -384 100 0 1 OMSL:closed_loop
p 128 -416 100 0 1 PV:$(top)$(mech)$(car)
use elongouts 80 -601 100 0 PID
xform 0 208 -512
p 128 -608 100 0 1 OMSL:closed_loop
p 128 -640 100 0 1 PV:$(top)$(mech)$(car)
p 336 -544 75 768 -1 pproc(OUT):PP
use outhier 576 -544 100 2048 OUTB
xform 0 496 -544
p 464 -608 100 0 0 IO:output
p 416 -640 100 0 0 model:connector
p 416 -672 100 0 0 revision:2.2
use outhier 576 -320 100 2048 OUTA
xform 0 496 -320
p 464 -384 100 0 0 IO:output
p 416 -416 100 0 0 model:connector
p 416 -448 100 0 0 revision:2.2
use inhier -256 -352 100 1536 VALB
xform 0 -176 -352
p -224 -416 100 0 0 IO:input
p -288 -448 100 0 0 model:connector
p -288 -480 100 0 0 revision:2.2
use inhier -256 -320 100 1536 VALA
xform 0 -176 -320
p -224 -384 100 0 0 IO:input
p -288 -416 100 0 0 model:connector
p -288 -448 100 0 0 revision:2.2
use inhier -256 -288 100 1536 SLNK
xform 0 -176 -288
p -224 -352 100 0 0 IO:input
p -288 -384 100 0 0 model:connector
p -288 -416 100 0 0 revision:2.2
use bc200tr -1248 -1656 -100 0 frame
xform 0 432 -352
p 1328 -1488 100 0 1 author:O. Frischmuth
p 1552 -1488 100 0 -1 border:C
p 1312 -1520 100 0 1 checked:O. Frischmuth
p 1584 -1488 100 0 -1 date:24 Jun 97
p 1552 -1376 100 0 -1 project:A&G unit
p 1552 -1440 100 0 -1 title:VAL to Link converter
[comments]
