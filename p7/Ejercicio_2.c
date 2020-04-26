/* Envío de señales definidas por el usuario entre dos procesos */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include "shmz.h"
#define SIGNAL_NO SIGUSR1 /* Renombre de una señal de usuario */
#define TIEMPO_LIMIT 10 /* Tiempo de temporización */
/* Variables globales */
static int i,hijo;
static int otro_pid;
/* Declaración de las funciones para tratamiento de señales */
void manejador(int sig);
void contador(int sig);
void terminar(int sig);
int cont, tiempo, semid;
/* Función principal */
int main(void)
{

    /*Esta variable es la que incrementaremos cada vez que se mande la señal "SIGUSR1"*/
    cont=0;

    printf("\nAhora mismo el contador vale %d",cont);
    printf("\nPara incrementarla, mandar señal SIGUSR1\n");


    /*Manejador para la señal SIGUSR1*/
    if(signal(SIGUSR1,manejador) == SIG_ERR)
    {
            perror("signal");
    }

    /*Manejador para la señal SIGALRM*/
    if(signal(SIGALRM,contador) == SIG_ERR)
    {
            perror("signal");
    }

    /*Manejador para la señal SIGUSR2 y terminar el proceso*/
    if(signal(SIGUSR2,terminar) == SIG_ERR)
    {
            perror("signal");
    }

           /*Mandamos una señal en un segundo*/
           alarm(1);

           while(1){
               sleep(1);
           }

}

void manejador(int sig){
    cont++;
    printf("Ahora el contador vale %d\n",cont);
}

void contador(int sig){
    tiempo++;
    alarm(1);
}

void terminar(int sig){
    printf("La variable tiempo vale %d",tiempo);
    semctl(semid,0,IPC_RMID,0);
    exit(EXIT_FAILURE);
}

/* Final función auxiliar */
