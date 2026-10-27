[schematic2]
uniq 5
[tools]
[detail]
[cell use]
use telDummySysStatus -32 231 100 0 telDummySysStatus#2
xform 0 64 336
p -32 240 100 0 1 seta:sys $(pwfs2)
use telDummySysStatus -32 455 100 0 telDummySysStatus#1
xform 0 64 560
p -32 464 100 0 1 seta:sys $(pwfs1)
use telDummySysStatus -32 679 100 0 telDummySysStatus#0
xform 0 64 784
p -32 688 100 0 1 seta:sys $(ag)cc:
use telDummySysStatus -32 7 100 0 telDummySysStatus#4
xform 0 64 112
p -32 16 100 0 1 seta:sys $(oiwfs)
use esirs 640 519 100 0 esirs#3
xform 0 848 672
p 784 640 100 0 1 FTVL:STRING
p 784 512 100 1024 -1 name:$(ag)aoName
use ba200tr -256 -200 -100 0 frame
xform 0 544 424
[comments]
