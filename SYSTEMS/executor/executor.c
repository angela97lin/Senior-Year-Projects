#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Work 5: How to get away with execution:
Write a c program that runs a command line program with exactly one command line argument. It should work as follows:
*Prompts the user for a program to run via the command line.
*Reads in that line (using fgets) and parses it to be used by one of the exec functions.
*Runs the command using exec
*You do not need to fork off a separate process and wait, the purpose of this assignment is only to parse a single line of input and run a program once.
*/
void execute(){
  printf("Please enter a command:\n");
  char s[256];

  //fgets(string, size, stdin)
  fgets(s, sizeof(s), stdin);

  //since arrays are immutable
  char* s1 = s; //user input
  //printf("%s\n",s1);
  
  char *sep;
  char** args = NULL;//to store arguments for execvp
  int i = 0;//how many args, including command

  //gets rid of trailing whitespace due to fgets
  s1 = strsep(&s1, "\n");
  //printf("ORIGINAL s1:%s\n",s1);
  
  while (sep = strsep(&s1, " ")){
    //printf("sep:%s\n",sep);
    //printf("s1:%s\n",s1);
    i++;
    args = realloc(args, sizeof(char*)*i);
    args[i-1] = sep;//start w/ 0
  }
  args[i] = 0;//set last element to NULL for safety purposes
  /*
  int t;
  for (t = 0; t<i; t++)
    printf("args %d:%s\n", t,args[t]);
  */
  execvp(args[0], args);
  free(args);
}

int main(){
  execute(); 
  return 0;
}
