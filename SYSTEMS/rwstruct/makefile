all: rwstruct.o
	gcc -o filer rwstruct.o

rwstruct.o: rwstruct.c rwstruct.h
	gcc -c rwstruct.c

clean: 
	rm test
	rm *.o
	rm *~


