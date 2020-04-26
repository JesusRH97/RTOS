#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
    int semid;
    struct sembuf operacion;
    /* Obtención del identificador que agrupa los semáforos */
    if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
    {
            perror("semget");
            exit(EXIT_FAILURE);
    }
    /* Operaciones sobre los semáforos */
    operacion.sem_flg = SEM_UNDO;

	int shmid;
	memo *zona;
	pid_t pid;
	char *nombre="p5-5";
	char *av[2];
	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);
	/* Escribimos en la zona de memoria común */

        do{

            operacion.sem_num = SEM_B; //SEM_A o SEM_B
            operacion.sem_op = -1; // +1 o -1
            semop(semid,&operacion,1);

            printf("suma\n");
            zona->tarea += 2;

            operacion.sem_num = SEM_A; //SEM_A o SEM_B
            operacion.sem_op = 1; // +1 o -1
            semop(semid,&operacion,1);


        }while(zona->tarea != 0);

        /* Borrado del semáforo */
        semctl(semid,0,IPC_RMID,0);
	/* Borrado de la zona de memoria compartida */
        shmctl(shmid, IPC_RMID,0);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
