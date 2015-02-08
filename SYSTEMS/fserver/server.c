#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

/*
Server program:
Should follow the pattern of a basic forking server. Things to make sure you do:
   * Create a well known pipe (WKP)
   * Remove the WKP when a client has connected
   * Create a subserver to handle communication with the client
   * Close/Remove the original WKP after the subserver is created
   * Create a new WKP after that
   * "Process" the input from the client and send the new message back
          The program can do anything you'd like to the input, but it must change it in some way.
   * The server should have a signal handler for ctrl-c so that before it exits it cleans up anything that it needs to.
*/

int to_client, from_client;
char cpid[256];
char confirm[256];

//signal handler
static void sighandler(int signo){
  if (signo == SIGINT){//CTRL-C
    close(from_client);
    close(to_client);
    remove("WKP");
    exit(0);
  }
}

void server_handshake(){
  //creating and opening the WKP
  mkfifo("WKP", 0664);
  from_client = open("WKP", O_RDONLY);
  
  read(from_client, cpid, sizeof(cpid));
  printf("New client: %s\n", cpid);
  
  to_client = open(cpid, O_WRONLY);
  strcpy(confirm,"Yay! You are now connected to the server.\n");
  //printf("confirm: %s\n", confirm);
  write(to_client, confirm, sizeof(confirm)); 

  //forking off subprocess
  int f = fork();
  if (f){//parent process
    remove("WKP");
  }
  else if (f == 0){//child process
    char res[256];
    while(1){
      read(from_client, res, sizeof(res)); 
      //printf("strlen: %d\n", strlen(res));
      //printf("server got: %s\n", res);

      //simple processing of client input
      strncat(res,"~! MEOW. =^.^=", 14);
      write(to_client, res, sizeof(res));
    }  
  close(from_client);
  close(to_client);
  }
}

int main(){

  signal(SIGINT, sighandler);
  printf("Opening server... Awaiting clients...\n");

  while(1){
    server_handshake();
  }
  return 0;
}
