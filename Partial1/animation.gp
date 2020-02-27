#set style data lines
set terminal gif animate delay 100
set output 'foobar.gif'

set view map
set pm3d at b map
set dgrid3d 200,200,2
set cbrange [270:373]
do for [i=1:79] { splot sprintf('files/data%d.txt', i) using 1:2:3; pause 0.5 }