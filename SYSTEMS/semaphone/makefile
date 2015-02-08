lsall: controls.o writer.o
	gcc -o controls controls.o 
	gcc -o writer writer.o

controls.o: controls.c controls.h
	gcc -c controls.c 

writer.o: writer.c writer.h
	gcc -c writer.c

clean:
	rm controls
	rm writer
	rm story.txt
	rm *.o
	rm *~
