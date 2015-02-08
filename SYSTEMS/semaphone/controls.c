#include "controls.h"

/*
Control for the resources:
Should take a command line argument to determine if it is creating or removing the resources.
     If creating:
          *Should make the shared memory, semaphore and file. 
	  *Set any values that are needed.
     If removing: 
          *Remove the shared memory and the semaphore
          *Display the full contents of the story.
*/

int semid;
int semkey;
int shmkey;
int sm;

int main(int argc, char** argv){
  //keys
  shmkey = ftok("makefile", 6);
  semkey = ftok("makefile", 'a');
  
  if (argc == 2){ //exactly two args, as expected
    if (strcmp(argv[1], "--c") == 0){
      creator();
    }
    else if (strcmp(argv[1], "--r") == 0){
      remover();
    }
    else {//given a command that is not defined
      printf("Please either type './controls --c' to create or './controls --r' to remove.\n");
    } 
  }
  else {//given too many or too little args
    printf("Please either type './controls --c' to create or './controls --r' to remove.\n");
  }
  return 0;
}

//creates shared memory segment, semaphore, and story.txt
void creator(){
  printf("Making new shared memory segment, semaphore, and story.txt...\n");
  int op = open("story.txt", O_RDWR | O_CREAT | O_EXCL, 0644);
  //printf("op:%d\n", op); 
  if (op == -1){
    printf("Error in creating 'story.txt': %s\n",strerror(errno));
  }
  else {
    //closing our story.txt after creation
    close(op);
  }
  //creating our shared memory segment
  sm = shmget(shmkey, 1024, IPC_CREAT | IPC_EXCL | 0664);
  //printf("sm: %d\n", sm);
  if (sm == -1){
    printf("Error in creating shared memory: %s\n", strerror(errno));
  }
  //creating our semaphore
  union semun su;
  semid = semget(semkey, 1, IPC_CREAT | 0664);
  if (semid == -1){
    printf("Error in creating semaphore: %s\n", strerror(errno));
  }
  else {
    su.val = 1;
    semctl(semid, 0, SETVAL, su);
  }
  //printf("semid: %d\n", semid);
  
  //int sval = semctl(semid, 0, GETVAL);
  //printf("sval: %d\n", sval);
  printf("Now please proceed to execute the writer file!\n");
}


//if './controls --r'
//prints contents of story.txt,
//then executes removal of shared memory segment,
// semaphore, and 'story.txt'
void remover(){
  printf("Removing shared memory, semaphore, and file...\n");
  
  //removing shared memory segment
  struct shmid_ds d;
  sm = shmget(shmkey, 1024, 0664);
  shmctl(sm, IPC_RMID, &d);
  
  //removing semaphore
  semid = semget(semkey, 1, 0664);
  semctl(semid, 0, IPC_RMID);
  int op = open("story.txt", O_RDONLY, 0644);
  
  //read and print the entirety of 'story.txt' 
  struct stat sb;
  stat("story.txt", &sb);
  int size = sb.st_size;
  printf("The size of this story is %d bytes!\n", size);
  char* story = (char*)malloc(sizeof(char)*size); 
  read(op, story, size);
  printf("Semaphone story:\n%s\n\n", story);
  close(op);

  //forking in order to remove story.txt
  int f = fork();
  if (f == 0) {//child process
    printf("Thank you for using Semaphone! Now deleting story.txt... Goodbye!~\n");
    execlp("rm", "rm", "story.txt", NULL);
  }
  else { //parent process
    wait(0);
  }
}
