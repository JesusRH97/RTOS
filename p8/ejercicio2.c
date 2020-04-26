/* Obtención de los identificadores y prioridad de un proceso */ 
 
#include <sys/types.h> 
#include <sys/resource.h> 
#include <sys/time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <signal.h>
int pid_hijo;
/* Función principal */ 
int main(int argc, char *argv[]) 
{

    printf("Va a ejecutarse el programa %s con prioridad %s",argv[1],argv[2]);
    switch(pid_hijo=fork()){
        case 0:

            if (execve(argv[1], NULL,0) == -1)
                {
                       perror("execve");
                       exit(EXIT_FAILURE);
                }
    default:
        setpriority(PRIO_PROCESS,pid_hijo,(int) argv[2]);
        break;
    }
wait(1000);
exit(EXIT_SUCCESS);
} 


/* Fin función principal */ 
