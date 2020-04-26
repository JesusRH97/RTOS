///Programa hijo
/* Programa hijo.c, cuyo ejecutable se lanza desde el proceso padre */
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
/* Función principal */
int main(int argc, char* argv[])
{
	int i = 0;
	int j = 0;
	fflush(stdout);
        i = atoi(argv[1]);
	while(j < i)
	{
                printf("Hola soy de nuevo el proceso hijo %d\n",j+1);
		j++;
                sleep(1);
	}
	exit(EXIT_SUCCESS);
	printf("\n");
}
/* Fin función principal */
