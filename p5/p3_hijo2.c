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
	memo * zona_mem;
	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona_mem = (memo *)shmat(shmid,0,0);
        zona_mem->resultado=(zona_mem->resultado)+3;
	/* int shmctl(int shmid, int cmd, struct shmid_ds *buff): proporciona varios modos de
	control sobre la zona de memoria compartida shmid. Los modos son entre otros:
	IPC_RMID: borrado,
	SHM_LOCK: bloquea la zona de memoria.
	SHM_UNLOCK: desbloqueo.
	buff es un puntero a una estructura con campos para almacenar el usuario, grupo de
	usuarios, etc. */
	/* Borrado de la zona de memoria compartida */
        /*shmctl(shmid,IPC_RMID,0);
        exit(EXIT_SUCCESS);*/
}
/* Fin función principal */
