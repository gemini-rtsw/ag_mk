[schematic2]
uniq 80
[tools]
[detail]
w 1256 923 100 0 n#79 inhier.SLNK.P 1104 912 1456 912 1456 1488 1712 1488 agSeqOiwfsDcCad.agSeqOiwfsDcCad#76.SLNK
w 1528 1563 100 0 n#78 inhier.INPB.P 1104 1136 1392 1136 1392 1552 1712 1552 agSeqOiwfsDcCad.agSeqOiwfsDcCad#76.INPB
w 1504 1627 100 0 n#77 inhier.INPA.P 1104 1360 1344 1360 1344 1616 1712 1616 agSeqOiwfsDcCad.agSeqOiwfsDcCad#76.INPA
w 1416 1691 100 0 n#69 elongouts.oiMask.VAL 944 1776 1168 1776 1168 1680 1712 1680 agSeqOiwfsDcCad.agSeqOiwfsDcCad#76.MASK
w 616 1819 100 0 n#68 hwin.hwin#67.in 592 1808 688 1808 elongouts.oiMask.DOL
w 1616 1755 100 0 n#59 inhier.OIWFS.P 1568 1744 1712 1744 agSeqOiwfsDcCad.agSeqOiwfsDcCad#76.OIWFS
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 528 1552 100 0 implement a particular command.
s 528 1584 100 0 specific WFS if they don't 
s 528 1616 100 0 This mask is used to disable
s 2432 2336 100 0 $Id: agSeqOiwfsDcOnlyCad.sch,v 1.2 2005/10/04 14:16:43 anunez Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2688 80 100 0 OIWFS specific CAD record
s 528 1488 100 0 A OIWFS that does not implement a
s 528 1456 100 0 command should set its bit to zero.
[cell use]
use inhier 1088 871 100 0 SLNK
xform 0 1104 912
use inhier 1088 1095 100 0 INPB
xform 0 1104 1136
use inhier 1088 1319 100 0 INPA
xform 0 1104 1360
use inhier 1552 1703 100 0 OIWFS
xform 0 1568 1744
use agSeqOiwfsDcCad 1712 1431 100 0 agSeqOiwfsDcCad#76
xform 0 2016 1632
p 1732 1404 100 0 1 seta:dev $(cad):dccad:
use hwin 400 1767 100 0 hwin#67
xform 0 496 1808
p 403 1800 100 0 -1 val(in):$(mask)
use elongouts 688 1687 100 0 oiMask
xform 0 816 1776
p 736 1872 100 0 -1 DESC:Mask for OIWFS
p 528 1694 100 0 0 OMSL:closed_loop
p 800 1680 100 1024 0 name:$(top)$(cad):$(I)
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
