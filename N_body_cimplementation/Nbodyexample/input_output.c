#include "allvars.h"

//////////////////////////////////////////////////////////////////
// Defining global variables declared in extern 
///////////////////////////////////////////////////////////////////

Particles *Particlesptr1;
int Ntotal;
io_encabezado encabezado;

////////////////////////////////////////////////////////////////////
// Defining and initilizing global variables declared in extern
//////////////////////////////////////////////////////////////////// 

double eps = 2;
double G = 43007.1;
double Totaltime = 1;

/// Routine for the initialization of the structure Particlesptr1
// argc: number of arguments of input by running the program
// argv: array that cotains the input
// opt: in case of 1 print the summy variable that read the size of the block of memory

int Initializaion(int argc, char *argv[], int opt)
{
  char * infile; // Variable for the name of the input file
  int i = 0;  //General purpose counter
  FILE * stream; //Pointer of file used to read initial conditions
  int dummy; //Used to read size of block and verify well reading

  //-----------------------------------------///////////////////////////////////////////////////////////////////////////////
  //-------Read file with input initial conditions
  if (argc<2){
    printf("The input type file was not supplied\n");
    exit(0);
  }
  else
    infile = argv[1];

  stream = fopen(infile,"rb");
  //----------------------------------------/////////////////////////////////////////////////////////////////////////////////


  //---------------------------------------//////////////////////////////////////////////////////////////////////////////////
  //------Reading general information about the configuration in the global type structure 
  // io_encabezado

  fread(&dummy, sizeof(int), 1 , stream);

  if (opt==1)
    printf("dummy %d\n",dummy);
  fread(&encabezado, sizeof(io_encabezado),1,stream);

  fread(&dummy, sizeof(int), 1, stream);

  if(opt==1)
    printf("dummy %d\n",dummy);

  //---------------------------------------//////////////////////////////////////////////////////////////////////////////////
  

  //---------------------------------------//////////////////////////////////////////////////////////////////////////////////
  //-------Defining and declarating gloabal variable Patricleptr1
  
  for(i=0; i<6; i++ )
    Ntotal += encabezado.Npart[i];

  Particlesptr1 = (Particles *) malloc( (size_t) Ntotal * sizeof(Particles) );
  //---------------------------------------//////////////////////////////////////////////////////////////////////////////////


  //---------------------------------------//////////////////////////////////////////////////////////////////////////////////
  //-------Initializing variable Patricleptr1             

  //  Postions
  fread(&dummy, sizeof(int), 1, stream);
  if (opt==1)
    printf("\ndummy %d\n",dummy);

  for(i=0; i<Ntotal; i++)
    {
      fread(&Particlesptr1[i].pos[X], sizeof(float) , 3, stream);
    }

  fread(&dummy, sizeof(int), 1, stream);
  if (opt==1)
    printf("dummy %d\n",dummy);
  //  Positions

  
  // Velocities
  fread(&dummy, sizeof(int), 1, stream);
  if (opt==1)
    printf("\ndummy %d\n",dummy);

  for(i=0; i<Ntotal; i++){
    fread(&Particlesptr1[i].vel[X],sizeof(float) , 3, stream);
  }

  fread(&dummy, sizeof(int), 1, stream);
  if(opt==1)
    printf("dummy %d\n",dummy);
  // Velocities
  

  // Identifications
  fread(&dummy, sizeof(int), 1, stream);
  if(opt==1)
    printf("\ndummy %d\n",dummy);

  for(i=0; i<Ntotal; i++){
    fread(&Particlesptr1[i].id,sizeof(unsigned int) , 1, stream);
  }

  fread(&dummy, sizeof(int), 1, stream);
  if (opt==1)
    printf("dummy %d\n",dummy);
  // Identifications

  
  // Calculating particles with explicit mass
  if (opt==1)
    printf("\nConditions to read mass\n");
  int nPartConMasa = 0;
  for(i = 0 ; i<6; i++)
    {
      if (encabezado.Npart[i]>0) // indicates existence of particles
	{
	  if (encabezado.mass[i]>0) // if true indicates that particles has a cte mass
	    nPartConMasa += 0;
	  else
	    {
	      nPartConMasa += encabezado.npartTotal[i];
	    }
	}
    }
  
  if(opt==1)
    printf("Particles with explicit mass: %d\n", nPartConMasa); //Particles with explicit mass
  // Calculating particles with explicit mass    

  
  /////////////  Masses when they are in encabezado (io_encabezado type variable in allvars.h) or explicit 
  if (nPartConMasa>0) // Condition to read memory block if they are explicit 
    {
      fread(&dummy, sizeof(dummy), 1, stream);
      if (opt==1)
	printf("dummy masa = %d\n",dummy);
    }
  

  // Routine to read explicit or implicit mass
  int nMin, nMax;
  nMin = nMax = 0;

  int j;
  for(j= 0; j<6; j++)
    {
      nMax = nMax + encabezado.npartTotal[j];

      if (opt==1)
	printf("type %d = %d particles [%d , %d]\n",j, encabezado.npartTotal[j], nMin, nMax);
      if (encabezado.npartTotal[j]>0)
	{
	  if (encabezado.mass[j]>0) // Condition to read particles if the mass is in the header
	    {
	      for(i = nMin ; i<nMax ; i++) 
		Particlesptr1[i].mass = encabezado.mass[j];
	      if (opt==1) //Read particles with explicit mass 
		printf("mass of such particles %lf\n\n", encabezado.mass[j]);
	    }
	  else
	    {
	      for(i = nMin ; i<nMax ; i++)
		fread(&Particlesptr1[i].id, sizeof(float) , 1, stream);
	    }
	}
      nMin = nMax;
    }
  // Routine to read explicit or implicit mass
  
  
  if (nPartConMasa>0) // Condition to read memory block if they are explicit
    {
      fread(&dummy, sizeof(dummy), 1, stream);
      if (opt==1)
	printf("dummy masa = %d\n",dummy);
    }  
  /////////////  Masses when they are in encabezado (io_encabezado type variable in allvars.h) or explicit

  
  //---------------------------------------//////////////////////////////////////////////////////////////////////////////////  
  
  fclose(stream); 

  return 0;
}

/// Routine to save configuration in a given time, in a file with name "namefile"
int imprimirSnapshoot(char *namefile, double t){

  int i,dummy; //general counter , rading purpose variable
  FILE *fSnaps = fopen(namefile,"wb"); //File to write the snapshot

  encabezado.time = t; //acutalizing time in header

  for(i= 0; i<6; i++)
    encabezado.mass[i] = 0; //Making clear that we are going to write mass explicitly

  dummy = 256; //size of the io_encabezado

  // printing encabezado
  fwrite(&dummy, sizeof (int), 1 , fSnaps);
  fwrite(&encabezado, sizeof(io_encabezado) , 1, fSnaps);
  fwrite(&dummy, sizeof (int), 1 , fSnaps);

  // Printing positions
  dummy = Ntotal*3*sizeof(float);
  fwrite(&dummy, sizeof (int), 1 , fSnaps);
  for(i = 0; i<Ntotal ; i++){
    fwrite(&Particlesptr1[i].pos[X], sizeof(float) , 3, fSnaps);
  }
  fwrite(&dummy, sizeof (int),1 , fSnaps);

  // Printing velocities
  fwrite(&dummy, sizeof (int),1 , fSnaps);
  for(i = 0; i<Ntotal ; i++){
    fwrite(&Particlesptr1[i].vel[X], sizeof(float) , 3, fSnaps);
  }
  fwrite(&dummy, sizeof (int),1 , fSnaps);

  // Printing ids
  dummy = Ntotal*sizeof(unsigned int);
  fwrite(&dummy, sizeof (unsigned int), 1 , fSnaps);
  for(i = 0; i<Ntotal; i++){
    fwrite(&Particlesptr1[i].id, sizeof(unsigned int) , 1, fSnaps);
  }
  fwrite(&dummy, sizeof (unsigned int),1 , fSnaps);
  
  // Printing explicit masses
  dummy = Ntotal*sizeof(float);
  fwrite(&dummy, sizeof (int),1 , fSnaps);
  for(i = 0; i<Ntotal ; i++){
    fwrite(&Particlesptr1[i].mass, sizeof(float) , 1, fSnaps);
  }
  fwrite(&dummy, sizeof (int),1 , fSnaps);

  return 0; 
}
