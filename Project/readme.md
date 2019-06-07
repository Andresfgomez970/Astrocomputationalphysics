---------------------------------------
---------------------------------------
ABOUT THE .C AND .PLT FILES 
---------------------------------------
---------------------------------------

densities_constructions.c
montecarlo.c
allvars.c
two_body_analytical.c
plot_histogram.plt
plot_histogram2.plt
plot_sky.plt
main.c






---------------------------------------
---------------------------------------
INFORMATION TO READ MAIN
---------------------------------------
---------------------------------------
To run the program the parameters in main must be changed. This one is divided in block of comments that illustrate an example of a possible output that can be obtained with the programs written. The example were tested to be run by uncommenting each block individually, after that it is enough to type "make runmain" to compile and run the executable or make to only compile. In the following more detailed instructions for each example are given:

---------------------- Example1 ----------------------------------------

It is designed to distribute points on a sphere of a given radius unifromly over it.

The input parameters are:

directory == name of the directory already created where the ouput of the example is desired to be saved.
N == number of points that are desired to be distributed uniformly over the sphere.
filename == name of the output file without .dat termination
method == method used for the reconstruction; only inversion and rejection are the possible options

The output is:
filename.dat, filename.param. The first one save the (x,y,z) double positions in binary format in the following way:
x0y0z0x1y2z2.... The second one save the information saved in filename.dat.

Note:
Leaving the parameters by default you could simply type "make run_example1" and the output images will be saved under the same names and saved in the same directory specified. 

--------------------- Example 2 ----------------------------------------

This example evaluates if the transformation between vector state and orbital parameters is being well done. For such task we take the Earth-Sun ystem vector state at perigee and rotate it to a system with w,i and W. Then the tranformation is applied and the values of w, i, W, e, a, f are econfirmed as expected and printed. 

-------------------- Example 3 -----------------------------------------

The kepler equation is solve for some given values of e, M and with a given tolerance, the result is printed in screen and confirmed using Wolfram. 

------------------- Example 4 -------------------------------------------

This example creates the distribution of possible distance for systems near the configuration of the Earth-Sun system after a characterisit a period of time for the Earth-Sun system. The values of (x,y,vz) are known and (z,vx,vy) are supposed to follow a uniform distribution given by some a ( U(-a,a) ).

The input parameters are:

directory == name of the directory already created where the ouput of the example is desired to be saved
x, y, vz == vector state known values
mu == reduced mass
t_peri == time that has passed since pericenter; as explained the time given it the orbital period of the Earth-Sun system
N == Number of points to map the resultan distribution
a == value that characterize the unifort distribution supposed for the (vx,vy,z) values

Note:
Leaving the parameters by default you could simply type "make run_example#" and the output images will depend on the value chosen for a. The name of the .dat and .png images are as follow:

UpNEarthSunSystem.dat where N characterize the value of a, if its is 0.2 then N = 2 and the same goes for the png's. The defult examples are:
run_example2 == a=0.1 
run_example3 == a=0.2 
run_example4 == a=0.5 
run_example2 == a=0.7 
remeber a must be modified in main

