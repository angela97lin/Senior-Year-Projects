void add_song_node(song_node **lib, song_node *newsong);

void add_song(song_node **lib, char artist[256], char tit[256]);

void delete_all(song_node **lib);

void print_letter(song_node **lib, char a);

void print_library(song_node **lib);

void print_artist(song_node **lib, char art[256]);

song_node *search_artist(song_node **lib, char artist[256]);

song_node *search_song(song_node **lib, char tit[256]);

void delete_song_node(song_node **lib, song_node *del);

void delete_song(song_node **lib, char art[256], char tit[256]);

void shuffle(song_node **lib, int num);

void shuffle_ten(song_node **lib);

int size_of_library(song_node **lib);
  
