segment .data

	msgPrincipal db 0xD,0xA,'CONTADOR DE 0 A 9 :)',0xA,0xD
	longitud1 equ $ - msgPrincipal
	SaltoLinea db 0xA
	longitud2 equ $ - SaltoLinea

segment .bss
	numero resb 1			;Reserva 2 bytes para la variable numero

segment .text
global _start

_start:
	;Impresion mensaje principal
	mov eax,4
	mov ebx,1
	mov ecx,msgPrincipal
	mov edx,longitud1
	int 80h

	mov ecx,10					;El registro ecx toma el valor de 10 para el ciclo
	mov eax,0					;El registro eax toma el valor de 1

	contador:
		push ecx					;Se guarda en la pila el valor de ecx para que el ciclo solo se haga 10 veces

		push eax
		add eax,'0'					;Toma representación de ASCII
		mov [numero],eax			;Como numero es un espacio de memoria y no un registro, se encierra entre corchetes
		mov eax,4					;Llamada al sistema 4, "sys_write"
		mov ebx,1					;Salida Estándar
		mov ecx,numero 				;Imprime la variable numero
		mov edx,1					;Longitud de numero
		int 80h

		mov eax,4
		mov ebx,1
		mov ecx,SaltoLinea
		mov edx,longitud2
		int 80h
		
		pop eax
		inc eax						;El registro que toma el valor de 1, se incrementa

		pop ecx
	loop contador 					;Al terminar el ciclo, se decrementa el registro ecx

	mov eax,4
	mov ebx,1
	mov ecx,SaltoLinea
	mov edx,longitud2
	int 80h

	;FINALIZAMOS EL PROGRAMA
	mov eax,1
	mov ebx,0
	int 80h