#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int id_proc;
	id_proc = fork();
	if (id_proc == 0)
	{
		printf("Soy el proceso hijo\n");
	}else
	{
		printf("Soy el proceso padre\n");
	}
	printf("Mensaje en ambos\n");
	exit(0);
}