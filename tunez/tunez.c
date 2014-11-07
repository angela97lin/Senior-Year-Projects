#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include "song.h"
#include "library.h"

/*this is our MAIN file, which will run when we MAKE and will serve to print
all happy things!
In order to run this file, simply type "make" into the terminal! (:
*/
song_node *library[26];
int main(){
  
  srand(time(NULL));//FOR ALL OUR WONDERFUL RANDOMNESS
  //THE LIBRARY FUNCTIONALITY: 
  //pointer to a pointer (array)
  song_node **library = (song_node**)(malloc(sizeof(song_node*)*26));
  printf("Now testing music library functions...\n");
  printf("Currently, the library has no songs. The size of the library should be 0.\n");
  printf("Size of library via fxn: %d\n",size_of_library(library));
  if (size_of_library(library) == 0){
    printf("Yay!\n");
  }
  printf("\nAdding one song to library...\n");
  printf("Currently, the library has one song. The size of the library should be 1.\n");
  
  add_song(library, "The Summer Set","Boomerang");
 
  printf("Size of library via fxn: %d\n",size_of_library(library));
  if (size_of_library(library) == 1){
    printf("Yay!\n");
  }
  printf("\nNow attempting to add duplicate song...Should result in a no-no and size of library should still be 1.\n");
  add_song(library, "The Summer Set","Boomerang");
  printf("Size of library via fxn: %d\n",size_of_library(library));
  if (size_of_library(library) == 1){
    printf("Yay!\n");
  }
  printf("\nNow adding 39 songs into music library...Size after addition should be 40.\n");
  add_song(library, "A Rocket to the Moon","She's Killing Me");
  add_song(library, "A Rocket to the Moon","Baby Blue Eyes");
  add_song(library, "Boys Like Girls","Thunder");
  add_song(library, "Faber Drive","Tongue Tied");
  add_song(library, "Linkin Park","Numb");
  add_song(library, "Linkin Park","In The End");
  add_song(library, "Hoobastank","The Reason");
  add_song(library, "The Cab","Intoxicated");
  add_song(library, "Rise Against","Prayer Of The Refugee");
  add_song(library, "Artist vs Poet","Whiskey Problems");
  add_song(library, "We The Kings","Skyway Avenue");
  add_song(library, "Marina and The Diamonds","How To Be A Heartbreaker");
  add_song(library, "Three Days Grace","Never Too Late");
  add_song(library, "Shinedown","Second Chance");
  add_song(library, "Relient K","Who I Am Hates Who I've Been");
  add_song(library, "Relient K","Be My Escape");
  add_song(library, "Parachute","White Dress");
  add_song(library, "Parachute","Can't Help");
  add_song(library, "Coldplay","A Sky Full of Stars");
  add_song(library, "Coldplay","Paradise");
  add_song(library, "SafetySuit","Let Go");
  add_song(library, "OneRepublic","Stop and Stare");
  add_song(library, "Every Avenue","Tell Me I'm A Wreck");
  add_song(library, "Yellowcard","Five Becomes Four");
  add_song(library, "Sum41","In Too Deep");
  add_song(library, "The Cab","Angel With a Shotgun");
  add_song(library, "Jimmy Eat World","The Middle");
  add_song(library, "Good Charlotte","I Don't Wanna Be In Love");
  add_song(library, "Matt Nathanson","Come On Get Higher");
  add_song(library, "OneRepublic","Good Life");
  add_song(library, "The Fray","Syndicate");
  add_song(library, "The Fray","You Found Me");
  add_song(library, "Maroon 5","This Love");
  add_song(library, "Maroon 5","Payphone");
  add_song(library, "Daughtry","Life After You");
  add_song(library, "Mat Kearney","Ships in the Night");
  add_song(library, "The Neighbourhood","Sweater Weather");
  add_song(library, "The Goo Goo Dolls","Slide");
  add_song(library, "Vertical Horizon","Everything You Want");
  
  printf("Size of library via fxn: %d\n",size_of_library(library));
  if (size_of_library(library) == 40){
    printf("Yay!\n");
  } 
  printf("\nCurrently, the library is...\n");
  print_library(library);

  printf("\n\nNow printing all artists starting with 's':\n");
  print_letter(library,'s');
  
  printf("Now printing all artists starting with 'S'. This should result in the same thing as printing all artists starting with 's':\n");
  print_letter(library,'S');
 
  printf("Now printing all artists starting with 'x'. This should result in an empty string:\n");
  print_letter(library,'x');
  printf("\nNow printing all songs by OneRepublic:\n");
  print_artist(library,"OneRepublic");
  print_library(library);
  printf("\nNow printing all songs by All Time Low. This should result in an empty list:\n");
  print_artist(library,"All Time Low");
  
  printf("\nNow shuffling using shuffle_ten which will print 10 songs.\n");
  shuffle_ten(library);
  
  printf("\nNow shuffling using shuffle where num = 20. This will print 20 songs.\n");
  shuffle(library,20);

  printf("\nNow searching for the first and only song by 'Yellowcard.' This should be 'Five Becomes Four':\n");
  printf("First song by 'Yellowcard' as returned by search_artist fxn:%s\n", search_artist(library,"Yellowcard")->title);
  print_library(library);
  printf("\nNow searching for the first song by 'The Cab'. This should be 'Angel With a Shotgun':\n");
  printf("First song by 'The Cab' as returned by search_artist fxn:%s\n", search_artist(library,"The Cab")->title);

  printf("\nNow searching for the song 'Sweater Weather'. We will vertify that we have found the song by printing its artist, which should be 'The Neighbourhood'.\n");
  printf("Artist of 'Sweater Weather', as returned by the search_song fxn: %s\n",search_song(library,"Sweater Weather")->artist);
  printf("\n\nAs previously stated, the current size of our library is:%d\n",size_of_library(library));

  printf("Let us now test deleting a song...We will delete Coldplay's 'Paradise'.\n");
  printf("Before deleting...\n");
  print_artist(library, "Coldplay");
  printf("After deleting 'Paradise'...\n");
  delete_song(library,"Coldplay","Paradise");
  print_artist(library, "Coldplay");
 
  printf("\n\nNow deleting entire library! :(((((((((((((\n");
  delete_all(library);
  printf("Now, the library has no songs again. The size of the library should be 0.\n");
  printf("Size of library via fxn: %d\n",size_of_library(library));
  if (size_of_library(library) == 0){
    printf("Yay!\n");
  }
  printf("\nPrinting the library to double confirm that library is empty and songless...\n");
  print_library(library);
  
  //=================================================================
  //LINKED LIST FUNCTIONALITY:  
  song_node *a = 0;//null, 0
  
  printf("Testing LINKED LIST FUNCTIONALITY:\n");
  printf("Currently, our linked list has 0 elements. The size should be 0.\n");
  printf("The size of our linked list as returned by the size_of_ll fxn: %d\n",size_of_ll(a));
  if (!size_of_ll(a))
    printf("Yippee!\n");
  printf("Now inserting 'It Ends Tonight' by 'The All-American Rejects' to the front of our linked list...\n");
  a = insert_front(a, "The All-American Rejects", "It Ends Tonight");
  printf("After insertion, our linked list looks like:\n");
  print_list(a);
  printf("We will now remove this song so we can build a list alphabetically...\n");
  a = remove_node(a, "The All-American Rejects", "It Ends Tonight");
  printf("After removing, our list should be empty again. Printing linked list to double check:\nLinked list:");
  print_list(a);
  printf("\nNow we will add a few songs to our linked list of song_nodes...\n");
  
  a = insert_alphabetically(a, "Metro Station","Seventeen Forever");
  a = insert_alphabetically(a, "Paramore", "When It Rains");
  a = insert_alphabetically(a, "The Maine", "Into Your Arms");
  a = insert_alphabetically(a, "The Maine", "Saving Grace");
  a = insert_alphabetically(a, "Marianas Trench", "Stutter");
  a = insert_alphabetically(a, "We The Kings", "Art of War");
  a = insert_alphabetically(a, "A Rocket to the Moon", "Mr. Right");
  a = insert_alphabetically(a, "Bowling For Soup", "Stacy's Mom");
  a = insert_alphabetically(a, "The Red Jumpsuit Apparatus", "Your Guardian Angel");
  a = insert_alphabetically(a, "Mayday Parade","Somebody That I Used To Know");  
  printf("After adding 10 songs...Our linked list:\n");
  print_list(a);
   printf("\nCurrently, our linked list has 10 elements. The size should be 10.\n");
  printf("The size of our linked list as returned by the size_of_ll fxn: %d\n\n",size_of_ll(a));
  
  printf("Now searching for the first song by 'The Maine'. The song 'Into Your Arms' should be returned.\n");
  printf("First song by 'The Maine':%s\n\n",find_first_song_by_artist(a,"The Maine")->title);
  
  printf("Now searching for the song 'Art of War' by 'We The Kings'. We will confirm that we have found the song by printing out the artist of the song, which should be 'We The Kings.\n");
  printf("The artist of 'Art of War' as returned by the find_song fxn is: %s\n",find_song(a, "Art of War")->artist);
  //printf("%s\n",find_song(a, "Lalala")->artist);//should result in segmentation fault because there is no Lalala
  
  printf("Now testing finding a random song. Let us do this five times...for fun.\n");
  printf("First random song: %s by %s\n",find_random(a)->title,find_random(a)->artist);
  printf("Second random song: %s by %s\n",find_random(a)->title,find_random(a)->artist);
  printf("Third random song: %s by %s\n",find_random(a)->title,find_random(a)->artist);
  printf("Fourth random song: %s by %s\n",find_random(a)->title,find_random(a)->artist);
  printf("Fifth random song: %s by %s\n",find_random(a)->title,find_random(a)->artist);
  

  printf("\nNow let us FREE THE LIST!!");
  free_list(a);
 
}
//end of main fxn
