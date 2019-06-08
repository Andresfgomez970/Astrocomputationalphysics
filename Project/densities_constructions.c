#include "densities_constructions.h"

// To obtain r from E and f from E the formulaes are wrong
int r_final_uniform(double x, double y, double vz, double mu, double t_peri,  int N, double a, char * directory)
{
  int i;
  double v[DIM*2]; 
  double E; 
  double r[N]; 
  FILE * stream_rhistogram;
  double z, vx, vy; 
  orbital_Param *orbital_param;  
  double w = 2*M_PI/t_peri; // t_peri was in this case a period
  double rmax=-1, rmin=2; 
  char namefile[200]; 
  
  orbital_param = (orbital_Param *) malloc( (size_t) 1 * sizeof(orbital_Param)  );

  if(orbital_param == NULL)
    {
      printf("Alocation of orbital_param failed \n");
      exit(0);
    }
  
  for(i=0; i<N; i++)
    {
      z =  (2*drand48() - 1 )* a;//(2*drand48() - 1 )* 0.1;
      vx = (2*drand48() - 1 )* a;//(2*drand48() - 1 )* 0.1;
      vy = (2*drand48() - 1 )* a;
      v[0]=x; v[1]=vx; v[2]=y; v[3]=vy; v[4]=z; v[5]=vz;

      Vector_State_To_Orbital_Parameters( mu,  v, orbital_param);

      //Print_Orbital_State(orbital_param);

      //printf("\n"); 
      
      E = Bisection_Kepler( 0 , orbital_param[0].e , 1e-10);

      //printf("E value: %lf\n", E); 
      
      if ( orbital_param[0].e <= 1)
	{
	  r[i] = orbital_param[0].rmin/(1-orbital_param[0].e) * ( 1 - orbital_param[0].e * cos(E) );
	}
      else if( orbital_param[0].e == 1)
	{
	  r[i] = 2*mu/sqrt(vx*vx+vy*vy+vz*vz); // wrong
	}
      else
	{
	  r[i] = orbital_param[0].rmin/(orbital_param[0].e -1) * ( 1 - orbital_param[0].e * cosh(E) );
	}

      if (rmax<r[i])
	rmax = r[i];
      if (rmin>r[i])
	rmin = r[i];
      
      
    }             

  a = a*10;
  sprintf(namefile,"%s%s%0.f%s",directory,"Up",a,"EarthSunSystem.dat");
  stream_rhistogram = fopen(namefile, "w");
  
  for(i = 0; i < N; i++)
    {
      fprintf(stream_rhistogram,"%lf\n" ,r[i]);
    }
  printf("rmax: %lf, rmin: %lf\n", rmax, rmin );

  return 0; 
}
  
