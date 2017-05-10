#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_MEMORIA 27					//Tamaño de la memoria compartida en bytes

int main (void)
{
	HANDLE hArchMapeo;
	char *idMemCompartida = "MemoriaCompartida";				//Identificador de la memoria compartida
	char *apDatos, *apTrabajo, c;
	hArchMapeo = CreateFileMapping (INVALID_HANDLE_VALUE,			//Usa memoria compartida
									NULL,							//Seguridad por default
									PAGE_READWRITE,					//Acceso de Lectura/Escritura a la memoria compartida
									0,								//Tamaño máximo parte alta de un DWORD
									TAM_MEMORIA,					//Tamaño máximo parte baja de un DWORD
									idMemCompartida);				//Identificador de la memoria compartida
	if (hArchMapeo == NULL)
	{
		printf("No se mapeo correctamente la memoria compartida (%i)\n", GetLastError ());
		exit (-1);
	}
	apDatos = (char *)MapViewOfFile (hArchMapeo,					//Manejador del mapeo
									FILE_MAP_ALL_ACCESS,			//Permiso de Lectura/Escritura dentro de la memoria compartida
									0,
									0,
									TAM_MEMORIA);					//Tamaño de la memoria compartida en bytes
	if (apDatos == NULL)
	{
		printf("No se creo correctamente la memoria compartida (%i)\n", GetLastError ());
		CloseHandle (hArchMapeo);
		exit (-1);
	}
	apTrabajo = apDatos;
	for (c = 'a'; c <= 'z'; c++)
		*apTrabajo++ = c;
	while (*apDatos != '*')
		sleep (1);
	UnmapViewOfFile (apDatos);
	CloseHandle (hArchMapeo);
	exit (0);
}