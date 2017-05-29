#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

typedef struct intercambio
{
	int mat1[TAM][TAM];
	int mat2[TAM][TAM];
	int matR[TAM][TAM];
	int band;
} INTER;

typedef struct intercambioS
{
	int matR[TAM][TAM];
	int band;
} INTERS;

////////////////////////////////////////////////////////////////////////////////////////////
////                                  	 nieto.c    		                            ////
////                                                                                    ////
////                                                                                    ////
//// Código del proceso nieto, que va a sumar 2 matrices recibidas de su padre por 		////
//// medio de memoria compartida y regresar el resultado de la suma a su proceso abuelo ////
//// por memoria compartida.															////
////                                                                                    ////
////                                                                                    ////
//// Autor: Romero Gamarra Joel Mauricio                                                ////
////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int shmid,shmid2;
	key_t llave;
	INTER *shm;
	INTERS *shm2;
	llave=5678;

	//Crea la memoria compartida para la suma de 2 matrices
	if((shmid=shmget(llave,sizeof(INTER),0666)) < 0)
	{
		perror("4-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	if((shm=(INTER *)shmat(shmid,NULL,0))==(INTER *)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	//Se relaiza la suma
	sumaMatrices(shm->mat1,shm->mat2,shm->matR);
	//Le da permiso al Hijo de proseguir con su ejecucion
	shm->band=0;

	//Crea la memoria para el resultado de la suma de las 2 matrices entre Nieto-Abuelo
	llave=5677;
	if((shmid2=shmget(llave,sizeof(INTERS),IPC_CREAT |0666)) < 0)
	{
		perror("5-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	if((shm2=(INTERS *)shmat(shmid2,NULL,0))==(INTERS *)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	//Copia el resultado de la suma en la 2da memoria compartida
	copiarMatriz(shm2->matR,shm->matR);
	//desasocia las memorias comaprtidas
	shmdt ((char *)shm);
	shmdt ((char *)shm2);
}