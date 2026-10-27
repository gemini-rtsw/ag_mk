[schematic2]
uniq 128
[tools]
[detail]
w 2498 2475 100 0 n#127 estringouts.estringouts#119.FLNK 2656 2592 2752 2592 2752 2464 2304 2464 2304 2368 2400 2368 elongouts.elongouts#120.SLNK
w 2850 2347 100 0 OCAR elongouts.elongouts#120.OUT 2656 2336 3104 2336 outhier.OCAR.p
w 2850 2571 100 0 OMESS estringouts.estringouts#119.OUT 2656 2560 3104 2560 outhier.OMESS.p
w 2178 2411 100 0 CAR inhier.CAR.P 2016 2400 2400 2400 elongouts.elongouts#120.DOL
w 2178 2587 100 0 SLNK inhier.SLNK.P 2016 2576 2400 2576 estringouts.estringouts#119.SLNK
w 2114 2699 100 0 MESS inhier.MESS.P 2016 2688 2272 2688 2272 2608 2400 2608 estringouts.estringouts#119.DOL
s 3456 1824 100 0 A&G Sequencer
s 3424 1760 100 0 CAR val and message
s 3120 1680 100 0 Pedro Gigoux
s 1728 2976 100 0 The only purpose of this schematic
s 1728 2944 100 0 is to simplify agSeqCarOiwfs
[cell use]
use inhier 2000 2359 100 0 CAR
xform 0 2016 2400
use inhier 2000 2647 100 0 MESS
xform 0 2016 2688
use inhier 2000 2535 100 0 SLNK
xform 0 2016 2576
use outhier 3072 2295 100 0 OCAR
xform 0 3088 2336
use outhier 3072 2519 100 0 OMESS
xform 0 3088 2560
use bb200tr 1312 1544 -100 0 frame
xform 0 2592 2368
use estringouts 2400 2503 100 0 estringouts#119
xform 0 2528 2576
p 2427 2616 100 0 0 DESC:$(subsys) activeC message
p 2336 2382 100 0 0 OMSL:closed_loop
p 2512 2496 100 1024 -1 name:$(top)$(subsys)Str
use elongouts 2400 2279 100 0 elongouts#120
xform 0 2528 2368
p 2285 2713 100 0 0 DESC:$(subsys) activeC value
p 2240 2286 100 0 0 OMSL:closed_loop
p 2512 2272 100 1024 -1 name:$(top)$(subsys)Val
p 2656 2336 75 768 -1 pproc(OUT):PP
[comments]
