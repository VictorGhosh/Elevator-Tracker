#!/usr/bin/gnuplot --persist

set terminal png
set output 'output.png'

set y2tics 0,1
set y2range[0:8]
set ytics nomirror
set y2tics nomirror

plot 'elevator1-7.txt' using 1 with lines axis x1y1 title columnheader, '' using 2 with lines axis x1y1 title columnheader, '' using 3 with lines axis x2y2 title columnheader
