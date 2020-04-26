/* Tratamiento de señal SIGTERM */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/* Función principal */
int main(void)
{
	int pid;
        int status;
	/* Creación de un proceso hijo */
	if((pid = fork()) == 0)
	{
		/* Bucle infinito */
		while(1)
		{
			printf("Hola soy el hijo con pid %d\n",getpid());
			sleep(1);
		}
	}
	/* El proceso padre realiza una espera activa de 10 s */
        sleep(10);
	printf("Soy el proceso padre -> mando fin al proceso hijo %d\n", pid);
	/* int kill(pid_t pid, int signum): permite enviar la señal signum al proceso con identificador pid */
        kill(pid,SIGTERM);
        wait(&status);
	exit(EXIT_SUCCESS);
}

/* Fin función principal */
