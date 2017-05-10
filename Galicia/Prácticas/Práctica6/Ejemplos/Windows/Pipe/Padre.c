#include "windows.h"
#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[])
{
	char mensaje[] = "Tuberias en Windows";
	DWORD escritos;																		//Bytes escritos
	HANDLE hLecturaPipe, hEscrituraPipe;												//Manejadores para escribir y leer en la tuberia
	PROCESS_INFORMATION piHijo;															//Información del proceso hijo
	STARTUPINFO siHijo;																	//Información para inicialización del proceso hijo
	SECURITY_ATTRIBUTES pipeSeg = {sizeof (SECURITY_ATTRIBUTES), NULL, TRUE};			//Atributos de seguridad no se cambian
	/*OBTENCIÓN DE INFORMACIÓN PARA INICIALIZACIÓN DEL PROCESO HIJO*/
	GetStartupInfo (&siHijo);
	/*CREACIÓN DE LA TUBERÍA SIN NOMBRE*/
	CreatePipe (&hLecturaPipe, &hEscrituraPipe, &pipeSeg, 0);
	/*ESCRITURA EN LA TUBERÍA SIN NOMBRE*/
	WriteFile (hEscrituraPipe, mensaje, strlen (mensaje) + 1, &escritos, NULL);

	siHijo.hStdInput = hLecturaPipe;									//Para que el proceso hijo pueda leer de la tubería
	siHijo.hStdError = GetStdHandle (STD_ERROR_HANDLE);
	siHijo.hStdOutput = GetStdHandle (STD_OUTPUT_HANDLE);				//Si el hijo pudiera escribir -> siHijo.hStdOutput = hEscrituraPipe
	siHijo.dwFlags = STARTF_USESTDHANDLES;

	/*CREACIÓN DEL PROCESO HIJO CON LA INFORMACIÓN ANTERIOR (siHijo)*/
	CreateProcess (NULL, argv[1], NULL, NULL, TRUE, 0, NULL, NULL, &siHijo, &piHijo);				//El TRUE es para heredar manejadores de la tuberia del padre
	/*ESPERAMOS LA EJECUCIÓN DEL PROCESO HIJO*/
	WaitForSingleObject (piHijo.hProcess, INFINITE);
	printf ("Mensaje recibido en el proceso hijo, termina el proceso padre. :)\n");
	CloseHandle (hLecturaPipe);
	CloseHandle (hEscrituraPipe);
	CloseHandle (piHijo.hThread);
	CloseHandle (piHijo.hProcess);
	return 0;
}