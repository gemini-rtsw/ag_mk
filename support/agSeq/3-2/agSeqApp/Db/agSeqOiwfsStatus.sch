[schematic2]
uniq 102
[tools]
[detail]
w 242 2059 100 0 OIWFS junction 224 1728 224 2048 320 2048 agSeqOiwfsLimits.agSeqOiwfsLimits#82.OIWFS
w 912 1211 100 0 OIWFS junction 896 1728 896 1200 976 1200 agSeqOiwfsFollowS.agSeqOiwfsFollowS#87.OIWFS
w 904 267 100 0 OIWFS junction 896 1200 896 256 960 256 agSeqOiwfsaoOffset.agSeqOiwfsaoOffset#98.OIWFS
w 1650 1211 100 0 OIWFS junction 1632 1200 1728 1200 agSeqOiwfsFldStop.agSeqOiwfsFldStop#84.OIWFS
w 1650 603 100 0 OIWFS junction 1632 592 1728 592 agSeqOiwfsCoeffs.agSeqOiwfsCoeffs#91.OIWFS
w 1650 267 100 0 OIWFS junction 1632 1728 1632 256 1728 256 agSeqOiwfsProbe.agSeqOiwfsProbe#99.OIWFS
w 1656 2059 100 0 OIWFS junction 1632 1728 1632 2048 1728 2048 agSeqOiwfsFocus.agSeqOiwfsFocus#80.OIWFS
w 2314 2059 100 0 OIWFS junction 2320 1728 2320 2048 2368 2048 agSeqOiwfsXY.agSeqOiwfsXY#78.OIWFS
w 2320 1211 100 0 OIWFS inhier.OIWFS.P 112 1728 2320 1728 2320 1200 2368 1200 agSeqOiwfsFilter.agSeqOiwfsFilter#83.OIWFS
w 906 2059 100 0 OIWFS junction 896 1728 896 2048 976 2048 agSeqOiwfsTrackId.agSeqOiwfsTrackId#81.OIWFS
w 248 603 100 0 OIWFS junction 224 1200 224 592 320 592 agSeqProbeOffset.agSeqProbeOffset#89.OIWFS
w 248 1211 100 0 OIWFS junction 224 1728 224 1200 320 1200 agSeqOiwfsName.agSeqOiwfsName#88.OIWFS
w 248 267 100 0 OIWFS junction 224 592 224 256 320 256 agSeqOiwfsZoffset.agSeqOiwfsZoffset#97.OIWFS
w 2314 763 100 0 OIWFS junction 2320 1200 2320 752 2368 752 agSeqOiwfsParkFlag.agSeqOiwfsParkFlag#101.OIWFS
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2432 2336 100 0 $Id: agSeqOiwfsStatus.sch,v 1.12 2005/10/04 14:16:43 anunez Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2720 80 100 0 Fetch OIWFS status items
[cell use]
use agSeqOiwfsParkFlag 2368 695 100 0 agSeqOiwfsParkFlag#101
xform 0 2592 816
p 2388 668 100 0 1 seta:top $(top)oiPark:
use agSeqOiwfsProbe 1728 199 100 0 agSeqOiwfsProbe#99
xform 0 1952 320
p 1808 176 100 0 1 seta:top $(top)pOff:
use agSeqOiwfsaoOffset 960 199 100 0 agSeqOiwfsaoOffset#98
xform 0 1184 320
p 1024 176 100 0 1 seta:top $(top)aoOff:
use agSeqOiwfsZoffset 320 199 100 0 agSeqOiwfsZoffset#97
xform 0 544 320
p 384 176 100 0 1 seta:top $(top)zoff:
use agSeqOiwfsCoeffs 1728 535 100 0 agSeqOiwfsCoeffs#91
xform 0 1952 736
p 1748 508 100 0 1 seta:top $(top)oi:
use agSeqOiwfsOutName 992 535 100 0 agSeqOiwfsOutName#90
xform 0 1216 736
p 1032 512 100 0 1 seta:top $(top)oiProcSysName
use agSeqProbeOffset 320 535 100 0 agSeqProbeOffset#89
xform 0 544 736
p 384 512 100 0 1 seta:top $(top)oi:
use agSeqOiwfsName 320 1143 100 0 agSeqOiwfsName#88
xform 0 544 1344
p 384 1104 100 0 1 seta:top $(top)oiName:
p 384 1072 100 0 1 setb:dev oiName:
use agSeqOiwfsFollowS 976 1143 100 0 agSeqOiwfsFollowS#87
xform 0 1200 1344
p 1056 1120 100 0 1 seta:top $(top)oiFollow:
use agSeqOiwfsFldStop 1728 1143 100 0 agSeqOiwfsFldStop#84
xform 0 1952 1344
p 1748 1116 100 0 1 seta:top $(top)oiFldStop:
use agSeqOiwfsFilter 2368 1143 100 0 agSeqOiwfsFilter#83
xform 0 2592 1344
p 2432 1120 100 0 1 seta:top $(top)oiFilt:
use agSeqOiwfsLimits 320 1911 100 0 agSeqOiwfsLimits#82
xform 0 544 2112
use agSeqOiwfsTrackId 976 1911 100 0 agSeqOiwfsTrackId#81
xform 0 1200 2112
p 996 1884 100 0 1 seta:top $(top)oiTrack:
use agSeqOiwfsFocus 1728 1911 100 0 agSeqOiwfsFocus#80
xform 0 1952 2112
p 1748 1884 100 0 1 seta:top $(top)oiFocus:
use inhier 96 1687 100 0 OIWFS
xform 0 112 1728
use agSeqOiwfsXY 2368 1911 100 0 agSeqOiwfsXY#78
xform 0 2592 2112
p 2432 1872 100 0 1 seta:top $(top)oiPosn:
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
