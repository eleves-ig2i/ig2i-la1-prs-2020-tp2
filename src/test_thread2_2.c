#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

/**
 * Nom : test_thread2_2.c
 * Auteur : Nathan SALEZ
 * Description : test de création de thread - Lancement de n threads parallèles ;
 * Chaque thread affiche son numéro toutes les 100 ms et incrémente un compteur.
 * n est défini par un argument passé en ligne de commande.
 * Date : 15/11/2019
 */

// TODO : ne marche pas

#define CHECK(sts,msg) if ((sts) != 0) {perror(msg);exit(-1);}

int compteurGlobal = 0;


void * routine(void * arg)
{
    struct timespec t1;
    t1.tv_sec = 0;
    t1.tv_nsec = 10000000;
    int id_thread = (int) arg;
    // /!\ ne pas récupérer l'adresse de arg mais sa valeur
    // sinon, les prochaines modifications affectant id_thread seront sauvegardées dans le thread courant
    while(1)
    {
        ++compteurGlobal;
        fprintf(stdout,"Thread %d - compteur global = %d\n",id_thread,compteurGlobal);
        nanosleep(&t1,NULL);
    }
    pthread_exit(NULL); // destruction du thread
}

int main(int argc, char* argv[])
{
#ifdef __DEBUG
    for(int i =0; i < argc; i++)
    {
        fprintf(stdout,"Debug - argv[%d] = '%s'\n",i,argv[i]);
    }
#endif
    int nb_threads = 0;
    if( argc > 1)
        nb_threads = atoi(argv[1]);
    else
        exit(EXIT_FAILURE);

#ifdef __DEBUG
    fprintf(stdout, "Debug - Nombre de threads = %d\n", nb_threads);
#endif

    pthread_t thread;
    for(int id_thread = 1; id_thread <= nb_threads; id_thread++)
    {
        CHECK(pthread_create(&thread, NULL, routine, (void *) id_thread),"Problème de création de thread.");
    }

    pthread_join(thread,NULL);

    return EXIT_SUCCESS;
}