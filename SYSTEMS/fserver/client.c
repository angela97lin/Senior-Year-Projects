#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
/*
Client program:
The client is the same for a basic server or a forking server, things to make sure you do:
   * Create a named pipe with a unique name
   * Remove the pipe once a connection is made.
   * Continue to run until the user enters a command to exit.
   * The client should exit when the user enters "exit"
*/
int from_server;
int to_server;
char line[256];
char pname[256];
  
void client_handshake(){
  
  //creating client's private pipe (named pipe with unique name)
  sprintf(pname, "%d", getpid());
  from_server = mkfifo(pname, 0664);
  //printf("pname: %s\n", pname);

  //connecting to server, sending name of private pipe
  to_server = open("WKP", O_WRONLY, 0664);
  if (to_server == -1){
    printf("Error in connecting to WKP... Please check that the server is running first!\n");
    remove(pname);
    exit(0);
  }
  write(to_server, pname, sizeof(pname));
  from_server = open(pname, O_RDONLY); 
  //connection made, removing private pipe
   read(from_server, line, sizeof(line));
 
 remove(pname);
}

int main(){
  client_handshake();

  while(1){
    printf("Enter anything! ('exit' or ENTER to quit):");
    fgets(line, sizeof(line), stdin);
    line[strlen(line)-1] = '\0';
    if (strcmp(line, "exit") == 0 || strcmp(line, "") == 0){
      printf("Client is now exiting...\n");
      return 0;
    }  
  write(to_server, line, sizeof(line));
  read(from_server, line, sizeof(line));
  //remove(pname);
  printf("\n-->%s\n", line);

  }
  return 0;
}
