#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#define TAM 100

int otraVez ();
void balanceo(FILE *pt);
void TH(int N, char O[], char A[], char D[]);
void conversion(char * inf, char * pos);
int prec_opr(char L,char G);
void calculo(char * pos);
void asteriscos(int x);

int main() 
{
	int resp,num,opc,ast;
	char A[10]="Auxiliar", O[10]="Inicio", D[10]="Destino", inf[TAM], pos[TAM];
	FILE *pt;
	while(opc!=2)
	{
		system("cls");
		printf("\n\n\t\t\tMENU\n\n\n");
		printf("1. Balanceo de par%cntesis.\n",130);
		printf("2. Torres de Hanoi.\n");
		printf("3. Evaluaci%cn de cadenas.\n",162);
		printf("4. Asteriscos.\n");
		printf("5. Salir.\n\n");
		scanf("%d",&resp);
		system("cls");
		switch(resp)  
		{
			case 1: 
				printf("\n\n\t\tBALANCEO:\n\n");
				pt=fopen("archivo.txt","r");
				balanceo(pt);
				printf("\n\n\n");
				opc = otraVez();
				break;
			case 2: 
				printf ("\nIngrese el n%cmero de discos para las torres de hanoi\n",163);
				scanf ("%d",&num);
				TH(num, O, A, D);
				printf("\n\n\n");
				opc = otraVez();
				break;
			case 3: 
				printf("\nIngrese la expresi%cn a evaluar:\t",162);
				scanf("%s",inf);
	      		conversion(inf,pos);
	      		calculo(pos);
	      		printf("\n\n\n");
	      		opc = otraVez();
				break;
			case 4: 
				printf("\n\nIngrese el numero de asteriscos:\t");
				scanf("%d",&ast);
				asteriscos(ast);
				printf("\n\n\n");
				opc = otraVez();
				break;
			case 5: 
				return 0;
				break;
		}
}
	return 0;
}

int otraVez()
{
	int x;
	printf("\n\n%cDesea hacer alguna otra operaci%cn?",168,162);
	printf("\n\n1.SI\t\t\t2.NO\n\n");
	scanf("%d",&x);
	return x;
}

void balanceo(FILE *pt)
{
	int linea=1;
	char c;
	pila s;
	NODO D;
	ini_pila(&s);
	c=fgetc(pt);
	while (c!=EOF)
	{		
		switch (c)
		{
			case '(' : case '[' : case '{':
				D.LL=c;
				D.Lg=linea;
				push(&s,D);
				break;
			case ')' : case ']' : case '}':
				if(empty(s))
				{
					printf("\n\nFalta signo de apertura en la linea\t %d\n\n",linea);
					exit(0);
					break;
				} else 
				{
					D=top(s);
					if((D.LL=='{'&&c=='}')||(D.LL=='['&&c==']')||(D.LL=='('&&c==')'))
						pop(&s);
					else
					{
						printf("\n\nError de correspondencia en la linea\t %d\n\n",linea);
						exit(0);
				    }
				}
				break;
			case '\n': linea ++;	
		}//SWITCH
	  c=fgetc(pt);	
	} // WHILE
	if(empty(s))
	{
		printf("\n\nArchivo balanceado\n");
	}
	else 
	{
		printf("\n\nError, falta signo de cierre en la linea %d\n\n",s->Lg);
		exit(0);
	}
	fclose(pt);
	printf("\n\n\n");	
}

void TH(int N, char O[], char A[], char D[])
{
	if(N==1)
	{
		printf ("Mover disco %d de %s a %s \n", N, O, D);
	}else
	{
		TH(N-1, O, D, A);
		printf ("Mover disco %d de %s a %s \n", N, O, D);
		TH(N-1, A, O, D);
	}
}

