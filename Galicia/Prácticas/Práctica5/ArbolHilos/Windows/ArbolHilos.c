#include <windows.h>
#include <stdio.h>

DWORD WINAPI hiloNivel2 (LPVOID lpParam);
DWORD WINAPI hiloNivel3 (LPVOID lpParam);
DWORD WINAPI hiloTerminal (LPVOID lpParam);

typedef struct DatosHilo
{
	char nivel2[];
	char c;
}hilo;

////////////////////////////////////////////////////////////////////////////////////////////
////                                   	ArbolHilos.c 	                                ////
////                                                                                    ////
////                                                                                    ////
//// Creación de árbol de 750 hilos en Windows, con 15 primeros hilos hijos de un 		////
//// proceso hijo, cada uno de los 15 creará 10 hijos más, y cada uno de esos 10 creará ////
//// los últimos 5 hijos. Los hijos terminales imprimen Práctica5 y los demás hilos 	////
//// van a imprimir su identificador y su nivel.										////
////                                                                                    ////
////                                                                                    ////
//// Autor: Romero Gamarra Joel Mauricio                                                ////
////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	DWORD idHilo;					//Identificador del hilo
	HANDLE manHilo;					//Manejador del hilo
	hilo datos;
	datos.c = 'a';
	manHilo = CreateThread (NULL, 0, hiloNivel2, &datos, 0, &idHilo);
	WaitForSingleObject (manHilo, INFINITE);
	return 0;
}

DWORD WINAPI hiloNivel2 (LPVOID lpParam)
{
	hilo * datos = (hilo *)lpParam;
	//printf("%s\n", datos->nivel2);
	printf("%c\n", datos->c);
	
	return 0;
}

DWORD WINAPI hiloNivel3 (LPVOID lpParam)
{
	hilo * datos = (hilo *)lpParam;
	//printf("%s\n", datos->nivel3);
	printf("%c\n", datos->c);
	
	return 0;
}

DWORD WINAPI hiloTerminal (LPVOID lpParam)
{
	printf("Pr%ctica 5\n", 160);
	return 0;
}