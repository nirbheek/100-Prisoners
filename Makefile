all:
	$(CC) -march=native -O3 -fopenmp 100_prisoners_openmp.c -o 100_omp_O3.o
	$(CC) -march=native -O3 100_prisoners.c -o 100_O3.o

test:
	time ./100_O3.o;
	time ./100_omp_O3.o;

clean:
	rm -f *.o
