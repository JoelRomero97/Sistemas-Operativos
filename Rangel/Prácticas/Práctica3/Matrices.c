#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int tammat;


void rellena(int **matrizA,int **matrizB,int tammat)
{
	int a,b;
	for (int i = 0; i < tammat; ++i)
	{
		for (int j = 0; j < tammat; ++j)
		{
			a=rand()%3;
			b=rand()%3;
			matrizA[i][j]=a;
			matrizB[i][j]=b;

		}
	}
}
void impresion_matriz(int **matrizA,int **matrizB,int tammat)
{
	printf("----------------MatrizA--------------\n");
	for (int i = 0; i < tammat; ++i)
	{
		for (int j = 0; j < tammat; ++j)
			printf("(%d)",matrizA[i][j]);
		printf("\n");
	}
	printf("----------------MatrizB--------------\n");
	for (int i = 0; i < tammat; ++i)
	{
		for (int j = 0; j < tammat; ++j)
			printf("(%d)",matrizB[i][j]);
		printf("\n");
	}
}


int main()
{
	int num_pro,procesos,tarea,status,**matrizA,**matrizB,**matrizR;
	int a=1;
	srand(time(NULL));
	printf("Programa de matrices\n");
	printf("Se crearan 2 matrices de (nxn)\n");
	printf("De el tamaño de la matriz\n");
	scanf("%d",&tammat);
	while (tammat<2)
	{
		printf("No puede existir una matriz menor a 2x2\n");
		scanf("%d",&tammat);
	}
	matrizA=(int **)malloc(sizeof(int *) * tammat);
	matrizB=(int **)malloc(sizeof(int *) * tammat);
	matrizR=(int **)malloc(sizeof(int *) * tammat);
	for (int i = 0; i < tammat; ++i)
	{
		matrizA[i]=(int *)malloc(sizeof(int *) * tammat);
		matrizB[i]=(int *)malloc(sizeof(int *) * tammat);
		matrizR[i]=(int *)malloc(sizeof(int *) * tammat);
	}
	rellena(matrizA,matrizB,tammat);
	impresion_matriz(matrizA,matrizB,tammat);
	printf("Agregue el numero de procesos: \n");
	scanf("%d",&num_pro);
	while (num_pro<1 || num_pro>tammat)
	{
		if (num_pro<1)
		{
			printf("No pueden existir menos de 2 procesos\n");
			scanf("%d",&num_pro);
		}
		else
		{
			printf("No pueden existir mas procesos que filas\n");
			scanf("%d",&num_pro);
		}
		
	}
	for (int i = 0; i < num_pro; ++i)
	{
		procesos=fork();
		if (procesos<0)
		{
			printf("Error en el proceso\n");
			exit(EXIT_FAILURE);
		}
		else if(procesos==0)
		{
			tarea=(tammat/num_pro);
			printf("Proceso: %d\n",a);
			if (num_pro%2==0) //Para numero proceso 2
			{
				for (int c = (tarea*(a-1)); c <= ((tarea*a)-1); ++c) //filas
				{
					for (int d = 0; d < tammat; ++d) //Columnas
					{
						matrizR[c][d]=0;
						for (int e = 0; e < tammat; ++e)
							matrizR[c][d]=(matrizR[c][d]+(matrizA[c][e]*matrizB[e][d]));
						printf("(%d)",matrizR[c][d]);
					}
					printf("\n");
				}
				exit(EXIT_SUCCESS);
			}
			else
			{
				if ((tarea*(a-1))==(tammat-2))
				{
					for (int c = (tarea*(a-1)); c <= (tarea*a); ++c) //filas
					{
						for (int d = 0; d < tammat; ++d) //Columnas
						{
							matrizR[c][d]=0;
							for (int e = 0; e < tammat; ++e)
								matrizR[c][d]=(matrizR[c][d]+(matrizA[c][e]*matrizB[e][d]));
							printf("(%d)",matrizR[c][d]);
						}
						printf("\n");
					}
					exit(EXIT_SUCCESS);	
				}
				for (int c = (tarea*(a-1)); c <= ((tarea*a)-1); ++c) //filas
				{
					for (int d = 0; d < tammat; ++d) //Columnas
					{
						matrizR[c][d]=0;
						for (int e = 0; e < tammat; ++e)
							matrizR[c][d]=(matrizR[c][d]+(matrizA[c][e]*matrizB[e][d]));
						printf("(%d)",matrizR[c][d]);
					}
					printf("\n");
				}
				exit(EXIT_SUCCESS);
			}

		}
		else if(procesos>0)
		{
			if (i==2)
				while(wait(&status)>0);
		}
		a++;		
	}
	free(matrizA);
	free(matrizB);
	free(matrizR);
	//Tarea=filas/numProc
	//[tarea(i-1),(tarea*i)-1] en i=1

}

//Practica de 1000 x 1000 con n procesos
//Pipe para comunicar procesos y ordenar proceso