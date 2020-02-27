#set style data lines
set terminal gif animate delay 3
set output 'foobar.gif'

set view map
set pm3d at b map
set dgrid3d 40,40
set cbrange [270:373]
do for [i=1:159] { splot sprintf('files/data%d.txt', i) using 1:2:3 title ""; pause 0.5 } 