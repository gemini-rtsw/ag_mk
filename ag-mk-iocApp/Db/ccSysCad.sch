[schematic2]
uniq 610
[tools]
[detail]
w -974 -733 100 0 n#605 hwout.hwout#609.outp -880 -736 -1008 -736 ecad2.test.OUTA
w -934 -573 100 0 n#604 ecad2.test.VAL -1008 -512 -960 -512 -960 -576 -848 -576 cadPlus.testp.STAT
w -932 -789 100 0 n#603 ecad2.test.SPLK -1008 -1024 -928 -1024 -928 -544 -848 -544 cadPlus.testp.SPIN
w -948 -757 100 0 n#602 ecad2.test.STLK -1008 -992 -944 -992 -944 -512 -848 -512 cadPlus.testp.STIN
w -990 51 100 0 n#597 hwout.hwout#601.outp -896 48 -1024 48 ecad2.park.OUTA
w -950 211 100 0 n#596 ecad2.park.VAL -1024 272 -976 272 -976 208 -864 208 cadPlus.parkp.STAT
w -948 -5 100 0 n#595 ecad2.park.SPLK -1024 -240 -944 -240 -944 240 -864 240 cadPlus.parkp.SPIN
w -964 27 100 0 n#594 ecad2.park.STLK -1024 -208 -960 -208 -960 272 -864 272 cadPlus.parkp.STIN
w -990 787 100 0 n#592 hwout.hwout#591.outp -896 784 -1024 784 ecad2.datum.OUTA
w 98 -917 100 0 n#588 hwout.hwout#525.outp 128 -928 128 -928 car2link.car2link#536.FLNK
w 82 -165 100 0 n#587 hwout.hwout#524.outp 112 -176 112 -176 car2link.car2link#533.FLNK
w 66 683 100 0 n#586 hwout.hwout#522.outp 96 672 96 672 car2link.car2link#528.FLNK
w 82 -101 100 0 n#546 hwout.hwout#543.outp 112 -112 112 -112 car2link.car2link#533.OUTA
w 98 -853 100 0 n#545 hwout.hwout#544.outp 128 -864 128 -864 car2link.car2link#536.OUTA
w 66 747 100 0 n#542 hwout.hwout#541.outp 96 736 96 736 car2link.car2link#528.OUTA
w -86 -917 100 0 n#537 ecars.testC.FLNK -80 -928 -32 -928 car2link.car2link#536.SLNK
w -278 -645 100 0 n#535 car2link.car2link#536.VALA -32 -864 -64 -864 -64 -656 -432 -656 -432 -704 -400 -704 ecars.testC.IVAL
w -294 107 100 0 n#534 car2link.car2link#533.VALA -48 -112 -80 -112 -80 96 -448 96 -448 48 -416 48 ecars.parkC.IVAL
w -102 -165 100 0 n#532 ecars.parkC.FLNK -96 -176 -48 -176 car2link.car2link#533.SLNK
w -310 955 100 0 n#531 car2link.car2link#528.VALA -64 736 -96 736 -96 944 -464 944 -464 896 -432 896 ecars.datumC.IVAL
w -118 683 100 0 n#530 ecars.datumC.FLNK -112 672 -64 672 car2link.car2link#528.SLNK
w -950 947 100 0 n#395 ecad2.datum.VAL -1024 1008 -976 1008 -976 944 -864 944 cadPlus.datump.STAT
w -948 731 100 0 n#394 ecad2.datum.SPLK -1024 496 -944 496 -944 976 -864 976 cadPlus.datump.SPIN
w -964 763 100 0 n#393 ecad2.datum.STLK -1024 528 -960 528 -960 1008 -864 1008 cadPlus.datump.STIN
s -1136 1120 100 0 positions for Park/Datum from the LUT.
s -1136 1152 100 0 The PLCs are started by the CC PLC but they still need
s -1008 1184 100 0 Positions to the DPRAm with the Preset Directive.
s -288 -441 100 0 Triggering is not possible if the record is not passive.
s -496 -624 100 0 CAD records of all the components simultaneously.
s -496 -576 100 0 This "src fanout" record triggers the "Park"
s -1184 -592 100 0 (D)
s -496 1024 100 0 This "src fanout" record triggers the "Datum"
s -496 976 100 0 CAD records of all the components simultaneously.
s -2528 -1616 500 0 A&G Components Controller system CAD records - 1
s -528 144 100 0 CAD records of all the components simultaneously.
s -528 192 100 0 This "src fanout" record triggers the "Park"
s -1200 192 100 0 (D)
s -1200 928 100 0 (C)
s 2448 -1168 500 512 ccSysCad.sch
s -1136 1184 100 0 Transfers
n 384 -1648 864 -1296 100
This schematic contains the
following systemwide Command
Action Directive (CAD) records
for the A&G Components Controller:
.
test  - Test the A&G CC.
.
init  - Reinitialise the A&G CC.
.
datum - Datum all A&G components.
.
park  - Park all A&G components.
.
.
_
[cell use]
use hwout 128 -969 100 0 hwout#525
xform 0 224 -928
p 224 -937 100 0 -1 val(outp):$(top)CCar.VAL PP NMS
use hwout 112 -217 100 0 hwout#524
xform 0 208 -176
p 208 -185 100 0 -1 val(outp):$(top)CCar.VAL PP NMS
use hwout 96 631 100 0 hwout#522
xform 0 192 672
p 192 663 100 0 -1 val(outp):$(top)CCar.VAL PP NMS
use hwout 96 695 100 0 hwout#541
xform 0 192 736
p 192 727 100 0 -1 val(outp):$(top)SCar.A
use hwout 112 -153 100 0 hwout#543
xform 0 208 -112
p 208 -121 100 0 -1 val(outp):$(top)SCar.B
use hwout 128 -905 100 0 hwout#544
xform 0 224 -864
p 224 -873 100 0 -1 val(outp):$(top)SCar.C
use hwout -896 743 100 0 hwout#591
xform 0 -800 784
p -928 752 100 0 -1 val(outp):$(top)datmev.DISV PP NMS
use hwout -896 7 100 0 hwout#601
xform 0 -800 48
p -928 16 100 0 -1 val(outp):$(top)parkev.DISV PP NMS
use hwout -880 -777 100 0 hwout#609
xform 0 -784 -736
p -912 -768 100 0 -1 val(outp):$(top)testev.DISV PP NMS
use eevents -848 704 100 0 datmev
xform 0 -784 656
p -864 560 100 0 1 PV:$(top)
p -864 528 100 0 1 def(INP):$(datmevnr)
p -928 688 75 1280 -1 palrm(INP):
p -960 688 75 1280 -1 pproc(INP):
use eevents -848 -32 100 0 parkev
xform 0 -784 -80
p -864 -176 100 0 1 PV:$(top)
p -864 -208 100 0 1 def(INP):$(parkevnr)
p -928 -48 75 1280 -1 palrm(INP):
p -960 -48 75 1280 -1 pproc(INP):
use eevents -832 -816 100 0 testev
xform 0 -768 -864
p -848 -960 100 0 1 PV:$(top)
p -848 -992 100 0 1 def(INP):$(testevnr)
p -912 -832 75 1280 -1 palrm(INP):
p -944 -832 75 1280 -1 pproc(INP):
use cadPlus -864 855 100 0 datump
xform 0 -784 960
p -864 832 100 0 1 set:cad DatumP
use cadPlus -864 119 100 0 parkp
xform 0 -784 224
p -864 96 100 0 1 set:cad ParkP
use cadPlus -848 -665 100 0 testp
xform 0 -768 -560
p -848 -688 100 0 1 set:cad TestP
use ccSysSub 1296 -153 100 0 ccSysSub#585
xform 0 1376 -48
use bd200tr -2688 -1784 -100 0 frame
xform 0 -48 -80
p 944 -1552 100 0 1 author:O.Frischmuth
p 944 -1632 100 0 1 checked:O.Frischmuth
p 1536 -1568 100 0 1 date:20 May 97
p 1472 -1280 100 0 1 project:A&G unit
p 1488 -1424 100 0 1 title:System Cad records
use car2link -64 583 100 0 car2link#528
xform 0 16 688
p -48 576 100 0 1 set1:car A
use car2link -48 -265 100 0 car2link#533
xform 0 32 -160
p -28 -292 100 0 1 set1:car B
use car2link -32 -1017 100 0 car2link#536
xform 0 48 -912
p -12 -1044 100 0 1 set1:car C
use ecars -288 -928 100 0 testC
xform 0 -240 -816
p -320 -992 100 0 1 DESC:Test CAR record
p -320 -1024 100 0 1 PV:$(top)
p -288 -944 100 1024 -1 name:
use ecars -336 -192 100 0 parkC
xform 0 -256 -64
p -336 -240 100 0 1 DESC:Park CAR record
p -336 -272 100 0 1 PV:$(top)
p -288 -192 100 1024 -1 name:
use ecars -336 656 100 0 datumC
xform 0 -272 784
p -352 608 100 0 1 DESC:Datum CAR record
p -352 576 100 0 1 PV:$(top)
p -304 656 100 1024 -1 name:
use ecad2 -1264 -256 100 0 park
xform 0 -1184 16
p -1280 -336 100 0 1 DESC:Park components
p -1248 16 100 0 1 FTVA:LONG
p -1248 -16 100 0 1 FTVB:LONG
p -1280 -304 100 0 1 PV:$(top)
p -1280 -368 100 0 1 SNAM:CAD_parkCC
p -1008 48 75 1024 -1 pproc(OUTA):PP
use ecad2 -1248 -1040 100 0 test
xform 0 -1168 -768
p -1264 -1120 100 0 1 DESC:Park components
p -1232 -768 100 0 1 FTVA:LONG
p -1232 -800 100 0 1 FTVB:LONG
p -1264 -1088 100 0 1 PV:$(top)
p -1264 -1152 100 0 1 SNAM:CAD_testCC
p -992 -736 75 1024 -1 pproc(OUTA):PP
use ecad2 -1264 480 100 0 datum
xform 0 -1184 752
p -1280 400 100 0 1 DESC:Datum subsystem
p -1248 752 100 0 1 FTVA:LONG
p -1248 720 100 0 1 FTVB:LONG
p -1280 432 100 0 1 PV:$(top)
p -1280 368 100 0 1 SNAM:CAD_datumCC
p -1008 784 75 1024 -1 pproc(OUTA):PP
[comments]
