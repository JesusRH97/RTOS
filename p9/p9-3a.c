/* Creación de un socket contra otra máquina */ 
/*CLIENTE*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#define PORT 3005
int sock;

int manejador(int sig);

/* Definición de la dirección lógica del socket */

/* Función principal */
void main(int argc, char *argv[])
{
	/* Declaración de las variables empleadas en la creación del socket */
        int len;
	struct sockaddr_in server;
	struct hostent *dest;
	/* Declaración de la estructura de datos usada en el intercambio de información */
	struct caracteristicas
	{
                char frase[100];
	} caract;

        if(signal(SIGINT,manejador) == SIG_ERR)
               {
                       perror("signal");
               exit(EXIT_FAILURE);
               }

	/* Comprobación de que en la línea de comandos se ha incluido el nombre de la
	máquina contra la que se lanza el socket */
        if (argc<2)
	{
		printf("\nFalta como parámetro el nombre de la maquina.");
		exit(EXIT_FAILURE);
	}

	/* int socket(int namespace, int style, int protocol): crea un socket especificando el
	modo de comunicación en style.
	El parámetro namespace establece el direccionamiento del socket y el protocolo a
	utilizar, pudiendo ser:
	PF_FILE : asociado a un fichero.
	AF_INET : asociado a Internet.
	El modo de comunicación especificado en style puede ser:
	SOCK_STREAM : modo similar al pipe.
	SOCK_DGRAM : modo a utilizar cuando no queremos un control de respuesta.
	El protocolo de comunicaciones es indicado en protocol, normalmente se pone a cero
	La función devuelve el descriptor de fichero para el nuevo socket o –1 en caso de fallo
	en la creación *//* Creación del socket */
	if((sock=socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("Error %d:%d, abriendo socket\n",errno>>8,errno&0xff);
		exit(EXIT_FAILURE);
	}

	/* Imprimimos el descriptor asignado al socket */
        /*printf("Socket: %d",sock);*/
	
	/* Inicializamos el primer campo de la estructura sockaddr_in con el formato de
	direccionamiento del socket */
	server.sin_family=AF_INET;
	
	/* struct hostent *gethostbyname(const char *name): proporciona información sobre la
	máquina indicada en name. Si no la encuentra devuelve un puntero nulo */
	dest=gethostbyname(argv[1]);
	
	/* Comprobamos la existencia de la máquina a la que nos vamos a conectar */
	if(dest == (struct hostent *)0)
	{
		printf("Error %d:%d, buscando host\n",errno>>8,errno&0xff);
		exit(EXIT_FAILURE);
	}

	/* void memcpy(void *to, const void *from, size_t size): copiamos size bytes de from a
	to. En nuestro caso pretendemos copiar la dirección de Internet de la máquina a la que
	nos queremos conectar y que la función gethostbyname introduce en dest->h_addr, en
	el segundo campo de la estructura server que es una estructura del tipo struct in_addr
	sin_addr que deberá contener dicha dirección */
	memcpy((char *)&server.sin_addr.s_addr,(char *)dest->h_addr,4);

	/* unsigned short int htons(unsigned short int hostshort): conversión del valor
	almacenado en hostshort (dirección lógica del socket) a una dirección de red */
        server.sin_port=htons(atoi(argv[2]));

	/* int connect(int socket, struct sockaddr *addr, size_t length): inicializa una conexión
	del socket asociado al descriptor socket, empleando la dirección especificada en addr y
	el tamaño indicado en lenght. Si el proceso de conexión funciona devuelve un cero, en
	caso contrario –1 */
	if (connect(sock,(struct sockaddr *)&server,sizeof(server)) == -1)
	{
		printf("Error %d:%d, conectando socket\n",errno>>8,errno&0xff);
		exit(EXIT_FAILURE);
	}

	/* Leemos a través del socket la información mandada por la otra máquina y la
	introducimos en la estructura caract */

        /*if((len= read(sock, &caract, sizeof(struct caracteristicas))) < 0)
		perror("read");

        printf("\nLeemos del socket: enviar -> %d, visi -> %d",caract.enviar,caract.visi);*/
	
	/* Mandamos la información almacenada en la estructura caract a la otra máquina a
	través del socket */
        /*caract.enviar=255;
        caract.visi=22;*/

        while(1){
        /*Leemos por teclado*/
        printf("Introduce una frase: ");
        fgets(caract.frase,sizeof(caract.frase),stdin);
        fflush(stdin);

	if (write(sock, &caract, sizeof(struct caracteristicas)) < 0)
		printf("Error %d:%d, escribiendo socket\n",errno>>8,errno&0xff);
        }
	

}

int manejador(int sig){
    /* Cerramos el descriptor asociado al socket */
    close(sock);
    printf("\nConexión finalizada...\n");
    exit(EXIT_SUCCESS);
}

/* Fin función principal */
