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
#define BUF_SIZE 8192		//Definimos un tamaño de búffer para la lectura de archivos

DWORD WINAPI hiloDirectorio (LPVOID lpParam);

typedef struct Directorios     //Definimos la estructura de argumentos para la función del hilo
{
  char origen[500];     //Ruta del directorio de origen
  char destino[500];    //Ruta del directorio destino
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
	directorios * dir = (directorios *) malloc (sizeof (directorios));
  printf ("Ejemplo de ruta: /Users/NombreUsuario/Desktop/CarpetaACopiar\n\n");
  printf ("Ingresa la ruta donde se encuentran los archivos a copiar:\t");
  scanf ("%s", dir->origen);
  printf ("Ingresa la ruta donde se van a copiar los archivos:\t");
  scanf ("%s", dir->destino);
  manHilo = CreateThread (NULL, 0, hiloDirectorio, &(*dir), 0, &idHilo);	      //Creación del hilo
  WaitForSingleObject (manHilo, INFINITE);                                  //Esperamos la finalización del hilo
  //printf ("\nOrigen (saliendo del hilo):\t %s\n", dir.origen);
  //printf ("\nDestino (saliendo del hilo):\t %s\n", dir.destino);
  CloseHandle (manHilo);
  return 0;
}

DWORD WINAPI hiloDirectorio (LPVOID lpParam)
{
  DWORD tipoArchivo, idHilo;
  HANDLE manHilo;                   //Manejador del hilo
  HANDLE input_fd, output_fd;             //Manejadores archivo de entrada y de salida
  directorios * direc = (directorios *)lpParam;         //Casteo de argumentos a tipo directorios
  DIR * dir;                            //Apuntador de tipo struct DIR
  ssize_t ret_n, ret_out;               //Número de bytes regresados por read() y write()
  struct dirent *dirEntry;              //Apuntador de tipo struct dirent
  struct stat inode;                    //Estructura de tipo struct stat
  char rutaOrigen[300], rutaDestino[300], buffer[BUF_SIZE];
  dir = opendir (direc->origen);
  if (dir == 0)                     //Si hay error al abrir el directorio
  {
    perror ("\nError al abrir el directorio");
    exit(1);
  }else                             //Si se abre correctamente el directorio
  {
    printf("\nEl directorio '%s' se abri%c correctamente.\n",direc->origen, 162);
  }
  while ((dirEntry = readdir (dir)) != 0)           //Mientras haya contenido en el directorio
  {
    sprintf (rutaOrigen, "%s/%s", direc->origen, dirEntry->d_name);           //Guardamos la ruta de origen de cada entrada leída en rutaOrigen
    tipoArchivo = GetFileAttributes (rutaOrigen);
    if (tipoArchivo == FILE_ATTRIBUTE_DIRECTORY)          //Si es un directorio
    {
      int nuevoDir;
      directorios * direc2 = (directorios *) malloc (sizeof (directorios));
      sprintf (direc2->origen, "%s/", rutaOrigen);                 //Almacenamos la nueva ruta de origen para el hilo
      sprintf (direc2->destino, "%s/%s/", direc->destino, dirEntry->d_name);               //Almacenamos la nueva ruta de destino para el hilo
      if (dirEntry->d_name[0] != '.')               //Si no es un archivo oculto
      {
        printf ("\nSe encontro el directorio: %s\n",direc2->origen);
        nuevoDir = mkdir (direc2->destino);      //Creamos el directorio en la carpeta destino
        if (nuevoDir != 0)
        {
          printf ("\nError al crear el directorio\n");
          return 0;
        }
        printf ("Creando hilo para su ejecucion\n");
        manHilo = CreateThread (NULL, 0, hiloDirectorio, &(*direc2), 0, &idHilo);       //Creación del hilo
        WaitForSingleObject (manHilo, INFINITE);                                  //Esperamos la finalización del hilo
      }
    }else if (tipoArchivo == FILE_ATTRIBUTE_ARCHIVE)
    {
      //printf("\nArchivo %s\n", dirEntry->d_name);
    }
  }
  return 0;
}




/*printf("Directorio de origen:\t%s\n",direc->origen);
printf("Directorio de destino:\t%s\n", direc->destino);
strcpy(direc->origen, "Users/Joel_/Desktop/origen");
strcpy(direc->destino, "Users/Joel_/Desktop/destino");*/