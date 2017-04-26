segment .data
	handleConsola 	dd 	1											;Primer argumento para la llamada al sistema _WriteConsoleA()
	cadImprimir 	db	'Ensamblando en Windows',0xA				;Segundo argumento para la llamada al sistema _WriteConsoleA()
	longitudCadena 	dd 	1											;Tercer argumento para la llamada al sistema _WriteConsoleA()
	caractEscritos 	dd 	1											;Cuarto argumento para la llamada al sistema _WriteConsoleA()
	ultimoArgumento	dd 	1											;Quinto argumento para la llamada al sistema _WriteConsoleA()

segment .text
	global _main
	extern _GetStdHandle@4
	extern _WriteConsoleA@20
	extern _ExitProcess@4

	_main:
		push dword -11
		call _GetStdHandle@4
		mov [handleConsola],eax

		xor eax,eax
		mov eax,23d
		mov [longitudCadena],eax
		xor eax,eax
		mov eax,0d
		mov [ultimoArgumento],eax

		push dword [ultimoArgumento]
		push dword caractEscritos
		push dword [longitudCadena]
		push dword cadImprimir
		push dword [handleConsola]
		call _WriteConsoleA@20

		xor eax,eax
		mov eax,0d
		mov [ultimoArgumento],eax
		push dword [ultimoArgumento]
		call _ExitProcess@4