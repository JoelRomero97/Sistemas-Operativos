#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "funciones.h"

void crearDirectorioConArchivos()
{
	system("cls");
	int len;
	char * username = getenv( "USERNAME" );		//Obtener el nombre del usuario
	if(username==NULL) 
		printf("Error al obtener el nombre de usuario :(\n");
	else // Crear directorio
	{
		int crearDir;
		int dir;
		char ruta[100];
		printf("Hola %s :D\n",username);
		printf("Ingrese la ruta donde seran creados los archivos:\n");
		scanf( "%s" , ruta );
		len = strlen(ruta);
		if( ruta[len-1] != '\"' )
			strcat(ruta,"\\");
		dir = SetCurrentDirectory( ruta );			//Regresa un 0 si falla, cualquier valor distinto de 0 en caso contrario
		if( dir != 0 )			//Ya existe el directorio
		{
			printf("\nError al crear el directorio, ya existe o la ruta esta mal especificada\n");
			system("pause");
		}
		else
		{
			crearDir = CreateDirectory(ruta,NULL);		//Crear el directorio con todos los permisos
			if(crearDir==0)
			{
				printf("\nOcurrio un error al crear el directorio\n");
				system("pause");
			}
			else
			{
				printf("\nSe ha creado exitosamente el directorio %s :)\n",ruta);
				system("pause");
				generarArchivos( ruta );
			}	
		}
	}
}

void generarArchivos(char * ruta)
{
	int a,i,n;
	HANDLE hFile; 					//Archivo a manejar
	DWORD dwBytesToWrite; 			//Numero de bytes a escribir
    DWORD dwBytesWritten = 0; 		//Numero de bytes escritos
	bool bErrorFlag = FALSE; 		//Bandera de error
	char cadena[100];
	char archivo[20];				//Nombre del archivo
	char direccion[150]={};
	system("cls");
	printf("\nIngresa la cantidad de archivos a generar:\t");
	scanf("%d",&n);
	fflush(stdin);
	for(i=0;i<n;i++)
	{
		strcat(direccion,ruta);
		fflush(stdin);
		printf("\n\nIngresa el nombre del archivo %d:\t", i+1);
		scanf("%[^\n]",&archivo);
		fflush(stdin);
		strcat(direccion,archivo);
		printf("Ingresa la cadena a ingresar en el archivo:\t");
		fflush(stdin);
		scanf("%[^\n]",&cadena);
		dwBytesToWrite = (DWORD)strlen(cadena);
		printf("Se ha guardado el archivo '%s' en:\t '%s'\n",archivo,direccion);
		hFile = CreateFile(direccion,           // Dirección del archivo
                        GENERIC_WRITE,          // Apertura para escritura
                        0,                      // No compartir
                        NULL,                   // Seguridad por defecto
                        CREATE_NEW,             // Solo crear un nuevo archivo
                        FILE_ATTRIBUTE_NORMAL,  // Archivo normal
                        NULL);                  // Sin plantillas de atributos
		bErrorFlag = WriteFile( 
                    hFile,           // Abrir archivo a manejar
                    cadena,          // Informacion a escribir
                    dwBytesToWrite,  // Numero de bytes a escribir
                    &dwBytesWritten, // Numero de bytes que fueron escritos
                    NULL);           // Ninguna estructura superpuesta
		printf("Se escribieron %d bytes en %s exitosamente.\n", dwBytesWritten, direccion);
		CloseHandle(hFile);//Cierra el archivo
		memset(archivo,0,20);
		memset(cadena,0,100);
		memset(direccion,0,150);
	}
	system("pause");	
}
