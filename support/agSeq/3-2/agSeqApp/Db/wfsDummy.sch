[schematic2]
uniq 5
[tools]
[detail]
w 718 1906 100 0 n#2 ecalcs.present.VAL 912 1584 1008 1584 1008 1904 464 1904 464 1776 624 1776 ecalcs.present.INPA
s 2704 80 100 0 dummy AGWPS records
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: wfsDummy.sch,v 1.2 1998/09/16 00:28:39 cjm Exp $
[cell use]
use esirs 1808 423 100 0 inPosition
xform 0 2016 576
p 1904 752 100 0 -1 DESC:AGWPS in position flag
p 1744 160 100 0 0 FDSC:Overall in position status for AGWPS
p 1744 128 100 0 0 FTVL:LONG
use esirs 1816 1528 100 0 health
xform 0 2000 1680
p 1936 1838 100 0 -1 DESC:AGWPS health
use esirs 1816 968 100 0 state
xform 0 2000 1120
p 1920 1278 100 0 -1 DESC:State of AGWPS
use ecalcs 648 1304 100 0 present
xform 0 768 1568
p 784 1358 100 0 1 CALC:(A+1)%1000
p 608 1854 100 0 -1 DESC:Incrementing counter
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
