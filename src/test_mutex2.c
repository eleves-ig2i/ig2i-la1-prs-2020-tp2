#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/**
 * Nom : test_mutex2.c
 * Auteur : Nathan SALEZ
 * Description : programme permettant d'étudier l'utilisation de mutex.
 * crée deux threads​ : ​ un qui incrémente une variable compteur par un nombre tiré au hasard entre 0 et 10,
 * et l'autre qui affiche un message lorsque la variable compteur dépasse 20.
 * Date : 18/11/2019
 */

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

/**
 * initialisation du mutex de condition sur le compteur
 */
pthread_cond_t mutex_condition_compteur = PTHREAD_COND_INITIALIZER;

pthread_mutex_t mutex_flag = PTHREAD_MUTEX_INITIALIZER;

/**
 * Retourne un nombre aléatoire compris dans l'intervalle [a,b[
 * @param a
 * @param b
 * @return le nombre aléatoire décrit ci-dessus, 0 si a égal ou supérieur à b.
 */
unsigned int generateRandomNumber(int min, int max) // cf openclassroom
{
    unsigned int randomNumber = rand()%(max-min) + min;
    return (min<max)*randomNumber;
}


/**
 * Traitement du thread 1
 * incrémente une variable compteur par un nombre tiré au hasard entre 0 et 10
 * @param arg
 * @return
 */
void * incrementerCompteur(void * arg)
{
    unsigned int compteur = generateRandomNumber(0,10+1);
    while( compteur <= 20) {
        fprintf(stdout,"Thread 1 - Compteur = %d\n",compteur);
        compteur++;
    }
    pthread_cond_signal(&mutex_condition_compteur);
    pthread_exit(NULL);
}


/**
 * Traitement du thread 2
 * autre qui affiche un message lorsque la variable compteur dépasse 20.
 * @param arg
 * @return
 */
void * afficherMessage(void * arg)
{
    pthread_mutex_lock(&mutex_flag);
    CHECK( pthread_cond_wait(&mutex_condition_compteur,&mutex_flag),"Problème d'attente pour la condition associée au mutex.\n");
    fprintf(stdout,"Thread 2 - Temps écoulé.\n");
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    pthread_t thread1,thread2;

    CHECK( pthread_create(&thread1,NULL,incrementerCompteur,NULL),"Impossible de créer le thread d'incrémentation de compteur.\n");
    CHECK( pthread_create(&thread2,NULL,afficherMessage,NULL),"Impossible de créer le thread d'affichage de message.\n");

    CHECK( pthread_join(thread1,NULL),"Impossible d'attendre le thread1.\n");
    CHECK( pthread_join(thread2,NULL),"Impossible d'attendre le thread1.\n");

    return EXIT_SUCCESS;
}