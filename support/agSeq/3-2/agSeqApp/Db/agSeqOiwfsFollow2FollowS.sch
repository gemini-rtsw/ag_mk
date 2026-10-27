[schematic2]
uniq 196
[tools]
[detail]
w 2610 2763 100 0 FOLLOWS egenSub.egenSub#193.OUTA 2464 2752 2816 2752 outhier.FOLLOWS.p
w 1970 2091 100 0 SLNK inhier.SLNK.P 1824 2080 2176 2080 egenSub.egenSub#193.SLNK
s 3056 1856 100 0 A&G Sequencer
s 2992 1792 100 0 Fetch OIWFS follow status
s 1056 3056 100 0 Gensubs have been used to generate the correct values for the
s 1056 3024 100 0 followS record because of problems with propagating the severities
s 1056 2992 100 0 when using fanout records.
s 1056 2960 100 0 It is important that the severity of followS is set to invalid
s 1056 2928 100 0 when an OIWFS is selected but the database isn't loaded
s 2736 1744 100 0 Pedro Gigoux
[cell use]
use outhier 2784 2711 100 0 FOLLOWS
xform 0 2800 2752
use inhier 1808 2039 100 0 SLNK
xform 0 1824 2080
use bb200tr 928 1576 -100 0 frame
xform 0 2208 2400
use egenSub 2176 1991 100 0 egenSub#193
xform 0 2320 2416
p 2160 2848 100 0 -1 DESC:Generate $(subsys) followS
p 1953 1765 100 0 0 FTA:LONG
p 1953 1765 100 0 0 FTB:DOUBLE
p 1953 1733 100 0 0 FTC:DOUBLE
p 1953 1701 100 0 0 FTD:DOUBLE
p 1953 1765 100 0 0 FTVA:STRING
p 2400 1920 100 0 0 SCAN:Passive
p 2208 1952 100 0 1 SNAM:$(snam)
p 1872 2784 100 0 1 def(INPA):$(follow)
p 1856 2688 100 0 0 def(INPB):0.000000000000000e+00
p 1424 2528 100 0 0 def(INPC):0.000000000000000e+00
p 1424 2368 100 0 0 def(INPD):0.000000000000000e+00
p 2288 1984 100 1024 -1 name:$(top)$(subsys)FollowS
p 2160 2762 75 0 -1 palrm(INPA):MS
p 2496 2762 75 0 -1 palrm(OUTA):MS
p 2464 2762 75 0 -1 pproc(OUTA):PP
[comments]
