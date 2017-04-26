#ifndef _MATRIXOP_H_
#define _MATRIXOP_H_
#define TAM 10
#define BUFFERSIZE 700

void
llenarMatrices();
double**
leerMatriz1();
double**
leerMatriz2();
double 
Determinante (double mat[TAM][TAM],int n);
void 
matrizCofactores (double m1[TAM][TAM], int n, double determinante);
void 
matrizCofactores2 (double m1[TAM][TAM], int n, double determinante);
void 
crearArchivo( char* resultado , char* archivo);
void
leerArchivo(char* direccion);
#endif