[schematic2]
uniq 63
[tools]
[detail]
w 304 -693 100 0 n#62 estringouts.yy.FLNK 336 -272 720 -272 720 -704 -64 -704 -64 -512 80 -512 estringouts.zz.SLNK
w -72 -277 100 0 SLNK inhier.SLNK.P -176 -288 80 -288 estringouts.yy.SLNK
w 416 -485 100 0 FLNK estringouts.zz.FLNK 336 -496 544 -496 outhier.FLNK.p
w -72 -477 100 0 n#57 inhier.VALB.P -176 -480 80 -480 estringouts.zz.DOL
w -72 -253 100 0 n#56 inhier.VALA.P -176 -256 80 -256 estringouts.yy.DOL
w 416 -301 100 0 OUTA estringouts.yy.OUT 336 -304 544 -304 outhier.OUTA.p
w 416 -525 100 0 OUTB estringouts.zz.OUT 336 -528 544 -528 outhier.OUTB.p
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
s 576 -1456 500 0 sir2link.sch
[cell use]
use outhier 608 -528 100 2048 OUTB
xform 0 528 -528
p 496 -592 100 0 0 IO:output
p 448 -624 100 0 0 model:connector
p 448 -656 100 0 0 revision:2.2
use outhier 608 -304 100 2048 OUTA
xform 0 528 -304
p 496 -368 100 0 0 IO:output
p 448 -400 100 0 0 model:connector
p 448 -432 100 0 0 revision:2.2
use outhier 608 -496 100 2048 FLNK
xform 0 528 -496
p 496 -560 100 0 0 IO:output
p 448 -592 100 0 0 model:connector
p 448 -624 100 0 0 revision:2.2
use inhier -256 -480 100 1536 VALB
xform 0 -176 -480
p -224 -544 100 0 0 IO:input
p -288 -576 100 0 0 model:connector
p -288 -608 100 0 0 revision:2.2
use inhier -256 -256 100 1536 VALA
xform 0 -176 -256
p -224 -320 100 0 0 IO:input
p -288 -352 100 0 0 model:connector
p -288 -384 100 0 0 revision:2.2
use inhier -256 -288 100 1536 SLNK
xform 0 -176 -288
p -224 -352 100 0 0 IO:input
p -288 -384 100 0 0 model:connector
p -288 -416 100 0 0 revision:2.2
use estringouts 192 -544 100 0 zz
xform 0 208 -512
p 144 -624 100 0 1 OMSL:closed_loop
p 144 -656 100 0 1 PV:$(sadtop)$(mech)$(sir)
p 240 -592 100 1024 0 name:$(top)$(I)
p 336 -528 75 768 -1 pproc(OUT):PP
use estringouts 192 -320 100 0 yy
xform 0 208 -288
p 144 -400 100 0 1 OMSL:closed_loop
p 144 -432 100 0 1 PV:$(sadtop)$(mech)$(sir)
p 240 -368 100 1024 0 name:$(top)$(I)
use bc200tr -1248 -1656 -100 0 frame
xform 0 432 -352
p 1328 -1488 100 0 1 author:O. Frischmuth
p 1552 -1488 100 0 -1 border:C
p 1312 -1520 100 0 1 checked:O. Frischmuth
p 1584 -1488 100 0 -1 date:24 Jun 97
p 1552 -1376 100 0 -1 project:A&G unit
p 1552 -1440 100 0 -1 title:VAL to Link converter
[comments]
