[schematic2]
uniq 16
[tools]
[detail]
w 696 555 100 0 n#15 telDummySysCad.telDummySysCad#5.FLNK 672 544 768 544 junction
w 696 811 100 0 n#15 telDummySysCad.telDummySysCad#4.FLNK 672 800 768 800 junction
w 696 1067 100 0 n#15 telDummySysCad.telDummySysCad#3.FLNK 672 1056 768 1056 768 320 junction
w 216 555 100 0 n#15 telDummySysCad.telDummySysCad#2.FLNK 192 544 288 544 junction
w 216 811 100 0 n#15 telDummySysCad.telDummySysCad#1.FLNK 192 800 288 800 junction
w 696 331 100 0 n#15 telDummySysCad.telDummySysCad#0.FLNK 192 1056 288 1056 288 320 1152 320 eseqs.eseqs#7.SLNK
w 1496 331 100 0 n#14 eseqs.eseqs#7.FLNK 1472 320 1568 320 1568 448 1664 448 ecars.ecars#6.SLNK
w 1496 619 100 0 n#13 eseqs.eseqs#7.LNK2 1472 608 1568 608 1568 640 junction
w 1544 651 100 0 n#13 eseqs.eseqs#7.LNK1 1472 640 1664 640 ecars.ecars#6.IVAL
w 1156 603 100 2 n#11 hwin.hwin#10.in 1152 608 1152 608 eseqs.eseqs#7.DOL2
w 1156 635 100 2 n#9 hwin.hwin#8.in 1152 640 1152 640 eseqs.eseqs#7.DOL1
[cell use]
use hwin 960 567 100 0 hwin#10
xform 0 1056 608
p 963 600 100 0 -1 val(in):IDLE
use hwin 960 599 100 0 hwin#8
xform 0 1056 640
p 963 632 100 0 -1 val(in):BUSY
use eseqs 1152 231 100 0 eseqs#7
xform 0 1312 480
p 768 -1668 100 0 0 DLY1:2
p 768 -1700 100 0 0 DLY2:0
p 768 -1732 100 0 0 DLY3:0.0e+00
p 1264 224 100 1024 -1 name:$(sys)seqCar
use ecars 1664 359 100 0 ecars#6
xform 0 1824 528
p 1776 352 100 1024 -1 name:$(sys)activeC
use telDummySysCad -32 999 100 0 telDummySysCad#0
xform 0 64 1104
p -64 992 100 0 1 setc:cmd init
use telDummySysCad -32 743 100 0 telDummySysCad#1
xform 0 64 848
p -64 736 100 0 1 setc:cmd debug
use telDummySysCad -32 487 100 0 telDummySysCad#2
xform 0 64 592
p -64 480 100 0 1 setc:cmd datum
use telDummySysCad 448 999 100 0 telDummySysCad#3
xform 0 544 1104
p 416 992 100 0 1 setc:cmd test
use telDummySysCad 448 743 100 0 telDummySysCad#4
xform 0 544 848
p 416 736 100 0 1 setc:cmd reboot
use telDummySysCad 448 487 100 0 telDummySysCad#5
xform 0 544 592
p 416 480 100 0 1 setc:cmd park
use bb200tr -416 -152 -100 0 frame
xform 0 864 672
[comments]
