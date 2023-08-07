#!/usr/bin/gnuplot --persist

set terminal pdf size 10,3
set output 'output.pdf'

set xrange [33341:5734189]

set y2tics 0,1
set y2range[0:8]
set ytics nomirror
set y2tics nomirror

set pointsize 0.005

plot 'ElevatorData.txt' using 1:2 pointtype 7 axis x1y1 title "lobby pressure", '' using 1:3 pointtype 7 axis x1y1 title "elevator pressure", '' using 5 with lines axis x2y2 title "floor guess"


set output 'output2.pdf'

f(x) = 129.24
plot 'ElevatorData.txt' using 1:6 pointtype 7 axis x1y1 title "difference", 129.24 title "1", 87.65 title "2", 46.38 title "3", 9.89 title "4", -27.14 title "5", -67.07 title "6"
