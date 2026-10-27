[schematic2]
uniq 81
[tools]
[detail]
w 1816 1579 100 0 n#80 elongouts.softCVal.FLNK 1984 1408 2048 1408 2048 1568 1632 1568 1632 1744 1728 1744 estringouts.softCMess.SLNK
w 2216 1707 100 0 n#76 elongouts.softCVal.OUT 1984 1344 2144 1344 2144 1696 2336 1696 ecars.activeC.IVAL
w 2200 1643 100 0 n#75 estringouts.softCMess.OUT 1984 1728 2112 1728 2112 1632 2336 1632 ecars.activeC.IMSS
w 2808 715 100 0 n#67 ecalcs.incr.VAL 2656 704 3008 704 outhier.SELN.p
w 2240 907 100 0 n#65 inhier.OIWFS.P 2160 896 2368 896 ecalcs.incr.INPA
w 2752 1707 100 0 n#27 ecars.activeC.VAL 2656 1696 2896 1696 outhier.CAR.p
w 2752 1643 100 0 n#26 ecars.activeC.OMSS 2656 1632 2896 1632 outhier.MESS.p
w 2752 1483 100 0 n#25 ecars.activeC.FLNK 2656 1472 2896 1472 outhier.FLNK.p
s 512 416 100 0 to when the OIWFS selected is NONE.
s 512 448 100 0 This is the CAR record which is written
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsCar.sch,v 1.3 2007/05/18 22:29:21 pedro Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Combine OIWFS CAR values
s 1152 2272 100 0 The purpose of this schematic is to emulate the behaviour of the real
s 1152 2240 100 0 OIWFS systems when the selected OIWFS is set to NONE
s 2048 288 100 0 This record simply increments the OIWFS number
s 2048 256 100 0 so as to provide an index for a selection record
[cell use]
use ecars 576 615 100 0 softC
xform 0 736 784
p 608 960 100 0 -1 DESC:CAR record used when OIWFS is NONE
p 688 608 100 1024 0 name:$(ag)none:$(I)
use ecars 2336 1415 100 0 activeC
xform 0 2496 1584
p 2368 1760 100 0 -1 DESC:Generic OIWFS CAR record
p 2448 1408 100 1024 0 name:$(top)$(I)
use estringouts 1728 1671 100 0 softCMess
xform 0 1856 1744
p 1696 1840 100 0 -1 DESC:Message from softC CAR record
p 1664 1550 100 0 0 OMSL:closed_loop
p 1664 1710 100 0 0 VAL:
p 1392 1776 100 0 -1 def(DOL):$(ag)none:softC.OMSS
p 1984 1728 75 768 -1 pproc(OUT):PP
use elongouts 1728 1287 100 0 softCVal
xform 0 1856 1376
p 1744 1488 100 0 -1 DESC:Value of $(ag):none:softC
p 1568 1294 100 0 0 OMSL:closed_loop
p 1440 1408 100 0 -1 def(DOL):$(ag)none:softC
p 1696 1408 75 1280 -1 pproc(DOL):CPP
p 1984 1344 75 768 -1 pproc(OUT):NPP
use outhier 2864 1431 100 0 FLNK
xform 0 2880 1472
use outhier 2864 1591 100 0 MESS
xform 0 2880 1632
use outhier 2864 1655 100 0 CAR
xform 0 2880 1696
use outhier 2976 663 100 0 SELN
xform 0 2992 704
use ecalcs 2368 423 100 0 incr
xform 0 2512 688
p 2464 608 100 0 1 CALC:A+1
p 2161 854 100 0 0 DESC:Increment OIWFS index
use inhier 2144 855 100 0 OIWFS
xform 0 2160 896
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
