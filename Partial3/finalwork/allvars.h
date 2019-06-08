#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include<gsl/gsl_errno.h>
#include<gsl/gsl_rng.h>
#include<gsl/gsl_sort.h>

#include"proto.h" 

#define X 0
#define Y 1
#define N_vecinos 64 //number of neig used to calculate intereaction for each particle


// General structure for SPH particle in 2 DIM 

typedef struct
{
  int id;
  double pos[2];
  double vel[2];
  double accel[2];
  double masa;
  int vecinos[N_vecinos];
  double distanciaVecinos[N_vecinos];
  double h; // maximum distance to the farthes neig 
  double densidad;
  double presion;
  double cs; // Sound velocity (depend in genera of the medium; takes constant for a given fluid here)
} SPH;


///////////////////////////////////////////
/// Global variables
///////////////////////////////////////////
extern SPH *sphPart;
extern int nPuntos;

extern double *d; // variable to save distance to given particle 
extern size_t *p; // variable asked by gsl to make sort of distances

extern double masaTotal; //for simulation maya
extern double densidad; 
extern double cs;

extern double masaTotal1; //for simulation maya1-2 
extern double masaTotal2;

extern double densidad1;
extern double densidad2; 

extern double cs1;
extern double cs2;

// for all simulations
extern double nu;
extern double tiempoTotal;
extern double dt; 
