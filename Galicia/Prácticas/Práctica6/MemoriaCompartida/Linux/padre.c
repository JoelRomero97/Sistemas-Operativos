#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "funciones.h"

typedef struct interccambio
{
	int m1[TAM][TAM];
	int m2[TAM][TAM];
	int mResult[TAM][TAM];
	int band;
} INTER;

typedef struct intercambioS
{
	int mResult[TAM][TAM];
	int band;
} INTERS;

////////////////////////////////////////////////////////////////////////////////////////////
////                                  		padre.c    		                            ////
////                                                                                    ////
////                                                                                    ////
//// Código del proceso padre que manda a un proceso hijo por sustitución de código 2 	////
//// matrices generadas aleatoriamente para multiplicarlas, y al recibir el resultado 	////
//// de la misma, y de la suma de su nieto, el proceso padre calcula las inversas, para	////
//// por último, imprimir el resultado de las inversas de los resultados en su archivo 	////
//// inversaSuma e inversaMultiplicacion.												////
////                                                                                    ////
////                                                                                    ////
//// Autor: Romero Gamarra Joel Mauricio                                                ////
////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	
	pid_t pid;
	char *argv[9];
	argv[0] = "hijo";
	int c;
	int shmid,shmid2;
	key_t llave;
	INTER *shm;
	INTERS *shm2;
	float inv[TAM][TAM];
	llave=5679;

	srand(time(NULL));

	//Crea la memoria compartida para la mutiplicacion de 2 matrices
	if((shmid=shmget(llave,sizeof(INTER),IPC_CREAT | 0666)) < 0)
	{
		perror("1-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	if((shm=(INTER *)shmat(shmid,NULL,0))==(INTER *)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	shm->band=-1;

	//LLena las 2 matrices con numeros aleatorios del 0 al 9
	generaMatriz(shm->m1);
	generaMatriz(shm->m2);
	//Imprime las matrices generadas
	printf("Matriz1:\n");
	imprimeMatriz(shm->m1);
	printf("Matriz2	:\n");
	imprimeMatriz(shm->m2);

	//se crea al hijo
	if((pid = fork()) == 0)
		execv(argv[0],argv);
	wait(0);

	//espera hasta que se haya calculado la multiplicacion
	while(shm->band==-1)
		sleep(1);

	//Crea la memoria compartida para el resultado de la suma
	llave=5677;
	if((shmid2=shmget(llave,sizeof(INTERS),IPC_CREAT |0666)) < 0)
	{
		perror("6-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	if((shm2=(INTERS *)shmat(shmid2,NULL,0))==(INTERS *)-1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}

	//Imprime la suma y la multiplicacion de las 2 matrices generadas
	printf("Suma:\n");
	imprimeMatriz(shm2->mResult);

	printf("Multiplicacion:\n");
	imprimeMatriz(shm->mResult);

	//Guardamos en sus respectivos archivos las inversas de la suma y la multiplicacion de las matrices
	inversa(shm->mResult,inv,TAM);
	creaArchivo(inv,"/home/joel/Desktop/inversaMultiplicacion");

	inversa(shm2->mResult,inv,TAM);
	creaArchivo(inv,"/home/joel/Desktop/inversaSuma");
	
	//Destruimos la memoria compartida
	shmdt ((char *)shm);
	shmdt ((char *)shm2);
	shmctl(shmid, IPC_RMID, NULL);
	shmctl(shmid2, IPC_RMID, NULL);
	exit(0);
}