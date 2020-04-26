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
	int i=10;
	int semid;
        int shmid;
	pid_t pid;
	struct sembuf operacion;
        memo* zona;
        int status;

        /*Zona de memoria compartida*/
        if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
        {
                perror("shmget");
                exit(EXIT_FAILURE);
        }

        /* Obtención del puntero a la estructura de datos compartida */
        zona = (memo *)shmat(shmid,0,0);

        /*Semáforo de procesos*/
	if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}

        operacion.sem_flg = SEM_UNDO;

        for(int i=10;i>=0;i--){
            /*Restringimos el acceso al semáforo que controla este semáforo*/
            operacion.sem_num = SEM_B;
            operacion.sem_op = -1;
            semop(semid,&operacion,1);
            /*Una vez que tenemos acceso, imprimimos la variable*/
            printf("La variable vale %d\n",(zona->tarea));
            /*Damos paso al smeáforo del otro proceso para que actúe*/
            operacion.sem_num = SEM_A;
            operacion.sem_op = 1;
            semop(semid,&operacion,1);
        }


}
/* Fin función principal */
