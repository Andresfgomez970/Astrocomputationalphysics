CC=gcc
CFLAGS=-I.
DEPS = allvars.h
OBJ = n_body.o input_output.o integrator.o

Nbody: $(OBJ) $(DEPS)
	$(CC) -Wall -o Nbody $(OBJ) -lm 

run: Nbody
	./Nbody galaxia.gad
	rm *.o 

$(OBJS): allvars.h

clean:
	rm *.o *~
