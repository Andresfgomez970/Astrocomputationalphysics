#include"allvars.h"

// Routine to alocate memory for the sph particles
//  respec
int aloca_memoria(void)
{

  sphPart = (SPH *)malloc( (size_t)nPuntos*sizeof(SPH) );
  if(sphPart == NULL){
    printf("Alocacion de sphPart fallo\n");
    exit(0);
  }

  d = (double *)malloc((size_t)(nPuntos-1)*sizeof(double));
  if(d == NULL){
    printf("Alocacion de d fallo\n");
    exit(0);
  }

  p = (size_t *)malloc((size_t)(nPuntos-1)*sizeof(size_t));
  if(p == NULL){
    printf("Alocacion de p fallo\n");
    exit(0);
  }

  return 0;
}

// Freee memory of used structures and arrays in the code
int libera_memoria(void)
{

  free(sphPart);
  free(d);
  free(p);
  
  return 0;
}
