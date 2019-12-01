#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include <string.h>
#include <ctype.h>

/**
 * Nom : test_caractere4_2.c
 * Auteur : Nathan SALEZ
 * Description : programme permettant d'étudier l'utilisation de flag pour un mécanisme de protection.
 * Date : 18/11/2019
 */

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

#define MAX_LENGTH 20

/**
 * si le flag est à 1, alors un thread a le droit d'effectuer son action et doit remettre le flag à 0 à la fin de son action.
 * sinon, le thread courant doit atteindre sa mise à 0.
 */
char flag = 1;

/**
 * affiche, caractère par caractère, le contenu d’une chaine de caractères de
 * longueur 20 et ne contenant que des A.
 * Attend ​ entre chaque affichage de caractère en utilisant deux boucles
 * imbriquées suffisamment longues pour y passer du temps ( ne pas utiliser sleep)
 * @param arg
 * @return
 */
void * fonctionA(void * arg)
{
    struct timespec t1;t1.tv_sec = 0;t1.tv_nsec = 10000000;

    while(flag != 1)
        nanosleep(&t1,NULL);

    flag = 0;
    for(size_t index = 0; index < MAX_LENGTH; index++)
        fprintf(stdout,"A");

    flag = 1;
    pthread_exit(NULL);
}

/**
 * affiche, caractère par caractère, le contenu d’une chaine de caractères de
 * longueur 20 et ne contenant que des A.
 * Attend ​ entre chaque affichage de caractère en utilisant deux boucles
 * imbriquées suffisamment longues pour y passer du temps ( ne pas utiliser sleep)
 * @param arg
 * @return
 */
void * fonctionB(void * arg)
{
    struct timespec t1;t1.tv_sec = 0;t1.tv_nsec = 10000000;

    while(flag != 1)
        nanosleep(&t1,NULL);

    flag = 0;
    for(size_t index = 0; index < MAX_LENGTH; index++)
        fprintf(stdout,"B");

    flag = 1;
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{

    pthread_t thread1, thread2;

    CHECK(pthread_create(&thread1,NULL,fonctionA,NULL),"Impossible de créer le thread 1.");
    CHECK(pthread_create(&thread2,NULL,fonctionB,NULL),"Impossible de créer le thread 2.");

    CHECK(pthread_join(thread1,NULL),"Impossible de récupérer les infos du thread 1.");
    CHECK(pthread_join(thread2,NULL),"Impossible de récupérer les infos du thread 2.");

    fprintf(stdout,"\n");
    return EXIT_SUCCESS;
}