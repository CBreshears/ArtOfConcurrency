CC = icc

LIBDIR = 
LIBS = $(LIBDIR) -lpthread 

all: radix

radix: radixsort.cpp
	$(CC) radixsort.cpp -o radix $(LIBS)

clean:
	rm -rf *.o radix
