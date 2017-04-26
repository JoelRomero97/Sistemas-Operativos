#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#define TAM 10

float Determinante (float m1[TAM][TAM],int n);
void matrizCofactores (float m1[TAM][TAM], int n, float determinante);		//SE REPITE LA FUNCIÓN PARA QUE SE ESCRIBA
void matrizCofactores2 (float m1[TAM][TAM], int n, float determinante);			//EN DIFERENTES ARCH LA M1 Y LA M2

int main(int argc, char const *argv[])
{
	int id_proc,i,j,status,procesos,l,k;
	float determinante, m1[TAM][TAM], m2[TAM][TAM],m3[TAM][TAM],aux[TAM][TAM];
	system("clear");
	printf("\t\tOPERACIONES CON MATRICES CUADRADAS :)\n\n");
	srand(time(NULL));
	for (i = 0; i < TAM; i++)			/*SE GENERAN AMBAS MATRICES ALEATORIAMENTE*/
	{
		for (j = 0; j < TAM; j++)
		{
			m1[i][j] = rand()%10;
			m2[i][j] = rand()%10;
		}
	}

	/********************IMPRIMIMOS LAS MATRICES INICIALES******************/
	printf("MATRIZ 1\n");
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			printf("%.0f\t",m1[i][j]);
		}
		printf("\n");
	}

	printf("\n\n\n");
	printf("MATRIZ 2\n");
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			printf("%.0f\t",m2[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");

	/************************************************************************/


	
	for (procesos = 0; procesos < 7; procesos++)
	{
		id_proc = fork();
		if (id_proc == 0)		//CÓDIGO DEL PROCESO HIJO
		{
			if (procesos == 0)					//REALIZAMOS LA SUMA DE MATRICES
			{
				for (i = 0;   i < TAM ;i++)
				{
					for (j = 0;   j < TAM ;j++)
					{
						m3[i][j] = m1[i][j] + m2[i][j];
					}
				}

				/***************************IMPRESIÓN DE LA SUMA***************************/

				printf("SUMA\n");
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						printf("%.0f\t",m3[i][j]);
					}
					printf("\n");
				}
				printf("\n\n\n");
				/***************************IMPRESIÓN DE LA SUMA***************************/


				exit(0);
			}else if (procesos == 1)			//REALIZAMOS LA RESTA DE MATRICES
			{
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						m3[i][j] = m1[i][j] - m2[i][j];
					}
				}

				/***************************IMPRESIÓN DE LA RESTA***************************/
				
				printf("RESTA\n");
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						printf("%.0f\t",m3[i][j]);
					}
					printf("\n");
				}
				printf("\n\n\n");
				/***************************IMPRESIÓN DE LA RESTA***************************/


				exit(0);
			}else if (procesos == 2)			//REALIZAMOS LA MULTIPLICACIÓN DE MATRICES
			{
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						m3[i][j] = 0;
						for (k = 0; k < TAM; k++)
						{
							m3[i][j] += (m1[i][k]*m2[k][j]);
						}
					}
				}

				/***************************IMPRESIÓN DE LA MULTIPLICACIÓN***************************/
				
				printf("MULTIPLICACIÓN\n");
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						printf("%.0f\t",m3[i][j]);
					}
					printf("\n");
				}
				printf("\n\n\n");
				/***************************IMPRESIÓN DE LA MULTIPLICACIÓN***************************/
				

				exit(0);
			}else if (procesos == 3)			//REALIZAMOS LA TRANSPUESTA DE CADA MATRIZ
			{
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						m3[i][j] = m1[j][i];
						aux[i][j] = m2[j][i];
					}
				}

				/***************************IMPRESIÓN DE TRANSPUESTA MATRIZ 1***************************/

				printf("TRANSPUESTA DE MATRIZ 1\n");
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						printf("%.0f\t",m3[i][j]);
					}
					printf("\n");
				}
				printf("\n\n\n");
				/***************************IMPRESIÓN DE TRANSPUESTA MATRIZ 1***************************/
				/***************************IMPRESIÓN DE TRANSPUESTA MATRIZ 2***************************/
				
				printf("TRANSPUESTA DE MATRIZ 2\n");
				for (i = 0; i < TAM; i++)
				{
					for (j = 0; j < TAM; j++)
					{
						printf("%.0f\t",aux[i][j]);
					}
					printf("\n");
				}
				printf("\n\n\n");
				/***************************IMPRESIÓN DE TRANSPUESTA MATRIZ 2***************************/
				exit(0);
			}else if (procesos == 4)			//REALIZAMOS LA INVERSA DE LA MATRIZ 1
			{
				determinante = Determinante (m1, TAM);
				if (determinante != 0)
				{
					matrizCofactores (m1, TAM, determinante);
				}else
				{
					printf("La matriz no tiene inversa\n");
				}
				exit(0);
			}else if (procesos == 5)			//REALIZAMOS LA INVERSA DE LA MATRIZ 2
			{
				determinante = Determinante (m2, TAM);
				if (determinante != 0)
				{
					matrizCofactores2 (m2, TAM, determinante);
				}else
				{
					printf("La matriz no tiene inversa\n");
				}
				exit(0);
			}else						//LEEMOS LOS ARCHIVOS Y LOS MOSTRAMOS AL USUARIO
			{
				exit(0);
			}
		}else					//CÓDIGO DEL PROCESO PADRE
		{
			while (wait(&status)>0);
		}
	}
		exit(0);
}

float Determinante (float m1[TAM][TAM],int n)
{
  float s = 1, det = 0;
  int i, j, k, m, x;
  float m2[TAM][TAM];
  if (n == 1)
  {
    return m1[0][0];
  }else
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
            }else
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

void matrizCofactores (float m1[TAM][TAM], int n, float determinante)
{
  float m2[TAM][TAM], matrizFactores[TAM][TAM], aux[TAM][TAM], inversa[TAM][TAM];
  int q, m, i, j, k, l;
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
            }else
            {
              q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k) * Determinante (m2, n-1));
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
  printf("MATRIZ INVERSA :D\n\n\n");
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      printf("%.3f\t", inversa[i][j]);
    }
    printf("\n");
  }
  printf("\n\n\n");
}

void matrizCofactores2 (float m1[TAM][TAM], int n, float determinante)
{
  float m2[TAM][TAM], matrizFactores[TAM][TAM], aux[TAM][TAM], inversa[TAM][TAM];
  int q, m, i, j, k, l;
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
            }else
            {
              q = 0; m++;
            }
          }
        }
      }
      matrizFactores[l][k] = (pow(-1, l + k) * Determinante (m2, n-1));
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
  printf("MATRIZ INVERSA 2 :D\n\n\n");
  for (i = 0; i < TAM; i++)
  {
    for (j = 0; j < TAM; j++)
    {
      printf("%.3f\t", inversa[i][j]);
    }
    printf("\n");
  }
  printf("\n\n\n");
}