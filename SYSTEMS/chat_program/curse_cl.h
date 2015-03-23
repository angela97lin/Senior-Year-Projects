#ifndef CURSE_CL_H
#define CURSE_CL_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>

void checkargs();
void initconnect();
void setnick();
void chatloop();

void initcl();
void clearinput();

static void SELFDESTRUCT(int sig);

WINDOW* create_newwin(int h, int w, int y, int x);
void destroy_win(WINDOW *local_win);

void printmsg(char* msg);
void sendmessage();

#endif //CURSE_CL_H
