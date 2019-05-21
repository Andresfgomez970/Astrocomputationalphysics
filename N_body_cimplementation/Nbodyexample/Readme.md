---------------- ABOUT THE PROGRAM

This program run a N body simulation based in some initial conditions given in gadget format (here galaxia.gad) and gives as output the different frames from its initial frame in the same format; nevertheless the philosophy of using less space because the initialization with the header (global variable named "encabezado.mass" form encabezado in allvars.h) conditions is not followed to write the ouptut of the program.

The program basicallly consist of four routines:

1. "Initialization": Read the initial configuration of particles. (defined in input_output.c).
2. "imprimirSnapshoot": Save the configuration of the system in a given time in a frame. (defined in input_output.c).
3. "Acceleration": Find the acceleration associated with each particle taking into account the interaction between particles. (defined in integrator.c)
4. "Evolve": Makes the evoulution of the system and save it in sequencial frames. (Here the program is designed to run with \
dt=0.001 and Totaltime=1). This variables are in input_output.c. This rutine also saves the circular velocity in time for \
a particle chosen arbitrarily, to illustrate the difference with the integration method of point3.

All is joined in allvars.h in order to only have to import this module in each .c file.

----------------- INSTRUCTIONS 

To run the program you shoud simply do: "make" (to compile) or "make run" (to run as explained) in the directory where everything lies. The program by defalult run the evolution of the initial configuration galaxia.gad, with a dt=0.001 and Ttotal=1 (Gyr units) and generates outputs of the form sim_eps_galaxy_#### where #### are digits and indicate the frame number; (each additional "one" respresents 1Gyr in time in the simulation). To change the globals "dt" "Totaltime" can be easily set in the main before evaluating Evolve.

------------------ RESULTS AND ANALYSIS

The simulation was run for the differnt smoothing distances proposed. It was observed that there is an optimal smoothening distance in the sence that reproduce a weak field interaction between the particles in such a system. From the fact that the velocity of particles in the system is of the order of 100 km/s = 100 kpc/Gyr and that the scale is of approximatelly of 1kpc and we have 7500 particles the relaxation time for the system is found to be of the order of 30Gyr, which implies that the system should not have destoy its strucutre as was observed in the simulation of esp=2 for examples.

Also it is observed that when eps=0 the interaction between some pairs of particles become so high that the some particles escape by irrealistic gravitational scaterring. Also, it is oberved with eps = 10 that the interaction became so little that the particles as all are no more a galaxy in the sense that are not gravitational bounded. The behavior in between 0.1 and 2 permit us to say that there is an optimal value for the smoothening distance.

Also the circular velocity as a function of time is saved in velocities.txt to compare it later with the behavior in 4. 