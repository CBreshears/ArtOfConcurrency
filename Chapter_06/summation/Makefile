CC = icc

LIBDIR = 
LIBS = $(LIBDIR) -lpthread 


all: sum_ser sum_omp sum_pth

sum_ser: sum_omp.cc
	$(CC) sum_omp.cc -o sum_ser

sum_omp: sum_omp.cc
	$(CC) -fopenmp sum_omp.cc -o sum_omp

sum_pth: sum_pth.cc
	$(CC) sum_pth.cc -o sum_pth $(LIBS)

clean:
	rm -rf *.o sum_ser sum_omp sum_pth
