#ifndef _montecarlo_h
#define _montecarlo_h

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<string.h> 
#include<gsl/gsl_sort.h>

double Sky_Function(double theta, double R);
int Syntetic_Sky(int N , char* directory , char* filename, char* mehtod);
double Mean(double *p, int size, int initial);
double Deviation(double *p, int size, int initial);
double Function(double x);
int Add_Interval(double x1, double x2, double *x, int size); 
int Mean_Dev_In_I(double a, double b, int Np, int Nd, double *fmean, double *fdev);
int Map_Function_1D(double a, double b, int Np, int Nd, int Nmax, double tol,double *fs, double *xs);


  
#endif  // ! _montecarlo_h
