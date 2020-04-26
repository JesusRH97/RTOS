/* Obtención de los identificadores de un proceso */ 
 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
 
/* Función principal */ 
int main(int argc, char *argv[]) 
{ 
	/* pid_t getpid(void): proporciona el identificador ID del proceso actual */
	/* pid_t getppid(void): proporciona el identificador ID del proceso padre del proceso actual */

	if(fork() == 0)
	{
		printf("[Hijo] El ID del proceso %s es %d\n", argv[0], (int) getpid());
		printf("[Hijo] El ID del proceso padre %s es %d\n", argv[0], (int) getppid()); 
	}
	else
	{
		printf("[Padre] El ID del proceso %s es %d\n", argv[0], (int) getpid());
		printf("[Padre] El ID del proceso padre %s es %d\n", argv[0], (int) getppid()); 
	}
pause();
        //exit(EXIT_SUCCESS);
} 
/* Fin función principal */ 
 
