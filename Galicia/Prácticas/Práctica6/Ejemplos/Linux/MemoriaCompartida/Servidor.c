#include <sys/types.h>					//Servidor de la memoria compartida
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define  TAM_MEMORIA 27					//Tamaño de la memoria compartida en bytes

int main (void)
{
	int shm_id;							//Identificador de la memoria compartida
	key_t llave;						//Llave para acceder a la memoria compartida
	char *shm, *s, c;
	llave = 5678;						//Mismo valor de llave que tiene el cliente
	shm_id = shmget (llave, TAM_MEMORIA, IPC_CREAT|0666);		//Creamos la memoria compartida
	if (shm_id < 0)
	{
		perror ("Error al crear la memoria compartida: shmget");
		exit(-1);
	}
	shm = shmat (shm_id, NULL, 0);
	if (shm == (char *)-1)
	{
		perror ("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}else
	{
		printf("Servidor corriendo! :)\n");
	}
	s = shm;
	for (c = 'a'; c <= 'z'; c++)
	{
		*s = c;
		s++;
	}
	*s = '\0';
	while (*shm != '*')						//Mientras no haya un asterisco, el servidor duerme 1 milisegundo
	{
		sleep(1);
	}
	exit(0);
}