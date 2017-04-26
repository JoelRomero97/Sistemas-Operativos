segment .data
	cadena db 'Programando en ensamblador para Linux',0xA			;Cadena a imprimir

segment .text
	
	global _start
_start:						;Inicio del programa

	mov edx,38d				;Longitud de cadena
	mov ecx,cadena   		;Cadena a escribir
	mov ebx,1				;Salida estándar
	mov eax,4				;Numero de llamada al sistema "sys_write"
	int 0x80				;Interrupción de llamadas al sistema del kernel de Linux
	mov eax,1				;Número de llamada al sistema "sys_exit"
	int 0x80				;Interrupción de llamadas al sistema del kernel de Linux