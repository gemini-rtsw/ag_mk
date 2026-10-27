[schematic2]
uniq 215
[tools]
[detail]
w 3010 2603 100 0 n#196 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#202.FOLLOWS 3008 2592 3072 2592 3072 2784 junction
w 2242 1451 100 0 n#196 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#200.FOLLOWS 2208 1440 2336 1440 junction
w 2242 1835 100 0 n#196 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#199.FOLLOWS 2208 1824 2336 1824 junction
w 2242 2219 100 0 n#196 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#198.FOLLOWS 2208 2208 2336 2208 junction
w 2242 2603 100 0 n#196 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#197.FOLLOWS 2208 2592 2336 2592 junction
w 2242 1067 100 0 n#196 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#201.FOLLOWS 2208 1056 2336 1056 2336 2784 junction
w 3154 2795 100 0 n#196 estringouts.none.OUT 2048 2784 4320 2784 estringouts.followS.SLNK
w 1970 715 100 0 n#214 superfout.fan.LNK7 1184 2144 1600 2144 1600 704 2400 704 2400 2432 2592 2432 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#202.SLNK
w 1378 2187 100 0 n#213 superfout.fan.LNK6 1184 2176 1632 2176 1632 896 1792 896 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#201.SLNK
w 1394 2219 100 0 n#211 superfout.fan.LNK5 1184 2208 1664 2208 1664 1280 1792 1280 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#200.SLNK
w 1410 2251 100 0 n#210 superfout.fan.LNK4 1184 2240 1696 2240 1696 1664 1792 1664 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#199.SLNK
w 1426 2283 100 0 n#209 superfout.fan.LNK3 1184 2272 1728 2272 1728 2048 1792 2048 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#198.SLNK
w 1506 2443 100 0 n#206 superfout.fan.LNK2 1184 2304 1280 2304 1280 2432 1792 2432 agSeqOiwfsFollow2FollowS.agSeqOiwfsFollow2FollowS#197.SLNK
w 1490 2811 100 0 n#205 superfout.fan.LNK1 1184 2336 1248 2336 1248 2800 1792 2800 estringouts.none.SLNK
w 722 2139 100 0 n#189 ecalcs.incr.VAL 736 2128 768 2128 768 2272 superfout.fan.SELL
w 714 2171 100 0 n#188 ecalcs.incr.FLNK 736 2160 752 2160 752 2048 768 2048 superfout.fan.SLNK
w 1594 2843 100 0 n#120 inhier.NONE.P 1456 2832 1792 2832 estringouts.none.DOL
w 282 2331 100 0 n#115 inhier.OIWFS.P 176 2320 448 2320 ecalcs.incr.INPA
s 3632 3104 100 0 $Id: agSeqOiwfsFollowS.sch,v 1.11 2007/07/06 22:53:07 pedro Exp $
s 3616 240 100 0 Sciences Ltd.
s 3616 272 100 0 Observatory
s 3616 304 100 0 Copyright
s 4272 368 200 0 A&G Sequencer
s 3632 96 100 0 Chris Mayer
s 4192 208 200 0 Fetch OIWFS follow status
[cell use]
use agSeqOiwfsFollow2FollowS 2592 2375 100 0 agSeqOiwfsFollow2FollowS#202
xform 0 2800 2512
p 2656 2368 100 0 1 seta:subsys nici
p 2656 2336 100 0 1 setb:snam agSeqGmosFollowS
p 2656 2304 100 0 1 setf:follow $(nici)wfs:FollowL
use agSeqOiwfsFollow2FollowS 1792 839 100 0 agSeqOiwfsFollow2FollowS#201
xform 0 2000 976
p 1856 832 100 0 1 seta:subsys nifs
p 1856 800 100 0 1 setb:snam agSeqOiwfsFollowS
p 1856 768 100 0 1 setf:follow $(nifs)sad:wfs:folIsFollow
use agSeqOiwfsFollow2FollowS 1792 1223 100 0 agSeqOiwfsFollow2FollowS#200
xform 0 2000 1360
p 1856 1216 100 0 1 seta:subsys f2
p 1856 1184 100 0 1 setb:snam agSeqGmosFollowS
p 1856 1152 100 0 1 setf:follow $(f2)wfs:followS
use agSeqOiwfsFollow2FollowS 1792 1607 100 0 agSeqOiwfsFollow2FollowS#199
xform 0 2000 1744
p 1856 1600 100 0 1 seta:subsys niri
p 1856 1568 100 0 1 setb:snam agSeqOiwfsFollowS
p 1856 1536 100 0 1 setf:follow $(niri)wfs:folIsFollow
use agSeqOiwfsFollow2FollowS 1792 1991 100 0 agSeqOiwfsFollow2FollowS#198
xform 0 2000 2128
p 1856 1984 100 0 1 seta:subsys nirs
p 1856 1952 100 0 1 setb:snam agSeqOiwfsFollowS
p 1856 1920 100 0 1 setf:follow $(nirs)wfs:folIsFollow
use agSeqOiwfsFollow2FollowS 1792 2375 100 0 agSeqOiwfsFollow2FollowS#197
xform 0 2000 2512
p 1856 2368 100 0 1 seta:subsys gmos
p 1856 2336 100 0 1 setb:snam agSeqGmosFollowS
p 1856 2304 100 0 1 setf:follow $(gmos)wfs:followS
use inhier 160 2279 100 0 OIWFS
xform 0 176 2320
use inhier 1424 2864 100 0 NONE
xform 0 1456 2832
use superfout 864 1936 100 0 fan
xform 0 976 2176
use bd200tr -160 -136 -100 0 frame
xform 0 2480 1568
use ecalcs 448 1847 100 0 incr
xform 0 592 2112
p 560 2032 100 0 1 CALC:A+1
p 416 2400 100 0 -1 DESC:Increment OIWFS index
p 560 1856 100 0 1 SCAN:1 second
use estringouts 4320 2711 100 0 followS
xform 0 4448 2784
p 4352 2864 100 0 -1 DESC:Following state
p 4256 2750 100 0 0 VAL:Off
p 4432 2704 100 1024 0 name:$(ag)oi:$(I)
use estringouts 1792 2727 100 0 none
xform 0 1920 2800
p 1808 2896 100 0 -1 DESC:State of None OIWFS
p 1728 2606 100 0 0 OMSL:closed_loop
p 1728 2766 100 0 0 VAL:Off
p 1536 2848 100 0 -1 def(DOL):$(ag)noRecord
p 1792 2832 75 1280 -1 palrm(DOL):MS
p 2080 2784 75 768 -1 palrm(OUT):MS
p 2048 2784 75 768 -1 pproc(OUT):PP
[comments]
