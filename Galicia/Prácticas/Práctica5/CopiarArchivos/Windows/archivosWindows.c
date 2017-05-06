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

struct Directorios    // Definición de la estructura de argumentos para la función del hilo
{
  char origen[500];     // Ruta del directorio de origen
  char destino[500];    // Ruta del directorio destino
};

typedef struct  Directorios directorios;

int main (int argc, char **argv)
{
  	DWORD idHilo;		              //Identificador del hilo
    HANDLE manHilo;                 //Manejador del hilo
  	//struct Directorios * directorios = (struct Directorios *) malloc (sizeof (struct Directorios));	         // Estructura para argumentos del hilo
  	directorios dir;
    printf ("Ejemplo de ruta: /home/NombreUsuario/Descargas/CarpetaCopiar\n");
    printf ("Ingresa la ruta donde se encuentran los archivos a copiar:\t");
    scanf ("%s", dir.origen);						// Guardamos la ruta de origen
    //printf ("\nOrigen:\t %s\n", dir.origen);
    printf ("\nIngresa la ruta donde se van a copiar los archivos:\t");
    scanf ("%s", dir.destino);						// Guardamos la ruta destino
    //printf ("\nDestino:\t %s\n", dir.destino);
    manHilo = CreateThread (NULL, 0, hiloDirectorio, &dir, 0, &idHilo);	      //Creación del hilo
    WaitForSingleObject (manHilo, INFINITE);
    printf ("\nOrigen (saliendo del hilo):\t %s\n", dir.origen);
    printf ("\nDestino (saliendo del hilo):\t %s\n", dir.destino);
    CloseHandle (manHilo);
    return 0;
}

DWORD WINAPI hiloDirectorio (LPVOID lpParam)
{
  directorios * direc = (directorios *)lpParam;
  printf("Directorio de origen:\t%s\n",direc->origen);
  printf("Directorio de destino:\t%s\n", direc->destino);
  strcpy(direc->origen, "Users/Joel_/Desktop/origen");
  strcpy(direc->destino, "Users/Joel_/Desktop/destino");
  return 0;
}