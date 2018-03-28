[schematic2]
uniq 47
[tools]
[detail]
[cell use]
use testlan 472 232 100 0 testlan#41
xform 0 624 352
p 448 208 100 0 1 set1:top ag:cc:pmac1
p 448 176 100 0 1 set2:command testLan
p 448 144 100 0 1 set3:EVENT_NUMBER 1
p 448 112 100 0 1 set4:BUSY 2
use pmac 80 231 100 0 pmac#42
xform 0 200 288
p 80 224 100 0 1 set0:top ag:cc:pmac2
p 80 192 100 0 1 set1:axis 1
p 80 160 100 0 1 set2:CARD 1
p 80 128 100 0 1 set3:c 1
p 80 96 100 0 1 set4:DELAY_SEC 15
use pmac -304 231 100 0 pmac#37
xform 0 -184 288
p -304 224 100 0 1 set0:top ag:cc:pmac1
p -304 192 100 0 1 set1:axis 0
p -304 160 100 0 1 set2:CARD 0
p -304 128 100 0 1 set3:c 0
p -304 96 100 0 1 set4:DELAY_SEC 15
[comments]
