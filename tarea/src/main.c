#include <stdio.h>
#include <stdlib.h>

#include "user_list.h"
#include "tweet_list.h"
#include "hash_table.h"
#include "main_screen.h"


int main() {

    /*Se inicializa la tabla de hash al comenzar el programa*/
    user_node** hash_table = new_hash_table();

    main_screen(hash_table);
    
    return 0;
}
