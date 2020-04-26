/* Envío de una señal a un proceso que se encuentra en estado de espera
de una señal de alarma de temporización */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
/* Prototipos */
void manejador(int sig);
/* Declaración de la función manejador */
/* Función principal */
int main(void)
{
        struct sigaction act, oact;

        /* Declaración de dos estructuras del tipo sigaction, dicha
        estructura contiene toda la información sobre el manejo de
        una señal particular, se compone de los siguientes campos:
        - sighandler_t sa_handler: es análogo al parámetro action de la función signal.
        - sigset_t sa_mask: especifica el conjunto de señales bloqueadas mientas
        funcione el manejador. (Utilizar las funciones sigaddset() y sigemptyset()).
        - int sa_flags: especifica una máscara de bits que afectan al comportamiento
        de la señal:
        - SA_RESTART: control de la señal durante operaciones de
        R/W.*/

        act.sa_handler = manejador; /* Especificamos el tratamiento a la señal */
        /* int sigemptyset(sigset_t *set): inicialización a cero del conjunto de señales
        bloqueadas */
        if(sigemptyset(&act.sa_mask) == -1)
	{
		perror("sigemtyset");
		exit(EXIT_FAILURE);
	}
	/* Inicialización de la máscara de bits a utilizar */
	act.sa_flags = 0;
	/* int sigaction(int signum, const struct sigaction *action, struct sigaction *old_action):
	el argumento action establece la nueva acción para la señal signum, en old_action se
	almacena el tratamiento previo, es decir cual fue el tratamiento aplicado antes de llevar
	a cabo action. Ambos parámetros pueden ser un puntero a un NULL */
	if(sigaction(SIGALRM, &act, &oact) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	/* unsigned int alarm(unsigned int seconds): lanza una temporización en segundos, la
	finalización se indica mediante un SIGALRM */
	alarm((unsigned int) 10);
	/* Bucle infinito */
	for(;;)
	{
	}
}
/* Fin función principal */
/* Definición de la función manejador, que permite abandonar el bucle infinito al
recibirse la señal de final de temporización */
void manejador(int sig)
{
	printf("Proceso terminado \n");
        //exit(EXIT_SUCCESS);
}
/* Final función auxiliar */
