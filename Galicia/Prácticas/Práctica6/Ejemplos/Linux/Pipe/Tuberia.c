#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define VALOR 1

int main (void)
{
	int desc_arch[2];			//Descriptor de archivo
	char buffer[100];
	if (pipe (desc_arch) != 0)
		exit(1);
	if (fork () == 0)			//Código del proceso hijo
	{
		while (VALOR)
		{
			read (desc_arch[0], buffer, sizeof (buffer));		//Posición 0 del descriptor es para lectura
			printf("Se recibió:\t%s\n", buffer);
		}
	}
	while (VALOR)
	{
		gets (buffer);							//Leemos del teclado
		write (desc_arch[1], buffer, strlen (buffer) + 1);		//Posición 1 del descriptor es para escritura
	}
}