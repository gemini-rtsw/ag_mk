[schematic2]
uniq 85
[tools]
[detail]
w 1896 971 100 0 n#84 hwin.hwin#83.in 1792 1056 1856 1056 1856 960 1984 960 elongouts.parkTrigger.DOL
w 1688 939 100 0 n#82 ecad4.ecad4#71.STLK 1440 928 1984 928 elongouts.parkTrigger.SLNK
w 2440 907 100 0 n#81 elongouts.parkTrigger.OUT 2240 896 2688 896 outhier.c#76.p
w 896 1131 100 0 n#75 inhier.OIWFS.P 720 1120 1120 1120 ecad4.ecad4#71.INPD
s 928 1984 200 0 command.
s 928 2048 200 0 a means of triggering the relevant part of that global
s 928 2112 200 0 by the global park command. This schematic simply provides
s 928 2176 200 0 This schematic is very simple as the real work is done
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsParkCad.sch,v 1.1 2003/02/07 16:51:31 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2688 80 100 0 OIWFS specific CAD record
[cell use]
use hwin 1600 1015 100 0 hwin#83
xform 0 1696 1056
p 1603 1048 100 0 -1 val(in):1
use elongouts 1984 839 100 0 parkTrigger
xform 0 2112 928
p 1968 1056 100 0 -1 DESC:Trigger park processing
p 1824 846 100 0 0 OMSL:closed_loop
p 2336 928 100 0 -1 def(OUT):$(ag)oiparkActCTrigger.PROC
p 2240 896 75 768 -1 pproc(OUT):PP
use outhier 2656 855 100 0 c#76
xform 0 2672 896
use inhier 704 1079 100 0 OIWFS
xform 0 720 1120
use ecad4 1120 839 100 0 ecad4#71
xform 0 1280 1216
p 1136 1600 100 0 -1 DESC:A&G Sequencer OIWFS CAD
p 1200 784 100 0 1 SNAM:$(snam)
p 1648 960 100 0 0 def(STLK):0.0
p 1232 832 100 1024 1 name:$(ag)oi:$(cad)
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
