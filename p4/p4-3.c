/* Creación de colas de mensajes, lectura de datos */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* Definición de la clave de la cola */
#define M_1 1
/* Prototipos */
int crearcola(int key);
int msg1;
/* Función principal */
int main()
{
    struct msgbuf
    {
            long mtype;
            int mtext;
    } time_msg;

        msg1=crearcola(M_1);

        if(msgrcv(msg1,&time_msg,sizeof(time_msg.mtext),1,0)>0)
        {
                printf("\n");
                printf("[CENTRAL] El gasto vale %d",time_msg.mtext);
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
