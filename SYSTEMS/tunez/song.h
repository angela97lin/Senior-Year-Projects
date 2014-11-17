typedef struct song_node {
  char artist[256];
  char title[256];
  struct song_node *next;}
  song_node;

//linked list function headers:
void print_list(song_node *n);

song_node *insert_front(song_node *existing, char art[256], char tit[256]);

song_node *free_list(song_node *n);

song_node *insert_alphabetically(song_node *existing, char art[256], char tit[256]);

song_node *remove_node(song_node *list, char art[256], char tit[256]);

song_node* remove_given_node(song_node *list_name, song_node *rem);

song_node *find_song(song_node *list_name, char tit[256]);

song_node *find_first_song_by_artist(song_node *list_name, char art[256]);

song_node *find_random(song_node *list_name);

int size_of_ll(song_node *n);
