[schematic2]
uniq 169
[tools]
[detail]
w 2418 1643 100 0 n#168 agSeqOiwfsLimit.agSeqOiwfsLimit#122.OUT 2336 1632 2560 1632 eaos.Ymax.SLNK
w 1802 1163 100 0 n#150 inhier.OIWFS.P 1744 1152 1920 1152 agSeqOiwfsLimit.agSeqOiwfsLimit#144.OIWFS
w 298 1163 100 0 n#149 inhier.OIWFS.P 240 1152 416 1152 agSeqOiwfsLimit.agSeqOiwfsLimit#143.OIWFS
w 2418 1163 100 0 n#142 agSeqOiwfsLimit.agSeqOiwfsLimit#144.OUT 2336 1152 2560 1152 eaos.Zmax.SLNK
w 914 1163 100 0 n#140 agSeqOiwfsLimit.agSeqOiwfsLimit#143.OUT 832 1152 1056 1152 eaos.Zmin.SLNK
w 1506 171 100 0 n#138 agSeqOiwfsLimitType.agSeqOiwfsLimitType#136.OUT 1440 160 1632 160 ebos.LimitType.SLNK
w 898 171 100 0 n#137 inhier.OIWFS.P 832 160 1024 160 agSeqOiwfsLimitType.agSeqOiwfsLimitType#136.OIWFS
w 2418 651 100 0 n#131 agSeqOiwfsLimit.agSeqOiwfsLimit#132.OUT 2336 640 2560 640 eaos.Rmax.SLNK
w 1802 651 100 0 n#130 inhier.OIWFS.P 1744 640 1920 640 agSeqOiwfsLimit.agSeqOiwfsLimit#132.OIWFS
w 914 651 100 0 n#126 agSeqOiwfsLimit.agSeqOiwfsLimit#127.OUT 832 640 1056 640 eaos.Rmin.SLNK
w 298 651 100 0 n#125 inhier.OIWFS.P 240 640 416 640 agSeqOiwfsLimit.agSeqOiwfsLimit#127.OIWFS
w 1802 1643 100 0 n#120 inhier.OIWFS.P 1744 1632 1920 1632 agSeqOiwfsLimit.agSeqOiwfsLimit#122.OIWFS
w 914 1675 100 0 n#116 agSeqOiwfsLimit.agSeqOiwfsLimit#117.OUT 832 1664 1056 1664 eaos.Ymin.SLNK
w 298 1675 100 0 n#115 inhier.OIWFS.P 240 1664 416 1664 agSeqOiwfsLimit.agSeqOiwfsLimit#117.OIWFS
w 2418 2155 100 0 n#111 agSeqOiwfsLimit.agSeqOiwfsLimit#112.OUT 2336 2144 2560 2144 eaos.Xmax.SLNK
w 1802 2155 100 0 n#110 inhier.OIWFS.P 1744 2144 1920 2144 agSeqOiwfsLimit.agSeqOiwfsLimit#112.OIWFS
w 914 2187 100 0 n#109 agSeqOiwfsLimit.agSeqOiwfsLimit#105.OUT 832 2176 1056 2176 eaos.Xmin.SLNK
w 298 2187 100 0 n#108 inhier.OIWFS.P 240 2176 416 2176 agSeqOiwfsLimit.agSeqOiwfsLimit#105.OIWFS
s 2720 80 100 0 Fetch OIWFS probe limits
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqOiwfsLimits.sch,v 1.14 2010/05/10 21:42:28 gemvx Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use inhier 816 119 100 0 OIWFS
xform 0 832 160
use inhier 224 2135 100 0 OIWFS
xform 0 240 2176
use inhier 1728 2103 100 0 OIWFS
xform 0 1744 2144
use inhier 224 1623 100 0 OIWFS
xform 0 240 1664
use inhier 1728 1591 100 0 OIWFS
xform 0 1744 1632
use inhier 224 599 100 0 OIWFS
xform 0 240 640
use inhier 1728 599 100 0 OIWFS
xform 0 1744 640
use inhier 224 1111 100 0 OIWFS
xform 0 240 1152
use inhier 1728 1111 100 0 OIWFS
xform 0 1744 1152
use eaos 1056 2087 100 0 Xmin
xform 0 1184 2176
p 800 1646 100 0 0 ADEL:0.0005
p 1104 2272 100 0 -1 DESC:Min X probe limit
p 1344 2272 100 0 1 EGU:mm
p 800 1742 100 0 0 IVOA:Set output to IVOV
p 800 1614 100 0 0 MDEL:0.0005
p 800 2030 100 0 0 PREC:3
p 1424 2128 100 0 -1 def(OUT):$(sad)oi:Xmin
p 1168 2080 100 1024 0 name:$(ag)oi$(I)
p 1312 2144 75 768 -1 pproc(OUT):PP
use eaos 2560 2055 100 0 Xmax
xform 0 2688 2144
p 2304 1614 100 0 0 ADEL:0.0005
p 2608 2240 100 0 -1 DESC:Max X probe limit
p 2848 2240 100 0 1 EGU:mm
p 2304 1710 100 0 0 IVOA:Set output to IVOV
p 2304 1582 100 0 0 MDEL:0.0005
p 2304 1998 100 0 0 PREC:3
p 2928 2096 100 0 -1 def(OUT):$(sad)oi:Xmax
p 2672 2048 100 1024 0 name:$(ag)oi$(I)
p 2816 2112 75 768 -1 pproc(OUT):PP
use eaos 1056 1575 100 0 Ymin
xform 0 1184 1664
p 800 1134 100 0 0 ADEL:0.0005
p 1104 1760 100 0 -1 DESC:Min Y probe limit
p 1344 1760 100 0 1 EGU:mm
p 800 1230 100 0 0 IVOA:Set output to IVOV
p 800 1102 100 0 0 MDEL:0.0005
p 800 1518 100 0 0 PREC:3
p 1408 1616 100 0 -1 def(OUT):$(sad)oi:Ymin
p 1168 1568 100 1024 0 name:$(ag)oi$(I)
p 1312 1632 75 768 -1 pproc(OUT):PP
use eaos 2560 1543 100 0 Ymax
xform 0 2688 1632
p 2304 1102 100 0 0 ADEL:0.0005
p 2608 1728 100 0 -1 DESC:Max Y probe limit
p 2848 1728 100 0 1 EGU:mm
p 2304 1198 100 0 0 IVOA:Set output to IVOV
p 2304 1070 100 0 0 MDEL:0.0005
p 2304 1486 100 0 0 PREC:3
p 2928 1584 100 0 -1 def(OUT):$(sad)oi:Ymax
p 2672 1536 100 1024 0 name:$(ag)oi$(I)
p 2816 1600 75 768 -1 pproc(OUT):PP
use eaos 1056 551 100 0 Rmin
xform 0 1184 640
p 800 110 100 0 0 ADEL:0.0005
p 1104 736 100 0 -1 DESC:Min R probe limit
p 1344 736 100 0 1 EGU:mm
p 800 206 100 0 0 IVOA:Set output to IVOV
p 800 78 100 0 0 MDEL:0.0005
p 800 494 100 0 0 PREC:3
p 1392 608 100 0 -1 def(OUT):$(sad)oi:Rmin
p 1168 544 100 1024 0 name:$(ag)oi$(I)
p 1312 608 75 768 -1 pproc(OUT):PP
use eaos 2560 551 100 0 Rmax
xform 0 2688 640
p 2304 110 100 0 0 ADEL:0.0005
p 2608 736 100 0 -1 DESC:Max R probe limit
p 2848 736 100 0 1 EGU:mm
p 2304 206 100 0 0 IVOA:Set output to IVOV
p 2304 78 100 0 0 MDEL:0.0005
p 2304 494 100 0 0 PREC:3
p 2928 608 100 0 -1 def(OUT):$(sad)oi:Rmax
p 2672 544 100 1024 0 name:$(ag)oi$(I)
p 2816 608 75 768 -1 pproc(OUT):PP
use eaos 1056 1063 100 0 Zmin
xform 0 1184 1152
p 800 622 100 0 0 ADEL:0.0005
p 1104 1248 100 0 -1 DESC:Min Z probe limit
p 1344 1248 100 0 1 EGU:mm
p 800 718 100 0 0 IVOA:Set output to IVOV
p 800 590 100 0 0 MDEL:0.0005
p 800 1006 100 0 0 PREC:3
p 1408 1104 100 0 -1 def(OUT):$(sad)oi:Zmin
p 1168 1056 100 1024 0 name:$(ag)oi$(I)
p 1312 1120 75 768 -1 pproc(OUT):PP
use eaos 2560 1063 100 0 Zmax
xform 0 2688 1152
p 2304 622 100 0 0 ADEL:0.0005
p 2592 1248 100 0 -1 DESC:Max Z probe limit
p 2848 1248 100 0 1 EGU:mm
p 2304 718 100 0 0 IVOA:Set output to IVOV
p 2304 590 100 0 0 MDEL:0.0005
p 2304 1006 100 0 0 PREC:3
p 2928 1104 100 0 -1 def(OUT):$(sad)oi:Zmax
p 2672 1056 100 1024 0 name:$(ag)oi$(I)
p 2816 1120 75 768 -1 pproc(OUT):PP
use agSeqOiwfsLimit 416 2023 100 0 agSeqOiwfsLimit#105
xform 0 624 2128
p 480 2016 100 0 1 seta:top $(top)Xmin:
p 480 1984 100 0 1 setb:nonedol $(ag)noRecord
p 480 1952 100 0 1 setc:gmdol $(gmos)wfs:probePatrolXLoLim
p 480 1920 100 0 1 setd:niridol $(niri)wfs:prbxMin
p 480 1888 100 0 1 sete:nirsdol $(nirs)wfs:prbxMin
p 480 1856 100 0 1 setf:f2dol $(f2)wfs:probePatrolXLoLim
p 480 1824 100 0 1 setg:nifsdol $(nifs)sad:wfs:prbxMin
p 480 1792 100 0 1 seth:nicidol $(nici)wfs:prbxMinmm
use agSeqOiwfsLimit 1920 1991 100 0 agSeqOiwfsLimit#112
xform 0 2128 2096
p 1984 1984 100 0 1 seta:top $(top)Xmax:
p 1984 1952 100 0 1 setb:nonedol $(ag)noRecord
p 1984 1920 100 0 1 setc:gmdol $(gmos)wfs:probePatrolXHiLim
p 1984 1888 100 0 1 setd:niridol $(niri)wfs:prbxMax
p 1984 1856 100 0 1 sete:nirsdol $(nirs)wfs:prbxMax
p 1984 1824 100 0 1 setf:f2dol $(f2)wfs:probePatrolXHiLim
p 1984 1792 100 0 1 setg:nifsdol $(nifs)sad:wfs:prbxMax
p 1984 1760 100 0 1 seth:nicidol $(nici)wfs:prbxMaxmm
use agSeqOiwfsLimit 416 1511 100 0 agSeqOiwfsLimit#117
xform 0 624 1616
p 480 1504 100 0 1 seta:top $(top)Ymin:
p 480 1472 100 0 1 setb:nonedol $(ag)noRecord
p 480 1440 100 0 1 setc:gmdol $(gmos)wfs:probePatrolYLoLim
p 480 1408 100 0 1 setd:niridol $(niri)wfs:prbyMin
p 480 1376 100 0 1 sete:nirsdol $(nirs)wfs:prbyMin
p 480 1344 100 0 1 setf:f2dol $(f2)wfs:probePatrolYLoLim
p 480 1312 100 0 1 setg:nifsdol $(nifs)sad:wfs:prbyMin
p 480 1280 100 0 1 seth:nicidol $(nici)wfs:prbyMinmm
use agSeqOiwfsLimit 1920 1479 100 0 agSeqOiwfsLimit#122
xform 0 2128 1584
p 1984 1472 100 0 1 seta:top $(top)Ymax:
p 1984 1440 100 0 1 setb:nonedol $(ag)noRecord
p 1984 1408 100 0 1 setc:gmdol $(gmos)wfs:probePatrolYHiLim
p 1984 1376 100 0 1 setd:niridol $(niri)wfs:prbyMax
p 1984 1344 100 0 1 sete:nirsdol $(nirs)wfs:prbyMax
p 1984 1312 100 0 1 setf:f2dol $(f2)wfs:probePatrolYHiLim
p 1984 1280 100 0 1 setg:nifsdol $(nifs)sad:wfs:prbyMax
p 1984 1248 100 0 1 seth:nicidol $(nici)wfs:prbyMaxmm
use agSeqOiwfsLimit 416 487 100 0 agSeqOiwfsLimit#127
xform 0 624 592
p 480 480 100 0 1 seta:top $(top)Rmin:
p 480 448 100 0 1 setb:nonedol $(ag)noRecord
p 480 416 100 0 1 setc:gmdol $(ag)noRecord
p 480 384 100 0 1 setd:niridol $(ag)noRecord
p 480 352 100 0 1 sete:nirsdol $(ag)noRecord
p 480 320 100 0 1 setf:f2dol $(ag)noRecord
p 480 288 100 0 1 setg:nifsdol $(ag)noRecord
p 480 256 100 0 1 seth:nicidol $(ag)noRecord
use agSeqOiwfsLimit 1920 487 100 0 agSeqOiwfsLimit#132
xform 0 2128 592
p 1984 480 100 0 1 seta:top $(top)Rmax:
p 1984 448 100 0 1 setb:nonedol $(ag)noRecord
p 1984 416 100 0 1 setc:gmdol $(ag)noRecord
p 1984 384 100 0 1 setd:niridol $(ag)noRecord
p 1984 352 100 0 1 sete:nirsdol $(ag)noRecord
p 1984 320 100 0 1 setf:f2dol $(ag)noRecord
p 1984 288 100 0 1 setg:nifsdol $(ag)noRecord
p 1984 256 100 0 1 seth:nicidol $(ag)noRecord
use agSeqOiwfsLimit 416 999 100 0 agSeqOiwfsLimit#143
xform 0 624 1104
p 480 992 100 0 1 seta:top $(top)Zmin:
p 480 960 100 0 1 setb:nonedol $(ag)noRecord
p 480 928 100 0 1 setc:gmdol $(ag)noRecord
p 480 896 100 0 1 setd:niridol $(niri)wfs:focMin
p 480 864 100 0 1 sete:nirsdol $(nirs)wfs:focMin
p 480 832 100 0 1 setf:f2dol $(ag)noRecord
p 480 800 100 0 1 setg:nifsdol $(ag)noRecord
p 480 768 100 0 1 seth:nicidol $(ag)noRecord
use agSeqOiwfsLimit 1920 999 100 0 agSeqOiwfsLimit#144
xform 0 2128 1104
p 1984 992 100 0 1 seta:top $(top)Zmax:
p 1984 960 100 0 1 setb:nonedol $(ag)noRecord
p 1984 928 100 0 1 setc:gmdol $(ag)noRecord
p 1984 896 100 0 1 setd:niridol $(niri)wfs:focMax
p 1984 864 100 0 1 sete:nirsdol $(nirs)wfs:focMax
p 1984 832 100 0 1 setf:f2dol $(ag)noRecord
p 1984 800 100 0 1 setg:nifsdol $(ag)noRecord
p 1984 768 100 0 1 seth:nicidol $(ag)noRecord
use agSeqOiwfsLimitType 1024 7 100 0 agSeqOiwfsLimitType#136
xform 0 1232 112
p 1044 -20 100 0 1 seta:top $(top)oiLimType:
use ebos 1632 71 100 0 LimitType
xform 0 1760 160
p 1680 256 100 0 -1 DESC:OIWFS limit type
p 1536 46 100 0 0 IVOA:Set output to IVOV
p 1312 14 100 0 0 ONAM:Radial
p 1312 46 100 0 0 ZNAM:XY
p 1312 -420 100 0 0 def(DOL):0.0
p 1968 128 100 0 -1 def(OUT):$(sad)oi:LimitType
p 1744 64 100 1024 0 name:$(ag)oi$(I)
p 1888 128 75 768 -1 pproc(OUT):PP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
