/* Comunicación de procesos mediante pipes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/* Función principal */
int main(void)
{
	int pfd[2];
	int status;
	/* Creación del pipe */
	if(pipe(pfd) == -1)
		perror("pipe");
	/* Creación de un proceso hijo */
	switch(fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			/* Cierre en el proceso hijo del descriptor del STDIN */
			if(close(0) == -1)
				perror("close");
			/* int dup(int old): copia el descriptor old en el primer descriptor disponible */
			/* Asignamos el descriptor de lectura del pipe almacenado en pdf[0] al STDIN, y cerramos el
			descriptor de escritura en el proceso hijo */
			if(dup(pfd[0]) == -1 || close(pfd[1]) == -1)
				perror("close");
			/* Ejecutamos el comando cat del sistema operativo */
			if(execlp("cat","cat",NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
		default:
			/* Cierre en el proceso padre del descriptor de lectura */
			if(close(pfd[0])==-1)
			perror("close");
			/* El proceso padre escribe en el pipe */
			if(write(pfd[1],"salgo en pantalla\n",19) ==-1)
			perror("write");
			/* Cierre en el proceso padre del descriptor de escritura */
			if(close(pfd[1])==-1)
			perror("close");
	}/* El proceso padre espera la finalización del proceso hijo */
	wait(&status);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */