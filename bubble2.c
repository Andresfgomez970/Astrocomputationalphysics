#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define RANDOM ( drand48() * 100 ) 
#define NPART 10 
#define DIM 3
#define X 0
#define Y 1
#define Z 2 

typedef struct{
  int id;
  double pos[DIM];
}Particles;

FILE *stream; 
Particles *Particlesptr; 
int idlist[NPART];
double dlist[NPART]; 
int idlist0[NPART];
double dlist0[NPART];

int Intialization(Particles *, int );
int Print_arrays(int ,int *, double *);
int Organization(void);


int main(int argc, char *argv[]){

  int id_part;  
  int i;
  
  printf( "Enter particle to find:");
  id_part = getchar();
  
  Particlesptr = (Particles *) malloc( (size_t) NPART * sizeof(Particles) );

  Intialization( Particlesptr , id_part);

  Organization(); 
  
  stream = fopen("Positions2.dat","w"); 
  
  for(i = 0; i<NPART; i++){
    //fwrite(&Particlesptr[i].pos, sizeof(double),DIM,stream);
    //fwrite(&Particlesptr[i].pos[X], sizeof(double),1,stream);
    //fwrite(&Particlesptr[i].pos[Y], sizeof(double),1,stream);
    //fwrite(&Particlesptr[i].pos[Z], sizeof(double),1,stream);
    fprintf(stream,"%lf %lf %lf \n",Particlesptr[i].pos[X], Particlesptr[i].pos[Y],Particlesptr[i].pos[Z]);
  }
  
  
  Print_arrays( (int) NPART, idlist0, dlist0);
  printf("\n");
  Print_arrays( (int) NPART, idlist, dlist);
    
  return 0; 
}

// This function assigns inital values to the distances and ids
int Intialization(Particles *Particlesptr, int id_ref){
  int i;
  double x, y, z;

  for(i= 0; i<NPART; i++ ) {
    x = RANDOM; y = RANDOM; z = RANDOM;
    Particlesptr[i].id = i;
    Particlesptr[i].pos[X] = x;
    Particlesptr[i].pos[Y] = y;
    Particlesptr[i].pos[Z] = z;
  }

  
  for(i=0 ; i<NPART ; i++ ){
    idlist[i] = i;
    x = ( Particlesptr[i].pos[X]-Particlesptr[id_ref].pos[X] );
    y = ( Particlesptr[i].pos[X]-Particlesptr[id_ref].pos[Y] );
    z = ( Particlesptr[i].pos[X]-Particlesptr[id_ref].pos[Z] );
    dlist[i] = sqrt( x*x + y*y + z*z );
    idlist0[i] = idlist[i];
    dlist0[i] = dlist[i];
  }

  return 0; 
} 

int Print_arrays(int N, int arr1[N], double arr2[N]){

  int i;
  
  for(i= 0 ; i<N; i++)
    printf("%d %lf\n", arr1[i],arr2[i]); 

  
  return 0; 
}  

int Organization(void){

  int i, j;
  int id1, id2;
  double d1,d2;
  for (i=0; i<NPART; i++)
    {
      for(j=0;j< (NPART-1 );j++)
	{
	  d1 = dlist[j];
	  d2 = dlist[j+1];
	  id1 = idlist[j];
	  id2 = idlist[j+1];
	  if (dlist[j]>dlist[j+1])
	    {
	      dlist[j+1] = d1;
	      dlist[j] = d2;
	      idlist[j+1] = id1;
	      idlist[j] = id2;
	    }

	}
    }
  
  
  return 0; 
}
