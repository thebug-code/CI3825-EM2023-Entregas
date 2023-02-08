#include <stdio.h>
#include <stdlib.h>

#include "user_list.h"
#include "tweet_list.h"
#include "hash_table.h"
#include "main_screen.h"

int main() {
    user_node **t = new_hash_table();
    /* user *u0 = new_user("admeneses", 5); */
    /* printf("%s\n", u0->username); */
    /*printf("%d\n", hash_code("admeneses\0")); */
    /*insert_user_hash_table(&t, u0); */
    /*insert_user_hash_table(&t, u0); */
    /*insert_user_hash_table(&t, u0); */
    /*printf("%d\n", hash_code(u0->username)); */
    /*printf("%s\n", t[9]->next->next->data->username); */
    main_screen(t);
    free_table(t);
    return 0;
}
