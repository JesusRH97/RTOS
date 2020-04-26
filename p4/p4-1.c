/* Creación de colas de mensajes */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
/* Definición de las claves de las colas */
#define M_1 1
#define M_2 2
#define M_3 3
/* Prototipos */
int crearcola(int key);
/* Función principal */
int main(void)
{
	int msg1, msg2, msg3;
	/* Llamadas a la función de creación de colas */
	msg1=crearcola(M_1);
	msg2=crearcola(M_2);
	msg3=crearcola(M_3);
	printf("Valores colas %d, %d, %d\n", msg1, msg2, msg3);
	exit(EXIT_SUCCESS);
}
/* Fin función principal */
/* Función que proporciona el identificador de la cola de mensaje */
int crearcola(int key)
{
	int msgqid;
	/* int msgget(int ident, int flag): proporciona un identificador para la cola de clave ident, con
	permisos flag (máscara de bits) */
	switch(msgqid = msgget(key, IPC_CREAT|0666))
	{
		/* IPC_CREAT, instrucción al sistema para crear la cola si todavía no existe */
		case -1:
			perror("msgget");
			exit(EXIT_FAILURE);
		default:
			return msgqid;
	}
} /* Fin función auxiliar */

/*NOTA:
Comprobar la creación de las tres colas de mensajes utilizando el comando del sistema
operativo ipcs.
Emplear para el borrado de las colas de mensaje el comando del sistema operativo:
ipcrm -q ID_cola*/
