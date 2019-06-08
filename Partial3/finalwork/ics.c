#include"allvars.h"

// Inital conitions for fluid between x E (0,1) and y E (0,1)
int genera_condiciones_iniciales_maya()
{
  int i, j, contador;
  double Lx=1.0, Ly=1.0;
  masaTotal = densidad * Lx *Ly;
  double deltaL, mp, rab, mb;
  
  // genera ids
  for( i=0; i<nPuntos; i++ )
    sphPart[i].id = i;

  // genera posiciones
  deltaL = (1.0/(sqrt(nPuntos)-1))*sqrt(masaTotal/densidad);

  contador = 0;
  for( i=0; i<sqrt(nPuntos); i++ )
    {
      for( j=0; j<sqrt(nPuntos); j++ )
	{
	  sphPart[contador].pos[X] = i*deltaL;
	  sphPart[contador].pos[Y] = j*deltaL;
	  contador++;
	}
    }

  // genera velocidades
  for( i=0; i<nPuntos; i++ )
    {
      sphPart[i].vel[X] = 0.0;
      sphPart[i].vel[Y] = 0.0;
    }

  // genera masas
  mp = masaTotal/nPuntos;
  for( i=0; i<nPuntos; i++ )
    sphPart[i].masa = mp;

  
  // encuentra vecinos
  for( i=0; i<nPuntos; i++ )
    vecinos(i);
  
  // genera densidad
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
  
  FILE *fIcs = fopen("condiciones_iniciales.dat","w");
  for( i=0; i<nPuntos; i++ )
    fprintf(fIcs,"%d %lf %lf %lf %lf %lf %lf %lf\n",
	    sphPart[i].id,
	    sphPart[i].pos[X], sphPart[i].pos[Y],
	    sphPart[i].vel[X], sphPart[i].vel[Y],
	    sphPart[i].masa, sphPart[i].densidad,
	    sphPart[i].presion);
  fclose(fIcs);

  FILE *fvecinos = fopen("vecinos.dat","w");
  int interes = sqrt(nPuntos);
  fprintf(fvecinos,"%d %lf %lf\n",
	    sphPart[interes].id,
	    sphPart[interes].pos[X], sphPart[interes].pos[Y]);
  for( i=0; i<N_vecinos; i++ )
    fprintf(fvecinos,"%d %lf %lf\n",
	    sphPart[sphPart[interes].vecinos[i]].id,
	    sphPart[sphPart[interes].vecinos[i]].pos[X], sphPart[sphPart[interes].vecinos[i]].pos[Y]);
  fclose(fvecinos);
  
  return 0;
}


// conditions to create to fluids with density1 and density2 (in allvars.h) with vx = 1
//  density1 down from x E (0,1) and y E (0.5,1) and density2 in x E (0,1) and y E (0.5,1) 
int genera_condiciones_iniciales_maya2()
{

  int i, j, contador;
  double Lx = 1, Ly = 1;
  masaTotal1 = densidad1 * Lx *Ly;
  masaTotal2 = densidad2 * Lx *Ly; 
  double deltaL, mp1, mp2, rab, mb;

  // genera ids
  for( i=0; i<nPuntos; i++ )
    sphPart[i].id = i;

  deltaL = (1.0/(sqrt(nPuntos)-1))*sqrt(Lx*Ly);
  
  mp1 = densidad1/nPuntos; //if density1 > density2, then the more dense part is down
  mp2 = densidad2/nPuntos;
  
  contador = 0;
  for( i=0; i<sqrt(nPuntos); i++ )
    {
      for( j=0; j<sqrt(nPuntos)/2; j++ )
	{
	  sphPart[contador].pos[X] = i*deltaL;
	  sphPart[contador].pos[Y] = j*deltaL;
	  sphPart[contador].masa = mp1;
	  sphPart[contador].cs = cs1;
	  sphPart[contador].vel[X] = 1.0;
	  sphPart[contador].vel[Y] = 0.0;
	  contador++; 
	}
    }

  
  
  for( i=0; i<sqrt(nPuntos); i++ )
    {
      for( j=sqrt(nPuntos)/2; j<sqrt(nPuntos); j++ )
	{
	  sphPart[contador].pos[X] = i*deltaL;
	  sphPart[contador].pos[Y] = j*deltaL;
	  sphPart[contador].masa = mp2;
	  sphPart[contador].cs = cs1;
	  sphPart[contador].vel[X] = 1.0;
	  sphPart[contador].vel[Y] = 0.0;
	  contador++; 
	}
    }
  
  // encuentra vecinos
  for( i=0; i<nPuntos; i++ )
    vecinos(i);

  // genera densidad
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

  
  FILE *fIcs = fopen("data/punto1/condiciones_iniciales.dat","w");
  for( i=0; i<nPuntos; i++ )
    fprintf(fIcs,"%d %lf %lf %lf %lf %lf %lf %lf\n",
	    sphPart[i].id,
	    sphPart[i].pos[X], sphPart[i].pos[Y],
	    sphPart[i].vel[X], sphPart[i].vel[Y],
	    sphPart[i].masa, sphPart[i].densidad,
	    sphPart[i].presion);
  fclose(fIcs);


  return 0;
}


