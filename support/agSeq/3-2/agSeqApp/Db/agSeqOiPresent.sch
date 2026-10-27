[schematic2]
uniq 44
[tools]
[detail]
w 4904 3499 100 0 n#43 agSeqSubsysPresent.agSeqSubsysPresent#42.DISV 4224 2976 4288 2976 4288 3488 5568 3488 esels.selectOiwfs.INPG
w 2536 3115 100 0 n#36 agSeqSubsysPresent.agSeqSubsysPresent#2.LOADED 2592 3104 2528 3104 junction
w 2536 2699 100 0 n#36 agSeqSubsysPresent.agSeqSubsysPresent#9.LOADED 2592 2688 2528 2688 junction
w 2536 2283 100 0 n#36 agSeqSubsysPresent.agSeqSubsysPresent#10.LOADED 2592 2272 2528 2272 junction
w 2536 1867 100 0 n#36 junction 2528 1856 2592 1856 agSeqSubsysPresent.agSeqSubsysPresent#26.LOADED
w 2472 3275 100 0 n#36 eais.enableOiwfsPresent.VAL 2464 3264 2528 3264 2528 1440 2592 1440 agSeqSubsysPresent.agSeqSubsysPresent#28.LOADED
w 3000 3275 100 0 n#36 junction 2528 3264 3520 3264 3520 3104 3584 3104 agSeqSubsysPresent.agSeqSubsysPresent#42.LOADED
w 4472 3531 100 0 n#41 agSeqSubsysPresent.agSeqSubsysPresent#28.DISV 3232 1312 3424 1312 3424 3520 5568 3520 esels.selectOiwfs.INPF
w 4456 3563 100 0 n#40 agSeqSubsysPresent.agSeqSubsysPresent#26.DISV 3232 1728 3392 1728 3392 3552 5568 3552 esels.selectOiwfs.INPE
w 4440 3595 100 0 n#39 agSeqSubsysPresent.agSeqSubsysPresent#10.DISV 3232 2144 3360 2144 3360 3584 5568 3584 esels.selectOiwfs.INPD
w 4424 3627 100 0 n#38 agSeqSubsysPresent.agSeqSubsysPresent#9.DISV 3232 2560 3328 2560 3328 3616 5568 3616 esels.selectOiwfs.INPC
w 4408 3659 100 0 n#37 agSeqSubsysPresent.agSeqSubsysPresent#2.DISV 3232 2976 3296 2976 3296 3648 5568 3648 esels.selectOiwfs.INPB
w 4168 3691 100 0 n#35 eaos.oiwfsNone.VAL 2464 3552 2816 3552 2816 3680 5568 3680 esels.selectOiwfs.INPA
w 3618 3723 100 0 OIWFS inhier.OIWFS.P 1728 3712 5568 3712 esels.selectOiwfs.NVL
w 2112 3323 100 0 n#24 hwin.hwin#23.in 2064 3312 2208 3312 eais.enableOiwfsPresent.INP
w 2152 3595 100 0 n#17 hwin.hwin#7.in 2144 3584 2208 3584 eaos.oiwfsNone.DOL
w 5926 3515 100 0 n#8 esels.selectOiwfs.VAL 5856 3504 6032 3504 outhier.DISV.p
s 4992 4016 100 0 $Id: agSeqOiPresent.sch,v 1.9 2010/11/10 14:47:45 gemvx Exp $
s 4784 1008 100 0 Chris Mayer
s 4800 1216 100 0 Copyright
s 4784 1184 100 0 Observatory
s 4784 1152 100 0 Sciences Ltd.
s 5392 1120 100 0 Generate OIWFS "present" value
s 5472 1264 150 0 A&G Sequencer
s 3040 3952 100 0 This schematic outputs a "disable" value from the selected OIWFS.
s 3040 3920 100 0 The value is combined with the disable values from the HRWFS
s 3040 3888 100 0 the two PWFS and the Components controller to yield an overall
s 3040 3856 100 0 disable value that is used to switch on and off the heartbeat of the A&G
s 1568 3536 100 0 If the OIWFS selected is "NONE" then never
s 1568 3504 100 0 disable the heartbeat.
s 1456 3248 100 0 Note that we always claim all the OIWFS are loaded.
s 1456 3216 100 0 This is done because the selection of which
s 1456 3184 100 0 OIWFS value to use is actually controlled by the input to NVL
[cell use]
use agSeqSubsysPresent 2592 1255 100 0 agSeqSubsysPresent#28
xform 0 2912 1392
p 2688 1248 100 0 1 seta:subnam nifs
p 2688 1216 100 0 1 setb:top $(top)$(subnam)
p 2688 1184 100 0 1 setc:subsys $(nifs)sad:wfs:
p 2688 1152 100 0 1 setd:present $(subsys)heartBeat
use agSeqSubsysPresent 2592 2919 100 0 agSeqSubsysPresent#2
xform 0 2912 3056
p 2656 2912 100 0 1 seta:subnam gmos
p 2656 2880 100 0 1 setb:top $(top)$(subnam)
p 2656 2848 100 0 1 setc:subsys $(gmos)wfs:
p 2656 2816 100 0 1 setd:present $(subsys)present
use agSeqSubsysPresent 2592 2503 100 0 agSeqSubsysPresent#9
xform 0 2912 2640
p 2656 2496 100 0 1 seta:subnam nirs
p 2656 2464 100 0 1 setb:top $(top)$(subnam)
p 2656 2432 100 0 1 setc:subsys $(nirs)wfs:
p 2656 2400 100 0 1 setd:present $(subsys)heartBeat
use agSeqSubsysPresent 2592 2087 100 0 agSeqSubsysPresent#10
xform 0 2912 2224
p 2656 2080 100 0 1 seta:subnam niri
p 2656 2048 100 0 1 setb:top $(top)$(subnam)
p 2656 2016 100 0 1 setc:subsys $(niri)wfs:
p 2656 1984 100 0 1 setd:present $(subsys)heartBeat
use agSeqSubsysPresent 2592 1671 100 0 agSeqSubsysPresent#26
xform 0 2912 1808
p 2672 1648 100 0 1 seta:subnam f2
p 2672 1616 100 0 1 setb:top $(top)$(subnam)
p 2672 1584 100 0 1 setc:subsys $(f2)wfs:
p 2672 1552 100 0 1 setd:present $(subsys)present
use agSeqSubsysPresent 3584 2919 100 0 agSeqSubsysPresent#42
xform 0 3904 3056
p 3648 2912 100 0 1 seta:subnam nici
p 3648 2880 100 0 1 setb:top $(top)$(subnam)
p 3648 2848 100 0 1 setc:subsys $(nici)wfs:
p 3648 2816 100 0 1 setd:present $(subsys)present
use bd200tr 960 776 -100 0 frame
xform 0 3600 2480
use hwin 1952 3543 100 0 hwin#7
xform 0 2048 3584
p 1955 3576 100 0 -1 val(in):0
use hwin 1872 3271 100 0 hwin#23
xform 0 1968 3312
p 1875 3304 100 0 -1 val(in):1
use eais 2208 3207 100 0 enableOiwfsPresent
xform 0 2336 3280
p 2192 3360 100 0 -1 DESC:Enable the loaded flags
p 1952 3022 100 0 0 EGU:none
p 2272 3168 100 0 1 PINI:YES
use eaos 2208 3463 100 0 oiwfsNone
xform 0 2336 3552
p 2160 3648 100 0 -1 DESC:Disable value when OIWFS is NONE
p 2176 3278 100 0 0 EGU:units
p 1952 3534 100 0 0 OMSL:closed_loop
use outhier 6000 3463 100 0 DISV
xform 0 6016 3504
use esels 5568 3223 100 0 selectOiwfs
xform 0 5712 3488
p 5584 3776 100 0 -1 DESC:Select OIWFS
p 5728 3264 100 0 1 SCAN:1 second
p 5728 3296 100 0 1 SELM:Specified
p 5536 3680 75 1280 -1 pproc(INPA):PP
use inhier 1712 3671 100 0 OIWFS
xform 0 1728 3712
[comments]
