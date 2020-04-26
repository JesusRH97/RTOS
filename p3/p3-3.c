/* Comunicación de procesos mediante pipes */
/* prog3.c que se ejecuta desde el programa anterior */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* Función principal */
int main(int argc, char* argv[])
/* Lista de argumentos de la función principal */
/* argc: número de argumentos */
/* argv: cadenas de caracteres con los argumentos */
{
        int descriptor_3, descriptor_6, nread, resultado, iteraciones;
        char s[100], multiplicacion[10],respuesta[10];
	/* Obtención del descriptor de lectura del pipe */
	/* int atoi(const char *cad): convierte la cadena de caracteres que apunta cad a un valor int. La
	cadena debe contener un número válido de entero. */
        descriptor_3=atoi(argv[1]);
        descriptor_6=atoi(argv[2]);
        iteraciones=atoi(argv[3]);
	/* Lectura de la información contenida en el pipe. */
        for(int i=1;i<=iteraciones;i++){
                     sleep(1);
        switch(nread = read(descriptor_3,multiplicacion,sizeof(multiplicacion)))
	{
		case -1:
			perror("read");
			break;
		case 0:
			perror("EOF");
			break;
		default:

                        resultado=atoi(multiplicacion);

                        resultado=2*resultado;
                        sprintf(respuesta,"%d",resultado);
                        if(write(descriptor_6, respuesta,sizeof(respuesta)) == -1)
                                perror("write");
            break;
        }
        }
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
