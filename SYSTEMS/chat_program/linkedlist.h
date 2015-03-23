#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "server.h"

struct node {
  struct user *user;
  struct node *next;
};

char print_list(struct node *);
struct node *insert_front(struct node *, struct node *);
struct node *free_list(struct node *);
struct node *createsong(struct user *user);
struct node *remove_node(struct node *, struct node *); //rets beginning of list

char *lowerstring(char *);

#endif //SERVER_H