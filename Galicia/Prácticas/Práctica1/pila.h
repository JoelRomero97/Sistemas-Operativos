struct nodo
{
	char LL,op;
	int Lg;
	float num;
	struct nodo *sig;
};
typedef struct nodo NODO;
typedef NODO *pila;
typedef enum m{OK,NO_MEMORY} mensaje;
typedef enum b{FALSE,TRUE} booleano;

NODO pop(pila *s);
mensaje push(pila *s,NODO D);
NODO top(pila s);
void ini_pila(pila *s);
booleano empty(pila s);
void lib_pila(pila *s);
