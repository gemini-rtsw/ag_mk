[schematic2]
uniq 144
[tools]
[detail]
w 738 1611 100 0 n#143 egenSub.followA.VALG 608 1600 928 1600 928 1504 1088 1504 egenSub.nici.INPA
w 754 1259 100 0 n#141 egenSub.followA.FLNK 608 1248 960 1248 960 1856 1088 1856 egenSub.none.SLNK
w 2914 1675 100 0 n#140 egenSub.nici.SLNK 1088 832 992 832 992 1664 4896 1664 4896 1824 4800 1824 egenSub.nifs.FLNK
w 754 1995 100 0 n#139 egenSub.followA.VALA 608 1984 960 1984 960 2528 1088 2528 egenSub.none.INPA
w 2594 2795 100 0 n#137 egenSub.followA.VALF 608 1664 800 1664 800 2784 4448 2784 4448 2528 4512 2528 egenSub.nifs.INPA
w 2290 2763 100 0 n#136 egenSub.followA.VALE 608 1728 832 1728 832 2752 3808 2752 3808 2528 3872 2528 egenSub.f2.INPA
w 1986 2731 100 0 n#135 egenSub.followA.VALD 608 1792 864 1792 864 2720 3168 2720 3168 2528 3232 2528 egenSub.niri.INPA
w 1682 2699 100 0 n#134 egenSub.followA.VALC 608 1856 896 1856 896 2688 2528 2688 2528 2528 2592 2528 egenSub.nirs.INPA
w 1378 2667 100 0 n#133 egenSub.followA.VALB 608 1920 928 1920 928 2656 1888 2656 1888 2528 1952 2528 egenSub.gmos.INPA
w 4226 1835 100 0 n#122 egenSub.f2.FLNK 4160 1824 4352 1824 4352 1856 4512 1856 egenSub.nifs.SLNK
w 3586 1835 100 0 n#117 egenSub.niri.FLNK 3520 1824 3712 1824 3712 1856 3872 1856 egenSub.f2.SLNK
w 2946 1835 100 0 n#116 egenSub.nirs.FLNK 2880 1824 3072 1824 3072 1856 3232 1856 egenSub.niri.SLNK
w 2306 1835 100 0 n#115 egenSub.gmos.FLNK 2240 1824 2432 1824 2432 1856 2592 1856 egenSub.nirs.SLNK
w 1490 1835 100 0 n#114 egenSub.none.FLNK 1376 1824 1664 1824 1664 1856 1952 1856 egenSub.gmos.SLNK
w 1956 2267 100 2 n#107 hwin.hwin#106.in 1952 2272 1952 2272 egenSub.gmos.INPE
w 1956 2331 100 2 n#105 hwin.hwin#104.in 1952 2336 1952 2336 egenSub.gmos.INPD
w 1956 2395 100 2 n#103 hwin.hwin#102.in 1952 2400 1952 2400 egenSub.gmos.INPC
w 1956 2459 100 2 n#101 hwin.hwin#100.in 1952 2464 1952 2464 egenSub.gmos.INPB
w 1400 2347 100 0 n#94 egenSub.none.OUTD 1376 2336 1472 2336 1472 2096 1504 2096 eaos.trackId.SLNK
w 216 1963 100 0 n#84 inhier.OIWFS.P 160 1952 320 1952 egenSub.followA.INPA
s 2224 1216 500 0 Add more instruments here
s 128 2992 100 0 subsystems not selected just get the same value sent repeatedly.
s 128 3024 100 0 subsystem that is selected will send out new data. The
s 128 3056 100 0 each time followA processes. It is just that only the 
s 128 3088 100 0 Note that all subsystem specific gensubs process
s 4432 208 100 0 Fanout of OIWFS demands
s 3712 112 100 0 Chris Mayer
s 4432 352 200 0 A&G Sequencer
s 3824 3120 100 0 $Id: agSeqOiwfsFollow.sch,v 1.12 2007/05/18 22:29:22 pedro Exp $
s 3728 336 100 0 Copyright
s 3728 304 100 0 Observatory
s 3728 272 100 0 Sciences Ltd.
s 256 976 100 0 The TCS data is written to port J
s 256 944 100 0 of this record which causes it to process
[cell use]
use egenSub 1088 743 100 0 nici
xform 0 1232 1168
p 1120 1584 100 0 -1 DESC:Fanout for NICI OIWFS
p 865 421 100 0 0 FTE:STRING
p 865 165 100 0 0 NOA:6
p 865 165 100 0 0 NOVA:6
p 800 1294 100 0 0 PREC:14
p 1168 736 100 0 1 SNAM:agSeqSubsysFollow
p 1408 1568 100 0 -1 def(OUTA):$(nici)wfs:followA.J
p 1376 1514 75 0 -1 pproc(OUTA):PP
use egenSub 4512 1767 100 0 nifs
xform 0 4656 2192
p 4544 2608 100 0 -1 DESC:Fanout for NIFS OIWFS
p 4289 1445 100 0 0 FTE:STRING
p 4289 1189 100 0 0 NOA:6
p 4289 1189 100 0 0 NOVA:6
p 4224 2318 100 0 0 PREC:14
p 4592 1760 100 0 1 SNAM:agSeqSubsysFollow
p 4832 2592 100 0 -1 def(OUTA):$(nifs)wfs:followA.J
p 4800 2538 75 0 -1 pproc(OUTA):PP
use egenSub 2592 1767 100 0 nirs
xform 0 2736 2192
p 2624 2608 100 0 -1 DESC:Fanout for NIRS OIWFS 
p 2369 1189 100 0 0 NOA:6
p 2369 1189 100 0 0 NOVA:6
p 2304 2318 100 0 0 PREC:14
p 2672 1760 100 0 1 SNAM:agSeqSubsysFollow
p 2912 2592 100 0 -1 def(OUTA):$(nirs)wfs:followA.J
p 2880 2538 75 0 -1 pproc(OUTA):PP
use egenSub 1952 1767 100 0 gmos
xform 0 2096 2192
p 1984 2608 100 0 -1 DESC:Fanout for GMOS OIWFS 
p 1729 1445 100 0 0 FTE:STRING
p 1729 1189 100 0 0 NOA:6
p 1729 1189 100 0 0 NOVA:6
p 1664 2318 100 0 0 PREC:14
p 2032 1760 100 0 1 SNAM:agSeqSubsysFollow
p 2272 2592 100 0 -1 def(OUTA):$(gmos)wfs:followA.J
p 2240 2538 75 0 -1 pproc(OUTA):PP
use egenSub 288 1184 100 0 followA
xform 0 464 1616
p 336 2064 100 0 -1 DESC:Fanout of continuous demands
p 97 965 100 0 0 FTA:LONG
p 97 325 100 0 0 NOJ:6
p 97 613 100 0 0 NOVA:6
p 97 581 100 0 0 NOVB:6
p 97 549 100 0 0 NOVC:6
p 97 517 100 0 0 NOVD:6
p 97 485 100 0 0 NOVE:6
p 97 453 100 0 0 NOVF:6
p 97 421 100 0 0 NOVG:6
p 97 389 100 0 0 NOVH:6
p 97 357 100 0 0 NOVI:6
p 32 1742 100 0 0 PREC:14
p 400 1184 100 0 1 SNAM:agSeqFollowA
p 432 1184 100 1024 0 name:$(ag)oi:$(I)
use egenSub 1088 1767 100 0 none
xform 0 1232 2192
p 1120 2608 100 0 -1 DESC:Fanout for OIWFS \"none\"
p 865 1189 100 0 0 NOA:6
p 865 1189 100 0 0 NOVA:6
p 800 2318 100 0 0 PREC:14
p 1168 1760 100 0 1 SNAM:agSeqSubsysFollow
p 865 1925 100 0 0 def(OUTA):0.000000000000000e+00
p 1376 2538 75 0 -1 pproc(OUTA):PP
p 1376 2346 75 0 -1 pproc(OUTD):PP
use egenSub 3232 1767 100 0 niri
xform 0 3376 2192
p 3264 2608 100 0 -1 DESC:Fanout for NIRI OIWFS 
p 3009 1189 100 0 0 NOA:6
p 3009 1189 100 0 0 NOVA:6
p 2944 2318 100 0 0 PREC:14
p 3312 1760 100 0 1 SNAM:agSeqSubsysFollow
p 3552 2592 100 0 -1 def(OUTA):$(niri)wfs:followA.J
p 3520 2538 75 0 -1 pproc(OUTA):PP
use egenSub 3872 1767 100 0 f2
xform 0 4016 2192
p 3904 2608 100 0 -1 DESC:Fanout for Flamingos-2
p 3649 1189 100 0 0 NOA:6
p 3649 1189 100 0 0 NOVA:6
p 3584 2318 100 0 0 PREC:14
p 3952 1760 100 0 1 SNAM:agSeqSubsysFollow
p 4192 2592 100 0 -1 def(OUTA):$(f2)wfs:followA.J
p 4160 2538 75 0 -1 pproc(OUTA):PP
use hwin 1760 2231 100 0 hwin#106
xform 0 1856 2272
p 1648 2256 100 0 -1 val(in):$(ag)oiwfsSel.VALF
use hwin 1760 2423 100 0 hwin#100
xform 0 1856 2464
p 1763 2456 100 0 -1 val(in):$(ag)tweakX
use hwin 1760 2359 100 0 hwin#102
xform 0 1856 2400
p 1763 2392 100 0 -1 val(in):$(ag)tweakY
use hwin 1760 2295 100 0 hwin#104
xform 0 1856 2336
p 1763 2328 100 0 -1 val(in):$(ag)tweakZ
use bd200tr -48 -120 -100 0 frame
xform 0 2592 1584
use eaos 1504 2007 100 0 trackId
xform 0 1632 2096
p 1584 2176 100 0 -1 DESC:Track id 
p 1472 1822 100 0 0 EGU:secs
p 1616 2000 100 1024 0 name:$(ag)none:wfs:$(I)
use inhier 144 1911 100 0 OIWFS
xform 0 160 1952
[comments]
