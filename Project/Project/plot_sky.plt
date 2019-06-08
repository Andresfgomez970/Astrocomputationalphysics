file_to_read = sprintf("%s.dat",ARG1)
output_image = sprintf("%s.png",ARG1)

set terminal png size 960, 1200 enhanced font "Helvetica,20"
set output output_image

title = sprintf("Synthetic Sky with N = %s points",ARG2)

set xlabel '{/Helvetica-Oblique X}'
set ylabel '{/Helvetica-Oblique Y}'
set zlabel '{/Helvetica-Oblique Z}'

set xrange [-1.1:1.1]
set yrange [-1.1:1.1]
set zrange [-1.1:1.1]

splot file_to_read binary format="%lf%lf%lf" u 1:2:3 title title
