/**
 * Implementacion de las pantallas de la aplicacion.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "timeline.h"
#include "screens.h"
#include "hash_table.h"
#include "user_list.h"

/* Pantalla principal del usuario. Se encarga de verificar si las 
 * opciones ingresadas son validas y de mostrar las demas pantallas.
 */
void screen1(user_node **hash_table) {
    char *input = malloc(8 * sizeof(char)); /* opciones de entrada */

    printf("\nDON’T MISS WHAT’S HAPPENING! LOGIN, SIGNUP OR LEAVE\n\n");
    fflush(stdin);
    fgets(input, 8, stdin); 

    clear_string(&input);

    if (!strcmp(input, "login")) {
        /* Login del usuario */
        screen2(hash_table);
        screen1(hash_table);
    }
    else if (!strcmp(input, "signup")) {
        /* Signup del usuario */
        screen4(hash_table);
        screen1(hash_table);
    }
    /* salida del programa*/
    else if (!strcmp(input, "leave")) {
        return;
    }
    else {
        printf("%s\n", input);
        printf("\nEntrada erronea. Por favor ingrese una opcion valida\n");
        screen1(hash_table);
    }
}

/* Segunda pantalla del usaurio. Se encarga de loguear un usuario y de mostrar
 * su timeline.
 */
void screen2(user_node **hash_table) {
    char *username = malloc(31 * sizeof(char)); /* username del usuario */
    char *password = malloc(16 * sizeof(char)); /* password del usuario */
    user *struct_user = NULL; /* Puntero al struct con los datos del user */

    read_user_and_pass(&username, &password);

    /* Verificar si el login es valido */
    struct_user = get_user(hash_table, username);
    if (!struct_user || struct_user->hash_password != hash_code(password)) {
        printf("\nEl usuario o la contrasena son incorrectos\n");
        return;
    }
    else {
        /* Mostrar timeline del usuario */
        show_timeline(struct_user->sig_list);
        screen3(hash_table, &struct_user, NULL); /* Mostrar pantalla 3 */
        return;
    }
}

/* Tercera pantalla del usuario. Ofrece las opciones de anadidura
 * de tweet, ir a un perfil, follow (si aplica) y de cerrar sesion.
 *
 * @param hash_table: Tabla de hash con los usuarios.
 * @param u: puntero a struct de usuario logueado.
 * @param to_user: Puntero a usuario al que [u] esta stalkeando.
 */
void screen3(user_node **hash_table, user **u, user *to_user) {
    user *struct_user = *u;
    char *input = malloc(8 * sizeof(char)); /* opciones de entrada */
    char *str_tw = malloc(283 * sizeof(char)); /* tweet del usuario */

    printf("\nWHATS HAPPENING?\n\n");
    fgets(input, 8, stdin); 

    clear_string(&input);

    /* Agregar tweet */
    if (!strcmp(input, "+")) {
        fgets(str_tw, 283, stdin); 
        clear_string(&str_tw);
        add_tweet(&struct_user, str_tw);

        printf("\nSu tweet fue anadido con exito\n");
        screen3(hash_table, u, NULL);
    }
    /* Ir a perfil de usuario */
    else if (!strcmp(input, "@")) {
        user *stalkear_user = NULL;
        char *username = malloc(31 * sizeof(char));
        fgets(username, 31, stdin);
        clear_string(&username);

        stalkear_user = get_user(hash_table, username); /* Obtener usuario a stalker */

        /* Verificar si el usuario existe */
        if (!stalkear_user) {
            printf("\n@%s no es un perfil de usuario existente", username);
            screen3(hash_table, u, NULL);
        }
        else {
            /* Mostrar tweet del usuario */
            printf("\nDescripcion: %s\n\n", stalkear_user->description);
            show_user_list(stalkear_user->sig_list);
            show_tweet_list(stalkear_user->tweet_list, stalkear_user->username);
            screen3(hash_table, u, stalkear_user);
        }
    }
    else if (to_user && !strcmp(input, "follow")) {

        if(!get_user_list(struct_user->sig_list, to_user->username)) {
            push_user_list(&struct_user->sig_list, to_user);
            printf("\nComenzo a seguir a @%s\n", to_user->username);
            screen3(hash_table, u, NULL);
        }
        else {
            printf("\nYa sigue al usuario @%s\n", to_user->username);
            screen3(hash_table, u, NULL);
        }
    }
    else if (!strcmp(input, "logout"))
        return;
    else {
        printf("\nEntrada erronea. Por favor ingrese una opcion valida\n");

        /* Verificar si se esta estalkeando a un usuaio */
        if (to_user)
            screen3(hash_table, u, to_user);
        else
            screen3(hash_table, u, NULL);
    }
}

/* Cuarta pantalla del usuario. Se encarga de registrar un usuario.
 */
void screen4(user_node **hash_table) {
    char *username = malloc(31 * sizeof(char)); /* username del usuario */
    char *password = malloc(16 * sizeof(char)); /* password del usuario */
    char *description = malloc(65 * sizeof(char)); /* password del usuario */

    read_user_and_pass(&username, &password);
    put_description(&description);
     
     /* Se agrega, en caso contrario se solicita otro username */
    if (!get_user(hash_table, username)) {
        insert_user_hash_table(&hash_table, new_user(username, hash_code(password), description));           
        printf("Registro exitoso.\n");
        return;
    }
    else {
        printf("\nEl usuario ya existe. Intente con otro usuario\n");
        return;
    }
}

/*
 * Anade un nuevo tweet al struct del usuario.
 *
 * @param u: Puntero al struct del usuario.
 * @param tw: tweet que el usuario quiere anadir.
 */
void add_tweet(user **u, char *str_tw) {
    user *struct_user = *u;
    
    push_tweet_list(&struct_user->tweet_list, new_tweet(str_tw, time(NULL))); 
    return;
}

/*
 * Pide por input standard el usuario y la contrasena.
 *
 * @param u: puntero a char donde se almacenara el username.
 * @param p: puntero a char donde se almacenara el contrasena.
 */
void read_user_and_pass(char **u, char **p) {
    char *username = *u;
    char *password = *p;

    printf("\nUSERNAME: ");
    fflush(stdin);
    fgets(username, 31, stdin); 
    clear_string(&username);

    printf("PASSWORD: ");
    fflush(stdin);
    fgets(password, 16, stdin); 
    clear_string(&password);
    printf("\n");

    return; 
}

void put_description(char **d) {
    char *description = *d;
    printf("DESCRIPTION: ");
    fflush(stdin);
    fgets(description, 65, stdin);
    clear_string(&description);
    printf("\n");
}

/* Remove trailing newline, if there. */
void clear_string(char **s) {
    char *input = *s;
    if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
        input[strlen(input) - 1] = '\0';
    return;
}
