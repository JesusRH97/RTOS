#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct
{
        int sensor_1;
        int sensor_2;
        float media;
        pthread_mutex_t mutex;
} datos;

void sensor_1(datos* f_datos)
{
	while (1)
	{
		/*Función que permite obtener la fecha actual y guardarla en una estructura
		especial del tipo timeval*/
                pthread_mutex_lock(&(f_datos->mutex));
                f_datos->sensor_1=rand()%10;
                printf("\nEl sensor 1 vale: %d",f_datos->sensor_1);
                pthread_mutex_unlock(&(f_datos->mutex));
                sleep(1);
	}
}

void sensor_2(datos* f_datos)
{

	while(1)
	{           
                pthread_mutex_lock(&(f_datos->mutex));
                f_datos->sensor_2=rand()%10;
                printf("\nEl sensor 2 vale: %d",f_datos->sensor_2);
                pthread_mutex_unlock(&(f_datos->mutex));
                sleep(3);

}
}

void media(datos* f_datos){

        while(1){

                pthread_mutex_lock(&(f_datos->mutex));
                f_datos->media=((f_datos->sensor_1)+(f_datos->sensor_2))/2;
                printf("\nLa media de los dos sensores es: %f",f_datos->media);
                pthread_mutex_unlock(&(f_datos->mutex));
                sleep(1);

        }
}

void main ()
{
	pthread_t t,p;
	datos mis_datos;
        mis_datos.media=0.0;
	/* Inicializa un semáforo para la exclusión mutua */
	pthread_mutex_init(&mis_datos.mutex, NULL);
        pthread_create(&t, NULL,(void*)sensor_1,&mis_datos);
        pthread_create(&p, NULL,(void*)sensor_2,&mis_datos);
        pthread_create(&p, NULL,(void*)media,&mis_datos);
	pthread_join(t, NULL);
	pthread_join(p, NULL);
}
