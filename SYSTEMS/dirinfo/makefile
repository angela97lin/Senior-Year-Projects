all: dirinfo.o
	gcc -o dir dirinfo.o

dirinfo.o: dirinfo.c dirinfo.h
	gcc -c dirinfo.c

clean:	
	rm dir
	rm *.o
	rm *~
