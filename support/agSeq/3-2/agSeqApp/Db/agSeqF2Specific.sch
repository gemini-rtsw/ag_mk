[schematic2]
uniq 74
[tools]
[detail]
w 1016 1355 100 0 n#73 agSeqOiwfsTransform.agSeqOiwfsTransform#57.FLNK 1792 1664 1888 1664 1888 1344 192 1344 192 640 272 640 agSeqOiwfsTransform.agSeqOiwfsTransform#69.SLNK
w 2112 1131 100 0 n#72 inhier.AOSTATE.P 1936 1120 2336 1120 egenSub.coeffs.INPC
w 1288 651 100 0 n#68 agSeqOiwfsTransform.agSeqOiwfsTransform#71.FLNK 1216 640 1408 640 agSeqOiwfsTransform.agSeqOiwfsTransform#70.SLNK
w 720 651 100 0 n#67 agSeqOiwfsTransform.agSeqOiwfsTransform#69.FLNK 656 640 832 640 agSeqOiwfsTransform.agSeqOiwfsTransform#71.SLNK
w 2776 715 100 0 n#65 egenSub.coeffs.VALJ 2624 704 2976 704 outhier.COEFFS.p
w 2144 1259 100 0 n#64 hwin.hwin#66.in 2000 1248 2336 1248 egenSub.coeffs.INPA
w 2144 1195 100 0 n#63 inhier.PORT.P 2000 1184 2336 1184 egenSub.coeffs.INPB
w 1288 1675 100 0 n#60 agSeqOiwfsTransform.agSeqOiwfsTransform#58.FLNK 1216 1664 1408 1664 agSeqOiwfsTransform.agSeqOiwfsTransform#57.SLNK
w 720 1675 100 0 n#59 agSeqOiwfsTransform.agSeqOiwfsTransform#56.FLNK 656 1664 832 1664 agSeqOiwfsTransform.agSeqOiwfsTransform#58.SLNK
s 2704 80 100 0 Flamingos-2 specific data
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
s 2432 2336 100 0 $Id: agSeqF2Specific.sch,v 1.1 2005/06/20 20:54:37 anunez Exp $
s 832 2240 200 0 This schematic acts as a container for Flamingos-2 specific data
[cell use]
use inhier 1984 1143 100 0 PORT
xform 0 2000 1184
use inhier 1920 1079 100 0 AOSTATE
xform 0 1936 1120
use agSeqOiwfsTransform 848 551 100 0 agSeqOiwfsTransform#71
xform 0 1024 816
p 848 544 100 0 1 seta:top $(top)3:ao:
p 848 512 100 0 1 setb:snam agSeqSetOiwfsTransform
p 848 480 100 0 1 setc:port 3
p 848 448 100 0 1 setd:oiwfs $(F2)
p 848 416 100 0 1 sete:aoDeployed 1
use agSeqOiwfsTransform 1424 551 100 0 agSeqOiwfsTransform#70
xform 0 1600 816
p 1424 544 100 0 1 seta:top $(top)5:ao:
p 1424 512 100 0 1 setb:snam agSeqSetOiwfsTransform
p 1424 480 100 0 1 setc:port 5
p 1424 432 100 0 1 setd:oiwfs $(F2)
p 1424 400 100 0 1 sete:aoDeployed 1
use agSeqOiwfsTransform 288 551 100 0 agSeqOiwfsTransform#69
xform 0 464 816
p 288 544 100 0 1 seta:top $(top)1:ao:
p 288 512 100 0 1 setb:snam agSeqSetOiwfsTransform
p 288 480 100 0 1 setc:port 1
p 288 448 100 0 1 setd:oiwfs $(F2)
p 288 416 100 0 1 sete:aoDeployed 1
use agSeqOiwfsTransform 848 1575 100 0 agSeqOiwfsTransform#58
xform 0 1024 1840
p 848 1568 100 0 1 seta:top $(top)3:
p 848 1536 100 0 1 setb:snam agSeqSetOiwfsTransform
p 848 1504 100 0 1 setc:port 3
p 848 1472 100 0 1 setd:oiwfs $(F2)
p 848 1440 100 0 1 sete:aoDeployed 0
use agSeqOiwfsTransform 1424 1575 100 0 agSeqOiwfsTransform#57
xform 0 1600 1840
p 1424 1568 100 0 1 seta:top $(top)5:
p 1424 1536 100 0 1 setb:snam agSeqSetOiwfsTransform
p 1424 1504 100 0 1 setc:port 5
p 1424 1456 100 0 1 setd:oiwfs $(F2)
p 1424 1424 100 0 1 sete:aoDeployed 0
use agSeqOiwfsTransform 288 1575 100 0 agSeqOiwfsTransform#56
xform 0 464 1840
p 288 1568 100 0 1 seta:top $(top)1:
p 288 1536 100 0 1 setb:snam agSeqSetOiwfsTransform
p 288 1504 100 0 1 setc:port 1
p 288 1472 100 0 1 setd:oiwfs $(F2)
p 288 1440 100 0 1 sete:aoDeployed 0
use hwin 1808 1207 100 0 hwin#66
xform 0 1904 1248
p 1811 1240 100 0 -1 val(in):$(F2)
use outhier 2944 663 100 0 COEFFS
xform 0 2960 704
use egenSub 2336 487 100 0 coeffs
xform 0 2480 912
p 2304 1344 100 0 -1 DESC:Generate current transform coeffs
p 2113 261 100 0 0 FTA:LONG
p 2113 261 100 0 0 FTB:LONG
p 2113 229 100 0 0 FTC:LONG
p 2113 -379 100 0 0 NOVJ:6
p 2400 384 100 0 1 SCAN:1 second
p 2400 432 100 0 1 SNAM:agSeqOiwfsPort
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
