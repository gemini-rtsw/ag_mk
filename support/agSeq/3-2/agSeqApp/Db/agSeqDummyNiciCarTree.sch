[schematic2]
uniq 31
[tools]
[detail]
w 1848 1675 100 0 n#30 ecars.probeC.VAL 1792 1664 1952 1664 1952 1472 2112 1472 egenSub.activeCCombine.INPB
w 1864 1611 100 0 n#29 ecars.probeC.OMSS 1792 1600 1984 1600 1984 1536 2112 1536 egenSub.activeCCombine.INPA
w 680 1451 100 0 n#28 ecars.softC.VAL 608 1440 800 1440 800 1696 928 1696 egenSub.probeCombine.INPD
w 664 1387 100 0 n#27 ecars.softC.OMSS 608 1376 768 1376 768 1760 928 1760 egenSub.probeCombine.INPC
w 680 1931 100 0 n#26 ecars.simC.VAL 608 1920 800 1920 800 1824 928 1824 egenSub.probeCombine.INPB
w 664 1867 100 0 n#25 ecars.simC.OMSS 608 1856 768 1856 768 1888 928 1888 egenSub.probeCombine.INPA
w 2472 1483 100 0 n#24 egenSub.activeCCombine.OUTB 2400 1472 2592 1472 2592 1280 2688 1280 ecars.activeC.IVAL
w 2456 1547 100 0 n#23 egenSub.activeCCombine.OUTA 2400 1536 2560 1536 2560 1216 2688 1216 ecars.activeC.IMSS
w 1992 875 100 0 n#20 ecars.probeC.FLNK 1792 1440 1920 1440 1920 864 2112 864 egenSub.activeCCombine.SLNK
w 1256 1835 100 0 n#18 egenSub.probeCombine.OUTB 1216 1824 1344 1824 1344 1664 1472 1664 ecars.probeC.IVAL
w 1272 1899 100 0 n#17 egenSub.probeCombine.OUTA 1216 1888 1376 1888 1376 1600 1472 1600 ecars.probeC.IMSS
w 654 1707 100 0 n#9 ecars.simC.FLNK 608 1696 736 1696 736 1216 junction
w 750 1227 100 0 n#9 ecars.softC.FLNK 608 1216 928 1216 egenSub.probeCombine.SLNK
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqDummyNiciCarTree.sch,v 1.2 2010/01/12 02:27:03 gemvx Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2704 80 100 0 Dummy instrument CAR tree
s 288 2144 100 0 This CAR record is written to by the 
s 288 2112 100 0 probe simulator
s 288 1024 100 0 This CAR is written to by the commands
s 288 992 100 0 tolerance, move, stop, follow
s 1120 2256 200 0 CAR tree for the NICI WFS simulator
[cell use]
use egenSub 2112 775 100 0 activeCCombine
xform 0 2256 1200
p 2160 1648 100 0 -1 DESC:Combine instrument CARs
p 1889 549 100 0 0 FTA:STRING
p 1889 549 100 0 0 FTB:LONG
p 1889 517 100 0 0 FTC:STRING
p 1889 485 100 0 0 FTD:LONG
p 1889 549 100 0 0 FTVA:STRING
p 1889 549 100 0 0 FTVB:LONG
p 2176 720 100 0 1 SNAM:agSeqInsActiveC
p 2400 1482 75 0 -1 pproc(OUTB):PP
use egenSub 928 1127 100 0 probeCombine
xform 0 1072 1552
p 976 2000 100 0 -1 DESC:Combine probe CARs
p 705 901 100 0 0 FTA:STRING
p 705 901 100 0 0 FTB:LONG
p 705 869 100 0 0 FTC:STRING
p 705 837 100 0 0 FTD:LONG
p 705 901 100 0 0 FTVA:STRING
p 705 901 100 0 0 FTVB:LONG
p 992 1056 100 0 1 SNAM:agSeqInsProbeC
p 1216 1834 75 0 -1 pproc(OUTB):PP
use ecars 1472 1383 100 0 probeC
xform 0 1632 1552
use ecars 288 1159 100 0 softC
xform 0 448 1328
p 368 1520 100 0 -1 DESC:CAR for commands
use ecars 288 1639 100 0 simC
xform 0 448 1808
p 336 1984 100 0 -1 DESC:CAR for WFS simulator
use ecars 2688 999 100 0 activeC
xform 0 2848 1168
p 2720 1376 100 0 -1 DESC:A&G subsystem CAR record
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
