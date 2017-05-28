/* Programa nieto.c */

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

void sumarMatrices(struct matrices *m);

int main ()
{
	printf("***************NIETO************************\n");
   struct matrices *suma; /* Apuntador donde guardaremos los datos leídos de laa tubería */
   suma = (struct matrices*)malloc(sizeof(struct matrices));
   DWORD escritos, leidos;	/* Parámetro para ReadFile y WriteFile */
   HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);	/* Obtenemos los manejadores heredados del proceso hijo */
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetStdHandle(STD_INPUT_HANDLE, hStdIn);	/* Establecemos los nuevos manejadores de entrada y salida */
   SetStdHandle(STD_OUTPUT_HANDLE, hStdOut);   
   /* Lectura desde la tubería sin nombre */
   ReadFile(hStdIn, suma, sizeof(struct matrices), &leidos, NULL);	/* Leemos lo que escribió el proceso hijo en la tubería */	
   CloseHandle(hStdIn); /* Cerramos el manejador de entrada */
   sumarMatrices(suma); /* Se realiza la multiplicación de matrices */
   strcpy(suma->res,"SUMA");
   WriteFile(hStdOut, suma, sizeof(struct matrices), &escritos, NULL);	/* Escribimos el resultado en la tubería del hijo */
   CloseHandle(hStdOut);	/* Cerramos el manejador de salida*/
   /* Regresamos a los manejadores default */
   SetStdHandle(STD_INPUT_HANDLE, GetStdHandle(STD_INPUT_HANDLE));
   SetStdHandle(STD_OUTPUT_HANDLE, GetStdHandle(STD_OUTPUT_HANDLE));
   return 0;
}

void sumarMatrices(struct matrices *m)
{
   int i, j;
	for (i = 0;   i < 10 ;i++)
	{
		for (j = 0;   j < 10 ;j++)
		{
			m->matriz3[i][j] = m->matriz1[i][j] + m->matriz2[i][j];
		}
	}
}