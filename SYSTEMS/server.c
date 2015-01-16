#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

//SERVER PROGRAM

char* process (char* s);

int main(int argc, char** argv){

  int socket_id, socket_client;
  char buffer[256];
  int i, b;

  //create a socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to an IP address and port
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(24601);
  sock.sin_addr.s_addr = INADDR_ANY;
  
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  printf("pre-listening\n");
  //server listens and waits until it receives a connection
  listen(socket_id, 1);

  printf("pre-accepting\n");

  while (1) {  
    //accept connection
    //socklen_t s;
    //s = sizeof(sock);
    socket_client = accept(socket_id, NULL, NULL); 
    //socket_client = accept(socket_id, (struct sockaddr *)&sock, &s)
    printf("accepted connection:");
    b = read(socket_client, buffer, sizeof(buffer));
    printf("received: %s\n", buffer);
    
    process(buffer);
    write (socket_client, buffer, strlen(buffer));
    
  }
  
  close(socket_client);
  printf("waiting for connection...\n");
 
  return 0;
}


char* process (char *s){
   strncat(s,"~! MEOW. =^.^=", 14);
   printf("s: %s\n", s);
   return s;

}

