/* Este programa trabaja con un único contador y dos threads para modificarlo. Ambos
threads incrementan el contador y ponen su valor en pantalla precedido de la palabra "Padre"
o “Hilo” según corresponda.
compilar con la línea de comandos:
$ cc -O -pthread -o programa1 programa1.c */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Prototipo de la función que va a ejecutar el thread hijo */
void funcionThread(void* parametro);

/*
* Principal
* Lanza un thread para la función funcionThread.
* Después de comprobar el posible error, realiza un bucle
* incrementando y mostrando el contador.
*/
void main()
{
	/* Contador*/
	int contador = 0;
	/* Identificador del thread hilo */
	pthread_t idHilo;
	/* Contador para seguir el bucle */
	int i = 1;
	/* error devuelto por la función de creación del thread */
	int error;

	/* Creamos el thread.
	En idHilo nos devuelve un identificador para el nuevo thread,
	Pasamos atributos del nuevo thread NULL para que los coja por defecto. Pasamos la
	función que se ejecutará en el nuevo hilo*/
	error=pthread_create(&idHilo,NULL,(void*)funcionThread,(void*)&contador);
	/* Comprobamos el error al arrancar el thread */
	if (error != 0)
	{
		perror ("No puedo crear thread");
		exit (-1);
	}
	/* Bucle para incrementar el contador y mostrarlo en pantalla */
	while (i++<25)
	{
		contador++;
		printf ("Padre : %d\n",contador);
		usleep(1000);
	}
}

/* Función que se ejecuta en el thread hijo.*/
void funcionThread(void* parametro)
{
	int* contador_funcion = (int*)parametro;
	/* Bucle infinito para incrementar contador y mostrarlo en pantalla. */
	while (1)
	{
                (*contador_funcion)++;
                printf ("Hilo : %d\n",*contador_funcion);
		usleep(10);
	}
}
