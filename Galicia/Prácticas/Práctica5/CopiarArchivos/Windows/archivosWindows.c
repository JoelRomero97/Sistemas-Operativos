#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#define BUF_SIZE 8192		// Se define un tamaño de búffer para la lectura de archivos

DWORD WINAPI hiloDirectorio (LPVOID lpParam);

typedef struct Directorios     // Definición de la estructura de argumentos para la función del hilo
{
  char origen[500];     // Ruta del directorio de origen
  char destino[500];    // Ruta del directorio destino
}directorios;

////////////////////////////////////////////////////////////////////////////////////////////
////                                   archivosWindows.c                                ////
////                                                                                    ////
////                                                                                    ////
//// Copiamos archivos de un directorio origen a un directorio destino, ambos definidos ////
//// por el usuario, utilizando el manejo de hilos en C.                                ////
////                                                                                    ////
////                                                                                    ////
//// Autor: Romero Gamarra Joel Mauricio                                                ////
////////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char **argv)
{
  system("cls");
	DWORD idHilo;		              //Identificador del hilo
  HANDLE manHilo;                 //Manejador del hilo
	directorios dir;
  printf ("Ejemplo de ruta: /Users/NombreUsuario/Desktop/CarpetaACopiar\n\n");
  printf ("Ingresa la ruta donde se encuentran los archivos a copiar:\t");
  scanf ("%s", dir.origen);
  printf ("Ingresa la ruta donde se van a copiar los archivos:\t");
  scanf ("%s", dir.destino);
  manHilo = CreateThread (NULL, 0, hiloDirectorio, &dir, 0, &idHilo);	      //Creación del hilo
  WaitForSingleObject (manHilo, INFINITE);
  //printf ("\nOrigen (saliendo del hilo):\t %s\n", dir.origen);
  //printf ("\nDestino (saliendo del hilo):\t %s\n", dir.destino);
  CloseHandle (manHilo);
  return 0;
}

DWORD WINAPI hiloDirectorio (LPVOID lpParam)
{
  directorios * direc = (directorios *)lpParam;
  DIR * dir;
  ssize_t ret_n, ret_out;
  struct dirent *dirEntry;
  struct stat inode;
  char ruta[300], nuevaRuta[300], buffer[BUF_SIZE];
  dir = opendir (direc->origen);
  if (dir == 0)                     //Si hay error al abrir el directorio
  {
    perror ("\nError al abrir el directorio");
    exit(1);
  }else                             //Si se abre correctamente el directorio
  {
    printf("\nEl directorio '%s' se abri%c correctamente.\n",direc->origen, 162);
  }
  return 0;
}




/*printf("Directorio de origen:\t%s\n",direc->origen);
printf("Directorio de destino:\t%s\n", direc->destino);
strcpy(direc->origen, "Users/Joel_/Desktop/origen");
strcpy(direc->destino, "Users/Joel_/Desktop/destino");*/