/*
---------------- ABOUT THE PROGRAM

This program run a N body simulation based in some initial conditions given in gadget format (here galaxia.gad) and gives an output the different frames from its initial frame in the same format; nevertheless the philosophy of using in the header global variable named "encabezado.mass" from encabezado is not followed here. 

The program basicallly of four routines: 

1. Initialization: Read the initial configuration of particles. (defined in input_output.c). 
2. imprimirSnapshoot: Save the configuration of the system in a given time in a frame. (defined in input_output.c).
3. Acceleration: Find the acceleration associated with each particle taking into account the interaction with the rest.  
(defined in integrator.c)
4. Evolve: Makes the evoulution of the system and save it in sequencial frames. (Here the program is designed to run with dt=0.001 and Totaltime=1). This variables are in input_output.c. This rutine also saves the circular velocity in time for a particle chosen arbitrarily to illutrate the difference with the integration mehod of point4. 

All is joined in allvars in order to only have to import this module in each .c file.

*/


#include "allvars.h"

int main(int argc, char *argv[]){  


  //debugger option to see of the data is being well readed 
  int opt = 0; 
  Initializaion(argc,argv, opt);

  //Explicit assignment of integration step (note that total time can be easily modified) as well as any global
  double dt = 0.001;

  printf("Frames are being calculated\n");
  // See at begining: 4.Evolve
  Evolve(Totaltime,dt);

  // Freeing memory assigned to the global varialble Particlesptr1 
  free(Particlesptr1); 
  return 0; 
  
}
