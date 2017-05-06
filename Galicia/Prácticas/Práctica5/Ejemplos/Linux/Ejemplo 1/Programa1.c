#include <stdio.h>
#include <pthread.h>

void * hilo (void * arg);		//"hilo" es el nombre de la función

int main(void)
{
	pthread_t id_hilo;
	pthread_create (&id_hilo, NULL, (void *)hilo, NULL);
	pthread_join (id_hilo, NULL);
	return 0;
}

void * hilo (void * arg)
{
	printf("Hola mundo desde un hilo en UNIX\n");
	return NULL;
}

//COMPILAR		->		gcc Programa1.c -o Programa1 -lpthread