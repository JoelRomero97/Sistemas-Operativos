#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrixop.h"

#define BUFFERSIZE 700

int
main(void)
{
	char *username = getenv( "USERNAME" );
	char suma[100]={};
	char resta[100]={};
	char multiplicacion[100]={};
	char transpuesta[100];
	char inversa1[100]={};
	char inversa2[100]={};
	strcpy(suma,"C:\\Users\\");
	strcpy(resta,"C:\\Users\\");
	strcpy(multiplicacion,"C:\\Users\\");
	strcpy(transpuesta,"C:\\Users\\");
	strcpy(inversa1,"C:\\Users\\");
	strcpy(inversa2,"C:\\Users\\");
	strcat(suma,username);
	strcat(resta,username);
	strcat(multiplicacion,username);
	strcat(transpuesta,username);
	strcat(inversa1,username);
	strcat(inversa2,username);
	strcat(suma,"\\Desktop\\suma.txt");
	strcat(resta,"\\Desktop\\resta.txt");
	strcat(multiplicacion,"\\Desktop\\multiplicacion.txt");
	strcat(transpuesta,"\\Desktop\\transpuesta.txt");
	strcat(inversa1,"\\Desktop\\inversa1.txt");
	strcat(inversa2,"\\Desktop\\inversa2.txt");
	leerArchivo(suma);
	leerArchivo(resta);
	leerArchivo(multiplicacion);
	leerArchivo(transpuesta);
	leerArchivo(inversa1);
	leerArchivo(inversa2);
	exit(0);
}