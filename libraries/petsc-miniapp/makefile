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

# Some tests
test : run_test1 run_test2

TEST_OPTIONS=-ts_monitor -snes_monitor -ksp_monitor -ts_view

run_test1: ${EXNAME}
	@rm -f test1.tmp
	@echo "Running Test 1"
	@aprun -n 1 ./main ${TEST_OPTIONS}  \
    2>&1 > test1.tmp
	@diff test1.tmp testref/test1.ref && \
    echo "Success" || \
    echo "Check: output does not match reference (see diff above)"
	@rm -f test1.tmp

run_test2: ${EXNAME}
	@rm -f test2.tmp
	@echo "Running Test 2"
	@aprun -n 2 ./main ${TEST_OPTIONS}  \
    2>&1 > test2.tmp
	@diff test2.tmp testref/test2.ref && \
    echo "Success" || \
    echo "Check: output does not match reference (see diff above)"
	@rm -f test2.tmp

.PHONY: ALL allclean test run_test1 run_test2
