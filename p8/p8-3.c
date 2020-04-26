/* Obtención de los identificadores y prioridad de un proceso, modificación de la prioridad de 
un proceso */ 
 
# include <sys/types.h> 
# include <sys/resource.h> 
# include <sys/time.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <stdio.h> 
 
/* Función principal */ 
int main(int argc, char *argv[]) 
{ 
	int pprio; 
	int prioridad; 
	 
	/* Obtención de la prioridad de un proceso */ 
	if((pprio=getpriority(PRIO_PROCESS,0)) == -1)
	{  
		perror("getpriority"); 
		exit(EXIT_FAILURE); 
	} 
	
	printf(" La prioridad del proceso %s es %d\n", argv[0], pprio); 
	 
	/* Modificación de la prioridad del proceso */ 
	printf("Introducir incremento de prioridad:\n"); 
	scanf("%d",&prioridad); 
	pprio+=prioridad; 
	 
	/* Comprobación del rango de prioridades */ 
	if(pprio > 19 || pprio < -20)
	{  
		printf("Excedido limite prioridad\n"); 
		exit(EXIT_FAILURE); 
	} 
	 
	/* int setpriority(int class, int id, int priority): permite modificar la prioridad (class) del proceso 
	con identificador id (0 significa proceso actual) al valor priority. */ 
	 
	/* Fijamos un nuevo valor de prioridad */ 
	setpriority(PRIO_PROCESS,0, pprio); 
	/* Obtención de la prioridad de un proceso */ 
	pprio=getpriority(PRIO_PROCESS, 0); 
	printf("Leemos nueva prioridad %d\n", pprio); 

	pause();
	
	exit(EXIT_SUCCESS); 
} 
/* Fin función principal */ 