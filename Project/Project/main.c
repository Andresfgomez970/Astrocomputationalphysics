#include"allvars.h"

int main(int argc, char *argv[])
{

  
  /*  
  ///////////////////////////////////////////
  /// Example 1
  ///////////////////////////////////////////

  //Do uniform sky for N = 100 and N = 100000
  
  char* directory = "data/montecarlo/synthetic/"; //Place to save the output
  
  int N = 20000;
  char* filename = "syntheticrej20000"; 
  char* method = "rejection"; 

  Syntetic_Sky( N, directory , filename , method);   
 
  
  filename = "syntheticinv20000"; 
  method = "inversion"; 
  
  Syntetic_Sky( N, directory , filename , method);   
  */
  

  /*
  ///////////////////////////////////////////
  /// Example 2
  //////////////////////////////////////////

  // Doing a prove on the obtation of the parameters for approximate orbit of the Earth-Sun 
  // system in the perigee from xy plane

  orbital_Param *orbital_param;
  
  double v[2*DIM] = {0.983223592,0,
		     0,1.0168445783306999,
		     0,0};

  double w = M_PI, i = M_PI/6, W = M_PI/2; 

  double Ms = 1.989e30;
  double Me = 5.97219e24;
    
  double mu = 1 + Me/Ms; 

  // ---- Allocation of orbital parameters
  orbital_param = (orbital_Param *) malloc( (size_t) 1 * sizeof(orbital_Param)  );

  if(orbital_param == NULL)
    {
      printf("Alocation of orbital_param failed \n");
      exit(0);
    }
  //---- 
 
  //---- Print initial vector and orbital parameters
  printf("%s","Initial vector and orbital parameters:\n");
  Print_Vector_State(v);
  Vector_State_To_Orbital_Parameters(mu,v,orbital_param);
  Print_Orbital_State(orbital_param);
  printf("%s","\n"); 
  printf("Vector state obtained by the orbital parameters:\n");
  Orbital_Parameters_To_State_Vector( mu, v, orbital_param[0]);
  Print_Vector_State(v);
  printf("%s","\n"); 
  //----- 

  
  
  //---- Put vector in orbit with (w,i,W)
  Euler_angles_rotation(v, w, i, W); //rotate v
  //---- 

  //---- Print vector and orbital parameters in orbit with following parameters
  printf("%s","\n\nVector and orbital parameters after rotation:\n");
  Print_Vector_State(v);
  Vector_State_To_Orbital_Parameters(mu,v,orbital_param); //find orbital parameters 
 
  Print_Orbital_State(orbital_param);
  printf("%s","\n");

  printf("Vector state obtained by the orbital parameters:\n");
  Orbital_Parameters_To_State_Vector( mu, v, orbital_param[0]);
  Print_Vector_State(v);
  //-----
  */
  

  
  /*
  ///////////////////////////////////////////
  /// Example 3
  //////////////////////////////////////////

  // Example solving for the Eccentric anomaly with bisection method for a given tolerance and
  //  mean anomaly, and eccentricity.
  
  double E = 0; 
  double M = 2.2715;
  double e = 0.75;
  double tol = 1e-10; 
  E = Bisection_Kepler( M, e, tol);
  printf("The determined value for the Eccentric anomaly is: %.10lf\n", E); 
  */

  /*
  ///////////////////////////////////////////
  /// Example 5
  //////////////////////////////////////////    


  // Density try for eath-sun system; only chage the value of a and direcoty to save the output and images
  double UT = 58.126363714904336; 
  double t_peri = 366.25/UT;
  double x = 0, vz = 1.0168445783306999, y=0.983223592;   
  double mu = 1 + 1e-5 ;  
  int N = 100000;
  double a = 1;
  char* directory="data/montecarlo/densities/"; 
  
  Vector_distribution( x, y, vz, mu, t_peri,  N, a, directory); 
  */
    

  /*
  ///////////////////////////////////////////
  /// Example 6
  //////////////////////////////////////////    

  // This part runs the evolution of a galactic configuration that follows GADGET format
  
  //debugger option to see of the data is being well readed
  int opt = 0;
  Initializaion(argc, argv, opt);

  //Explicit assignment of integration step (note that total time can be easily modified) as well as any global
  double dt = 0.001;

  printf("Frames are being calculated\n");

  // See at begining of input_output.c for initialization of Totaltime and other variables
  char *directory;
  directory = "data/n_body_config/";
  Evolve(Totaltime,dt,directory);
  
  // Freeing memory assigned to the global varialble Particlesptr1
  free(Particlesptr1);
  */


  /*
  ///////////////////////////////////////////
  /// Example 7
  ////////////////////////////////////////// 
  // Adaptative montecarlo sample

  
  int Nmax = 1E5; 
  double a=0, b=7, tol = 3e-3;
  int Np=1, Nd=200; //why does it take so long to converge?

  //Np: number of points xi to calculate fmean_i_I in a given interval
  //Nd: number of points of f's to calculate fmean_I in the inteval

  double fs[Nmax],xs[Nmax]; 
  int number_of_points; 

  number_of_points = Map_Function_1D(a, b, Np, Nd, Nmax,tol,fs, xs) - 1; 

  Save_X_vs_Y(xs, fs,number_of_points, 4, "function.txt"); 
  */

  
  ///////////////////////////////////////////
  /// Example 8
  ////////////////////////////////////////// 

  double UT = 58.126363714904336;
  double t_peri = 366.25/UT; 
  double x = 0, vz = 1.0168445783306999, y=0.983223592;                                                                                    
  double mu= 1 + 1e-5 ;                                                                                                                   
  int N = 10;
  char* directory="data/montecarlo/densities/";         
  size_t Npoints = 10000;
  
  //printf("Maximum integer: %lld\n",ULLONG_MAX);
  Chi_Square_Euler( x, y, vz, mu,  N, directory, Npoints);
  

  return 0; 
}
