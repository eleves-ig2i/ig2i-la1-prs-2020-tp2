#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include <string.h>
#include <ctype.h>

/**
 * Nom : test_thread3_1.c
 * Auteur : Nathan SALEZ
 * Description :  deux threads affichant caractère par caractère le contenu d’une phrase donnée ; l’un affiche les
 * caractères en majuscules, l’autre en minuscules.
 * Date : 18/11/2019
 */

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

#define MAX_LENGTH 200

typedef enum
{
    LOWER_CASE,
    UPPER_CASE
} case_string_t;

/**
 * On définit le type du message à envoyer aux threads,
 * avec une chaine de caractères,
 * la casse pour l'affichage,
 * et l'id du message (qui sera l'id du thread)
 */
typedef struct
{
    char chaine[MAX_LENGTH];
    case_string_t casse;
    int id_message;
} message_t;

void * printString(void * arg)
{
    message_t * message = (message_t *) arg;

    for(size_t index =0; index < strlen(message->chaine); index++)
    {
        if( message->casse == LOWER_CASE)
        {
            fprintf(stdout,"%c", tolower(message->chaine[index]));
        } else if( message->casse == UPPER_CASE)
        {
            fprintf(stdout,"%c", toupper(message->chaine[index]));
        }
    }

    pthread_exit(&(message->id_message));
}

int main(int argc, char* argv[])
{
    char * phrase = "Bonjour ceci est le message à reproduire";
    message_t message1,message2;
    pthread_t thread1,thread2;
    int * response1, *response2;

    message1.id_message=1;
    message1.casse=LOWER_CASE;
    strcpy(message1.chaine,phrase);

    message2.id_message=2;
    message2.casse=UPPER_CASE;
    strcpy(message2.chaine,phrase);

    pthread_create(&thread1,NULL,printString,&message1);
    pthread_create(&thread2,NULL,printString,&message2);

    pthread_join(thread1,&response1);
    pthread_join(thread2,&response2);


    fprintf(stdout,"\nThread %d terminé\n",*response1);
    fprintf(stdout,"Thread %d terminé\n",*response2);


    return EXIT_SUCCESS;
}