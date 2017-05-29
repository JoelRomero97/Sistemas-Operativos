#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define TAM 10

void generaMatriz(int matriz[TAM][TAM])
{
    int i, j;
    srand(time(NULL));
    for (i = 0; i < TAM; i++)
    {
        for (j = 0; j < TAM; j++)
        {
            matriz[i][j] = rand()%10;
        }
    }
}

void copiarMatriz(int m1 [TAM][TAM],int m2[TAM][TAM])
{
    int i, j;
	for (i = 0; i < TAM; i++)
    {
		for (j = 0; j < TAM; j++)
        {
			m1[i][j] = m2[i][j];
        }
    }
}

void sumaMatrices(int m1 [TAM][TAM],int m2[TAM][TAM],int mResult[TAM][TAM])
{
	for (int i = 0; i < TAM; i++)
    {
		for (int j = 0; j < TAM; j++)
        {
			mResult[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void multiplicaMatrices(int m1 [TAM][TAM],int m2[TAM][TAM],int mResult[TAM][TAM])
{
	for (int i = 0; i < TAM; i++)
    {
		for (int j = 0; j < TAM; j++)
        {
			for (int k = 0; k < TAM; k++)
            {
				mResult[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void imprimeMatriz(int matriz[TAM][TAM])
{
    int i, j;
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int determinante(int matriz[TAM][TAM],int size)
{
    int s=1,det=0,m_minor[TAM][TAM];
    int i,j,m,n,c;
    if (size==1)
    	return (matriz[0][0]);
    else
    {
        det=0;
        for (c=0;c<size;c++)
        {
            m=0;
            n=0;
            for (i=0;i<size;i++)
                for (j=0;j<size;j++)
                {
                    m_minor[i][j]=0;
                    if (i != 0 && j != c)
                    {
                        m_minor[m][n]=matriz[i][j];
                        if (n<(size-2))
                            n++;
                        else
                        {
                            n=0;
                            m++;
                        }
                    }
                }
            det=det + s * (matriz[0][c] * determinante(m_minor,size-1));
            s=-1 * s;
        }
    }
    return (det);
}

void cofactor(int matriz[TAM][TAM],int cofac[TAM][TAM],int size)
{
    int m_cofactor[TAM][TAM];
    int p,q,m,n,i,j;
    for (q=0;q<size;q++)
        for (p=0;p<size;p++)
        {
            m=0;
            n=0;
            for (i=0;i<size;i++)
                for (j=0;j<size;j++)
                    if (i != q && j != p){
                        m_cofactor[m][n]=matriz[i][j];
                        if (n<(size-2))
                        n++;
                        else{
                            n=0;
                            m++;
                        }
                    }

            cofac[q][p]=pow(-1,p+q) * determinante(m_cofactor,size-1);
        }  
}

void inversa(int matriz[TAM][TAM],float m_inversa[TAM][TAM],int size)
{
    int i,j;
    int m_transpuesta[TAM][TAM],matriz_cofactor[TAM][TAM],d;
    
    cofactor(matriz,matriz_cofactor,TAM);

    for (i=0;i<size;i++)
    	for (j=0;j<size;j++)
    		m_transpuesta[i][j]=matriz_cofactor[j][i];
    d=determinante(matriz,size);
    for (i=0;i<size;i++)
    	for (j=0;j<size;j++)
    		m_inversa[i][j]=(float)m_transpuesta[i][j] / (float)d;
}

void creaArchivo(float inversa[TAM][TAM],char nombre[128])
{
	int arch, i, j;
	char c[10];
	char tab = '\t', ln='\n';
	arch = creat(nombre,0777);
	if(arch == -1)
		perror("Error  al abrir fichero:");
	else{
		for (i = 0; i < TAM; i++)                   //Guarda el contenido leído en el archivo destino
        {
	    	for (j = 0; j < TAM; j++)
            {
	    			sprintf(c,"%.2f",inversa[i][j]);
	    			write(arch,c,strlen(c));	
					write(arch,&tab,sizeof(tab)); 
			}
			write(arch,&ln,sizeof(ln));
		}
		close(arch);
        printf("Se creó correctamente el archivo en la ruta:\t%s\n", nombre);
	}
}