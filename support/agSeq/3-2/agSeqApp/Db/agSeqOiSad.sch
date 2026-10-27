[schematic2]
uniq 27
[tools]
[detail]
w 2584 747 100 0 n#23 esirs.focus.FLNK 2512 896 2560 896 2560 736 2656 736 esirs.inPosition.SLNK
w 2008 747 100 0 n#20 esirs.y.FLNK 1888 896 1968 896 1968 736 2096 736 esirs.focus.SLNK
w 1376 747 100 0 n#19 esirs.x.FLNK 1264 896 1328 896 1328 736 1472 736 esirs.y.SLNK
s 2432 2336 100 0 $Id: agSeqOiSad.sch,v 1.4 2003/02/07 16:55:29 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2800 80 100 0 SAD records
[cell use]
use esirs 872 232 100 0 probeParked
xform 0 1056 384
p 960 542 100 0 -1 DESC:OIWFS parked flag
p 784 -32 100 0 0 FDSC:Parked flag of the selected OIWFS
p 928 270 100 0 1 FTVL:LONG
p 928 384 100 0 1 SCAN:1 second
p 928 304 100 0 1 def(INP):$(ag)oiPark:probeParked
p 960 224 100 1024 0 name:$(top)$(I)
use esirs 216 232 100 0 fldstopName
xform 0 400 384
p 304 542 100 0 -1 DESC:A&G OIWFS field stop name
p 128 -32 100 0 0 FDSC:Field stop name of selected OIWFS
p 272 270 100 0 1 FTVL:STRING
p 272 302 100 0 0 SCAN:Passive
p -272 510 100 0 0 def(INP):0.0
p 304 224 100 1024 0 name:$(top)$(I)
use esirs 2096 647 100 0 focus
xform 0 2304 800
p 2032 608 100 0 0 ADEL:0.0005
p 2144 960 100 0 -1 DESC:Z position of probe
p 2176 736 100 0 1 EGU:mm
p 2032 384 100 0 0 FDSC:Current focus position of probe
p 2176 704 100 0 1 FTVL:DOUBLE
p 2032 32 100 0 0 MDEL:0.0005
p 2288 576 100 0 0 PREC:3
p 2176 784 100 0 0 SCAN:Passive
p 2176 816 100 0 1 def(INP):$(ag)oiFocus:focus
p 2208 640 100 1024 0 name:$(top)$(I)
p 2096 896 75 1280 -1 palrm(INP):MS
use esirs 1472 647 100 0 y
xform 0 1680 800
p 1408 608 100 0 0 ADEL:0.0005
p 1520 960 100 0 -1 DESC:Y position of probe
p 1552 736 100 0 1 EGU:mm
p 1408 384 100 0 0 FDSC:Current y position in focal plane
p 1552 704 100 0 1 FTVL:DOUBLE
p 1408 32 100 0 0 MDEL:0.0005
p 1664 576 100 0 0 PREC:3
p 1552 784 100 0 0 SCAN:Passive
p 1552 816 100 0 1 def(INP):$(ag)oiPosn:y
p 1584 640 100 1024 0 name:$(top)$(I)
p 1472 896 75 1280 -1 palrm(INP):MS
use esirs 848 647 100 0 x
xform 0 1056 800
p 784 608 100 0 0 ADEL:0.0005
p 896 960 100 0 -1 DESC:X position of probe
p 928 736 100 0 1 EGU:mm
p 784 384 100 0 0 FDSC:Current x position in focal plane
p 928 704 100 0 1 FTVL:DOUBLE
p 784 32 100 0 0 MDEL:0.0005
p 1040 576 100 0 0 PREC:3
p 928 784 100 0 1 SCAN:1 second
p 928 816 100 0 1 def(INP):$(ag)oiPosn:x
p 960 640 100 1024 0 name:$(top)$(I)
p 848 896 75 1280 -1 palrm(INP):MS
use esirs 216 648 100 0 filterName
xform 0 400 800
p 304 958 100 0 -1 DESC:A&G OIWFS filter name
p 272 686 100 0 1 FTVL:STRING
p 272 718 100 0 0 SCAN:Passive
p -272 926 100 0 0 def(INP):0.0
p 304 640 100 1024 0 name:$(top)$(I)
use esirs 176 1479 100 0 LimitType
xform 0 384 1632
p 224 1792 100 0 -1 DESC:Limit type of current OIWFS
p 112 1216 100 0 0 FDSC:Limit type of OIWFS, 0 = XY, 1 = Radial
p 256 1536 100 0 1 FTVL:LONG
p 288 1472 100 1024 0 name:$(top)$(I)
use esirs 832 1479 100 0 Rmin
xform 0 1040 1632
p 768 1440 100 0 0 ADEL:0.0005
p 880 1792 100 0 -1 DESC:Min. radius of OIWFS
p 912 1568 100 0 1 EGU:mm
p 768 1216 100 0 0 FDSC:Min. radius to which oiwfs can reach
p 912 1536 100 0 1 FTVL:DOUBLE
p 768 864 100 0 0 MDEL:0.0005
p 1024 1408 100 0 0 PREC:3
p 944 1472 100 1024 0 name:$(top)$(I)
use esirs 1456 1479 100 0 Rmax
xform 0 1664 1632
p 1392 1440 100 0 0 ADEL:0.0005
p 1504 1792 100 0 -1 DESC:Max. radius of OIWFS
p 1536 1568 100 0 1 EGU:mm
p 1392 1216 100 0 0 FDSC:Max. radius to which oiwfs can reach
p 1536 1536 100 0 1 FTVL:DOUBLE
p 1392 864 100 0 0 MDEL:0.0005
p 1648 1408 100 0 0 PREC:3
p 1568 1472 100 1024 0 name:$(top)$(I)
use esirs 176 1063 100 0 Xmin
xform 0 384 1216
p 112 1024 100 0 0 ADEL:0050.0
p 224 1376 100 0 -1 DESC:Min. x limit of OIWFS
p 256 1152 100 0 1 EGU:mm
p 112 800 100 0 0 FDSC:Min. x coord. to which oiwfs can reach
p 256 1120 100 0 1 FTVL:DOUBLE
p 112 448 100 0 0 MDEL:0.0005
p 368 992 100 0 0 PREC:3
p 288 1056 100 1024 0 name:$(top)$(I)
use esirs 832 1063 100 0 Xmax
xform 0 1040 1216
p 768 1024 100 0 0 ADEL:0.0005
p 880 1376 100 0 -1 DESC:Max. x limit of OIWFS
p 912 1152 100 0 1 EGU:mm
p 768 800 100 0 0 FDSC:Max. x coord. to which oiwfs can reach
p 912 1120 100 0 1 FTVL:DOUBLE
p 768 448 100 0 0 MDEL:0.0005
p 1024 992 100 0 0 PREC:3
p 944 1056 100 1024 0 name:$(top)$(I)
use esirs 1456 1063 100 0 Ymin
xform 0 1664 1216
p 1504 1376 100 0 -1 DESC:Min. y limit of OIWFS
p 1536 1152 100 0 1 EGU:mm
p 1392 800 100 0 0 FDSC:Min. y coord. to which oiwfs can reach
p 1536 1120 100 0 1 FTVL:DOUBLE
p 1648 992 100 0 0 PREC:3
p 1568 1056 100 1024 0 name:$(top)$(I)
use esirs 2080 1063 100 0 Ymax
xform 0 2288 1216
p 2128 1376 100 0 -1 DESC:Max. y limit of OIWFS
p 2160 1152 100 0 1 EGU:mm
p 2016 800 100 0 0 FDSC:Max. y coord. to which oiwfs can reach
p 2160 1120 100 0 1 FTVL:DOUBLE
p 2272 992 100 0 0 PREC:3
p 2192 1056 100 1024 0 name:$(top)$(I)
use esirs 2680 648 100 0 inPosition
xform 0 2864 800
p 2768 958 100 0 -1 DESC:OIWFS in position flag
p 2592 384 100 0 0 FDSC:in position flag of the sel. OIWFS
p 2736 686 100 0 1 FTVL:LONG
p 2736 718 100 0 0 SCAN:Passive
p 2736 720 100 0 1 def(INP):$(ag)inPos:inPosition
p 2768 640 100 1024 0 name:$(top)$(I)
use esirs 2080 1479 100 0 Zmin
xform 0 2288 1632
p 2016 1440 100 0 0 ADEL:0.0005
p 2128 1792 100 0 -1 DESC:Min. z limit of OIWFS
p 2160 1568 100 0 1 EGU:mm
p 2016 1216 100 0 0 FDSC:Min. z coord. to which oiwfs can reach
p 2160 1536 100 0 1 FTVL:DOUBLE
p 2016 864 100 0 0 MDEL:0.0005
p 2272 1408 100 0 0 PREC:3
p 2192 1472 100 1024 0 name:$(top)$(I)
use esirs 2656 1479 100 0 Zmax
xform 0 2864 1632
p 2592 1440 100 0 0 ADEL:0.0005
p 2704 1792 100 0 -1 DESC:Max. z limit of OIWFS
p 2736 1568 100 0 1 EGU:mm
p 2592 1216 100 0 0 FDSC:Max. z coord. to which oiwfs can reach
p 2736 1536 100 0 1 FTVL:DOUBLE
p 2592 864 100 0 0 MDEL:0.0005
p 2848 1408 100 0 0 PREC:3
p 2768 1472 100 1024 0 name:$(top)$(I)
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
