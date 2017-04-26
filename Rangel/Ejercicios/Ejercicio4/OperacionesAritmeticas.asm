section .data
	msgIncremento db 'El incremento de 1 es: ',0xA,0xD
	longitud1 equ $ - msgIncremento
	msgDecremento db 0xA,0xD,'El decremento de 2 es: ',0xA,0xD
	longitud2 equ $ -msgDecremento
	msgSuma db 0xA,0xD,'La suma de 1 + 2 es: ',0xA,0xD
	longitud3 equ $ - msgSuma
	msgResta db 0xA,0xD,'La resta de 2 - 1 es: ',0xA,0xD
	longitud4 equ $ - msgResta

section .bss				;Sirve para declarar variables no inicializadas
	res resb 1				;A la variable llamada res, reserva espacio de memoria de 1 byte.

section .text
	global _start

_start:
	mov eax,4					;Llamada al sistema 4, "sys_write" para imprimir incremento
	mov ebx,1					;Salida estándar
	mov ecx,msgIncremento 		;Imprime el mensaje 1
	mov edx,longitud1 			;Pasamos la longitud de la cadena
	int 80h

	;INCREMENTO
	mov eax,1					;El registro eax toma el valor de 1
	inc eax						;El registro que toma el valor de 1, se incrementa
	add eax,'0'					;Toma representación de ASCII
	mov [res],eax				;Como res es un espacio de memoria y no un registro, se encierra entre corchetes
	mov eax,4					;Llamada al sistema 4, "sys_write"
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h	

	mov eax,4					;Llamada al sistema "sys_write" para imprimir decremento
	mov ebx,1
	mov ecx,msgDecremento
	mov edx,longitud2
	int 80h

	;DECREMENTO
	mov eax,2					;El registro eax toma el valor de 2
	dec eax
	add eax,'0'
	mov [res],eax
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h

	mov eax,4					;Llamada al sistema "sys_write" para imprimir suma
	mov ebx,1
	mov ecx,msgSuma
	mov edx,longitud3
	int 80h

	;SUMA
	mov eax,1
	mov ebx,2
	add eax,ebx					;Se suma el valor del registro eax y el valor de del registro ebx
	mov eax,'0'
	mov [res],eax
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h

	mov eax,4					;Llamada al sistema "sys_write" para imprimir resta
	mov ebx,1
	mov ecx,msgResta
	mov edx,longitud3
	int 80h

	;RESTA
	mov eax,2
	mov ebx,1
	add eax,ebx					;Se resta el valor del registro eax y el valor de del registro ebx
	mov eax,'0'
	mov [res],eax
	mov eax,4
	mov ebx,1
	mov ecx,res
	mov edx,1
	int 80h

	;FINALIZAMOS EL PROGRAMA
	mov eax,1
	mov ebx,0
	int 80h