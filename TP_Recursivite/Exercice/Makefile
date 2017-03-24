include Makefile.compilation

#
# Modules
#

OBJ= exo1 exo2 exo3 exo4 exo5  

exo1 : exo1.c 
	$(CCLNK) $(CFLAGS) $(LIBMATH) exo1.c -o exo1 -I./

exo2 : exo2.c 
	$(CCLNK) $(CFLAGS) $(LIBMATH) exo2.c -o exo2 -I./

exo3 : exo3.c
	$(CCLNK) $(CFLAGS) $(LIBMATH) exo3.c -o exo3 -I./

exo4 : exo4.c
	$(CCLNK) $(CFLAGS) $(LIBMATH) exo4.c -o exo4 -I./

exo5 : exo5.c
	$(CCLNK) $(CFLAGS) $(LIBMATH) exo5.c -o exo5 -I./

all : $(OBJ)

clean :
	- rm  *.o
	- rm exo1
	- rm exo2
	- rm exo3
	- rm exo4
	- rm exo5

tests : 
	./exo1
	./exo2
	./exo3
	./exo4
	./exo5
