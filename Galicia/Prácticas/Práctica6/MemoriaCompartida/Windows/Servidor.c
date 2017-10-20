#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_MEM 400							//Tamaño de la memoria en bytes
#define TAM 10								//Tamaño de las matrices

void LlenarMatrices (float m1[TAM][TAM], float m2[TAM][TAM]);

int main (void)
{
	HANDLE hArchMapeo;
	char *idSuma = "MemoriaSuma";					//Identificador de la memoria compartida
	float *apDatos, *apTrabajo, m1[TAM][TAM], m2[TAM][TAM];
	int i, j;
	if ((hArchMapeo = CreateFileMapping (INVALID_HANDLE_VALUE,			//Usa memoria compartida
									NULL,							//Seguridad por default
									PAGE_READWRITE,					//Acceso de Lectura/Escritura a la memoria compartida
									0,								//Tamaño máximo parte alta de un DWORD
									TAM_MEM,						//Tamaño máximo parte baja de un DWORD
									idSuma)							//Identificador de la memoria compartida
									) == NULL)
	{
		printf("No se mapeo correctamente la memoria compartida (%i)\n", GetLastError ());
		exit (-1);
	}
	if ((apDatos = (float *) MapViewOfFile (hArchMapeo,					//Manejador del mapeo
									FILE_MAP_ALL_ACCESS,			//Permiso de Lectura/Escritura dentro de la memoria compartida
									0,
									0,
									TAM_MEM)					//Tamaño de la memoria compartida en bytes
									) == NULL)
	{
		printf("No se creo correctamente la memoria compartida (%i)\n", GetLastError ());
		CloseHandle (hArchMapeo);
		exit (-1);
	}
	LlenarMatrices (m1, m2);
	apTrabajo = apDatos;
	for (i = 0; i < TAM; i ++)
	{
		for (j = 0; j < TAM; j++)
		{
			*apTrabajo++ = m1[i][j];
		}
	}
	*apTrabajo = '\0';
	while (*apDatos != '*')
		sleep (1);
	UnmapViewOfFile (apDatos);
	CloseHandle (hArchMapeo);
	exit (0);
}

void LlenarMatrices (float m1[TAM][TAM], float m2[TAM][TAM])
{
	int i, j;
	srand(time(NULL));
	for (i = 0; i < TAM; i ++)
	{
		for (j = 0; j < TAM; j ++)
		{
			m1[i][j] = rand()%9;
			m2[i][j] = rand()%9;
		}
	}
	printf("MATRIZ 1\n\n");
	for (i = 0; i < TAM; i ++)
	{
		for (j = 0; j < TAM; j ++)
		{
			printf("%.0f ", m1[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	/*printf("\n\nMATRIZ 2\n\n");
	for (i = 0; i < TAM; i ++)
	{
		for (j = 0; j < TAM; j ++)
		{
			printf("%.0f ", m2[i][j]);
		}
		printf("\n");
	}*/
}