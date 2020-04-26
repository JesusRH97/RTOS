/* Obtención de los identificadores y prioridad de un proceso */ 
 
#include <sys/types.h> 
#include <sys/resource.h> 
#include <sys/time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <signal.h>
int cont14=0;
int cont15=0;
int cont16=0;
int manejador(int sig);
/* Función principal */ 
int main(int argc, char *argv[]) 
{


    /*Procesos infinitos*/
        switch(fork()){
            case 0:

                for(;;);

            default:
                break;

        }

        switch(fork()){
            case 0:
                for(;;);

            default:
                break;

        }

        switch(fork()){
            case 0:
               for(;;);

            default:
                break;

        }

        if(signal(SIGINT,manejador) == SIG_ERR)
                          {
                                  perror("signal");
                                  exit(EXIT_FAILURE);
                          }

        /*Procesos con prioridad*/
        /*Prioridad 15*/
        switch(fork()){
            case 0:
            /* Fijamos un nuevo valor de prioridad */
            setpriority(PRIO_PROCESS,0, 15);
            while(1){
            for(int i=0;i<=10000000;i++)
            {}
                cont15++;
            }

            default:
                break;

        }
        /*Prioridad 14*/
        switch(fork()){
            case 0:
            /* Fijamos un nuevo valor de prioridad */

            setpriority(PRIO_PROCESS,0, 14);
            while(1){
            for(int i=0;i<=10000000;i++){
            }

                cont14++;
            }
            default:
                break;

        }
        /*Prioridad 16 */
        /* Fijamos un nuevo valor de prioridad */
        setpriority(PRIO_PROCESS,0, 16);
        while(1){
        for(int i=0;i<=10000000;i++)
        {}
            cont16++;
        }

} 

int manejador(int sig){

    switch(getpriority(PRIO_PROCESS,0)){
    case 14:
        printf("Número ciclos hijo con prioridad 14 vale: %d\n",cont14);
        break;
    case 15:
        printf("Número ciclos hijo con prioridad 15 vale: %d\n",cont15);
        break;
    case 16:
        printf("Número ciclos hijo con prioridad 16 vale: %d\n",cont16);
        break;
    }
    exit(EXIT_SUCCESS);
}

/* Fin función principal */ 
