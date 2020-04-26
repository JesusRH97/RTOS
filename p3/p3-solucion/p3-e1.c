/* Comunicación de procesos mediante pipes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
/* Función principal */
int main(void)
{
	int pfd[2], pfd2[2], nread;
	char fdstr[10], fdstr2[10];
	int status;
	/* Creación del pipe */
	if(pipe(pfd) == -1 || pipe(pfd2) == -1)
		perror("pipe");
	/* Creación de un proceso hijo */
	switch(fork()){
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			/* Cierre de descriptor*/
			if(close(pfd[1]) == -1 || close(pfd2[0]) == -1)
				perror("close");
			
			/* int sprintf(char *buffer, const char *formato,...): su funcionamiento es
			idéntico a la función printf, salvo que la salida generada se pone en el array
			apuntado por buffer. El valor devuelto es igual al número de caracteres puesto
			en el array */
			sprintf(fdstr,"%d",pfd[0]);
			sprintf(fdstr2,"%d",pfd2[1]);

			/* int execlp(const char *filename, const char *argv[0],..): permite la ejecución
			del programa filename como un nuevo proceso imagen. La lista de argumentos
			es:
			const char *filename: contiene el nombre del programa
			ejecutable.
			const char argv[]: el primer elemento de array es el
			nombre de programa, y el último un puntero NULL. */

			if (execlp("./p3-e1b", "p3-e1b", fdstr, fdstr2, NULL) == -1) 
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
	}

	if(close(pfd[0]) == -1 || close(pfd2[1]) == -1)
		perror("close");
	/* El proceso padre escribe en el pipe */
	if(write(pfd[1],"Hola hijo",10) == -1)
		perror("write");
	printf("[Padre]Frase escrita\n");

	char s[100];
	switch(nread = read(pfd2[0],s,sizeof(s)))
	{
		case -1:
			perror("read");
			break;
		case 0:
			perror("EOF");
			break;
		default:
			printf("[Padre]Leídos : %d bytes : %s \n",nread,s);
	}
	/* El proceso padre espera la finalización del proceso hijo */
	wait(&status);
	/* Cierre de descriptor */
	if(close(pfd[1]) == -1 || close(pfd2[0]) ==- 1)
		perror("close");

	exit(EXIT_SUCCESS);
}
/* Fin función principal */