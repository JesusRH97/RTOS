/* Obtención del modo de funcionamiento del scheduler para el proceso en ejecución */ 
 
#include <sched.h> 
#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h> 
 
/* Prototipos */ 
void tipo_sche(int tipo); 
 
/* Función principal */ 
int main(void) 
{ 
	/*  Llamada  a  la  función  tipo_sche(),  recibe  como  parámetro  el  scheduler  empleado  por  el 
	proceso con identificador pid */ 
	/*  int  sched_getscheduler(pid_t  pid):  proporciona  el  tipo  de  scheduler  empleado  en  el  modo 
	de funcionamiento del proceso pid. Si pid es 0 la función proporciona el scheduler del proceso 
	desde el que se realiza la llamada */ 
	// struct sched_param sp = {
 //        .sched_priority = 10
 //    };
	// sched_setscheduler(getpid(), SCHED_RR, &sp);
	tipo_sche(sched_getscheduler((pid_t) 0)); 

	exit(EXIT_SUCCESS); 
} 
/* Fin función principal */ 

/* Función auxiliar */ 
void tipo_sche(int tipo) 
{ 
	switch(tipo)
	{ 
		case -1:  
			perror("sched_getscheduler"); 
			exit(EXIT_FAILURE);

		case SCHED_OTHER: 
			/* Default: scheduler por defecto que emplea el sistema operativo, se basa en un tick de ciclo 
			QUANTUM  que  junto  con  la  prioridad  del  proceso  establece  su  tiempo  de  ciclo.  Este  tick  de 
			tiempo puede ser alterado en tiempo de ejecución por el programa, junto con la prioridad del 
			proceso */ 
			printf("Este proceso está usando QUANTUM\n"); 
			break;

		case SCHED_RR: 
			/*  Round  Robin:  el  funcionamiento  es  similar  al  caso  anterior  salvo  que  el  tick  de  ciclo 
			QUANTUM no puede ser alterado en tiempo de ejecución por el programa */ 
			printf("Este proceso está usando ROUND ROBIN\n"); 
			break;

		case SCHED_FIFO: 
			/* FIFO: en este caso el tick de ciclo QUANTUM para un proceso es infinito, tratando de que 
			cada proceso tenga el tiempo suficiente para ejecutarse de forma completa o bien hasta que 
			quede bloqueado */ 
			printf("Este proceso está usando FIFO\n"); 
			break; 

		default: 
			printf("Este proceso está usando un algoritmo desconocido\n"); 
			break; 
	} 
} 
 /* Final función auxiliar */