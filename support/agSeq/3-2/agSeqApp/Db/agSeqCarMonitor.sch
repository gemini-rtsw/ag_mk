[schematic2]
uniq 59
[tools]
[detail]
w 1224 875 100 0 ACTVAL elongins.elongins#55.VAL 1120 976 1184 976 1184 864 1312 864 outhier.ACTVAL.p
w 1288 1019 100 0 n#57 elongins.elongins#55.FLNK 1120 1008 1504 1008 efanouts.IssueStop.SLNK
w 2296 1643 100 0 n#19 eaos.ActIdle.OUT 2368 736 2592 736 2592 1632 2048 1632 2048 2032 junction
w 1970 1872 100 0 n#19 eaos.ActTimeoutErr.OUT 1808 1664 1968 1664 1968 2032 2224 2032 ecars.ecars#0.IVAL
w 2264 1611 100 0 n#18 estringouts.ActNullMess.OUT 2368 1040 2560 1040 2560 1600 2016 1600 2016 1968 junction
w 1992 1970 100 0 n#18 estringouts.ActTimeoutMess.OUT 1808 1968 2224 1968 ecars.ecars#0.IMSS
w 1904 1067 100 0 n#48 efanouts.IssueStop.LNK2 1744 1056 2112 1056 estringouts.ActNullMess.SLNK
w 2248 914 100 0 n#44 estringouts.ActNullMess.FLNK 2368 1072 2496 1072 2496 912 2048 912 2048 768 2112 768 eaos.ActIdle.SLNK
w 2040 802 100 0 n#43 hwin.hwin#47.in 2016 800 2112 800 eaos.ActIdle.DOL
w 1214 1483 100 0 n#8 efanouts.IssueStop.LNK1 1744 1088 1872 1088 1872 1472 592 1472 592 1728 junction
w 526 1730 100 0 n#8 eaos.StopTimer.FLNK 432 1728 656 1728 agSeqTimeOut.agSeqTimeOut#4.STOP
w 2712 1819 -100 0 FLNK ecars.ecars#0.FLNK 2544 1808 2928 1808 outhier.FLNK.p
w 2712 1970 100 0 n#25 ecars.ecars#0.OMSS 2544 1968 2928 1968 outhier.CSOMSS.p
w 2712 2034 100 0 n#24 ecars.ecars#0.VAL 2544 2032 2928 2032 outhier.CSVAL.p
w 1688 1842 100 0 n#17 estringouts.ActTimeoutMess.FLNK 1808 2000 1936 2000 1936 1840 1488 1840 1488 1696 1552 1696 eaos.ActTimeoutErr.SLNK
w 1368 1986 100 0 n#16 agSeqTimeOut.agSeqTimeOut#4.EXPIRED 1104 1920 1232 1920 1232 1984 1552 1984 estringouts.ActTimeoutMess.SLNK
w 1480 1730 100 0 n#15 hwin.hwin#14.in 1456 1728 1552 1728 eaos.ActTimeoutErr.DOL
w 494 1986 100 0 n#7 eaos.StartTimer.FLNK 432 1984 592 1984 592 1920 656 1920 agSeqTimeOut.agSeqTimeOut#4.START
s 2432 2336 100 0 $Id: agSeqCarMonitor.sch,v 1.3 2001/09/20 15:12:14 ajf Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2672 80 100 0 Combine A&G subsys CAR values
[cell use]
use elongins 864 919 100 0 elongins#55
xform 0 992 992
p 928 1064 100 0 1 DESC:Monitor activeC
p 560 1032 100 0 -1 def(INP):$(prefix)$(recname)
p 976 912 100 1024 -1 name:$(top)actWait
p 832 1024 75 1280 -1 pproc(INP):CPP
use hwin 1848 760 100 0 hwin#47
xform 0 1920 800
p 1827 792 100 0 -1 val(in):$(CAR_IDLE)
use hwin 1288 1688 100 0 hwin#14
xform 0 1360 1728
p 1267 1720 100 0 -1 val(in):$(CAR_ERROR)
use eaos 2136 680 100 0 ActIdle
xform 0 2240 768
p 2144 864 100 0 -1 DESC:Output idle status
p 1856 750 100 0 0 OMSL:closed_loop
p 2368 736 75 768 -1 pproc(OUT):PP
use eaos 200 1864 100 0 StartTimer
xform 0 304 1952
p 160 2030 100 0 -1 DESC:Dummy record to trigger Start
use eaos 200 1608 100 0 StopTimer
xform 0 304 1696
p 160 1774 100 0 -1 DESC:Dummy record to trigger Stop
use eaos 1576 1608 100 0 ActTimeoutErr
xform 0 1680 1696
p 1568 1790 100 0 -1 DESC:Output error status
p 1296 1678 100 0 0 OMSL:closed_loop
p 1808 1664 75 768 -1 pproc(OUT):PP
use estringouts 2136 984 100 0 ActNullMess
xform 0 2240 1056
p 2128 1136 100 0 -1 DESC:Output null string
p 2048 1022 100 0 0 VAL:string
use estringouts 1576 1912 100 0 ActTimeoutMess
xform 0 1680 1984
p 1568 2078 100 0 -1 DESC:Output time out string
p 1488 1950 100 0 0 VAL:$(subsys) timed out
use outhier 2920 1768 100 0 FLNK
xform 0 2912 1808
use outhier 2920 1992 100 0 CSVAL
xform 0 2912 2032
use outhier 2920 1928 100 0 CSOMSS
xform 0 2912 1968
use outhier 1304 824 100 0 ACTVAL
xform 0 1296 864
use agSeqTimeOut 680 1672 100 0 agSeqTimeOut#4
xform 0 880 1824
p 720 1662 100 0 1 seta:timeout 6.0
use efanouts 1528 872 100 0 IssueStop
xform 0 1624 1024
p 1488 928 100 0 1 SELM:All
use ecars 2248 1752 100 0 ecars#0
xform 0 2384 1920
p 2288 2094 100 0 -1 DESC:Command sent CAR
p 2332 1744 100 1024 1 name:$(ag)$(subsys)CommSentC
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
