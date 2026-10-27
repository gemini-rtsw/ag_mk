[schematic2]
uniq 82
[tools]
[detail]
w 1000 1291 100 0 n#81 agSeqOiwfsTransform.agSeqOiwfsTransform#57.FLNK 1792 1600 1888 1600 1888 1280 160 1280 160 480 272 480 agSeqOiwfsTransform.agSeqOiwfsTransform#80.SLNK
w 1288 491 100 0 n#77 agSeqOiwfsTransform.agSeqOiwfsTransform#78.FLNK 1216 480 1408 480 agSeqOiwfsTransform.agSeqOiwfsTransform#79.SLNK
w 720 491 100 0 n#76 agSeqOiwfsTransform.agSeqOiwfsTransform#80.FLNK 656 480 832 480 agSeqOiwfsTransform.agSeqOiwfsTransform#78.SLNK
w 2048 1083 100 0 n#70 inhier.AOSTATE.P 1808 1072 2336 1072 egenSub.coeffs.INPC
w 2144 1211 100 0 n#67 hwin.hwin#68.in 2000 1200 2336 1200 egenSub.coeffs.INPA
w 2776 667 100 0 n#66 egenSub.coeffs.VALJ 2624 656 2976 656 outhier.COEFFS.p
w 2144 1147 100 0 n#64 inhier.PORT.P 2000 1136 2336 1136 egenSub.coeffs.INPB
w 1288 1611 100 0 n#60 agSeqOiwfsTransform.agSeqOiwfsTransform#58.FLNK 1216 1600 1408 1600 agSeqOiwfsTransform.agSeqOiwfsTransform#57.SLNK
w 720 1611 100 0 n#59 agSeqOiwfsTransform.agSeqOiwfsTransform#56.FLNK 656 1600 832 1600 agSeqOiwfsTransform.agSeqOiwfsTransform#58.SLNK
s 2672 80 100 0 NIRI specific data
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
s 2432 2336 100 0 $Id: agSeqGmosSpecific.sch,v 1.4 2003/07/09 11:58:02 cjm Exp $
s 832 2240 200 0 This schematic acts as a container for GMOS specific data
[cell use]
use agSeqOiwfsTransform 848 1511 100 0 agSeqOiwfsTransform#58
xform 0 1024 1776
p 848 1504 100 0 1 seta:top $(top)3:
p 848 1472 100 0 1 setb:snam agSeqSetOiwfsTransform
p 848 1440 100 0 1 setc:port 3
p 848 1408 100 0 1 setd:oiwfs $(GMOS)
p 848 1376 100 0 1 sete:aoDeployed 0
use agSeqOiwfsTransform 1424 1511 100 0 agSeqOiwfsTransform#57
xform 0 1600 1776
p 1424 1504 100 0 1 seta:top $(top)5:
p 1424 1472 100 0 1 setb:snam agSeqSetOiwfsTransform
p 1424 1440 100 0 1 setc:port 5
p 1424 1408 100 0 1 setd:oiwfs $(GMOS)
p 1424 1360 100 0 1 sete:aoDeployed 0
use agSeqOiwfsTransform 288 1511 100 0 agSeqOiwfsTransform#56
xform 0 464 1776
p 288 1504 100 0 1 seta:top $(top)1:
p 288 1472 100 0 1 setb:snam agSeqSetOiwfsTransform
p 288 1440 100 0 1 setc:port 1
p 288 1408 100 0 1 setd:oiwfs $(GMOS)
p 288 1360 100 0 1 sete:aoDeployed 0
use agSeqOiwfsTransform 848 391 100 0 agSeqOiwfsTransform#78
xform 0 1024 656
p 848 384 100 0 1 seta:top $(top)3:ao:
p 848 352 100 0 1 setb:snam agSeqSetOiwfsTransform
p 848 320 100 0 1 setc:port 3
p 848 288 100 0 1 setd:oiwfs $(GMOS)
p 848 256 100 0 1 sete:aoDeployed 1
use agSeqOiwfsTransform 1424 391 100 0 agSeqOiwfsTransform#79
xform 0 1600 656
p 1424 384 100 0 1 seta:top $(top)5:ao:
p 1424 352 100 0 1 setb:snam agSeqSetOiwfsTransform
p 1424 320 100 0 1 setc:port 5
p 1424 288 100 0 1 setd:oiwfs $(GMOS)
p 1424 240 100 0 1 sete:aoDeployed 1
use agSeqOiwfsTransform 288 391 100 0 agSeqOiwfsTransform#80
xform 0 464 656
p 288 384 100 0 1 seta:top $(top)1:ao:
p 288 352 100 0 1 setb:snam agSeqSetOiwfsTransform
p 288 320 100 0 1 setc:port 1
p 288 288 100 0 1 setd:oiwfs $(GMOS)
p 288 240 100 0 1 sete:aoDeployed 1
use inhier 1984 1095 100 0 PORT
xform 0 2000 1136
use inhier 1792 1031 100 0 AOSTATE
xform 0 1808 1072
use hwin 1808 1159 100 0 hwin#68
xform 0 1904 1200
p 1811 1192 100 0 -1 val(in):$(GMOS)
use outhier 2944 615 100 0 COEFFS
xform 0 2960 656
use egenSub 2336 439 100 0 coeffs
xform 0 2480 864
p 2304 1296 100 0 -1 DESC:Generate current transform coeffs
p 2113 213 100 0 0 FTA:LONG
p 2113 213 100 0 0 FTB:LONG
p 2113 181 100 0 0 FTC:LONG
p 2464 640 100 0 1 NOVJ:6
p 2400 336 100 0 1 SCAN:1 second
p 2400 384 100 0 1 SNAM:agSeqOiwfsPort
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
