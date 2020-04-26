/* Creación de pipes (I/O) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* Función principal */
int main(void)
{
	int pfd[2];
	/* Array para almacenar los descriptores de fichero del pipe */
	int nread;
	char s[100];
	/* Buffer para lectura de los datos del pipe */
	/* int pipe(int filedes[2]): creación de un pipe, los descriptores de fichero de lectura y escritura
	son almacenados en filedes[0] y filedes[1] respectivamente */
	if(pipe(pfd) == -1)
		perror("pipe");
	/* Escritura de datos en el pipe */
	/* ssize_t write(int filedes, const void *buffer, size_t size): escribe la cantidad size de bytes del
	buffer en el fichero con descriptor fideles. La información almacenada en buffer puede no ser
	una cadena de caracteres */
	if(write(pfd[1],"Escribo en la tuberia",22) == -1)
		perror("write");
	/* Lectura de datos del pipe */
	/* ssize_t read(int fideles, void *buffer, size_t size): lee la cantidad size de bytes del fichero con
	descriptor fideles, almacenándolos en buffer. Devuelve la cantidad de bytes leídos */
	nread=read(pfd[0],s,sizeof(s));
	switch(nread)
	{
		case -1:
			perror("read");
			break;
		case 0:
			perror("EOF");
			break;
		default:
			printf("Leídos : %d bytes : %s \n",nread,s);
	}
	/* Cierre de los descriptores de fichero de escritura y lectura del pipe */
	/* int close(int filedes): cierra el descriptor de fichero. La función close devuelve un 0 en
	condiciones normales, o –1 en caso de fallo. */
	close(pfd[0]);
	close(pfd[1]);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */