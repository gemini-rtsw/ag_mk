[schematic2]
uniq 3
[tools]
[detail]
s 496 672 100 0 $Id: agSeqTweakOffsets.sch,v 1.1 2005/06/30 20:41:27 anunez Exp $
s 560 -160 100 0 A&G Sequencer
s 512 -224 100 0 Tweak Offset Records
s 240 -272 100 0 Arturo Nunez
[cell use]
use eais -192 391 100 0 tweakX
xform 0 -64 464
p -403 537 100 0 0 DESC:Offset X
p -448 206 100 0 0 EGU:mm
p -80 384 100 1024 0 name:$(top)tweakX
use eais -192 199 100 0 tweakY
xform 0 -64 272
p -403 345 100 0 0 DESC:Y Offset
p -448 14 100 0 0 EGU:mm
p -80 192 100 1024 0 name:$(top)tweakY
use eais -192 39 100 0 tweakZ
xform 0 -64 112
p -403 185 100 0 0 DESC:Z offset
p -448 -146 100 0 0 EGU:mm
p -80 32 100 1024 0 name:$(top)tweakZ
use ba200tr -608 -440 -100 0 frame
xform 0 192 184
p -608 -416 100 0 0 model:frame
p 716 -284 100 1792 -1 page:
p -608 -392 100 0 0 revision:2.2
[comments]
