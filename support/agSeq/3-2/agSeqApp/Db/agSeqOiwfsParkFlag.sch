[schematic2]
uniq 210
[tools]
[detail]
w 3154 2507 100 0 n#209 elongouts.nifs.OUT 3136 2496 3232 2496 junction
w 3266 2763 100 0 n#209 elongouts.probeParked.SLNK 4512 2752 1984 2752 elongouts.none.OUT
w 2002 907 100 0 n#209 elongouts.f2.OUT 1984 896 2080 896 2080 2752 junction
w 2002 1515 100 0 n#209 elongouts.niri.OUT 1984 1504 2080 1504 junction
w 2002 2123 100 0 n#209 elongouts.nirs.OUT 1984 2112 2080 2112 junction
w 2002 2411 100 0 n#209 elongouts.gmos.OUT 1984 2400 2080 2400 junction
w 3154 1899 100 0 n#209 elongouts.nici.OUT 3136 1888 3232 1888 3232 2752 junction
w 2802 2443 100 0 n#203 ecalcs.nifsCalc.VAL 2784 2432 2880 2432 elongouts.nifs.DOL
w 2802 2475 100 0 n#202 ecalcs.nifsCalc.FLNK 2784 2464 2880 2464 elongouts.nifs.SLNK
w 1530 395 100 0 n#200 superfout.fan.LNK7 976 384 2144 384 2144 1632 2496 1632 ecalcs.niciCalc.SLNK
w 1514 427 100 0 n#199 superfout.fan.LNK6 976 416 2112 416 2112 2240 2496 2240 ecalcs.nifsCalc.SLNK
w 2802 1835 100 0 n#197 ecalcs.niciCalc.VAL 2784 1824 2880 1824 elongouts.nici.DOL
w 2802 1867 100 0 n#194 ecalcs.niciCalc.FLNK 2784 1856 2880 1856 elongouts.nici.SLNK
w 1410 939 100 0 n#182 superfout.fan.LNK5 976 448 1152 448 1152 928 1728 928 elongouts.f2.SLNK
w 1202 1259 100 0 n#180 superfout.fan.LNK4 976 480 1120 480 1120 1248 1344 1248 ecalcs.niriCalc.SLNK
w 1186 1867 100 0 n#179 superfout.fan.LNK3 976 512 1088 512 1088 1856 1344 1856 ecalcs.nirsCalc.SLNK
w 1362 2443 100 0 n#178 superfout.fan.LNK2 976 544 1056 544 1056 2432 1728 2432 elongouts.gmos.SLNK
w 1154 2715 100 0 n#177 superfout.fan.LNK1 976 576 1024 576 1024 2704 1344 2704 elongins.rawPark.SLNK
w 4594 2635 100 0 n#174 elongouts.probeParked.OUT 4768 2720 4832 2720 4832 2624 4416 2624 4416 2528 4512 2528 ebis.parkState.SLNK
w 1634 2731 100 0 n#172 elongins.rawPark.FLNK 1600 2720 1728 2720 elongouts.none.SLNK
w 1634 2699 100 0 n#171 elongins.rawPark.VAL 1600 2688 1728 2688 elongouts.none.DOL
w 1650 1451 100 0 n#167 ecalcs.niriCalc.VAL 1632 1440 1728 1440 elongouts.niri.DOL
w 1650 1483 100 0 n#166 ecalcs.niriCalc.FLNK 1632 1472 1728 1472 elongouts.niri.SLNK
w 1650 2059 100 0 n#164 ecalcs.nirsCalc.VAL 1632 2048 1728 2048 elongouts.nirs.DOL
w 1650 2091 100 0 n#163 ecalcs.nirsCalc.FLNK 1632 2080 1728 2080 elongouts.nirs.SLNK
w 498 523 100 0 n#154 ecalcs.calc.VAL 448 400 496 400 496 512 560 512 superfout.fan.SELL
w 458 443 100 0 n#153 ecalcs.calc.FLNK 448 432 528 432 528 288 560 288 superfout.fan.SLNK
w 64 603 100 0 n#79 inhier.OIWFS.P 16 592 160 592 ecalcs.calc.INPA
s 768 2848 100 0 doesn't suffer from this problem.
s 768 2880 100 0 record was added. The gmos record
s 768 2912 100 0 on startup hence this extra login
s 768 2944 100 0 record gave a very large value
s 768 2976 100 0 It was found that the logout none
s 4272 128 100 0 Fetch OIWFS park flag
s 3568 -16 100 0 Chris Mayer
s 4256 256 200 0 A&G Sequencer
s 3584 192 100 0 Copyright
s 3584 160 100 0 Observatory
s 3584 128 100 0 Sciences Ltd.
s 3696 2992 100 0 $Id: agSeqOiwfsParkFlag.sch,v 1.6 2010/01/12 02:27:04 gemvx Exp $
s 1232 880 100 0 Left room for a calc record
s 1232 848 100 0 here in case f2 needs to
s 1232 816 100 0 the park signal inverted
s 2832 1328 500 0 Add extra instruments here
[cell use]
use bd200tr -224 -232 -100 0 frame
xform 0 2416 1472
use elongouts 2880 1945 100 0 nici
xform 6 3008 1856
p 2944 1760 100 0 -1 DESC:Park flag
p 2720 1714 100 0 0 EGU:none
p 2720 1938 100 0 0 OMSL:closed_loop
p 2880 1824 75 1280 -1 palrm(DOL):MS
p 3168 1888 75 768 -1 palrm(OUT):MS
p 3136 1888 75 768 -1 pproc(OUT):PP
use elongouts 2880 2553 100 0 nifs
xform 6 3008 2464
p 2944 2368 100 0 -1 DESC:Park flag
p 2720 2322 100 0 0 EGU:none
p 2720 2546 100 0 0 OMSL:closed_loop
p 2880 2432 75 1280 -1 palrm(DOL):MS
p 3168 2496 75 768 -1 palrm(OUT):MS
p 3136 2496 75 768 -1 pproc(OUT):PP
use elongouts 1728 1561 100 0 niri
xform 6 1856 1472
p 1792 1376 100 0 -1 DESC:Park flag
p 1568 1330 100 0 0 EGU:none
p 1568 1554 100 0 0 OMSL:closed_loop
p 1728 1440 75 1280 -1 palrm(DOL):MS
p 2016 1504 75 768 -1 palrm(OUT):MS
p 1984 1504 75 768 -1 pproc(OUT):PP
use elongouts 1728 2169 100 0 nirs
xform 6 1856 2080
p 1792 1984 100 0 -1 DESC:Park flag
p 1568 1938 100 0 0 EGU:none
p 1568 2162 100 0 0 OMSL:closed_loop
p 1728 2048 75 1280 -1 palrm(DOL):MS
p 2016 2112 75 768 -1 palrm(OUT):MS
p 1984 2112 75 768 -1 pproc(OUT):PP
use elongouts 1728 2809 100 0 none
xform 6 1856 2720
p 1792 2624 100 0 -1 DESC:Park flag
p 1568 2578 100 0 0 EGU:none
p 1568 2802 100 0 0 OMSL:closed_loop
p 1488 2656 100 0 0 def(DOL):0.0
p 1728 2688 75 1280 -1 palrm(DOL):MS
p 2016 2752 75 768 -1 palrm(OUT):MS
p 1984 2752 75 768 -1 pproc(OUT):PP
use elongouts 4512 2663 100 0 probeParked
xform 0 4640 2752
p 4576 2832 100 0 -1 DESC:OIWFS probe parked status
p 4352 2894 100 0 0 EGU:none
p 4800 2720 75 768 -1 palrm(OUT):MS
p 4768 2720 75 768 -1 pproc(OUT):PP
use elongouts 1728 2343 100 0 gmos
xform 0 1856 2432
p 1792 2528 100 0 -1 DESC:Park flag
p 1568 2574 100 0 0 EGU:none
p 1568 2350 100 0 0 OMSL:closed_loop
p 1504 2512 100 0 -1 def(DOL):$(gmos)wfs:probePark
p 1728 2464 75 1280 -1 palrm(DOL):MS
p 2016 2400 75 768 -1 palrm(OUT):MS
p 1984 2400 75 768 -1 pproc(OUT):PP
use elongouts 1728 839 100 0 f2
xform 0 1856 928
p 1792 1008 100 0 -1 DESC:Park flag
p 1568 1070 100 0 0 EGU:none
p 1568 846 100 0 0 OMSL:closed_loop
p 1536 1008 100 0 -1 def(DOL):$(f2)wfs:probePark
p 1728 960 75 1280 -1 palrm(DOL):MS
p 2016 896 75 768 -1 palrm(OUT):MS
p 1984 896 75 768 -1 pproc(OUT):PP
use ecalcs 2496 1543 100 0 niciCalc
xform 0 2640 1808
p 2576 1872 100 0 1 CALC:A=0?1:0
p 2560 2064 100 0 -1 DESC:Invert NICI status
p 2240 2080 100 0 -1 def(INPA):$(nici)wfs:prbParked
p 2208 1822 100 0 0 def(INPB):0.000000000000000e+00
p 2496 2016 75 1280 -1 palrm(INPA):MS
use ecalcs 2496 2151 100 0 nifsCalc
xform 0 2640 2416
p 2576 2480 100 0 1 CALC:A=0?1:0
p 2560 2672 100 0 -1 DESC:Invert NIFS status
p 2240 2688 100 0 -1 def(INPA):$(nifs)sad:wfs:prbParked
p 2208 2430 100 0 0 def(INPB):0.000000000000000e+00
p 2496 2624 75 1280 -1 palrm(INPA):MS
use ecalcs 1344 1767 100 0 nirsCalc
xform 0 1488 2032
p 1424 2096 100 0 1 CALC:A=0?1:0
p 1408 2288 100 0 -1 DESC:Invert NIRS status
p 1136 2304 100 0 -1 def(INPA):$(nirs)wfs:prbParked
p 1344 2240 75 1280 -1 palrm(INPA):MS
use ecalcs 1344 1159 100 0 niriCalc
xform 0 1488 1424
p 1424 1488 100 0 1 CALC:A=0?1:0
p 1408 1680 100 0 -1 DESC:Invert NIRI status
p 1136 1696 100 0 -1 def(INPA):$(niri)wfs:prbParked
p 1344 1632 75 1280 -1 palrm(INPA):MS
use ecalcs 160 119 100 0 calc
xform 0 304 384
p 272 320 100 0 1 CALC:A+1
p 336 208 100 0 1 SCAN:.2 second
use superfout 640 160 100 0 fan
xform 0 768 416
use elongins 1344 2631 100 0 rawPark
xform 0 1472 2704
p 1133 2905 100 0 0 DESC:Extra input record
p 1088 2702 100 0 0 EGU:units
p 1200 2784 100 0 -1 def(INP):$(ag)noRecord
p 1344 2736 75 1280 -1 palrm(INP):MS
use ebis 4512 2455 100 0 parkState
xform 0 4640 2528
p 4576 2592 100 0 -1 DESC:OIWFS park state
p 4288 2366 100 0 0 ONAM:Parked
p 4288 2398 100 0 0 ZNAM:Not parked
use inhier 0 551 100 0 OIWFS
xform 0 16 592
[comments]
