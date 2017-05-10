#include "windows.h"
#include "stdio.h"

int main ()
{
	char mensaje[20];
	DWORD leidos;
	HANDLE hStdIn = GetStdHandle (STD_INPUT_HANDLE);			//Indicamos la entrada estándar en la tubería
	SECURITY_ATTRIBUTES pipeSeg = {sizeof (SECURITY_ATTRIBUTES), NULL, TRUE};

	/*Lectura desde la tubería sin nombre*/
	ReadFile (hStdIn, mensaje, sizeof (mensaje), &leidos, NULL);				//Leemos lo que haya en la tubería
	printf ("Mensaje recibido del proceso padre:\t%s\n", mensaje);
	CloseHandle (hStdIn);														//Cerramos el manejador
	printf("Termina el proceso hijo, continua el proceso padre... :)\n");
	return 0;
}