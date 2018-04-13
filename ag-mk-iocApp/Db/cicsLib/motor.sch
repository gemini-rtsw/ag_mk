[schematic2]
uniq 25
[tools]
[detail]
w 739 848 100 0 n#1 junction 736 544 736 1152 960 1152 960 1632 1056 1632 ecalcs.done.INPE
w 528 547 100 0 n#1 ebis.dsearch.VAL 320 544 736 544 736 256 1056 256 ecalcs.change.INPE
w -80 99 100 0 n#2 hwin.hwin#323.in -128 96 -32 96 eseq.dseq.DOL2
w -144 595 100 0 n#3 inhier.DSCH.P -352 592 64 592 ebis.dsearch.INP
w 336 579 100 0 n#4 ebis.dsearch.FLNK 320 576 352 576 352 320 -352 320 -352 -192 -32 -192 eseq.dseq.SLNK
w 2032 387 100 0 n#5 elongouts.current.OUT 1728 384 2336 384 outhier.CURR.p
w 1792 899 100 0 n#6 elongouts.curvel.VAL 1728 896 1856 896 1856 544 864 544 864 320 1056 320 ecalcs.change.INPC
w 2096 899 100 0 n#6 junction 1856 896 2336 896 outhier.CVEL.p
w 1792 1539 100 0 n#7 ebos.moving.VAL 1728 1536 1856 1536 1856 1216 992 1216 992 960 1056 960 ecalcs.ramp.INPF
w 2096 1539 100 0 n#7 junction 1856 1536 2336 1536 outhier.MOV.p
w -144 851 100 0 n#8 inhier.ENBL.P -352 848 64 848 ebis.enable.INP
w -144 1107 100 0 n#9 inhier.MVEL.P -352 1104 64 1104 elongins.maxvel.INP
w -144 1347 100 0 n#10 inhier.DMND.P -352 1344 64 1344 elongins.demand.INP
w 515 824 100 0 n#11 junction 512 1296 512 352 1056 352 ecalcs.change.INPB
w 416 1299 100 0 n#11 elongins.demand.VAL 320 1296 512 1296 512 1728 544 1728 ecalcs.diff.INPB
w 867 1344 100 0 n#12 junction 864 1568 864 1120 1056 1120 ecalcs.ramp.INPA
w 848 1571 100 0 n#12 ecalcs.diff.VAL 832 1568 864 1568 864 1760 1056 1760 ecalcs.done.INPA
w 688 451 100 0 n#13 junction 896 448 480 448 480 1760 544 1760 ecalcs.diff.INPA
w 1360 195 100 0 n#13 ecalcs.change.VAL 1344 192 1376 192 1376 448 896 448 896 384 1056 384 ecalcs.change.INPA
w 1424 451 100 0 n#13 junction 1376 448 1472 448 elongouts.current.DOL
w 1408 1571 100 0 n#14 ecalcs.done.VAL 1344 1568 1472 1568 ebos.moving.DOL
w 1360 1603 100 0 n#15 ecalcs.done.FLNK 1344 1600 1376 1600 1376 1536 1472 1536 ebos.moving.SLNK
w 675 1104 100 0 n#16 junction 672 1024 672 1184 928 1184 928 1664 1056 1664 ecalcs.done.INPD
w 675 544 100 0 n#16 junction 672 800 672 288 1056 288 ecalcs.change.INPD
w 496 803 100 0 n#16 ebis.enable.VAL 320 800 672 800 672 1024 1056 1024 ecalcs.ramp.INPD
w 1392 227 100 0 n#17 ecalcs.change.FLNK 1344 224 1440 224 1440 416 1472 416 elongouts.current.SLNK
w 688 1059 100 0 n#18 elongins.maxvel.VAL 320 1056 1056 1056 ecalcs.ramp.INPC
w 1808 931 100 0 n#19 elongouts.curvel.FLNK 1728 928 1888 928 1888 512 832 512 832 0 1056 0 ecalcs.change.SLNK
w 1808 1571 100 0 n#20 ebos.moving.FLNK 1728 1568 1888 1568 1888 1184 1024 1184 1024 736 1056 736 ecalcs.ramp.SLNK
w 864 1603 100 0 n#21 ecalcs.diff.FLNK 832 1600 896 1600 896 1376 1056 1376 ecalcs.done.SLNK
w 1360 963 100 0 n#22 ecalcs.ramp.FLNK 1344 960 1376 960 1376 896 1472 896 elongouts.curvel.SLNK
w 1408 931 100 0 n#23 ecalcs.ramp.VAL 1344 928 1472 928 elongouts.curvel.DOL
w 554 98 -100 0 n#24 eseq.dseq.LNK2 544 96 640 96 640 -192 680 -192 hwoutl.hwoutl#328.outp
s 640 1312 100 0 1 second/2 second
s 144 -208 100 0 Wait 10 seconds
s 2144 448 100 0 Current position
s 2144 944 100 0 Current velocity
s 2208 1568 100 0 Moving flag
s -368 624 100 0 Start datum search
s -368 880 100 0 Enable/Disable motion
s -368 1136 100 0 Maximum velocity
s -368 1376 100 0 Demand position
s 1312 -32 100 0 (6,7) Update current position.
s 1312 0 100 0 (4,5) Determine suitable velocity.
s 1312 32 100 0 (2,3) Has destination been reached?
s 1312 64 100 0 (1) Calculate current/demand difference.
s 1760 448 100 0 (7)
s 1216 352 100 0 (6)
s 1568 992 100 0 (5)
s 1216 1072 100 0 (4)
s 1568 1616 100 0 (3)
s 1216 1728 100 0 (2)
s 688 1728 100 0 (1)
s 1792 -320 500 0 motor.sch
s 384 1856 500 0 CICS Motor Simulator
s 160 1856 100 0 SCAN 0.2 second
n -128 1440 232 1776 100
This database simulates the behaviour
of an instrument motor. It strives
to make the current position the same
as the demand position, driving the
motor at maximum velocity but
slowing down as the demand position is
approached. Movement may be stopped
dead by activating the "enable" binary
input. A datum search can be simulated
by activating the "dsearch" binary input.
The search stops after 10 seconds. The
current position, velocity and
movement flag are made available to
the outside world.
_
[cell use]
use bc200tr -688 -488 -100 0 frame
xform 0 992 816
p 1888 -320 100 0 1 author:S.M.Beard
p 2112 -336 100 0 -1 border:C
p 1888 -352 100 0 1 checked:B.Goodrich
p 2144 -336 100 0 -1 date:18 Jul 97
p 2128 -208 100 0 -1 project:A&G Unit
p 2128 -272 100 0 -1 title:A&G motor simulator
use notes 1952 -89 100 0 notes#327
xform 0 2208 96
p 1980 222 100 0 -1 COMMENT1:ICD14
p 1980 190 100 0 -1 COMMENT2:=====
p 1980 160 100 0 -1 COMMENT3:To interface easily to the CICS, low level
p 1980 128 100 0 -1 COMMENT4:motor control should operate through the
p 1980 96 100 0 -1 COMMENT5:interface shown here. Compulsory inputs are
p 1980 64 100 0 -1 COMMENT6:demand position, enable and datum, and
p 1980 32 100 0 -1 COMMENT7:compulsory outputs are the current position
p 1980 0 100 0 -1 COMMENT8:and moving flag. Variations are possible
p 1980 -32 100 0 -1 COMMENT9:if the SNL is edited - e.g. see NIRI.
use hwin -320 55 100 0 hwin#323
xform 0 -224 96
p -317 88 100 0 -1 val(in):0
use eseq -32 -281 100 0 dseq
xform 0 256 16
p 288 126 100 0 1 DLY2:4.0
p 32 -320 100 0 1 PV:$(top)$(mech)$(motor)
p 544 96 75 768 -1 pproc(LNK2):PP
use outhier 2328 1496 100 0 MOV
xform 0 2320 1536
use outhier 2328 856 100 0 CVEL
xform 0 2320 896
use outhier 2328 344 100 0 CURR
xform 0 2320 384
use inhier -344 1304 100 0 DMND
xform 0 -352 1344
use inhier -344 1064 100 0 MVEL
xform 0 -352 1104
use inhier -344 808 100 0 ENBL
xform 0 -352 848
use inhier -344 552 100 0 DSCH
xform 0 -352 592
use ebis 64 743 100 0 enable
xform 0 192 816
p 128 688 100 0 1 ONAM:enable
p 128 656 100 0 1 PV:$(top)$(mech)$(motor)
p 128 720 100 0 1 ZNAM:disable
use ebis 64 487 100 0 dsearch
xform 0 192 560
p 128 432 100 0 1 ONAM:find_datum
p 128 400 100 0 1 PV:$(top)$(mech)$(motor)
p 128 464 100 0 1 ZNAM:normal
use ecalcs 1056 647 100 0 ramp
xform 0 1200 912
p 1120 608 100 0 1 CALC:F=1?(D#0?(A>C?C:MAX(A/2,1)):0):0
p 768 798 100 0 0 EGU:engineering units per cycle
p 1120 576 100 0 1 PV:$(top)$(mech)$(motor)
p 1120 576 100 0 0 SCAN:Passive
use ecalcs 1056 -89 100 0 change
xform 0 1200 176
p 1136 -128 100 0 1 CALC:E=0?(D#0?(A<B?A+C:A>B?A-C:A):A):0
p 768 62 100 0 0 EGU:engineering units
p 1136 -160 100 0 1 PV:$(top)$(mech)$(motor)
p 1136 -160 100 0 0 SCAN:Passive
use ecalcs 1056 1287 100 0 done
xform 0 1200 1552
p 1120 1264 100 0 1 CALC:E=0?(D#0?(A=0?0:1):0):1
p 768 1438 100 0 0 EGU:0/1
p 1120 1232 100 0 1 PV:$(top)$(mech)$(motor)
use ecalcs 544 1287 100 0 diff
xform 0 688 1552
p 608 1264 100 0 1 CALC:ABS(A-B)
p 256 1438 100 0 0 EGU:engineering units
p 608 1200 100 0 1 PV:$(top)$(mech)$(motor)
p 608 1232 100 0 1 SCAN:Passive
use elongouts 1472 327 100 0 current
xform 0 1600 416
p 1536 256 100 0 1 EGU:engineering units
p 1536 622 100 0 0 HIGH:100000
p 1536 686 100 0 0 HIHI:100000
p 1536 224 100 0 1 HOPR:100000
p 1536 654 100 0 0 LOLO:-100000
p 1536 192 100 0 1 LOPR:-100000
p 1536 590 100 0 0 LOW:-100000
p 1536 288 100 0 1 OMSL:closed_loop
p 1536 160 100 0 1 PV:$(top)$(mech)$(motor)
use elongouts 1472 807 100 0 curvel
xform 0 1600 896
p 1536 736 100 0 1 EGU:engineering units per cycle
p 1536 1102 100 0 0 HIGH:10000
p 1536 1166 100 0 0 HIHI:10000
p 1536 704 100 0 1 HOPR:10000
p 1536 1134 100 0 0 LOLO:0
p 1536 672 100 0 1 LOPR:0
p 1536 1070 100 0 0 LOW:0
p 1536 768 100 0 1 OMSL:closed_loop
p 1536 640 100 0 1 PV:$(top)$(mech)$(motor)
use elongins 64 999 100 0 maxvel
xform 0 192 1072
p 144 992 100 0 1 EGU:eng. units per cycle
p 32 1134 100 0 0 HIGH:10000
p 32 1198 100 0 0 HIHI:10000
p 144 960 100 0 1 HOPR:10000
p 32 1166 100 0 0 LOLO:1
p 144 928 100 0 1 LOPR:1
p 128 896 100 0 0 LOW:1
p 144 896 100 0 1 PV:$(top)$(mech)$(motor)
use elongins 64 1239 100 0 demand
xform 0 192 1312
p 144 1232 100 0 1 EGU:engineering units
p 32 1374 100 0 0 HIGH:100000
p 32 1438 100 0 0 HIHI:100000
p 144 1200 100 0 1 HOPR:100000
p 32 1406 100 0 0 LOLO:-100000
p 144 1168 100 0 1 LOPR:-100000
p 32 1342 100 0 0 LOW:-100000
p 144 1136 100 0 1 PV:$(top)$(mech)$(motor)
use ebos 1472 1447 100 0 moving
xform 0 1600 1536
p 1536 1408 100 0 1 OMSL:closed_loop
p 1536 1344 100 0 1 ONAM:moving
p 1536 1312 100 0 1 PV:$(top)$(mech)$(motor)
p 1536 1376 100 0 1 ZNAM:stopped
use hwoutl 680 -264 100 0 hwoutl#328
xform 0 872 -216
p 778 -201 100 0 -1 val(outp):$(top)$(mech)$(motor)dsearch
[comments]
