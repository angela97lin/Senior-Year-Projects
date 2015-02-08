#include "writer.h"

/*
The writing program:
     1. Will attempt to access the resources using the semaphore. 
     2. Once in, it should display the last line added to the file (the shared memory should contain the size of the last line).
     3. Then prompt the use for the next line.
     4. Once a new line is added, it should write that to the file, update the shared memory and then release the semaphore
*/

int fd;
int semkey;
int shmkey;
int semid;
int sm;

int main(){
  printf("Welcome to Semaphone!\n\n");

  //check if 'story.txt' exists, if not, then prompt to create first
  fd = open("story.txt", O_RDWR | O_APPEND, 0644);
  
  if (fd == -1){//if cannot open 'story.txt', prompt to run controls file, then quit  
    printf("Error in opening 'story.txt: %s\n", strerror(errno));
    printf("Please try executing the controls file first!\n");
    return 0;
  }
  
  //setting keys
  shmkey = ftok("makefile", 6);
  semkey = ftok("makefile", 'a');
 
  //getting our semaphore:
  semid = semget(semkey, 1, 0664);

  //checking if available to use:
  int sval = semctl(semid, 0, GETVAL);
  if (sval == 0)
    printf("Currently waiting for other writer to finish...\n");
 
  //setting sembuf and performing down operation
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; //down
  semop(semid, &sb, 1); 
 
  //accessing shared memory and attaching
  sm = shmget(shmkey, 1024, 0664);
  int *lsize = shmat(sm, 0, 0);
 
  //seeking, reading, and printing current last line
  lseek(fd, (*lsize * -1), SEEK_END);
  char *lastline = (char*)malloc(sizeof(char)*(*lsize+1));
  read(fd, lastline, *lsize);
  printf("Currently, the last sentence of 'story.txt' is:\n%s\n", lastline);
  printf("The size of this last sentence is %d bytes long!\n", *lsize);

  //prompt:
  printf("What should the next line be?\n\n");
  char s[512];
  fgets(s, sizeof(s), stdin);//user input
  char *input = s;

  //getting rid of trailing whitespaces,
  //adding spaces between entries
  input = strsep(&input, "\n");
  printf("\nYou have entered: %s\n", input);
  input = strcat(input, " ");
  
  //writing to file and updating value of shared memory
  int b = write(fd, input, strlen(input));
  *lsize = b;
  printf("%d bytes have been written to 'story.txt' :-)\nThank you for your contribution!\n", *lsize);
  
  //detaching, closing, and releasing
  shmdt(lsize);
  close(fd);
  sb.sem_op = 1; //up-ing
  semop(semid, &sb, 1);

  return 0;
}
