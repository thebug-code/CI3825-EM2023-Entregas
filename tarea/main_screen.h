#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__

#include "user_list.h"

/**
 * Funciones para la pantalla principal
 */

void main_screen(user_node **hash_table);
void read_user_and_pass(char username[], char password[]);
void timeline_screen(user *user, user_node **hash_table);
void desplegar();
void user_menu(user *user, user_node **hash_table);
void folower_menu();
void write_tweet(user* user);

#endif
