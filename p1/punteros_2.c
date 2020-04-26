#include<stdlib.h> /* cabecera de la librería estándar de C*/
#include<stdio.h> /* cabecera de la librería de entrada/salida de datos */
#include<errno.h> /* cabecera de la librería de manejo de códigos de error */
#include<string.h>
int main( int argc, char * argv[] )
{
// argc - numero de argumentos de entrada + 1
// argv[] - array de argumentos de entrada
// argv[0] = RUTA/nombre-programa
// argv[1] = argumento 1
// argv[i] = argumento i
// argv[argc] = ultimo argumento introducido
// argv[>argc] = datos locales (nombre maquina, etc)

	if(argc < 3)
	{
		printf("Introduce 2 argumentos\n");
		return 0;
	}

	// punteros a entero
	int * pt_i;
	int * pt_j;

	// puntero a caracteres
	char * frase;
	int i;
	size_t n;

	// malloc - reserva de memoria dinámica
	pt_i = (int*)malloc( 1 * sizeof( int ) );
	pt_j = (int*)malloc( 1 * sizeof( int ) );
	frase = (char*)malloc( 15 * sizeof( char ));

	// Asignación del contenido de memoria del puntero a entero
	*pt_i = atoi(argv[1]);
	printf( "(1) pt_i = %d\n",*pt_i );
	*pt_j = 102;
	printf( "(1) pt_j = %d\n",*pt_j );
	pt_j = pt_i;
	*pt_i = 209;
	printf( "(2) pt_i = %d\n",*pt_i );
	printf( "(2) pt_j = %d\n",*pt_j );

	// Pregunta para el alumno: ¿Cuánto vale *pt_j?
	// ¿Cómo es que ha cambiado su valor de 102 a 209?

	// Asignación a cadena de caracteres
	strcpy( frase, argv[2] );
	n = strlen( frase );
	printf( "(3) frase[%d] = %s\n",(int)n,frase );
	printf( "(4) primera letra es = %c\n", *frase );
	//frase = frase + 1;
	printf( "(5) segunda letra es = %c\n", *(frase +1));
	// free - libera memoria dinámica
	free( pt_i );
	
	printf("Frase completa: ");
	for(int i = 0; i < n; i++)
	{
		printf("%c", *(frase + i));
	}
	printf("\n");




	return 0;
}
