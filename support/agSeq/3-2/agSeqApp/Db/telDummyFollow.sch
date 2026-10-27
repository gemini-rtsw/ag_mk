[schematic2]
uniq 95
[tools]
[detail]
w 2296 555 100 0 n#93 elongouts.elongouts#90.OUT 2272 544 2368 544 hwout.hwout#92.outp
w 2020 603 100 2 n#91 elongouts.elongouts#90.DOL 2016 608 2016 608 hwin.hwin#88.in
w 1816 587 100 0 n#87 egenSub.egenSub#0.FLNK 1664 576 2016 576 elongouts.elongouts#90.SLNK
w 1992 1291 100 0 n#85 egenSub.egenSub#0.OUTA 1664 1280 2368 1280 hwout.hwout#1.outp
w 376 -277 100 0 n#84 eaos.eaos#77.FLNK 288 -224 352 -224 352 -288 448 -288 elongouts.elongouts#18.SLNK
w 344 -245 100 0 n#83 eaos.eaos#77.VAL 288 -256 448 -256 elongouts.elongouts#18.DOL
w 36 -229 100 2 n#82 hwin.hwin#9.in 32 -224 32 -224 eaos.eaos#77.DOL
w 344 11 100 0 n#81 eaos.eaos#79.VAL 288 0 448 0 elongouts.elongouts#17.DOL
w 36 27 100 2 n#80 hwin.hwin#7.in 32 32 32 32 eaos.eaos#79.DOL
w 708 -69 100 2 n#73 hwout.hwout#23.outp 704 -64 704 -64 elongouts.elongouts#17.OUT
w 536 747 100 0 n#72 eaos.eaos#32.FLNK 704 896 800 896 800 736 320 736 320 640 448 640 eaos.eaos#33.SLNK
w 264 235 100 0 n#70 hwin.hwin#69.in 128 224 448 224 eaos.eaos#62.DOL
w 264 459 100 0 n#68 hwin.hwin#67.in 128 448 448 448 eaos.eaos#61.DOL
w 888 171 100 0 n#66 eaos.eaos#62.OUT 704 160 1120 160 1120 992 1376 992 egenSub.egenSub#0.F
w 856 395 100 0 n#65 eaos.eaos#61.OUT 704 384 1056 384 1056 1056 1376 1056 egenSub.egenSub#0.E
w 536 299 100 0 n#64 eaos.eaos#61.FLNK 704 448 800 448 800 288 320 288 320 192 448 192 eaos.eaos#62.SLNK
w 536 523 100 0 n#63 eaos.eaos#33.FLNK 704 672 800 672 800 512 320 512 320 416 448 416 eaos.eaos#61.SLNK
w 536 1483 100 0 n#59 elongouts.elongouts#57.FLNK 704 1632 800 1632 800 1472 320 1472 320 1344 448 1344 eaos.eaos#27.SLNK
w 264 683 100 0 n#55 hwin.hwin#54.in 128 672 448 672 eaos.eaos#33.DOL
w 264 907 100 0 n#53 hwin.hwin#52.in 128 896 448 896 eaos.eaos#32.DOL
w 264 1131 100 0 n#51 hwin.hwin#50.in 128 1120 448 1120 eaos.eaos#31.DOL
w 264 1387 100 0 n#49 hwin.hwin#48.in 128 1376 448 1376 eaos.eaos#27.DOL
w 1160 1131 100 0 n#47 eaos.eaos#33.OUT 704 608 992 608 992 1120 1376 1120 egenSub.egenSub#0.D
w 1128 1195 100 0 n#46 eaos.eaos#32.OUT 704 832 928 832 928 1184 1376 1184 egenSub.egenSub#0.C
w 1096 1259 100 0 n#45 eaos.eaos#31.OUT 704 1056 864 1056 864 1248 1376 1248 egenSub.egenSub#0.B
w 1016 1323 100 0 n#44 eaos.eaos#27.OUT 704 1312 1376 1312 egenSub.egenSub#0.A
w 536 1195 100 0 n#42 eaos.eaos#27.FLNK 704 1376 800 1376 800 1184 320 1184 320 1088 448 1088 eaos.eaos#31.SLNK
w 536 971 100 0 n#40 eaos.eaos#31.FLNK 704 1120 800 1120 800 960 320 960 320 864 448 864 eaos.eaos#32.SLNK
w 708 -325 100 2 n#26 hwout.hwout#25.outp 704 -320 704 -320 elongouts.elongouts#18.OUT
[cell use]
use hwout 2368 503 100 0 hwout#92
xform 0 2464 544
p 2576 544 100 0 -1 val(outp):$(ag)oi:followA.PROC
use elongouts 2016 487 100 0 elongouts#90
xform 0 2144 576
p 1856 494 100 0 0 OMSL:closed_loop
p 2128 480 100 1024 -1 name:t1:followProc
use hwin 1824 567 100 0 hwin#88
xform 0 1920 608
p 1827 600 100 0 -1 val(in):1
use eaos 448 103 100 0 eaos#62
xform 0 576 192
p 192 174 100 0 0 OMSL:closed_loop
p 560 96 100 1024 -1 name:$(tcs)dz
use eaos 448 327 100 0 eaos#61
xform 0 576 416
p 192 398 100 0 0 OMSL:closed_loop
p 560 320 100 1024 -1 name:$(tcs)dy
use eaos 448 551 100 0 eaos#33
xform 0 576 640
p 192 622 100 0 0 OMSL:closed_loop
p 560 544 100 1024 -1 name:$(tcs)dx
use eaos 448 775 100 0 eaos#32
xform 0 576 864
p 192 846 100 0 0 OMSL:closed_loop
p 560 768 100 1024 -1 name:$(tcs)z0
use eaos 448 999 100 0 eaos#31
xform 0 576 1088
p 192 1070 100 0 0 OMSL:closed_loop
p 560 992 100 1024 -1 name:$(tcs)y0
use eaos 448 1255 100 0 eaos#27
xform 0 576 1344
p 192 1326 100 0 0 OMSL:closed_loop
p 512 1216 100 0 1 PINI:YES
p 560 1248 100 1024 -1 name:$(tcs)x0
use eaos 32 -345 100 0 eaos#77
xform 0 160 -256
p 96 -384 100 0 1 PINI:YES
p 144 -352 100 1024 -1 name:$(tcs)stopVal
use eaos 32 -89 100 0 eaos#79
xform 0 160 0
p 96 -128 100 0 1 PINI:YES
p 144 -96 100 1024 -1 name:$(tcs)startVal
use hwin -64 183 100 0 hwin#69
xform 0 32 224
p -61 216 100 0 -1 val(in):5
use hwin -64 407 100 0 hwin#67
xform 0 32 448
p -61 440 100 0 -1 val(in):3
use hwin -64 631 100 0 hwin#54
xform 0 32 672
p -61 664 100 0 -1 val(in):1
use hwin -64 855 100 0 hwin#52
xform 0 32 896
p -61 888 100 0 -1 val(in):11
use hwin -64 1079 100 0 hwin#50
xform 0 32 1120
p -61 1112 100 0 -1 val(in):9
use hwin -64 1335 100 0 hwin#48
xform 0 32 1376
p -61 1368 100 0 -1 val(in):7
use hwin -160 -265 100 0 hwin#9
xform 0 -64 -224
p -157 -232 100 0 -1 val(in):1
use hwin -160 -9 100 0 hwin#7
xform 0 -64 32
p -157 24 100 0 -1 val(in):0
use elongouts 448 1511 100 0 elongouts#57
xform 0 576 1600
p 288 1518 100 0 0 OMSL:closed_loop
p 560 1504 100 1024 -1 name:$(tcs)reset
use elongouts 448 -377 100 0 elongouts#18
xform 0 576 -288
p 288 -370 100 0 0 OMSL:closed_loop
p 496 -416 100 0 0 PINI:NO
p 560 -384 100 1024 -1 name:$(tcs)stop
use elongouts 448 -121 100 0 elongouts#17
xform 0 576 -32
p 288 -114 100 0 0 OMSL:closed_loop
p 560 -128 100 1024 -1 name:$(tcs)start
use hwout 704 -361 100 0 hwout#25
xform 0 800 -320
p 928 -320 100 0 -1 val(outp):$(tcs)follow.DISA
use hwout 704 -105 100 0 hwout#23
xform 0 800 -64
p 928 -64 100 0 -1 val(outp):$(tcs)follow.DISA
use hwout 2368 1239 100 0 hwout#1
xform 0 2464 1280
p 2576 1280 100 0 -1 val(outp):$(ag)oi:followA.J
use egenSub 1376 519 100 0 egenSub#0
xform 0 1520 944
p 1472 1024 100 0 0 FTE:DOUBLE
p 1504 1312 100 0 1 NOVA:6
p 1424 480 100 0 1 SCAN:2 second
p 1424 448 100 0 1 SNAM:agSeqTelFollow
p 1488 512 100 1024 -1 name:$(tcs)follow
p 1664 1290 75 0 -1 pproc(OUTA):NPP
[comments]
