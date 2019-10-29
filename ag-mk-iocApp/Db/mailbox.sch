[schematic2]
uniq 72
[tools]
[detail]
w 808 1803 100 0 n#71 estringouts.estringouts#63.FLNK 1008 1744 1056 1744 1056 1792 608 1792 608 2000 752 2000 estringins.mailbox.SLNK
w 1000 1715 100 0 n#65 hwout.hwout#64.outp 1040 1712 1008 1712 estringouts.estringouts#63.OUT
w 672 2034 100 0 n#34 hwin.hwin#33.in 640 2032 752 2032 estringins.mailbox.INP
s 1936 352 500 512 mailbox.sch
[cell use]
use hwout 1040 1671 100 0 hwout#64
xform 0 1136 1712
p 1136 1664 100 0 -1 val(outp):$(top)mailbox.VAL
use estringouts 752 1655 100 0 estringouts#63
xform 0 880 1728
p 816 1584 100 0 1 DTYP:Soft Channel
p 816 1616 100 0 1 SCAN:Passive
p 816 1552 100 0 1 VAL:empty
p 928 1648 100 1024 1 name:$(top)mailboxin
use bc200tr -544 168 -100 0 frame
xform 0 1136 1472
p 2032 336 100 0 1 author:O.Frischmuth
p 2256 320 100 0 -1 border:C
p 2032 304 100 0 1 checked:O.Frischmuth
p 2288 320 100 0 -1 date:22 Jul 97
p 2256 448 100 0 -1 project:A&G unit
p 2256 384 100 0 -1 title:PMAC mailbox schematic
use hwin 472 1992 100 0 hwin#33
xform 0 544 2032
p 448 1984 100 0 -1 val(in):#C$(c) S2
use estringins 832 1968 100 0 mailbox
xform 0 880 2000
p 816 1856 100 0 1 DTYP:PMAC-VME ASCII
p 816 1888 100 0 1 SCAN:Passive
p 816 1824 100 0 1 VAL:unused (for now)
p 816 1918 100 0 1 name:$(top)mailbox
[comments]
