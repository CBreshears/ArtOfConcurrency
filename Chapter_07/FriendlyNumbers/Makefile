CC = icc

all: map_reduce map_reduce_omp

map_reduce: map_reduce_omp.cc
	$(CC) map_reduce_omp.cc -o map_reduce $(LIBS)

map_reduce_omp: map_reduce_omp.cc
	$(CC) -fopenmp map_reduce_omp.cc -o map_reduce_omp $(LIBS)

clean:
	rm -rf *.o map_reduce map_reduce_omp
