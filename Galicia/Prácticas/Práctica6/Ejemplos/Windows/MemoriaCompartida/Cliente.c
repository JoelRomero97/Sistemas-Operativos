#include <windows.h>
#include <stdio.h> 
#include <stdlib.h>
#define TAM_MEMORIA 27 								//Tamaño de la memoria compartida en bytes
int main (void)
{
	HANDLE hArchMapeo;
	char * idMemCompartida = "MemoriaCompartida";				//Identificador de la memoria compartida, equivalente en Windows de "key_t"
	char *apDatos, *apTrabajo;
	if ((hArchMapeo = OpenFileMapping (FILE_MAP_ALL_ACCESS, 		//Acceso Lectura/Escritura de la memoria compartida
								FALSE,								//No se hereda el nombre
								idMemCompartida)					//Identificador de la memoria compartida)
								) == NULL)
	{
		printf("No se abrio correctamente el archivo de mapeo de la memoria compartida (%i)\n", GetLastError ());
		exit (-1);
	}
	if ((apDatos = (char *)MapViewOfFile (hArchMapeo,				//Manejador del mapeo 
									FILE_MAP_ALL_ACCESS,			//Permiso de lectura y escritura dentro de la memoria compartida
									0,
									0,
									TAM_MEMORIA)					//Tamaño de la memoria en bytes) 
									)== NULL)
	{
		printf("No se accedio correctamente a la memoria compartida (%i)\n", GetLastError ());
		CloseHandle (hArchMapeo);						//Cerramos el manejador del mapeo
		exit (-1);
	}
	for (apTrabajo = apDatos; *apTrabajo != '\0'; apTrabajo++)
		putchar (*apTrabajo);
	putchar ('\n');
	*apDatos = '*';
	UnmapViewOfFile (apDatos);
	CloseHandle (hArchMapeo);
	exit (0);
}