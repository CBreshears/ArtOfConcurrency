CC = icc

LIBDIR = 
LIBS =

all: insertionsort_ser shellsort_ser shellsort_hpar_ser

insertionsort_ser: insertionsort_ser.cc
	$(CC) insertionsort_ser.cc -o insertionsort_ser

shellsort_ser: shellsort_ser.cc
	$(CC) shellsort_ser.cc -o shellsort_ser

shellsort_hpar_ser: shellsort_hpar_ser.cc
	$(CC) shellsort_hpar_ser.cc -o shellsort_hpar_ser

clean:
	rm -rf *.o insertionsort_ser shellsort_ser shellsort_hpar_ser
