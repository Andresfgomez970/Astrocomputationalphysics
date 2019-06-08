#include"allvars.h"

// Kernel used for the interpolation the density; literal equation from Monaghan_1992.pdf page 12 
double kernel(double r, double h)
{
  double q;

  q = r/h;

  if( (q>=0.0) && (q<=1.0) )
    return (  (10.0 /(7.0*M_PI) ) / (h*h) ) * ( 1.0 - 1.5*q*q + (3.0/4.0)*q*q*q  );

  if( (q>1.0) && (q<=2.0) )
    return ( (10.0/(7.0*M_PI))/(h) )*(  0.25*(2.0-q)*(2.0-q)*(2.0-q)  );
	  
  return 0.0;
}

// Kernel used for the interpation in the acceleration equation; literal equations of the presentation 
double nabla_kernel(double r, double h, int coord, int a, int b)
{

  double q, x;

  q = r/h;
  x = fabs( sphPart[a].pos[coord] - sphPart[b].pos[coord] );
  
  if( (q>=0.0) && (q<=1.0) )
    return (  ( 10.0/(7.0*M_PI) ) / (h*h) )*( -( 3.0/(h*h) )*x + ( 9.0/(4.0*h*h) )*q*x  );
    
  if( (q>1.0) && (q<=2.0) )
    return ( (10.0/(7.0*M_PI))/(h*h) )*( -(3.0/(4.0*h))*(2.0-q)*(2.0-q)*(x/r) );
	  
  return 0.0;
}
