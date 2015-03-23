Chatter (Chat Program)
============
### Period 4
### Angela Lin, Jeffrey He, Lawrence Lim
============

####Compiling Instructions:
$ make

####How to use our project:
First, run server:

$ ./server

Then, in (a) separate window(s), run client:

$ ./curse_cl 127.0.0.1 desiredusername

If you wish to change your nickname at any time, please type:

/nick newnickname

####Known bugs:
* Special keys (Backspace, Delete, Up, Down, etc.) do not function as usual in ncurses

####Files:
* makefile
* server.c
* server.h
* curse_cl.c
* curse_cl.h
* curses.h
* linkedlist.c
* linkedlist.h
