[schematic2]
uniq 9
[tools]
[detail]
w 990 1131 100 0 n#7 junction 1216 864 1216 1120 800 1120 800 1056 896 1056 ecalcs.ecalcs#6.INPA
w 1214 907 100 0 n#8 ecalcs.ecalcs#6.FLNK 1184 896 1280 896 1280 704 1376 704 esirs.esirs#3.SLNK
w 1262 875 100 0 n#7 ecalcs.ecalcs#6.VAL 1184 864 1376 864 esirs.esirs#3.INP
[cell use]
use ecalcs 896 583 100 0 ecalcs#6
xform 0 1040 848
p 928 512 100 0 1 CALC:A+1
p 928 544 100 0 1 SCAN:1 second
p 1008 576 100 1024 -1 name:$(sys)heartbeat
use esirs 96 903 100 0 esirs#0
xform 0 304 1056
p 256 1056 100 0 1 FTVL:STRING
p 224 896 100 1024 -1 name:$(sys)state
use esirs 96 199 100 0 esirs#1
xform 0 304 352
p 256 352 100 0 1 FTVL:STRING
p 224 192 100 1024 -1 name:$(sys)health
use esirs 1376 615 100 0 esirs#3
xform 0 1584 768
p 1536 768 100 0 1 FTVL:LONG
p 1504 608 100 1024 -1 name:$(sys)present
use esirs 96 551 100 0 esirs#4
xform 0 304 704
p 256 704 100 0 1 FTVL:LONG
p 256 544 100 1024 -1 name:$(sys)inPosition
use bb200tr -288 -184 -100 0 frame
xform 0 992 640
[comments]