int Chi_Square_Euler(double x, double y, double vz, double mu,  int N, char * directory, size_t Npoints)
{ 
  //double rmin = 0.6, rmax = 10, fmin = 0, fmax= 2*M_PI, emin=0, emax=10, imin= -M_PI/2,
  //  imax = M_PI/2, wmin = 0, wmax = 2*M_PI, Wmin = 0,Wmax = 2*M_PI;

  double rmin = 0.6, rmax = 60, fmin = 0, fmax= 2*M_PI, emin=0, emax=10, imin= -M_PI/2,
    imax = M_PI/2, wmin = 0, wmax = 2*M_PI, Wmin = 0,Wmax = 2*M_PI;   

  // Note that division is taken by N-1 to incude the borders
  double rminstep=(rmax-rmin)/(N-1),fstep=(fmax-fmin)/(N-1), estep=(emax-emin)/(N-1), istep=(imax-imin)/(N-1)
    , wstep=(wmax-wmin)/(N-1), Wstep=(Wmax-Wmin)/(N-1); 
  double var0[2*DIM] = {rmin, fmin, emin, wmin, imin, Wmin};
  double varsteps[2*DIM] = {rminstep, fstep, estep, wstep, istep, Wstep};
    
  int Nvars = 2*DIM, k = 0, dummy;
  long long unsigned int total_config = 1, j=0;

  //state_Vector * state_vector; //Save all vector states obtained; this to evaluate possible constrains
  orbital_Param * orbital_param; //Save all the orbital parameters obtained
  
  
  double v[2*DIM] ={0,0,
		    0,0,
		    0,0}; //vector to be obtained from Obrbital_Parameters_To_State_Vector


  char namefile[200]; //Name of the file to save orbital_param[i], r_square[i]
  FILE *stream;  // Pointer to "namefile"
  FILE *stream2;  //Param file
  
  for(j = 0; j < Nvars; j++)
    {
      total_config *= N; 
    }
  
  //state_vector = (state_Vector *) malloc( (size_t) total_config* sizeof(state_Vector)  );
  orbital_param = (orbital_Param *) malloc( total_config * sizeof(orbital_Param)  );
  //double r_square[total_config];  
  double *r_square; //Save distance
  r_square = (double *) malloc( total_config * sizeof(double) ); 
  long long unsigned int steps; 
  
  for(j=0; j < total_config; j++)
    {
      dummy = j;
      for(k = 0; k < Nvars; k++)
	{
	  steps = (double) (dummy % (long long unsigned) N );
	  if (k==0){
	    orbital_param[j].rmin = steps * varsteps[k] + var0[k];
	    //printf("(%lld, %lf)\n", steps ,  orbital_param[j].a );
	  }
	  else if(k==1){
	    orbital_param[j].f = steps * varsteps[k] + var0[k];
	    //printf("(%lld, %lf)\n", steps ,  orbital_param[j].f );
	  }
	  else if(k==2){
	    orbital_param[j].e =  steps * varsteps[k] + var0[k];
	    //printf("(%lld, %lf)\n", steps ,  orbital_param[j].e );
	  }
	  else if(k==3){
	    orbital_param[j].w = steps *varsteps[k] + var0[k];
	    //printf("(%lld, %lf)\n", steps ,  orbital_param[j].w );
	  }
	  else if(k==4){
	    orbital_param[j].i = steps * varsteps[k] + var0[k];
	    //printf("(%lld ,%lf)\n", steps , orbital_param[j].i );
	  }
	  else if(k==5){
	    orbital_param[j].W = steps * varsteps[k] + var0[k];
	    //printf("(%lld, %lf)\n", steps ,  orbital_param[j].W );
	  }
       	  dummy = dummy/N;

	}

       
      Orbital_Parameters_To_State_Vector(mu, v, orbital_param[j] );
      r_square[j] = sqrt ( (v[0]-x)*(v[0]-x) + (v[2]-y)*(v[2]-y) + (v[5]-vz)*(v[5]-vz) ) ;
      
      /*
      printf("%s","\n");
      Print_Orbital_State(&orbital_param[j]);
      printf("%s","\n");
      printf("modeled and observed\n xm: %e, ym: %e, vzm: %e,\n xo: %e, yo: %e, zo: %e\n",x,y,vz,v[0],v[2],v[5]);
      printf("distance: %lf\n",r_square[j]);
      printf("%s","\n");
      */
      
    }

  /// Organize distances
  size_t *p;

  p = (size_t *) malloc( (size_t) (total_config) * sizeof(size_t) );

  if(p == NULL){
    printf("Alocation of p failed \n");
    exit(0);
  }

  gsl_sort_index(p, r_square, 1, total_config);
  
  sprintf(namefile,"%s%s",directory,"distances.dat");

  // Saving values for certain ranges of distances and obtaining maximum and minimums; as intervals
  //  are not further use, the same variables defined for them are used for such task

  stream = fopen(namefile,"w"); 
  for (j=0; j<Npoints; j++)
    {
      if( rmin > orbital_param[p[j]].rmin )
	rmin =  orbital_param[p[j]].rmin;
      if( rmax < orbital_param[p[j]].rmin )
	rmax = orbital_param[p[j]].rmin;

      if( fmin > orbital_param[p[j]].f )
	fmin =  orbital_param[p[j]].f;
      if( fmax < orbital_param[p[j]].f )
	fmax = orbital_param[p[j]].f;
      
      if( emin > orbital_param[p[j]].e )
	emin =  orbital_param[p[j]].e;
      if( emax < orbital_param[p[j]].e )
	emax = orbital_param[p[j]].e;

      if( wmin > orbital_param[p[j]].w )
        wmin =  orbital_param[p[j]].w;
      if( wmax < orbital_param[p[j]].w )
        wmax = orbital_param[p[j]].w;
      
      if( imin > orbital_param[p[j]].i )
	imin =  orbital_param[p[j]].i;
      if( emax < orbital_param[p[j]].i )
	imax = orbital_param[p[j]].i;
      
      if( Wmin > orbital_param[p[j]].W )
	Wmin =  orbital_param[p[j]].W;
      if( Wmax < orbital_param[p[j]].W )
        Wmax = orbital_param[p[j]].W;

      fprintf(stream,"%lf %lf %lf %lf %lf %lf %lf \n", orbital_param[p[j]].rmin, orbital_param[p[j]].f , orbital_param[p[j]].e,
	      orbital_param[p[j]].w, orbital_param[p[j]].i , orbital_param[p[j]].W, r_square[ p[j] ] );
    }

  sprintf(namefile,"%s%s",directory,"distances.param");
  stream2 = fopen(namefile,"w");
  
  fprintf(stream2,"%lf %lf\n",rmin,rmax);
  fprintf(stream2,"%lf %lf\n",fmin,fmax);
  fprintf(stream2,"%lf %lf\n",emin,emax);
  fprintf(stream2,"%lf %lf\n",wmin,wmax);
  fprintf(stream2,"%lf %lf\n",imin,imax);
  fprintf(stream2,"%lf %lf\n",Wmin,Wmax);
  fprintf(stream2,"%lf %lf\n",r_square[ p[0] ], r_square[ p[Npoints] ]); 

  free(orbital_param);
  free(p);
  free(r_square); 
  
  return 0; 
}

