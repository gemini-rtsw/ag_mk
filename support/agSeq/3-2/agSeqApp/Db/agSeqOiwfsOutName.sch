[schematic2]
uniq 15
[tools]
[detail]
w 194 1931 100 0 n#1 hwin.hwin#134.in 160 1984 192 1984 192 1920 256 1920 ecalcs.calcSel.INPA
w 2386 1259 100 0 n#2 estringouts.ao.OUT 2336 1248 2496 1248 junction
w 2386 1515 100 0 n#2 estringouts.wfs.OUT 2336 1504 2496 1504 junction
w 2386 1771 100 0 n#2 estringouts.undefined.OUT 2336 1760 2496 1760 junction
w 2386 2003 100 0 n#2 estringouts.estringouts#123.OUT 2336 1992 2496 1992 2496 896 2608 896 esirs.esirs#132.SLNK
w 1538 2019 100 0 n#3 efanouts.fan1.LNK1 976 1728 1056 1728 1056 2008 2080 2008 estringouts.estringouts#123.SLNK
w 350 1355 100 0 n#4 ecalcs.calcSel.FLNK 544 1760 600 1760 600 1344 160 1344 160 1200 256 1200 embbis.prOutput.SLNK
w 562 1227 100 0 n#5 embbis.prOutput.FLNK 512 1216 672 1216 672 1648 736 1648 efanouts.fan1.SLNK
w 178 1899 100 0 n#6 hwin.hwin#121.in 160 1888 256 1888 ecalcs.calcSel.INPB
w 1874 939 100 0 n#7 efanouts.fan2.LNK3 1824 928 1984 928 1984 1264 2080 1264 estringouts.ao.SLNK
w 1858 971 100 0 n#8 efanouts.fan2.LNK2 1824 960 1952 960 1952 1520 2080 1520 estringouts.wfs.SLNK
w 1970 1787 100 0 n#9 efanouts.fan2.LNK1 1824 992 1920 992 1920 1776 2080 1776 estringouts.undefined.SLNK
w 1450 1035 100 0 n#10 ecalcs.calcInc.FLNK 1440 1024 1520 1024 1520 912 1584 912 efanouts.fan2.SLNK
w 1506 1003 100 0 n#11 ecalcs.calcInc.VAL 1440 992 1632 992 efanouts.fan2.SELL
w 1074 811 100 0 n#12 efanouts.fan1.LNK2 976 1696 1056 1696 1056 800 1152 800 ecalcs.calcInc.SLNK
w 802 1195 100 0 n#13 embbis.prOutput.VAL 512 1184 1152 1184 ecalcs.calcInc.INPA
w 634 1739 100 0 n#14 ecalcs.calcSel.VAL 544 1728 784 1728 efanouts.fan1.SELL
s 2432 2336 100 0 $Id: agSeqOiwfsOutName.sch,v 1.2 2007/05/18 22:29:23 pedro Exp $
s 2720 80 100 0 Generate OIWFS name
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use hwin -32 1847 100 0 hwin#121
xform 0 64 1888
p -32 1920 100 0 -1 val(in):$(ag)oiwfsDisabled
use hwin -32 1943 100 0 hwin#134
xform 0 64 1984
p -32 2024 100 0 -1 val(in):$(ag)oiwfsdcLoaded
use esirs 2608 807 100 0 esirs#132
xform 0 2816 960
p 2736 1120 100 0 -1 DESC:Current Pixel Router output
p 2544 544 100 0 0 FDSC:Name of selected PR output channel
p 2744 928 100 0 1 FTVL:STRING
p 2752 784 100 1024 -1 name:$(top)
use estringouts 2080 1935 100 0 estringouts#123
xform 0 2208 2008
p 2016 1974 100 0 0 VAL:
p 1864 2040 100 0 -1 def(DOL):$(ag):norecord
p 2192 1928 100 1024 -1 name:$(top)blank
p 2080 2040 75 1280 -1 palrm(DOL):MS
p 2368 1992 75 768 -1 palrm(OUT):MS
p 2336 1992 75 768 -1 pproc(OUT):PP
use estringouts 2080 1191 100 0 ao
xform 0 2208 1264
p 2107 1304 100 0 0 DESC:OIWFS NIRI
p 2016 1070 100 0 0 OMSL:closed_loop
p 2016 1230 100 0 0 VAL:
p 1760 1280 100 0 -1 def(DOL):$(top)prOutput.TWST
p 2336 1248 75 768 -1 pproc(OUT):PP
use estringouts 2080 1447 100 0 wfs
xform 0 2208 1520
p 2107 1560 100 0 0 DESC:OIWFS GMOS
p 2016 1326 100 0 0 OMSL:closed_loop
p 2016 1486 100 0 0 VAL:
p 1760 1536 100 0 -1 def(DOL):$(top)prOutput.ONST
p 2336 1504 75 768 -1 pproc(OUT):PP
use estringouts 2080 1703 100 0 undefined
xform 0 2208 1776
p 2107 1816 100 0 0 DESC:OIWFS Undefined
p 2016 1582 100 0 0 OMSL:closed_loop
p 2016 1742 100 0 0 VAL:
p 1760 1792 100 0 -1 def(DOL):$(top)prOutput.ZRST
p 2336 1760 75 768 -1 pproc(OUT):PP
use ecalcs 1152 711 100 0 calcInc
xform 0 1296 976
p 1248 896 100 0 1 CALC:A+1
p 1168 1248 100 0 -1 DESC:Increment Pixel Roter output
use ecalcs 256 1447 100 0 calcSel
xform 0 400 1712
p 400 1488 100 0 1 CALC:A=0?1:(B=1?1:2)
p 240 1984 100 0 -1 DESC:Triggers appropriate link
p 400 1456 100 0 1 SCAN:1 second
use efanouts 1584 775 100 0 fan2
xform 0 1704 928
p 1664 1088 100 0 -1 DESC:Select PR output name
p 1440 894 100 0 0 SELM:Specified
use efanouts 736 1511 100 0 fan1
xform 0 856 1664
p 816 1824 100 0 0 DESC:
p 760 1816 100 0 1 SELM:Specified
p 1008 1664 75 1280 -1 pproc(LNK3):NPP
use embbis 256 1127 100 0 prOutput
xform 0 384 1200
p 304 1296 100 0 -1 DESC:Pixel router output
p 432 1008 100 0 1 ONST:WFS
p 320 1008 100 0 1 ONVL:1
p -32 1246 100 0 0 SCAN:Passive
p 432 960 100 0 1 TWST:AO
p 320 960 100 0 1 TWVL:2
p 432 1056 100 0 1 ZRST:Undefined
p 320 1056 100 0 1 ZRVL:0
p -16 1216 100 0 -1 def(INP):$(oiwfs)prmOutput
p 256 1232 75 1280 -1 palrm(INP):MS
[comments]
