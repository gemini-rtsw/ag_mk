[schematic2]
uniq 1
[tools]
[detail]
s 1152 1984 200 0 macro that will be used by the schematics under this one
s 1152 2080 200 0 The main function of this schematic is to define the "top"
s 2672 80 100 0 Top level schematic for SAD
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqSadTopTest1.sch,v 1.1 2007/05/18 22:29:25 pedro Exp $
[cell use]
use agSeqSad 1624 1256 100 0 agSeqSad#0
xform 0 1920 1440
p 1600 1216 100 0 1 seta:top ag1:
p 1600 1184 100 0 1 setb:ag ag1:
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
