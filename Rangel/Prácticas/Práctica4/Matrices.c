#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * hilo (void *arg);

typedef struct Matrices		// Definición de la estructura de argumentos para la función del hilo
{
  int **m1, **m2,**m3, n;
}matrices;

void crearMatrices (void *args);
void GenerarMatrices (void *args);
void ImprimirMatriz (int **m1, int x, int n);

////////////////////////////////////////////////////////////////////////////////
////								Matrices.c 								////
////																		////
////																		////
//// Multiplicación de matrices utilizando un hilo y una estructura donde	////
//// almacenamos las 3 matrices, y el numero de filas que tendrá la matriz 	////
//// regresando la estructura completa como parámetro con pthread_exit.		////
////																		////
////																		////
//// Autor: Romero Gamarra Joel Mauricio									////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	int i, j;
	pthread_t id_Hilo;
	matrices * matriz = (matrices *) malloc (sizeof (matrices));
	system ("clear");
	printf ("Digite el tamaño de la matriz:\t");
	scanf ("%d",&matriz->n);
	crearMatrices ((void *)matriz);
	GenerarMatrices((void *)matriz);
	ImprimirMatriz(matriz->m1, 1, matriz->n);
	ImprimirMatriz(matriz->m2, 2, matriz->n);
	pthread_create (&id_Hilo, NULL, (void *)hilo, (void *)matriz);		//Creación del hilo
  	pthread_join(id_Hilo, (void *)&matriz);
  	ImprimirMatriz(matriz->m3, 3, matriz->n);
  	return 0;
}

void crearMatrices (void *args)
{
	int i;
	matrices * matriz = (matrices *)args;			//Casteo de los argumentos
	matriz->m1 = (int **)malloc(sizeof(int *) * (matriz->n));
	matriz->m2 = (int **)malloc(sizeof(int *) * (matriz->n));
	matriz->m3 = (int **)malloc(sizeof(int *) * (matriz->n));
	for (int i = 0; i < (matriz->n); i++)
	{
		matriz->m1[i] = (int *)malloc(sizeof(int *) * (matriz->n));
		matriz->m2[i] = (int *)malloc(sizeof(int *) * (matriz->n));
		matriz->m3[i] = (int *)malloc(sizeof(int *) * (matriz->n));
	}
}

void GenerarMatrices(void *args)
{
	int i, j;
	matrices * matriz = (matrices *)args;			//Casteo de los argumentos
	srand (time (NULL));
	for (i = 0; i < (matriz->n); i++)
	{
		for (j = 0; j < (matriz->n); j++)
		{
			matriz->m1[i][j] = rand()%5;
			matriz->m2[i][j] = rand()%5;
		}
	}
	return;
}

void ImprimirMatriz(int **m1, int x, int n)
{
	int i, j;
	printf("\n\nMatriz %d\n", x);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ",m1[i][j]);
		}
		printf("\n");
	}
	return;
}

void * hilo (void *arg)
{
	int i, j, k;
	matrices * matriz = (matrices *)arg;			//Casteo de los argumentos
	for (i = 0; i < (matriz->n); i++)
	{
		for (j = 0; j < (matriz->n); j++)
		{
			matriz->m3[i][j] = 0;
			for (k = 0; k < (matriz->n); k++)
			{
				matriz->m3[i][j] += (matriz->m1[i][k]*matriz->m2[k][j]);
			}
		}
	}
	pthread_exit((void *)matriz);
}