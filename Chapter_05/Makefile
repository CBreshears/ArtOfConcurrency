CC = icc

LIBDIR = 
PLIBS = $(LIBDIR) -lpthread 
TLIBS = $(LIBDIR) -ltbb


all: pi pi_omp pi_tbb pi_pth

pi: pi_omp.cc
	$(CC) pi_omp.cc -o pi

pi_omp: pi_omp.cc
	$(CC) -fopenmp pi_omp.cc -o pi_omp

pi_tbb: pi_tbb.cc
	$(CC) pi_tbb.cc -o pi_tbb $(TLIBS)

pi_pth: pi_pth.cc
	$(CC) pi_pth.cc -o pi_pth $(PLIBS)

clean:
	rm -rf *.o pi pi_omp pi_tbb pi_pth
