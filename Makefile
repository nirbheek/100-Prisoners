all: 100_O3.o 100_omp_O3.o

100_O3.o: 100_prisoners.c
	$(CC) -ffast-math -march=native -O3 100_prisoners.c -o 100_O3.o

100_omp_O3.o: 100_prisoners.c
	$(CC) -ffast-math -march=native -O3 -fopenmp -DOMP 100_prisoners.c -o 100_omp_O3.o

test: all
	time ./100_O3.o;
	time ./100_omp_O3.o;

clean:
	rm -f *.o a.out
