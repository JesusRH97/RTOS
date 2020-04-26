/* Obtención de los identificadores y prioridad de un proceso */ 
 
#include <sys/types.h> 
#include <sys/resource.h> 
#include <sys/time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
 
/* Función principal */ 
int main(int argc, char *argv[]) 
{ 
	int pprio; 
	 
	/* int getpriority(int class, int id): permite leer la prioridad (class) del proceso con identificador 
	id (0 significa proceso actual). La variable class puede tomar los siguientes valores: 
	PRIO_PROCESS: prioridad de un proceso. 
	PRIO_PGRP: prioridad de un grupo de procesos. 
	El  rango  de  prioridades  depende  el  sistema  operativo,  pero  en  la  mayoría  de  los  casos  varía 
	entre –20 y 20, en otros oscila entre 0 y 255 */ 
	 
	/* Obtención de la prioridad de un proceso */ 
	if((pprio=getpriority(PRIO_PROCESS,0)) == -1)
	{  
		perror("getpriority"); 
		exit(EXIT_FAILURE); 
	} 
	 
	printf("La prioridad del proceso %s es %d\n", argv[0], pprio); 
	 
	exit(EXIT_SUCCESS); 
} 
/* Fin función principal */ 