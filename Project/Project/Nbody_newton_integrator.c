#include "Nbody_Programs.h"


// Routine to calculate the acceleration of each particles in the
// global variables Particleptr1; which have the configurartion of
// the system in each instant of time
int Acceleration(){
  int i, j;
  double dr[3];
  double r,r3;
  double eps2;
  eps2 = eps*eps;

  for(i = 0; i<Ntotal; i++)
    {
      Particlesptr1[i].accel[X]=0; //  Accelerations are the differential equation
      Particlesptr1[i].accel[Y]=0; // that is: they are not accomulative
      Particlesptr1[i].accel[Z]=0;
      for (j = 0; j<Ntotal; j++)
	{
	  if (j!=i)
	    {
	      //Note that this is easier than managing another strucure
	      dr[X] =  Particlesptr1[i].pos[X] - Particlesptr1[j].pos[X]; 
	      dr[Y] =  Particlesptr1[i].pos[Y] - Particlesptr1[j].pos[Y];
	      dr[Z] =  Particlesptr1[i].pos[Z] - Particlesptr1[j].pos[Z];
	      r = sqrt( dr[X]*dr[X]+dr[Y]*dr[Y]+dr[Z]*dr[Z] + eps2); //eps2 = (smoothing distance)**2  
	      r3 = r*r*r;
	      Particlesptr1[i].accel[X]  += -G*Particlesptr1[j].mass*dr[X]/r3; //Gravitational field
	      Particlesptr1[i].accel[Y]  += -G*Particlesptr1[j].mass*dr[Y]/r3;
	      Particlesptr1[i].accel[Z]  += -G*Particlesptr1[j].mass*dr[Z]/r3;
	    }//Calculate how j particles affects i.
	}
    }// Claculate force over i 
  return 0;
}

// Routine to calculate the evolution frame for and the circular velocity at each time and save it.
int Evolve(double Totaltime, double dt, char *directory){
  int i, counter = 0; // general purpose counter and frame counter
  double t = 0; //initial time
  char namefiles[10000]; //array to save file names

  sprintf(namefiles,"%ssim_eps_galaxy_%.4d", directory,counter); // Initial frame 
  imprimirSnapshoot(namefiles,t); //Write initial frame 

  //////////////////////////////////////////////////
  int nr; //Number of particles to find mean circlar velocity in a given region 
  int framenumber; //total number of frames
  framenumber = (int) (Totaltime/dt + 10); //size of following array to that is used to save circular velocity in each frame
  double vc[framenumber]; //circular velocity in each frame for the initial particles chosen
  double x,y,z; //Variables to simplify calculations
  FILE *stream2; //file to ave circular velocities
  stream2 = fopen("velocities.txt","wb"); //file to save the time vs circular velocity for the given particles

  // Region of observation of the nr particles
  double minr = 1;
  double stepr=0.1;
  double zmax=0.01;

  // Contidion to count the number of particles in the last region to calculate nr. And so the mean divideing later by it
  for(i = 0; i<Ntotal; i++)
    {
      x = Particlesptr1[i].pos[X]; y = Particlesptr1[i].pos[Y]; z = Particlesptr1[i].pos[Z];

      if( x*x+y*y+z*z>minr && x*x+y*y+z*z<(minr+stepr) && z<zmax && z>-zmax )
	nr += 1;
    }

  //printf("particles in such positions %d\n",nr);

  int ids[nr];
  int idindex=0;

  // Saving in itial particles id's
  for(i = 0; i<Ntotal; i++)
    {
      x = Particlesptr1[i].pos[X]; y = Particlesptr1[i].pos[Y]; z = Particlesptr1[i].pos[Z];

      if( x*x+y*y+z*z>minr && x*x+y*y+z*z<(minr+stepr) && z<zmax && z>-zmax)
	{
	  ids[idindex] = Particlesptr1[i].id;
	  idindex+=1;
	}
    }
  
  
  while(t<Totaltime)
    {
      // appliaction of leapfrog method
      printf("time = %.10f dt = %.10f\n",t,dt);

      for(i = 0; i<Ntotal; i++)
	{
	  Particlesptr1[i].pos[X] += 0.5* Particlesptr1[i].vel[X]*dt ;
	  Particlesptr1[i].pos[Y] += 0.5* Particlesptr1[i].vel[Y]*dt ;
	  Particlesptr1[i].pos[Z] += 0.5* Particlesptr1[i].vel[Z]*dt ;
	}

      Acceleration();

      for(i = 0; i<Ntotal; i++)
	{
	  Particlesptr1[i].vel[X] = Particlesptr1[i].vel[X] + Particlesptr1[i].accel[X]*dt ;
	  Particlesptr1[i].vel[Y] = Particlesptr1[i].vel[Y] + Particlesptr1[i].accel[Y]*dt ;
	  Particlesptr1[i].vel[Z] = Particlesptr1[i].vel[Z] + Particlesptr1[i].accel[Z]*dt ;
	}

      for(i = 0; i<Ntotal; i++)
	{
	  Particlesptr1[i].pos[X] = Particlesptr1[i].pos[X] + 0.5* Particlesptr1[i].vel[X]*dt ;
	  Particlesptr1[i].pos[Y] = Particlesptr1[i].pos[Y] + 0.5* Particlesptr1[i].vel[Y]*dt ;
	  Particlesptr1[i].pos[Z] = Particlesptr1[i].pos[Z] + 0.5* Particlesptr1[i].vel[Z]*dt ;
	}
      // appliaction of leapfrog method

      
      // calculation of circular velocity in time = couter*dt
      vc[counter] = 0;
      for(i=0; i<nr;i++)
	{
	  x = Particlesptr1[ids[i]].pos[X]; y = Particlesptr1[ids[i]].pos[Y]; z = Particlesptr1[ids[i]].pos[Z];
	  vc[counter] += (x*Particlesptr1[ids[i]].vel[Y] - y*Particlesptr1[ids[i]].vel[X]);
	}
      vc[counter] = vc[counter]/sqrt(x*x+y*y)/nr;
      // calculation of circular velocity in time = couter*dt 
      
      // save the just calculated frame in a given time 
      counter += 1;
      sprintf(namefiles,"%ssim_eps_galaxy_%.4d", directory,counter);
      t += dt;
      imprimirSnapshoot(namefiles,t);

    } // Run over time

  // Routine to save time vs velocity 
  printf("%s","Integration done\n");
  for (i = 0; i < framenumber; i++)
    {
      t = i*dt;
      if (vc[i]>1)
	{
	  fwrite(&t, (size_t) sizeof(double) , 1 , stream2);
	  fwrite(&vc[i], (size_t) sizeof(double) , 1 , stream2);
	}
    }
  free(stream2);
  // Routine to save time vs velocity 
  
  
  return 0; 
}


