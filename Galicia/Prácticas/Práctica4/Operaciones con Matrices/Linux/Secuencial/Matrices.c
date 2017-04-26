#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#define TAM 10

void generarMatrices ();
void suma (float m1[TAM][TAM], float m2[TAM][TAM]);
void resta (float m1[TAM][TAM], float m2[TAM][TAM]);
void multiplicacion (float m1[TAM][TAM], float m2[TAM][TAM]);
void transpuesta (float m1[TAM][TAM], float m2[TAM][TAM]);
float Determinante (float m1[TAM][TAM],int n);
void matrizCofactores (float m1[TAM][TAM], int n, float determinante);		//SE REPITE LA FUNCIÓN PARA QUE SE ESCRIBA
void matrizCofactores2 (float m1[TAM][TAM], int n, float determinante);			//EN DIFERENTES ARCH LA M1 Y LA M2

int main(int argc, char const *argv[])
{
	generarMatrices();
}

void generarMatrices ()
{
	int i, j;
	float determinante, m1[TAM][TAM], m2[TAM][TAM];
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
	suma (m1, m2);
	resta (m1, m2);
	multiplicacion (m1, m2);
	transpuesta (m1, m2);
	determinante = Determinante (m1, TAM);
	if (determinante != 0)
	{
		matrizCofactores (m1, TAM, determinante);
	}else
	{
		printf("La matriz no tiene inversa\n");
	}
	determinante = Determinante (m2, TAM);
	if (determinante != 0)
	{
		matrizCofactores2 (m2, TAM, determinante);
	}else
	{
		printf("La matriz no tiene inversa\n");
	}
}

void suma (float m1[TAM][TAM], float m2[TAM][TAM])
{
	float m3[TAM][TAM];
	int i, j;
	for (i = 0;   i < TAM ;i++)
	{
		for (j = 0;   j < TAM ;j++)
		{
			m3[i][j] = m1[i][j] + m2[i][j];
		}
	}
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
}

void resta (float m1[TAM][TAM], float m2[TAM][TAM])
{
	int i, j;
	float m3[TAM][TAM];
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			m3[i][j] = m1[i][j] - m2[i][j];
		}
	}
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
}

void multiplicacion (float m1[TAM][TAM], float m2[TAM][TAM])
{
	float m3[TAM][TAM];
	int i, j, k;
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
}

void transpuesta (float m1[TAM][TAM], float m2[TAM][TAM])
{
	int i, j;
	float m3[TAM][TAM], aux[TAM][TAM];
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			m3[i][j] = m1[j][i];
			aux[i][j] = m2[j][i];
		}
	}
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