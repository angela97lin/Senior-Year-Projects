#include "server.h"


#define MAX_USERS 256
#define MAX_NICKSIZE 256
#define BUFF_SIZE 256

int socket_id, socket_client;
char buffer[BUFF_SIZE];
char nick[MAX_NICKSIZE];
int i, b;
int client_to_server[2];
struct node *connections;
struct node *current;

int main(int argc, char** argv){
  
  init();
  
  while (1) {
    //accept connection
    //socklen_t s;
    //s = sizeof(sock);
    //socket_client = accept(socket_id, (struct sockaddr *)&sock, &s)
    
    socket_client = accept(socket_id, NULL, NULL); 
    
    if(socket_client > -1) {
      printf("socket client: %d\n",socket_client);
      struct user *new_user = (struct user *)malloc(sizeof(struct user));
      new_user -> socketfd = socket_client;
      struct node *new_node = createsong(new_user);
      connections = insert_front(connections, new_node); 
      int f = fork();
      if (f == 0) {
	current = new_node;
	//SHOULD BE HERE WHERE WE USE THE MAGICAL CLOUD SHIT
	subserver();
      }
      
    }
    i = read(client_to_server[READ], buffer, BUFF_SIZE);
    if(i > -1) {
      printf("Broadcast process received: %s\n", buffer);
      struct node *here = connections;
      while(here) {
	write(here->user->socketfd, buffer, strlen(buffer) + 1);
	here = here->next;
      }
    }
    usleep(50000);
  }
  
  close(client_to_server[WRITE]);
  close(client_to_server[READ]);
  close(socket_client);
  printf("waiting for connection...\n");
  
  return 0;
}

void init() {
  //create a socket
  socket_id = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
  
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
  pipe2(client_to_server, O_NONBLOCK);
}


void subserver() {
  close(client_to_server[READ]);
  while (1) {
    b = read(socket_client, buffer, BUFF_SIZE);
    if(b>0) {
      process(buffer);
    } else {
      if (errno == ECONNABORTED) {
	printf("Connection aborted. Exiting subserver\n");
	remove_node(connections,current);
	exit(0);
      } else if (errno == ECONNRESET)  {
	printf("%s\t Exiting subserver\n", strerror(errno));
	remove_node(connections,current);
	exit(0);
      }
      
    }
    usleep(50000);
  } 
}

char* process (char *s){
  //check for /nick command
  char* loc = strstr(s, "/nick ");
  if (loc) { //aka if requesting to change nickname
    printf("Setting nickname...\n");
    char *loc_n = strchr(loc, '\n');
    if (loc_n){ //if there's a \n (aka renaming self)
      //printf("has newline!\n");
      *(strchr(loc, '\n')) = 0;
    }
    strcpy(nick, loc + strlen("/nick "));
    return nick;
  }
  char message[BUFF_SIZE];
  snprintf(message, BUFF_SIZE, "%s: %s", nick, s);
  
  write(client_to_server[WRITE], message, strlen(message) + 1);
  return s; 
}
