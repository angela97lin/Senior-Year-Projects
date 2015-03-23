#ifndef SERVER_H
#define SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include "linkedlist.h"
#include <errno.h>


#define MAX_USERS 256
#define MAX_NICKSIZE 256
#define BUFF_SIZE 256
#define READ 0
#define WRITE 1
struct user{
	int socketfd;
	char nick[MAX_NICKSIZE]; 
};

void init();
void subserver();
void broadcast();

char* process (char* s);

int add_user(struct user person);
char *get_nick(int socketfd);
int set_nick(int socketfd, char *nick);
int remove_user(int socketfd);

#endif //SERVER_H
