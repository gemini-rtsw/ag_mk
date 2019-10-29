[schematic2]
uniq 892
[tools]
[detail]
w -224 1619 100 0 PLC_RESP inhier.PLC_RESP.P -256 1616 -96 1616 egenSub.carh.INPJ
w -246 1171 100 0 c#886 inhier.SDIS.P -256 1168 -176 1168 hwout.hwout#889.outp
w 1194 1723 100 0 n#880 estringouts.sirso.DOL 1584 1712 864 1712 864 2160 192 2160 egenSub.carh.VALB
w 1810 1675 100 0 n#879 hwout.hwout#875.outp 1840 1664 1840 1664 estringouts.sirso.OUT
w 1810 2267 100 0 n#874 hwout.hwout#471.outp 1840 2256 1840 2256 elongouts.carl.OUT
w 1810 2331 100 0 n#873 hwout.hwout#872.outp 1840 2320 1840 2320 elongouts.carl.FLNK
w 1554 2011 100 0 n#871 hwin.hwin#870.in 1584 2000 1584 2000 eevents.carev.INP
w 586 2195 100 0 n#839 egenSub.carh.OUTA 192 2192 1040 2192 junction
w 1282 2323 100 0 n#839 elongouts.carl.DOL 1584 2320 1040 2320 1040 2192 ecars.C.IVAL
w 1442 1971 100 0 n#473 ecars.C.FLNK 1360 1968 1584 1968 eevents.carev.SLNK
s -256 2352 100 0 In that case, the CAR doesn't have to be updated.
s -256 2384 100 0 This record is disabled if the PLC-Response didn't change.
s 3296 320 500 512 compCar.sch
s 1056 2496 100 0 Using an event is necessary for breaking up the logset.
s 1072 2464 100 0 An input link doesn't lead to a logset.
s 384 1936 100 0 PP link with PLC response from DPRead
s 384 1824 100 0 PP link with CAR value to mech CAR
s 384 1792 100 0 Health string for SAD
s 2144 2256 100 0 the receiving record is a gensub
s 2144 2224 100 0 which cannot simply be triggered with PP NMS
s 2112 1648 100 0 the receiving record is a SIR
[cell use]
use hwout 384 2247 100 0 hwout#891
xform 0 480 2288
p 384 2320 100 0 -1 val(outp):$(top)$(mech)C.IVAL PP NMS
use hwout 1840 1623 100 0 hwout#875
xform 0 1936 1664
p 1936 1696 100 0 -1 val(outp):$(sadtop)$(mech)Health.VAL PP NMS
use hwout 1840 2279 100 0 hwout#872
xform 0 1936 2320
p 1936 2311 100 0 -1 val(outp):$(cartop)CCar.VAL PP NMS
use hwout 1840 2215 100 0 hwout#471
xform 0 1936 2256
p 1936 2256 100 0 -1 val(outp):$(cindex)
use hwout -176 1127 100 0 hwout#889
xform 0 -80 1168
p -176 1200 100 0 -1 val(outp):$(top)$(mech)carh.DISV PP NMS
use inhier -336 1152 100 0 SDIS
xform 0 -256 1168
use inhier -384 1600 100 0 PLC_RESP
xform 0 -256 1616
use elongouts 1648 2368 100 0 carl
xform 0 1712 2288
p 1632 2096 100 0 1 EVNT:$(car2evnr)
p 1632 2192 100 0 1 OMSL:closed_loop
p 1632 2160 100 0 1 PV:$(top)$(mech)
p 1632 2128 100 0 1 SCAN:Event
p 1840 2256 75 768 -1 pproc(OUT):NPP
use estringouts 1648 1744 100 0 sirso
xform 0 1712 1680
p 1648 1504 100 0 1 EVNT:$(car2evnr)
p 1648 1568 100 0 1 OMSL:closed_loop
p 1648 1600 100 0 1 PV:$(top)$(mech)
p 1648 1536 100 0 1 SCAN:Event
p 1648 1472 100 0 1 VAL:GOOD
p 1840 1664 75 768 -1 pproc(OUT):PP
use hwin 1392 1959 100 0 hwin#870
xform 0 1488 2000
p 1392 2032 100 0 -1 val(in):$(car2evnr)
use egenSub 0 1472 100 0 carh
xform 0 48 1856
p -32 1392 100 0 1 DESC:CAR value handler
p -384 1870 100 0 0 EFLG:ALWAYS
p -16 2224 100 0 1 FTA:LONG
p -16 2192 100 0 1 FTB:LONG
p -16 2160 100 0 1 FTC:LONG
p -16 2128 100 0 1 FTD:LONG
p -16 2096 100 0 1 FTE:LONG
p -16 2064 100 0 1 FTF:LONG
p -16 2032 100 0 1 FTG:LONG
p -16 2000 100 0 1 FTH:LONG
p -16 1968 100 0 1 FTI:LONG
p -16 1936 100 0 1 FTJ:LONG
p -16 1824 100 0 1 FTVA:LONG
p -16 1792 100 0 1 FTVB:STRING
p -16 1760 100 0 1 FTVC:LONG
p -16 1728 100 0 1 FTVD:LONG
p -16 1696 100 0 1 FTVE:LONG
p -16 1664 100 0 1 FTVF:LONG
p -16 1632 100 0 1 FTVG:LONG
p -16 1600 100 0 1 FTVH:LONG
p -16 1568 100 0 1 FTVI:LONG
p -16 1536 100 0 1 FTVJ:LONG
p -32 1296 100 0 1 INAM:CarHandler
p 288 2224 100 0 1 NOA:1
p 288 2192 100 0 1 NOB:1
p 288 2160 100 0 1 NOC:1
p 288 2128 100 0 1 NOD:1
p 288 2096 100 0 1 NOE:1
p 288 2064 100 0 1 NOF:1
p 288 2032 100 0 1 NOG:1
p 288 2000 100 0 1 NOH:1
p 288 1968 100 0 1 NOI:1
p 288 1936 100 0 1 NOJ:1
p 288 1824 100 0 1 NOVA:1
p 288 1792 100 0 1 NOVB:1
p 288 1760 100 0 1 NOVC:1
p 288 1728 100 0 1 NOVD:1
p 288 1696 100 0 1 NOVE:1
p 288 1664 100 0 1 NOVF:1
p 288 1632 100 0 1 NOVG:1
p 288 1600 100 0 1 NOVH:1
p 288 1568 100 0 1 NOVI:1
p 288 1536 100 0 1 NOVJ:1
p -32 1264 100 0 1 PREC:2
p -32 1360 100 0 1 PV:$(top)$(mech)
p -32 1424 100 0 1 SCAN:Passive
p -32 1328 100 0 1 SNAM:CarHandler
p 16 1886 100 0 -1 Type:genSub
p 192 2202 75 0 -1 pproc(OUTA):PP
p 192 1946 75 0 -1 pproc(OUTE):PP
use eborderD -1840 -281 100 0 eborderD#217
xform 0 800 1424
p 2032 -64 100 768 -1 author:O.Frischmuth
p 3056 -80 100 0 1 border:D
p 1952 -128 100 0 1 checked:O.Frischmuth
p 2320 -144 100 768 -1 date:21 Jan 97
p 2288 192 200 768 -1 file:compCar.sch
p 2960 -144 100 0 1 id:frame
p 2608 -144 100 0 1 model:frame
p 2784 -80 100 0 -1 page:
p 1904 192 100 0 1 project:A&G unit
p 2384 -64 100 0 -1 revision:2.2
p 2304 64 100 0 1 title:One and multiple axis discrete and continuous move CAD records
use eevents 1664 2048 100 0 carev
xform 0 1728 1968
p 1648 1872 100 0 1 PV:$(top)$(mech)
p 1648 1840 100 0 0 def(INP):0.000000000000000e+00
use ecars 1120 1952 100 0 C
xform 0 1200 2080
p 1104 1840 100 0 1 DESC:mech's CAR record
p 1104 1904 100 0 1 PV:$(top)$(mech)
p 1104 1872 100 0 1 SCAN:Passive
p 1152 1952 100 1024 -1 name:
[comments]
