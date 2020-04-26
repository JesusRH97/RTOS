/* Este programa muestra información del usuario que lo está ejecutando */
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* Función principal */
int main(void)
{
	/* Definición de las variables utilizadas en el programa */
	uid_t yo;
	/* uid_t es un entero que representa al usuario IDs */
	struct passwd *mipass;
	/* passwd es una estructura que presenta distintos campos
	con información del usuario */
	struct group *migrup;
	/* group es una estructura que presenta distintos campos con
	información del grupo de usuarios */
	char **miembros;
	/* Información del usuario */
	/* uid_t getuid(): proporciona el identificador ID de usuario del proceso */
	yo = getuid();
	/* struct passwd * getpwuid(uid_t uid): proporciona un puntero a una estructura que contiene
	información sobre el usuario uid:
		struct passwd{
			char *pw_name; //contiene el login del usuario 
			char *pw_passwd; // palabra clave encriptada del usuario 
			uid_t pw_uid; //Idinetificador ID de usuario 
			.....................
			} */
	mipass = getpwuid(yo);
	if(!mipass)
	{
		printf("No encuentro al usuario %d \n",(int) yo);
		exit(EXIT_FAILURE);
	}
	/* Salida por pantalla de la información de usuario */
	printf("Soy: %s \n",mipass->pw_gecos);
	printf("Mi login es: %s\n", mipass->pw_name);
	printf("Mi id es: %d \n", (int) (mipass->pw_uid));
	printf("Mi directorio de trabajo es: %s\n", mipass->pw_dir);
	printf("Mi shell es: %s\n", mipass->pw_shell);
	/* Información del grupo */
	/* struct group * getgrgid(gid_t gid): proporciona un puntero a una estructura que contiene
	información sobre el grupo de usuario gid (Identificador ID de grupo para dicho usuario):
		struct group {
			char gr_name; // nombre del grupo de usuarios 
			gid_t gr_gid; // identificador ID del grupo 
			char **gr_mem; // array de punteros con los nombres de todos los usuarios del grupo 
			}
	*/
	migrup = getgrgid(mipass->pw_gid);
	if(!migrup)
	{
		printf("No encuentro el grupo %d \n",(int) (mipass->pw_gid));
		exit(EXIT_FAILURE);
	}
	/* Salida por pantalla de la información de grupo de usuarios */
	printf("Mi grupo es: %s (%d)\n", migrup->gr_name, (int) (mipass->pw_gid));
	printf("Los miembros del grupo son:\n");
	miembros = migrup->gr_mem;
	/* Array de punteros con los nombres de los usuarios del grupo */
	while(*miembros) 
	{
		printf("%s \n",*(miembros));
		miembros++;
	}
	return EXIT_SUCCESS;
}
/* Fin función principal */