CXX=CC
CUDA=nvcc
CXXFLAGS=-O3 -fopenmp
CUDAFLAGS=-O3 -std=c++11 -arch=sm_35

SOURCES = stats.cu  data.cu  operators.cu  linalg.cu    main.cu
HEADERS = stats.h   data.h   operators.h   linalg.h
OBJ     = stats.o   data.o   operators.o   linalg.o

.SUFFIXES: .cpp

all: main tests

stats.o: stats.cu $(HEADERS)
	$(CUDA) $(CUDAFLAGS) -c stats.cu

data.o: data.cu $(HEADERS)
	$(CUDA) $(CUDAFLAGS) -c data.cu

operators.o: operators.cu $(HEADERS)
	$(CUDA) $(CUDAFLAGS) -c operators.cu

linalg.o: linalg.cu $(HEADERS)
	$(CUDA) $(CUDAFLAGS) -c linalg.cu

main.o: main.cu $(HEADERS)
	$(CUDA) $(CUDAFLAGS) -c main.cu

tests.o: tests.cu $(HEADERS)
	$(CUDA) $(CUDAFLAGS) -c tests.cu

main: $(OBJ) main.o
	$(CC) $(CXXFLAGS) $(OBJ) main.o -o main -lcublas

tests: data.o linalg.o tests.o
	$(CC) $(CXXFLAGS) tests.o $(OBJ) -o tests -lcublas
	aprun ./tests

clean:
	rm -f main
	rm -f *.o
	rm -f *.i
	rm -f output.*
