#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct
{
	struct timeval tv;
	pthread_mutex_t mutex;
} datos;

void timer(datos* f_datos)
{
	while (1)
	{
		/*Función que permite obtener la fecha actual y guardarla en una estructura
		especial del tipo timeval*/
		pthread_mutex_unlock(&(f_datos->mutex));
		gettimeofday(&(f_datos->tv), NULL);
		sleep(1);
	}
}

void printer(datos* f_datos)
{
	struct timeval tv2;
	long sec,usec;
	while(1)
	{
		pthread_mutex_lock(&(f_datos->mutex));
		gettimeofday(&tv2, NULL);
		/* Calculo la diferencia en segundos y microsegundos */
		sec=f_datos->tv.tv_sec-tv2.tv_sec;
		usec=labs(f_datos->tv.tv_usec-tv2.tv_usec);

		if (f_datos->tv.tv_sec > tv2.tv_sec)
		{
			sec -= 1;	
			usec = 1000000-usec;
		}
		if (f_datos->tv.tv_sec < tv2.tv_sec)
		{
			sec += 1;	
			usec = 1000000-usec;
		}

		printf("Tiempo actual: %8ld.%06ld. Diferencia:%8ld.%06ld\n",f_datos->tv.tv_sec,f_datos->tv.tv_usec,sec,usec);
	}
}

void main ()
{
	pthread_t t,p;
	datos mis_datos;
	/* Inicializa un semáforo para la exclusión mutua */
	pthread_mutex_init(&mis_datos.mutex, NULL);
	pthread_mutex_lock(&(mis_datos.mutex));
	pthread_create(&t, NULL,(void*)timer,&mis_datos);
	pthread_create(&p, NULL,(void*)printer,&mis_datos);
	pthread_join(t, NULL);
	pthread_join(p, NULL);
}
