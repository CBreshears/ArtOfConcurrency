CC = icc

LIBDIR = 
LIBS = $(LIBDIR) -lpthread 

all: reduction_pth

reduction_pth: reduction_pth.cc
	$(CC) reduction_pth.cc -o reduction_pth $(LIBS)

clean:
	rm -rf *.o reduction_pth
