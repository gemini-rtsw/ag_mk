[schematic2]
uniq 1
[tools]
[detail]
w 754 139 100 0 OIWFS agSeqOiwfsStatus.agSeqOiwfsStatus#36.OIWFS 896 128 672 128 672 608 junction
w 1810 619 100 0 OIWFS agSeqInPosition.agSeqInPosition#24.OIWFS 1952 608 1728 608 1728 1120 junction
w 1842 747 100 0 PWFS2 agSeqInPosition.agSeqInPosition#24.PWFS2 1952 736 1792 736 1792 1312 junction
w 1858 811 100 0 PWFS1 agSeqInPosition.agSeqInPosition#24.PWFS1 1952 800 1824 800 1824 1408 junction
w 1880 875 100 0 OIDC agSeqInPosition.agSeqInPosition#24.OIDC 1952 864 1856 864 1856 1504 junction
w 1908 939 100 0 CC agSeqInPosition.agSeqInPosition#24.CC 1952 928 1888 928 1888 1600 junction
w 754 619 100 0 OIWFS agSeqState.agSeqState#23.OIWFS 896 608 672 608 672 1120 junction
w 786 747 100 0 PWFS2 agSeqState.agSeqState#23.PWFS2 896 736 736 736 736 1312 junction
w 802 811 100 0 PWFS1 agSeqState.agSeqState#23.PWFS1 896 800 768 800 768 1408 junction
w 824 875 100 0 OIDC agSeqState.agSeqState#23.OIDC 896 864 800 864 800 1504 junction
w 852 939 100 0 CC agSeqState.agSeqState#23.CC 896 928 832 928 832 1600 junction
w 1176 1611 100 0 CC inhier.CC.P 128 1600 2272 1600 2272 2048 2496 2048 agSeqCarCombine.agSeqCarCombine#8.CC
w 1428 2059 100 0 CC agSeqHealth.agSeqHealth#5.CC 1568 2048 1312 2048 1312 1600 junction
w 516 2059 100 0 CC agSeqPresent.agSeqPresent#2.CC 640 2048 416 2048 416 1600 junction
w 1192 1515 100 0 OIDC inhier.OIDC.P 128 1504 2304 1504 2304 1984 2496 1984 agSeqCarCombine.agSeqCarCombine#8.OIDC
w 1432 1995 100 0 OIDC agSeqHealth.agSeqHealth#5.OIDC 1568 1984 1344 1984 1344 1504 junction
w 520 1995 100 0 OIDC agSeqPresent.agSeqPresent#2.OIDC 640 1984 448 1984 448 1504 junction
w 1208 1419 100 0 PWFS1 inhier.PWFS1.P 128 1408 2336 1408 2336 1920 2496 1920 agSeqCarCombine.agSeqCarCombine#8.PWFS1
w 1442 1931 100 0 PWFS1 agSeqHealth.agSeqHealth#5.PWFS1 1568 1920 1376 1920 1376 1408 junction
w 530 1931 100 0 PWFS1 agSeqPresent.agSeqPresent#2.PWFS1 640 1920 480 1920 480 1408 junction
w 1224 1323 100 0 PWFS2 inhier.PWFS2.P 128 1312 2368 1312 2368 1856 2496 1856 agSeqCarCombine.agSeqCarCombine#8.PWFS2
w 1458 1867 100 0 PWFS2 agSeqHealth.agSeqHealth#5.PWFS2 1568 1856 1408 1856 1408 1312 junction
w 546 1867 100 0 PWFS2 agSeqPresent.agSeqPresent#2.PWFS2 640 1856 512 1856 512 1312 junction
w 784 1221 100 0 HRWFS inhier.HRWFS.P 128 1216 1440 1216 1440 1792 1568 1792 agSeqHealth.agSeqHealth#5.HRWFS
w 1256 1131 100 0 OIWFS inhier.OIWFS.P 128 1120 2432 1120 2432 1728 2496 1728 agSeqCarCombine.agSeqCarCombine#8.OIWFS
w 1490 1739 100 0 OIWFS agSeqHealth.agSeqHealth#5.OIWFS 1568 1728 1472 1728 1472 1120 junction
w 578 1739 100 0 OIWFS agSeqPresent.agSeqPresent#2.OIWFS 640 1728 576 1728 576 1120 junction
s 2672 80 100 0 Root schematic for A&G sequencer
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqStatus.sch,v 1.6 2013/01/31 18:42:21 pedro Exp $
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use inhier 112 1175 100 0 HRWFS
xform 0 128 1216
use inhier 112 1271 100 0 PWFS2
xform 0 128 1312
use inhier 112 1367 100 0 PWFS1
xform 0 128 1408
use inhier 112 1463 100 0 OIDC
xform 0 128 1504
use inhier 112 1559 100 0 CC
xform 0 128 1600
use inhier 112 1079 100 0 OIWFS
xform 0 128 1120
use agSeqOiwfsStatus 896 71 100 0 agSeqOiwfsStatus#36
xform 0 1120 272
use agSeqInPosition 1904 615 100 0 agSeqInPosition#24
xform 0 2176 784
p 2016 544 100 0 1 seta:top $(top)inPos:
use agSeqState 872 616 100 0 agSeqState#23
xform 0 1120 784
p 976 544 100 0 1 seta:top $(top)state:
use agSeqCarCombine 2584 1632 100 0 agSeqCarCombine#8
xform 0 2720 1904
p 2576 1664 100 0 1 seta:top $(top)car:
use agSeqHealth 1560 1736 100 0 agSeqHealth#5
xform 0 1840 1904
p 1632 1664 100 0 1 seta:top $(top)hlth:
use agSeqPresent 616 1736 100 0 agSeqPresent#2
xform 0 864 1904
[comments]
