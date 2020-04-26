#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
    int semid;
    pid_t pid;
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
    semctl(semid,SEM_B,SETVAL,0);

	int shmid;
	memo *zona;
        //pid_t pid;
	char *nombre="p5-5";
	char *nombre2="p5-5b";
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
	zona->tarea = 0;
	/* Creación de un proceso hijo */
	switch(pid=fork())
	{
		case (pid_t) -1:
			(void) perror("fork");
			exit(EXIT_FAILURE);
		case (pid_t) 0:
			/* Ejecutamos el proceso2 */
			av[0]=nombre;
			av[1]=(char *)0; /* Puntero a un null */
			if(execve(nombre,av,0) == -1)
			{
				(void) perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	switch(pid=fork())
	{
		case (pid_t) -1:
			(void) perror("fork");
			exit(EXIT_FAILURE);
		case (pid_t) 0:
			/* Ejecutamos el proceso2 */
			av[0]=nombre2;
			av[1]=(char *)0; /* Puntero a un null */
			if(execve(nombre2,av,0) == -1)
			{
				(void) perror("execlp");
				exit(EXIT_FAILURE);
			}
	}

        do{
	printf("Escribe un numero: ");
	fflush(stdin);
	scanf("%d",&zona->tarea);

        if(zona->tarea!=0)
        semctl(semid,SEM_B,SETVAL,1);

	sleep(1);
	printf("El resultado es: %d\n", zona->tarea);
        }while(zona->tarea!=0);

	wait(NULL);
	/* Borrado de la zona de memoria compartida */
	shmctl(shmid, IPC_RMID,0);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
