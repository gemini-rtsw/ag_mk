[schematic2]
uniq 5
[tools]
[detail]
s 1280 2032 150 0 epics records needed by timelib
s 1184 2080 150 0 This is a top level schematic to provide the
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2640 80 100 0 Top-level schematic for timelib records
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 Timelib records
s 2432 2336 100 0 $Id: timeTop.sch,v 1.1 1999/10/14 14:58:40 cjm Exp $
[cell use]
use timelib 1344 1479 100 0 timelib#4
xform 0 1552 1648
p 1456 1456 100 0 1 seta:top gm:wfs:
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
