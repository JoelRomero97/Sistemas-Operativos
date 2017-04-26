#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "matrixop.h"
#define TAM 10

int
main(void)
{
	int i, j;
	char resultado[300];
	char buffer[6]={};
	double **mat1 = NULL;
	double **mat2 = NULL;
	mat1 = leerMatriz1();
	mat2 = leerMatriz2();
	double mat3[TAM][TAM];
	for (i = 0;   i < TAM ;i++)
	{
		for (j = 0;   j < TAM ;j++)
		{
			mat3[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
	/***************************IMPRESIÓN DE LA SUMA***************************/
	strcpy(resultado,"SUMA ( M1 + M2 )\r\n");
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			sprintf(buffer,"%.0lf\t",mat3[i][j]);
			strcat(resultado,buffer);
			memset(buffer,0,6);
		}
		strcat(resultado,"\r\n");
	}
	free(mat1);
	free(mat2);
	crearArchivo(resultado,"suma.txt");
	exit(0);
}