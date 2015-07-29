# Use this makefile on a cray XC system such as Piz Daint
#
# use modules:
#   PrgEnv-cray
#   cray-petsc

OBJ = main.o system.o dump.o

# cray-petsc uses an older version of the library
#  which in particular lacks new read-only access to vectors
SPECIAL_FLAGS=-DUSE_OLD_API

main: $(OBJ) 
	cc -o $@ $(OBJ)
 
%.o : %.c
	cc ${SPECIAL_FLAGS} -c -o $@ $<

clean : 
	rm -f main $(OBJ) out.m output.*

.PHONY: ALL allclean
