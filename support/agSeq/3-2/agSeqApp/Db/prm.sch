[schematic2]
uniq 36
[tools]
[detail]
w 2696 1835 100 0 n#33 eseqs.eseqs#27.LNK1 2624 1824 2816 1824 hwout.hwout#32.outp
w 2664 1803 100 0 n#33 eseqs.eseqs#27.LNK2 2624 1792 2752 1792 2752 1824 junction
w 2168 1803 100 0 n#31 hwin.hwin#28.in 2080 1792 2304 1792 eseqs.eseqs#27.DOL2
w 1944 1515 100 0 n#30 ecad2.ecad2#24.STLK 1632 1504 2304 1504 eseqs.eseqs#27.SLNK
w 2232 1835 100 0 n#25 hwin.hwin#29.in 2208 1824 2304 1824 eseqs.eseqs#27.DOL1
w 2296 2283 100 0 n#23 ecad2.ecad2#0.VALB 1632 3136 1760 3136 1760 2272 2880 2272 esirs.esirs#6.INP
w 2328 2667 100 0 n#22 ecad2.ecad2#0.VALA 1632 3200 1824 3200 1824 2656 2880 2656 esirs.esirs#1.INP
w 2728 2123 100 0 n#21 eseqs.eseqs#2.LNK3 2496 3168 2624 3168 2624 2112 2880 2112 esirs.esirs#6.SLNK
w 2568 3211 100 0 n#20 eseqs.eseqs#2.LNK2 2496 3200 2688 3200 2688 2496 2880 2496 esirs.esirs#1.SLNK
w 2600 3147 100 0 n#19 eseqs.eseqs#2.LNK4 2496 3136 2752 3136 2752 3232 junction
w 2664 3243 100 0 n#19 eseqs.eseqs#2.LNK1 2496 3232 2880 3232 ecars.ecars#5.IVAL
w 2104 3147 100 0 n#16 hwin.hwin#7.in 2080 3136 2176 3136 eseqs.eseqs#2.DOL4
w 2104 3243 100 0 n#15 hwin.hwin#3.in 2080 3232 2176 3232 eseqs.eseqs#2.DOL1
w 1880 2923 100 0 n#11 ecad2.ecad2#0.STLK 1632 2912 2176 2912 eseqs.eseqs#2.SLNK
[cell use]
use esirs 3840 2023 100 0 esirs#35
xform 0 4048 2176
p 3976 2144 100 0 1 FTVL:STRING
p 3952 2016 100 1024 -1 name:$(top)prmMode
use esirs 3840 2407 100 0 esirs#34
xform 0 4048 2560
p 3992 2552 100 0 1 FTVL:STRING
p 3952 2400 100 1024 -1 name:$(top)prmHealth
use hwout 2816 1783 100 0 hwout#32
xform 0 2912 1824
p 2832 1864 100 0 -1 val(outp):$(top)prmC.IVAL .PP .NMS
use hwin 1888 3095 100 0 hwin#7
xform 0 1984 3136
p 1891 3128 100 0 -1 val(in):$(IDLE)
use hwin 1888 3191 100 0 hwin#3
xform 0 1984 3232
p 1891 3224 100 0 -1 val(in):$(BUSY)
use hwin 1888 1751 100 0 hwin#28
xform 0 1984 1792
p 1891 1784 100 0 -1 val(in):$(IDLE)
use hwin 2016 1783 100 0 hwin#29
xform 0 2112 1824
p 2019 1816 100 0 -1 val(in):$(BUSY)
use eseqs 2176 2823 100 0 eseqs#2
xform 0 2336 3072
p 2240 3368 100 0 1 DLY2:1.0
p 2240 3328 100 0 1 DLY4:1.0
p 2288 2816 100 1024 -1 name:$(top)prmSeq1
p 2512 3232 75 1024 -1 pproc(LNK1):PP
p 2512 3200 75 1024 -1 pproc(LNK2):PP
p 2512 3168 75 1024 -1 pproc(LNK3):PP
p 2512 3136 75 1024 -1 pproc(LNK4):PP
use eseqs 2304 1415 100 0 eseqs#27
xform 0 2464 1664
p 2368 1912 100 0 1 DLY2:1.0
p 2368 1920 100 0 0 DLY4:0.0
p 2416 1408 100 1024 -1 name:$(top)prmSeq2
p 2640 1824 75 1024 -1 pproc(LNK1):NPP
p 2640 1792 75 1024 -1 pproc(LNK2):NPP
p 2640 1760 75 1024 -1 pproc(LNK3):NPP
p 2640 1728 75 1024 -1 pproc(LNK4):NPP
use ecad2 1312 2823 100 0 ecad2#0
xform 0 1472 3136
p 1408 3216 100 0 1 FTVA:LONG
p 1408 3176 100 0 1 FTVB:LONG
p 1376 3456 100 0 1 SNAM:prmSelectCAD
p 1424 2816 100 1024 -1 name:$(top)prmSelect
use ecad2 1312 1415 100 0 ecad2#24
xform 0 1472 1728
p 1408 1808 100 0 0 FTVA:STRING
p 1408 1768 100 0 0 FTVB:STRING
p 1376 2048 100 0 1 SNAM:prmTestCAD
p 1424 1408 100 1024 -1 name:$(top)prmTest
use esirs 2880 2023 100 0 esirs#6
xform 0 3088 2176
p 3040 2160 100 0 1 FTVL:LONG
p 2992 2016 100 1024 -1 name:$(top)prmOutput
use esirs 2880 2407 100 0 esirs#1
xform 0 3088 2560
p 3032 2552 100 0 1 FTVL:LONG
p 2992 2400 100 1024 -1 name:$(top)prmInput
use ecars 2880 2951 100 0 ecars#5
xform 0 3040 3120
p 2992 2944 100 1024 -1 name:$(top)prmC
use bc200tr 1048 1120 -100 0 frame
xform 0 2728 2424
[comments]