void conversion(char * inf, char * pos)
{
	int i=0,j=0;
	pila opr;
	NODO D;
	ini_pila(&opr);
	int pre=0;
	while(inf[i]!='\0')
	{
		if (inf[i]>='0'&&inf[i]<='9')  //ES UN NUMERO
		{
			pos[j++]=inf[i++];	
		}else if ( inf[i] == '(' )   //PARENTESIS QUE ABRE
		{
		     D.op=inf[i++];
		     push(&opr,D); 			 
		}else if (inf[i] == '+'||inf[i] =='-'|| inf[i] =='*'||inf[i] == '/') //OPERADOR
		{
		   if( empty(opr) )  //PRIMER OPERADOR
		   {
				D.op=inf[i++];
				push(&opr,D);
			}else 
			{ // 1
				pre=prec_opr(inf[i],top(opr).op);
				if(pre==1)  //LEIDO < GUARDADO
				{   
		   			while(!empty(opr)&&top(opr).op!='(')
					{
	   			    	pos[j++]=pop(&opr).op;
					}
  					D.op=inf[i++];
  					push(&opr,D);
  				}else if(pre==2)  //LEIDO = GUARDADO
	 		 	{   
   		 			pos[j++]=pop(&opr).op;
				  	D.op=inf[i++];
  				    push(&opr,D);
				}else if(pre==3)  //LEIDO > GUARDADO
  		  		{ 
       	 	  	 	D.op=inf[i++];
	  		        push(&opr,D);
				}
			} // else 1
		} // IF operador
		else if ( inf[i] == ')' )  //PARENTESIS QUE CIERRA
		{
			while(!empty(opr)&&top(opr).op!='(')
			{
				pos[j++]=pop(&opr).op;
			}
			pop(&opr).op;				
			i++;
		}	
	}//WHILE
	while(!empty(opr))
	{
		pos[j++]=pop(&opr).op;
	}
	pos[j]='\0';
	//puts(pos);	
} // pos2inf

int prec_opr(char L,char G)
{
   int l,g;
	if(L=='+'||L=='-')
	{
		l=1;
	}else if(L=='*'||L=='/')
	{
		l=2;
	}
	if(G=='+'||G=='-')
	{
 	   g=1;
	}else if(G=='*'||G=='/')
	{
 	  g=2;
	}
	if(l-g==0)
	    return 2;
	if(l-g<0)
        return 1;
    return 3;
}

void calculo(char * pos)
{
	char c[10];
	int i=0;
	float a1=0;
	float a2=0;
	float x=0;
	pila opr;
	ini_pila(&opr);
	NODO D;
	do
	{
		if(pos[i]>='0' && pos[i]<='9')
		{
			c[0]=pos[i];
    		D.num=atoi(c);
    		push(&opr,D);
		}
		if (pos[i] == '+'|| pos[i] == '-'|| pos[i] == '*'|| pos[i] == '/')
		{
			if (pos[i] == '+')
			{
				a2=pop(&opr).num;
				a1=pop(&opr).num;
				x=(a1+a2);
				D.num=x;
				push (&opr, D);
			}
			if (pos[i] == '-')
			{
				a2=pop(&opr).num;
				a1=pop(&opr).num;
				x=(a1-a2);
				D.num=x;
				push (&opr, D);
			}
			if (pos[i] == '*')
			{
				a2=pop(&opr).num;
				a1=pop(&opr).num;
				x=(a1*a2);
				D.num=x;
				push (&opr, D);
			}
			if (pos[i] == '/')
			{
				a2=pop(&opr).num;
				a1=pop(&opr).num;
				if(a2==0)
				{
					x=111;
					break;
				}else
				{
					x=(a1/a2);
					D.num=x;
					push (&opr, D);
				}
			}
		}
		i++;
	}while(pos[i]!=00);
	if(x==111)
	{
		printf("El resultado es una indeterminacion\n");
	}else
	{
		x=pop(&opr).num;
		printf("El resultado de la expresion es: %.2f\n", x);
	}
}

