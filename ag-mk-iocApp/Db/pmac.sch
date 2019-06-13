[schematic2]
uniq 214
[tools]
[detail]
s -592 448 100 0 PMAC Global Mailbox
s 2304 304 500 512 something.sch
[cell use]
use ecars -328 1400 100 0 ecars#213
xform 0 -192 1568
p -240 1392 100 1024 -1 name:$(top)logDataC
use mailbox -608 471 100 0 mailbox#211
xform 0 -488 528
use pmacGlobalStatus 456 1392 100 0 pmacGlobalStatus#203
xform 0 800 1648
p 496 1540 200 0 1 seta:ADDRESS1 X:$0003
p 496 1476 200 0 1 setb:ADDRESS2 Y:$0003
use pmacCSStatus 456 1960 100 0 pmacCSStatus#202
xform 0 800 2216
p 448 2084 200 0 1 seta:ADDRESS1 Y:$D0B8
p 448 2020 200 0 1 setb:ADDRESS2 Y:$D0CB
p 448 1972 200 0 1 setc:NUM 2:
use pmacGeneral -568 1824 100 0 pmacGeneral#201
xform 0 -224 2080
p -544 1956 200 0 1 seta:motor 1
p -544 1892 200 0 1 setb:SETSC_ADDR_SIC Y:$07F1
p -572 1797 100 0 1 setc:BUSY 2
use bc200tr -944 -56 -100 0 frame
xform 0 736 1248
p 1616 112 100 0 1 author:O.Frischmuth
p 1856 96 100 0 -1 border:C
p 1616 80 100 0 1 checked:O.Frischmuth
p 1888 112 100 0 -1 date:12 May 97
p -944 -56 100 0 0 id:frame
p -944 -32 100 0 0 model:frame
p 2140 100 100 1792 -1 page: 
p 1984 64 100 0 1 pagenum:
p 1888 224 100 0 1 project:A&G unit
p -944 -8 100 0 0 revision:2.2
p 1872 160 100 0 1 title:GBD CC - PWFS1/2
[comments]
