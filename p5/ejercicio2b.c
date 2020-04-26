/* Crea una zona de memoria común, escribe en ella y la borra */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "shmz.h" /* Fichero que contiene la información de la estructura de datos a
compartir */
/* Función principal */
int main(void)
{
	int shmid;
        char frase[100];
	memo *zona;
	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);

        strcpy(frase," ");

        while(strcmp("adios",frase)!=0){

        strcpy(frase,zona->s);

        if(strcmp(frase,zona->s)!=0)
        printf("\nLa frase ha cambiado. Ahora es: %s",zona->s);

}

}
/* Fin función principal */
