/* Comunicación de procesos mediante pipes */
/* prog3.c que se ejecuta desde el programa anterior */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* Función principal */
int main(int argc, char *argv[])
/* Lista de argumentos de la función principal */
/* argc: número de argumentos */
/* argv: cadenas de caracteres con los argumentos */
{
	int fd, fd2, nread;
	/* Obtención del descriptor de lectura del pipe */
	/* int atoi(const char *cad): convierte la cadena de caracteres que apunta cad a un valor int. La
	cadena debe contener un número válido de entero. */
	fd=atoi(argv[1]);
	fd2=atoi(argv[2]);
	//printf("Lectura de descriptor: %d \n",fd);
	/* Lectura de la información contenida en el pipe. */

	int numero;
	char c_numero[10];

	while(1 == 1)
	{

		char s[100];

		switch(nread = read(fd,s,sizeof(s)))
		{
			case -1:
				perror("read");
				break;
			case 0:
				perror("EOF");
				break;
			default:
				numero = atoi(s);
				numero = numero * 2;
				sprintf(c_numero,"%d\n",numero);
		}
		sleep(1);
		if(write(fd2,c_numero,10) == -1)
			perror("write");
	}
	exit(EXIT_SUCCESS);
}
/* Fin función principal */