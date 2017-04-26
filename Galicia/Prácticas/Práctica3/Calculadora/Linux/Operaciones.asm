segment .data
	msg1 db "CALCULADORA",0xA,0xD
	longitud1 equ $-msg1
	msgMultiplicacion db 0xA,0xD,"1.-Mulltiplicacion",0xA,0xD 
	longitud2 equ $-msgMultiplicacion
	msgDivision db "2.-Division" ,0xA,0xD
	longitud3 equ $-msgDivision
	msgSuma db "3.-Suma" ,0xA,0xD
	longitud11 equ $-msgSuma
	msgResta db "4.-Resta" ,0xA,0xD
	longitud12 equ $-msgResta
	msgOpcion db "Digite la opcion: " ,0xA,0xD
	longitud4 equ $-msgOpcion
	msgNumero1 db "Digita el numero 1: ",0xA
	longitud5 equ $-msgNumero1
	msgNumero2 db "Digita el numero 2: ",0xA
	longitud6 equ $-msgNumero2
	msgOpcionInvalida db "Error de opcion",0xA
	longitud7 equ $-msgOpcionInvalida
	msgFinal db 0xD,"Fin de programa",0xA
	longitud8 equ $-msgFinal
	msgResultado db 0xD,"El resultado es: ",0xA
	longitud9 equ $-msgResultado
	SaltoDeLinea db 0xA
	longitud10 equ $-SaltoDeLinea


segment .bss
	opc resb 1  				;Reserva 1 byte de memoria para variable resb
	num1 resw 2 				;Reserva 4 bytes de memoria para variable num1
	num2 resw 2 				;Reserva 4 bytes de memoria para variable num2
	resultado  resw 2 			;Reserva 4 bytes de memoria para variable resultado


segment .text
	global _start

_start:

	;Impresion mensaje 1
	mov eax,4
	mov ebx,1
	mov ecx,msg1
	mov edx,longitud1
	int 80h

	;Impresion mensaje 2
	mov eax,4
	mov ebx,1
	mov ecx,msgMultiplicacion
	mov edx,longitud2
	int 80h
	
	;Impresion mensaje 3
	mov eax,4
	mov ebx,1
	mov ecx,msgDivision
	mov edx,longitud3
	int 80h
	
	;Impresion del mensaje 11
	mov eax,4
	mov ebx,1
	mov ecx,msgSuma
	mov edx,longitud11
	int 80h
	
	;Impresion del mensaje 12
	mov eax,4
	mov ebx,1
	mov ecx,msgResta
	mov edx,longitud12
	int 80h
	
	;Impresion mensaje 4
	mov eax,4
	mov ebx,1
	mov ecx,msgOpcion
	mov edx,longitud4
	int 80h
	
	;Leer la opción
	mov eax,3
	mov ebx,0
	mov ecx,opc
	mov edx,2   							;edx con 2 porque absorbe los caracteres del salto de linea
	int 80h

	;Convierte la opción a valor ASCII
	mov ah,[opc]							;Se mueve opc al registro al
	sub ah, '0'								;conversion del registro a ASCII

	;Buscamos opciones
	cmp ah,1
	je  multiplicar
	cmp ah,2
	je dividir
	cmp ah,3
	je suma
	cmp ah,4
	je resta

	;Si se ingresa otro valor marcara error y la salida
	mov eax,4
	mov ebx,1
	mov ecx,msgOpcionInvalida
	mov edx,longitud7
	int 80h
	jmp salida


multiplicar:
	
	;Impresion de mensaje 5
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero1
	mov edx,longitud5
	int 80h
	
	;Leer num1
	mov eax,3
	mov ebx,0
	mov ecx,num1
	mov edx,2
	int 80h
	
	;Impresion de mensaje 6
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero2
	mov edx,longitud6
	int 80h
	
	;Leer num2
	mov eax,3
	mov ebx,0
	mov ecx,num2
	mov edx,2
	int 80h
	
	;Se imprime mensaje 9
	mov eax, 4
	mov ebx, 1
	mov ecx, msgResultado
	mov edx, longitud9
	int 80h

	;Se mueven los dos numeros a los registros ax por ser de 16 bits
	mov eax,[num1]
	mov ebx,[num2]

	;Se convierten los registros de ASCII a decimal
	sub eax,'0'
	sub ebx,'0'
	
	;Se hace la Mulltiplicacion Ax= DX:Ax * Bx
	mul ebx
	
	;Convierten decimal a ASCII
	add eax,'0'
	
	;Se mueve ax al valor de res
	mov [resultado],eax
	
	;Se imprime el resultado
	mov eax,4
	mov ebx,1
	mov ecx,resultado
	mov edx,1
	int 80h
	jmp salida


