#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * hilo (void *arg);

typedef struct Matrices		// Definición de la estructura de argumentos para la función del hilo
{
  int **m1, **m2,**m3, n;
}matrices;

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
	matriz->m1 = (int **)malloc(sizeof(int *) * matriz->n);
	matriz->m2 = (int **)malloc(sizeof(int *) * matriz->n);
	matriz->m3 = (int **)malloc(sizeof(int *) * matriz->n);
	for (int i = 0; i < (matriz->n); i++)
	{
		matriz->m1[i] = (int *)malloc(sizeof(int *) * matriz->n);
		matriz->m2[i] = (int *)malloc(sizeof(int *) * matriz->n);
		matriz->m3[i] = (int *)malloc(sizeof(int *) * matriz->n);
	}
	srand (time (NULL));
	for (i = 0; i < (matriz->n); i++)			/*SE GENERAN AMBAS MATRICES ALEATORIAMENTE*/
	{
		for (j = 0; j < (matriz->n); j++)
		{
			matriz->m1[i][j] = rand()%10;
			matriz->m2[i][j] = rand()%10;
		}
	}

	printf("\n\nMatriz 1\n\n");
	for (i = 0; i < (matriz->n); i++)
	{
		for (j = 0; j < (matriz->n); j++)
		{
			printf("%d ",matriz->m1[i][j]);
		}
		printf("\n");
	}
	printf("\n\nMatriz 2\n\n");
	for (i = 0; i < (matriz->n); i++)
	{
		for (j = 0; j < (matriz->n); j++)
		{
			printf("%d ",matriz->m2[i][j]);
		}
		printf("\n");
	}
	pthread_create (&id_Hilo, NULL, (void *)hilo, (void *)matriz);		//Creación del hilo
  	pthread_join(id_Hilo, (void *)&matriz);
  	printf("\n\nMatriz resultante\n\n");
  	for (i = 0; i < (matriz->n); i++)
	{
		for (j = 0; j < (matriz->n); j++)
		{
			printf("%d ",matriz->m3[i][j]);
		}
		printf("\n");
	}
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