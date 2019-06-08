
#include"allvars.h"


// Routine to find the N_vecinos to a particle
int vecinos(int nParticula)
{

  int i, counter=0; // general counters 
  int *indice; //array to save index of the particles exclusing the particle of interest

  // Calculate ditances to the particle of interest an assign index memoery and values excluding it
  indice = (int *)malloc( (size_t)(nPuntos-1)*sizeof(int) ); 

  for( i=0; i<nPuntos; i++ )
    {
      if( i!=nParticula )
	{
	  indice[counter] = sphPart[i].id;
	  d[counter++] = sqrt( 
			    ( sphPart[nParticula].pos[X] - sphPart[i].pos[X])*(sphPart[nParticula].pos[X] - sphPart[i].pos[X])+
			    ( sphPart[nParticula].pos[Y] - sphPart[i].pos[Y])*(sphPart[nParticula].pos[Y] - sphPart[i].pos[Y]) );
	}
    }

  // sort the pointers in p, d[p[0]] is the nearest distance to a particle from the one studied
  gsl_sort_index(p, d, 1, nPuntos-1);

  for( i=0; i<N_vecinos; i++ )
    {
      sphPart[nParticula].vecinos[i] = indice[p[i]];
      sphPart[nParticula].distanciaVecinos[i] = d[p[i]];
    }

  // asignate "escala de suavizado"
  sphPart[nParticula].h = d[p[N_vecinos-1]];

  // free memory 
  free(indice);
  
  return 0;
}

// Routine that calculates the acceleration of the system
int acceleracion(void)
{

  int i, j, b; // general counters

  // Variable to effectuate calculation in the acceleration equation calculations
  //  principally to simplyfy calculations in viscosity 
  double rab, mb; 
  double muab,alpha,beta,eta2,rhoa,rhob,rhoab; 
  double vdotr;
  double piab; 

  // parameter for viscosity 
  alpha = 1;
  beta = 0.01;
  
  // Aceleration equation based in field pressure and viscosity
  for( i=0; i<nPuntos; i++ )
    {
      sphPart[i].accel[X] = sphPart[i].accel[Y] = 0.0;

      for( j=0; j<N_vecinos; j++ )
	{
	  rab = sphPart[i].distanciaVecinos[j];
	  b = sphPart[i].vecinos[j];
	  mb = sphPart[b].masa;

	  //// Calculation of viscosity accoring to Monaghan_1992.pdf
	  // vdot of rab and vab
	  vdotr = ( sphPart[i].pos[X] - sphPart[b].pos[X] )*( sphPart[i].vel[X] - sphPart[b].vel[X] ) + (sphPart[i].pos[Y] - sphPart[b].pos[Y])*( sphPart[i].vel[Y] -  sphPart[b].vel[Y] );
	  rhoa = sphPart[i].densidad;
	  rhob = sphPart[b].densidad;
	  
	  
	  if (vdotr <0)
	    {
	      eta2 = sphPart[i].h * sphPart[i].h * 0.01; // asignation according to article Monaghan_1992.pdf
	      muab  = sphPart[i].h*vdotr/(rab*rab + eta2); 
	      rhoab = (rhoa+rhob)/2.;
	      piab = - (alpha*sphPart[i].cs *muab + beta*muab*muab )/ rhoab;
	      
	    }
	  else
	    piab = 0; 
	  	  	  
	  // acceleration assignation 
	  sphPart[i].accel[X] += -mb*( (sphPart[i].presion/(rhoa*rhoa) ) + (sphPart[b].presion/(rhob*rhob)) + piab  )*nabla_kernel(rab, sphPart[i].h, 0, i, b) ;
	  
	  
	  	  
	}
      
    }

  return 0;
}

