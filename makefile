all: matrix.o mf.o
	g++ mf.o matrix.o -o a -l sqlite3
	rm *.o
matrix.o: matrix.cpp
	g++ -c matrix.cpp
mf.o: mf.cpp
	g++ -c mf.cpp
