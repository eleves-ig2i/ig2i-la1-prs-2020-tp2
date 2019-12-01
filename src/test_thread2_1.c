#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

/**
 * Nom : test_thread2_1.c
 * Auteur : Nathan SALEZ
 * Description : test de création de thread - passage de paramètre par thread.
 * On vérifie le passage de paramètre à l'aide de l'affichage du numéro du thread créé.
 * Date : 15/11/2019
 */

#define NB_THREADS 50000

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

void * do_something(void * arg)
{
    int * numThread = (int*) arg;
    if( numThread != NULL && *numThread%(NB_THREADS/10) == 0) // On souhaite afficher 10 fois le numéro du thread
    {
        fprintf(stdout,"thread secondaire - id du thread actuel = %d\n",*numThread);
    }
    pthread_exit(numThread); // destruction du thread
}

int main(int argc, char* argv[])
{
    void * response;

    for(int j=0; j < NB_THREADS;j++)
    {
        pthread_t pthread;
        CHECK(pthread_create(&pthread,NULL,do_something,&j),"Impossible de créer le thread."); // création du thread

        CHECK(pthread_join(pthread,&response),"Problème de communication avec le thread créé."); // attente de la fin du thread créé.

        int * status = (int *)(response);
        if(status != NULL && *status%(NB_THREADS/10) == 0) // On souhaite afficher 10 fois le numéro du thread
        {
            fprintf(stdout,"thread main - id du thread actuel = %d\n",*status);
        }

    }
    return EXIT_SUCCESS;
}