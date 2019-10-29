[schematic2]
uniq 51
[tools]
[detail]
w 928 571 100 0 n#50 motor.motor#36.CURR 928 560 976 560 hwout.hwout#47.outp
w 928 299 100 0 n#49 motor.motor#35.CURR 928 288 976 288 hwout.hwout#48.outp
w 714 595 100 0 n#34 hwin.hwin#38.in 720 592 768 592 motor.motor#36.MVEL
w 714 323 100 0 n#33 hwin.hwin#37.in 720 320 768 320 motor.motor#35.MVEL
s 1392 128 100 0 - - - - - More motors can be added - - - - -
s 688 752 150 0 List of motors making up the mechanism...
s 1600 -160 500 512 comp2.sch
s 144 1264 100 0 Two axis 
s 144 1232 100 0 component CAD records.
n -272 -96 258 256 100
This schematic contains the srcbase
records which simulate the behaviour of
a 2 axis discrete mechanism.
.
In general, a mechanism can contain one
or more motors, and a separate subschematic
defines the records for each motor.
More motors can be added by adding new
instances of the "motor" schematic with
different values for the "motor"
variable.
.
This 2 axis mechanism has two motors.
.
_
n -512 1376 68 1728 100
This schematic contains all the srcbase
records pertaining to a two axis
continuous component of the A&G.
.
The schematic is divided into the
following subschematics:
.
comp2ccCad  - Component CAD records.
compcar    - Component CAR records.
(comp2cSad  - Component Status/Alarm srcbase)
comp2Mech - 2 axis mechanism
simulation srcbase
.
The SNL connects these srcbases.
_
[cell use]
use hwout 976 519 100 0 hwout#47
xform 0 1072 560
p 1072 551 100 0 -1 val(outp):$(top)$(mech)DPRead.A
use hwout 976 247 100 0 hwout#48
xform 0 1072 288
p 1072 279 100 0 -1 val(outp):$(top)$(mech)DPRead.B
use hwin 552 552 100 0 hwin#38
xform 0 624 592
p 531 584 100 0 -1 val(in):40000
use hwin 552 280 100 0 hwin#37
xform 0 624 320
p 531 312 100 0 -1 val(in):40000
use motor 768 439 100 0 motor#36
xform 0 848 560
p 784 400 100 0 1 set:motor :
use motor 768 167 100 0 motor#35
xform 0 848 288
p 788 140 100 0 1 set:motor :2:
use compCad 256 1031 100 0 compCad#30
xform 0 336 1136
use snl 1792 1415 100 0 snl#18
xform 0 2080 1728
p 1904 1712 100 0 1 FNAM:cicsSt.stpp
p 1904 1680 100 0 1 SS:comp_ss
use bc200tr -880 -360 -100 0 frame
xform 0 800 944
p 1696 -192 100 0 1 author:O.Frischmuth
p 1920 -208 100 0 -1 border:C
p 1696 -224 100 0 1 checked:O.Frischmuth
p 1952 -208 100 0 -1 date:24 Jun 97
p 1936 -80 100 0 -1 project:A&G unit
p 1936 -144 100 0 -1 title:Two Axis Component Schematic
[comments]
