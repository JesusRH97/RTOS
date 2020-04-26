/* Creación y empleo de semáforos en la sincronización de procesos */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shmz.h"

/* Función principal */
int main(void)
{
        int shmid;
        int semid;
        memo *zona;
        struct sembuf operacion;

        /*Creación de la zona de memoria compartida*/
        if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
        {
                perror("shmget");
                exit(EXIT_FAILURE);
        }
        /* Obtención del puntero a la estructura de datos compartida */
        zona = (memo *)shmat(shmid,0,0);
        zona->tarea=10;
        /*Creación de los semáforos*/
        if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
        {
                perror("semget");
                exit(EXIT_FAILURE);
        }
        /* Inicialización de los semáforos */
        semctl(semid,SEM_A,SETVAL,1);
        semctl(semid,SEM_B,SETVAL,0);
        operacion.sem_flg = SEM_UNDO;

        /*Creación de los procesos*/
        switch(fork()){
                case -1:
                        (void) perror("fork");
                        exit(EXIT_FAILURE);
                case 0:

                        if(execlp("./ejercicio2b","ejercicio2b",NULL) == -1)
                        {
                                (void) perror("execlp");
                                exit(EXIT_FAILURE);
                        }
        }

        for(int i=10;i>=0;i--){
            /*Restringimos el acceso al semáforo que controla este semáforo*/
            operacion.sem_num = SEM_A;
            operacion.sem_op = -1;
            semop(semid,&operacion,1);
            /*Una vez que tenemos acceso, derementamos la variable*/
            zona->tarea=i;
            sleep(1);
            /*Damos paso al smeáforo del otro proceso para que actúe*/
            operacion.sem_num = SEM_B;
            operacion.sem_op = 1;
            semop(semid,&operacion,1);
        }

        /* Borrado del semáforo */
        semctl(semid,0,IPC_RMID,0);
        /* Borrado de la zona de memoria compartida */
        shmctl(shmid, IPC_RMID,0);
        exit(EXIT_SUCCESS);
}
/* Fin función principal */
