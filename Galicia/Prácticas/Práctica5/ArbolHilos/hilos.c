#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

void * hiloNivel2 (void *arg);
void * hiloNivel3 (void *arg);
void * hiloTerminal (void *arg);
int i;

/////////////////////////////////////////////////////////////////////////
////                         hilos.c	                             ////
////																 ////
////																 ////
//// Creaci髇 de un 醨bol de hilos a partir de un proceso hijo, el   ////
//// cual comienza creando 15 hilos iniciales, que a su vez crean 	 ////
//// 10 hilos cada uno de esos 15 hilos, y a su vez, esos 150 crean  ////
//// los ultimos 5 hilos. Los hilos terminales imprimen "Practica 5" ////
//// mientras que los otros hilos imprimen su identificador y su 	 ////
//// nivel al que pertenecen.										 ////
////																 ////
////																 ////
//// Autor: Romero Gamarra Joel Mauricio                    		 ////
/////////////////////////////////////////////////////////////////////////

int main ()
{
  int id_proc, status;
  system("clear");
  printf("\n\n\n\tIDENTIFICADOR\t\t\tNIVEL\n\n");
  id_proc = fork ();
  if (id_proc == 0)										//C贸digo del proceso hijo
  {
  	printf("\t%d\t\t\t\t1\t\t<- Proceso hijo\n", getpid());
	pthread_t id_Hilo[15];
  	for (i = 0; i < 3; i++)
  	{
	    pthread_create (&id_Hilo[i], NULL, (void *)hiloNivel2, NULL);		// Creaci贸n de los primeros 15 hilos
  	}
  	for (i = 0; i < 3; i++)
  	{
  		pthread_join(id_Hilo[i], NULL);
  	}
  	exit(0);
  }
  else														//C贸digo del proceso padre
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
  	for (i = 0; i < 2; i++)
  	{
    	pthread_create (&id_Hilo[i], NULL, (void *)hiloNivel3, NULL);				// Se crean los 10 hilos
	}
	for (i = 0; i < 2; ++i)
	{
		pthread_join(id_Hilo[i], NULL);
	}
	//pthread_exit(NULL);
	return NULL;
}

void * hiloNivel3 (void *arg)
{
	printf ("\t%lu\t\t\t3\t\t<-NIVEL 3\n", pthread_self());
	pthread_t id_Hilo[5];
  	for (i = 0; i < 5; i++)
  	{
	    pthread_create (&id_Hilo[i], NULL, (void *)hiloTerminal, NULL);			// Creaci贸n de los 煤ltimos 5 hilos
  	}
  	for (i = 0; i < 5; i++)
  	{
  		pthread_join (id_Hilo[i], NULL);											//Espera a que se ejecuten los hilos
  	}
  	//pthread_exit(NULL);
  	return NULL;
}

void * hiloTerminal (void *arg)
{
  printf ("\tPractica 5\n");
  pthread_exit(NULL);
}

