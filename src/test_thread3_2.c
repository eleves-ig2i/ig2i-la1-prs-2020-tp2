#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include <string.h>
#include <ctype.h>

/**
 * Nom : test_thread3_2.c
 * Auteur : Nathan SALEZ
 * Description :  deux threads affichant caractère par caractère le contenu d’une phrase donnée ; l’un affiche les
 * caractères en majuscules, l’autre en minuscules;
 * avec une pause aléatoire en ds (10^-1 secondes) comprise entre 0 et 1 seconde pour le 1er thread
 * et une pause aléatoire en ds (10^-1 secondes) comprise entre 0 et 2 secondes pour le 2e thread
 *
 * Date : 18/11/2019
 */

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

#define MAX_LENGTH 200

#define MINIMAL_TIMESTAMP_NS 10000000

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

/**
 * Retourne un nombre aléatoire compris dans l'intervalle [a,b[
 * @param a
 * @param b
 * @return le nombre aléatoire décrit ci-dessus, 0 si a égal ou supérieur à b.
 */
long generateRandomNumber(int min, int max) // cf openclassroom
{
    long randomNumber = rand()%(max-min) + max;
    return (min<max)*randomNumber;
}

/**
 * Callback des 2 threads.
 * @param arg
 * @return
 */
void * printString(void * arg)
{
    message_t * message = (message_t *) arg;

    struct timespec t1;
    t1.tv_sec = 0;

    for(size_t index =0; index < strlen(message->chaine); index++)
    {
        if( message->casse == LOWER_CASE) {
            fprintf(stdout, "%c", tolower(message->chaine[index]));
            t1.tv_nsec = MINIMAL_TIMESTAMP_NS*generateRandomNumber(0,11); // durée comprise entre 0 et 10 ds

        }
        else if( message->casse == UPPER_CASE) {
            fprintf(stdout, "%c", toupper(message->chaine[index]));
            t1.tv_nsec = MINIMAL_TIMESTAMP_NS*generateRandomNumber(0,21); // durée comprise entre 0 et 20 ds
        }

        CHECK(nanosleep(&t1,NULL),"Impossible d'utiliser nanosleep.");
    }

    pthread_exit(&(message->id_message));
}

int main(int argc, char* argv[])
{
    srand(time(NULL)); // initialisation du random
    char * phrase = "Bonjour ceci est le message a reproduire";
    message_t message1,message2;
    pthread_t thread1,thread2;
    int * response1, *response2;

    message1.id_message=1;
    message1.casse=LOWER_CASE;
    strcpy(message1.chaine,phrase);

    message2.id_message=2;
    message2.casse=UPPER_CASE;
    strcpy(message2.chaine,phrase);

    CHECK(pthread_create(&thread1,NULL,printString,&message1),"Impossible de créer le thread 1.");
    CHECK(pthread_create(&thread2,NULL,printString,&message2),"Impossible de créer le thread 2.");

    CHECK(pthread_join(thread1,&response1),"Impossible de récupérer les infos du thread 1.");
    CHECK(pthread_join(thread2,&response2),"Impossible de récupérer les infos du thread 2.");


    fprintf(stdout,"\nThread %d terminé\n",*response1);
    fprintf(stdout,"Thread %d terminé\n",*response2);


    return EXIT_SUCCESS;
}