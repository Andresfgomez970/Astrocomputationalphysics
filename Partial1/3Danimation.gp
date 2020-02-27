#set xrange [0:10]
#set yrange [0:10]

set terminal gif animate delay 0.25
set output 'foobar2.gif'

set dgrid3d 40,40
set hidden3d
set ticslevel 0
set pm3d
set zrange [270:375]

do for [i=1:159] { splot sprintf('files/data%d.txt', i) using 1:2:3; pause 0.5 }