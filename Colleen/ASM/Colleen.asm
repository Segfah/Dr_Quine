section .text
	global main
	extern printf

; Este comentario está fuera de la función main

empty:
	ret

main:
	push rbp
	; Este comentario está dentro de la función main
	call empty
	lea rdi, [rel code]
	mov rsi, 10
	mov rdx, 96
	lea rcx, [rel code]
	call printf
	pop rbp
	ret

section .data
code db `section .text%1$c	global main%1$c	extern printf%1$c%1$c; Este comentario está fuera de la función main%1$c%1$cempty:%1$c	ret%1$c%1$cmain:%1$c	push rbp%1$c	; Este comentario está dentro de la función main%1$c	call empty%1$c	lea rdi, [rel code]%1$c	mov rsi, 10%1$c	mov rdx, 96%1$c	lea rcx, [rel code]%1$c	call printf%1$c	pop rbp%1$c	ret%1$c%1$csection .data%1$ccode db %2$c%3$s%2$c, 0x0%1$c`, 0x0
