#!/usr/bin/gunplot --persist

# GENERAL
set style line 1 lt 3 dt 2 lw 1 lc rgb 'red'

# STAIR/FOOT DATA
set terminal pngcairo size 1200,768 font 'Helvetica, 22'
set output 'footDat.png'
set title "Data on Foot" offset 0,-1
set xlabel "Reading Number"
set ylabel "Base Pressure - Lobby Pressure (hPa)"
set xtics nomirror
set ytics nomirror

set arrow from 1,-145 rto graph 1,0 ls 1 nohead # 1
set arrow from 1,-102 rto graph 1,0 ls 1 nohead # 2
set arrow from 1,-66 rto graph 1,0 ls 1 nohead # 3
set arrow from 1,-24 rto graph 1,0 ls 1 nohead # 4
set arrow from 1,13 rto graph 1,0 ls 1 nohead # 5
set arrow from 1,53 rto graph 1,0 ls 1 nohead # 6
set arrow from 1,95 rto graph 1,0 ls 1 nohead # 7

plot 'June19-Numbered.txt' using 4:($2-$1) with line axis x1y1 notitle

# ELEVATOR DATA
set terminal pngcairo size 2048,820 font 'Helvetica,22'
set output 'elevatorDat.png'
set title "Data from Inside of Elevator" offset 0,-1
set xlabel "Time from Start (ms)"
set ylabel "Base Pressure - Lobby Pressure (hPa)"
set xrange [33341:5734189]
set xtics nomirror
set ytics nomirror

set arrow from 50000,-145 rto graph 1,0 ls 1 nohead # 1
set arrow from 50000,-102 rto graph 1,0 ls 1 nohead # 2
set arrow from 50000,-66 rto graph 1,0 ls 1 nohead # 3
set arrow from 50000,-24 rto graph 1,0 ls 1 nohead # 4
set arrow from 50000,13 rto graph 1,0 ls 1 nohead # 5
set arrow from 50000,53 rto graph 1,0 ls 1 nohead # 6
set arrow from 50000,95 rto graph 1,0 ls 1 nohead # 7

plot 'ElevatorData.txt' using ($1):($6) with line axis x1y1 notitle
