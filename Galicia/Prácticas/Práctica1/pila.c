#include "pila.h"
#include <stdlib.h>

NODO pop(pila *s)
{
	NODO copia;
	copia = **s;
	free(*s);
	*s = copia.sig;
	copia.sig = NULL;
	return copia;
}
mensaje push(pila *s,NODO D)
{
	pila copia = (pila)malloc(sizeof(NODO));
	if(copia == NULL)
		return NO_MEMORY;
	*copia = D;
	if(empty(*s))
		copia->sig = NULL;
	 else
		copia->sig = *s;
    *s = copia;
	return OK;
}
NODO top(pila s)
{
	NODO copia;
	copia = *s;
	copia.sig = NULL;
	return copia;
}
void ini_pila(pila *s)
{
	*s = NULL;
}
booleano empty(pila s)
{
	if(s==NULL)
		return TRUE;
	return FALSE;
}
void lib_pila(pila *s)
{
	while (!empty(*s))
	{
		pop(s);
	}
}

