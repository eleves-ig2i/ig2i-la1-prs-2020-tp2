#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/**
 * Nom : test_mutex3.c
 * Auteur : Nathan SALEZ
 * Description : programme permettant d'étudier l'utilisation de mutex.
 * Un thread d'affichage est utilisé lorsqu'un thread a fini ses calculs.
 * Date : 18/11/2019
 */

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

#define NB_THREADS 10

/**
 * initialisation du mutex d'accès à stdout
 */
pthread_mutex_t mutex_flag_calcul = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t mutex_cond_stdout = PTHREAD_COND_INITIALIZER;

/**
 * Calcule la somme des entiers de 0 à 5*in_param
 * La fonction est "thread safe"
 * @param arg
 * @return
 */
void * calculer(void * arg)
{
    // avant de faire le calcul, on lock le mutex d'accès à stdout
    // pour cela on utilise la fonction pthread_mutex_lock
    CHECK(pthread_mutex_lock(&mutex_flag_calcul), "Impossible de locker le mutex.\n");

    int in_param = (int) arg;
    int out_param = 0;
    fprintf(stdout,"Thread %d - Début du calcul\n",in_param);
    for(int index = 0; index <= in_param*5;index++)
    {
        // pour vérifier que le calcul ne soit pas interrompu,
        // on affiche un message à chaque itération.
        fprintf(stdout,"Thread %d - Calcul en cours ..\n",in_param);
        out_param += index;
    }
    CHECK( pthread_cond_signal(&mutex_cond_stdout),"Impossible d'envoyer un signal au mutex de condition.\n");
    CHECK(pthread_mutex_unlock(&mutex_flag_calcul), "Impossible de débloquer le mutex stdout.\n");
    pthread_exit(NULL);
}

/**
 * Affiche un message quand un thread a terminé toutes ses itérations.
 * @param arg
 * @return
 */
void * afficher( void * arg)
{
    for(size_t index =0; index < NB_THREADS; index++) {
        CHECK(pthread_cond_wait(&mutex_cond_stdout, &mutex_flag_calcul), "Impossible d'attendre le mutex de condition");
        fprintf(stdout, "Calcul terminé.\n");
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{

    pthread_t tab_threads[NB_THREADS];

    pthread_t thread_affichage;

    CHECK( pthread_create(&thread_affichage,NULL,afficher,NULL),"Impossible de créer le thread d'affichage.\n");
    for(size_t index = 0; index < NB_THREADS; index++)
    {
        CHECK(pthread_create(&(tab_threads[index]), NULL, calculer, (void *) index), "Impossible de créer un thread.");
    }
    for(size_t index = 0; index < NB_THREADS; index++)
    {
        CHECK(pthread_join(tab_threads[index], NULL), "Impossible de récupérer les infos d'un thread.")
    }

    pthread_join(thread_affichage,NULL);

    return EXIT_SUCCESS;
}