[schematic2]
uniq 24
[tools]
[detail]
s 2432 2336 100 0 $Id: agSeqSad.sch,v 1.4 1999/10/19 16:07:26 cjm Exp $
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2800 80 100 0 SAD records
[cell use]
use agSeqOiSad 192 1351 100 0 agSeqOiSad#23
xform 0 384 1504
p 212 1324 100 0 1 seta:top $(top)oi:
use esirs 2064 1863 100 0 state
xform 0 2272 2016
p 2160 2176 100 0 -1 DESC:Overall state of A&G
p 2000 1600 100 0 0 FDSC:A&G is BOOTING/INITIALISING/RUNNING
p 2144 1904 100 0 1 FTVL:LONG
use esirs 856 1864 100 0 inPosition
xform 0 1040 2016
p 944 2174 100 0 -1 DESC:A&G in position flag
p 768 1600 100 0 0 FDSC:Overall in position flag of the A&G
p 912 1902 100 0 1 FTVL:LONG
p 912 1934 100 0 1 SCAN:Passive
p 368 2142 100 0 0 def(INP):0.0
use esirs 1464 1864 100 0 name
xform 0 1648 2016
p 1616 2176 100 0 -1 DESC:A&G name
p 1376 1600 100 0 0 FDSC:rec. for systems that holds sys name
p 1520 1902 100 0 1 FTVL:STRING
p 1520 1934 100 0 1 SCAN:Passive
p 976 2142 100 0 0 def(INP):0.0
use esirs 200 1864 100 0 health
xform 0 384 2016
p 288 2174 100 0 -1 DESC:A&G health record
p 256 1902 100 0 1 FTVL:STRING
p 256 1934 100 0 0 SCAN:Passive
p -288 2142 100 0 0 def(INP):0.0
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
