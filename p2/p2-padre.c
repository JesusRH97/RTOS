///Programa padre
/* Creación, terminación y control de procesos hijo a partir de un proceso padre */
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
char *nombre = "hijo";
/* Función principal */
int main(int argc, char* argv[])
{
	pid_t pid;
        char *av[3];
        int status;
	/* Creación de un proceso hijo */
	switch(pid = fork())
	{
		case (pid_t) -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case (pid_t) 0:
			/* int execve(const char *filename, char *const argv[], char *const envp[]): 
			Permite la ejecución del programa nombre como un nuevo proceso
			imagen. La lista de argumentos es:
			 const char *filename: contiene el nombre del programa ejecutable.
			 char *const argv[]: el primer elemento de array es el nombre de programa, y el
			último un puntero NULL.
			 char *const env[]: permite declarar el posible entorno de funcionamiento del
			programa */
			av[0]=nombre;
                        av[1]=argv[1];
                        av[2]=NULL;
                        if(execve(nombre,av,NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
	}
	printf("Soy el proceso padre\n");
	/* Espera del proceso padre a la terminación del proceso hijo */
	wait(&status);
	printf("Fin del proceso hijo\n");
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
