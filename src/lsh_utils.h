#ifndef LSH_UTILS_H
#define LSH_UTILS_H


/*
Utils declarations
*/
char * curr_dir();
void print_dir(char type);
char *get_homedir(void);
char *build_full_path(const char* p_home, const char* p_cfg_file_name);
bool file_exists(const char *filenamme);

#endif // LSH_UTILS_H
