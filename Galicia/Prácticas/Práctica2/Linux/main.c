#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "funciones.h"


int main(int argc, char *argv[])
{
	crearDirectorioConArchivos();
	return 0;
}
