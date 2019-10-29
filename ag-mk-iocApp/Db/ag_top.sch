[schematic2]
uniq 1
[tools]
[detail]
s 1568 2368 100 0 $Id: ag_top.sch,v 1.9 2001/09/19 13:51:55 ajf Exp $
s 976 112 100 0 contains the GIS interface
s -704 688 100 0 PMAC Global Mailbox
s 2176 256 500 512 ag_top.sch
s -720 2144 500 0 Top level A&G Components Controller schematic
s -704 896 100 0 PMAC Global Mailbox
s 976 144 100 0 counter torques to the torque PLC prog,
s 976 80 100 0 and refreshes the tolerance copies in DPRAM.
s 976 176 100 0 this subsheet applies calculated
n 1696 448 2128 784 100
This is the top level schematic for the
A&G unit
Components Controller.
.
It contains no srcbase records, but
defines the following macro variables
and includes the "hrwfs" and "ag" schematic:
.
top    = Top level record name prefix.
.
sadtop = Status/Alarm Database prefix.
.
.
.
_
[cell use]
use bc200tr -1024 -104 -100 0 Frame
xform 0 656 1200
p 1552 64 100 0 1 author:O.Frischmuth
p 1776 48 100 0 -1 border:C
p 1552 32 100 0 1 checked:O.Frischmuth
p 1808 48 100 0 -1 date:12 May 97
p 1792 176 100 0 -1 project:A&G unit
p 1792 112 100 0 -1 title:Top level schematic
use encrelay -720 967 100 0 encrelay#53
xform 0 -600 1024
p -720 960 100 0 1 set1:top ${hrwfs}
use specials 1152 343 100 0 specials#52
xform 0 1272 400
p 1152 336 100 0 1 set1:top ${ag}
p 1152 304 100 0 1 set2:top2 ${ag}cc:
p 1152 272 100 0 1 set3:top3 ${hrwfs}cc:
use mailbox -720 583 100 0 mailbox#46
xform 0 -600 640
p -720 576 100 0 1 set0:top ${ag}cc:pmac2
p -720 544 100 0 1 set3:c 1
use mailbox -720 775 100 0 mailbox#45
xform 0 -600 832
p -720 768 100 0 1 set0:top ${ag}cc:pmac1
p -720 736 100 0 1 set3:c 0
use notes -880 103 100 0 notes#44
xform 0 -624 288
p -852 414 100 0 -1 COMMENT1:if a record has a "PV" property,
p -852 382 100 0 -1 COMMENT2:the record's label is taken automatically
p -852 352 100 0 -1 COMMENT3:instead of the "name" property!!
p -852 320 100 0 -1 COMMENT4:Attention! if using of "name" is desired.
use timesyst 1360 480 100 0 timesyst#38
xform 0 1272 528
p 1152 464 100 0 1 set1:top ${ag}cc:
use pmacUpDown 0 343 100 0 pmacUpDown#54
xform 0 328 432
p 0 336 100 0 1 set1:top ${ag}cc:
p 240 336 100 0 1 set2:axis pmac1
p 432 336 100 0 1 set3:schematic UpDown
p 0 304 100 0 1 set4:BUSY 1
p 240 304 100 0 1 set5:CARD 0
use pmacUpDown 0 103 100 0 pmacUpDown#55
xform 0 328 192
p 0 96 100 0 1 set1:top ${ag}cc:
p 240 96 100 0 1 set2:axis pmac2
p 432 96 100 0 1 set3:schematic UpDown
p 0 64 100 0 1 set4:BUSY 1
p 240 64 100 0 1 set5:CARD 1
use gbd 800 1280 100 0 gbd
xform 0 1168 1504
p 720 1168 100 0 1 set1:top ${ag}
p 1248 1168 100 0 1 set10:ccdatmDIR ${ag}cc:datum.DIR
p 1248 1136 100 0 1 set11:ccparkDIR ${ag}cc:park.DIR
p 1248 1104 100 0 1 set12:cctestDIR ${ag}cc:test.DIR
p 720 1136 100 0 1 set2:systop ${ag}cc:
p 720 1104 100 0 1 set3:sadtop ${ag}
p 720 1072 100 0 1 set4:cartop ${ag}cc:
p 720 1040 100 0 1 set5:ftop ag_
p 1024 1168 100 0 1 set6:parkevnr 1
p 1024 1136 100 0 1 set7:datmevnr 2
p 1024 1104 100 0 1 set8:testevnr 3
p 1024 1072 100 0 1 set9:car2evnr 4
p 1024 1040 100 0 1 seta:ag ${ag}
p 720 1008 100 0 1 setb:cadtop ${ag}
use hrwfs -288 1264 100 0 hrwfs
xform 0 80 1504
p -400 1184 100 0 1 set1:top ${hrwfs}
p 144 1184 100 0 1 set10:ccdatmDIR ${hrwfs}cc:datum.DIR
p 144 1152 100 0 1 set11:ccparkDIR ${hrwfs}cc:park.DIR
p 144 1120 100 0 1 set12:cctestDIR ${hrwfs}cc:test.DIR
p -400 1152 100 0 1 set2:systop ${hrwfs}cc:
p -400 1120 100 0 1 set3:sadtop ${hrwfs}
p -400 1088 100 0 1 set4:cartop ${hrwfs}cc:
p -400 1056 100 0 1 set5:ftop hrwfs_
p -96 1184 100 0 1 set6:parkevnr 6
p -96 1152 100 0 1 set7:datmevnr 7
p -96 1120 100 0 1 set8:testevnr 8
p -96 1088 100 0 1 set9:car2evnr 9
p -96 1056 100 0 1 seta:ag ${ag}
p -400 1024 100 0 1 setb:cadtop ${hrwfs}cc:
[comments]
