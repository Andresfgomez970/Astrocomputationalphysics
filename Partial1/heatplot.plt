# To run the comment we should do:
#    gnuplot -p "data.gp"
#set terminal postfile       (These commented lines would be used to )
#set output  "d2_plot.ps"    (generate a postscript file.            )

#set terminal gif anumate delay 100 
#set ouput "foorbar.gif"

t = t + 0.5/80.
outfile = sprintf('animation/bessel%03.0f.png',80*t)
set output outfile

set view map
set pm3d at b map
set dgrid3d 200,200,2
set cbrange [270:373]
splot 'files/data'.i.'.txt' u 1:2:3
i = i + 1

if (t<end_time) reread;