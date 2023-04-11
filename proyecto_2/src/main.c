#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cli_parser.h"
#include "directory_parser.h"

#define MAX_PATH_LEN 1024

int main(int argc, char* argv[]) {

    
    options_t *opts = (options_t*)malloc(sizeof(options_t));
    handle_cli_args(argc, argv, opts);


    traverse_directory_dfs(opts->region, opts->species, opts->appear_type);


    

    return 0;
}

