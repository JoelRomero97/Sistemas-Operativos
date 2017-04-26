segment .data
    handleConsola   dd 1        ;1er argumento para la llamada al sistema _WriteConsoleA()
    cadenaImprimir  db '0',0xA  ;El 10=0xA es para que haga un salto de linea
    longitudCadena  dd 2        ;3er argumento para la llamada al sistema _WriteConsoleA()
                                ;Tamaño=2, se cuenta el salto de linea
    caractEscritos  dd 1        ;4to argumento para la llamada al sistema _WriteConsoleA()
    ultimoArgumento dd 1        ;5to argumento para la llamada al sistema _WriteConsoleA()
    counter         dd 0

segment .text
    global _main
    extern _GetStdHandle@4      ;Acceso externo a la llamada al sistema _GetStdHandle()
    extern _WriteConsoleA@20    ;Acceso externo a la llamada al sistema _WriteConsoleA()
    extern _ExitProcess@4       ;Acceso externo a la llamada al sistema _ExitProcess()

_main: 
	  push dword -11           ;Argumento pasado por la pila y usado en _GetStdHandle() para la salida estándar
    call _GetStdHandle@4        ;Invocación de _GetStdHandle()
    mov [handleConsola],eax             ;Devolución del manejador de consola para escritura en el registro eax
    xor eax,eax                         ;Limpieza del registro eax (eax=0)
    mov eax,2d                          ;longitud de cadena a imprimir
    mov [longitudCadena],eax            ;Se guarda la longitud en memoria
    xor eax,eax                         ;Limpieza del registro eax (eax=0)
    mov eax,0d
    mov [ultimoArgumento],eax           ;Valor del 5to argumento para _WriteConsoleA()

  ;Loop
  loop:
      push dword [ultimoArgumento]    ;5to argumento de _WriteConsoleA() pasado por pila
      push dword caractEscritos       ;4to argumento de _WriteConsoleA() pasado por pila
      push dword [longitudCadena]     ;3er argumento de _WriteConsoleA() pasado por pila
      push dword cadenaImprimir       ;2do argumento de _WriteConsoleA() pasado por pila
      push dword [handleConsola]      ;1er argumento de _WriteConsoleA() pasado por pila
      call _WriteConsoleA@20          ;Invocación de _WriteConsoleA()

      inc byte [cadenaImprimir]       ;Agrega 1 byte al primer byte del numero
      inc dword [counter]             ;Agrega 1 a la direccion de memoria
      mov eax, [counter]              ;Se guarda en memoria
      cmp eax,10                      ;Regresa al ciclo mientras sea menor a 10
  jb loop

    xor eax,eax                         ;Limpieza del registro eax (eax=0)
    mov eax,0d
    mov [ultimoArgumento],eax           ;Valor del argumento para _ExitProcess()
    push dword [ultimoArgumento]        ;Argumento de _ExitProcess() pasado por pila
    call _ExitProcess@4                 ;Invocación de _ExitProcess