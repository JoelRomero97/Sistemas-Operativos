#include <sys/types.h>						//Cliente de la memoria compartida
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_MEMORIA 27						//Tamaño de la memoria compartida en bytes

int main (void)
{
	int shm_id;								//Id de la memoria compartida
	key_t llave;							//Llave para poder acceder a la memoria compartida
	char *shm, *s;
	llave = 5678;							//Valor asignado a la llave, puede estar entre 1 y 65,536
	shm_id = shmget (llave, TAM_MEMORIA, 0666);			//Obtenemos memoria compartida con la llave del servidor
	if (shm_id < 0)
	{
		perror ("Error al obtener la memoria compartida: shmget");
		exit(-1);
	}
	shm = shmat (shm_id, NULL, 0);			//Enlace de memoria compartida
	if (shm == (char *)-1)
	{
		perror ("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	for (s = shm; *s != '\0'; s++)
	{
		putchar (*s);			//Imprimimos lo que haya en la memoria compartida hasta el final de la misma
		printf("\n");
	}
	putchar ('\n');				//Salto de línea al final
	*shm = '*';					//Ponemos * para indicar que ha terminado el cliente
	exit(0);
}