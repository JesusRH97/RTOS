/* Crea una zona de memoria común y la borra */
/*EJERCICIO 1*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
# include <unistd.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
        int shmid;
        char numero[100];
	memo * zona_mem;
	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona_mem = (memo *)shmat(shmid,0,0);

        /*Pedimos el número por teclado*/
        printf("\nEscribe un numero: ");
        scanf("%s",numero);
        zona_mem->resultado=atoi(numero);

        /*Hacemos los procesos hijos*/
        /*Hijo 1*/
        switch(fork()){

        case -1:
            perror("read");
            break;

        case 0:
            if(execlp("./p3_hijo1","p3_hijo1",NULL)==-1){
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }

        /*Hijo 2*/
        switch(fork()){

        case -1:
            perror("read");
            break;

        case 0:
            if(execlp("./p3_hijo2","p3_hijo2",NULL)==-1){
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }

        /*Dejamos tiempo para realizar las operaciones haciendo un sleep(1)*/
        sleep(1);

        /*Leemos la variable de la zona de memoria*/
        printf("\nLa variable resulta ser %d",zona_mem->resultado);

	/* int shmctl(int shmid, int cmd, struct shmid_ds *buff): proporciona varios modos de
	control sobre la zona de memoria compartida shmid. Los modos son entre otros:
	IPC_RMID: borrado,
	SHM_LOCK: bloquea la zona de memoria.
	SHM_UNLOCK: desbloqueo.
	buff es un puntero a una estructura con campos para almacenar el usuario, grupo de
	usuarios, etc. */
	/* Borrado de la zona de memoria compartida */
        //shmctl(shmid,IPC_RMID,0);
        exit(EXIT_SUCCESS);
}
/* Fin función principal */
