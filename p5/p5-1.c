/* Creación de una zona de memoria común */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
	int shmid;
	memo *zona_mem;
	/* int shmget(int key, int size, int flag): proporciona el identificador de segmento de la
	zona de memoria compartida asociado a key. Si la zona de memoria compartida ya
	existe devuelve su identificador, en caso contrario la crea aplicando la información
	contenida en flag (máscara asociada a los permisos de usuario, grupo,...) */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* char *shmat(int shmid, char *shmaddr, int flag): proporciona un puntero a la
	estructura de datos de la zona de memoria compartida. El primer parámetro es el
	identificador de segmento obtenido a través de shmget(), el segundo se refiere a la
	dirección de mapeo ( 0 dirección seleccionada por el S.0 ), mientras que el tercer
	parámetro es un flag que indica modos de funcionamiento:
	SHM_RND: S.O. trata de acercarse lo más posible a shmaddr.
	SHM_RDONLY: solo lectura.
	*/
	zona_mem = (memo *) shmat(shmid,0,0);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
/* NOTA: utilizar el comando ipcs del S.O para comprobar su existencia */