#include <process.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <dirent.h>

/*
Utils implementations
*/

bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); // close the file
    }
    return is_exist;
}

char* build_full_path(const char* p_home, const char* p_cfg_file_name)
{
#ifdef _WIN32
    const char *path_separator = "\\";
#else
    const char *path_separator = "/";
#endif

    size_t len = strlen(p_home) + strlen(path_separator) + strlen(p_cfg_file_name) + 1;

    char* fullpath = malloc(len);
    if (!fullpath)
    {
        perror("malloc error!");
        return NULL;
    }

    snprintf(fullpath, len, "%s%s%s", p_home, path_separator, p_cfg_file_name);

    return fullpath;
}

char *get_homedir(void)
{
    char homedir[PATH_MAX];
#ifdef _WIN32
    snprintf(homedir, PATH_MAX, "%s%s", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
#else
    snprintf(homedir, PATH_MAX, "%s", getenv("HOME"));
#endif
    return strdup(homedir);
}

char * curr_dir()
{
    char* buffer;
    if( (buffer=getcwd(NULL, 0)) == NULL)
    {
        perror("currdir error");
        return "";
    }
    return buffer;
}

void print_dir(char type)
{
    DIR *d = opendir(".");
    if (!d) return;

    struct dirent *e;
    DIR *test;

    while((e=readdir(d)))
    {
        if  (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".")  )
            continue;
        test = opendir(e->d_name);

        switch(type)
        {
        case 'D': //just directories
            if (test) printf("[DIR] %s\n", e->d_name);
            break;
        case 'F': //just files
            if (!test) printf("[FILE] %s\n", e->d_name);
            break;
        case 'A': //files and directories
            printf("%s %s\n", test ? "[DIR]" : "[FILE]", e->d_name);
            break;
        default:
            printf("Use 'F', 'D' or 'A' as type \n");
            break;

        }
        if (test) closedir(test);
    }
    closedir(d);
}

