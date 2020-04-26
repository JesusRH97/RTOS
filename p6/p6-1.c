/* Creación y empleo de semáforos en la sincronización de procesos */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include "shmz.h"

/* Función principal */
int main(void)
{
	int i=10;
	int semid;
	pid_t pid;
	struct sembuf operacion;
	int status;
	/* Variable empleada en el bucle while */
	/* int semget(int key, int nsems, int flag): proporciona el identificador para el conjunto
	de semáforos nsems asociados a la llave key. Si el conjunto de semáforos ya existe
	proporciona su identificador y en caso contrario los crea con los permisos indicados en
	flag */
	if((semid = semget(LLAVE,2,IPC_CREAT|0600)) == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	/* int semctl(int semid, int semnum, int cmd, union semun arg): permite la realización de
	distintas operaciones de control sobre el conjunto de semáforos agrupados en semid.
	La variable semnum establece el semáforo seleccionado, mientras que cmd indica la
        operación a efectuar.
	La union arg presenta distintos campos donde se puede almacenar el valor de los
	semáforos, estados de los procesos, etc.
	*/
	/* Inicialización de los semáforos */
        semctl(semid,SEM_A,SETVAL,0);
        semctl(semid,SEM_B,SETVAL,1);
	/* Lectura del valor actual de los semáforos */
	printf("Valor semáforo A: %d\n", semctl(semid,SEM_A,GETVAL,0));
	printf("Valor semáforo B: %d\n", semctl(semid,SEM_B,GETVAL,0));
	/* Creación de un proceso hijo */


	switch(pid=fork())
	{
		case (pid_t) -1:
			(void) perror("fork");
			exit(EXIT_FAILURE);
                case (pid_t) 0:
			if(execlp("./p6-2","p6-2",NULL) == -1)
			{
				(void) perror("execlp");
				exit(EXIT_FAILURE);
		}
	}
	/* int semop(int semid, struct sembuf *sops, unsigned nsops): permite realizar
	operaciones sobre los semáforos asociados al identificador semid.
	Campos de la estructura sembuf:
	struct sembuf{
		short sem_num; // Semáforo sobre el que actuar
		short sem_op; // Operación a realizar: incremento, decremento 
		short sem_flg; // Las posibles opciones son: IPC_NOWAIT y SEM_UNDO 
	};
	El número de estructuras de operaciones asociadas a los semáforos es dado por nsops */
	/* Operaciones sobre los semáforos */
	operacion.sem_flg = SEM_UNDO;
	/* No activamos ninguna opcion */
	while(i)
	{
                operacion.sem_num = SEM_A; //SEM_A o SEM_B
                operacion.sem_op = -1; // +1 o -1
                semop(semid,&operacion,1);
		printf("Proceso A ------ %d\n",i--);
                operacion.sem_num = SEM_B; //SEM_A o SEM_B
                operacion.sem_op = 1; // +1 o -1
		semop(semid,&operacion,1);
	}
	/* Espera del proceso padre a la finalización del hijo */
	wait(&status);
	/* Borrado del semáforo */
        //semctl(semid,0,IPC_RMID,0);
}
/* Fin función principal */
