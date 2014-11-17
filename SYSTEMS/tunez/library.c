#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>
#include "song.h"
#include "library.h"

int find_slot(song_node **lib, char artist[256]){
  int slot;
  if (artist[0]>=65 && artist[0]<=90){
    slot = artist[0]-65;
  }
  else if (artist[0]>=97 && artist[0]<=122){
    slot = artist[0]-97;
  }
  else {
    return;
  }
  //printf("slot:%d\n",slot);
  return slot;
}
//adds a given song node to the music library
void add_song_node(song_node **lib, song_node *newsong){
  int slot = find_slot(lib,newsong->artist);
  lib[slot] = insert_alphabetically(lib[slot], newsong->artist, newsong->title);
}

//adds a new song (song_node) to the music library, given artist and title of song
void add_song(song_node **lib, char artist[256], char tit[256]){
  int slot = find_slot(lib,artist);
  //printf("SLOT:%d\n",slot);
  lib[slot] = insert_alphabetically(lib[slot], artist, tit);
  //print_list(lib[slot]);
}

//searches for a given song (first one found if more than one artist with same song title) and returns the pointer to the song; if song is not found, then return 0
song_node *search_song(song_node **lib, char tit[256]){
  int i = 0;
  while (i<26){
    song_node* song = find_song(lib[i], tit);
    if (song)
      return song;
    else
      i++;
  }
  printf("Song '%s' was not found.\n", tit);
  return 0;
}

//searches for the first song by an artist
song_node *search_artist(song_node **lib, char artist[256]){
  int slot = find_slot(lib,artist);
  //printf("slot:%d",slot);
  //print_list(lib[slot]);
  song_node* song = find_first_song_by_artist(lib[slot], artist);
  //printf("%s", song->artist);
  return song;
}

void delete_song_node(song_node **lib, song_node *del){
  int slot = find_slot(lib,del->artist);
  lib[slot] = remove_given_node(lib[slot], del);
}

void delete_song(song_node **lib, char art[256], char tit[256]){
  int slot = find_slot(lib, art);
  lib[slot] = remove_node(lib[slot], art, tit);
  //print_list(lib[slot]);
}

void delete_all(song_node **lib){
  int i;
  for(i=0;i<26;i++){
    lib[i]=0;
  }
}
int size_of_library(song_node **lib){
  int i;
  int size = 0;
  for (i=0; i<26;i++){
    size = size + size_of_ll(lib[i]);
  }
  return size;
}

void shuffle_ten(song_node **lib){
  shuffle(lib, 10);
}
//may have repeats -->ok!
void shuffle(song_node **lib, int num){
  srand(time(NULL));
  if (num > size_of_library(lib)){
    printf("You have attempted to request more songs than there are in the library! We will return as many songs as possible.\n");
    num = size_of_library(lib);
  }
  while (num > 0){
    int slot = rand() % 26;
    //printf("slot:%d\n", slot);
    if (lib[slot]){//not pointing to emptiness
      song_node *rand = find_random(lib[slot]);
      printf("~%s by %s\n", rand->title, rand->artist);
      num--;
    }
    else 
      slot = rand() % 26;
    //printf("num:%d", num);
  }
  
}
/*
Why does this cause lib[slot] to disappear and the library to shrink?
void print_artist(song_node **lib, char art[256]){
  int slot = find_slot(lib, art);
  printf("\nSongs by %s:\n", art);
  while (lib[slot]){
    if (strcasecmp(lib[slot]->artist,art)==0){
      printf("%s\n",lib[slot]->title);
    }
      lib[slot] = lib[slot]->next;
  }
  printf("\n==============\n");
}
*/
void print_artist(song_node **lib, char art[256]){
  int slot = find_slot(lib, art);
  printf("\nSongs by %s:\n", art);
  song_node *helper = lib[slot];
  while (helper){
    if (strcasecmp(helper->artist,art)==0){
      printf("%s\n",helper->title);
    }
      helper = helper->next;
  }
  printf("\n==============\n");
}

void print_library(song_node **lib){
  int i = 0;
  printf("\n=================YOUR MUSIC LIBRARY===============\n");
  printf("Here is your music library, arranged by ARIST NAME:\n");
  for (i = 0; i<26; i++){
    printf("%c:\n",i+65);
    print_list(lib[i]);
    printf("\n");
  }
  printf("\n==================END OF LIBRARY===================\n");
}

void print_letter(song_node **lib, char a){
  int slot = a;
  if (a >= 97 && a <= 122){//a-z
    slot = slot-97;
  }
  else if (a >= 65 && a <=90){//A-Z
    slot = slot-65;
  }
  else {
    printf("You're crazy. Please search between a-z or A-Z!\n");
    return;
  }
  printf("Printing all songs by artists starting with '%c':\n",a);
  //printf("slot:%d\n",slot);
  print_list(lib[slot]);
}
