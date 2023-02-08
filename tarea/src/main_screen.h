#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__

#include "user_list.h"

/**
 * Funciones para la pantalla principal
 */

void main_screen(user_node **hash_table);
void read_user_and_pass(char username[], char password[]);
#endif
