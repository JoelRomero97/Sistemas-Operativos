/* Programa padre.c */

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

/*
Para mejor visualización del código visitar:
https://github.com/IvanovskyOrtega/Sistemas-Operativos/Practica6

INSTRUCCIONES DE COMPILACIÓN:

gcc padre.c -o padre.exe -lm -Wall
gcc hijo.c -o hijo.exe -Wall
gcc nieto.c -o nieto.exe -Wall

EJECUCIÓN:
padre.exe

*/

struct matrices
{
	int matriz1[10][10];
	int matriz2[10][10];
	int matriz3[10][10];
	char res[14];
};

void llenarMatrices(struct matrices *m);
void imprimirMatriz(struct matrices *m);
void imprimirMatrices(struct matrices *m);
void crearArchivo( char* resultado , char* archivo);
double Determinante (double m1[10][10],int n);
void matrizCofactores (double m1[10][10], int n, double determinante);
void matrizCofactores2 (double m1[10][10], int n, double determinante);

HANDLE hLecturaPipeIn = NULL, hEscrituraPipeIn = NULL;
HANDLE hLecturaPipeOut = NULL, hEscrituraPipeOut = NULL;

int main (int argc, char *argv[])
{
  int i, j;
	printf("***************PADRE************************\n");
   struct matrices mult;/* Declaramos una variable de nuestra estructura matrices */
   struct matrices *res1, *res2; /* Apuntadores donde guardaremos los resultados obtenidos por los procesos hijo y nieto */
   res1 = (struct matrices*)malloc(sizeof(struct matrices)); 
   res2 = (struct matrices*)malloc(sizeof(struct matrices));
   DWORD escritos, leidos; /* Parámetro para las funciones ReadFile y WriteFile */
   llenarMatrices(&mult);	/* Se llenan las matrices 1 y 2 de la variable mult */
   printf("Enviare estas matrices a mi hijo\n");
   imprimirMatrices(&mult);	/* Se imprimen las matrices */
   SECURITY_ATTRIBUTES pipeSeg =
             {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE}; /* Atributos de seguridad */
   /* Creación de las tuberías sin nombre */
   CreatePipe (&hLecturaPipeOut, &hEscrituraPipeOut, &pipeSeg, 0); /* Tubería para salida */
   CreatePipe (&hLecturaPipeIn, &hEscrituraPipeIn, &pipeSeg, 0); /* Tubería para entrada */
   /* Escritura en la tubería sin nombre */
   WriteFile(hEscrituraPipeIn, &mult, sizeof(struct matrices), &escritos, NULL);
   /* Creamos el proceso hijo */
   PROCESS_INFORMATION piHijo;
   STARTUPINFO siHijo;
   GetStartupInfo (&siHijo);
   siHijo.hStdError  = GetStdHandle (STD_ERROR_HANDLE);
   siHijo.hStdOutput = hEscrituraPipeOut;	/* Redirigimos la salida estándar */
   siHijo.hStdInput  = hLecturaPipeIn;	/* Redirigimos la entrada estándar */
   siHijo.dwFlags = STARTF_USESTDHANDLES;
   CreateProcess (
		NULL, 
		 "hijo.exe",	/* Nombre del programa que ejecutará el proceso */
		 NULL,
		 NULL,
         	 TRUE,  /* Hereda el proceso hijo los manejadores de la tubería del padre */
         	 0, 
		 NULL, 
		 NULL, 
		 &siHijo, 
		 &piHijo
	);	 
   WaitForSingleObject (piHijo.hProcess, INFINITE); /* Esperamos a que concluya */
   CloseHandle(piHijo.hThread);
   CloseHandle(piHijo.hProcess); /* Cerramos los manejadores de proceso */
   printf("Han concluido el proceso hijo y nieto\n");
   CloseHandle(hEscrituraPipeIn);  /* Cerramos el manejador de escritura para poder leer */
   ReadFile(hLecturaPipeOut, res1, sizeof(struct matrices), &leidos, NULL);
   ReadFile(hLecturaPipeOut, res2, sizeof(struct matrices), &leidos, NULL); 
   CloseHandle(hLecturaPipeOut); 
   CloseHandle(hEscrituraPipeOut); 
   CloseHandle(hLecturaPipeIn);  /* Cerramos los manejadores restantes de las tuberías  */
   if(strcmp(res1->res,"MULTIPLICACION")==0)
	   printf("Recibi este resultado de mi hijo:\n");
   else if(strcmp(res1->res,"SUMA")==0)
	   printf("Recibi este resultado de mi nieto:\n");
   imprimirMatriz(res1);
   if(strcmp(res2->res,"MULTIPLICACION")==0)
	   printf("Recibi este resultado de mi hijo:\n");
   else if(strcmp(res2->res,"SUMA")==0)
	   printf("Recibi este resultado de mi nieto:\n");
   imprimirMatriz(res2);
   printf("Ahora calculare las inversas de las matrices resultado que recibi:\n");
   double determinante1;
   double determinante2;
   double inv1[10][10]; /* Matrices auxiliares para el calculo de la inversa */
   double inv2[10][10];
   for(i = 0 ; i < 10 ; i++ )
   {
	   for(j = 0 ; j < 10 ; j++ )
	   {
		   inv1[i][j] = res1->matriz3[i][j];
		   inv2[i][j] = res2->matriz3[i][j];
	   }   
   }
   determinante1 = Determinante (inv1, 10);
	if (determinante1 != 0)
	{
		matrizCofactores(inv1, 10, determinante1);
	}
	else
	{
		printf("La matriz 1 no tiene inversa\n");
	}
	determinante2 = Determinante (inv2, 10);
	if (determinante2 != 0)
	{
		matrizCofactores2(inv2, 10, determinante2);
	}
	else
	{
		printf("La matriz 2 no tiene inversa\n");
	}
   printf("He terminado, los resultados se han guardado en su archivo correspondiente.\n");
   return 0;
}

