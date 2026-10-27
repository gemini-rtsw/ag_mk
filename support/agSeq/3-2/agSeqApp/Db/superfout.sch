[schematic2]
uniq 8
[tools]
[detail]
w 1240 907 -100 0 FLNK efanouts.fan01.FLNK 976 832 1056 832 1056 896 1472 896 1472 336 1600 336 outhier.FLNK.p
w 1200 75 -100 0 FLNK efanouts.fan03.FLNK 976 64 1472 64 1472 336 junction
w 1240 523 -100 0 FLNK efanouts.fan02.FLNK 976 496 1056 496 1056 512 1472 512 junction
w 536 91 100 0 n#1 efanouts.fan00.LNK3 480 80 640 80 640 -48 736 -48 efanouts.fan03.SLNK
w 208 683 100 0 n#2 egenSub.selIdxGs.VALC 48 672 416 672 416 320 704 320 704 32 784 32 efanouts.fan03.SELL
w 1168 -197 -100 0 LNK18 efanouts.fan03.LNK6 976 -128 1056 -128 1056 -208 1328 -208 outhier.LNK18.p
w 1184 -133 -100 0 LNK17 efanouts.fan03.LNK5 976 -96 1088 -96 1088 -144 1328 -144 outhier.LNK17.p
w 1200 -69 -100 0 LNK16 efanouts.fan03.LNK4 976 -64 1120 -64 1120 -80 1328 -80 outhier.LNK16.p
w 1200 -5 -100 0 LNK15 efanouts.fan03.LNK3 976 -32 1120 -32 1120 -16 1328 -16 outhier.LNK15.p
w 1184 59 -100 0 LNK14 efanouts.fan03.LNK2 976 0 1088 0 1088 48 1328 48 outhier.LNK14.p
w 1168 123 -100 0 LNK13 efanouts.fan03.LNK1 976 32 1056 32 1056 112 1328 112 outhier.LNK13.p
w 536 123 100 0 n#3 efanouts.fan00.LNK2 480 112 640 112 640 384 736 384 efanouts.fan02.SLNK
w 520 155 100 0 n#4 efanouts.fan00.LNK1 480 144 608 144 608 720 736 720 efanouts.fan01.SLNK
w 120 75 100 0 n#5 egenSub.selIdxGs.FLNK 48 64 240 64 efanouts.fan00.SLNK
w 1168 187 -100 0 LNK12 efanouts.fan02.LNK6 976 304 1056 304 1056 176 1328 176 outhier.LNK12.p
w 1184 251 -100 0 LNK11 efanouts.fan02.LNK5 976 336 1088 336 1088 240 1328 240 outhier.LNK11.p
w 1192 315 -100 0 LNK10 efanouts.fan02.LNK4 976 368 1104 368 1104 304 1328 304 outhier.LNK10.p
w 1208 379 -100 0 LNK9 efanouts.fan02.LNK3 976 400 1136 400 1136 368 1328 368 outhier.LNK9.p
w 1128 443 -100 0 LNK8 efanouts.fan02.LNK2 976 432 1328 432 outhier.LNK8.p
w 1184 507 -100 0 LNK7 efanouts.fan02.LNK1 976 464 1088 464 1088 496 1328 496 outhier.LNK7.p
w 1184 571 -100 0 LNK6 efanouts.fan01.LNK6 976 640 1088 640 1088 560 1328 560 outhier.LNK6.p
w -400 107 -100 0 SLNK inhier.SLNK.P -512 96 -240 96 egenSub.selIdxGs.SLNK
w 1200 635 -100 0 LNK5 efanouts.fan01.LNK5 976 672 1120 672 1120 624 1328 624 outhier.LNK5.p
w 1040 715 -100 0 LNK4 efanouts.fan01.LNK4 976 704 1152 704 1152 688 1328 688 outhier.LNK4.p
w 1040 747 -100 0 LNK3 efanouts.fan01.LNK3 976 736 1152 736 1152 752 1328 752 outhier.LNK3.p
w 1200 827 -100 0 LNK2 efanouts.fan01.LNK2 976 768 1120 768 1120 816 1328 816 outhier.LNK2.p
w 1184 891 -100 0 LNK1 efanouts.fan01.LNK1 976 800 1088 800 1088 880 1328 880 outhier.LNK1.p
w 254 747 100 0 n#6 egenSub.selIdxGs.VALB 48 736 496 736 496 464 784 464 efanouts.fan02.SELL
w 398 811 100 0 n#7 egenSub.selIdxGs.VALA 48 800 784 800 efanouts.fan01.SELL
w -402 779 -100 0 A inhier.SELL.P -528 768 -240 768 egenSub.selIdxGs.INPA
s 1088 -384 100 0 Arturo Nunez
s 1072 -320 100 0 Observatories
s 1104 -288 100 0 Gemini
s 1392 -272 100 0 Super Fonout
s 1152 944 100 0 $Id: superfout.sch,v 1.3 2005/10/04 21:33:17 anunez Exp $
[cell use]
use bb200tr -720 -552 -100 0 frame
xform 0 560 272
use outhier 1296 -249 100 0 LNK18
xform 0 1312 -208
use outhier 1296 -185 100 0 LNK17
xform 0 1312 -144
use outhier 1296 -121 100 0 LNK16
xform 0 1312 -80
use outhier 1296 -57 100 0 LNK15
xform 0 1312 -16
use outhier 1296 7 100 0 LNK14
xform 0 1312 48
use outhier 1296 71 100 0 LNK13
xform 0 1312 112
use outhier 1296 135 100 0 LNK12
xform 0 1312 176
use outhier 1296 199 100 0 LNK11
xform 0 1312 240
use outhier 1296 263 100 0 LNK10
xform 0 1312 304
use outhier 1296 327 100 0 LNK9
xform 0 1312 368
use outhier 1296 391 100 0 LNK8
xform 0 1312 432
use outhier 1296 455 100 0 LNK7
xform 0 1312 496
use outhier 1296 519 100 0 LNK6
xform 0 1312 560
use outhier 1296 583 100 0 LNK5
xform 0 1312 624
use outhier 1296 647 100 0 LNK4
xform 0 1312 688
use outhier 1296 711 100 0 LNK3
xform 0 1312 752
use outhier 1296 775 100 0 LNK2
xform 0 1312 816
use outhier 1296 839 100 0 LNK1
xform 0 1312 880
use outhier 1568 295 100 0 FLNK
xform 0 1584 336
use efanouts 736 -185 100 0 fan03
xform 0 856 -32
p 720 -160 100 0 1 SELM:Specified
use efanouts 240 -73 100 0 fan00
xform 0 360 80
use efanouts 736 247 100 0 fan02
xform 0 856 400
p 720 272 100 0 1 SELM:Specified
use efanouts 736 583 100 0 fan01
xform 0 856 736
p 720 608 100 0 1 SELM:Specified
use inhier -528 55 100 0 SLNK
xform 0 -512 96
use inhier -544 727 100 0 SELL
xform 0 -528 768
use egenSub -240 7 100 0 selIdxGs
xform 0 -96 432
p -160 864 100 0 -1 DESC:Select Index
p -463 -219 100 0 0 FTA:LONG
p -463 -219 100 0 0 FTVA:LONG
p -463 -219 100 0 0 FTVB:LONG
p -463 -251 100 0 0 FTVC:LONG
p -463 -283 100 0 0 FTVD:LONG
p -463 -315 100 0 0 FTVE:LONG
p -463 -379 100 0 0 FTVF:LONG
p -463 -379 100 0 0 FTVG:LONG
p -463 -411 100 0 0 FTVH:LONG
p -463 -443 100 0 0 FTVI:LONG
p -463 -475 100 0 0 FTVJ:LONG
p -224 -32 100 0 1 SNAM:superFanoutSelIndex
p -528 414 100 0 1 INAM:agSeqGensubInit
[comments]
