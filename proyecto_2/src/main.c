#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include  "cli_parser.h"

/*
#define MAX_PATH_LEN 1024

void traverse_directory_dfs(char* region, char* species, char* appear_type) {
    DIR* dir;
    struct dirent* entry;
    char path[1024];
    struct stat statbuf;

    dir = opendir(directory_path);
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir))) {
        Omite los directorios "." y ".." 
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        Construye el path absoluto del archivo 
        snprintf(path, sizeof(path), "%s/%s", directory_path, entry->d_name);
      
        Obtiene la información del archivo
        if (lstat(path, &statbuf) == -1) {
          perror("lstat");
          continue;
        }
      
        if (S_ISDIR(statbuf.st_mode)) {
            printf("Found directory: %s (inode: %ld)\n", path, statbuf.st_ino);
            traverse_directory_dfs(path);
        } else {
            printf("Found file: %s (inode: %ld)\n", entry->d_name, statbuf.st_ino);
        }
    }

    closedir(dir);
}
*/

int main(int argc, char* argv[]) {
    /* Parsea los argumentos de la línea de comandos */
    options_t *opts = (options_t*)malloc(sizeof(options_t));
    handle_cli_args(argc, argv, opts);

    /*
    char* directory_path = malloc(strlen(argv[1]) + 1);
    strcpy(directory_path, argv[1]);
      
    Construye el path absoluto del directorio
    if (directory_path[0] != '/') {
      char* cwd = getenv("PWD");
      directory_path = realloc(directory_path, strlen(cwd) + strlen(argv[1]) + 2);
      snprintf(directory_path, strlen(cwd) + strlen(argv[1]) + 2, "%s/%s", cwd, argv[1]);
      printf(directory_path);
      printf("---------------\n");
    }

    traverse_directory_dfs(directory_path);

    free(directory_path);
    */

    return 0;
}

