The LFU algorithm seems to be functioning as it is intended. The design is very simple. One thing that it does is, if multiple numbers have the same frequency, and that frequency happens to be the lowest, then the very first one sequentially will be the page that is swapped out.

for Example,

Num:		1	2	3	4	5	…
Freq:		3	2	1	1	1	…

if this page table had 5 slots and these 5 values were in the page table sequentially, and a 6th reference came about, page 3 would be swapped out, because it is the first in line, sequentially, to have the value of the lowest frequency.