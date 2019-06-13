[schematic2]
uniq 30
[tools]
[detail]
w 98 -533 100 0 n#1 egenSub.EngPosA.VALG -512 96 -288 96 -288 -544 544 -544 544 -160 688 -160 elutins.relut.INPD
w -374 1835 100 0 n#2 hwout.hwout#455.outp -320 1824 -368 1824 sir2link.HSirL.FLNK
w -350 395 100 0 n#3 egenSub.EngPosA.OUTB -512 384 -128 384 -128 416 -64 416 egenSub.PosA.B
w -350 459 100 0 n#4 egenSub.EngPosA.OUTA -512 448 -128 448 -128 480 -64 480 egenSub.PosA.A
w -350 139 100 0 n#5 egenSub.EngPosA.OUTF -512 128 -128 128 -128 160 -64 160 egenSub.PosA.F
w -350 203 100 0 n#6 egenSub.EngPosA.OUTE -512 192 -128 192 -128 224 -64 224 egenSub.PosA.E
w -350 267 100 0 n#7 egenSub.EngPosA.OUTD -512 256 -128 256 -128 288 -64 288 egenSub.PosA.D
w -350 331 100 0 n#8 egenSub.EngPosA.OUTC -512 320 -128 320 -128 352 -64 352 egenSub.PosA.C
w 604 -29 100 0 n#9 efanouts.SADfan.SLNK 1056 208 608 208 608 -256 224 -256 egenSub.PosA.FLNK
w 1194 -485 100 0 n#10 efanouts.SADfan.LNK4 1296 192 1760 192 1760 -496 688 -496 688 -256 elutins.relut.SLNK
w 1514 235 100 0 n#11 efanouts.SADfan.LNK3 1296 224 1792 224 1792 -368 2016 -368 esirs.esirs#381.SLNK
w 1626 267 100 0 n#12 efanouts.SADfan.LNK2 1296 256 2016 256 esirs.$(engsir).SLNK
w 2458 267 100 0 n#13 esirs.$(engsir).FLNK 2432 416 2464 416 2464 256 2512 256 esirs.$(possir).SLNK
w 1338 483 100 0 n#14 esirs.$(possir).INP 2512 416 2512 480 224 480 egenSub.PosA.VALA
w 2064 1275 100 0 FLNK efanouts.SADfan.FLNK 1296 320 1760 320 1760 1264 2416 1264 outhier.FLNK.p
w 1514 299 100 0 n#15 efanouts.SADfan.LNK1 1296 288 1792 288 1792 784 2016 784 esirs.Datumed.SLNK
w 2954 795 100 0 n#16 esirs.Parked.FLNK 2928 944 2960 944 2960 784 3008 784 esirs.inPosition.SLNK
w 2458 795 100 0 n#17 esirs.Datumed.FLNK 2432 944 2464 944 2464 784 2512 784 esirs.Parked.SLNK
w 2458 -357 100 0 n#18 esirs.esirs#381.FLNK 2432 -208 2464 -208 2464 -368 2512 -368 esirs.esirs#388.SLNK
w -582 1835 100 0 n#19 sir2link.HSirL.SLNK -528 1824 -576 1824 esirs.Health.FLNK
w 1162 571 100 0 n#20 junction 656 560 1728 560 1728 416 2016 416 esirs.$(engsir).INP
w 130 563 100 0 n#20 elutins.relut.INPA 688 32 656 32 656 560 -336 560 -336 480 -512 480 egenSub.EngPosA.VALA
w -222 -213 100 0 n#21 egenSub.PosA.SLNK -64 -224 -320 -224 -320 -256 -512 -256 egenSub.EngPosA.FLNK
w 130 531 100 0 n#22 elutins.relut.INPC 688 -96 624 -96 624 528 -304 528 -304 352 -512 352 egenSub.EngPosA.VALC
w 130 547 100 0 n#23 elutins.relut.INPB 688 -32 640 -32 640 544 -320 544 -320 416 -512 416 egenSub.EngPosA.VALB
w -374 1771 100 0 n#24 sir2link.HSirL.OUTB -368 1760 -320 1760 hwout.hwout#183.outp
w -374 1795 100 0 n#25 hwout.hwout#184.outp -320 1792 -368 1792 sir2link.HSirL.OUTA
w -582 1771 100 0 n#26 sir2link.HSirL.VALB -528 1760 -576 1760 esirs.Health.OMSS
w -582 1803 100 0 n#27 esirs.Health.VAL -576 1792 -528 1792 sir2link.HSirL.VALA
w 978 -181 100 0 n#28 elutins.relut.FLNK 944 -32 960 -32 960 -192 1056 -192 1056 -176 esirs.Name.SLNK
w 986 -5 100 0 n#29 elutins.relut.VAL 944 -64 976 -64 976 -16 1056 -16 esirs.Name.INP
s 2032 1968 100 0 $Id: compSad.sch,v 1.4 2002/05/22 03:32:51 cjm Exp $
s 96 1824 100 0 PP link for triggering the health combination gensub
s 96 1744 100 0 OMSS
s 96 1792 100 0 health string (bad etc.)
s 2544 -160 100 0 value pushed in by xlat.VALG
s 2032 -160 100 0 value pushed in by xlat.VALD
s 3152 992 100 0 value pushed in by xlat.VALB
s 2576 992 100 0 value pushed in by DPRead.VALH
s 2000 992 100 0 value pushed in by DPRead.VALG
s 2912 -528 100 0 ag: records was also built by the connection from
s 2912 -496 100 0 in one lockset, but the lockset with the most
s 2912 -464 100 0 and all connected DPRead records together
s 2912 -432 100 0 NPP links are enough to bring Cinp
s 2976 -192 100 0 The health and flags combination records
s -1328 384 100 0 pushed in
s -1328 416 100 0 2 values
s -1328 352 100 0 by DPRead
s -896 -672 100 0 In this case, the other trigger is ignored.
s -896 -640 100 0 of this record can be changed to e.g. 1 second.
s -896 -608 100 0 If one wants to run the SAD independently, the SCAN field
s -896 -576 100 0 It is triggered synchronous to the DPRead record.
s -896 -544 100 0 This record triggers the chain of SIRs behind.
s 496 -64 100 0 / probes: angle
s 384 -192 100 0 targ.PA
s 384 -160 100 0 targ.RT
s 384 -64 100 0 target z
s 384 -32 100 0 target y
s 384 0 100 0 target x
s -272 176 100 0 Offset
s -272 208 100 0 Scale
s 2128 832 100 0 =Datumed
s 2128 800 100 0 =not datumed
s -240 1488 100 0 (1)
s -176 1520 100 0 The "state" and "health"
s -176 1488 100 0 SIR records are updated by channel
s -176 1456 100 0 access from the state notation code.
s 624 -560 100 0 This "Lutin" record tries to translate
s 624 -592 100 0 engineering position to a named position.
s 1232 -1072 500 512 compSad.sch
s -1168 384 100 0 actual pos.
s -1168 352 100 0 target pos. (DPRam)
s -272 240 100 0 ForPar
s 384 96 100 0 x
s 384 64 100 0 y
s 384 32 100 0 z
s 384 -96 100 0 probe:RT
s 384 -128 100 0 probe:PA
s 2112 832 100 0 1
s 2112 800 100 0 0
s -432 272 100 0 Mark=1/2 for probes
s 384 -224 100 0 ori
s -416 208 100 0 pushed in
s -416 240 100 0 3 values
s -416 176 100 0 by CalParm
s 2976 -224 100 0 run on an own scan task (0.5s).
s 2912 -560 100 0 the global CC commands test, datum, park to all mechs.
s 2912 -592 100 0 Only NPP input links (pulling) don't from locksets.
s 2976 -256 100 0 "Cinp" pulls the flags value out of this record.
s 624 -656 100 0 N.B. the INPD link is used to read the
s 624 -688 100 0 dummy 4th coordinate uised by the science
s 624 -720 100 0 fold.
n 1360 -1088 1837 -752 100
This schematic contains the Status/Alarm
Database for a A&G 2 axis discrete mechanism.
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
use hwout -320 1751 100 0 hwout#184
xform 0 -224 1792
p -224 1783 100 0 -1 val(outp):$(hindex)
use hwout -320 1719 100 0 hwout#183
xform 0 -224 1760
p -224 1751 100 0 -1 val(outp):$(mindex)
use hwout -320 1783 100 0 hwout#455
xform 0 -224 1824
p -224 1824 100 0 -1 val(outp):$(trgtop2).VAL PP NMS
use sir2link -528 1671 100 0 HSirL
xform 0 -448 1776
p -528 1632 100 0 1 set1:sir Hlth
use efanouts 1152 176 100 0 SADfan
xform 0 1176 224
p 1104 80 100 0 1 PV:$(sadtop)$(mech)
p 1104 48 100 0 1 SCAN:Passive
use esirs 2768 -448 100 0 esirs#388
xform 0 2720 -304
p 2608 -480 100 0 1 DESC:Mech flags
p 2608 -544 100 0 1 EGU:bin
p 2608 -512 100 0 1 FDSC:flags
p 2736 -208 100 0 1 FTVL:LONG
p 2608 -640 100 0 1 HHSV:MAJOR
p 2896 -640 100 0 1 HIGH:2
p 2896 -672 100 0 1 HIHI:2
p 2752 -640 100 0 1 HSV:MINOR
p 2608 -672 100 0 1 LLSV:MAJOR
p 2992 -640 100 0 1 LOLO:-1
p 2992 -672 100 0 1 LOW:0
p 2752 -672 100 0 1 LSV:MINOR
p 2483 -900 100 0 0 NELM:1
p 2503 -920 100 0 0 NORD:1
p 2704 -592 100 0 0 SCAN:Passive
p 2608 -576 100 0 1 SNAM:
p 2736 -416 100 1024 -1 name:$(sadtop)$(mech)flags
use esirs 2800 176 100 0 $(possir)
xform 0 2720 320
p 2608 144 100 0 1 DESC:Mechs real world pos.
p 2608 80 100 0 1 EGU:units
p 2608 112 100 0 1 FDSC:$(mechanism) real world position
p 2720 416 100 0 1 FTVL:DOUBLE
p 2608 -16 100 0 1 HHSV:MAJOR
p 2768 -16 100 0 1 HSV:MINOR
p 2608 -48 100 0 1 LLSV:MAJOR
p 2768 -48 100 0 1 LSV:MINOR
p 2784 48 100 0 1 NELM:1
p 2648 -56 100 0 0 NORD:1
p 2784 80 100 0 1 PREC:3
p 2704 32 100 0 0 SCAN:Passive
p 2608 48 100 0 1 SNAM:
p 2736 208 100 1024 -1 name:$(sadtop)$(mech)$(possir)
use esirs 2320 176 100 0 $(engsir)
xform 0 2224 320
p 2112 144 100 0 1 DESC:Mechs eng. position
p 2112 80 100 0 1 EGU:eng.units
p 2112 112 100 0 1 FDSC:$(mechanism) position
p 2240 416 100 0 1 FTVL:LONG
p 2112 -16 100 0 1 HHSV:MAJOR
p 2272 -16 100 0 1 HSV:MINOR
p 2112 -48 100 0 1 LLSV:MAJOR
p 2272 -48 100 0 1 LSV:MINOR
p 2320 48 100 0 1 NELM:1
p 2152 -56 100 0 0 NORD:1
p 2320 80 100 0 1 PREC:1
p 2304 16 100 0 0 SCAN:Passive
p 2112 48 100 0 1 SNAM:
p 2240 208 100 1024 -1 name:$(sadtop)$(mech)$(engsir)
use esirs -688 1072 100 0 Label
xform 0 -560 1184
p -704 1008 100 0 1 DESC:Component label
p -817 608 100 0 0 EGU:
p -704 976 100 0 1 FDSC:$(mechanism)
p -704 944 100 0 1 FTVL:STRING
p -797 588 100 0 0 NELM:1
p -777 568 100 0 0 NORD:1
p -704 848 100 0 1 PV:$(sadtop)$(mech)
p -704 912 100 0 1 SNAM:
p -704 880 100 0 1 VAL:$(mechanism)
use esirs 2608 736 100 0 Parked
xform 0 2720 848
p 2608 672 100 0 1 DESC:Mech parked?
p 2768 912 100 0 1 EGU:0/1
p 2608 640 100 0 1 FDSC:parked? [YES=1|NO=0]
p 2736 944 100 0 1 FTVL:LONG
p 2483 252 100 0 0 NELM:1
p 2503 232 100 0 0 NORD:1
p 2608 608 100 0 1 PV:$(sadtop)$(mech)
p 2704 560 100 0 0 SCAN:Passive
p 2608 576 100 0 1 SNAM:
use esirs -704 1584 100 0 Health
xform 0 -784 1728
p -896 1552 100 0 1 DESC:Component health
p -1041 1152 100 0 0 EGU:
p -896 1520 100 0 1 FDSC:$(mechanism) health
p -896 1488 100 0 1 FTVL:STRING
p -896 1392 100 0 1 HHSV:MAJOR
p -464 1392 100 0 1 HIGH:1
p -592 1392 100 0 1 HIHI:2
p -736 1392 100 0 1 HSV:MINOR
p -896 1360 100 0 1 LLSV:MAJOR
p -592 1360 100 0 1 LOLO:0
p -464 1360 100 0 1 LOW:0
p -736 1360 100 0 1 LSV:MINOR
p -1021 1132 100 0 0 NELM:1
p -1001 1112 100 0 0 NORD:1
p -896 1424 100 0 1 SCAN:Passive
p -896 1456 100 0 1 SNAM:
p -592 1456 100 0 1 VAL:GOOD
p -784 1616 100 1024 -1 name:$(sadtop)$(mech)Health
use esirs 2128 736 100 0 Datumed
xform 0 2224 848
p 2112 672 100 0 1 DESC:Mecht datumed?
p 2272 912 100 0 1 EGU:0/1
p 2112 640 100 0 1 FDSC:datumed? [YES=1|NO=0]
p 2240 944 100 0 1 FTVL:LONG
p 1987 252 100 0 0 NELM:1
p 2007 232 100 0 0 NORD:1
p 2112 608 100 0 1 PV:$(sadtop)$(mech)
p 2208 560 100 0 0 SCAN:Passive
p 2112 576 100 0 1 SNAM:
use esirs -1264 1072 100 0 State
xform 0 -1152 1168
p -1264 992 100 0 1 DESC:Component state
p -1264 832 100 0 0 EGU:
p -1264 960 100 0 1 FDSC:$(mechanism) mech state
p -1264 928 100 0 1 FTVL:STRING
p -1384 328 100 0 0 NELM:1
p -1404 348 100 0 0 NORD:1
p -1264 864 100 0 1 PV:$(sadtop)$(mech)
p -1264 896 100 0 1 SNAM:
use esirs 1152 -224 100 0 Name
xform 0 1264 -112
p 1152 -288 100 0 1 DESC:Mechs position name
p 1152 -448 100 0 1 EGU:names
p 1152 -320 100 0 1 FDSC:Name of $(mechanism) position
p 1152 -352 100 0 1 FTVL:STRING
p 1152 -480 100 0 1 NELM:1
p 1192 -488 100 0 0 NORD:1
p 1152 -416 100 0 1 PV:$(sadtop)$(mech)
p 1248 -400 100 0 0 SCAN:Passive
p 1152 -384 100 0 1 SNAM:
use esirs 3264 704 100 0 inPosition
xform 0 3216 848
p 3104 672 100 0 1 DESC:Mech in position?
p 3264 912 100 0 1 EGU:0/1
p 3104 640 100 0 1 FDSC:in position? [YES=1|NO=0]
p 3232 944 100 0 1 FTVL:LONG
p 3104 576 100 0 1 HHSV:MAJOR
p 3392 576 100 0 1 HIGH:2
p 3392 544 100 0 1 HIHI:2
p 3248 576 100 0 1 HSV:MINOR
p 3104 544 100 0 1 LLSV:MAJOR
p 3488 576 100 0 1 LOLO:-1
p 3488 544 100 0 1 LOW:0
p 3248 544 100 0 1 LSV:MINOR
p 2979 252 100 0 0 NELM:1
p 2999 232 100 0 0 NORD:1
p 3200 560 100 0 0 SCAN:Passive
p 3104 608 100 0 1 SNAM:
p 3232 736 100 1024 -1 name:$(sadtop)$(mech)inPosition
use esirs 2272 -448 100 0 esirs#381
xform 0 2224 -304
p 2112 -480 100 0 1 DESC:InPosMode
p 2112 -544 100 0 1 EGU:bin
p 1952 -688 100 0 0 EVNT:0
p 2112 -512 100 0 1 FDSC:InPosMode
p 2240 -208 100 0 1 FTVL:LONG
p 2112 -640 100 0 1 HHSV:MAJOR
p 2400 -640 100 0 1 HIGH:2
p 2400 -672 100 0 1 HIHI:2
p 2256 -640 100 0 1 HSV:MINOR
p 1952 -912 100 0 0 HYST:0.0
p 2112 -672 100 0 1 LLSV:MAJOR
p 2496 -640 100 0 1 LOLO:-1
p 2496 -672 100 0 1 LOW:0
p 2256 -672 100 0 1 LSV:MINOR
p 1987 -900 100 0 0 NELM:1
p 2007 -920 100 0 0 NORD:1
p 2208 -592 100 0 0 SCAN:Passive
p 2112 -576 100 0 1 SNAM:
p 2240 -416 100 1024 -1 name:$(sadtop)$(mech)inPosMode
use outhier 2432 1264 100 0 FLNK
xform 0 2400 1264
use eborderD -1600 -1273 100 0 eborderD#254
xform 0 1040 432
p 2032 -1056 100 768 1 author:O.Frischmuth
p 2528 -1136 100 0 1 border:D
p 2032 -1120 100 0 1 checked:O.Frischmuth
p 2704 -1056 100 768 1 date:27 Jan 97
p 2528 -800 200 768 0 file:$RCSfile: compSad.sch,v $
p -1540 -1340 100 0 0 id:frame
p -1520 -1360 100 0 0 model:frame
p 3024 -1072 100 0 -1 page:
p 2512 -1136 100 0 0 primitive:eborderD
p 2656 -784 100 0 1 project:A&G unit
p 2624 -1056 100 0 -1 revision:2.2
p 2528 -912 100 0 1 title:component's Status/Alarm Database
use egenSub 32 -272 100 0 PosA
xform 0 80 112
p 0 -416 100 0 1 DESC:Mechs Real World Pos.
p 16 464 100 768 1 FTA:LONG
p 16 432 100 768 1 FTB:LONG
p 16 400 100 768 1 FTC:LONG
p 16 368 100 768 1 FTD:LONG
p 16 336 100 768 1 FTE:LONG
p 16 304 100 768 1 FTF:LONG
p 16 272 100 768 1 FTG:LONG
p 16 240 100 768 1 FTH:DOUBLE
p 16 208 100 768 1 FTI:DOUBLE
p 16 176 100 768 1 FTJ:DOUBLE
p 16 96 100 768 1 FTVA:DOUBLE
p 16 64 100 768 1 FTVB:DOUBLE
p 16 32 100 768 1 FTVC:DOUBLE
p 16 0 100 768 1 FTVD:DOUBLE
p 16 -32 100 768 1 FTVE:DOUBLE
p 16 -64 100 768 1 FTVF:DOUBLE
p 16 -96 100 768 1 FTVG:DOUBLE
p 16 -128 100 768 1 FTVH:DOUBLE
p 16 -160 100 768 1 FTVI:DOUBLE
p 16 -192 100 768 1 FTVJ:DOUBLE
p 16 -224 100 0 1 FTVK:LONG
p -192 464 100 0 1 NOA:1
p -192 432 100 0 1 NOB:1
p -192 400 100 0 1 NOC:1
p -192 368 100 0 1 NOD:1
p -192 336 100 0 1 NOE:1
p -192 304 100 0 1 NOF:1
p -192 272 100 0 1 NOG:1
p -192 240 100 0 1 NOH:7
p -192 208 100 0 1 NOI:3
p -192 176 100 0 1 NOJ:3
p 288 96 100 0 1 NOVA:1
p 288 64 100 0 1 NOVB:1
p 288 32 100 0 1 NOVC:1
p 288 0 100 0 1 NOVD:1
p 288 -32 100 0 1 NOVE:1
p 288 -64 100 0 1 NOVF:1
p 288 -96 100 0 1 NOVG:1
p 288 -128 100 0 1 NOVH:1
p 288 -160 100 0 1 NOVI:1
p 288 -192 100 0 1 NOVJ:1
p 288 -224 100 0 1 NOVK:2
p 0 -480 100 0 1 PREC:3
p 0 -384 100 0 1 PV:$(sadtop)$(mech)
p 0 -448 100 0 1 SCAN:Passive
p 0 -352 100 0 1 SNAM:RecalcPos
p 224 458 75 0 -1 pproc(OUTA):NPP
p 224 394 75 0 -1 pproc(OUTB):NPP
use egenSub -704 -272 100 0 EngPosA
xform 0 -656 112
p -736 -416 100 0 1 DESC:Mechs Eng. Pos.
p -720 480 100 768 1 FTA:LONG
p -720 448 100 768 1 FTB:LONG
p -720 416 100 768 1 FTC:LONG
p -720 384 100 768 1 FTD:LONG
p -720 352 100 768 1 FTE:LONG
p -720 320 100 768 1 FTF:LONG
p -720 288 100 0 1 FTG:LONG
p -720 256 100 0 1 FTH:LONG
p -720 224 100 0 1 FTI:LONG
p -720 192 100 0 1 FTJ:LONG
p -720 96 100 0 1 FTVA:LONG
p -720 64 100 0 1 FTVB:LONG
p -720 32 100 0 1 FTVC:LONG
p -720 0 100 0 1 FTVD:LONG
p -720 -32 100 0 1 FTVE:LONG
p -720 -64 100 0 1 FTVF:LONG
p -720 -96 100 0 1 FTVG:LONG
p -720 -128 100 0 1 FTVH:LONG
p -720 -160 100 0 1 FTVI:LONG
p -720 -192 100 0 1 FTVJ:LONG
p -928 480 100 0 1 NOA:1
p -928 448 100 0 1 NOB:1
p -928 416 100 0 1 NOC:1
p -928 384 100 0 1 NOD:3
p -928 352 100 0 1 NOE:3
p -928 320 100 0 1 NOF:1
p -928 288 100 0 1 NOG:1
p -928 256 100 0 1 NOH:1
p -928 224 100 0 1 NOI:1
p -928 192 100 0 1 NOJ:1
p -448 96 100 0 1 NOVA:1
p -448 64 100 0 1 NOVB:1
p -448 32 100 0 1 NOVC:1
p -448 0 100 0 1 NOVD:1
p -448 -32 100 0 1 NOVE:1
p -448 -64 100 0 1 NOVF:1
p -448 -96 100 0 1 NOVG:1
p -448 -128 100 0 1 NOVH:1
p -448 -160 100 0 1 NOVI:1
p -448 -192 100 0 1 NOVJ:1
p -736 -480 100 0 1 PREC:1
p -736 -384 100 0 1 PV:$(sadtop)$(mech)
p -736 -448 100 0 1 SCAN:Passive
p -736 -352 100 0 1 SNAM:EngPos
p -512 458 75 0 -1 pproc(OUTA):NPP
p -512 394 75 0 -1 pproc(OUTB):NPP
p -512 330 75 0 -1 pproc(OUTC):NPP
p -1088 94 100 0 1 INAM:EngPossic
use notes -896 -1049 100 0 notes#269
xform 0 -640 -864
p -868 -738 100 0 -1 COMMENT1:This gensub holds the calculated
p -868 -770 100 0 -1 COMMENT2:real world position for all axes.
use elutins 832 -256 100 0 relut
xform 0 816 -80
p 752 -352 100 0 1 FDIR:./data
p 752 -384 100 0 1 FNAM:$(ftop)$(mech).lut
p 768 96 100 0 1 FTVA:LONG
p 768 64 100 0 1 FTVB:LONG
p 768 32 100 0 1 FTVC:LONG
p 768 0 100 0 1 FTVD:LONG
p 768 -32 100 0 1 FTVG:LONG
p 688 -82 100 0 0 PRIO:LOW
p 752 -416 100 0 1 PV:$(sadtop)$(mech)
p 752 -320 100 0 1 SCAN:Passive
p 752 -448 100 0 1 SELB:15
p 784 -80 100 0 -1 Type:lutin
p 1084 -816 100 0 0 def(INPB):0.000000000000000e+00
p 736 190 100 0 0 primitive:elutins
[comments]
