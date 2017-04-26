#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int id_proceso,i,j,k,status,n;
	system("clear");
	printf("\n\nPID\t\tPPID\n\n");
	for(i = 0; i<10 ; i++)
	{
		id_proceso = fork();
		if(id_proceso == 0)								//SI ES PROCESO HIJO
		{
			printf("%d\t\t%d\n",getpid(),getppid());
			if(i == 0||i == 9)
			{
				n = 5;
			}else if(i == 1||i == 8)
			{
				n = 4;
			}else if(i == 2||i == 7)
			{
				n = 3;
			}else if(i == 3||i == 6)
			{
				n = 2;
			}else
			{
				n = 2;
			}
			for(j = 0; j < n; j++)					//CREA UN N HIJOS, CADA UNO ES PADRE DEL SIGUIENTE
			{
				id_proceso = fork();
				if(id_proceso == 0)					//SI ES PROCESO HIJO
				{
					printf("%d\t\t%d\n", getpid(),getppid());
					if((j == (n-1))&&(i != 4)&&(i != 5))					//QUIERE DECIR QUE YA ES EL ÚLTIMO
					{
						for (k = 0; k < n; k++)						//CREA LOS ÚLTIMOS N HIJOS DE UN PADRE
						{
							id_proceso = fork();
							if(id_proceso == 0)						//SI ES PROCESO HIJO
							{
								printf("%d\t\t%d\n", getpid(),getppid());
								exit(0);
							}else							//SI ES PROCESO PADRE
							{
								while(wait(&status)>0);
								printf("%d\t\t%d\n", getpid(),getppid());
							}
						}
					}
				}else
				{
					while(wait(&status)>0);				//ESPERA A QUE SE TERMINEN DE CREAR LOS HIJOS
					printf("%d\t\t%d\n",getpid(),getppid());					
					exit(0);			
				}
			}
			exit(0);
		}else											//SI ES PROCESO PADRE
		{
			while(wait(&status)>0);					//ESPERA A QUE SE TERMINEN DE CREAR LOS HIJOS
			printf("%d\t\t%d\t<-SOY EL PROCESO PADRE PRINCIPAL\n\n",getpid(),getppid());					
			//exit(0);						//PONERLO PARA MOSTRAR SOLO LA PRIMER RAMA
		}
	}
	exit(0);					//PONERLO PARA MOSTRAR EL ÁRBOL COMPLETO
}