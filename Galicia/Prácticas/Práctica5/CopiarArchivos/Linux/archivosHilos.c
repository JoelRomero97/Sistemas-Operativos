#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/**
  Autor: Ivan Ortega Victoriano 
  
  Este programa se encarga de copiar los archivos de un directorio especificado
  a otro directorio destino, haciendo uso de hilos y llamadas al sistema del 
  sistema operativo Linux.
  
  Compilación: gcc archivosConHilos.c -o archLinux -lpthread -Wall
  
*/

#define BUF_SIZE 8192		// Se define un tamaño de búffer para la lectura de archivos

struct Directorios		// Definición de la estructura de argumentos para la función del hilo
{
  char origen[500];			// Ruta del directorio de origen
  char destino[500];		// Ruta del directorio destino
};

void * hiloDirectorio (void *arg);

int main (int argc, char **argv)
{
  	pthread_t idThread;		//Identificador del hilo
  	struct Directorios * directorios = (struct Directorios *) malloc (sizeof (struct Directorios));	// Estructura para argumentos del hilo
  	if (argc != 2)
    {
      printf ("Ingresar rutas de los directorios.\n");
      printf ("Ejemplo: /home/NombreUsuario/Descargas/CarpetaCopiar\n");
      printf ("Ingresa la ruta donde se encuentran los archivos a copiar:\t");
      scanf ("%s", directorios->origen);						// Guardamos la ruta de origen
      printf ("\nOrigen:\t %s\n", directorios->origen);
      printf ("\nIngresa la ruta donde se copiarán los archivos:\t");
      scanf ("%s", directorios->destino);						// Guardamos la ruta destino
      printf ("\nDestino:\t %s\n", directorios->destino);
      pthread_create (&idThread, NULL, hiloDirectorio, (void *) directorios);		//Crea el hilo
      pthread_join (idThread, NULL);				//Esperamos a la ejecución del hilo
    }
}

void * hiloDirectorio (void *arg)
{
  	int input_fd, output_fd;				// Descriptores de archivo de entrada y salida
	ssize_t ret_in, ret_out;				// Numero de bytes regresados por read() y write()
	char buffer[BUF_SIZE];				// Buffer de caractéres
	pthread_t idThread;					// Creamos un identificador de hilo
	DIR *dir;								// Apuntador de tipo struct DIR
	struct dirent *dirEntry;				// Apuntador de tipo struct dirent
	struct stat inode;					// Variable de tipo struct stat
	struct Directorios *directorios = NULL;				// Variable de tipo struct Directorios
	directorios = (struct Directorios *) arg;				// Cast de los argumentos a tipo struct Directorios
	char name[300];						// Arreglo que guardará la ruta de cada archivo encontrado en el directorio origen
	char destino[1000];					// Arreglo que guardará la nueva ruta destino para cada archivo encontrado en el directorio origen
	dir = opendir (directorios->origen);					// Abrimos el directorio con la llamada al sistema opendir()
	printf ("\nSe abrira el directorio: %s\n", directorios->origen);
	printf ("\nDirectorio destino: %s\n", directorios->destino);
 	if (dir == 0)							// Error al abrir directorio
    {
      perror ("Error al abrir el directorio");
      exit (1);
    }
  	while ((dirEntry = readdir (dir)) != 0)		// Empezamos a leer el contenido del directorio
    {
      	sprintf (name, "%s/%s", directorios->origen, dirEntry->d_name);	// Almacenamos la ruta de origen de cada entrada leída
	    lstat (name, &inode);				// Llamada al sistema lstat para conocer información de la entrada
	    if (S_ISDIR (inode.st_mode))	// Si la entrada es un directorio
		{
	  		int crearDir;		// Variable para crear el directorio
	  		struct Directorios *directorios2 = (struct Directorios *) malloc (sizeof (struct Directorios));
			sprintf (directorios2->origen, "%s/", name);	// Almacenamos la nueva ruta de origen para el hilo
			sprintf (directorios2->destino, "%s/%s/", directorios->destino, dirEntry->d_name);	// Almacenamos la nueva ruta de destino para el hilo
			if (dirEntry->d_name[0] != '.')	// No se copiarán directorios ocultos
	    	{
		      	printf ("\nSe encontro el directorio: %s\n",
			    directorios2->origen);
		      	crearDir = mkdir (directorios2->destino, 0777);	// Creamos el directorio en la carpeta destino
		      	if (crearDir != 0)
				{
		  			printf ("\nError al crear el directorio\n");
		  			return NULL;										// Se cancela la ejecución del hilo
				}
	      		printf ("Creando hilo para su ejecucion\n");
	      		pthread_create (&idThread, NULL, hiloDirectorio, (void *) directorios2);	// Creación del hilo
	      		pthread_join (idThread, NULL);					// Esperamos a la conclusión del hilo
	    	}
		}else if (S_ISREG (inode.st_mode))						// Si la entrada leída es un registro
		{
		  	printf ("\nArchivo ");
		  	printf (" %s\n", dirEntry->d_name);
		  	sprintf (destino, "%s/%s", directorios->destino, dirEntry->d_name);	// Guardamos la ruta del archivo de origen
		  	// Crea descriptor del archivo de entrada
		  	input_fd = open (name, O_RDONLY);						// Se abre el archivo en modo de lectura
		  	if (input_fd == -1)
	    	{
	      		perror ("open");									// Error al abrir al archivo
	      		return NULL;
	    	}
	  		// Crea descriptor del archivo de salida
	  		output_fd = open (destino, O_WRONLY | O_CREAT, 0644);	// Se abre el archivo en modo de escritura (lo crea si no existe)
	  		if (output_fd == -1)									// Error al abrir el archivo
	    	{
	      		perror ("open");
	      		return NULL;
	    	}
	  		// Iniciamos proceso de copiado
	  		while ((ret_in = read (input_fd, &buffer, BUF_SIZE)) > 0)		// Empezamos a leer el archivo a copiar
	  		{
	    		ret_out = write (output_fd, &buffer, (ssize_t) ret_in);	// Escribimos en el archivo copia
	    		if (ret_out != ret_in)									// Ocurrió un error de escritura
				{
		  			perror ("write");
		  			return NULL;
				}
	  		}
	  		printf ("Se copio correctamente el archivo :)\n");
	  		close (input_fd);								// Cerrar descriptores de archivo 
	  		close (output_fd);							// Cerrar descriptores de archivo 
		}else if (S_ISLNK (inode.st_mode))
		{
			printf ("lnk ");
		}
    }
  	return NULL;
}