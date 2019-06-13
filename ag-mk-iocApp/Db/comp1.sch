[schematic2]
uniq 47
[tools]
[detail]
w 88 1099 100 0 n#46 inhier.SLNK.P 16 1088 208 1088 compCad.compCad#21.SLNK
w 544 1099 100 0 n#45 compCad.compCad#21.FLNK 464 1088 672 1088 outhier.FLNK.p
w 1032 75 100 0 n#42 motor.motor#38.CURR 992 64 1120 64 hwout.hwout#41.outp
w 776 107 100 0 n#40 hwin.hwin#39.in 768 96 832 96 motor.motor#38.MVEL
s 1696 2112 100 0 $Id: comp1.sch,v 1.3 2001/05/05 22:43:31 cjm Exp $
s 1600 -160 500 512 comp1.sch
s 736 240 150 0 List of motors making up the mechanism...
s 752 352 100 0 - - - - - More motors can be added - - - - -
n -512 1376 68 1728 100
This schematic contains all the srcbase
records pertaining to a single axis
discrete component of the A&G.
.
The schematic is divided into the
following subschematics:
.
compCad  - Component CAD records.
compCar    - Component CAR records.
comp1dSad  - Component Status/Alarm srcbase
comp1Mech - 1 axis 
mechanism simulation srcbase
.
The SNL connects these srcbases.
_
n -208 -112 322 240 100
This schematic contains the srcbase
records which simulate the behaviour of
a 1 axis discrete mechanism.
.
In general, a mechanism can contain one
or more motors, and a separate subschematic
defines the records for each motor.
More motors can be added by adding new
instances of the "motor" schematic with
different values for the "motor"
variable.
.
This 1 axis mechanism has one motor.
.
_
[cell use]
use inhier 0 1047 100 0 SLNK
xform 0 16 1088
use outhier 640 1047 100 0 FLNK
xform 0 656 1088
use hwout 1120 23 100 0 hwout#41
xform 0 1216 64
p 1216 55 100 0 -1 val(outp):$(top)$(mech)DPRead.A
use hwin 576 55 100 0 hwin#39
xform 0 672 96
p 579 88 100 0 -1 val(in):40000
use motor 832 -57 100 0 motor#38
xform 0 912 64
p 832 -64 100 0 1 seta:motor :
use agMechSim 1648 295 100 0 agMechSim#37
xform 0 1776 560
p 1668 268 100 0 1 seta:top $(top)$(mech):
use bc200tr -880 -360 -100 0 frame
xform 0 800 944
p 1696 -192 100 0 1 author:O.Frischmuth
p 1920 -208 100 0 -1 border:C
p 1696 -224 100 0 1 checked:O.Frischmuth
p 1952 -208 100 0 -1 date:24 Jun 97
p 1936 -80 100 0 -1 project:A&G unit
p 1936 -144 100 0 -1 title:One Axis Component Schematic
use compCad 256 1031 100 0 compCad#21
xform 0 336 1136
use snl 1760 1447 100 0 snl#18
xform 0 2048 1760
p 1872 1744 100 0 1 FNAM:cicsSt.stpp
p 1872 1712 100 0 1 SS:comp1_ss
[comments]
