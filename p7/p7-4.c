/* Envío de señales definidas por el usuario entre dos procesos */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#define SIGNAL_NO SIGUSR1 /* Renombre de una señal de usuario */
#define TIEMPO_LIMIT 10 /* Tiempo de temporización */
/* Variables globales */
static int i,hijo;
static int otro_pid;
/* Declaración de las funciones para tratamiento de señales */
void manejador(int sig);
void contador(int sig);
/* Función principal */
int main(void)
{
	struct sigaction act;
	hijo=0;
	/* Inicialización de la variable hijo */
	/* Creación de un proceso hijo */
	if((otro_pid = fork()) == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	act.sa_handler = contador;
	/* Inicialización manejo de señal */
	/* Inicialización del conjunto de señales bloqueadas */
	if(sigemptyset(&act.sa_mask) == -1)
	{
		perror("sigemtyset");
		exit(EXIT_FAILURE);
	}
	/* Inicialización de la máscara de bits */
	act.sa_flags = 0;
	/* Activación del tratamiento asociado a la señal SIGUSR1 */
	if(sigaction(SIGNAL_NO,&act,(struct sigaction *)NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	/* Inicialización de un nuevo manejador de señal */
	act.sa_handler=manejador;
	/* Activación del tratamiento asociado a la señal SIGALRM */
	if(sigaction(SIGALRM,&act,(struct sigaction *)NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	/* Temporización */
	alarm(TIEMPO_LIMIT);
	/* Bloque de programa para el proceso hijo */
	if(!otro_pid)
	{
		hijo=1;
		otro_pid = getppid(); /* Obtención del identificador del proceso padre */
		printf("El PID del proceso padre es: %d \n", otro_pid);
		/* El proceso hijo manda al proceso padre la señal SIGUSR1 */
		if(kill(otro_pid,SIGNAL_NO) == -1)
		{
			perror("kill");
			exit(EXIT_FAILURE);
		}
	}
	/* Bucle infinito */
	for(;;)
	{
		/* Espera de una señal */
		pause();
	}
}
/* Fin función principal */
/* Definición de la función manejador */
void manejador(int sig)
{
/* Condición de entrada al proceso padre */
	if(!hijo) 
	{
		printf("Señales mandadas por segundo por el proceso hijo: %d\n", i/TIEMPO_LIMIT);
	}
		exit(EXIT_SUCCESS);
}
	/* Final función auxiliar */


/* Definición de la función contador */
void contador(int sig)
{
	/* Incremento de la variable i */
	i++;
	/* Mandamos al proceso con identificador otro_pid la señal SIGUSR1 */
	if(kill(otro_pid,SIGNAL_NO) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}
}

/* Final función auxiliar */