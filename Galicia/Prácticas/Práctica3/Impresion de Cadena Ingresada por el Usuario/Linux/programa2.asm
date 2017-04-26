segment .bss			;Segmento de datos

	cadena resb 50

segment .text
	global _start
_start:

	mov edx,50d					;Longitud del búfer
	mov ecx,cadena 				;Cadena a leer
	mov ebx,0					;Entrada estándar
	mov eax,3					;Numero de llamada al sistema "sys_read"
	int 0x80					;Interrupcion de llamada al sistema del kernel de Linux
	mov edx,50d					;Longitud de cadena
	mov ecx,cadena 				;Cadena a escribir
	mov ebx,1					;Salida estándar
	mov eax,4					;Numero de llamada al sistema "sys_write"
    int 0x80					;Interrupcion de llamada al sistema del kernel de Linux
    mov eax,1					;Numero de llamada al sistema "sys_exit"
    int 0x80					;Interrupcion de llamada al sistema del kernel de Linux