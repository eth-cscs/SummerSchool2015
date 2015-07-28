CC=cc
CCFLAGS=
ifeq ($(PE_ENV),PGI)
	# -Minfo outputs extra diagnostic information
	# -hacc generates accelerated kernels from openacc directives
	CCFLAGS  = -acc=verystrict
	CCFLAGS += -ta=nvidia,nofma,cc35,cuda5.5 # target architecture
	#CCFLAGS  = -Minfo=accel
	CCFLAGS += -g # debug flags
endif
ifeq ($(PE_ENV),CRAY)
	# -h list=md outputs extra diagnostic files
	# -hacc generates accelerated kernels from openacc directives
	CCFLAGS  = -h list=md -hacc -O3
endif

SOURCES = stats.c data.c operators.c linalg.c
HEADERS = stats.h   data.h   operators.h   linalg.h
OBJ     = stats.o   data.o   operators.o   linalg.o   main.o

all: main

stats.o: stats.c stats.h
	$(CC) $(CCFLAGS) -c stats.c -o stats.o

data.o: data.c data.h
	$(CC) $(CCFLAGS) -c data.c -o data.o

operators.o: operators.c operators.h
	$(CC) $(CCFLAGS) -c operators.c -o operators.o

linalg.o: linalg.c linalg.h
	$(CC) $(CCFLAGS) -c linalg.c -o linalg.o

main.o: main.c $(HEADERS)
	$(CC) $(CCFLAGS) -c $< -o $@

main: $(OBJ)
	$(CC) $^ -o $@ 

clean:
	rm -f main *.o *.i *.ptx *.bin *.gpu *.lst *.cg *.opt