dividir:
	
	;Impresion de mensaje 5
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero1
	mov edx,longitud5
	int 80h
	
	;Leer num1
	mov eax,3
	mov ebx,0
	mov ecx,num1
	mov edx,2
	int 80h
	
	;Impresion de mensaje 6
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero2
	mov edx,longitud6
	int 80h
	
	;Leer num2
	mov eax,3
	mov ebx,0
	mov ecx,num2
	mov edx,2
	int 80h
	
	;Se imprime mensaje 9
	mov eax, 4
	mov ebx, 1
	mov ecx, msgResultado
	mov edx, longitud9
	int 80h

	;Se mueven los datos de numeros a registros
	mov al,[num1]
	mov bl,[num2]
	
	;Conversion de ASCII a decimal
	sub al,'0'
	sub bl,'0'
	
	;Division al=ax/bl
	div bl
	
	;Conversion de decimal a ASCII
	add ax,'0'
	
	;Se mueve el resultado a al
	mov [resultado],ax
	
	;Impresion resultado
	mov eax,4
	mov ebx,1
	mov ecx,resultado
	mov edx,1
	int 80h
	jmp salida

suma:
	
	;Impresion de mensaje 5
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero1
	mov edx,longitud5
	int 80h
	
	;Leer num1
	mov eax,3
	mov ebx,0
	mov ecx,num1
	mov edx,2
	int 80h
	
	;Impresion de mensaje 6
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero2
	mov edx,longitud6
	int 80h
	
	;Leer num2
	mov eax,3
	mov ebx,0
	mov ecx,num2
	mov edx,2
	int 80h
	
	;Se imprime mensaje 9
	mov eax, 4
	mov ebx, 1
	mov ecx, msgResultado
	mov edx, longitud9
	int 80h	
	
	;Se mueven los datos de los numeros a los registros
	mov eax, [num1]
	mov ebx, [num2]
	
	;Conversion de ASCII a decimal
	sub eax, '0'
	sub ebx, '0'
	
	;Se suman los valores
	add eax,ebx

	;Convierte de decimal a ASCII
	add eax,'0'
	
	;Se mueve el resultado a eax
	mov [resultado],eax
	
	;Se imprime le resultado
	mov eax,4
	mov ebx,1
	mov ecx,resultado
	mov edx,1
	int 80h
	jmp salida

resta:
	
	;Impresion de mensaje 5
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero1
	mov edx,longitud5
	int 80h
	
	;Leer num1
	mov eax,3
	mov ebx,0
	mov ecx,num1
	mov edx,2
	int 80h
	
	;Impresion de mensaje 6
	mov eax,4
	mov ebx,1
	mov ecx,msgNumero2
	mov edx,longitud6
	int 80h
	
	;Leer num2
	mov eax,3
	mov ebx,0
	mov ecx,num2
	mov edx,2
	int 80h
	
	;Se imprime mensaje 9
	mov eax, 4
	mov ebx, 1
	mov ecx, msgResultado
	mov edx, longitud9
	int 80h	
	
	;Se mueven los numeros a los registros 
	mov eax,[num1]
	mov ebx,[num2]
	
	;Se restan los valores 
	sub eax,ebx
	
	;Se convierte el valor de decimal a ASCII
	add eax,'0'
	
	;Se mueve el resultado al registro
	mov [resultado], eax
	
	;Se imprime le resultado
	mov eax,4
	mov ebx,1
	mov ecx,resultado
	mov edx,1
	int 80h
	jmp salida

	
	;Concluimos el programa	
salida:
	;Imprimir Salto de linea
	mov eax,4
	mov ebx,1
	mov ecx,SaltoDeLinea
	mov edx,longitud10
	int 80h
	
	;Imprimir Fin de programa
	mov eax,4
	mov ebx,1
	mov ecx,msgFinal
	mov edx,longitud8
	int 80h
	mov eax,1
	mov ebx,0
	int 80h