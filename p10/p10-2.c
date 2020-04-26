/* Ejemplo de uso de la cancelación y espera de los hilos */
/*Desde la función principal se envía la cancelación al hilo y se espera la finalización de este.
Por otro lado, el hilo deshabilita su cancelación y realiza una espera para después habilitar de
nuevo su cancelación*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Prototipo de la función que va a ejecutar el thread hijo */
void funcionThread();

void main()
{
	/* Identificador del thread hilo */
	pthread_t idHilo;
	/* error devuelto por la función de creación del thread */
	int error;
	/* Creamos el thread*/
	error = pthread_create(&idHilo, NULL,(void*)funcionThread, NULL);
	/* Comprobamos el error al arrancar el thread */
	if (error != 0)
	{
		perror ("No puedo crear thread");
		exit (-1);
	}
        sleep(5);
	/* Enviamos la cancelación al hilo*/
	pthread_cancel(idHilo);
	printf("Enviada cancelación al Hilo\n");
	/*Espera hasta la finalización del hilo*/
	pthread_join(idHilo, NULL);
	printf("Hilo Finalizado\n");
	exit(1);
}
/* Funcion que se ejecuta en el thread.*/
void funcionThread()
{
	printf("Hilo iniciado\n");
	/*deshabilitación de la cancelación del hilo*/
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	sleep(10);
	/*habilitación de la cancelación del hilo*/
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}
