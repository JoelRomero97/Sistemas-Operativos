#include <windows.h>
#include <stdio.h>

DWORD WINAPI funcionHilo (LPVOID lpParam);

struct Informacion
{
	int val_1;
	int val_2;
};

typedef struct Informacion info;

int main ()
{
	DWORD idHilo;			//Identificador del hilo
	HANDLE manHilo;			//Manejador del hilo
	info argumentos;
	argumentos.val_1 = 10;
	argumentos.val_2 = 100;

	//Creación del hilo
	manHilo = CreateThread (NULL, 0, funcionHilo, &argumentos, 0, &idHilo);
	//Esperamos la finalización del hilo
	WaitForSingleObject (manHilo, INFINITE);
	printf("VALORES AL SALIR DEL HILO\n1:\t%i\n2:\t%i\n\n", argumentos.val_1, argumentos.val_2);

	//Cerramos el manejador del hilo creado
	CloseHandle (manHilo);
	return 0;
}

DWORD WINAPI funcionHilo (LPVOID lpParam)
{
	info * datos = (info *)lpParam;
	printf("VALORES AL ENTRAR AL HILO\n1:\t%i\n2:\t%i\n\n",datos->val_1, datos->val_2);
	datos->val_1*=2;
	datos->val_2*=2;
	return 0;
}