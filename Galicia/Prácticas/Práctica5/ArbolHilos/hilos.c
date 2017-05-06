#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void * hiloNivel2 (void *arg);
void * hiloNivel3 (void *arg);
void * hiloTerminal (void *arg);



int main (void)
{
  int id_proc, status;
  int i, j;
  system("clear");
  printf("\n\n\n\tIDENTIFICADOR\t\t\tNIVEL\n\n");
  id_proc = fork ();
  if (id_proc == 0)										//Código del proceso hijo
  {
  	printf("\t%d\t\t\t\t1\t\t<- Proceso hijo\n", getpid());
	pthread_t id_Hilo[15];
  	for (i = 0; i < 15; i++)
  	{
	    pthread_create (&id_Hilo[i], NULL, (void *)hiloNivel2, NULL);		// Creación de los primeros 15 hilos
  	}
  	for (i = 0; i < 15; i++)
  	{
  		pthread_join(id_Hilo[i], NULL);
  	}
  	exit(0);
  }
  else														//Código del proceso padre
  {
    while(wait(&status)>0);									//Espera a que se termine de ejecutar el hijo
  	printf("\t%d\t\t\t\t0\t\t<- Proceso padre\n", getpid());
  }
  exit(0);
}

void * hiloNivel2 (void *arg)
{
	printf ("\t%lu\t\t\t2\n", pthread_self());
	pthread_t id_Hilo[10];
	int i, j;
  	for (i = 0; i < 10; i++)
  	{
    	pthread_create (&id_Hilo[i], NULL, (void *)hiloNivel3, NULL);				// Se crean los 10 hilos
	}
	for (i = 0; i < 10; ++i)
	{
		pthread_join(id_Hilo[i], NULL);
	}
	pthread_exit(NULL);
}

void * hiloNivel3 (void *arg)
{
	printf ("\t%lu\t\t\t3\n", pthread_self());
	pthread_t id_Hilo[5];
	int i, j;
  	for (i = 0; i < 5; i++)
  	{
	    pthread_create (&id_Hilo[i], NULL, (void *)hiloTerminal, NULL);			// Creación de los últimos 5 hilos
  	}
  	for (i = 0; i < 5; i++)
  	{
  		pthread_join (id_Hilo[i], NULL);											//Espera a que se ejecuten los hilos
  	}
  	pthread_exit(NULL);
}

void * hiloTerminal (void *arg)
{
  printf ("\tPractica 5\t\t\t4\n");
  pthread_exit(NULL);
}