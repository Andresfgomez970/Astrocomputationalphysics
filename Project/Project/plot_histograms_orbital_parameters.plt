reset

filename = sprintf("%s.dat",ARG1)
fileparam = sprintf("%s.param",ARG1)

# color definitions
set terminal png size 1050,762 enhanced font 'Verdana,10' #persist
set output sprintf("%s.png",ARG1)


set style line  1 lc rgb '#0060ad' pt 5 ps 0.2 lt 1 lw 2    # blue

#id = system(" awk '{if(NR==1) print $1}' fileparam ")

set multiplot layout 2,3 rowsfirst
title = " " 

do for [i=1:6] {
   l = sprintf("{if(NR==%d) print $1}",i)
   l2 = sprintf("{if(NR==%d) print $2}",i)
   id = sprintf(" awk '%s' %s ",l,fileparam)
   id2 = sprintf("awk '%s' %s",l2,fileparam)
   id = system(id)
   id2 = system(id2)
   binwidth = (id2-id)/( 1 + log(ARG2)/log(2) )
   bin(x,width) = width*floor(x/width) + width/2.0
   set boxwidth binwidth
   set xrange [id:id2]
   plot filename using (bin(column(i),binwidth)):(1.0) smooth freq with boxes title title 
}


#binwidth = ARG2 #0.00018
#bin(x,width) = width*floor(x/width) + width/2.0
#set boxwidth binwidth
#title = " " #"\n Histogram with erros in parameters \n (z,vx,vy) of 10 percent when v=(0,0,1)"  

#set xrange [0.8:1.1]

#plot filename  using (bin($7,binwidth)):(1.0) smooth freq with boxes title title
