#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

typedef struct Matrices		// Definición de la estructura de matrices
{
  int **m1, **m2,**m3;
}matrices;

void crearMatrices (void *args, int n);
void GenerarMatrices (int **m1, int **m2, int n);
void ImprimirMatriz (int **m1, int x, int n);
int ** SumaMatrices (int **m1, int **m2, int **m3, int n);

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
	int i, j, n, status;
	int suma[2], mult[2];						//Descriptores de archivo
	matrices * matriz = (matrices *) malloc (sizeof (matrices));
	matrices * matrizSuma = (matrices *) malloc (sizeof (matrices));
	matrices * matrizMult = (matrices *) malloc (sizeof (matrices));
	system ("clear");
	printf ("Digite el tamaño de la matriz:\t");
	scanf ("%d",&n);
	crearMatrices ((void *)matriz, n);
	crearMatrices ((void *)matrizSuma, n);
	crearMatrices ((void *)matrizMult, n);
	GenerarMatrices (matriz->m1, matriz->m2, n);
	//ImprimirMatriz (matriz->m1, 1, n);
	//ImprimirMatriz (matriz->m2, 2, n);
	if (pipe (suma) != 0)						//Creamos la tubería para la suma
	{
		exit(1);
	}
	if (pipe (mult) != 0)						//Creamos la tubería para la multiplicación
	{
		exit(1);
	}
	if (fork () == 0)
	{
		read (suma[0], matriz, sizeof (matrices *));
		printf("Se recibieron las matrices\n\n\n");
		ImprimirMatriz (matriz->m1, 1, n);
		ImprimirMatriz (matriz->m2, 2, n);
		matriz->m3 = SumaMatrices (matriz->m1, matriz->m2, matriz->m3, n);
		printf("\nMatriz resultante de la suma que se mandará por la tubería 'suma'\n");
		ImprimirMatriz (matriz->m3, 3, n);
		write (suma[1], matriz, sizeof (matrices *));
	}else
	{
		write (suma[1], matriz, sizeof(matrices *));			//Mandamos 2 matrices para sumarlas
		while(wait(&status)>0);
		read (suma [0], matriz, sizeof (matrices *));
		printf("\n\nSe recibió la suma de las matrices que es\n");
		ImprimirMatriz (matriz->m3, 3, n);
	}
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

int ** SumaMatrices (int **m1, int **m2, int **m3, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			m3[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return m3;
	//ImprimirMatriz(m3, 3, n);
}