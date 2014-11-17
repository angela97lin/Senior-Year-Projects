#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "rwstruct.h"

/* 
Write a program that will read and write structs. Specifically:

    Create a struct that has at least 2 different pieces of data (my example uses an int and a string). 
    write 10 instances of that struct to a file
    read in those 10 instance from the file and print them out
    ask the user to enter the number of an entry, lseek to that entry and print it out (i.e. if the user enters 2, it should print out the second struct in the file)
    ask the user to enter the number of an entry, lseek to that entry, modify that entry (to whatever you'd like), and then print out the entire file.(i.e. if the user enters 2, write a new struct in the second spot, then print out all the entries.

*/
data* list[10];
char* strstuff[10] = {"Here is cero",
		      "Here is one.",
		      "Here is dos",
		      "Here is san",
		      "Here is quatro",
		      "Here is five",
		      "Here is my favorite number!",
		      "Here is lucky seven~",
		      "Here is magic 8!",
		      "Here is the last elemento~" };


//char* strstuff[10] = {"1","2","3","4","5","6","7","8","9","0" };


int main(){
  int fd;//file descriptor
  fd = open("test", O_CREAT | O_TRUNC | O_RDWR);
  //prints out file error, if any
  if (fd < 0)
    printf("error %d: %s\n", errno, strerror(errno));

  //printf("fd:%d\n",fd); //should return 3!
  //int yay = 4;
  //int b = write(fd,&yay,sizeof(int));//should return 4
  //printf("b:%d\n",b);
  //int i = 0;
  //for (i = 0; i<10; i++){
  //  printf("%s\n",strstuff[i]);
  //}

  //setting up our list of data structs
  int i = 0;
  for (i = 0; i<10; i++){
    list[i] = (data*)malloc(sizeof(data));
    list[i]->num = i*10;
    strcpy(list[i]->str,strstuff[i]);//using strcpy since arrays are immutable
    //printf("i = %d, new_data->num = %d, new_data->str = %s\n",i,new_data->num, new_data->str);
  }

  //WRITING TO A FILE:
  int sum;//will return total bytes written
  int b;//returns bytes written when you go through for-loop once
  for (i = 0; i<10; i++){
    //printf("&list[i]:%lu\n",(list[i]));
    //printf("list[i].str:%s\n",list[i]->str);
    //printf("list[i].num:%d\n",list[i]->num);
    b = write(fd, list[i], sizeof(data));
    //printf("b:%d\n",b);
    sum = sum+b;
  }
  printf("Wrote %d bytes!\n", sum);


  ////////////////////////////////////////////////////////
  //READING A FILE
  lseek(fd, 0, SEEK_SET);//setting cursor back to beginning of file
  data printable;//temporary node
  for (i = 0; i<10; i++){  
    int amtrd = read(fd, &printable, sizeof(data));
    printf("%d: Bytes Read: %d, str: %s, num: %d\n",i, amtrd, printable.str, printable.num);
  }

  ///////////////////////////////////////////////////////
  //QUERIES: FINDING
  printf("Which element would you like to see? Please choose between 0-9.\n");
  int input;
  scanf("%d",&input);
  printf("You entered: %d...Now attempting...\n", input);
  lseek(fd, input*sizeof(data), SEEK_SET);
  data wanted;
  if (input >= 0 && input < 10){
    int amtrd = read(fd, &wanted, sizeof(data));
    printf("%d: Bytes Read: %d, str: %s, num: %d\n",input, amtrd, wanted.str, wanted.num);
  }
  else {
    printf("You fool!\n");
  }
  ////////////////////////////////////////////////////////
  //QUERIES: MODIFYING
  printf("Which element would you like to modify? Please choose between 0-9.\n");
  scanf("%d",&input);
  if (input >= 0 && input <10){
    lseek(fd, input*sizeof(data), SEEK_SET);
    printf("What would you like the new str to be?\n");
    char* new_str[100];
    scanf("%s", new_str);
    printf("What would you like the new num to be?\n");
    int new_num = 0;//default 0
    scanf("%d",&new_num);
    
    //printf("new_num:%d\n",new_num);
    data *replace = (data*)malloc(sizeof(data));
    replace->num = new_num;
    printf("replace->num:%d\n",replace->num);
    printf("new_str:%s\n",new_str);
    strcpy(replace->str, new_str);
    int rewrite = write(fd, replace, sizeof(data));
    lseek(fd, 0, SEEK_SET);//once again, cursor back to beginning

    //printing list again
    for (i = 0; i<10; i++){
      int amtrd = read(fd, &printable, sizeof(data));
      printf("%d: Bytes Read: %d, str: %s, num: %d\n",i, amtrd, printable.str, printable.num);
    }
  }
  close(fd);//closing file :D
}
