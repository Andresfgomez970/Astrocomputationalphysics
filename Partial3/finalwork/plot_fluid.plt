## program to plot density field in time together with plot_fluid_principal.gp

t = t + 0.5/Number_of_frames
outfile = sprintf("%s/fluid%.5d.png",dir_to_save_images,i) #assumed that thereare not more than 1E5 frames

set terminal png
set output outfile

## sort in oder to make the plot process correctly 
fluido = sprintf("<sort -n -k 7 data/punto1/fluido_cont_%.5d.dat", i*10) ## They are assumed to go in steps of 10 an data is in punto1
titulo = sprintf("%d",i*10)
plot [-1:5][-0.1:1.1] fluido u 2:3:7 w p palette ps 1.5 pt 7 t titulo

i = i + 1
if (t<end_time) reread;

