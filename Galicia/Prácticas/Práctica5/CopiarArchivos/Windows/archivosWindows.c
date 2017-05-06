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
  DWORD  dwBytesRead, dwBytesWritten, dwPos, tipoArchivo, idHilo;
  BYTE   buffer[BUF_SIZE];
  HANDLE manHilo;                   //Manejador del hilo
  HANDLE input_fd, output_fd;             //Manejadores archivo de entrada y de salida
  directorios * direc = (directorios *)lpParam;         //Casteo de argumentos a tipo directorios
  DIR * dir;                            //Apuntador de tipo struct DIR
  ssize_t ret_in, ret_out;               //Número de bytes regresados por read() y write()
  struct dirent *dirEntry;              //Apuntador de tipo struct dirent
  struct stat inode;                    //Estructura de tipo struct stat
  char rutaOrigen[300], rutaDestino[300];
  dir = opendir (direc->origen);
  if (dir == 0)                     //Si hay error al abrir el directorio
  {
    perror ("\nError al abrir el directorio: ");
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
        printf ("\nSe encontr%c el directorio: %s\n", 162, direc2->origen);
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
    }else if (tipoArchivo == FILE_ATTRIBUTE_ARCHIVE)                            //Si la entrada es un archivo
    {
      //printf("\nArchivo %s\n", dirEntry->d_name);
      sprintf (rutaDestino, "%s/%s", direc->destino, dirEntry->d_name);         //Guardamos la ruta del archivo de origen
      input_fd = CreateFile (rutaOrigen, GENERIC_READ, 0, NULL, OPEN_EXISTING, 
                              FILE_ATTRIBUTE_NORMAL, NULL);         //Abrimos el archivo existente en modo lectura
      if (input_fd == INVALID_HANDLE_VALUE)         //Si ocurre un error al abrir el archivo
      {
        perror("Error al abrir el archivo: ");
        return 0;
      }else             //Si no hay errores al abrir el archivo
      {
        printf("El archivo %s se abri%c correctamente.\n", rutaOrigen, 162);
      }
      output_fd = CreateFile(rutaDestino, FILE_APPEND_DATA, FILE_SHARE_READ, 
                              NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);         //Creamos el archivo en modo escritura
      if (output_fd == INVALID_HANDLE_VALUE)        //Si ocurre un error al abrir el archivo
      {
        perror("Error al crear el archivo: ");
        return 0;
      }else             //Si no hay errores al abrir el archivo
      {
        printf("El archivo %s se cre%c correctamente.\n", rutaDestino, 162);
      }
      //Comenzamos a copiar los archivos dentro de la ruta destino
      while (ReadFile(input_fd, buffer, sizeof(buffer), &dwBytesRead, NULL) && dwBytesRead > 0)         //Mientras haya bytes en el archivo abierto para lectura
      {
        dwPos = SetFilePointer(output_fd, 0, NULL, FILE_END);
        WriteFile(output_fd, buffer, dwBytesRead, &dwBytesWritten, NULL);
      }
    }
  }
  return 0;
}




/*printf("Directorio de origen:\t%s\n",direc->origen);
printf("Directorio de destino:\t%s\n", direc->destino);
strcpy(direc->origen, "Users/Joel_/Desktop/origen");
strcpy(direc->destino, "Users/Joel_/Desktop/destino");*/