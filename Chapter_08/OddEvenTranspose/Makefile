CC = icc

LIBDIR = 
LIBS =

all: oddeven_ser oddeven_omp oddeven_final

oddeven_ser: oddeven_omp.cc
	$(CC) oddeven_omp.cc -o oddeven_ser

oddeven_omp: oddeven_omp.cc
	$(CC) -fopenmp oddeven_omp.cc -o oddeven_omp

oddeven_final: oddeven_final.cc
	$(CC) -fopenmp oddeven_final.cc -o oddeven_final

clean:
	rm -rf *.o oddeven_ser oddeven_omp oddeven_final
