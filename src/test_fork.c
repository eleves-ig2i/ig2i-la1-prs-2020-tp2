#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

/**
 * Nom : test_fork.c
 * Auteur : Nathan SALEZ
 * Description : test de création de processus à l'aide de l'appel système fork()
 * Date : 15/11/2019
 */

#define NB_THREADS 50000

void do_nothing()
{
    int i = 0;
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    int pid, status;

    for(int j=0; j < NB_THREADS; j++)
    {
        switch( pid = fork())
        {
            case -1 :
                perror("fork()");
            exit(EXIT_FAILURE);

            case 0 :
                do_nothing();

            default:
                waitpid(pid,&status,0);
        }
    }
    return EXIT_SUCCESS;
}