// Rountine that evolve the system and save the outpt
int evoluciona(void)
{

  int i, j, b, counter;
  double t, mb, rab, vab[2], dw[2];
  double dDensidad;
  char salida[500];
  FILE *fSnaps;

  counter = 0;
  
  while( t<tiempoTotal )
    {
     
      
      // mueve posiciones y velocidad with leap-frog kdk
      acceleracion();
      
      // kick
      for( i=0; i<nPuntos; i++ )
	{
	  sphPart[i].vel[X] = sphPart[i].vel[X] + 0.5*dt*sphPart[i].accel[X];
	  sphPart[i].vel[Y] = sphPart[i].vel[Y] + 0.5*dt*sphPart[i].accel[Y];
	}
      
      // drift
      for( i=0; i<nPuntos; i++ )
	{
	  sphPart[i].pos[X] = sphPart[i].pos[X] + dt*sphPart[i].vel[X];
	  sphPart[i].pos[Y] = sphPart[i].pos[Y] + dt*sphPart[i].vel[Y];
	}
      
      acceleracion();
      
      // kick
      for( i=0; i<nPuntos; i++ )
	{
	  sphPart[i].vel[X] = sphPart[i].vel[X] + 0.5*dt*sphPart[i].accel[X];
	  sphPart[i].vel[Y] = sphPart[i].vel[Y] + 0.5*dt*sphPart[i].accel[Y];
	}

      // actualiza vecinos
      for( i=0; i<nPuntos; i++ )
	vecinos(i);


#ifdef CONTINUIDAD
      //evolucion del campo de densidad y presion con ecuacion de continuidad
      for( i=0; i<nPuntos; i++ )
	{
	  dDensidad = 0.0;
	  for( j=0; j<N_vecinos; j++ )
	    {
	      rab = sphPart[i].distanciaVecinos[j];
	      b = sphPart[i].vecinos[j];
	      mb = sphPart[b].masa;
	      vab[X] = sphPart[i].vel[X] - sphPart[b].vel[X]; 
	      vab[Y] = sphPart[i].vel[Y] - sphPart[b].vel[Y]; 
	      dw[X] = nabla_kernel(rab, sphPart[i].h, 0, i, b);	      
	      dw[Y] = nabla_kernel(rab, sphPart[i].h, 1, i, b);	      

	      dDensidad += mb*( vab[X]*dw[X] + vab[Y]*dw[Y] );
 
	    }

	  sphPart[i].densidad += dDensidad*dt;	  
	  sphPart[i].presion = cs*cs*sphPart[i].densidad;

	}
#else      
      //evolucion del campo de densidad y presion con sumatoria
      for( i=0; i<nPuntos; i++ )
	{
	  sphPart[i].densidad = 0.0;
	  for( j=0; j<N_vecinos; j++ )
	    {
	      rab = sphPart[i].distanciaVecinos[j];
	      mb = sphPart[sphPart[i].vecinos[j]].masa;
	      sphPart[i].densidad += mb*kernel(rab,sphPart[i].h); 
	    }
	  sphPart[i].presion = cs*cs*sphPart[i].densidad;
	}
 #endif     

      t += dt; 
      if(counter%10==0) // save each 10*dt a frame wiith information
	{
	  printf("iteration = %d\n",counter);
#ifdef CONTINUIDAD
	  // directory and name to save the ouput
	  sprintf(salida,"data/punto1/fluido_cont_%.5d.dat",counter);
#else
	  // directory and name to save the output
	  sprintf(salida,"data/punto1/fluido_%.5d.dat",counter);
#endif
	  fSnaps = fopen(salida,"w");
	  for( i=0; i<nPuntos; i++ )
	    fprintf(fSnaps,"%d %lf %lf %lf %lf %lf %lf %lf\n",
		    sphPart[i].id,
		    sphPart[i].pos[X], sphPart[i].pos[Y],
		    sphPart[i].vel[X], sphPart[i].vel[Y],
		    sphPart[i].masa, sphPart[i].densidad,
		    sphPart[i].presion);
	  fclose(fSnaps);

	}

      counter++;

    }
  
  return 0;
}
