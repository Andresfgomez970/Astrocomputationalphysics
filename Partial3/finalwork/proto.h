
int genera_condiciones_iniciales(void);
int genera_condiciones_iniciales_maya();
int genera_condiciones_iniciales_maya2(void); 
int genera_condiciones_iniciales_maya3(void); 


int aloca_memoria(void);
int libera_memoria(void);

double kernel(double r, double h);
double nabla_kernel(double r, double h, int coord, int a, int b);

int vecinos(int nParticula);
int acceleracion(void);
int evoluciona(void);
