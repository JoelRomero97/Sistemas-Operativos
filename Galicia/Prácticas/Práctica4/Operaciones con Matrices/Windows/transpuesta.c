#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrixop.h"
#define TAM 10

int
main(void)
{
	int i, j;
	char resultado[500];
	char buffer[6]={};
	double **mat1 = NULL;
	double **mat2 = NULL;
	mat1 = leerMatriz1();
	mat2 = leerMatriz2();
	double mat1T[TAM][TAM];
	double mat2T[TAM][TAM];
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			mat1T[i][j] = mat1[j][i];
			mat2T[i][j] = mat2[j][i];
		}
	}
			
	/***************************IMPRESIÓN DE TRANSPUESTA MATRIZ 1***************************/
	strcpy(resultado,"TRANSPUESTA DE MATRIZ 1\r\n");
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			sprintf(buffer,"%.0lf\t",mat1T[i][j]);
			strcat(resultado,buffer);
			memset(buffer,0,6);
		}
		strcat(resultado,"\r\n");
	}

	/***************************IMPRESIÓN DE TRANSPUESTA MATRIZ 2***************************/
	strcat(resultado,"\r\nTRANSPUESTA DE MATRIZ 2\r\n");
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			sprintf(buffer,"%.0lf\t",mat2T[i][j]);
			strcat(resultado,buffer);
			memset(buffer,0,6);
		}
		strcat(resultado,"\r\n");
	}
	free(mat1);
	free(mat2);
	crearArchivo(resultado,"transpuesta.txt");
	exit(0);
}