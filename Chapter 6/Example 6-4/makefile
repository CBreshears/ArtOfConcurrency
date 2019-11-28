CC = icc

LIBDIR = 
LIBS = $(LIBDIR) -lpthread 
#LIBS = $(LIBDIR)


all: pi

pi: Example5-3.cpp
	$(CC) Example5-3.cpp -o pi $(LIBS)

psum: Example6-4.cpp
	$(CC) Example6-4.cpp -o psum $(LIBS)

phsum: Example7-2.cpp
	$(CC) Example7-2.cpp -o phsum $(LIBS)

clean:
	rm -rf *.o pi psum phsum
