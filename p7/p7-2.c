/* Envío de una señal desde la línea de comandos del sistema operativo a un proceso
que se encuentra en estado de espera de una señal */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
/* Prototipos */
void manejador(int sig);
/* Declaración de la función manejador */
/* Función principal */
int main(void)
{
	/* Instalación de un nuevo manejador para la señal SIGINT */
        if(signal(SIGINT,manejador) == SIG_ERR)
	{
		perror("signal");
    	exit(EXIT_FAILURE);
	}
	/* Bucle infinito */
	printf("Esperando a que el usuario termine la ejecución\n");
	while(1)
	{
		/* int pause(): deja el proceso suspendido en espera de la llegada de una señal */
		pause();
	}
}
/* Fin función principal */
/* Definición de la función manejador */
void manejador(int sig)
/* “sig” es el número identificador de la señal recibida */
{
	printf("Terminación de proceso %d a petición de usuario \n", getpid());
        exit(EXIT_SUCCESS);
}
/* Final función auxiliar */

/*Para ejecutar el programa es preciso:
-
-
utilizar el comando del S.O. ps –a para comprobar el pid asignado al
proceso,
enviar la señal al proceso desde la línea de comandos del sistema operativo
mediante el uso del comando kill:
- kill –número señal pid del proceso,
- ej. kill –9 228 (-9 = SIGKILL)*/
