#include <stdio.h>
#include <pthread.h>

void * hilo (void * arg);

int main(void)
{
	pthread_t id_hilo;
	char * mensaje = "Hola a todos desde el hilo";
	int devolucion_hilo;
	pthread_create (&id_hilo, NULL, hilo, (void *)mensaje);
	pthread_join (id_hilo, (void *)&devolucion_hilo);
	printf("Valor = %i\n", devolucion_hilo);
	return 0;
}

void * hilo (void * arg)
{
	char * men;
	int resultado_hilo = 0;
	men = (char *)arg;
	printf("%s\n", men);
	resultado_hilo = 100;
	pthread_exit ((void *)resultado_hilo);
}

//COMPILAR		->		gcc Programa2.c -o Programa2 -lpthread