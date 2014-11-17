#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include "song.h"

//returns the size of the linked list
int size_of_ll(song_node *n){
  int size = 0;
  while (n){
    size++;
    n = n->next;
  }
  return size;
}
  
//prints song title and artist name
void print_list(song_node *n){
  while (n){
    printf("~%s by %s\n", n->title, n->artist);
    n = n->next;
  }
}

//finds and returns a pointer to an individual song based on song name; if not in specified list, returns 0
song_node *find_song(song_node *list_name, char tit[256]){
  while (list_name){
    if (strcasecmp(list_name->title,tit)==0)
      return list_name;
    else 
      list_name = list_name->next;
  }
  //printf("Specified song NOT FOUND\n");
  return 0;
}

//finds and returns a pointer to the first song by the specifed artist in specified list (list_name); if not in list, return 0
song_node *find_first_song_by_artist(song_node *list_name, char art[256]){
  while(list_name){
    //printf("strcasecmp(list_name->artist, art):%d",strcasecmp(list_name->artist, art));
    if (strcasecmp(list_name->artist, art)==0)
      return list_name;
    else
      list_name = list_name->next;
  }
  printf("There are no songs by this artist! Booooo.\n");
  return 0;
}

//finds and returns a pointer to a random song in the specified list; perhaps random is not so random?
song_node *find_random(song_node *list_name){
  int r = rand() % (size_of_ll(list_name));
  //printf("r:%d\n",r);
  while (r > 0){
    list_name = list_name->next;
    r--;
    //printf("current song is now:%s\n",list_name->title);
  }
  return list_name;
}
//removes a node in specified list by being given node
song_node* remove_given_node(song_node *list_name, song_node *rem){
  song_node *front = list_name;
  if (list_name == rem){ //checks if we are removing first node
    if (list_name->next == NULL){ //if first node is the ONLY node...
      printf("Removing the one and only! :c\n");
      return NULL;
    }
    else {
      song_node *new_front = list_name->next;//necessary so we can free before returning (?)
      free(list_name);
      return (new_front);
    }
  }
  else {//not removing first node!
    song_node *helper_node = list_name;
    list_name = list_name->next;
    while (list_name){
      if (list_name == rem){ //if we are at the node we want to remove
	helper_node->next = list_name->next; 
	free(list_name);
	return front;
      }
      else {
	helper_node = list_name;
	list_name = list_name->next;
      }
    }
    return front;
  }
}

//removes a node from specified list based on artist and title
song_node* remove_node(song_node *list_name, char art[256], char tit[256]){
  song_node *front = list_name;//reference to the first node
  song_node *helper_node = list_name;//used to backtrack
  int artcomp = (strcasecmp(list_name->artist, art));
  int titlecomp = (strcasecmp(list_name->title, tit));
  //printf("Artcomp:%d\nTitlecomp:%d\n",artcomp,titlecomp); 
  if (artcomp == 0 && titlecomp == 0){//removing first node
    if(list_name->next == NULL){//if first node is only node
      //printf("Removing the one and only! :c\n");
      return NULL;
    }
    else {//just set the new front to the second node and freeeee the first node!   
      song_node *new_front = list_name->next;
      free(list_name);
      return (new_front);
    }
  }
  else { //we are NOT removing the first node
    list_name = list_name->next;
    while (list_name){
      artcomp = (strcasecmp(list_name->artist, art));
      titlecomp = (strcasecmp(list_name->title, tit));
      //printf("artcomp:%d\ntitlecomp:%d\n",artcomp,titlecomp);
      if (artcomp == 0 && titlecomp == 0){//this is what we are looking for!
	helper_node->next = list_name->next;
	//printf("helper_node's song:%s\n",helper_node->title);
	free(list_name);//free! free!!
	return front;
      } 
      else {
	helper_node = list_name;
	list_name = list_name->next;
      }
    }
    return front;
    }
}
//possible to just move data to next node and then free previous one?! :D

//inserts new song_node to the beginning of a specified linked list
song_node *insert_front(song_node *existing, char art[256], char tit[256]){
  song_node *new_node = (song_node *)malloc(sizeof(song_node));
  strcpy((new_node->artist), art);
  //printf("Artist:%s\n",newsong_node->artist);
  strcpy((new_node->title), tit);
  //printf("Title:%s\n",newsong_node->title);
  new_node->next = existing;
  return new_node;
}

//inserts new song_node alphabetically...
song_node *insert_alphabetically(song_node *existing, char art[256], char tit[256]){
  song_node *first = existing;//pointer that can be used to retrieve stuff later
  song_node *helper_node = existing;
  song_node *newsong_node = (song_node*)malloc(sizeof(song_node));
  strcpy((newsong_node->artist), art);//copy into new node the artist
  strcpy((newsong_node->title), tit);//copy into new node the title 
  if (existing == NULL) //if the list is currently empty
    return newsong_node;
  int artcomp = (strcasecmp(existing->artist, art));
  int titlecomp = (strcasecmp(existing->title, tit));  
  if (artcomp >= 0){//checks if we should place new node first
    if (artcomp == 0 && titlecomp > 0){
      newsong_node->next = existing;
      return newsong_node;
    }
    if (artcomp > 0){
      newsong_node->next = existing;
      return newsong_node;
    }
  }
  while (existing){
    artcomp = (strcasecmp(existing->artist, art));
    if (artcomp < 0){//keep moving on
      helper_node = existing;
      existing = existing->next;
    }
    else if (artcomp > 0){//we need to stop!
      helper_node->next = newsong_node;
      newsong_node->next = existing;
      return first;
    }
    else { //artcomp == 0; the two artists are equal so we must check titles
      titlecomp = (strcasecmp(existing->title, tit));
      if (titlecomp < 0){
	helper_node = existing;
	existing = existing->next;
      }
      else if (titlecomp > 0){
	helper_node -> next = newsong_node;
	newsong_node->next = existing;
	return first;
      }
      else {//titles and artists are equal->must be duplicate
	printf("Duplicate! Not appended.\n");
	return first;
      }
    }
  }
  //must insert in last
  if (existing == NULL){
    helper_node->next = newsong_node;
  }
  return first;
}
	
//FREEES the specified list! ^-^ (freeeeee~~~)
song_node *free_list(song_node *n){
  song_node *placeholder;
  while (n){
    placeholder = n;
    n = n->next;
    free(placeholder);
  }
  return n;
}