void llenarMatrices(struct matrices *m)
{
  int i, j;
	srand(clock());
	for(i = 0; i < 10 ; i++)
	{
		for ( j = 0 ; j < 10 ; j++ )
		{
			m->matriz1[i][j] = rand()%20;
			m->matriz2[i][j] = rand()%20;
		}
	}
}

void imprimirMatrices(struct matrices *m)
{
  int i, j;
   printf("M1\n");
   for(i = 0; i < 10 ; i++)
	{
		for ( j = 0 ; j < 10 ; j++ )
		{
			 printf("%d\t",m->matriz1[i][j]);
		}
		printf("\n");
	}
    printf("M2\n");
	for(i = 0; i < 10 ; i++)
	{
		for ( j = 0 ; j < 10 ; j++ )
		{
			 printf("%d\t",m->matriz2[i][j]);
		}
		printf("\n");
	}
}

void imprimirMatriz(struct matrices *m)
{
  int i, j;
	printf("%s\n",m->res);
   for(i = 0; i < 10 ; i++)
	{
		for ( j = 0 ; j < 10 ; j++ )
		{
			 printf("%d\t",m->matriz3[i][j]);
		}
		printf("\n");
	}
}

void 
crearArchivo( char* resultado , char* archivo)
{
	HANDLE hFile; 		//Manejador de archivo
	DWORD dwBytesToWrite; 	//Numero de bytes a escribir
	DWORD dwBytesWritten = 0; //Numero de bytes escritos
	bool bErrorFlag = FALSE; //Bandera de error
	dwBytesToWrite = (DWORD)strlen(resultado);
	printf("\n\tSe ha guardado el archivo en:\n\t%s\n",archivo);
	
	hFile = CreateFile(archivo, 		// Dirección del archivo
	GENERIC_WRITE, 			// Apertura para escritura
	0, 					// No compartir
	NULL,					// Seguridad por defecto
	CREATE_ALWAYS, 			// Siempre crear (remplazar si existe)
	FILE_ATTRIBUTE_NORMAL, 		// Archivo normal
	NULL); 					// Sin plantillas de atributos
	bErrorFlag = WriteFile(
	hFile, 					// Abrir archivo a manejar
	resultado, 				// Información a escribir
	dwBytesToWrite, 			// Numero de bytes a escribir
	&dwBytesWritten, 			// Numero de bytes que fueron escritos
	NULL); 					// Ninguna estructura superpuesta
	if(!bErrorFlag)
		printf("\tError al crear el archivo :(\n\n");
	else
		printf("\tSe escribieron %lu bytes en %s exitosamente.\n\n",dwBytesWritten, archivo);
	CloseHandle(hFile);			//Cierra el archivo
}

double 
Determinante (double m1[10][10],int n)
{
  double s = 1, det = 0;
  int i, j, k, m, x;
  double m2[10][10];
  if (n == 1)
  {
    return m1[0][0];
  }
  else
  {
    for (k = 0; k < n; k++)
    {
      m = 0;
      x = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          m2[i][j] = 0;
          if (i != 0 && j != k)
          {
            m2[m][x] = m1[i][j];
            if (x < (n - 2))
            {
              x++;
            }
			else
            {
              x = 0;
              m++;
            }
          }
        }
      }
      det = det + s * (m1[0][k] * Determinante(m2, n-1));
      s *= -1;
    }
  }
  return det;
}

void 
matrizCofactores (double m1[10][10], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  double m2[10][10], matrizFactores[10][10], aux[10][10], inversa[10][10];
  for (l = 0; l < n; l++)
  {
    for (k = 0; k < n; k++)
    {
      m = 0; q = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          if ( i != l && j != k)
          {
            m2[m][q] = m1[i][j];
            if (q < (n-2))
            {
              q++;
            }
			else 
            {
				q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k)* Determinante (m2, n-1));
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  /*****************IMPRESION DE LA INVERSA*************/
  strcpy(resultado,"MATRIZ INVERSA 1\r\n ");
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	strcat(resultado,"\r\n");
  }
  crearArchivo(resultado,"inversaSuma.txt");
}

void 
matrizCofactores2 (double m1[10][10], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  double m2[10][10], matrizFactores[10][10], aux[10][10], inversa[10][10];
  for (l = 0; l < n; l++)
  {
    for (k = 0; k < n; k++)
    {
      m = 0; q = 0;
      for (i = 0; i < n; i++)
      {
        for (j = 0; j < n; j++)
        {
          if ( i != l && j != k)
          {
            m2[m][q] = m1[i][j];
            if (q < (n-2))
            {
              q++;
            }
			else 
            {
				q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k)* Determinante (m2, n-1));
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  
  /*****************IMPRESION DE LA INVERSA*************/
  strcpy(resultado,"MATRIZ INVERSA 2\r\n");
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < 10; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	  strcat(resultado,"\r\n");
  }
  crearArchivo(resultado,"inversaMultiplicacion.txt");
}