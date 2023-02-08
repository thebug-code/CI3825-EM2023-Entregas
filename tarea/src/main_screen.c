/**
 * Implementacion de la pantalla principal de la aplicacion
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "timeline.h"
#include "main_screen.h"
#include "hash_table.h"
#include "user_list.h"

/**
 * Muestra la pantalla principal, la cual pide los datos al usuario
 * @param hash_table: tabla de hash con los usuarios
 */
void main_screen(user_node **hash_table) {
    char input[7]; /* opciones de entrada */
    char username[31]; /* username del usuario */
    char password[16]; /* password del usuario */
    user *struct_user = NULL; /* Puntero al struct con los datos del user */

    printf("\nDON’T MISS WHAT’S HAPPENING! LOGIN, SIGNUP OR LEAVE\n\n");
    scanf("%s", input);

    /* login del programa*/
    if(!strcmp(input, "login")) {
        read_user_and_pass(username, password);

        /* Verificar si el login es valido */
        struct_user = get_user(hash_table, username);
        if (!struct_user || struct_user->hash_password != hash_code(password)) {
            printf("\nEl usuario o la contrasena son incorrectos\n");
            main_screen(hash_table);
        }
        else {
            /* Mostrar timeline del usuario */
            show_timeline(struct_user->sig_list);
        }

    }
    /* signup del programa*/
    else if (!strcmp(input, "signup")) {
        read_user_and_pass(username, password);

        /**
         * se agrega, en caso contrario se solicita otro username
         */
        if (!get_user(hash_table, username)) {
            insert_user_hash_table(&hash_table, new_user(username, hash_code(password)));           
        }
        else {
            printf("\nEl usuario ya existe. Intente con otro usuario\n");
        }
        main_screen(hash_table);
    }
    /* salida del programa*/
    else if (!strcmp(input, "leave")) {
        exit(0);
    }
    /* regresa al prompt inicial en caso de que la entrada sea erronea*/
    else {
        printf("\nEntrada erronea. Por favor ingrese una opcion valida\n");

        main_screen(hash_table);
    }
}

/*
 * Pide por input standard el usuario y la contrasena.
 *
 * @param username[]: arreglo donde se almacenara el username.
 * @param password[]: arreglo donde se almacenara la contrasena.
 */
void read_user_and_pass(char username[], char password[]) {
    printf("\nUSERNAME: ");
    scanf("%s", username);
    printf("PASSWORD: ");
    scanf("%s", password);
}