// conditions to create to fluids with density1 and density2 (in allvars.h) with vx = 1
//  density1 down from x E (0,1) and y E (0,1) and density2 in x E (4,5) and y E (0,1) 
int genera_condiciones_iniciales_maya3()
{

  int i, j, contador;
  double Lx = 1, Ly = 1;
  masaTotal1 = densidad1 * Lx *Ly;
  masaTotal2 = densidad2 * Lx *Ly; 
  double deltaL1,deltaL2, mp1, mp2, rab, mb;

  // genera ids
  for( i=0; i<nPuntos; i++ )
    sphPart[i].id = i;

  // genera posiciones
  deltaL1 = (1.0/(sqrt(nPuntos)-1))*sqrt(masaTotal1/densidad1);
  deltaL2 = (1.0/(sqrt(nPuntos)-1))*sqrt(masaTotal2/densidad2);
  printf("%lf, %lf", deltaL1, deltaL2);

  // first particles
  contador = 0;
  for( i=0; i<sqrt(nPuntos/2); i++ )
    {
      for( j=0; j<sqrt(nPuntos/2); j++ )
	{
	  sphPart[contador].pos[X] = j*deltaL1;
	  sphPart[contador].pos[Y] = i*deltaL1;
	  contador++; 
      	}
    }
  
  // second particles
  for( i=0; i<sqrt(nPuntos/2); i++ )
    {
      for( j=0; j<sqrt(nPuntos/2); j++ )
	{
	  sphPart[contador].pos[X] = 4 + j*deltaL1;
	  sphPart[contador].pos[Y] = i*deltaL1;
	  contador++; 
      	}
    }


  // genera velocidades; this remain equal
  
  for( i=0; i<nPuntos/2; i++ )
    {
      sphPart[i].vel[X] = 10000;//1.0;
      sphPart[i].vel[Y] = 0.0;
    }
  
  for( i=nPuntos/2; i<nPuntos; i++ )
    {
      sphPart[i].vel[X] = -10000;//-1.0;
      sphPart[i].vel[Y] = 0.0;
    }
  
  // genera masas
  mp1 = masaTotal1/nPuntos/2; //if density1 > density2, then the more dense part is down 
  mp2 = masaTotal2/nPuntos/2;
  
  for(i = 0; i < nPuntos/2 ; i++)
    sphPart[i].masa = mp1;

  for(j = nPuntos/2; j<=nPuntos; j++)
    sphPart[j].masa = mp2; 


  for(i = 0; i < nPuntos/2 ; i++)
    sphPart[i].cs = cs1;

  for(j = nPuntos/2; j<=nPuntos; j++)
    sphPart[j].cs = cs2; 

  
  // encuentra vecinos
  for( i=0; i<nPuntos; i++ )
    vecinos(i);

  // genera densidad
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

  
  FILE *fIcs = fopen("data/punto2/condiciones_iniciales.dat","w");
  for( i=0; i<nPuntos; i++ )
    {
    fprintf(fIcs,"%d %lf %lf %lf %lf %lf %lf %lf\n",
	    sphPart[i].id,
	    sphPart[i].pos[X], sphPart[i].pos[Y],
	    sphPart[i].vel[X], sphPart[i].vel[Y],
	    sphPart[i].masa, sphPart[i].densidad,
	    sphPart[i].presion);
    }
  fclose(fIcs);

  return 0;
}
