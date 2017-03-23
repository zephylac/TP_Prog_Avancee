include Makefile.compilation

#
# Objets
#

fich_obj_test_exo1=test_exo1.o exo1.o
fich_obj_test_exo2=test_exo2.o exo2.o
fich_obj_test_exo3=test_exo3.o exo3.o
fich_obj_test_exo4=test_exo4.o exo4.o
fich_obj_test_exo5=test_exo5.o exo5.o


#
# Tests (executables+objets)
#

BIN = test_exo1 test_exo2 test_exo3 test_exo4 test_exo5 

test_exo1 : $(fich_obj_test_exo1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_exo1) -o test_exo1 

test_exo1.o : test_exo1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_exo1.c -o test_exo1.o -I./ 

test_exo1 : $(fich_obj_test_exo1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_exo1) -o test_exo1 

test_exo1.o : test_exo1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_exo1.c -o test_exo1.o -I./ 

test_exo1 : $(fich_obj_test_exo1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_exo1) -o test_exo1 

test_exo1.o : test_exo1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_exo1.c -o test_exo1.o -I./ 

test_exo1 : $(fich_obj_test_exo1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_exo1) -o test_exo1 

test_exo1.o : test_exo1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_exo1.c -o test_exo1.o -I./ 

test_exo1 : $(fich_obj_test_exo1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_exo1) -o test_exo1 

test_exo1.o : test_exo1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_exo1.c -o test_exo1.o -I./ 


#
# Modules
#

OBJ= exo1.o exo2.o exo3.o exo4.o exo5.o  

exo1.o : exo1.c exo1.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) exo1.c -o exo2.o -I./

exo1.o : exo1.c exo1.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) exo1.c -o exo2.o -I./

exo1.o : exo1.c exo1.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) exo1.c -o exo2.o -I./

exo1.o : exo1.c exo1.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) exo1.c -o exo2.o -I./

exo1.o : exo1.c exo1.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) exo1.c -o exo2.o -I./

all : $(BIN) $(OBJ)

clean :
	- rm  *.o
	- rm test_exo1
	- rm test_exo2
	- rm test_exo3
	- rm test_exo4
	- rm test_exo5

tests : 
	./test_exo1
	./test_exo2
	./test_exo3
	./test_exo4
	./test_exo5
