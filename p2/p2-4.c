/* Creación, terminación y control de procesos hijo a partir de un proceso padre */
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
/* Prototipos */
int hijo1(void);
int hijo2(void);
void padre(void);
/* Función principal */
int main (void)
{
        pid_t pid_hijo1, pid_hijo2;
	int status;
	/* Creación de un proceso hijo */
        switch(pid_hijo1 = fork())
	{
                case -1:
			perror("fork");
			exit(EXIT_FAILURE);
                case 0:
                        exit(hijo1());
			break;
		default:

                        switch(pid_hijo2 = fork()){

                        case -1:
                            perror("fork");
                            exit(EXIT_FAILURE);
                        case 0:
                            exit(hijo2());
                            break;
                        default:
			/* pid_t waitpid(pid_t pid, int *status, int options): provoca una espera del
			proceso padre hasta que el proceso hijo con identificador pid finalice. Si pid es
			–1 realiza una espera asociada a la finalización de todos los procesos hijos, es
			decir, se comporta como wait(). La información del estado del proceso hijo se
			almacena en status. El tercer argumento es una máscara de bits (deberá valer
			0 “OR”). La función devuelve el identificador pid del proceso cuyo estado está
			proporcionando. */
			padre();
			/* pid_t waitpid(pid_t pid, int *status, int options): provoca una espera del
			proceso padre hasta que el proceso hijo con identificador pid finalice. Si pid es
			–1 realiza una espera asociada a la finalización de todos los procesos hijos, es
			decir, se comporta como wait(). La información del estado del proceso hijo se
			almacena en status. El tercer argumento es una máscara de bits (deberá valer
			0 “OR”). La función devuelve el identificador pid del proceso cuyo estado está
			proporcionando. */
                        waitpid(pid_hijo1, &status, 0);
                        waitpid(pid_hijo2, &status, 0);
			/* pid_t wait(int *status): provoca una espera del proceso padre hasta que
			cualquier proceso hijo finalice. La información del estado del proceso hijo se
			almacena en status.*/
                        //wait(&status);
                        sleep(1);
                        printf("Ya han terminado los procesos hijos\n");
			break;
	}
        }

	exit(EXIT_SUCCESS);
}
/* Fin función principal */
/* Declaración de las dos funciones que permiten identificar ambos procesos */
int hijo1(void)
{
	sleep(1);
        printf("Hola soy el proceso hijo 1\n");
	return 1;
}

int hijo2(void)
{
        sleep(2);
        printf("Hola soy el proceso hijo 2\n");
        return 1;
}

void padre(void)
{
	printf("Hola soy el proceso padre\n");
}
