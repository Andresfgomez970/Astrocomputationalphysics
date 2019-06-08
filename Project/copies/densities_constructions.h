#ifndef _density_constructions_h
#define _density_constructions_h

#include "montecarlo.h"
#include "two_body_analytical.h"
#include <float.h>
#include <limits.h>
#include <gsl/gsl_sort.h>


int r_final_uniform(double x, double y, double vz, double mu, double t_peri ,int N, double a, char * directory); 
int Vector_distribution(double x, double y, double vz, double mu, double t_peri,  int N, double a, char * directory);

typedef struct{
  double v[6]; 

} state_Vector; 

int Save_Vector_Index(state_Vector *state_vector, int index, int N, char* directory);
int Chi_Square_Euler(double x, double y, double vz, double mu,  int N, char * directory, size_t Npoints);

#endif  // ! _density_constructions_h   
