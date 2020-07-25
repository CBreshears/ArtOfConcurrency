CC = icc

all: selection_ser

selection_ser: SerialSelection.cpp  SortSelect.cpp  SortSelect.h
	$(CC) SortSelect.cpp SerialSelection.cpp -o selection_ser

clean:
	rm -rf *.o selection_ser
