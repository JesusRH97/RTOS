#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

/*NOTA: "lock" equivale a en semáforos restar 1, y "unlock" a sumar 1.
 * Cuando se inicializan los mutex, se inicializan a 1*/

typedef struct
{
        /*Contador*/
        int contador;
        /*Semáforo 1*/
        pthread_mutex_t mutex_1;
        /*Semáforo 2*/
        pthread_mutex_t mutex_2;
} datos;

void contador(datos* f_datos)
{
        for(int i=10;i>=1;i--)
	{

                /*Función que permite obtener la fecha actual y guardarla en una estructura
		especial del tipo timeval*/
                /*Mutex_1 = 0*/
                pthread_mutex_lock(&(f_datos->mutex_1));
                f_datos->contador--;
                /*Mutex_2 = 1 => desbloqueado*/
                pthread_mutex_unlock(&(f_datos->mutex_2));



	}
}

void printer(datos* f_datos)
{

        for(int i=10;i>=1;i--)
	{

                /*Mutex_2 = -1 => bloqueado. Tenemos que esperar a que nos lo
                  desbloqueen desde l otra función*/
                pthread_mutex_lock(&(f_datos->mutex_2));
                printf("\n%d",f_datos->contador);
                /*Mutex_1 = 1 => desbloqueado*/
                pthread_mutex_unlock(&(f_datos->mutex_1));
}
}

void main ()
{
	pthread_t t,p;
	datos mis_datos;
        mis_datos.contador=11;
	/* Inicializa un semáforo para la exclusión mutua */
        /*Mutex_1 = 1*/
        pthread_mutex_init(&mis_datos.mutex_1, NULL);
        /*Mutex_2 = 1*/
        pthread_mutex_init(&mis_datos.mutex_2, NULL);
        /*Mutex_2 = 0*/
        pthread_mutex_lock(&(mis_datos.mutex_2));
        pthread_create(&t, NULL,(void*)contador,&mis_datos);
	pthread_create(&p, NULL,(void*)printer,&mis_datos);
	pthread_join(t, NULL);
	pthread_join(p, NULL);
}
