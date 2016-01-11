#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

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
  //inet_aton("127.0.0.1", &(sock.sin_addr) );

  inet_aton(argv[1], &(sock.sin_addr) );
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //connect: a way to initiate a TCP connection
  //will block until connection is established
  //returns 0 if successful, -1 if failed
  //block occurs if there is an open socket but server is not ready
  //to accept data
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock)); 
  printf("i: %d\n", i);
  while (1){
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);
    printf("buffer: %s\n", buffer);
    *(strchr(buffer, '\n')) = 0;
    b = write (socket_id, buffer, strlen(buffer)+1);
    if (strncmp (buffer, "exit", sizeof(buffer)) == 0)
      break;
    b = read(socket_id, buffer, strlen(buffer));
    
  }
  printf("connect returned %d\n", i);
  return 0;
}

