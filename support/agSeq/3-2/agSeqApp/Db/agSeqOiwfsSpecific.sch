[schematic2]
uniq 90
[tools]
[detail]
w 1544 875 100 0 n#74 junction 1248 864 1888 864 1888 1088 1952 1088 agSeqGpiSpecific.agSeqGpiSpecific#88.AOSTATE
w 904 875 100 0 n#74 junction 608 864 1248 864 1248 1088 1312 1088 agSeqNifsSpecific.agSeqNifsSpecific#71.AOSTATE
w 1256 1771 100 0 n#74 junction 1248 1536 1248 1760 1312 1760 agSeqF2Specific.agSeqF2Specific#69.AOSTATE
w 1224 1547 100 0 n#74 junction 608 1536 1888 1536 1888 1760 1952 1760 agSeqGmosSpecific.agSeqGmosSpecific#59.AOSTATE
w 632 1099 100 0 n#74 junction 608 1088 704 1088 agSeqNirsSpecific.agSeqNirsSpecific#68.AOSTATE
w 568 1771 100 0 n#74 egenSub.aoDeployed.VALA 480 1760 704 1760 agSeqNiriSpecific.agSeqNiriSpecific#57.AOSTATE
w 632 459 100 0 n#74 junction 608 1760 608 448 704 448 agSeqNiciSpecific.agSeqNiciSpecific#79.AOSTATE
w 1956 1019 -100 2 GPIPORT inhier.GPIPORT.P 1952 1024 1952 1024 agSeqGpiSpecific.agSeqGpiSpecific#88.PORT
w 708 379 100 0 n#85 inhier.NICIPORT.P 704 384 704 384 agSeqNiciSpecific.agSeqNiciSpecific#79.PORT
w 1299 1124 -100 0 NIFSPORT inhier.NIFSPORT.P 1296 1024 1312 1024 agSeqNifsSpecific.agSeqNifsSpecific#71.PORT
w 1268 1707 -100 0 F2PORT inhier.F2PORT.P 1296 1696 1312 1696 agSeqF2Specific.agSeqF2Specific#69.PORT
w 672 1035 -100 0 c#67 inhier.NIRSPORT.P 688 1024 704 1024 agSeqNirsSpecific.agSeqNirsSpecific#68.PORT
w 1920 1707 100 0 n#60 inhier.GMOSPORT.P 1936 1696 1952 1696 agSeqGmosSpecific.agSeqGmosSpecific#59.PORT
w 672 1707 100 0 n#58 inhier.NIRIPORT.P 688 1696 704 1696 agSeqNiriSpecific.agSeqNiriSpecific#57.PORT
s 2448 1184 100 0 be needed or not.
s 2448 1216 100 0 at the time of implementation whether they will
s 2448 1248 100 0 were added just because it was not clear
s 2448 1280 100 0 Note: The coordinate transformation for GPI
s 832 2240 200 0 This schematic acts as a container for OIWFS specific data
s 2432 2336 100 0 $Id: agSeqOiwfsSpecific.sch,v 1.12 2013/05/29 16:36:37 pedro Exp $
s 2432 80 100 0 Sciences Ltd.
s 2432 112 100 0 Observatory
s 2432 144 100 0 Copyright
s 2704 128 200 0 A&G Sequencer
s 2432 32 100 0 Chris Mayer
s 2672 80 100 0 OIWFS specific data
[cell use]
use agSeqGpiSpecific 1952 935 100 0 agSeqGpiSpecific#88
xform 0 2192 1200
p 2016 928 100 0 1 seta:top $(top)gpi:
use inhier 688 343 100 0 NICIPORT
xform 0 704 384
use inhier 672 983 100 0 NIRSPORT
xform 0 688 1024
use inhier 1920 1655 100 0 GMOSPORT
xform 0 1936 1696
use inhier 672 1655 100 0 NIRIPORT
xform 0 688 1696
use inhier 1280 1655 100 0 F2PORT
xform 0 1296 1696
use inhier 1280 983 100 0 NIFSPORT
xform 0 1296 1024
use inhier 1936 983 100 0 GPIPORT
xform 0 1952 1024
use agSeqNiciSpecific 704 295 100 0 agSeqNiciSpecific#79
xform 0 944 560
p 768 288 100 0 1 seta:top $(top)nici:
use agSeqNifsSpecific 1312 935 100 0 agSeqNifsSpecific#71
xform 0 1552 1200
p 1376 928 100 0 1 seta:top $(top)nifs:
use agSeqF2Specific 1312 1607 100 0 agSeqF2Specific#69
xform 0 1552 1872
p 1376 1600 100 0 1 seta:top $(top)$(f2)
use agSeqNirsSpecific 704 935 100 0 agSeqNirsSpecific#68
xform 0 944 1200
p 768 928 100 0 1 seta:top $(top)nirs:
use agSeqNiriSpecific 768 1607 100 0 agSeqNiriSpecific#57
xform 0 944 1872
p 768 1600 100 0 1 seta:top $(top)niri:
use egenSub 192 967 100 0 aoDeployed
xform 0 336 1392
p 176 1840 100 0 -1 DESC:Convert TCS useAO state to a flag
p -31 741 100 0 0 FTA:STRING
p 288 1760 100 0 1 FTVA:LONG
p 288 864 100 0 1 SCAN:1 second
p 304 912 100 0 1 SNAM:agSeqAoDeployed
p -48 1792 100 0 -1 def(INPA):$(tcs)im:AOConfigFlag
p 176 1738 75 0 -1 palrm(INPA):MS
p 144 1738 75 0 -1 pproc(INPA):NPP
use agSeqGmosSpecific 1984 1607 100 0 agSeqGmosSpecific#59
xform 0 2192 1872
p 2016 1600 100 0 1 seta:top $(top)gmos:
use bc200tr -160 -136 -100 0 frame
xform 0 1520 1168
[comments]
