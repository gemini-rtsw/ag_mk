[schematic2]
uniq 6
[tools]
[detail]
w 2168 3723 100 0 n#1 hwin.hwin#13.in 2144 3712 2240 3712 estringins.estringins#19.INP
w 2168 4011 100 0 n#2 hwin.hwin#12.in 2144 4000 2240 4000 estringins.estringins#17.INP
w 1222 3979 100 0 n#3 ebis.ebis#6.VAL 1088 3968 1392 3968 egenSub.egenSub#10.INPA
w 824 2659 100 0 n#4 esirs.esirs#9.VAL 1056 2936 1120 2936 1120 2648 576 2648 576 2504 704 2504 ebis.ebis#24.INP
w 856 2627 100 0 n#5 esirs.esirs#9.FLNK 1056 2968 1152 2968 1152 2616 608 2616 608 2472 704 2472 ebis.ebis#24.SLNK
[cell use]
use bc200tr 208 1816 -100 0 frame
xform 0 1888 3120
use ebis 832 3911 100 0 ebis#6
xform 0 960 3984
p 904 4048 100 0 1 ONAM:MANUAL
p 904 4080 100 0 1 ZNAM:AUTOMATIC
p 944 3904 100 1024 -1 name:$(top)encoderMode
use estringins 2240 3895 100 0 estringins#17
xform 0 2368 3968
p 2352 3888 100 1024 -1 name:$(top)lensOff
use estringins 2240 3607 100 0 estringins#19
xform 0 2368 3680
p 2352 3600 100 1024 -1 name:$(top)fldstopOff
use hwin 1952 3959 100 0 hwin#12
xform 0 2048 4000
p 1888 4048 100 0 -1 val(in):$(top)lensxlat.VALA .CP .NMS
use hwin 1952 3671 100 0 hwin#13
xform 0 2048 3712
p 1888 3768 100 0 -1 val(in):$(top)fldstopxlat.VALA .CP .NMS
use egenSub 1392 3207 100 0 egenSub#10
xform 0 1536 3632
p 1488 3968 100 0 1 FTA:LONG
p 1480 3416 100 0 1 FTJ:LONG
p 1169 2725 100 0 0 FTVJ:DOUBLE
p 1432 4064 100 0 1 SNAM:encoderRelay
p 1504 3200 100 1024 -1 name:$(top)encoderRelay
use egenSub 2880 3199 100 0 egenSub#11
xform 0 3024 3624
p 2968 3960 100 0 1 FTA:STRING
p 2968 3896 100 0 1 FTB:STRING
p 2968 3832 100 0 1 FTC:LONG
p 2944 4048 100 0 1 SNAM:encoderOff
p 2536 3968 100 0 1 def(INPA):$(top)lensOff
p 2504 3888 100 0 1 def(INPB):$(top)fldstopOff
p 2496 3824 100 0 1 def(INPC):$(top)encoderMode
p 2992 3192 100 1024 -1 name:$(top)encoderOff
p 2832 3970 75 0 -1 pproc(INPA):CP
p 2832 3906 75 0 -1 pproc(INPB):CP
use ebis 704 2399 100 0 ebis#24
xform 0 832 2472
p 1008 2456 100 0 1 ONAM:ON
p 1008 2488 100 0 1 ZNAM:OFF
p 816 2392 100 1024 -1 name:$(top)encoderStatusStr
use esirs 640 2719 100 0 esirs#9
xform 0 848 2872
p 752 2840 100 0 1 FTVL:LONG
p 752 2760 100 0 1 SCAN:1 second
p 752 2800 100 0 1 SNAM:encoderStatus
p 752 2712 100 1024 -1 name:$(top)encoderStatus
[comments]
