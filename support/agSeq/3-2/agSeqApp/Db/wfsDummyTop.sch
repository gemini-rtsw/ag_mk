[schematic2]
uniq 2
[tools]
[detail]
s 992 1888 200 0 by the underlying schematics
s 976 1952 200 0 Its main purpose is to define the "top" macro for use
s 976 2080 200 0 This is the top level schematic for the dummy WFSPS
s 2432 2336 100 0 $Id: wfsDummyTop.sch,v 1.1.1.1 1998/07/29 16:02:28 Gemini Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2656 80 100 0 Top-level schematic for dummy WFSPS
s 976 2016 200 0 It is only intended to be used for test purposes.
[cell use]
use wfsDummy 1272 1224 100 0 wfsDummy#1
xform 0 1568 1408
p 1248 1184 100 0 1 seta:top ag:wfs:
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
