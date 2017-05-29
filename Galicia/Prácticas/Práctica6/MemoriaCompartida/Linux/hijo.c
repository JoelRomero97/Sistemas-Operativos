#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones.h"

typedef struct intercambio
{
	int mat1[TAM][TAM];
	int mat2[TAM][TAM];
	int matR[TAM][TAM];
	int flag;
} MATRIZ;

////////////////////////////////////////////////////////////////////////////////////////////
////                                  		 hijo.c    		                            ////
////                                                                                    ////
////                                                                                    ////
//// Código del proceso hijo que va a multiplicar 2 matrices recibidas de su padre, por ////
//// medio de memoria compartida, y a su vez creando otro proceso hijo que va a sumar 2	////
//// matrices, el hijo, regresará a su padre el resultado por la memoria compartida.	////
////                                                                                    ////
////                                                                                    ////
//// Autor: Romero Gamarra Joel Mauricio                                                ////
////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	pid_t pid;
	int shmid, shmid2;
	key_t llave, llave2;
	MATRIZ *shm, *shm2;
	llave = 5679;
	argv[1] = "nieto";

	//Creamos la memoria compartida para la mutiplicacion de 2 matrices
	if((shmid = shmget(llave,sizeof(MATRIZ),0666)) < 0)
	{
		perror("2-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	if((shm = (MATRIZ *) shmat (shmid, NULL, 0)) == (MATRIZ *) -1 )
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}
	
	//Se realiza la multiplicacion de las matrices
	multiplicaMatrices (shm->mat1, shm->mat2, shm->matR);
	//la bandera da permiso al padre de proseguir con su ejecucion
	shm -> flag = 0;
	
	//Crea la memoria compartida para la suma de las 2 matrices
	llave2 = 5678;
	if((shmid2 = shmget (llave2, sizeof (MATRIZ), IPC_CREAT | 0666)) < 0)
	{
		perror("3-Error al obtener memoria compartida: shmget");
		exit(-1);
	}
	if((shm2 = (MATRIZ *) shmat (shmid2, NULL, 0)) == (MATRIZ *) -1)
	{
		perror("Error al enlazar la memoria compartida: shmat");
		exit(-1);
	}

	//Se copian las matrices generadas de la memoria compartida Padre-Hijo a la memoria de Hijo-Abuelo
	copiarMatriz (shm2->mat1, shm->mat1);
	copiarMatriz (shm2->mat2, shm->mat2);

	//Se crea el proceso para el nieto
	if((pid = fork()) == 0)
		execv(argv[1],argv);
	wait(0);

	//Espera hasta que se haya calculado la suma
	while(shm2 -> flag == -1)
		sleep(1);
	
	//Destruimos la memoria compartida
	shmdt ((char *)shm);
	shmdt ((char *)shm2);
	shmctl(shmid2, IPC_RMID, NULL);
	exit(0);
}