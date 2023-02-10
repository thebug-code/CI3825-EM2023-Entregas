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
#include "tweet_list.h"

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
            printf("\nInvalid username or password\n");
            main_screen(hash_table);
        }
        else {
            /* Mostrar timeline del usuario */
            timeline_screen(struct_user, hash_table);
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
            printf("\nExisting user. Try another user\n");
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

/**
 * Muestra el timeline del usuario
 * 
 * @param hash_table: tabla de hash con los usuarios
 * @param struct_user: usurio al que se le mostrara el timeline
 */
void timeline_screen(user *struct_user, user_node **hash_table) {
    show_timeline(struct_user->sig_list);
    user_menu(struct_user, hash_table);
}

/**
 * Crea un tweet
 * 
 * @param hash_table: Usuario que crea el tweet
 */
void write_tweet(user *struct_user) {
    char* str = malloc(282);
    time_t tm;
    tweet* tweet;

    scanf("%s", str);

    tm = time(0);

    tweet = new_tweet(str, tm);
    push_tweet_list(&struct_user->tweet_list, tweet);
}

/**
 * Muestra los tweets de un usuario
 * 
 * @param hash_table: Usuario que muestra los tweets
 */
void show_tweets(user *struct_user) {
    tweet_node *tw_list = struct_user->tweet_list;

    while (tw_list != NULL) {
        printf("User @%s\n", struct_user->username);
        printf("Dijo a las %s: '%s'\n", ctime(&(tw_list->data->tm)), tw_list->data->str_tweet);
        printf("-------------------------------\n");
        tw_list = tw_list->next;
    }
    return;
}

/**
 * Recibe un comando del usuario, para escribir un tweet, para ir
 * al perfil de un usuario, para seguir a un usuario, para regresar
 * al timeline o para regregras al prompt inicial
 * 
 * @param hash_table: tabla de hash con los usuarios
 * @param struct_user: usurio al que se le mostrara el timeline
 * @param struct_follower: perfil del usuario visitado
 */
void follower_menu(user *struct_user, user *struct_follower, user_node **hash_table) {
    char opcion[7];
    char username[31];
    user *struct_follower_2 = NULL;

    printf("\nWHAT’S HAPPENING?\n\n");
    scanf("%s", opcion);

    /* se escribe un tweet*/
    if(!strcmp(opcion, "+")) {
        printf("\nWhat are you thinking?\n\n");
        write_tweet(struct_user);
        follower_menu(struct_user, struct_follower, hash_table);
    }

    /* se va a la cuenta de un usuario*/
    else if(!strcmp(opcion, "@")) {
        scanf("%s", username);

        if(!get_user(hash_table, username)) {
            printf("\nThis user does not exist\n");
            follower_menu(struct_user, struct_follower, hash_table);
        }
        else {
            struct_follower_2 = get_user(hash_table, username);
            show_tweets(struct_follower_2);
            follower_menu(struct_user, struct_follower_2, hash_table);
        }
    }
    /* se sigue al usuario actual*/
    else if(!strcmp(opcion, "follow")) {
        push_user_list(&struct_follower->sig_list, struct_user);
        printf("%s" ,struct_follower->sig_list->data->username);
    }
    /* se regresa al timeline*/
    else if (!strcmp(opcion, "timeline")) {
        timeline_screen(struct_user, hash_table);
    }
    /* se regresa al prompt inicial*/
    else if(!strcmp(opcion, "logout")) {
        main_screen(hash_table);
    }
    else {
        printf("\nWrong input. Please enter a valid option\n");
        follower_menu(struct_user, struct_follower_2, hash_table);
    }
}


/**
 * Recibe un comando del usuario, para escribir un tweet, para ir
 * al perfil de un usuario o para regregras al prompt inicial
 * 
 * @param hash_table: tabla de hash con los usuarios
 * @param struct_user: usurio al que se le mostrara el timeline
 */
void user_menu(user *struct_user, user_node **hash_table) {
    char opcion[7];
    char username[31];
    user *struct_follower = NULL;

    printf("\nWHAT’S HAPPENING?\n\n");
    scanf("%s", opcion);

    /* se escribe un tweet*/
    if(!strcmp(opcion, "+")) {
        printf("\nWhat are you thinking?\n\n");
        write_tweet(struct_user);
        timeline_screen(struct_user, hash_table);
    }
    /* se va a la cuenta de un usuario*/
    else if(!strcmp(opcion, "@")) {
        scanf("%s", username);

        if(!get_user(hash_table, username)) {
            printf("\nThis user does not exist\n");
            user_menu(struct_user, hash_table);
        }
        else {
            struct_follower = get_user(hash_table, username);
            show_tweets(struct_follower);
            follower_menu(struct_user, struct_follower, hash_table);
        }
    }
    /* se regresa al prompt inicial*/
    else if(!strcmp(opcion, "logout")) {
        main_screen(hash_table);
    }
    else {
        printf("\nWrong input. Please enter a valid option\n");
        user_menu(struct_user, hash_table);
    }
}