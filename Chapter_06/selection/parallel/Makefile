CC = icc

LIBDIR = 
LIBS = $(LIBDIR) -ltbb


all: selection_par

selection_par: CountAndMark.h FindMedians.h PackingMove.h PackingScan.h ParallelSelection.cpp SortSelect.cpp SortSelect.h
	$(CC) SortSelect.cpp ParallelSelection.cpp -o selection_par $(LIBS)

clean:
	rm -rf *.o selection_par
