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
	int pfd[2], nread;
	char s[100];
	/* Obtención del descriptor de lectura del pipe */
	/* int atoi(const char *cad): convierte la cadena de caracteres que apunta cad a un valor int. La
	cadena debe contener un número válido de entero. */
	pfd[0]=atoi(argv[1]);
	pfd[1]=atoi(argv[2]);
	/* Lectura de la información contenida en el pipe. */
	sleep(1);
	switch(nread = read(pfd[0],s,sizeof(s)))
	{
		case -1:
			perror("read");
			break;
		case 0:
			perror("EOF");
			break;
		default:
			printf("[Hijo]Leídos : %d bytes : %s \n",nread,s);
	}
	sleep(1);
	if(write(pfd[1],"Hola padre", 11) == -1)
		perror("write");
	/* Cierre del descriptor de lectura en el proceso hijo */
	if(close(pfd[0]) ==- 1 || close(pfd[1]) ==- 1)
		perror("close");
	exit(EXIT_SUCCESS);
}
/* Fin función principal */