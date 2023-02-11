#ifndef __MAIN_SCREEN_H__
#define __MAIN_SCREEN_H__

#include "user_list.h"

/**
 * Funciones para la pantalla principal
 */

void read_user_and_pass(char **username, char **password);
void add_tweet(user **u, char *str_tw);
void secondary_screen(user **u);
void screen1(user_node **hash_table);
void screen2(user_node **hash_table);
void screen3(user_node **hash_table, user **u, user *to_user);
void screen4(user_node **hash_table);
void clear_string(char **input);
#endif
