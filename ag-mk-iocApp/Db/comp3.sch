[schematic2]
uniq 59
[tools]
[detail]
w 560 1099 100 0 n#58 compCad.compCad#30.FLNK 464 1088 704 1088 outhier.FLNK.p
w 88 1099 100 0 n#57 inhier.SLNK.P 16 1088 208 1088 compCad.compCad#30.SLNK
w 992 683 100 0 n#56 motor.motor#36.CURR 992 672 1040 672 hwout.hwout#50.outp
w 992 411 100 0 n#55 motor.motor#35.CURR 992 400 1040 400 hwout.hwout#52.outp
w 992 139 100 0 n#54 hwout.hwout#53.outp 1040 128 992 128 motor.motor#48.CURR
w 778 163 100 0 n#47 hwin.hwin#49.in 784 160 832 160 motor.motor#48.MVEL
w 778 707 100 0 n#34 hwin.hwin#38.in 784 704 832 704 motor.motor#36.MVEL
w 778 435 100 0 n#33 hwin.hwin#37.in 784 432 832 432 motor.motor#35.MVEL
s 144 1232 100 0 component CAD records.
s 144 1264 100 0 Two axis 
s 1600 -160 500 512 comp3.sch
s 608 896 150 0 List of motors making up the mechanism...
s 1712 2112 100 0 $Id: comp3.sch,v 1.2 2001/05/05 22:43:31 cjm Exp $
n -512 1376 68 1728 100
This schematic contains all the srcbase
records pertaining to a two axis
continuous component of the A&G.
.
The schematic is divided into the
following subschematics:
.
comp3ccCad  - Component CAD records.
compcar    - Component CAR records.
(comp3cSad  - Component Status/Alarm srcbase)
comp3Mech - 3 axis mechanism
simulation srcbase
.
The SNL connects these srcbases.
_
n -272 -96 258 256 100
This schematic contains the srcbase
records which simulate the behaviour of
a 3 axis discrete mechanism.
.
In general, a mechanism can contain one
or more motors, and a separate subschematic
defines the records for each motor.
More motors can be added by adding new
instances of the "motor" schematic with
different values for the "motor"
variable.
.
This 3 axis mechanism has 3 motors.
.
_
[cell use]
use inhier 0 1047 100 0 SLNK
xform 0 16 1088
use outhier 672 1047 100 0 FLNK
xform 0 688 1088
use hwout 1040 631 100 0 hwout#50
xform 0 1136 672
p 1136 663 100 0 -1 val(outp):$(top)$(mech)DPRead.A
use hwout 1040 359 100 0 hwout#52
xform 0 1136 400
p 1136 391 100 0 -1 val(outp):$(top)$(mech)DPRead.B
use hwout 1040 87 100 0 hwout#53
xform 0 1136 128
p 1136 119 100 0 -1 val(outp):$(top)$(mech)DPRead.C
use motor 832 279 100 0 motor#35
xform 0 912 400
p 852 252 100 0 1 set:motor :2:
use motor 832 7 100 0 motor#48
xform 0 912 128
p 852 -20 100 0 1 set:motor :3:
use motor 832 551 100 0 motor#36
xform 0 912 672
p 848 512 100 0 1 set:motor :
use bc200tr -880 -360 -100 0 frame
xform 0 800 944
p 1696 -192 100 0 1 author:O.Frischmuth
p 1920 -208 100 0 -1 border:C
p 1696 -224 100 0 1 checked:O.Frischmuth
p 1952 -208 100 0 -1 date:24 Jun 97
p 1936 -80 100 0 -1 project:A&G unit
p 1936 -144 100 0 -1 title:3 Axis Component Schematic
use hwin 616 392 100 0 hwin#37
xform 0 688 432
p 595 424 100 0 -1 val(in):40000
use hwin 616 664 100 0 hwin#38
xform 0 688 704
p 595 696 100 0 -1 val(in):40000
use hwin 616 120 100 0 hwin#49
xform 0 688 160
p 595 152 100 0 -1 val(in):40000
use compCad 256 1031 100 0 compCad#30
xform 0 336 1136
use snl 1792 1415 100 0 snl#18
xform 0 2080 1728
p 1904 1712 100 0 1 FNAM:cicsSt.stpp
p 1904 1680 100 0 1 SS:comp_ss
[comments]
