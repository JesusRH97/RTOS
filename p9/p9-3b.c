/* Aceptación de un socket creado desde otra máquina */ 
/*SERVIDOR*/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <errno.h>
#include <signal.h>
#define PORT 3005
int sock;

int manejador(int sig);

/* Definición de la dirección lógica del socket */
/* Función principal */
void main(int argc, char* argv[])
{
	/* Declaración de las variables empleadas en la creación del socket */
        int msgsock;
	struct sockaddr_in server;
	/* Declaración de la estructura de datos usada en el intercambio de información */
	struct caracteristicas
	{
                char frase[100];
	} caract;/* Inicialización de los campos de la estructura */

        /*caract.enviar = 128;
        caract.visi = 11;*/

        if(signal(SIGINT,manejador) == SIG_ERR)
               {
                       perror("signal");
               exit(EXIT_FAILURE);
               }
	
	/* Creación del socket */
	if((sock=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	/* Inicializamos el primer campo de la estructura sockaddr_in con el formato de
	direccionamiento del socket */
	server.sin_family=AF_INET;

	/* Inicializamos el segundo campo de la estructura sockaddr_in indicando al programa
	que deberá esperar la llegada de una petición de conexión */
	server.sin_addr.s_addr= INADDR_ANY;

	/* Conversión de la dirección lógica a dirección de red */
        server.sin_port=htons(atoi(argv[1]));

	/* int bind(int socket, struct sockaddr *addr, size_t lenght): asigna una dirección al
	socket asociado al descriptor socket. El segundo y tercer parámetro contienen la
	información de la dirección y tamaño */
	if (bind(sock,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	/* int listen(int socket, unsigned int n): habilita la espera para aceptar conexiones sobre
	socket. El parámetro n indica el tamaño de la cola para llamadas pendientes */
	listen(sock,1);

	/* int accept(int socket, struct sockaddr *addr, size_t lenght_ptr): provoca la aceptación
	de la llamada realizada para socket. Esta función se queda en estado de espera si no hay
	llamadas pendientes. El segundo y tercer parámetro son utilizados para devolver
	información sobre el nombre del cliente que inició la conexión.
	La función devuelve el nuevo descriptor de fichero para el nuevo socket */
	if ((msgsock=accept(sock,(struct sockaddr *)0, (int *)0)) == -1)
		perror("accept");

	/* Mandamos la información almacenada en la estructura caract a la otra máquina a
	través del socket */
        /*if(write(msgsock, &caract, sizeof(struct caracteristicas)) < 0)
                printf("Error %d:%d, escribiendo socket\n",errno>>8,errno&0xff);*/

	/* Leemos a través del socket la información mandada por la otra máquina y la
	introducimos en la estructura caract */

        while(1){
        if(read(msgsock, &caract, sizeof(struct caracteristicas)) <= 0)
		perror("read");

        printf("\nLeemos del socket: %s",caract.frase);
        }
	
	/* Cerramos los descriptores asociados al socket */
	close(msgsock);
	close(sock);
	printf("\nConexión finalizada...\n");
	exit(EXIT_SUCCESS);
}

int manejador(int sig){
    /* Cerramos el descriptor asociado al socket */
    close(sock);
    printf("\nConexión finalizada...\n");
    exit(EXIT_SUCCESS);
}
/* Fin función principal */
