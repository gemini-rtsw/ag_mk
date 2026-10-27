[schematic2]
uniq 75
[tools]
[detail]
w 2328 843 100 0 n#74 inhier.CC.P 2304 832 2400 832 agSeqDriveSubCad.agSeqDriveSubCad#22.SDIS
w 2304 1515 100 0 n#73 inhier.PWFS2.P 2256 1504 2400 1504 agSeqDriveSubCad.agSeqDriveSubCad#44.SDIS
w 2304 2091 100 0 n#72 inhier.PWFS1.P 2256 2080 2400 2080 agSeqDriveSubCad.agSeqDriveSubCad#43.SDIS
w 1232 1515 100 0 n#71 inhier.OIDC.P 1200 1504 1312 1504 agSeqDriveSubCad.agSeqDriveSubCad#23.SDIS
w 1016 2027 100 0 n#69 elongouts.oiMask.VAL 544 2112 768 2112 768 2016 1312 2016 agSeqOiwfsCad.agSeqOiwfsCad#54.MASK
w 216 2155 100 0 n#68 hwin.hwin#67.in 192 2144 288 2144 elongouts.oiMask.DOL
w 1000 1387 100 0 n#65 junction 736 1376 1312 1376 agSeqDriveSubCad.agSeqDriveSubCad#23.INPB
w 1352 1611 100 0 n#65 junction 736 1600 2016 1600 2016 1952 2400 1952 agSeqDriveSubCad.agSeqDriveSubCad#43.INPB
w 2184 1387 100 0 n#65 junction 2016 1600 2016 1376 2400 1376 agSeqDriveSubCad.agSeqDriveSubCad#44.INPB
w 2184 715 100 0 n#65 junction 2016 1376 2016 704 2400 704 agSeqDriveSubCad.agSeqDriveSubCad#22.INPB
w 1000 1899 100 0 n#65 ecad2.$(cad).VALB 496 1168 736 1168 736 1888 1312 1888 agSeqOiwfsCad.agSeqOiwfsCad#54.INPB
w 984 1451 100 0 n#64 junction 704 1440 1312 1440 agSeqDriveSubCad.agSeqDriveSubCad#23.INPA
w 1320 1643 100 0 n#64 junction 704 1632 1984 1632 1984 2016 2400 2016 agSeqDriveSubCad.agSeqDriveSubCad#43.INPA
w 2168 1451 100 0 n#64 junction 1984 1632 1984 1440 2400 1440 agSeqDriveSubCad.agSeqDriveSubCad#44.INPA
w 2168 779 100 0 n#64 junction 1984 1440 1984 768 2400 768 agSeqDriveSubCad.agSeqDriveSubCad#22.INPA
w 984 1963 100 0 n#64 ecad2.$(cad).VALA 496 1232 704 1232 704 1952 1312 1952 agSeqOiwfsCad.agSeqOiwfsCad#54.INPA
w 1720 587 100 0 n#63 efanouts.$(cad)Fan.LNK5 960 896 1088 896 1088 576 2400 576 agSeqDriveSubCad.agSeqDriveSubCad#22.SLNK
w 1160 1835 100 0 n#62 efanouts.$(cad)Fan.FLNK 960 1056 1056 1056 1056 1824 1312 1824 agSeqOiwfsCad.agSeqOiwfsCad#54.SLNK
w 1216 2091 100 0 n#59 inhier.OIWFS.P 1168 2080 1312 2080 agSeqOiwfsCad.agSeqOiwfsCad#54.OIWFS
w 1496 939 100 0 n#51 efanouts.$(cad)Fan.LNK4 960 928 2080 928 2080 1248 2400 1248 agSeqDriveSubCad.agSeqDriveSubCad#44.SLNK
w 1480 971 100 0 n#50 efanouts.$(cad)Fan.LNK3 960 960 2048 960 2048 1824 2400 1824 agSeqDriveSubCad.agSeqDriveSubCad#43.SLNK
w 1176 1259 100 0 n#49 efanouts.$(cad)Fan.LNK2 960 992 1088 992 1088 1248 1312 1248 agSeqDriveSubCad.agSeqDriveSubCad#23.SLNK
w 590 946 100 0 n#2 ecad2.$(cad).STLK 496 944 720 944 efanouts.$(cad)Fan.SLNK
s 128 1792 100 0 command should set its bit to zero.
s 128 1824 100 0 A OIWFS that does not implement a
s 2800 80 100 0 CAD record
s 2432 32 100 0 Chris Mayer
s 2704 128 200 0 A&G Sequencer
s 2432 2336 100 0 $Id: agSeqCad.sch,v 1.8 2005/10/04 14:16:43 anunez Exp $
s 128 1952 100 0 This mask is used to disable
s 128 1920 100 0 specific WFS if they don't 
s 128 1888 100 0 implement a particular command.
[cell use]
use hwin 0 2103 100 0 hwin#67
xform 0 96 2144
p 3 2136 100 0 -1 val(in):$(mask)
use elongouts 288 2023 100 0 oiMask
xform 0 416 2112
p 336 2208 100 0 -1 DESC:Mask for OIWFS
p 128 2030 100 0 0 OMSL:closed_loop
p 400 2016 100 1024 0 name:$(top)$(cad):$(I)
use inhier 1152 2039 100 0 OIWFS
xform 0 1168 2080
use inhier 2312 792 100 0 CC
xform 0 2304 832
use inhier 1208 1464 100 0 OIDC
xform 0 1200 1504
use inhier 2240 2039 100 0 PWFS1
xform 0 2256 2080
use inhier 2240 1463 100 0 PWFS2
xform 0 2256 1504
use agSeqOiwfsCad 1312 1767 100 0 agSeqOiwfsCad#54
xform 0 1616 1968
p 1332 1740 100 0 1 seta:dev $(cad):
use agSeqDriveSubCad 2424 520 100 0 agSeqDriveSubCad#22
xform 0 2704 720
p 2464 510 100 0 1 seta:top $(top)cc$(cad):
p 2464 478 100 0 1 setb:subsys cc
p 2464 416 100 0 1 sete:subcad $(ag)$(subsys):$(subcadname)
p 2464 416 100 0 0 setf:instru CC
use agSeqDriveSubCad 1336 1192 100 0 agSeqDriveSubCad#23
xform 0 1616 1392
p 1392 1182 100 0 1 seta:top $(top)oiwfs$(cad):
p 1392 1150 100 0 1 setb:subsys oiwfs
p 1392 1088 100 0 1 sete:subcad $(oiwfs)$(subcadname)
p 1412 1066 100 0 0 setf:instru OIWFSDC
use agSeqDriveSubCad 2424 1768 100 0 agSeqDriveSubCad#43
xform 0 2704 1968
p 2480 1758 100 0 1 seta:top $(top)pwfs1$(cad):
p 2480 1726 100 0 1 setb:subsys pwfs1
p 2480 1664 100 0 1 sete:subcad $(pwfs1)$(subcadname)
p 2500 1642 100 0 0 setf:instru PWFS1
use agSeqDriveSubCad 2424 1192 100 0 agSeqDriveSubCad#44
xform 0 2704 1392
p 2480 1182 100 0 1 seta:top $(top)pwfs2$(cad):
p 2480 1150 100 0 1 setb:subsys pwfs2
p 2480 1088 100 0 1 sete:subcad $(pwfs2)$(subcadname)
p 2500 1066 100 0 0 setf:instru PWFS2
use efanouts 744 808 -100 0 $(cad)Fan
xform 0 840 960
p 688 752 100 0 1 SELM:All
p 832 784 100 1024 1 name:$(top)$(cad)Fanout
use ecad2 200 856 -100 0 $(cad)
xform 0 336 1168
p 256 1502 100 0 -1 DESC:A&G sequencer CAD
p 240 798 100 0 1 SNAM:$(snam)
p 288 848 100 1024 1 name:$(ag)$(cad)
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
