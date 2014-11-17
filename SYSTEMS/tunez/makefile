all: tunez.o song.o library.o	
	gcc -o tunez song.o tunez.o library.o

#main file (executable file)
tunez.o: tunez.c song.h library.h
	gcc -c tunez.c 

#library/array functionality
library.o: library.c library.h song.h	
	gcc -c library.c

#linked list functionality
song.o: song.h song.c
	gcc -c song.c

#make all clean
clean:
	rm *.o
	rm *~
