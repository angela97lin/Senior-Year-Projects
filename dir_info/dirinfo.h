int dir_size(char* path[256]);

int is_dir(struct dirent *file);

void list_dirs(char *currdir[256]);

int is_reg_file(struct dirent* file); 

void list_reg_files(char *currdir[256]);

void list_files(char *currdir[256]);
