#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

/*
Work 4: Please follow the directions
Due Wednesday (10/29) Morning 8am

You will write a program that will gather various information about a directory, specifically:

*list all the files in the directory
*specify which files are directories (if any)
*show the total size of all the regular files the directory
-->note that you do not have to recursively go through any subdirectories to find their size for this part (unless you want to, but that is not a simple task)
*By default, have the program scan the current directory
*The program should be able to take a command line argument representing the directory to be scanned.

Possible enhancements:
*Recursively list the files in any subdirectories, update the total to include the total size of subdirectories
*Print out the size in a more readable format (like using K, M, G for -byte prefixes)
*/

int dir_size(char* path[256]){
  int ret;
  DIR* stream;
  stream = opendir(path);
  //printf("has opened\n");
  struct dirent *a = readdir(stream);
  char *this = ".";
  char *before = "..";
  char* original[256];//used to store original path since at end, we end up one level higher generally
  char* currdir[256];

  getcwd(original, sizeof(original));
  while (a){
    if (a->d_type == DT_REG){
      struct stat info;
      stat(a->d_name, &info);
      //printf("info.st_size:%d\n",info.st_size);
      ret = ret + info.st_size;
    }
    else if (a->d_type == DT_DIR && (strcmp(a->d_name,this) && strcmp(a->d_name,before))){//recursively find size 
      //chdir(path);
      //printf("a->name:%s\n",a->d_name);
      chdir(a->d_name);
      getcwd(currdir, sizeof(currdir));
      //printf("currdir:%s\n",currdir);
      //printf("dir_size(a->d_name):%d\n",dir_size(currdir)); 
      ret = ret + dir_size(currdir); 
      chdir(".."); 
    } 
    a = readdir(stream);//kind of like moving pointer along
  }
  rewinddir(stream);
  chdir(original);
  //printf("now currdir:%s\n",currdir);   
  return ret;
}

//returns 1 if file is a directory
//returns 0 if file is NOT a directory
int is_dir(struct dirent *file){
  if (file->d_type == DT_DIR)//if file is a directory
    return 1;
  else 
    return 0;
}

void list_dirs(char *currdir[256]){
  DIR* stream;
  stream = opendir(currdir);
  struct dirent *a;
  a = readdir(stream);
  printf("Directories in %s:\n",currdir);
  while (a){
    if (is_dir(a))
      printf("%s\n", a->d_name);
    a = readdir(stream);
  }
  rewinddir(stream);
}

int is_reg_file(struct dirent* file){
  if (file->d_type == DT_REG)
    return 1;
  else
    return 0;
}

void list_reg_files(char *currdir[256]){
  getcwd(currdir, sizeof(currdir));
  DIR* stream;
  stream = opendir(currdir);
  struct dirent *a;
  a = readdir(stream);
  printf("Regular files in %s:\n",currdir);
  while (a){
    if (is_reg_file(a))
      printf("%s\n",a->d_name);
    a = readdir(stream);
  }
  rewinddir(stream);
}


void list_files(char *currdir[256]){
  DIR* stream;
  stream = opendir(currdir);
  struct dirent *a;
  a = readdir(stream);
  printf("Files in %s:\n",currdir);
  while (a){
    printf("type of file:%d\n",a->d_type);
    printf("name of file:%s\n",a->d_name);
    //printf("Is dir?:%d\n", is_dir(a));
    //if (is_dir(a))
    //  printf("%s is a directory!\n", a->d_name);
    a = readdir(stream);
  }
  rewinddir(stream);
}

int main(int argc, char** argv){
  //printf("DT_DIR:%d\n", DT_DIR);
  //printf("DT_REG:%d\n", DT_REG);
  char* currdir[256];
  if (argc == 1){
    getcwd(currdir, sizeof(currdir));
    printf("Current working directory (cwd) is:%s\n\n", currdir);
    printf("Here are statistics for directory %s:\n", currdir);
    printf("Total Directory Size:%d Bytes\n",dir_size(currdir));
    //list_files(currdir);
    list_dirs(currdir);
    printf("\n");
    list_reg_files(currdir);
    printf("\n");
  }
  else { //given a specific command line argument representing the directory to be scanned
    strcpy(currdir,argv[1]);
    printf("Command line argument is:%s\n\n", currdir);
    printf("Here are statistics for directory %s:\n", currdir);
    printf("Total Directory Size:%d Bytes\n\n",dir_size(currdir));
    //list_files(currdir);
    list_dirs(currdir);
    printf("\n");
    list_reg_files(currdir);
    printf("\n");

  }
  return 0;
}
