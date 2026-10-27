[schematic2]
uniq 132
[tools]
[detail]
w 3370 3019 100 0 FLNK elongouts.elongouts#120.FLNK 3248 3232 3296 3232 3296 3008 3504 3008 outhier.FLNK.p
w 3394 3147 100 0 VAL elongouts.elongouts#120.VAL 3248 3264 3328 3264 3328 3136 3520 3136 outhier.VAL.p
w 3354 3307 100 0 OUT elongouts.elongouts#120.OUT 3248 3296 3520 3296 outhier.OUT.p
w 2434 3051 100 0 n#127 elongins.elongins#119.FLNK 2320 3392 2400 3392 2400 3040 2528 3040 ecalcs.ecalcs#121.SLNK
w 2394 3435 100 0 n#126 elongins.elongins#119.VAL 2320 3424 2528 3424 ecalcs.ecalcs#121.INPA
w 2874 3243 100 0 n#125 ecalcs.ecalcs#121.VAL 2816 3232 2992 3232 elongouts.elongouts#120.DOL
w 2874 3275 100 0 n#124 ecalcs.ecalcs#121.FLNK 2816 3264 2992 3264 elongouts.elongouts#120.SLNK
w 1850 3243 100 0 INP inhier.INP.P 1808 3232 1952 3232 1952 3376 2064 3376 elongins.elongins#119.INP
w 1906 3419 100 0 SLNK inhier.SLNK.P 1808 3408 2064 3408 elongins.elongins#119.SLNK
s 3440 2592 100 0 Signal inversion
s 3472 2656 100 0 A&G Sequencer
s 3136 2512 100 0 Pedro Gigoux
[cell use]
use ecalcs 2528 2951 100 0 ecalcs#121
xform 0 2672 3216
p 2656 3008 100 0 1 CALC:A<=0?1:0
p 2512 3472 100 0 -1 DESC:calc record
p 2640 2944 100 1024 -1 name:$(top)$(signal)
p 2528 3424 75 1280 -1 palrm(INPA):MS
use elongouts 3008 3168 100 0 elongouts#120
xform 6 3120 3264
p 3104 3360 100 1024 -1 name:$(top)$(signal)Out
use elongins 2096 3328 100 0 elongins#119
xform 6 2192 3408
p 2176 3488 100 1024 -1 name:$(top)$(signal)In
use outhier 3472 2967 100 0 FLNK
xform 0 3488 3008
use outhier 3488 3095 100 0 VAL
xform 0 3504 3136
use outhier 3488 3255 100 0 OUT
xform 0 3504 3296
use inhier 1792 3367 100 0 SLNK
xform 0 1808 3408
use inhier 1792 3191 100 0 INP
xform 0 1808 3232
use bb200tr 1344 2376 -100 0 frame
xform 0 2624 3200
[comments]
