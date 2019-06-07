#ifndef _two_body_analytical_h
#define _two_body_analytical_h

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<gsl/gsl_blas.h>
#include<string.h>

#define DIM 3
#define X 0
#define Y 1
#define Z 2
#define RTD 180/M_PI
#define DTR M_PI/180

typedef struct
{
  double rmin;
  double f;
  double e; 

  double w;
  double i;
  double W;


} orbital_Param;

int Rotation(double theta , double *v, char*axis); 
int Round_To_N_Decimal(double *r,int n);
int Euler_angles_rotation(double *v, double w, double i, double W);
int Print_Vector_State(double *v);
double Dot_Product(double v[DIM],double w[DIM]);
int Cross_Product(double r[DIM],double v[DIM], double h[DIM]);
int Assign_Vector(double *v, double *pos, double *vel);
int Sum_Vectors(double v[DIM],double w[DIM], double sum[DIM]);
int Multiply_Vector_By_C(double v[DIM], double c, double r[DIM]);
double Norm(double v[DIM]);
int Vector_State_To_Orbital_Parameters(double mu, double *v, orbital_Param * orbital_param); 
int Print_Orbital_State(orbital_Param * orbital_param); 
double Kepler(double E, double e,double M);
double Bisection_Kepler( double M, double e, double tol);
int Orbital_Parameters_To_State_Vector(double mu, double *v, orbital_Param orbital_param);

#endif // ! _two_body_analytical
