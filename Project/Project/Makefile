CC=gcc
GSLUBICATION = /home/$(USER)/local/
CFLAGS= -I. -I$(GSLUBICATION)include/gsl/ -I$(GSLUBICATION)include/ -g
LFLAGS= -L$(GSLUBICATION)lib/ -lgsl -lgslcblas -lm
DEPS = allvars.h
OBJ = montecarlo.o main.o two_body_analytical.o densities_constructions.o input_output.o Nbody_newton_integrator.o #allvars.o 
EXEC = main.out

Main: $(OBJ) $(DEPS)
	$(CC) -Wall -o $(EXEC) $(OBJ) $(CFLAGS) $(LFLAGS)
	rm *.o 

runmain: Main
	./$(EXEC) 

runmain25: Main
	./$(EXEC) 25

run_example1: runmain
	gnuplot -c plot_sky.plt data/montecarlo/synthetic/syntheticrej20000 20000
	gnuplot -c plot_sky.plt data/montecarlo/synthetic/syntheticinv20000 20000
#Termination name of file and place as place/termination  == ARG1 ; N_points=ARG2

run_example2: runmain
	gnuplot -c plot_histogram.plt data/montecarlo/densities/Up1EarthSunSystem 0.002 0.1
#Termination name of file and place as place/termination  == ARG1 ; With bins=ARG2 and a in U(-a,a) distribution

run_example3: runmain
	gnuplot -c plot_histogram.plt data/montecarlo/densities/Up2EarthSunSystem 0.002 0.2

run_example4: runmain
	gnuplot -c plot_histogram.plt data/montecarlo/densities/Up5EarthSunSystem 0.002 0.5

run_example5: runmain
	gnuplot -c plot_histogram.plt data/montecarlo/densities/Up7EarthSunSystem 0.02 0.7

run_example8: runmain25
	gnuplot -c plot_histograms_orbital_parameters.plt data/montecarlo/densities/distances 1000000

plot_histogram: 
	gnuplot -c plot_histogram.plt data/montecarlo/densities/Up7EarthSunSystem 0.002 0.1 --persist
#in UP7EarthSunSystem goes the name of a alreay generated file without the termination .dat

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS) $(LFLAGS)

clean:
	rm *.o* *~ 


