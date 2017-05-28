/* Programa hijo.c */

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct matrices
{
	int matriz1[10][10];
	int matriz2[10][10];
	int matriz3[10][10];
	char res[14];
};

void llenarMatrices(struct matrices *m);
void multiplicarMatrices(struct matrices *m);

HANDLE hLecturaPipeIn = NULL, hEscrituraPipeIn = NULL;
HANDLE hLecturaPipeOut = NULL, hEscrituraPipeOut = NULL;

int main ()
{
   struct matrices *mult; /* Apuntador d donde guardaremos los datos leídos de la tubería */
   mult = (struct matrices*)malloc(sizeof(struct matrices));
   struct matrices *suma;/* Apuntador donde se crearán las nuevas matrices para el proceso nieto */
   suma = (struct matrices*)malloc(sizeof(struct matrices));
   llenarMatrices(suma); /* Se llenan las matrices que se enviarán al proceso nieto */
   DWORD escritos, leidos; /* Parámetro para ReadFile y WriteFile */
   HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE); /* Obtenemos los manejadores heredados del proceso padre */
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetStdHandle(STD_INPUT_HANDLE, hStdIn); /* Establecemos los nuevos manejadores de entrada y salida */
   SetStdHandle(STD_OUTPUT_HANDLE, hStdOut);   
   SECURITY_ATTRIBUTES pipeSeg =
             {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE}; 
   ReadFile(hStdIn, mult, sizeof(struct matrices), &leidos, NULL); /* Leemos lo que escribió el proceso padre */
   CloseHandle(hStdIn);  /* Cerramos el manejador de entrada */
   multiplicarMatrices(mult);  /* Multiplicamos las matrices almacenadas en mult que recibimos del proceso padre */
   strcpy(mult->res,"MULTIPLICACION");
/* Creación de la tubería sin nombre */
   CreatePipe (&hLecturaPipeOut, &hEscrituraPipeOut, &pipeSeg, 0); /* Tubería para salida */
   CreatePipe (&hLecturaPipeIn, &hEscrituraPipeIn, &pipeSeg, 0); /* Tubería para entrada */
   /* Escritura en la tubería sin nombre */
   WriteFile(hEscrituraPipeIn, suma, sizeof(struct matrices), &escritos, NULL);
   /* Creamos el proceso hijo */
   PROCESS_INFORMATION piHijo;
   STARTUPINFO siHijo;
   GetStartupInfo (&siHijo);
   siHijo.hStdError  = GetStdHandle (STD_ERROR_HANDLE);
   siHijo.hStdOutput = hEscrituraPipeOut; /* Redirección de la salida estándar */
   siHijo.hStdInput  = hLecturaPipeIn;	/* Redirección de la entrada estándar */
   siHijo.dwFlags = STARTF_USESTDHANDLES;
   CreateProcess (
		NULL, 
		 "nieto.exe",	/* Nombre del programa que ejecutará el proceso */
		 NULL,
		 NULL,
         	 TRUE,  /* Hereda el proceso nieto los manejadores de la tubería del hijo */
         	 0, 
		 NULL, 
		 NULL, 
		 &siHijo, 
		 &piHijo
	);	 
   WaitForSingleObject (piHijo.hProcess, INFINITE); /* Esperamos a que concluya */
   CloseHandle(piHijo.hThread);
   CloseHandle(piHijo.hProcess); /* Cerramos los manejadores de proceso */
   printf("Regresamos al padre\n");
   CloseHandle(hEscrituraPipeIn);  /* Cerramos el manejador de escritura para poder leer */
   ReadFile(hLecturaPipeOut, suma, sizeof(struct matrices), &leidos, NULL); /* Leemos lo que escribió el proceso nieto */
   CloseHandle(hLecturaPipeOut); 
   CloseHandle(hEscrituraPipeOut); 
   CloseHandle(hLecturaPipeIn); /* Cerramos los manejadores restantes  */
   WriteFile(hStdOut, mult, sizeof(struct matrices), &escritos, NULL); /* Escribimos los resultados en la tubería padre */
   WriteFile(hStdOut, suma, sizeof(struct matrices), &escritos, NULL);
   CloseHandle(hStdOut);  /* Cerramos el manejador de salida */
   SetStdHandle(STD_INPUT_HANDLE, GetStdHandle(STD_INPUT_HANDLE));	/* Cambiamos a los manejadores default */
   SetStdHandle(STD_OUTPUT_HANDLE, GetStdHandle(STD_OUTPUT_HANDLE)); 
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

void multiplicarMatrices(struct matrices *m)
{
   int i, j, k;
	for ( i = 0; i < 10; i++)
	{
		for ( j = 0; j < 10; j++)
		{
			m->matriz3[i][j] = 0.0;
			for ( k = 0; k < 10; k++)
			{
				m->matriz3[i][j] += (m->matriz1[i][k]*m->matriz2[k][j]);
			}
		}
	}
}