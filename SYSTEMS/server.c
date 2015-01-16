#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet.h/in.h>

//SERVER PROGRAM

char* process (char* s);

int main(int argc, char** argv){

  int socket_id;
  char buffer[256];
  int i, b;

  //create a socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to an IP address and port
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(24601);
  sock.sin_addr.sin_addr = INADDR_ANY;
  
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //server listens and waits until it receives a connection
  listen(socket_id, 0);

  //accepts connection
  
  socklen_t s;
  s = sizeof(sock);
  accept(socket_id, (struct sockaddr *)&sock, &s)
  return 0;
}

char* process (char *s){
  char *p;

  return p;

}

