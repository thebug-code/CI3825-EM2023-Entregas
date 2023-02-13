#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "screens.h"

int main() {
    /*Se inicializa la tabla de hash al comenzar el programa*/
    user_node **t = new_hash_table();

    screen1(t);
    free_table(t);

    return 0;
}
