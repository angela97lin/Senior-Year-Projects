#include <stdio.h>
#include <stdlib.h>
/*
Write a simple linked list program. You will need a define a node struct with the following data members:
    A piece of data (your choice, but make it a primitive data type)
    A pointer to the next node
Create the following functions:
    -->print_list
        Should take a pointer to a node struct and print out all of the data in the list
    -->insert_front
        Should take a pointer to the existing list and the data to be added, create a new node, put it at the beginning of the list and return a pointer to the beginning of the list.
    -->free_list
        Should take a pointer to a list as a parameter and then go through the entire list freeing each node and return a pointer to the beginning of the list (which should be NULL by then).          
*/

typedef struct foo {
  int a;
  struct foo *next;}
  node;

void print_list(node *n);
node *insert_front(node *existing, int a);
node *free_list(node *n);

int main(){
  //setting up linked list for testing purposes; there is no need to use various
  //nodes--> use insert_front! 
  
  node *a = 0;//null/0
  a = insert_front(a, 1);
  a = insert_front(a, 2);
  a = insert_front(a, 3);
  printf("Now printing linked list...\nResult should be:\n3\n2\n1\n");
  printf("Results via print_list fxn:\n");
  print_list(a);
  ////////////////////////////////////////////////////

  printf("Now testing insert_front fxn...\n");
  printf("Before inserting 4, list is:\n");
  print_list(a);
  printf("After insertion, the new list should be:\n4\n3\n2\n1\n");
  printf("After testing, the new list is:\n");
  print_list(insert_front(a, 4));
  a = insert_front(a, 4);
  ////////////////////////////////////////////////////

  printf("Now testing free_list fxn:\n");
  printf("Before freeing, list is:\n");
  print_list(a);
  printf("Aftering free_list, list should be:\n0 or NULL\n");
  printf("After testing, free_list returns:\n");
  a = free_list(a);//free_list does not actually modify a
  print_list(a);

}

void print_list(node *n){
  while (n){
    printf("%d\n", n->a);//or (*n).a
    n = n->next;
  }
}

node *insert_front(node *existing, int a){
  node *newnode = (node *)malloc(sizeof(node));
  newnode->a = a;
  newnode->next = existing;
  return newnode;
}

node *free_list(node *n){
  node *placeholder;  
  while (n){
    placeholder = n->next;
    free(n);
    n = placeholder;
  }
  return n;
}

//DW's version:
//node *free_list(node *n){
//node *p;
//while (front) {
//p = front;
//front = front->next;
//free(p)
//}
//return front;
//}
