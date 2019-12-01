#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/**
 * Nom : test_mutex1.c
 * Auteur : Nathan SALEZ
 * Description : programme permettant d'étudier l'utilisation de mutex.
 * Date : 18/11/2019
 */

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

#define NB_THREADS 10

/**
 * initialisation du mutex d'accès à stdout
 */
pthread_mutex_t mutex_flag = PTHREAD_MUTEX_INITIALIZER;

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
    pthread_mutex_lock(&mutex_flag);

    int in_param = (int) arg;
    int out_param = 0;
    fprintf(stdout,"Thread %d - Début du calcul\n",in_param);
    for(int index = 0; index <= in_param*5;index++)
    {
        // pour vérifier que le calcul ne soit pas interrompu,
        // on affiche un message à chaque itération.
        //fprintf(stdout,"Thread %d - Calcul en cours ..\n",in_param);
        out_param += index;
    }
    fprintf(stdout,"Thread %d - Fin du calcul - out_param = %d\n",in_param, out_param);

    pthread_mutex_unlock(&mutex_flag);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{

    pthread_t tabThreads[NB_THREADS];

    for(size_t index = 0; index < NB_THREADS; index++)
    {
        CHECK(pthread_create(&(tabThreads[index]),NULL,calculer,(void *) index),"Impossible de créer un thread.");
    }
    for(size_t index = 0; index < NB_THREADS; index++)
    {
        CHECK(pthread_join(tabThreads[index],NULL),"Impossible de récupérer les infos d'un thread.")
        fprintf(stdout,"Fin du thread %ld\n",index);
    }

    return EXIT_SUCCESS;
}