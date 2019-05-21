#ifndef _allvars_h
#define _allvars_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "input_output.h"
#include "integrator.h"

#define X 0
#define Y 1
#define Z 2

typedef struct{
  int Npart[6];  //number of particles of each type
  double mass[6]; //if explicit mass exist all have the same if Npart is different from 0; otherwise they are in file
  double time;
  double redshift;
  int flag_sfr; //flag for star formation rate
  int flag_feedback; //activate supernova explosions
  unsigned int npartTotal[6];
  int flag_cooling;
  int num_files;
  double Boxsize;
  double Omega0; // Density of baryons
  double OmegaLambda; // Density of dark matter
  double HubbleParam;
  int flag_stellarage;
  int flag_metals;
  unsigned int npartTotalHighWord[6];
  int flag_entropy_instead_u;
  char fill[256-6*4-6*8-2*8-2*4-6*4-2*4-4*8-2*4-6*4-1*4]; /* Fill to 256 bytes */
} io_encabezado;


// Structures of the particles
typedef struct{
  unsigned int id;
  float pos[3];
  float vel[3];
  float mass;
  float accel[3];
  float accelMag;
}Particles;

///////////////////////////////////////
////  Global variables
//////////////////////////////////////

extern Particles *Particlesptr1;
extern int Ntotal;
extern io_encabezado encabezado;

extern double eps;
extern double G;
extern double Totaltime;


#endif  // ! _allvars_h  
