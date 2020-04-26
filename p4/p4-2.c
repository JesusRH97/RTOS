/* Creación de colas de mensajes, envío de datos */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
/* Definición de la clave de la cola */
#define M_1 1
/* Prototipos */
int crearcola(int key);
int manejador(int sig);
int cantidad=0;
int msg1;
int status;
struct msgbuf
{
        long mtype;
        int mtext;
} time_msg;
/* Función principal */
int main(void)
{

        /*struct msgbuf time_msg;
        struct msgbuf presenta dos campos:
        long mtype, permite definir al usuario una etiqueta asociada al mensaje.
        char mtext[], texto del mensaje que se envía. */


        if(signal(SIGINT,manejador) == SIG_ERR)
              {
                      perror("signal");
              exit(EXIT_FAILURE);
              }

        /* Llamada a la función de creación de colas */
        msg1=crearcola(M_1);
        time_msg.mtext=0;
        while(1)
        {
                /* unsigned int sleep(unsigned int seconds): provoca una espera en segundos, en función del
                valor del parámetro */
                printf("[PTV] Introduce gasto: ");
                scanf("%d",&time_msg.mtext);
                printf("\n");
                time_msg.mtype=1;
                cantidad=cantidad+time_msg.mtext;
                time_msg.mtext=cantidad;
                /* int msgsnd(int msg, struct msgbuf * buf, int size, int flag): envía el mensaje almacenado en
                el segundo campo de buf, de tamaño size, a la cola con identificador msg. El cuarto parámetro
                sirve para controlar el nivel de ocupación de la cola */
                /* Introducción de datos en la cola */


        }


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

int manejador(int sig){


    time_msg.mtext=cantidad;
    if(msgsnd(msg1,&time_msg,sizeof(time_msg.mtext),0) == -1)
    {
            perror("msgsnd");

    }


    switch(fork()){
        case 0:
            if (execlp("./CENTRAL","CENTRAL", NULL) == -1)
                                {
                                        perror("execlp");
                                        exit(EXIT_FAILURE);
                                }

    }

    wait(&status);
    exit(EXIT_FAILURE);
}
