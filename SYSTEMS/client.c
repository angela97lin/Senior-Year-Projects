#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet.h/in.h>

//CLIENT PROGRAM

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
  inet_aton("127.0.0.1", &(sock.sin_addr) );

  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //connect: a way to initiate a TCP connection
  //will block until connection is established
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock)); 

  return 0;
}

