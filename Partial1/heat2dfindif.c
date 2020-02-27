#include<stdio.h>
#include<stdlib.h>
#include<math.h>   
#include<time.h>    
#include<malloc.h> // For compatibility of compilers
#include<string.h>


int main(int argc, char *argv[]){

  double xmin=0,xmax=10,ymin=0,ymax=10,tmin=0,tmax=30000;
  int Nx=40,Ny=40;
  int Ntime=160; 
  double xstep = (xmax-xmin)/Nx, ystep = (ymax-ymin)/Ny, tstep=(tmax-tmin)/Ntime;
  FILE * datap;
  double x,y;
  int lenfile = 30;  
  char namefiles[lenfile]; 
  double T[Nx][Ny];
  double Te[Nx][Ny];
  
  // Physical parameter constants
  double K = 205.0; // Thermical conductivity of Al in W/(m K) 
  double Ti = 100+273.15; // Initial temperature of plate K
  double rho = 2700; //Density of aluminium kg m^-3
  double C = 900; // Specific heat of aluminium J/(kg * K)
  double n = K * tstep/(xstep*xstep*rho*C);
  double Tb = 273.15; //Initial temperature of the Boundary
  
  int TeqM(int Nx,int Ny, double T[Ny][Nx] , double M[Ny][Nx] );
  int Mprint(int Nx, int Ny, double T[Ny][Nx]);
  
  sprintf(namefiles,"files/data%d.txt",0); 
 
  datap = fopen (namefiles,"w");

  x=xmin-xstep;
  fprintf(datap,"#%4c %10c %9c\n",'x','y','T'); 
  for(int i=0; i<Nx; ++i){
    x +=xstep;
    y = ymin-ystep; 
    for(int j=0; j<Ny; ++j){
      y += ystep; 
      if (i==0 || j==0 || i==(Nx-1) || j==(Ny-1) ){
	fprintf(datap,"%9.4lf %9.4lf %9.4lf\n",x,y ,Tb);
	T[i][j] = Tb;
	Te[i][j] = Tb; 
      }
      else{ 
	fprintf(datap,"%9.4lf %9.4lf %9.4lf\n",x,y ,Ti);
	T[i][j] = Ti;
	Te[i][j] = Ti;
      }
    }
  }

  
  
  for(int k=0; k < Ntime; ++k){
    sprintf(namefiles,"files/data%d.txt",k+1);
    datap = fopen (namefiles,"w");
    x=xmin;
    TeqM(Nx,Ny,T,Te);

    //Mprint(Nx,Ny ,Te ); 
    //printf("\n");
    //Mprint(Nx,Ny ,T );
    //printf("\n");
    //printf("\n again: %lf",Te[2][1]);

    for(int i=0; i<Nx ; ++i){
      x+=xstep; 
      y=ymin;
      for(int j=0; j<Ny ; ++j){
	y+=ystep; 
	if (i==0 || i== (Nx-1) || j==0 || j== (Ny-1) )
	  fprintf(datap,"%9.4lf %9.4lf %9.4lf\n",x , y, Tb );
	else{
	  Te[i][j] = T[i][j] + n*(T[i+1][j] + T[i][j+1] + T[i-1][j] + T[i][j-1]
	  			  - 4*T[i][j] );
	  //printf("\n%d,%d ",i,j);
	  //if(i==1 && j==1)
	  //  printf("\n %d,%d,%d, %lf",i,j,k,Te[i][j]);
	  fprintf(datap,"%9.4lf %9.4lf %9.4lf\n",x ,y,Te[i][j]);
	}
      }
    }
  }
      
  fclose(datap); 
  
  return 0; 
}


int Mprint(int Nx, int Ny, double T[Nx][Ny]){
  for (int i=0;  i<Nx; ++i){
    for(int j=0; j<Ny; ++j)
      printf("%.3lf ",T[i][j]);
    printf("\n");
  }
  return 0;  
}
  
int TeqM(int Nx, int Ny,  double T[Nx][Ny], double Te[Nx][Ny] ){

  for (int i=0;  i<Nx; ++i){
    for(int j=0; j<Ny; ++j){
      T[i][j] = Te[i][j];
    }
  }
    
  return 0; 
}



