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
	double **mat1 = NULL;
	double **mat2 = NULL;
	mat1 = leerMatriz1();
	mat2 = leerMatriz2();
	double determinante1;
	double determinante2;
	double m1[TAM][TAM],m2[TAM][TAM];
	for( int i = 0 ; i < TAM ; i++ )
	{
		for( int j = 0 ; j < TAM ; j++ )
		{
			m1[i][j]=mat1[i][j];
			m2[i][j]=mat2[i][j];
		}
	}
	determinante1 = Determinante (m1, 10);
	if (determinante1 != 0)
	{
		matrizCofactores(m1, 10, determinante1);
	}
	else
	{
		printf("La matriz 1 no tiene inversa\n");
	}
	determinante2 = Determinante (m2, 10);
	if (determinante2 != 0)
	{
		matrizCofactores2(m2, 10, determinante2);
	}
	else
	{
		printf("La matriz 2 no tiene inversa\n");
	}
	free(mat1);
	free(mat2);
	exit(0);
}