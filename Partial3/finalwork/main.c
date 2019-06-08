#include"allvars.h"

/*
The principal idea of this program is to evolve some initial conditions given 
a fluid represented by particles, each one with an associated mass. 
In general, in this version the interpolation of the navier-stokes equations 
is carried out for a fluid under a pressure field and with viscosity. 
 */

int main(int argc, char *argv[])
{

  // Number of points to run the simulation
  nPuntos = atoi(argv[1]);
  printf("\n%d particulas de SPH\n",nPuntos);

  
  aloca_memoria();
  printf("memoria alocada\n");

  /*
  // conditions to create fluid with density (in allvars.h) and with vx = 1 
  //  in region x E (0,1) and y E (0,1)
  genera_condiciones_iniciales_maya();
  printf("condiciones iniciales construidas\n"); 
  */


  // conditions to create to fluids with density1 and density2 (in allvars.h) with vx = 1 
  //  density1 down from x E (0,1) and y E (0.5,1) and density2 in x E (0,1) and y E (0.5,1) 
  genera_condiciones_iniciales_maya2(); //rountine to construct conitions for point1
  printf("condiciones iniciales construidas\n");
 

  /*
  // conditions to create to fluids with density1 and density2 (in allvars.h) with vx = 1
  //  density1 down from x E (0,1) and y E (0,1) and density2 in x E (4,5) and y E (0,1) 
  genera_condiciones_iniciales_maya3();
  printf("condiciones iniciales construidas\n"); 
  */
  
  // General parameters before evolution (generate the different output)
  dt = 1E-6;
  tiempoTotal = dt*2000;
  printf("Totaltime: %e \n", tiempoTotal);
  evoluciona();
  printf("Evolucion del sistema\n");

  
  libera_memoria();
  printf("memoria liberada\n");
  

  return 0;
}
