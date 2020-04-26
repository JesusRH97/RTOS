/* Comunicación de procesos mediante pipes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
/* Función principal */
int main(void)
{
        int pfd[2], pfd1[2],resultado1,cantidad;
        char descriptor_3[10], descriptor_6[10], numero[10], resultado[10], iteraciones[10];
        int status, nread;
        char s[100];
	/* Creación del pipe */
	if(pipe(pfd) == -1)
		perror("pipe");
        /* Creación del otro pipe */
        if(pipe(pfd1) == -1)
                perror("pipe");
	/* Creación de un proceso hijo */

        printf("Cuantas multiplicaciones quieres realizar?: ");
        scanf("%d",&cantidad);

	switch(fork()){
		case -1:
                        perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			/* Cierre del descriptor de escritura del pipe en el proceso hijo */
			if(close(pfd[1]) == -1)
				perror("close");
			/* int sprintf(char *buffer, const char *formato,...): su funcionamiento es
			idéntico a la función printf, salvo que la salida generada se pone en el array
			apuntado por buffer. El valor devuelto es igual al número de caracteres puesto
			en el array */

                        sprintf(descriptor_3,"%d",pfd[0]);
                        sprintf(descriptor_6,"%d",pfd1[1]);
                        sprintf(iteraciones,"%d",cantidad);

			/* int execlp(const char *filename, const char *argv[0],..): permite la ejecución
			del programa filename como un nuevo proceso imagen. La lista de argumentos
			es:
			const char *filename: contiene el nombre del programa
			ejecutable.
			const char argv[]: el primer elemento de array es el
			nombre de programa, y el último un puntero NULL. */
                        if (execlp("./p3-3","p3-3", descriptor_3, descriptor_6, iteraciones, NULL) == -1)
			{
				perror("execlp");
				exit(EXIT_FAILURE);
			}
	}
	/* Cierre del descriptor de lectura en el proceso padre */
	if(close(pfd[0]) ==- 1)
		perror("close");

        for(int i=1;i<=cantidad;i++){

        //Pedimos un número por teclado
        printf("Introduce un número: ");
        scanf("%s",numero);

	/* El proceso padre escribe en el pipe */
        if(write(pfd[1],numero,sizeof(numero)) == -1)
		perror("write");

        //Leemos del descriptor 5
        switch(nread = read(pfd1[0],resultado,sizeof(resultado)))
        {
                case -1:
                        perror("read");
                        break;
                case 0:
                        perror("EOF");
                        break;
                default:
                        resultado1=atoi(resultado);
                        printf("\nEl resultado de multiplicarlo por el doble es: %d\n",resultado1);
        }
        }


	/* El proceso padre espera la finalización del proceso hijo */
	wait(&status);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
