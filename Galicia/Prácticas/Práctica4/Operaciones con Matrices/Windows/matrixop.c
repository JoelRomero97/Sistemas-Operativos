#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define TAM 10
#define BUFFERSIZE 700

void
llenarMatrices()
{
	FILE *m1 = fopen("mat1.txt","w");
	FILE *m2 = fopen("mat2.txt","w");
	int mat1[10][10];
	int mat2[10][10];
	srand(time(NULL));
	for (int i = 0; i < TAM; i++)			/*SE GENERAN AMBAS MATRICES ALEATORIAMENTE*/
	{
		for (int j = 0; j < TAM; j++)
		{
			mat1[i][j] = rand()%10;
			mat2[i][j] = rand()%10;
			fprintf(m1,"%d\t",mat1[i][j]);
			fprintf(m2,"%d\t",mat2[i][j]);
		}
		fprintf(m1,"\n");
		fprintf(m2,"\n");
	}
	fclose(m1);
	fclose(m2);
	printf("\nMATRIZ 1\n\n");
	for (int i = 0; i < TAM; i++)			/*SE IMPRIMEN LAS MATRICES A PANTALLA*/
	{
		for (int j = 0; j < TAM; j++)
		{
			printf("%d\t",mat1[i][j]);
		}
		printf("\n");
	}
	printf("\nMATRIZ 2\n");
	for (int i = 0; i < TAM; i++)			
	{
		for (int j = 0; j < TAM; j++)
		{
			printf("%d\t",mat2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

double**
leerMatriz1()
{
	double **mat1;
	mat1 = (double **)malloc(10*sizeof(double *));
	for(int i = 0 ; i < 10 ; i++)
	{
		mat1[i] = (double *)malloc(10*sizeof(double));
	}
	FILE *m1 = fopen("mat1.txt","r");
	for( int i = 0 ; i < 10 ; i++ )
	{
		for( int j = 0 ; j < 10 ; j++ )
		{
			fscanf(m1, "%lf\t",&mat1[i][j] );
		}
	}
	fclose(m1);
	return mat1;
}

double**
leerMatriz2()
{
	double **mat2;
	mat2 = (double **)malloc(10*sizeof(double *));
	for(int i = 0 ; i < 10 ; i++)
	{
		mat2[i] = (double *)malloc(10*sizeof(double));
	}
	FILE *m2 = fopen("mat2.txt","r");
	for( int i = 0 ; i < 10 ; i++ )
	{
		for( int j = 0 ; j < 10 ; j++ )
		{
			fscanf(m2, "%lf\t",&mat2[i][j] );
		}
	}
	fclose(m2);
	return mat2;
}

void 
crearArchivo( char* resultado , char* archivo)
{
	char *username = getenv( "USERNAME" );
	char direccion[100];
	strcpy(direccion,"C:\\Users\\");
	strcat(direccion,username);
	strcat(direccion,"\\Desktop\\");
	strcat(direccion,archivo);
	HANDLE hFile; //Archivo a manejar
	DWORD dwBytesToWrite; //Numero de bytes a escribir
	DWORD dwBytesWritten = 0; //Numero de bytes escritos
	bool bErrorFlag = FALSE; //Bandera de error
	dwBytesToWrite = (DWORD)strlen(resultado);
	printf("\n\tSe ha guardado el archivo en:\n\t%s\n",direccion);
	
	hFile = CreateFile(direccion, // Dirección del archivo
	GENERIC_WRITE, // Apertura para escritura
	0, // No compartir
	NULL, // Seguridad por defecto
	CREATE_ALWAYS, // Sobreescribe el archivo en caso de que exite, si no, crea uno nuevo
	FILE_ATTRIBUTE_NORMAL, // Archivo normal
	NULL); // Sin plantillas de atributos
	
	bErrorFlag = WriteFile(
	hFile, // Abrir archivo a manejar
	resultado, // Información a escribir
	dwBytesToWrite, // Numero de bytes a escribir
	&dwBytesWritten, // Numero de bytes que fueron escritos
	NULL); // Ninguna estructura superpuesta
	if(!bErrorFlag)
		printf("\tError al crear el archivo :(\n\n");
	else
		printf("\tSe escribieron %lu bytes en %s exitosamente.\n\n",dwBytesWritten, direccion);
	CloseHandle(hFile);//Cierra el archivo
}

void
leerArchivo(char* direccion)
{
	HANDLE hFile;								//Manejador de Archivo
    DWORD  dwBytesRead = 0;						//Numero de bytes a leer
    char   ReadBuffer[BUFFERSIZE] = {0};		//Arreglo para guardar el texto a leer
	
	hFile = CreateFile(direccion,             // Direccion del archivo
                       GENERIC_READ,          // Apertura para lectura
                       0,     				  // Compartir para lectura
                       NULL,                  // Seguridad por defect
                       OPEN_EXISTING,         // Archivo existente únicamente
                       FILE_ATTRIBUTE_NORMAL, // archivo normal
                       NULL);                 // Sin atributos
	 
	if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf("Error: no se pudo abrir el archivo %s para lectura.\n", direccion);
		return;
    }
	
	// Lee un caracter menos que el tamaño del buffer para guardar espacio
    // para el caracter NULL de fin 
    
	if( FALSE == ReadFile(hFile, ReadBuffer, BUFFERSIZE-1, &dwBytesRead, NULL) )
    {
        printf("Error: No se pudo leer el archivo.\n GetLastError=%08lu\n", GetLastError());
        CloseHandle(hFile);
        return;
    }
	
    if (dwBytesRead > 0 && dwBytesRead <= BUFFERSIZE-1)
    {
        ReadBuffer[dwBytesRead]='\0'; // caracter NULL 

        printf("Se leyeron %lu bytes del archivo", dwBytesRead);
        printf("\n\n%s\n\n", ReadBuffer);
    }
    else if (dwBytesRead == 0)
    {
        printf("Ne se leyo informacion de %s\n", direccion);
    }
    else
    {
        printf("\n ** Valor inesperado para dwBytesRead ** \n");
    }
    
    CloseHandle(hFile);
}

double 
Determinante (double m1[TAM][TAM],int n)
{
  double s = 1, det = 0;
  int i, j, k, m, x;
  double m2[TAM][TAM];
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
matrizCofactores (double m1[TAM][TAM], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  double m2[TAM][TAM], matrizFactores[TAM][TAM], aux[TAM][TAM], inversa[TAM][TAM];
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
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  /*****************IMPRESION DE LA INVERSA*************/
  strcpy(resultado,"\r\nMATRIZ INVERSA 1 :D\r\n ");
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	strcat(resultado,"\r\n");
  }
  crearArchivo(resultado,"inversa1.txt");
}



void 
matrizCofactores2 (double m1[TAM][TAM], int n, double determinante)
{
  char resultado[700];
  char buffer[8]={};
  int q, m, i, j, k, l;
  double m2[TAM][TAM], matrizFactores[TAM][TAM], aux[TAM][TAM], inversa[TAM][TAM];
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
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      aux[i][j] = matrizFactores[j][i];
    }
  }
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      inversa[i][j] = aux[i][j] / determinante;
    }
  }
  
  /*****************IMPRESION DE LA INVERSA*************/
  strcpy(resultado,"\r\nMATRIZ INVERSA 2 :D\r\n");
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
	  sprintf(buffer,"%.3lf\t",inversa[i][j]);
	  strcat(resultado,buffer);
	  memset(buffer,0,8);
    }
	strcat(resultado,"\r\n");
  }
  crearArchivo(resultado,"inversa2.txt");
}
