#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

/**
 * Nom : test_thread.c
 * Auteur : Nathan SALEZ
 * Description : test de création de threads
 * Date : 15/11/2019
 */

#define NB_THREADS 50000

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

void * do_nothing(void * arg)
{
    int i = 0;
    pthread_exit(NULL); // destruction du thread
}

int main(int argc, char* argv[])
{
    int pid, status;

    for(int j=0; j < NB_THREADS;j++)
    {
        pthread_t pthread;
        CHECK(pthread_create(&pthread,NULL,do_nothing,NULL),"Impossible de créer le thread."); // création du thread

        CHECK(pthread_join(pthread,NULL),"Problème de communication avec le thread créé."); // attente de la fin du thread créé.

    }
    return EXIT_SUCCESS;
}