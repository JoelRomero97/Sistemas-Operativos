#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	char *argv[3];
	argv[0] = "/home/joel/Desktop/Sistemas Operativos/Galicia/Prácticas/Práctica4/Sustitución de Código/Hola";
	argv[1] = "Desde el proceso hijo";
	argv[2] = NULL;
	if ((pid = fork()) == 0)
	{
		printf("Soy el proceso hijo ejecutando: %s\n", argv[0]);
		execv(argv[0], argv);
	}else
	{
		wait(0);
		printf("Soy el proceso padre\n");
		exit(0);
	}
}