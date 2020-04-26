/* Creación y empleo de semáforos en la sincronización de procesos,
este programa es el proceso2 lanzado desde el programa1 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include "shmz.h"

/* Función principal */
int main(void)
{
	int i=10;
	int semid;
	struct sembuf operacion;
	/* Variable empleada en el bucle while */
	/* Obtención del identificador que agrupa los semáforos */
	if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	/* Operaciones sobre los semáforos */
	operacion.sem_flg = SEM_UNDO;
	while(i)
	{
                operacion.sem_num = SEM_B; //SEM_A o SEM_B
                operacion.sem_op = -1; // +1 o -1
		semop(semid,&operacion,1);
		printf("Proceso B ------ %d\n",i--);
                operacion.sem_num = SEM_A; //SEM_A o SEM_B
                operacion.sem_op = 1; // +1 o -1
		semop(semid,&operacion,1);
	}
	/* Borrado del semáforo */
	semctl(semid,0,IPC_RMID,0);
}
/* Fin función principal */
