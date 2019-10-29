[schematic2]
uniq 129
[tools]
[detail]
w 1666 1486 100 0 n#127 eseqs.eseqs#109.LNK2 1536 1344 1664 1344 1664 1568 1728 1568 egenSub.egenSub#120.SLNK
w 2098 2178 100 0 n#125 egenSub.egenSub#120.OUTB 2016 2176 2240 2176 hwout.hwout#124.outp
w 2098 2242 100 0 n#123 egenSub.egenSub#120.OUTA 2016 2240 2240 2240 hwout.hwout#122.outp
w 1130 1842 100 0 n#121 ecad2.ecad2#6.VALA 752 1840 1568 1840 1568 2240 1728 2240 egenSub.egenSub#120.INPA
w 1618 1378 100 0 n#116 eseqs.eseqs#109.LNK1 1536 1376 1760 1376 hwout.hwout#115.outp
w 866 1334 100 0 n#112 ecad2.ecad2#6.STLK 752 1552 864 1552 864 1056 1216 1056 eseqs.eseqs#109.SLNK
w 1122 1378 100 0 n#111 hwin.hwin#110.in 1088 1376 1216 1376 eseqs.eseqs#109.DOL1
w 898 1960 100 0 n#72 ecad2.ecad2#6.FLNK 752 1680 896 1680 896 2192 928 2192 engAck.engAck#59.SLNK
w 834 2168 100 0 n#71 ecad2.ecad2#6.VAL 752 2032 832 2032 832 2256 928 2256 engAck.engAck#59.INP
s 2560 1440 100 0 (instead of ASCII strings)
s 2096 1440 100 0 binary data read from pointer NULL up.
s 2096 1472 100 0 It can save 500kB not to call init. The written file will then contain
s 2096 1504 100 0 normally, INAM would be "$(command)Proc" (as now INAMsic)
s 2720 96 200 0 TEST COMMAND
s 2784 176 100 0 MCS Level 3
s 2480 144 100 0 Andy Foster
[cell use]
use esirs 2504 1640 100 0 esirs#128
xform 0 2688 1792
p 2640 1726 100 0 1 FTVL:LONG
p 2592 1632 100 1024 -1 name:$(top)LANperfL
use hwout 2264 2136 100 0 hwout#124
xform 0 2336 2176
p 2288 2126 100 0 -1 val(outp):$(top)logDataC.IVAL .PP
use hwout 2264 2200 100 0 hwout#122
xform 0 2336 2240
p 2304 2270 100 0 -1 val(outp):$(top)LANperfL .PP
use hwout 1784 1336 100 0 hwout#115
xform 0 1856 1376
p 1824 1406 100 0 -1 val(outp):$(top)logDataC.IVAL .PP
use egenSub 1752 1480 100 0 egenSub#120
xform 0 1872 1904
p 2128 1774 100 0 0 EVNT:0
p 1824 2238 100 0 1 FTA:STRING
p 1824 2206 100 0 0 FTB:DOUBLE
p 1824 2158 100 0 1 FTVA:LONG
p 1824 2126 100 0 1 FTVB:LONG
p 1824 2080 100 0 1 FTVC:LONG
p 1824 2048 100 0 1 FTVD:LONG
p 1824 2016 100 0 1 FTVE:LONG
p 1984 1440 100 0 1 INAM:
p 2096 1552 100 0 1 INAMsic:$(command)MemInit
p 2128 1806 100 0 0 SCAN:Passive
p 1712 1440 100 0 1 SNAM:$(command)Proc
p 1840 1472 100 1024 -1 name:$(top)$(command)genSub
p 2016 2250 75 0 -1 pproc(OUTA):NPP
p 2016 2186 75 0 -1 pproc(OUTB):NPP
use hwin 920 1336 100 0 hwin#110
xform 0 992 1376
p 899 1368 100 0 -1 val(in):$(BUSY)
use eseqs 1240 968 100 0 eseqs#109
xform 0 1376 1216
p 1328 1422 100 0 1 DLY2:0.1
p 1328 960 100 1024 -1 name:$(top)$(command)Seq
p 1552 1376 75 1024 -1 pproc(LNK1):NPP
p 1552 1344 75 1024 -1 pproc(LNK2):PP
use engAck 952 2056 100 0 engAck#59
xform 0 1120 2192
use ecad2 456 1464 100 0 ecad2#6
xform 0 592 1776
p 544 1950 100 0 1 FTVA:STRING
p 528 1918 100 0 0 FTVB:STRING
p 496 2094 100 0 1 SNAM:$(command)CAD
p 544 1456 100 1024 -1 name:$(top)$(command)
p 768 1808 75 1024 -1 pproc(OUTA):NPP
use bc200tr -128 -104 -100 0 frame
xform 0 1552 1200
[comments]
