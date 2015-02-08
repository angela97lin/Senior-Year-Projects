#include "curses.h"
#include "curse_cl.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>

#define BUFF_SIZE 256

int socket_id;
char buffer[BUFF_SIZE];
char buffer2[BUFF_SIZE];
int i, b;

WINDOW* messages;
WINDOW* input;

char* inbuf; 
int inbufindex;
int inchr;

int main(int argc, char *argv[]) { 

  checkargs(argc);
  initconnect(argv[1]);
  setnick(argv[2]);
  initcl();
  while((inchr = getch()) != KEY_F(1)) {
    if(inchr!=ERR) {
      int cury,curx;
      getyx(stdscr,cury,curx);
      if(curx<79) {
        inbuf[inbufindex] = inchr;
        inbufindex++;
      } else {
        noecho();
      }
      if(inchr==10 && inbufindex>0) {
        sendmessage();
        clearinput();
      }
      if(inchr==127 && inbufindex>0) {
        inbufindex--;
        inbufindex--;
        inbuf[inbufindex] = '\0';
        mvprintw(cury,curx-3,"   ");
        move(cury,curx-3);
      }
    }

    b = read(socket_id, buffer, BUFF_SIZE);
  	if(b>-1) {
    	snprintf(buffer2, BUFF_SIZE, "%s\n", buffer);
    	printmsg(buffer2);
  	}

    //sprintf(buffer, "%d", inchr);
    //printmsg(buffer);
  }
  SELFDESTRUCT(0);
  return 0;
}

void checkargs(int argc) {
  if (argc != 3) {
  	printf("usage: ./client <IP address> <desired nickname>\n");
	printf("Exiting...\n");
	exit(1);
  }
}

void initconnect(char* ip) {
  //create a socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to an IP address and port
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(24601);
  //inet_aton("127.0.0.1", &(sock.sin_addr) );

  inet_aton(ip, &(sock.sin_addr) );
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //connect: a way to initiate a TCP connection
  //will block until connection is established
  //returns 0 if successful, -1 if failed
  //block occurs if there is an open socket but server is not ready
  //to accept data
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock)); 
  printf("i: %d\t%s\n", i, strerror(errno));
  if (i){
    //most likely because of the TIMEOUT thing... SO_READDR?
    printf("Error in connecting!: %s\n", strerror(errno));
    
    exit(0);
  }
  fcntl(socket_id, F_SETFL, fcntl(socket_id, F_GETFL, 0) | O_NONBLOCK);
}

void setnick(char* nick) {
  snprintf(buffer, BUFF_SIZE, "/nick %s", nick);
  b = write(socket_id, buffer, strlen(buffer) + 1);
  if (b == -1 || b == 0){ //either 0 bytes written, or error
  	printf("Failed to set nick! %s\n", strerror(errno));
  	exit(1);
  }
}


void initcl() {
  inbuf = malloc(100*sizeof(char));
  inbufindex = 0;
 
  signal(SIGINT, SELFDESTRUCT);

  int x,y,w,h;

  WINDOW* win = initscr();
  cbreak();
  nodelay(win, TRUE);
  keypad(stdscr,TRUE);
  //nonl();
  //echo();

  w = COLS;
  h = 3;
  y = LINES-3;
  x = 0;
  refresh();
  input = create_newwin(h,w,y,x);

  w = COLS;
  h = LINES-3;
  y = 0;
  x = 0;
  refresh();
  messages = create_newwin(h,w,y,x);
  scrollok(messages,TRUE);
  
  move(LINES-2,1);
  refresh();
}

void clearinput() {
  inbufindex = 0;
  wclear(input);
  box(input,0,0);
  move(LINES-2,1);
  wrefresh(input);
  refresh();
}

static void SELFDESTRUCT(int sig) {
  endwin();
  exit(0);
}

WINDOW* create_newwin(int h, int w, int y, int x) {
  WINDOW* r;
  r = newwin(h,w,y,x); 
  box(r,0,0);
  wrefresh(r);
  return r;
}

void destroy_win(WINDOW* w) {
  wborder(w,' ',' ',' ',' ',' ',' ',' ',' ');
  wrefresh(w);
  delwin(w);
}

void printmsg(char* msg) {
  int row,col;
  wborder(messages,' ',' ',' ',' ',' ',' ',' ',' ');
  scroll(messages);
  getmaxyx(messages,col,row);
  mvwprintw(messages,col-2,1,msg);
  box(messages,0,0);
  wrefresh(messages);
}

void sendmessage() {
  inbuf[inbufindex] = '\0';
  b = write(socket_id, inbuf, strlen(inbuf)+1);
}
