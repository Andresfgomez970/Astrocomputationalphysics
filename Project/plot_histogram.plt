
filename = sprintf("%s.dat",ARG1)

set terminal png size 1000, 800 enhanced font "Helvetica,22"
set output sprintf("%s.png",ARG1)

binwidth = ARG2 #0.00018
bin(x,width)=width*floor(x/width) + width/2.0
set boxwidth binwidth

title = sprintf( "\n \n Histogram for %s with a %s \n in parameters (Z0,Vx0,Vy0) \n when v0=(0,0,1) and x0=(0,1,0)", ARG3, ARG4)


plot filename using (bin($1,binwidth)):(1.0) smooth freq with boxes title title
