#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
	int shmid;
	memo *zona;
	int semid;
	struct sembuf operacion;
	pid_t pid;
	char *nombre="p5-5";
	char *av[2];

	if((semid = semget(LLAVE,3,IPC_CREAT|0600)) == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}

	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);
	/* Escribimos en la zona de memoria común */

	while(1)
	{
		operacion.sem_flg = SEM_UNDO;
		operacion.sem_num = SEM_C; 
		operacion.sem_op = -1;
		semop(semid,&operacion,1);

		printf("multiplica\n");
		zona->tarea *= 3;

		operacion.sem_num = SEM_A; 
		operacion.sem_op = 1;
		semop(semid,&operacion,1);
	}

	/* Borrado de la zona de memoria compartida */
	//shmctl(shmid, IPC_RMID,0);
        exit(EXIT_SUCCESS);
}
/* Fin función principal */
