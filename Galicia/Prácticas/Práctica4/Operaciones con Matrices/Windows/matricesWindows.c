#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "matrixop.h"
#define TAM 10
int
main(int argc, char *argv[])
{
	STARTUPINFO si;		        	/* Estructura de información inicial para Windows */
    PROCESS_INFORMATION pi;         /* Estructura de información del adm. de procesos */
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    argv[1] = "suma.exe";
	argv[2] = "resta.exe";
	argv[3] = "multiplicacion.exe";
	argv[4] = "transpuesta.exe";
	argv[5] = "inversa.exe";
	argv[6] = "lectura.exe";
	
	llenarMatrices();				/* Funcion para llenar matrices. Se encuentra en matrixop.c */
	
	for( int j = 1 ; j <= 6 ; j++ )
	{
		if(!CreateProcess(NULL, argv[j], NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			printf( "Fallo al invocar CreateProcess( %lu )\n", GetLastError() );
			return -1;
		}
		WaitForSingleObject(pi.hProcess, INFINITE); /* Espera a que cada proceso hijo concluya en forma secuencial */
	}
	
	CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
	
}