/// Problem: to obtain r from E and f from E the formulaes are wrong
int Vector_distribution(double x, double y, double vz, double mu, double t_peri,  int N, double a, char * directory)
{
  int i,j;
  double v[DIM*2];
  double E;
  double r[N];
  double z, vx, vy;
  orbital_Param *orbital_param, *reference_param;
  double w = 2*M_PI/t_peri; // t_peri was in this case a period
  double rmax=-1, rmin=2;
  char namefile[200];
  double vf[2*DIM], f; 
  state_Vector *state_vector; 
  int index; 
  
  orbital_param = (orbital_Param *) malloc( (size_t) 1 * sizeof(orbital_Param)  );
  reference_param = (orbital_Param *) malloc( (size_t) 1 * sizeof(orbital_Param)  );
  state_vector = (state_Vector *) malloc( (size_t) N * sizeof(state_Vector)  );

  reference_param[0].e = 0.016616;
  reference_param[0].W = M_PI/2;
  reference_param[0].i = M_PI/2;
  reference_param[0].rmin = 0.99984;
  reference_param[0].f = 0;
  reference_param[0].w = 0; 
  
  if(orbital_param == NULL)
    {
      printf("Alocation of orbital_param failed \n");
      exit(0);
    }

  i = 0; 
  while(i<N)
    {
      z =  (2*drand48() - 1 )* 0.01;//(2*drand48() - 1 )* 0.1;
      vx = (2*drand48() - 1 )* 0.01;//(2*drand48() - 1 )* 0.1;
      vy = (2*drand48() - 1 )* 0.01;
      v[0]=x; v[1]=vx; v[2]=y; v[3]=vy; v[4]=z; v[5]=vz;

      Vector_State_To_Orbital_Parameters( mu,  v, orbital_param);

      // Comparisons that reproduce the orbit
      if ( orbital_param[0].e > reference_param[0].e*(1+2./10.) || orbital_param[0].e < reference_param[0].e*(1-2./10.) )
		{
			printf("e %lf, i %d\n",orbital_param[0].e, i); 
			continue;
		}	

      else if ( orbital_param[0].rmin > reference_param[0].rmin*(1+2./10.) || orbital_param[0].rmin < reference_param[0].rmin*(1-2./10.) )
		{
			printf("a %lf, i %d\n",orbital_param[0].rmin, i); 
			continue;
		}	


      //pass conditions
      i++; 
	      

      E = Bisection_Kepler( 0 , orbital_param[0].e , 1e-10);

      if ( orbital_param[0].e <= 1)
	{
          r[i] = orbital_param[0].rmin/(1-orbital_param[0].e) * ( 1 - orbital_param[0].e * cos(E) );
        }
      else if( orbital_param[0].e == 1)
	{
          r[i] = 2*mu/sqrt(vx*vx+vy*vy+vz*vz);
	    }
      else
        {
          r[i] = orbital_param[0].rmin/(orbital_param[0].e -1) * ( 1 - orbital_param[0].e * cosh(E) );
	}

      f = 2*atan( sqrt( 1+orbital_param[0].e/(1-orbital_param[0].e) )*tan(E/2) );

      vf[0] = r[i]* cos(f); vf[1]=-mu*sin(f); vf[2]=r[i]*sin(f); vf[3]=mu*(orbital_param[0].e+cos(f));vf[4]=0; vf[5]=0;  

      Euler_angles_rotation(vf, orbital_param[0].w, orbital_param[0].i, orbital_param[0].W); 
      
      for(j=0; j<2*DIM; j++)
      	state_vector[i].v[j] = vf[j]; 

    }

  for (index=0 ;index < 2*DIM; index++)
    {
      Save_Vector_Index(state_vector, index, N, directory);
    }

  
  return 0; 

} 

int Save_Vector_Index(state_Vector *state_vector, int index, int N, char* directory)
{
  
  FILE * stream_rhistogram;
  double max, min;
  char namefile[200];
  int i;

  
  sprintf(namefile,"%s%s%d%s",directory,"SE",index,".dat");
  stream_rhistogram = fopen(namefile, "w");
 
  max = -1E6;
  min = 1E6;
 

  for(i = 0; i < N; i++)
    {
  
      if ( max < state_vector[i].v[index] )
	max = state_vector[i].v[index];
      if ( min > state_vector[i].v[index])
	min = state_vector[i].v[index];

      fprintf(stream_rhistogram,"%lf\n" ,state_vector[i].v[index] );


    }

  printf("density constructed for %d with min %e and max %e\n",index,min,max);



  return 0; 
}
