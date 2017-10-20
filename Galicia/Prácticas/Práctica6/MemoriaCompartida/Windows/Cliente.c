#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define TAM_MEM 400							//Tamaño de la memoria en bytes
#define TAM 10								//Tamaño de las matrices

int main (void)
{
	HANDLE hArchMapeo;
	char * idSuma = "MemoriaSuma";
	float *apDatos, *apTrabajo;
	if ((hArchMapeo = OpenFileMapping (FILE_MAP_ALL_ACCESS, 		//Acceso Lectura/Escritura de la memoria compartida
								FALSE,								//No se hereda el nombre
								idSuma)								//Identificador de la memoria compartida)
								) == NULL)
	{
		printf("No se abrio correctamente el archivo de mapeo de la memoria compartida (%i)\n", GetLastError ());
		exit (-1);
	}
	if ((apDatos = (float *)MapViewOfFile (hArchMapeo,				//Manejador del mapeo 
									FILE_MAP_ALL_ACCESS,			//Permiso de lectura y escritura dentro de la memoria compartida
									0,
									0,
									TAM_MEM)						//Tamaño de la memoria en bytes
									)== NULL)
	{
		printf("No se accedio correctamente a la memoria compartida (%i)\n", GetLastError ());
		CloseHandle (hArchMapeo);						//Cerramos el manejador del mapeo
		exit (-1);
	}
	for (apTrabajo = apDatos; *apTrabajo != '\0'; apTrabajo++)
		 printf("%0.f ", *apTrabajo);
	printf ("\n");
	*apDatos = '*';
	UnmapViewOfFile (apDatos);
	CloseHandle (hArchMapeo);
	exit (0);
}