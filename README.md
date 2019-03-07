# Astrocomputationalphysics
This is a repository that will contains codes and reference to Astrocomputationalphysics. It is intended to guide to the simulation of galaxy mergers in the future.


## Bubble method 

bubble2.c : This program generates the same 10 random particles and then calculate respect to the n (this is a varibale given for the user) generated particle (n<10) al the distances; then sorts them from little to greater. An finnaly when done you can run: "gnuplot gnuplot -c plot_postions.plt ARG1 --persist" to plot all the particles identified in the following way: 

- It gives a color respect to the varible to which the distances are calculated. 
- It paits with another coller the firs ARG1 neighbors to the variable. 
- The rest of the particles are plot with only one color.

