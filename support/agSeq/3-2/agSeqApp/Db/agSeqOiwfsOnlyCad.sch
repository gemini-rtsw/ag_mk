[schematic2]
uniq 102
[tools]
[detail]
w 452 315 100 2 n#101 hwin.hwin#100.in 448 320 448 320 ecad8.ecad8#76.INPH
w 264 587 100 0 OIWFS inhier.OIWFS.P 128 576 448 576 ecad8.ecad8#76.INPD
w 452 379 100 2 n#98 hwin.hwin#97.in 448 384 448 384 ecad8.ecad8#76.INPG
w 452 443 100 2 n#96 hwin.hwin#95.in 448 448 448 448 ecad8.ecad8#76.INPF
w 452 507 100 2 n#94 hwin.hwin#93.in 448 512 448 512 ecad8.ecad8#76.INPE
w 1432 1563 100 0 n#74 ecad8.ecad8#76.VALB 768 736 1200 736 1200 1552 1712 1552 agSeqOiwfsCad.agSeqOiwfsCad#54.INPB
w 1416 1627 100 0 n#73 ecad8.ecad8#76.VALA 768 800 1168 800 1168 1616 1712 1616 agSeqOiwfsCad.agSeqOiwfsCad#54.INPA
w 1032 139 100 0 n#72 ecad8.ecad8#76.STLK 768 128 1344 128 1344 1488 1712 1488 agSeqOiwfsCad.agSeqOiwfsCad#54.SLNK
w 1416 1691 100 0 n#69 elongouts.oiMask.VAL 944 1776 1168 1776 1168 1680 1712 1680 agSeqOiwfsCad.agSeqOiwfsCad#54.MASK
w 616 1819 100 0 n#68 hwin.hwin#67.in 592 1808 688 1808 elongouts.oiMask.DOL
w 1616 1755 100 0 n#59 inhier.OIWFS.P 1568 1744 1712 1744 agSeqOiwfsCad.agSeqOiwfsCad#54.OIWFS
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 528 1552 100 0 implement a particular command.
s 528 1584 100 0 specific WFS if they don't 
s 528 1616 100 0 This mask is used to disable
s 2432 2336 100 0 $Id: agSeqOiwfsOnlyCad.sch,v 1.3 2005/10/04 14:16:43 anunez Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2688 80 100 0 OIWFS specific CAD record
s 528 1488 100 0 A OIWFS that does not implement a
s 528 1456 100 0 command should set its bit to zero.
[cell use]
use hwin 256 279 100 0 hwin#100
xform 0 352 320
p 144 320 100 0 -1 val(in):$(ag)oiwfsSel.VALF
use hwin 256 343 100 0 hwin#97
xform 0 352 384
p 259 376 100 0 -1 val(in):$(ag)tweakZ
use hwin 256 407 100 0 hwin#95
xform 0 352 448
p 259 440 100 0 -1 val(in):$(ag)tweakY
use hwin 256 471 100 0 hwin#93
xform 0 352 512
p 259 504 100 0 -1 val(in):$(ag)tweakX
use hwin 400 1767 100 0 hwin#67
xform 0 496 1808
p 403 1800 100 0 -1 val(in):$(mask)
use inhier 112 535 100 0 OIWFS
xform 0 128 576
use inhier 1552 1703 100 0 OIWFS
xform 0 1568 1744
use ecad8 448 39 100 0 ecad8#76
xform 0 608 544
p 480 1056 100 0 -1 DESC:A&G Sequencer OIWFS CAD
p 544 608 100 0 0 FTVE:DOUBLE
p 544 576 100 0 0 FTVF:DOUBLE
p 544 544 100 0 0 FTVG:DOUBLE
p 464 0 100 0 1 SNAM:$(snam)
p 560 32 100 1024 1 name:$(ag)oi:$(cad)
use elongouts 688 1687 100 0 oiMask
xform 0 816 1776
p 736 1872 100 0 -1 DESC:Mask for OIWFS
p 528 1694 100 0 0 OMSL:closed_loop
p 800 1680 100 1024 0 name:$(top)$(cad):$(I)
use agSeqOiwfsCad 1712 1431 100 0 agSeqOiwfsCad#54
xform 0 2016 1632
p 1732 1404 100 0 1 seta:dev oi:$(cad):
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
