[schematic2]
uniq 150
[tools]
[detail]
w -726 -549 100 0 n#149 esirs.simLevelL.VAL -736 -560 -656 -560 -656 -528 -576 -528 esirs.simuMode.INP
w -662 -677 100 0 n#148 esirs.simLevelL.FLNK -736 -528 -688 -528 -688 -688 -576 -688 esirs.simuMode.SLNK
s 976 -1072 500 512 ccSysSad.sch
s -912 -1280 500 0 System SAD
s -464 -416 100 0 additional records (not in ICD)
s 320 1024 100 0 $Id: ccSysSad.sch,v 1.3 2000/12/20 13:27:56 cjm Exp $
n -2064 -1248 -1584 -896 100
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
use esirs -576 -777 100 0 simuMode
xform 0 -368 -624
p -480 -800 100 0 1 DESC:Simulation mode
p -625 -896 100 0 0 FDSC:Debugging mode [NOLOG|NONE|MIN|FULL]
p -480 -832 100 0 1 FTVL:STRING
p -620 -996 100 0 0 NELM:1
p -600 -1016 100 0 0 NORD:1
p -480 -896 100 0 1 PV:$(sadtop)
p -480 -864 100 0 1 SNAM:agSimModeSIR
p -384 -608 100 0 -1 Type:sir
use esirs 112 -73 100 0 state
xform 0 320 80
p 208 -96 100 0 1 DESC:Instrument state
p 63 -496 100 0 0 EGU: 
p 63 -192 100 0 0 FDSC:Instrument state [BOOTING|INITIALISING|RUNNING|CONFIGURING]
p 208 -128 100 0 1 FTVL:STRING
p 83 -516 100 0 0 NELM:1
p 103 -536 100 0 0 NORD:1
p 208 -192 100 0 1 PV:$(sadtop)
p 208 -160 100 0 1 SNAM:
p 208 -240 100 0 1 VAL:BOOTING
use esirs -576 503 100 0 name
xform 0 -368 656
p -480 480 100 0 1 DESC:Instrument Name
p -625 80 100 0 0 EGU: 
p -480 480 100 0 0 FDSC:Instrument Name - should be A&G
p -480 448 100 0 1 FTVL:STRING
p -605 60 100 0 0 NELM:1
p -585 40 100 0 0 NORD:1
p -480 384 100 0 1 PV:$(sadtop)
p -480 416 100 0 1 SNAM:
p -480 336 100 0 1 VAL:A&G
use esirs 0 -777 100 0 debugMode
xform 0 208 -624
p 96 -800 100 0 1 DESC:Debugging mode
p -49 -896 100 0 0 FDSC:Debugging mode [NOLOG|NONE|MIN|FULL]
p 96 -832 100 0 1 FTVL:STRING
p -44 -996 100 0 0 NELM:1
p -24 -1016 100 0 0 NORD:1
p 96 -896 100 0 1 PV:$(sadtop)
p 96 -864 100 0 1 SNAM:
p 192 -608 100 0 -1 Type:sir
use esirs -576 -57 100 0 historyLog
xform 0 -368 96
p -480 -80 100 0 1 DESC:History log record
p -625 -176 100 0 0 FDSC:History log record (should be BIGSTRING)
p -480 -112 100 0 1 FTVL:STRING
p -620 -276 100 0 0 NELM:1
p -600 -296 100 0 0 NORD:1
p -480 -176 100 0 1 PV:$(sadtop)
p -480 -144 100 0 1 SNAM:
use esirs 80 503 100 0 present
xform 0 288 656
p 31 -272 100 0 0 ADEL:0.000000000000000e+00
p 31 -208 100 0 0 BRSV:NO_ALARM
p 144 480 100 0 1 DESC:Current time / Heart Beat
p 31 -336 100 0 0 DISS:NO_ALARM
p 31 208 100 0 0 DISV:1
p 31 80 100 0 0 EGU:units
p 31 464 100 0 0 EVNT:0
p 31 384 100 0 0 FDSC:Heart beat record - shows that CC is still alive
p 144 448 100 0 1 FTVL:LONG
p 31 -80 100 0 0 HHSV:NO_ALARM
p 31 -16 100 0 0 HIGH:0.0000000e+00 
p 31 48 100 0 0 HIHI:0.0000000e+00 
p 31 -112 100 0 0 HSV:NO_ALARM
p 31 -240 100 0 0 HYST:0.000000000000000e+00
p 31 -176 100 0 0 LLSV:NO_ALARM
p 31 16 100 0 0 LOLO:0.0000000e+00 
p 31 -48 100 0 0 LOW:0.0000000e+00 
p 31 -144 100 0 0 LSV:NO_ALARM
p 31 -304 100 0 0 MDEL:0.000000000000000e+00
p 51 -485 100 0 0 NELM:1
p 71 -505 100 0 0 NORD:1
p 31 496 100 0 0 PHAS:0
p 31 240 100 0 0 PINI:NO
p 31 144 100 0 0 PREC:0
p 31 -368 100 0 0 PRIO:LOW
p 144 384 100 0 1 PV:$(sadtop)
p 31 528 100 0 0 SCAN:Passive
p 31 -352 100 0 0 SIMS:NO_ALARM
p 144 416 100 0 1 SNAM:
p 256 672 100 0 -1 Type:sir
p 31 336 100 0 0 def(FLNK):0.000000000000000e+00
p 31 -432 100 0 0 def(INP):0.000000000000000e+00
p 31 -464 100 0 0 def(SDIS):0.000000000000000e+00
p 64 762 75 0 -1 palrm(INP):NMS
p 64 570 75 0 -1 palrm(SDIS):NMS
p 32 762 75 0 -1 pproc(INP):NPP
p 32 570 75 0 -1 pproc(SDIS):NPP
p 31 272 100 0 0 primitive:sir
p 31 304 100 0 0 typ(FLNK):path
p 31 -400 100 0 0 typ(INP):path
p 31 -465 100 0 0 typ(SDIS):path
use esirs -1152 -777 100 0 simLevelL
xform 0 -944 -624
p -1056 -800 100 0 1 DESC:Simulation Level
p -1201 -896 100 0 0 FDSC:Simulation level [NONE|VSM|FAST|FULL]
p -1056 -832 100 0 1 FTVL:LONG
p -1196 -996 100 0 0 NELM:1
p -1176 -1016 100 0 0 NORD:1
p -1056 -896 100 0 1 PV:$(sadtop)
p -1056 -864 100 0 1 SNAM:
p -960 -608 100 0 -1 Type:sir
use bc200tr -2256 -1448 -100 0 frame
xform 0 -576 -144
p 304 -1280 100 0 1 author:O.Frischmuth
p 304 -1312 100 0 1 checked:O.Frischmuth
p 576 -1296 100 0 -1 date:18 Apr 1997
p 560 -1168 100 0 1 project:A&G unit
p 544 -1280 100 0 -1 size:C
p 560 -1232 100 0 -1 title:A&G CC system Status/Alarm Database
[comments]
