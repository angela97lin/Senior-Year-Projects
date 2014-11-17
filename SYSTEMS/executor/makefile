all: executor.o
	gcc -o execute executor.o

executor.o: executor.c
	gcc -c executor.c

clean:
	rm *.o
	rm *~
