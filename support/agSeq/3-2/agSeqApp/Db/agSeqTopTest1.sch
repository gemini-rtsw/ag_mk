[schematic2]
uniq 6
[tools]
[detail]
s 944 720 200 0 to avoid code duplication
s 2736 80 100 0 Top level schematic
s 2448 32 100 0 Chris Mayer
s 2720 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqTopTest1.sch,v 1.3 2013/05/29 16:35:09 pedro Exp $
s 864 2064 200 0 This is the top level schematic for the A&G Sequencer.
s 880 2000 200 0 Its main purpose is to define the "top" macro for use
s 896 1936 200 0 by the underlying schematics
s 2448 144 100 0 Copyright
s 2448 112 100 0 Observatory
s 2448 80 100 0 Sciences Ltd.
s 944 832 200 0 The site dependant is definitions are stored
s 944 768 200 0 at the next level of the schematic hierarchy
[cell use]
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
use agSeqSiteDep 736 1015 100 0 agSeqSiteDep#5
xform 0 1408 1304
p 1264 1424 100 0 -1 setag:ag ag1:
p 528 1152 100 0 -1 setcadmark:CAD_MARK 0
p 528 1120 100 0 -1 setcadstart:CAD_START 3
p 528 1344 100 0 -1 setcarbusy:CAR_BUSY 2
p 528 1312 100 0 -1 setcarerror:CAR_ERROR 3
p 528 1376 100 0 -1 setcaridle:CAR_IDLE 0
p 1888 1264 100 0 -1 sethr:hrwfs hrwfs:
p 2224 1440 100 0 -1 setinst00:NONE 0
p 2224 1376 100 0 -1 setinst01:GMOS 1
p 2224 1312 100 0 -1 setinst02:NIRS 2
p 2224 1248 100 0 -1 setinst03:NIRI 3
p 2224 1184 100 0 -1 setinst04:F2 4
p 2224 1120 100 0 -1 setinst05:NIFS 5
p 2224 1056 100 0 -1 setinst06:NICI 6
p 2224 992 100 0 -1 setinst07:GSAOI 7
p 2224 928 100 0 -1 setinst08:GPI 8
p 976 1264 100 0 -1 setoi:oiwfs oiwfs:
p 1440 1264 100 0 -1 setp1:pwfs1 pw1:
p 1664 1264 100 0 -1 setp2:pwfs2 pw2:
p 1616 1424 100 0 -1 setsad:sad ag1:
p 1456 1424 100 0 -1 settcs:tcs tcs:
p 1136 1424 100 0 -1 settop:top ag1:
[comments]
