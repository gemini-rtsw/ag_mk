[schematic2]
uniq 49
[tools]
[detail]
w 1288 475 100 0 n#48 efanouts.FanNotLoad.LNK1 1232 464 1392 464 1392 160 1488 160 elongouts.EnableVal.SLNK
w 1272 443 100 0 n#47 efanouts.FanNotLoad.LNK2 1232 432 1360 432 1360 544 1488 544 ecalcs.CalcDisv.SLNK
w 1144 907 100 0 n#46 inhier.c#45.P 848 896 1488 896 ecalcs.CalcDisv.INPB
w 2808 514 100 0 n#44 elongouts.Disabled.VAL 2656 512 3008 512 outhier.DISV.p
w 1122 1336 100 0 n#42 eao.Present.U0 928 1760 1120 1760 1120 864 1488 864 ecalcs.CalcDisv.INPC
w 1032 1890 100 0 n#36 eao.Present.VAL 928 1888 1184 1888 1184 2080 1328 2080 eseqs.WaitPresent.DOL1
w 1760 1154 100 0 n#41 eaos.OldPresent.VAL 2144 2080 2304 2080 2304 1152 1264 1152 1264 928 1488 928 ecalcs.CalcDisv.INPA
w 2274 648 100 0 n#40 elongouts.CalcOut.OUT 2144 736 2272 736 2272 512 2400 512 elongouts.Disabled.SLNK
w 1984 130 100 0 n#40 elongouts.EnableVal.OUT 1744 128 2272 128 2272 512 junction
w 1744 2082 100 0 n#37 eseqs.WaitPresent.LNK1 1648 2080 1888 2080 eaos.OldPresent.SLNK
w 1016 1986 100 0 n#35 eao.Present.FLNK 928 1984 1152 1984 1152 1760 1328 1760 eseqs.WaitPresent.SLNK
w 128 1794 100 0 n#34 inhier.c#21.P 16 1792 288 1792 eao.Present.DOL
w 1824 802 100 0 n#19 ecalcs.CalcDisv.VAL 1776 736 1808 736 1808 800 1888 800 elongouts.CalcOut.DOL
w 1808 770 100 0 n#18 ecalcs.CalcDisv.FLNK 1776 768 1888 768 elongouts.CalcOut.SLNK
w 1424 194 100 0 n#15 hwin.hwin#14.in 1408 192 1488 192 elongouts.EnableVal.DOL
w 952 466 100 0 n#10 ecalcs.IncNotLoad.VAL 816 352 912 352 912 464 1040 464 efanouts.FanNotLoad.SELL
w 886 386 100 0 n#9 ecalcs.IncNotLoad.FLNK 816 384 992 384 efanouts.FanNotLoad.SLNK
w 358 546 100 0 n#8 inhier.LOADED.P 224 544 528 544 ecalcs.IncNotLoad.INPA
s -32 2208 100 0 record for use by the TCS.
s -32 2240 100 0 It combines their "present" records into a single "present"
s -32 2272 100 0 Components Controller or WFS Processing system.
s -32 2304 100 0 This schematic handles the presence (or absence) of the 
s 2640 80 100 0 Generate disabel value for subsystem
s 2432 2336 100 0 $Id: agSeqSubsysPresent.sch,v 1.5 2001/09/25 10:43:21 ajf Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
[cell use]
use inhier 24 1752 100 0 c#21
xform 0 16 1792
use inhier 232 504 100 0 LOADED
xform 0 224 544
use inhier 832 855 100 0 c#45
xform 0 848 896
use outhier 3000 472 100 0 DISV
xform 0 2992 512
use elongouts 1912 680 100 0 CalcOut
xform 0 2016 768
p 1728 686 100 0 0 OMSL:closed_loop
p 2256 734 100 0 0 def(OUT):0.0
p 2144 736 75 768 -1 pproc(OUT):PP
use elongouts 1512 72 100 0 EnableVal
xform 0 1616 160
p 1328 78 100 0 0 OMSL:closed_loop
p 1856 126 100 0 0 def(OUT):0.0
p 1744 128 75 768 -1 pproc(OUT):PP
use elongouts 2424 424 100 0 Disabled
xform 0 2528 512
p 2368 606 100 0 -1 DESC:Indicates a disabled subsystem
use eao 312 1256 100 0 Present
xform 0 608 1712
p 416 1326 100 0 0 ADEL:0.000000000000000e+00
p 452 2042 100 0 1 DESC:Check alarm on \"present\"
p 640 1902 100 0 0 DISS:NO_ALARM
p 416 1550 100 0 0 DISV:1
p 416 1614 100 0 0 DRVH:0.0000000e+00
p 416 1582 100 0 0 DRVL:0.0000000e+00
p 640 1582 100 0 1 EGU:none
p 416 1678 100 0 0 EGUF:0.0000000e+00
p 416 1646 100 0 0 EGUL:0.0000000e+00
p 416 1902 100 0 0 EVNT:0
p 640 1742 100 0 0 HHSV:NO_ALARM
p 640 1806 100 0 0 HIGH:0.0000000e+00
p 640 1870 100 0 0 HIHI:0.0000000e+00
p 640 1966 100 0 0 HOPR:0.0000000e+00
p 640 1710 100 0 0 HSV:NO_ALARM
p 416 1358 100 0 0 HYST:0.000000000000000e+00
p 416 1422 100 0 0 IVOA:Continue normally
p 416 1390 100 0 0 IVOV:0.000000000000000e+00
p 640 1646 100 0 0 LLSV:NO_ALARM
p 640 1838 100 0 0 LOLO:0.0000000e+00
p 640 1934 100 0 0 LOPR:0.0000000e+00
p 640 1774 100 0 0 LOW:0.0000000e+00
p 640 1678 100 0 0 LSV:NO_ALARM
p 416 1838 100 0 1 OMSL:closed_loop
p 416 1774 100 0 0 OROC:0.0000000e+00
p 416 1934 100 0 0 PHAS:0
p 640 1614 100 0 0 PRIO:LOW
p 416 1966 100 0 1 SCAN:10 second
p 416 1486 100 0 0 SIML:0.000000000000000e+00
p 416 1454 100 0 0 SIMS:NO_ALARM
p 416 1518 100 0 0 SIOL:0.000000000000000e+00
p 48 1838 100 0 -1 def(DOL):$(present)
p 288 1792 75 1280 -1 palrm(DOL):MS
p 896 1760 100 1024 -1 username(U0):SEVR
use eaos 1912 1992 100 0 OldPresent
xform 0 2016 2080
p 1904 2190 100 0 -1 DESC:Old value of \"present\"
use eseqs 1352 1672 100 0 WaitPresent
xform 0 1488 1920
p 1440 1982 100 0 1 DLY1:9.9
p 1440 1950 100 0 0 DLY2:0.0
p 1744 2046 100 0 0 def(LNK2):0.0
p 1664 2080 75 1024 -1 pproc(LNK1):PP
p 1664 2048 75 1024 -1 pproc(LNK2):NPP
use ecalcs 1512 456 100 0 CalcDisv
xform 0 1632 720
p 1648 542 100 0 -1 CALC:(A=B)||(C=3)?1:0
p 992 878 100 0 0 def(INPA):0.0
p 880 912 100 0 -1 def(INPB):$(present)
use ecalcs 552 72 100 0 IncNotLoad
xform 0 672 336
p 640 286 100 0 1 CALC:A+1
p 560 606 100 0 -1 DESC:Increment NotLoaded flag
p 672 126 100 0 1 SCAN:1 second
use hwin 1240 152 100 0 hwin#14
xform 0 1312 192
p 1219 184 100 0 -1 val(in):0
use efanouts 1016 248 100 0 FanNotLoad
xform 0 1112 400
p 848 366 100 0 0 SELM:Specified
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
