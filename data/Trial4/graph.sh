#!/usr/bin/gnuplot --persist

set terminal pdf size 10,3
set output 'output.pdf'

set x2range [33341:5734189]

set mxtics 10
set mytics 10
set style line 101 lt 1 lc rgb "dark-violet" lw 1
set style line 102 lt 1 lc rgb "grey" lw 0.5
set grid mxtics mytics ls 102, ls 102

set pointsize 0.005

plot 'pressureTesting.txt' using 1:8 pointtype 7 axis x1y1 title "Difference Trial 4", 'ElevatorDatat3.txt' using 1:6 pointtype 7 axis x2y1 title "Difference Trial 3"