void asteriscos(int NumeroDeAsteriscosHorizontales)
{
	FILE *ptr_archivo;
	char nombreFichero [] = "Asteriscos.txt";
	int i,j,NumeroDeEspaciosFuera,NumeroDeEspaciosDentro, NumeroDeAsteriscosDentro = 1, acum1 = 0;
	if((ptr_archivo = fopen(nombreFichero,"w+")) == NULL)
	{
		printf("No se ha podido abrir el archivo %s\n",nombreFichero);
	}
	NumeroDeEspaciosFuera = (NumeroDeAsteriscosHorizontales/2);
	while(NumeroDeEspaciosFuera != 0)
	{
		NumeroDeEspaciosDentro = (NumeroDeEspaciosFuera*2);
		for(i = 1; i <= NumeroDeEspaciosFuera;i++)
		{
			printf(" ");
			fwrite(" ",sizeof(char),1,ptr_archivo);
			if(i == NumeroDeEspaciosFuera)
			{
				printf("*");
				fwrite("*",sizeof(char),1,ptr_archivo);
				if(acum1 ==0)
				{
					for(j = 1; j <= NumeroDeEspaciosDentro;j++)
					{
						printf(" ");
						fwrite(" ",sizeof(char),1,ptr_archivo);
						if(j == NumeroDeEspaciosDentro)
						{					
							printf("*");
							fwrite("*",sizeof(char),1,ptr_archivo);
							NumeroDeAsteriscosDentro = NumeroDeAsteriscosDentro+2;
							i = NumeroDeAsteriscosDentro;
							for(i = 1;i <= NumeroDeEspaciosFuera;i++)
							{
								printf(" ");
								fwrite(" ",sizeof(char),1,ptr_archivo);
							}
						}
					}
					acum1++;
				}else
				{
					for(i = 0; i < acum1; i++)
					{
						printf(" ");
						fwrite(" ",sizeof(char),1,ptr_archivo);
					}
					printf("*");
					fwrite("*",sizeof(char),1,ptr_archivo);
					acum1 = acum1 + 2;
					for(j = 1; j <= NumeroDeEspaciosDentro;j++)
					{
						printf(" ");
						fwrite(" ",sizeof(char),1,ptr_archivo);
						if(j == NumeroDeEspaciosDentro)
						{
							for(i = 0; i < acum1;i++)
							{
								printf("*");
								fwrite("*",sizeof(char),1,ptr_archivo);
							}
							NumeroDeAsteriscosDentro = NumeroDeAsteriscosDentro+2;
							i = NumeroDeAsteriscosDentro;
							for(i = 1;i <= NumeroDeEspaciosFuera;i++)
							{
								printf(" ");
								fwrite(" ",sizeof(char),1,ptr_archivo);
							}
						}
					}
				}
			}
		}
		printf("\n");
		fwrite("\n",sizeof(char),1,ptr_archivo);
		NumeroDeEspaciosFuera--;
	}	
	while(NumeroDeEspaciosFuera != (NumeroDeAsteriscosHorizontales/2)+1)
	{
		if(NumeroDeEspaciosFuera == 0)
		{
			printf("*");
			fwrite("*",sizeof(char),1,ptr_archivo);
			for(i = 0; i < acum1; i++)
			{
				printf(" ");
				fwrite(" ",sizeof(char),1,ptr_archivo);
			}
			for(i = 0; i <= NumeroDeAsteriscosDentro;i++)
			{
				printf("*");
				fwrite("*",sizeof(char),1,ptr_archivo);
			}
			acum1 = acum1 - 2;
		}else if(NumeroDeEspaciosFuera != (NumeroDeAsteriscosHorizontales/2)+1)
		{
			for(i = 0; i < NumeroDeEspaciosFuera;i++)
			{
				printf(" ");
				fwrite(" ",sizeof(char),1,ptr_archivo);
			}
			printf("*");
			fwrite("*",sizeof(char),1,ptr_archivo);
			for(i = 0; i < acum1;i++)
			{
				printf(" ");
				fwrite(" ",sizeof(char),1,ptr_archivo);
			}
			if((NumeroDeEspaciosFuera*2)+1 != NumeroDeAsteriscosHorizontales)
			{
				printf("*");
				fwrite("*",sizeof(char),1,ptr_archivo);
			}
			for(i = 0; i < (NumeroDeEspaciosFuera*2);i++)
			{
				printf(" ");
				fwrite(" ",sizeof(char),1,ptr_archivo);
			}
			for(i = 0; i < NumeroDeAsteriscosDentro; i++)
			{
				printf("*");
				fwrite("*",sizeof(char),1,ptr_archivo);
			}
			for(i = 0; i < NumeroDeEspaciosFuera; i++)
			{
				printf(" ");
				fwrite(" ",sizeof(char),1,ptr_archivo);
			}
			acum1 = acum1 - 2;
		}
		printf("\n");
		fwrite("\n",sizeof(char),1,ptr_archivo);
		NumeroDeAsteriscosDentro = NumeroDeAsteriscosDentro - 2;
		NumeroDeEspaciosFuera++;
	}
	printf("\n\n%cDesea guardar en un archivo?\n\n1. SI\t\t\t2.NO\n",168);
	scanf("%d",&i);
	fclose(ptr_archivo);
	if(i == 1)
		printf("Archivo guardado como %s\n",nombreFichero);
	remove("Asteriscos.txt");

}
