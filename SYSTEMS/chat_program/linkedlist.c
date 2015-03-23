#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"


char print_list(struct node *PTR) {
  if(!PTR) {
    printf("Cannot print: List is empty\n");
    return 0;
  }
  
  while(PTR->next) {
    printf("%s\t",PTR->user->nick);
    PTR = PTR->next;
  }
  printf("%s\t\n",PTR->user->nick);
  return 1;
}

struct node *insert_front(struct node *PTR, struct node *song) {
  song->next = PTR;
  return song;
}


struct node *createsong(struct user *user) {
  struct node *new = (struct node *)malloc(sizeof(struct node));
  new->user = user;
  return new;
}

struct node *free_list(struct node* list) {
  struct node *n;
  while(list) {
    n = list->next;
    free(list->user);
    free(list);
    list = n;
  }
  return list;
}

struct node *search_list_nick(struct node* lookin, char *nick) {
  while(lookin) {
    if(strcmp(lookin->user->nick,nick) == 0) {
      return lookin;
    }
    lookin = lookin->next;
  }

  return 0;
}

char *lowerstring(char *str) {
  int i;
  for (i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
  return str;
}


struct node *remove_node(struct node *list, struct node *toremove) {
  struct node *prev = 0;
  struct node *copy = list;
  if (list == toremove) {
    struct node *ret = list -> next;
    free(toremove->user); 
    free(toremove);
    return ret;
  }
  while(list) {
    if (list == toremove) {
      prev -> next = list -> next;
      free(toremove->user);
      free(toremove);
      return copy;
    }
    prev = list;
    list = list -> next;
  }
  return copy;
}
