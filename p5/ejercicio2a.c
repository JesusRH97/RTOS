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
	memo *zona;
	/* Creación de la zona de memoria compartida */
	if((shmid = shmget(CLAVE_SHM, sizeof(memo), IPC_CREAT|0666)) == -1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	/* Obtención del puntero a la estructura de datos compartida */
	zona = (memo *)shmat(shmid,0,0);




        //fflush(stdin);
        printf("Escribe una frase: ");
        scanf("%s",zona->s);





        switch (fork()) {

        case -1:
            perror("read");
            break;

        case 0:
            if(execlp("./ejercicio2b","ejercicio2b",NULL)==-1){
                perror("execlp");
                exit(EXIT_FAILURE);
            }
            break;
        }

        do{
            printf("Escribe una frase: ");
            scanf("%s",zona->s);
        }while(strcmp("adios",zona->s)!=0);


        sleep(1);
	/* Borrado de la zona de memoria compartida */
        //shmctl(shmid, IPC_RMID,0);
}
/* Fin función principal */
