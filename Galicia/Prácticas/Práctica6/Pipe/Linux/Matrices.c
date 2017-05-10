#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Matrices		// Definición de la estructura de matrices
{
  int **m1, **m2,**m3;
}matrices;

void crearMatrices (void *args, int n);
void GenerarMatrices (int **m1, int **m2, int n);
void ImprimirMatriz (int **m1, int x, int n);

////////////////////////////////////////////////////////////////////////////////
////								Matrices.c 								////
////																		////
////																		////
//// Multiplicación, suma e inversa de matrices utilizando tuberías para 	////
//// comunicar a los procesos hijos con sus padres y viceversa, sabiendo	////
//// cual matriz es resultado de cual proceso, ya que el hijo realiza la 	////
//// multiplicación y el nieto realiza la suma.								////
////																		////
////																		////
//// Autor: Romero Gamarra Joel Mauricio									////
////////////////////////////////////////////////////////////////////////////////

int main (void)
{
	int i, j, n;
	int desc_arch[2];					//Descriptor de archivo
	matrices * matriz = (matrices *) malloc (sizeof (matrices));
	system ("clear");
	printf ("Digite el tamaño de la matriz:\t");
	scanf ("%d",&n);
	crearMatrices ((void *)matriz, n);
	GenerarMatrices(matriz->m1, matriz->m2, n);
	ImprimirMatriz(matriz->m1, 1, n);
	ImprimirMatriz(matriz->m2, 2, n);
	if (pipe (desc_arch) != 0)					//Creamos la tubería
		exit(1);								//Salimos si ocurre un error en la creación






	/*if (fork () == 0)			//Código del proceso hijo
	{
		while (VALOR)
		{
			read (desc_arch[0], buffer, sizeof (buffer));		//Posición 0 del descriptor es para lectura
			printf("Se recibió:\t%s\n", buffer);
		}
	}
	while (VALOR)
	{
		gets (buffer);							//Leemos del teclado
		write (desc_arch[1], buffer, strlen (buffer) + 1);		//Posición 1 del descriptor es para escritura
	}*/
}

void crearMatrices (void *args, int n)
{
	int i;
	matrices * matriz = (matrices *)args;			//Casteo de los argumentos
	matriz->m1 = (int **)malloc(sizeof(int *) * n);
	matriz->m2 = (int **)malloc(sizeof(int *) * n);
	matriz->m3 = (int **)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
	{
		matriz->m1[i] = (int *)malloc(sizeof(int *) * n);
		matriz->m2[i] = (int *)malloc(sizeof(int *) * n);
		matriz->m3[i] = (int *)malloc(sizeof(int *) * n);
	}
}

void GenerarMatrices(int **m1, int **m2, int n)
{
	int i, j;
	srand (time (NULL));
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			m1[i][j] = rand()%10;
			m2[i][j] = rand()%10;
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