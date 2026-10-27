[schematic2]
uniq 45
[tools]
[detail]
w 2552 1803 100 0 n#35 junction 2528 1088 2528 1792 2624 1792 agSeqCad.agSeqCad#20.OIDC
w 1976 1099 100 0 n#35 junction 1952 1088 2048 1088 agSeqCad.agSeqCad#38.OIDC
w 1976 1803 100 0 n#35 junction 1952 528 1952 1792 2048 1792 agSeqCad.agSeqCad#37.OIDC
w 1400 1099 100 0 n#35 junction 1376 1088 1472 1088 agSeqCad.agSeqCad#40.OIDC
w 1400 1803 100 0 n#35 junction 1376 528 1376 1792 1472 1792 agSeqCad.agSeqCad#39.OIDC
w 1280 539 100 0 n#35 inhier.OIDC.P 80 528 2528 528 2528 1088 2624 1088 agSeqCad.agSeqCad#22.OIDC
w 840 1035 100 0 n#36 junction 832 1024 896 1024 agSeqCad.agSeqCad#42.OIWFS
w 840 1739 100 0 n#36 agSeqCad.agSeqCad#41.OIWFS 896 1728 832 1728 832 432 junction
w 1416 1739 100 0 n#36 agSeqCad.agSeqCad#39.OIWFS 1472 1728 1408 1728 1408 432 junction
w 1992 1035 100 0 n#36 junction 1984 1024 2048 1024 agSeqCad.agSeqCad#38.OIWFS
w 1992 1739 100 0 n#36 agSeqCad.agSeqCad#37.OIWFS 2048 1728 1984 1728 1984 432 junction
w 1296 443 100 0 n#36 inhier.OIWFS.P 80 432 2560 432 2560 1024 2624 1024 agSeqCad.agSeqCad#22.OIWFS
w 2568 1739 100 0 n#36 junction 2560 1024 2560 1728 2624 1728 agSeqCad.agSeqCad#20.OIWFS
w 1384 1867 100 0 n#34 agSeqCad.agSeqCad#39.PWFS2 1472 1856 1344 1856 1344 624 junction
w 1960 1163 100 0 n#34 junction 1920 1152 2048 1152 agSeqCad.agSeqCad#38.PWFS2
w 1960 1867 100 0 n#34 agSeqCad.agSeqCad#37.PWFS2 2048 1856 1920 1856 1920 624 junction
w 1264 635 100 0 n#34 inhier.PWFS2.P 80 624 2496 624 2496 1152 2624 1152 agSeqCad.agSeqCad#22.PWFS2
w 2536 1867 100 0 n#34 junction 2496 1152 2496 1856 2624 1856 agSeqCad.agSeqCad#20.PWFS2
w 1384 1163 100 0 n#34 junction 1344 1152 1472 1152 agSeqCad.agSeqCad#40.PWFS2
w 1368 1931 100 0 n#33 agSeqCad.agSeqCad#39.PWFS1 1472 1920 1312 1920 1312 720 junction
w 1944 1227 100 0 n#33 junction 1888 1216 2048 1216 agSeqCad.agSeqCad#38.PWFS1
w 1944 1931 100 0 n#33 agSeqCad.agSeqCad#37.PWFS1 2048 1920 1888 1920 1888 720 junction
w 1248 731 100 0 n#33 inhier.PWFS1.P 80 720 2464 720 2464 1216 2624 1216 agSeqCad.agSeqCad#22.PWFS1
w 2520 1931 100 0 n#33 junction 2464 1216 2464 1920 2624 1920 agSeqCad.agSeqCad#20.PWFS1
w 1368 1227 100 0 n#33 junction 1312 1216 1472 1216 agSeqCad.agSeqCad#40.PWFS1
w 1352 1995 100 0 n#32 agSeqCad.agSeqCad#39.CC 1472 1984 1280 1984 1280 816 junction
w 1928 1291 100 0 n#32 junction 1856 1280 2048 1280 agSeqCad.agSeqCad#38.CC
w 1928 1995 100 0 n#32 agSeqCad.agSeqCad#37.CC 2048 1984 1856 1984 1856 816 junction
w 1232 827 100 0 n#32 inhier.CC.P 80 816 2432 816 2432 1280 2624 1280 agSeqCad.agSeqCad#22.CC
w 2504 1995 100 0 n#32 junction 2432 1280 2432 1984 2624 1984 agSeqCad.agSeqCad#20.CC
w 1352 1291 100 0 n#32 junction 1280 1280 1472 1280 agSeqCad.agSeqCad#40.CC
s 2432 2336 100 0 $Id: agSeqCommands.sch,v 1.12 2007/05/18 22:29:20 pedro Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2672 80 100 0 Root schematic for A&G sequencer
s 1504 352 100 0 N.B. the reboot command is not connected
s 1504 320 100 0 to the OIWFS input. This means that this
s 1504 288 100 0 command will never be sent to on to an instrument
s 1504 256 100 0 by this sequencer.
s 896 352 100 0 The verify and endVerify commands are not
s 896 320 100 0 currently implemented in the CC, PWFS1
s 896 288 100 0 PWFS2 or HRWFS so the inputs are not 
s 896 256 100 0 connected.
s 2336 384 100 0 The mask bits are used to disable commands in particular
s 2336 352 100 0 OIWFS. The default is to assume all instruments implement
s 2336 320 100 0 the command so all bits are set and mask is set to 63
s 2336 288 100 0 If for example GMOS (which is at bit posn. 1) doesn't implement 
s 2336 256 100 0 a commnad then its bit is cleared leaving the mask set to 61.
[cell use]
use agSeqCad 920 968 100 0 agSeqCad#42
xform 0 1040 1264
p 976 960 100 0 1 seta:cad endVerify
p 976 928 100 0 1 setb:snam agSeqCADCommon
p 976 896 100 0 1 setc:mask 4093
p 1016 888 100 0 0 setd:gmsubcad endVerify
p 1096 808 100 0 0 sete:nirssubcad endVerify
p 1036 868 100 0 0 setf:nirisubcad endVerify
p 1076 828 100 0 0 setg:subcadname endVerify
p 1116 788 100 0 0 seth:f2subcad endVerify
p 1136 768 100 0 0 seti:nifssubcad endVerify
p 1156 748 100 0 0 setj:nicisubcad endVerify
use agSeqCad 920 1672 100 0 agSeqCad#41
xform 0 1040 1968
p 976 1664 100 0 1 seta:cad verify
p 976 1632 100 0 1 setb:snam agSeqCADCommon
p 976 1584 100 0 1 setc:mask 4093
p 1076 1532 100 0 0 setd:gmsubcad verify
p 1096 1512 100 0 0 sete:nirssubcad verify
p 1116 1492 100 0 0 setf:nirisubcad verify
p 1136 1472 100 0 0 setg:subcadname verify
p 1156 1452 100 0 0 seth:f2subcad verify
p 1176 1432 100 0 0 seti:nifssubcad verify
p 1196 1412 100 0 0 setj:nicisubcad verify
use agSeqCad 1496 1672 100 0 agSeqCad#39
xform 0 1616 1968
p 1552 1664 100 0 1 seta:cad test
p 1552 1632 100 0 1 setb:snam agSeqCADCommon
p 1552 1584 100 0 1 setc:mask 4095
p 1672 1512 100 0 0 setd:gmsubcad test
p 1692 1492 100 0 0 sete:nirssubcad test
p 1632 1552 100 0 0 setf:nirisubcad test
p 1712 1472 100 0 0 setg:subcadname test
p 1732 1452 100 0 0 seth:f2subcad test
p 1752 1432 100 0 0 seti:nifssubcad test
p 1772 1412 100 0 0 setj:nicisubcad test
use agSeqCad 2072 968 100 0 agSeqCad#38
xform 0 2192 1264
p 2128 960 100 0 1 seta:cad park
p 2128 928 100 0 1 setb:snam agSeqCADCommon
p 2128 896 100 0 1 setc:mask 4095
p 2168 888 100 0 0 setd:gmsubcad park
p 2188 868 100 0 0 sete:nirssubcad park
p 2208 848 100 0 0 setf:nirisubcad park
p 2128 896 100 0 0 setg:subcadname park
p 2228 828 100 0 0 seth:f2subcad park
p 2248 808 100 0 0 seti:nifssubcad park
p 2268 788 100 0 0 setj:nicisubcad park
use agSeqCad 2072 1672 100 0 agSeqCad#37
xform 0 2192 1968
p 2128 1664 100 0 1 seta:cad datum
p 2128 1632 100 0 1 setb:snam agSeqCADCommon
p 2128 1584 100 0 1 setc:mask 4095
p 2168 1592 100 0 0 setd:gmsubcad datum
p 2248 1512 100 0 0 sete:nirssubcad datum
p 2208 1552 100 0 0 setf:nirisubcad datum
p 2268 1492 100 0 0 setg:subcadname datum
p 2288 1472 100 0 0 seth:f2subcad datum
p 2308 1452 100 0 0 seti:nifssubcad datum
p 2328 1432 100 0 0 setj:nicisubcad datum
use agSeqCad 2648 968 100 0 agSeqCad#22
xform 0 2768 1264
p 2688 944 100 0 1 seta:cad debug
p 2688 912 100 0 1 setb:snam agSeqCADdebug
p 2688 864 100 0 1 setc:mask 4061
p 2728 872 100 0 0 setd:gmsubcad debug
p 2748 756 100 0 0 sete:nirssubcad debug
p 2688 816 100 0 0 setf:nirisubcad debug
p 2728 776 100 0 0 setg:subcadname debug
p 2768 736 100 0 0 seth:f2subcad debug
p 2788 716 100 0 0 seti:nifssubcad debug
p 2808 696 100 0 0 setj:nicisubcad debug
use agSeqCad 2648 1672 100 0 agSeqCad#20
xform 0 2768 1968
p 2704 1664 100 0 1 seta:cad init
p 2704 1632 100 0 1 setb:snam agSeqCADCommon
p 2704 1584 100 0 1 setc:mask 4095
p 2744 1592 100 0 0 setd:gmsubcad init
p 2824 1512 100 0 0 sete:nirssubcad init
p 2784 1552 100 0 0 setf:nirisubcad init
p 2844 1492 100 0 0 setg:subcadname init
p 2864 1472 100 0 0 seth:f2subcad init
p 2884 1452 100 0 0 seti:nifssubcad init
p 2904 1432 100 0 0 setj:nicisubcad init
use agSeqCad 1496 968 100 0 agSeqCad#40
xform 0 1616 1264
p 1552 960 100 0 1 seta:cad reboot
p 1552 928 100 0 1 setb:snam agSeqCADCommon
p 1552 896 100 0 1 setc:mask 4061
p 1592 888 100 0 0 setd:gmsubcad reboot
p 1612 868 100 0 0 sete:nirssubcad reboot
p 1632 848 100 0 0 setf:nirisubcad reboot
p 1672 808 100 0 0 setg:subcadname reboot
p 1692 788 100 0 0 seth:f2subcad reboot
p 1712 768 100 0 0 seti:nifssubcad reboot
p 1732 748 100 0 0 setj:nicisubcad reboot
use inhier 64 391 100 0 OIWFS
xform 0 80 432
use inhier 64 775 100 0 CC
xform 0 80 816
use inhier 64 679 100 0 PWFS1
xform 0 80 720
use inhier 64 583 100 0 PWFS2
xform 0 80 624
use inhier 64 487 100 0 OIDC
xform 0 80 528
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
