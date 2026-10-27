[schematic2]
uniq 104
[tools]
[detail]
w 1410 91 100 0 n#103 hwin.hwin#100.in 1152 80 1728 80 1728 1440 1824 1440 egenSubD.transform.INPK
w 1394 235 100 0 n#102 hwin.hwin#84.in 1152 224 1696 224 1696 1472 1824 1472 egenSubD.transform.INPJ
w 1378 411 100 0 n#101 hwin.hwin#79.in 1152 400 1664 400 1664 1504 1824 1504 egenSubD.transform.INPI
w 1144 971 100 0 n#99 eaos.zzero.VAL 544 800 704 800 704 960 1632 960 1632 1536 1824 1536 egenSubD.transform.INPH
w 1336 811 100 0 n#98 eaos.zscale.VAL 1152 800 1568 800 1568 1568 1824 1568 egenSubD.transform.INPG
w 1080 1355 100 0 n#97 eaos.yzero.VAL 544 1184 704 1184 704 1344 1504 1344 1504 1600 1824 1600 egenSubD.transform.INPF
w 1608 1643 100 0 n#96 eaos.xzero.VAL 1152 1184 1440 1184 1440 1632 1824 1632 egenSubD.transform.INPE
w 1544 1771 100 0 n#94 eaos.orient.VAL 1152 1856 1312 1856 1312 1760 1824 1760 egenSubD.transform.INPA
w 1016 1419 100 0 n#93 eaos.yscale.VAL 544 1536 704 1536 704 1408 1376 1408 1376 1664 1824 1664 egenSubD.transform.INPD
w 1544 1707 100 0 n#92 eaos.xscale.VAL 1152 1536 1312 1536 1312 1696 1824 1696 egenSubD.transform.INPC
w 1240 1739 100 0 n#91 eaos.nonperp.VAL 544 1856 704 1856 704 1728 1824 1728 egenSubD.transform.INPB
w 2280 1035 100 0 n#83 egenSubD.transform.FLNK 2112 1024 2496 1024 outhier.FLNK.p
w 1152 1067 100 0 n#82 inhier.SLNK.P 528 1056 1824 1056 egenSubD.transform.SLNK
w 2424 1707 100 0 n#70 egenSubD.transform.VALB 2112 1696 2784 1696 outhier.c#69.p
w 2424 1771 100 0 n#68 egenSubD.transform.VALA 2112 1760 2784 1760 outhier.c#67.p
s 1056 2240 200 0 This schematic provides a linear transform
s 2432 2336 100 0 $Id: agSeqOiwfsTransform.sch,v 1.4 2002/11/25 00:43:52 cjm Exp $
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2672 80 100 0 OIWFS specific data
s 1216 2144 200 0 between OIWFS and TCS coordinates
s 2528 1536 100 0 VALA contains the 6 coeffs. of the
s 2528 1504 100 0 affine transformation from OIWFS to TCS coords
s 2528 1472 100 0 VALB contains the inverse transformation.
[cell use]
use hwin 960 39 100 0 hwin#100
xform 0 1056 80
p 963 72 100 0 -1 val(in):$(aoDeployed)
use egenSubD 1824 967 100 0 transform
xform 0 1968 1392
p 1728 1824 100 0 -1 DESC:Store coeffs of OIWFS-TCS transf.
p 1601 517 100 0 0 FTI:LONG
p 1601 485 100 0 0 FTJ:LONG
p 1601 741 100 0 0 FTK:LONG
p 1952 1760 100 0 1 NOVA:6
p 1952 1696 100 0 1 NOVB:6
p 1536 1342 100 0 0 SNAM:$(snam)
use hwin 960 183 100 0 hwin#84
xform 0 1056 224
p 963 216 100 0 -1 val(in):$(oiwfs)
use hwin 960 359 100 0 hwin#79
xform 0 1056 400
p 963 392 100 0 -1 val(in):$(port)
use outhier 2752 1719 100 0 c#67
xform 0 2768 1760
use outhier 2752 1655 100 0 c#69
xform 0 2768 1696
use outhier 2464 983 100 0 FLNK
xform 0 2480 1024
use inhier 512 1015 100 0 SLNK
xform 0 528 1056
use eaos 896 1767 100 0 orient
xform 0 1024 1856
p 832 1952 100 0 -1 DESC:Relative orientation of OIWFs and TCS
p 640 1614 100 0 0 DRVH:360.0
p 640 1582 100 0 0 DRVL:-360.0
p 864 1582 100 0 0 EGU:degs
p 640 1678 100 0 0 EGUF:360.0
p 640 1646 100 0 0 EGUL:-360.0
p 864 1966 100 0 0 HOPR:360.0
p 640 1422 100 0 0 IVOA:Set output to IVOV
p 864 1934 100 0 0 LOPR:-360.0
p 640 1710 100 0 0 PREC:2
use eaos 288 1767 100 0 nonperp
xform 0 416 1856
p 224 1952 100 0 -1 DESC:Relative nonperp of OIWFs and TCS
p 32 1614 100 0 0 DRVH:360.0
p 32 1582 100 0 0 DRVL:-360.0
p 256 1582 100 0 0 EGU:degs
p 32 1678 100 0 0 EGUF:360.0
p 32 1646 100 0 0 EGUL:-360.0
p 256 1966 100 0 0 HOPR:360.0
p 32 1422 100 0 0 IVOA:Set output to IVOV
p 256 1934 100 0 0 LOPR:-360.0
p 32 1710 100 0 0 PREC:2
use eaos 896 1447 100 0 xscale
xform 0 1024 1536
p 896 1632 100 0 -1 DESC:Scale factor for X axis
p 864 1262 100 0 0 EGU:none
p 640 1102 100 0 0 IVOA:Set output to IVOV
p 640 1070 100 0 0 IVOV:1.0
p 640 1390 100 0 0 PREC:3
use eaos 288 1447 100 0 yscale
xform 0 416 1536
p 288 1632 100 0 -1 DESC:Scale factor for Y axis
p 256 1262 100 0 0 EGU:none
p 32 1102 100 0 0 IVOA:Set output to IVOV
p 32 1070 100 0 0 IVOV:1.0
p 32 1390 100 0 0 PREC:3
use eaos 896 1095 100 0 xzero
xform 0 1024 1184
p 896 1280 100 0 -1 DESC:Zero point for X axis
p 864 910 100 0 0 EGU:unknown
p 640 750 100 0 0 IVOA:Set output to IVOV
p 640 718 100 0 0 IVOV:0.0
p 640 1038 100 0 0 PREC:3
use eaos 288 1095 100 0 yzero
xform 0 416 1184
p 288 1280 100 0 -1 DESC:Zero point for Y axis
p 256 910 100 0 0 EGU:unknown
p 32 750 100 0 0 IVOA:Set output to IVOV
p 32 718 100 0 0 IVOV:0.0
p 32 1038 100 0 0 PREC:3
use eaos 896 711 100 0 zscale
xform 0 1024 800
p 896 896 100 0 -1 DESC:Scale factor for Z axis
p 864 526 100 0 0 EGU:none
p 640 366 100 0 0 IVOA:Set output to IVOV
p 640 334 100 0 0 IVOV:1.0
p 640 654 100 0 0 PREC:3
use eaos 288 711 100 0 zzero
xform 0 416 800
p 288 896 100 0 -1 DESC:Zero point for Z axis
p 256 526 100 0 0 EGU:mm
p 32 366 100 0 0 IVOA:Set output to IVOV
p 32 334 100 0 0 IVOV:0.0
p 32 654 100 0 0 PREC:3
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
