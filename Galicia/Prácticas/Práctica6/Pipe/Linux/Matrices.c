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
	int n, status;
	int suma [2], mult [2], sumaResultado [2], multResultado [2];						//Descriptores de archivo
	matrices * matriz = (matrices *) malloc (sizeof (matrices));
	matrices * matrizSuma = (matrices *) malloc (sizeof (matrices));
	matrices * matrizMult = (matrices *) malloc (sizeof (matrices));
	system ("clear");
	printf ("Digite el tamaño de la matriz:\t");
	scanf ("%d",&n);
	int resSuma [n][n], resMult[n][n];
	crearMatrices ((void *)matriz, n);
	crearMatrices ((void *)matrizSuma, n);
	crearMatrices ((void *)matrizMult, n);
	GenerarMatrices (matrizSuma->m1, matrizSuma->m2, n);
	GenerarMatrices (matrizMult->m1, matrizMult->m2, n);
	if (pipe (suma) != 0)								//Creamos la tubería para la suma
	{
		exit(1);
	}
	if (pipe (sumaResultado) != 0)						//Creamos la tubería para resultado de la suma
	{
		exit(1);
	}
	if (pipe (mult) != 0)								//Creamos la tubería para la multiplicación
	{
		exit(1);
	}
	if (pipe (multResultado) != 0)						//Creamos la tubería para resultado de la multiplicación
	{
		exit(1);
	}
	if (fork () == 0)
	{
		read (suma[0], matrizSuma, sizeof (matrices *));
		printf("\n\nSe recibieron las matrices\n\n");
		ImprimirMatriz (matrizSuma->m1, 1, n);
		ImprimirMatriz (matrizSuma->m2, 2, n);
		matrizSuma->m3 = SumaMatrices (matrizSuma->m1, matrizSuma->m2, matrizSuma->m3, n);
		printf("\n\nLa matriz resultante de la suma antes de escribirla en el pipe, es:\n\n");
		ImprimirMatriz (matrizSuma->m3, 3, n);
		for (int i = 0; i < n; i ++)
		{
			for (int j = 0; j < n; j ++)
			{
				resSuma[i][j] = matrizSuma->m3[i][j];
			}
		}
		write (sumaResultado[1], resSuma, sizeof (resSuma));
	}else
	{
		write (suma[1], matrizSuma, sizeof(matrices *));			//Mandamos 2 matrices para sumarlas
		while(wait(&status)>0);
		read (sumaResultado [0], resSuma, sizeof (resSuma));
		printf("\n\nSe recibió la suma de las matrices que es:\n");
		for (int i = 0; i < n; i ++)
		{
			for (int j = 0; j < n; j ++)
			{
				matriz->m3[i][j] = resSuma[i][j];
			}
		}
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
	for (i = 0; i < n; i++)
	{
		matriz->m1[i] = (int *)malloc(sizeof(int ) * n);
		matriz->m2[i] = (int *)malloc(sizeof(int ) * n);
		matriz->m3[i] = (int *)malloc(sizeof(int ) * n);
	}
}

void GenerarMatrices(int **m1, int **m2, int n)
{
	int i, j;
	srand (clock ());
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			m1[i][j] = rand()%6;
			m2[i][j] = rand()%6;
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
}