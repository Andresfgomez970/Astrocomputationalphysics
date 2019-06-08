#initializing values for the loop and start the loop

dir_to_save_images = sprintf("%s",ARG1)
Number_of_frames = ARG2 

t = 0
i = 0
end_time = 0.5
instruction = sprintf("mkdir -p %s",dir_to_save_images)
system(instruction)
load 'plot_fluid.plt'
