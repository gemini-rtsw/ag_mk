[schematic2]
uniq 238
[tools]
[detail]
w -686 -37 100 0 n#237 esirs.esirs#219.FLNK -832 112 -736 112 -736 -48 -576 -48 esirs.esirs#218.SLNK
w -1406 -37 100 0 n#236 eaos.limitScan.FLNK -1504 -48 -1248 -48 esirs.esirs#219.SLNK
w -732 -485 100 0 n#229 esirs.esirs#217.FLNK -832 -400 -736 -400 -736 -560 -576 -560 esirs.esirs#216.SLNK
w -718 -293 100 0 n#227 esirs.esirs#218.FLNK -160 112 -48 112 -48 -304 -1328 -304 -1328 -560 -1248 -560 esirs.esirs#217.SLNK
w -1150 -901 100 0 n#209 hwin.hwin#222.in -960 -944 -960 -912 -1280 -912 -1280 -1040 -1216 -1040 esirs.esirs#221.INP
w -710 -1189 100 0 n#208 esirs.esirs#221.FLNK -800 -1040 -736 -1040 -736 -1200 -624 -1200 esirs.esirs#220.SLNK
w -766 -1061 100 0 n#207 esirs.esirs#221.VAL -800 -1072 -672 -1072 -672 -1040 -624 -1040 esirs.esirs#220.INP
w 546 -133 100 0 n#205 esirs.esirs#167.SLNK 416 128 272 128 272 -144 880 -144 880 -256 832 -256 esirs.esirs#168.FLNK
w 420 283 100 2 n#204 hwin.hwin#203.in 416 288 416 288 esirs.esirs#167.INP
w 386 -245 100 0 n#172 hwin.hwin#171.in 416 -256 416 -256 esirs.esirs#168.INP
s -160 608 100 0 This schematic holds some extra SIR records that are needed
s -144 560 100 0 by the TCS but are not yet part of the formal ICD
s 896 -1184 500 512 pwfsSysSad.sch
s 224 384 100 0 1: enough samples for this trackId
n -2096 -1328 -1616 -976 100
This schematic contains the systemwide
Status/Alarm Database for the A&G.
It contains these universal records:
.
name   - Name of instrument (defaulted
to "A&G".
.
state  - State of instrument (BOOTING,
INITIALISING or RUNNING).
.
health - Health of instrument (GOOD,
WARNING or BAD).
.
plus others as shown.
_
[cell use]
use eaos -1760 -169 100 0 limitScan
xform 0 -1632 -80
p -1600 -192 100 0 1 SCAN:2 second
p -1648 -176 100 1024 0 name:$(top)$(I)
use hwin -1152 -985 100 0 hwin#222
xform 0 -1056 -944
p -1152 -992 100 0 -1 val(in):$(top)probexlat.VALF
use hwin 224 -297 100 0 hwin#171
xform 0 320 -256
p 224 -224 100 0 -1 val(in):$(top)followA.VALG
use hwin 224 247 100 0 hwin#203
xform 0 320 288
p 224 320 100 0 -1 val(in):$(top)followA.VALE
use esirs -1136 -1248 100 0 esirs#221
xform 0 -1008 -1136
p -1152 -1328 100 0 1 DESC:follow ? (1/0)
p -992 -1152 100 0 1 EGU:units
p -1024 -1120 100 0 1 FTVL:LONG
p -1152 -1296 100 0 1 SCAN:2 second
p -976 -1296 100 0 1 SNAM:
p -1024 -1264 100 1024 1 name:$(sadtop)followL
use esirs -544 -1248 100 0 esirs#220
xform 0 -416 -1136
p -560 -1328 100 0 1 DESC:Follow ? (on/off)
p -400 -1152 100 0 1 EGU:units
p -432 -1120 100 0 1 FTVL:STRING
p -560 -1296 100 0 1 SCAN:Passive
p -368 -1296 100 0 1 SNAM:followSIR
p -432 -1264 100 1024 1 name:$(sadtop)followS
use esirs -1168 -96 100 0 esirs#219
xform 0 -1040 16
p -1184 -176 100 0 1 DESC:Maximum radius of probe movement
p -976 32 100 0 1 EGU:mm
p -1184 -208 100 0 1 FDSC:Maximum radius of probe movement
p -1184 -240 100 0 1 FTVL:DOUBLE
p -1184 -272 100 0 1 MDEL:0.005
p -976 0 100 0 1 NELM:1
p -976 -32 100 0 1 PREC:2
p -1184 -144 100 0 1 SCAN:Passive
p -1200 160 100 0 1 def(INP):$(top)Rmax
p -1072 -96 100 1024 1 name:$(sad)Rmax
use esirs -496 -96 100 0 esirs#218
xform 0 -368 16
p -512 -176 100 0 1 DESC:Minimum radius of probe movement
p -304 16 100 0 1 EGU:mm
p -512 -208 100 0 1 FDSC:Minimum radius of probe movement
p -512 -240 100 0 1 FTVL:DOUBLE
p -512 -272 100 0 1 MDEL:0.005
p -304 -16 100 0 1 NELM:1
p -304 -48 100 0 1 PREC:2
p -496 -48 100 0 0 SCAN:Passive
p -512 160 100 0 1 def(INP):$(top)Rmin
p -400 -112 100 1024 1 name:$(sad)Rmin
use esirs -1168 -608 100 0 esirs#217
xform 0 -1040 -496
p -1184 -688 100 0 1 DESC:Maximum focus of probe
p -992 -496 100 0 1 EGU:mm
p -1184 -720 100 0 1 FDSC:Maximum focus of probe
p -1184 -752 100 0 1 FTVL:DOUBLE
p -1184 -784 100 0 1 MDEL:0.005
p -992 -528 100 0 1 NELM:1
p -992 -560 100 0 1 PREC:2
p -1168 -560 100 0 0 SCAN:Passive
p -1200 -352 100 0 1 def(INP):$(top)Zmax
p -1072 -624 100 1024 1 name:$(sad)Zmax
use esirs -496 -608 100 0 esirs#216
xform 0 -368 -496
p -512 -688 100 0 1 DESC:Minimum focus of probe
p -320 -480 100 0 1 EGU:mm
p -512 -720 100 0 1 FDSC:Minimum focus of probe
p -512 -752 100 0 1 FTVL:DOUBLE
p -512 -784 100 0 1 MDEL:0.005
p -320 -512 100 0 1 NELM:1
p -320 -544 100 0 1 PREC:2
p -496 -560 100 0 0 SCAN:Passive
p -528 -352 100 0 1 def(INP):$(top)Zmin
p -400 -624 100 1024 1 name:$(sad)Zmin
use esirs 512 -464 100 0 esirs#168
xform 0 624 -352
p 512 -528 100 0 1 DESC:trackId being followed
p 672 -352 100 0 1 EGU: 
p 512 -560 100 0 1 FDSC:trackId
p 624 -320 100 0 1 FTVL:DOUBLE
p 392 -1192 100 0 0 NELM:1
p 372 -1172 100 0 0 NORD:1
p 672 -384 100 0 1 PREC:3
p 512 -592 100 0 1 SCAN:1 second
p 512 -624 100 0 1 SNAM:
p 640 -464 100 1024 1 name:$(sadtop)trackId
use esirs 512 80 100 0 esirs#167
xform 0 624 192
p 512 16 100 0 1 DESC:Following Data health
p 672 192 100 0 1 EGU:
p 512 -16 100 0 1 FDSC:health
p 624 224 100 0 1 FTVL:STRING
p 392 -648 100 0 0 NELM:1
p 372 -628 100 0 0 NORD:1
p 512 -48 100 0 1 SCAN:Passive
p 512 -80 100 0 1 SNAM:arraySSIR
p 640 80 100 1024 1 name:$(sadtop)arrayS
use bc200tr -2320 -1544 -100 0 frame
xform 0 -640 -240
p 240 -1376 100 0 1 author:O.Frischmuth
p 240 -1408 100 0 1 checked:O.Frischmuth
p 512 -1392 100 0 -1 date:18 Apr 1997
p 496 -1264 100 0 1 project:A&G unit
p 480 -1376 100 0 -1 size:C
p 496 -1328 100 0 -1 title:A&G CC system Status/Alarm Database
[comments]
