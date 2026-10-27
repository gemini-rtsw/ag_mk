[schematic2]
uniq 4
[tools]
[detail]
s 992 1888 200 0 by the underlying schematics
s 976 1952 200 0 Its main purpose is to define the "top" macro for use
s 976 2080 200 0 This is the top level schematic for the dummy A&G records
s 2432 2336 100 0 $Id: f2DummyTop.sch,v 1.1 2005/06/28 16:00:42 anunez Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2640 80 100 0 Top-level schematic for dummy subsystem
s 976 2016 200 0 It is only intended to be used for test purposes.
s 2432 144 100 0 Copyright
s 2432 112 100 0 Observatory
s 2432 80 100 0 Sciences Ltd.
[cell use]
use agSeqDummyF2 1248 1207 100 0 agSeqDummyF2#3
xform 0 1568 1392
p 1264 1184 100 0 1 seta:top f2:wfs:
p 2016 1504 100 0 -1 setb:CAR_IDLE 0
p 2016 1440 100 0 -1 setc:CAR_BUSY 2
p 2016 1376 100 0 -1 setd:CAD_START 3
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
