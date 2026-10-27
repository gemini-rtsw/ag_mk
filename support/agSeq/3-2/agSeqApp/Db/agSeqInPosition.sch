[schematic2]
uniq 68
[tools]
[detail]
w 856 795 100 0 n#67 inhier.PWFS2.P 816 784 944 784 agSeqSubsysInPosn.agSeqSubsysInPosn#45.LOADED
w 856 1195 100 0 n#66 inhier.PWFS1.P 816 1184 944 1184 agSeqSubsysInPosn.agSeqSubsysInPosn#43.LOADED
w 856 1579 100 0 n#65 inhier.OIDC.P 816 1568 944 1568 agSeqSubsysInPosn.agSeqSubsysInPosn#41.LOADED
w 864 1931 100 0 n#64 inhier.CC.P 816 1920 960 1920 agSeqSubsysInPosn.agSeqSubsysInPosn#39.LOADED
w 856 427 100 0 n#63 inhier.OIWFS.P 816 416 944 416 agSeqOiInPosn.agSeqOiInPosn#47.OIWFS
w 1648 331 100 0 n#62 agSeqOiInPosn.agSeqOiInPosn#47.FLNK 1392 320 1952 320 1952 912 2016 912 esels.calcInPosn.SLNK
w 1584 427 100 0 n#61 agSeqOiInPosn.agSeqOiInPosn#47.INPOSN 1392 416 1824 416 1824 1168 2016 1168 esels.calcInPosn.INPE
w 1568 795 100 0 n#60 agSeqSubsysInPosn.agSeqSubsysInPosn#45.INPOSN 1392 784 1792 784 1792 1200 2016 1200 esels.calcInPosn.INPD
w 1552 1195 100 0 n#59 agSeqSubsysInPosn.agSeqSubsysInPosn#43.INPOSN 1392 1184 1760 1184 1760 1232 2016 1232 esels.calcInPosn.INPC
w 1552 1579 100 0 n#58 agSeqSubsysInPosn.agSeqSubsysInPosn#41.INPOSN 1392 1568 1760 1568 1760 1264 2016 1264 esels.calcInPosn.INPB
w 1576 1931 100 0 n#57 agSeqSubsysInPosn.agSeqSubsysInPosn#39.INPOSN 1408 1920 1792 1920 1792 1296 2016 1296 esels.calcInPosn.INPA
w 2360 1195 100 0 n#56 esels.calcInPosn.VAL 2304 1120 2336 1120 2336 1184 2432 1184 elongouts.inPosition.DOL
w 2344 1163 100 0 n#55 esels.calcInPosn.FLNK 2304 1152 2432 1152 elongouts.inPosition.SLNK
w 1160 539 100 0 n#53 agSeqSubsysInPosn.agSeqSubsysInPosn#45.FLNK 1392 688 1472 688 1472 528 896 528 896 320 944 320 agSeqOiInPosn.agSeqOiInPosn#47.SLNK
w 1160 923 100 0 n#52 agSeqSubsysInPosn.agSeqSubsysInPosn#43.FLNK 1392 1088 1472 1088 1472 912 896 912 896 688 944 688 agSeqSubsysInPosn.agSeqSubsysInPosn#45.SLNK
w 1160 1307 100 0 n#51 agSeqSubsysInPosn.agSeqSubsysInPosn#41.FLNK 1392 1472 1472 1472 1472 1296 896 1296 896 1088 944 1088 agSeqSubsysInPosn.agSeqSubsysInPosn#43.SLNK
w 1160 1675 100 0 n#50 agSeqSubsysInPosn.agSeqSubsysInPosn#39.FLNK 1408 1824 1472 1824 1472 1664 896 1664 896 1472 944 1472 agSeqSubsysInPosn.agSeqSubsysInPosn#41.SLNK
w 680 1835 100 0 n#49 efanouts.fan.FLNK 304 1264 448 1264 448 1824 960 1824 agSeqSubsysInPosn.agSeqSubsysInPosn#39.SLNK
s 1280 2240 200 0 Generate A&G "inPosition" flag
s 32 2176 100 0 some transitions being missed.
s 32 2208 100 0 at greater than 1 Hz but may result in
s 32 2240 100 0 This ensures that the SAD item is not updated
s 32 2272 100 0 All processing is driven off the fan record
s 2768 64 100 0 flag for A&G
s 2656 96 100 0 Generate overall "in position"
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqInPosition.sch,v 1.6 2007/05/18 22:29:20 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use esels 2016 839 100 0 calcInPosn
xform 0 2160 1104
p 2176 896 100 0 1 SELM:Low Signal
use agSeqOiInPosn 944 263 100 0 agSeqOiInPosn#47
xform 0 1168 368
use agSeqSubsysInPosn 944 631 100 0 agSeqSubsysInPosn#45
xform 0 1168 736
p 1008 624 100 0 1 seta:top $(top)pwfs2:
p 1008 576 100 0 1 setb:recname $(pwfs2)inPosition
use agSeqSubsysInPosn 944 1031 100 0 agSeqSubsysInPosn#43
xform 0 1168 1136
p 1008 1024 100 0 1 seta:top $(top)pwfs1:
p 1008 976 100 0 1 setb:recname $(pwfs1)inPosition
use agSeqSubsysInPosn 944 1415 100 0 agSeqSubsysInPosn#41
xform 0 1168 1520
p 1008 1408 100 0 1 seta:top $(top)oiwfs:
p 1008 1360 100 0 1 setb:recname $(oiwfs)inPosition
use agSeqSubsysInPosn 960 1767 100 0 agSeqSubsysInPosn#39
xform 0 1184 1872
p 1024 1760 100 0 1 seta:top $(top)cc:
p 1024 1712 100 0 1 setb:recname $(ag)cc:inPosition
use efanouts 64 1015 100 0 fan
xform 0 184 1168
p -16 1088 100 0 1 SCAN:1 second
use inhier 800 1527 100 0 OIDC
xform 0 816 1568
use inhier 800 1879 100 0 CC
xform 0 816 1920
use inhier 800 1143 100 0 PWFS1
xform 0 816 1184
use inhier 800 743 100 0 PWFS2
xform 0 816 784
use inhier 800 375 100 0 OIWFS
xform 0 816 416
use elongouts 2432 1063 100 0 inPosition
xform 0 2560 1152
p 2432 1264 100 0 -1 DESC:A&G in position status
p 2272 1038 100 0 0 IVOA:Set output to IVOV
p 2272 1070 100 0 0 OMSL:closed_loop
p 2128 1216 100 0 0 def(DOL):0.0
p 2800 1120 100 0 -1 def(OUT):$(sad)inPosition
p 2576 992 100 1024 0 name:$(top)$(I)
p 2688 1120 75 768 -1 pproc(OUT):PP
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
