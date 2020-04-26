/* Fichero shmz.h, contiene información sobre la zona de memoria que se pretende
compartir entre diversos procesos, será preciso incluirlo en la cabecera del fichero de
aquellos procesos que se conecten a la zona de memoria común */
/* Definición de la clave de acceso a la zona de memoria común */
#define CLAVE_SHM ((key_t) 1001)

/* Definición de llaves para semáforos */
#define SEM_A 0
#define SEM_B 1
#define LLAVE 1

/* Estructura de datos que se pretende compartir en la zona de memoria común */
typedef struct{
	int tarea;
}memo;
