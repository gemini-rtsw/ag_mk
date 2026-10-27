[schematic2]
uniq 21
[tools]
[detail]
w 2130 1659 100 0 n#1 estringouts.nifsState.OUT 2080 1648 2240 1648 junction
w 2130 2619 100 0 n#1 estringouts.gmosState.OUT 2080 2608 2240 2608 junction
w 2130 2395 100 0 n#1 estringouts.nirsState.OUT 2080 2384 2240 2384 junction
w 2130 1883 100 0 n#1 estringouts.f2State.OUT 2080 1872 2240 1872 junction
w 2130 2171 100 0 n#1 estringouts.niriState.OUT 2080 2160 2240 2160 junction
w 3042 3019 100 0 n#1 estringouts.noneState.OUT 2080 2832 2240 2832 2240 3008 3904 3008 3904 2240 4320 2240 egenSub.combine.I
w 2130 1435 100 0 n#1 estringouts.niciState.OUT 2080 1424 2240 1424 2240 2832 junction
w 2690 2059 100 0 n#2 superfout.superfout#60.FLNK 1040 1824 1120 1824 1120 2048 4320 2048 egenSub.combine.SLNK
w 1538 1451 100 0 n#3 superfout.superfout#60.LNK7 1040 1600 1312 1600 1312 1440 1824 1440 estringouts.niciState.SLNK
w 1538 1675 100 0 n#4 superfout.superfout#60.LNK6 1040 1632 1312 1632 1312 1664 1824 1664 estringouts.nifsState.SLNK
w 1522 1899 100 0 n#5 superfout.superfout#60.LNK5 1040 1664 1280 1664 1280 1888 1824 1888 estringouts.f2State.SLNK
w 1506 2187 100 0 n#6 superfout.superfout#60.LNK4 1040 1696 1248 1696 1248 2176 1824 2176 estringouts.niriState.SLNK
w 1626 1483 -100 0 c inhier.c#99.P 1488 1472 1824 1472 estringouts.niciState.DOL
w 1496 2411 100 0 n#7 superfout.superfout#60.LNK3 1040 1728 1216 1728 1216 2400 1824 2400 estringouts.nirsState.SLNK
w 1480 2635 100 0 n#8 superfout.superfout#60.LNK2 1040 1760 1184 1760 1184 2624 1824 2624 estringouts.gmosState.SLNK
w 1464 2859 100 0 n#9 superfout.superfout#60.LNK1 1040 1792 1152 1792 1152 2848 1824 2848 estringouts.noneState.SLNK
w 1624 2443 -100 0 c estringouts.nirsState.DOL 1824 2432 1472 2432 inhier.c#34.P
w 1624 2667 -100 0 c inhier.c#32.P 1472 2656 1824 2656 estringouts.gmosState.DOL
w 1632 1707 -100 0 c inhier.c#74.P 1488 1696 1824 1696 estringouts.nifsState.DOL
w 1624 2219 -100 0 c inhier.c#36.P 1472 2208 1824 2208 estringouts.niriState.DOL
w 576 1643 100 0 n#10 ecalcs.incr.FLNK 576 1632 624 1632 624 1504 superfout.superfout#60.SLNK
w 568 1611 100 0 n#11 ecalcs.incr.VAL 576 1600 608 1600 608 1728 624 1728 superfout.superfout#60.SELL
w 1632 1931 -100 0 c inhier.c#57.P 1488 1920 1824 1920 estringouts.f2State.DOL
w 4128 2539 100 0 n#12 inhier.PWFS2.P 3984 2528 4320 2528 egenSub.combine.INPD
w 4128 2603 100 0 n#13 inhier.PWFS1.P 3984 2592 4320 2592 egenSub.combine.INPC
w 4128 2667 100 0 n#14 inhier.OIDC.P 3984 2656 4320 2656 egenSub.combine.INPB
w 4128 2731 100 0 n#15 inhier.CC.P 3984 2720 4320 2720 egenSub.combine.INPA
w 4128 2283 100 0 n#16 inhier.c#48.P 3984 2272 4320 2272 egenSub.combine.INPH
w 4128 2347 100 0 n#17 inhier.c#46.P 3984 2336 4320 2336 egenSub.combine.INPG
w 4128 2411 100 0 n#18 inhier.c#44.P 3984 2400 4320 2400 egenSub.combine.INPF
w 4128 2475 100 0 n#19 inhier.c#42.P 3984 2464 4320 2464 egenSub.combine.INPE
w 184 1803 100 0 n#20 inhier.OIWFS.P 128 1792 288 1792 ecalcs.incr.INPA
w 4760 2667 -100 0 c egenSub.combine.OUTB 4608 2656 4960 2656 outhier.c#14.p
w 4760 2731 -100 0 c egenSub.combine.OUTA 4608 2720 4960 2720 outhier.c#13.p
s 4256 288 100 0 Generate state record
s 3600 176 100 0 Chris Mayer
s 4224 432 200 0 A&G Sequencer
s 3744 3184 100 0 $Id: agSeqState.sch,v 1.10 2007/05/18 22:29:25 pedro Exp $
s 3600 400 100 0 Copyright
s 3600 368 100 0 Observatory
s 3600 336 100 0 Sciences Ltd.
[cell use]
use bd200tr -160 -56 -100 0 frame
xform 0 2480 1648
use estringouts 1824 1367 100 0 niciState
xform 0 1952 1440
p 1888 1504 100 0 -1 DESC:NICI state
p 1760 1246 100 0 0 OMSL:closed_loop
p 1552 1488 100 0 -1 def(DOL):$(nici)wfs:state
use estringouts 1824 1815 100 0 f2State
xform 0 1952 1888
p 1888 1952 100 0 -1 DESC:Flamingos-2 state
p 1760 1662 100 0 0 IVOA:Set output to IVOV
p 1760 1630 100 0 0 IVOV:BOOTING
p 1760 1694 100 0 0 OMSL:closed_loop
p 1760 1854 100 0 0 VAL:BOOTING
p 1552 1936 100 0 -1 def(DOL):$(f2)wfs:state
use estringouts 1824 2551 100 0 gmosState
xform 0 1952 2624
p 1888 2688 100 0 -1 DESC:GMOS state
p 1760 2398 100 0 0 IVOA:Set output to IVOV
p 1760 2366 100 0 0 IVOV:BOOTING
p 1760 2430 100 0 0 OMSL:closed_loop
p 1760 2590 100 0 0 VAL:BOOTING
p 1536 2672 100 0 -1 def(DOL):$(gmos)wfs:state
use estringouts 1824 2775 100 0 noneState
xform 0 1952 2848
p 1888 2912 100 0 -1 DESC:State of OIWFS \"None\"
p 1760 2814 100 0 0 VAL:RUNNING
use estringouts 1824 2327 100 0 nirsState
xform 0 1952 2400
p 1888 2464 100 0 -1 DESC:NIRS state
p 1760 2174 100 0 0 IVOA:Set output to IVOV
p 1760 2142 100 0 0 IVOV:BOOTING
p 1760 2206 100 0 0 OMSL:closed_loop
p 1760 2366 100 0 0 VAL:BOOTING
p 1536 2448 100 0 -1 def(DOL):$(nirs)wfs:state
use estringouts 1824 2103 100 0 niriState
xform 0 1952 2176
p 1888 2240 100 0 -1 DESC:NIRI state
p 1760 1950 100 0 0 IVOA:Set output to IVOV
p 1760 1918 100 0 0 IVOV:BOOTING
p 1760 1982 100 0 0 OMSL:closed_loop
p 1760 2142 100 0 0 VAL:BOOTING
p 1536 2224 100 0 -1 def(DOL):$(niri)wfs:state
use estringouts 1824 1591 100 0 nifsState
xform 0 1952 1664
p 1888 1728 100 0 -1 DESC:NIFS State
p 1760 1438 100 0 0 IVOA:Set output to IVOV
p 1760 1406 100 0 0 IVOV:BOOTING
p 1760 1470 100 0 0 OMSL:closed_loop
p 1760 1630 100 0 0 VAL:BOOTING
p 1536 1712 100 0 -1 def(DOL):$(nifs)sad:wfs:state
use inhier 1472 1431 100 0 c#99
xform 0 1488 1472
use inhier 1472 1879 100 0 c#57
xform 0 1488 1920
use inhier 3992 2488 100 0 PWFS2
xform 0 3984 2528
use inhier 3992 2552 100 0 PWFS1
xform 0 3984 2592
use inhier 3992 2616 100 0 OIDC
xform 0 3984 2656
use inhier 3992 2680 100 0 CC
xform 0 3984 2720
use inhier 112 1751 100 0 OIWFS
xform 0 128 1792
use inhier 1456 2615 100 0 c#32
xform 0 1472 2656
use inhier 1456 2391 100 0 c#34
xform 0 1472 2432
use inhier 1456 2167 100 0 c#36
xform 0 1472 2208
use inhier 3968 2423 100 0 c#42
xform 0 3984 2464
use inhier 3968 2359 100 0 c#44
xform 0 3984 2400
use inhier 3968 2295 100 0 c#46
xform 0 3984 2336
use inhier 3968 2231 100 0 c#48
xform 0 3984 2272
use inhier 1472 1655 100 0 c#74
xform 0 1488 1696
use superfout 624 1399 100 0 superfout#60
xform 0 832 1632
use ecalcs 288 1319 100 0 incr
xform 0 432 1584
p 384 1488 100 0 1 CALC:A+1
p 448 1376 100 0 1 SCAN:1 second
use outhier 4928 2679 100 0 c#13
xform 0 4944 2720
use outhier 4928 2615 100 0 c#14
xform 0 4944 2656
use egenSub 4344 1960 100 0 combine
xform 0 4464 2384
p 4271 2823 100 0 -1 DESC:Calculate value of state record
p 4097 1733 100 0 0 FTA:LONG
p 4097 1733 100 0 0 FTB:LONG
p 4097 1701 100 0 0 FTC:LONG
p 4097 1669 100 0 0 FTD:LONG
p 4097 1637 100 0 0 FTE:STRING
p 4097 1573 100 0 0 FTF:STRING
p 4097 1573 100 0 0 FTG:STRING
p 4097 1541 100 0 0 FTH:STRING
p 4097 1509 100 0 0 FTI:STRING
p 4400 2750 100 0 1 FTVA:STRING
p 4432 2686 100 0 1 FTVB:LONG
p 4352 1918 100 0 1 SCAN:1 second
p 4352 1886 100 0 1 SNAM:agSeqCombineState
p 4016 2606 100 0 0 def(INPC):0.0
p 4016 2542 100 0 0 def(INPD):0.0
p 4080 2480 100 0 -1 def(INPE):$(ag)cc:state
p 4080 2416 100 0 -1 def(INPF):$(oiwfs)state
p 4080 2368 100 0 -1 def(INPG):$(pwfs1)state
p 4080 2288 100 0 -1 def(INPH):$(pwfs2)state
p 4704 2752 100 0 -1 def(OUTA):$(sad)state.IMSS
p 4688 2672 100 0 -1 def(OUTB):$(sad)state
p 4432 1952 100 1024 0 name:$(top)$(I)
p 4608 2730 75 0 -1 pproc(OUTA):NPP
p 4608 2666 75 0 -1 pproc(OUTB):PP
[comments]
