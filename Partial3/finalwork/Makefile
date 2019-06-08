
OPT   +=  -DCONTINUIDAD

CC = gcc
UBICATIONGSL=/home/andres/local
#CFLAGS = -I. -g -Wall -I$(UBICATIONGSL)/include
CFLAGS = -I. -Wall -I$(UBICATIONGSL)/include $(OPT)
LFLAGS = -lm -L$(UBICATIONGSL)/lib -lgsl -lgslcblas 
OBJS = main.o allvars.o ics.o aloca.o kernel.o rutinas_sph.o allvars.h proto.h
EXEC = sph2.out

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(EXEC)
	rm *.o

clean:
	rm *~ *.out *.o

#To run it the following files must be modified
# main: change Totaltime and dt
# main: the routine enera_condiciones_iniciales_maya#() must be used depending of the case
# ics.c: name of the file where output files are saved
# rutinas_sph.c: name of the file where the ouput files are saved
# plot_fluid.plt: file where the parameters of the fluid are saved 
# plot_fluid.plt: run by indicating where the uoutput ...
# plot_velocity.plt: scale factor depending of the simulation, range of positions

#Conditions for the number input in each case

run1_ver1: $(EXEC) $(OBJS)
	./$(EXEC) 100	
	gnuplot -c plot_fluid_principal.gp data/punto1/animationN100t2Em4dt1Em6 200
	ffmpeg -i data/punto1/animationN100t2Em4dt1Em6/fluid%05d.png data/punto1/animationN100t2Em4dt1Em6/video.mp4
	gnuplot -c plot_velocity_principal.gp data/punto1/animationN100t2Em4dt1Em6/velocity/ 100
	ffmpeg -i data/punto1/animationN100t2Em4dt1Em6/velocity/fluid%05d.png -r 5 data/punto1/animationN100t2Em4dt1Em6/velocity/video.mp4

run1_ver2: $(EXEC) $(OBJS)
	./$(EXEC) 256
	gnuplot -c plot_fluid_principal.gp data/punto1/animationN256t2Em4dt1Em6 200
	ffmpeg -i data/punto1/animationN256t2Em4dt1Em6/fluid%05d.png data/punto1/animationN256t2Em4dt1Em6/video.mp4


run1_ver3: $(EXEC) $(OBJS)
	./$(EXEC) 144
	gnuplot -c plot_fluid_principal.gp data/punto1/animationN144t2Em4dt1Em7 2000
	ffmpeg -i data/punto1/animationN144t2Em4dt1Em7/fluid%05d.png -r 250 data/punto1/animationN144t2Em4dt1Em7/video.mp4
	gnuplot -c plot_velocity_principal.gp data/punto1/animationN144t2Em4dt1Em7/velocity 2000
	ffmpeg -i data/punto1/animationN144t2Em4dt1Em7/velocity/fluid%05d.png -r 250 data/punto1/animationN144t2Em4dt1Em7/velocity/video.mp4

run2_ver1: $(EXEC) $(OBJS)
	./$(EXEC) 200
	gnuplot -c plot_fluid_principal.gp data/punto2/animationN100t1Em4dt1Em6 100
	ffmpeg -i data/punto2/animationN100t1Em4dt1Em6/fluid%05d.png data/punto2/animationN100t1Em4dt1Em6/video.mp4
	gnuplot -c plot_velocity_principal.gp data/punto2/animationN100t1Em4dt1Em6/velocity 80
	ffmpeg -i data/punto2/animationN100t1Em4dt1Em6/velocity/fluid%05d.png -r 20 data/punto2/animationN100t1Em4dt1Em6/velocity/video.mp4


run2_ver2: $(OBJS) $(OBJS)
	./$(EXEC) 200
	gnuplot -c plot_fluid_principal.gp data/punto2/animationN100t1Em4dt1Em7 1000
	ffmpeg -i data/punto2/animationN100t1Em4dt1Em7/fluid%05d.png data/punto2/animationN100t1Em4dt1Em7/video.mp4
	gnuplot -c plot_velocity_principal.gp data/punto2/animationN100t1Em4dt1Em7/velocity 800
	ffmpeg -i data/punto2/animationN100t1Em4dt1Em7/velocity/fluid%05d.png -r 250 data/punto2/animationN100t1Em4dt1Em7/velocity/video.mp4

run2_ver3: $(EXEC) $(OBJS)
	./$(EXEC) 512
	gnuplot -c plot_fluid_principal.gp data/punto2/animationN800t1Em4dt1Em7 600
	ffmpeg -i data/punto2/animationN800t1Em4dt1Em7/fluid%05d.png -r 250 -vframes 5000 data/punto2/animationN800t1Em4dt1Em7/video.mp4
	gnuplot -c plot_velocity_principal.gp data/punto2/animationN800t1Em4dt1Em7/velocity 600
	ffmpeg -i data/punto2/animationN800t1Em4dt1Em7/velocity/fluid%05d.png -r 250 -vframes 5000 data/punto2/animationN800t1Em4dt1Em7/velocity/video.mp4

