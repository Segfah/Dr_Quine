section.text:
	global _start
	extern dprintf

; Este programa genera un archivo Grace_kid.c que contiene su propio código

%define FILENAME `Grace_kid.asm`
%define init _start:
%macro main 0
	lea rdi, [rel filename]
	mov rsi, 577
	mov rdx, 420
	mov rax, 2
	syscall

	push rax
	pop rdi
	lea rsi, [rel code]
	mov rdx, 10
	mov rcx, 37
	mov r8, 96
	mov r9, rsi
	call dprintf

	mov rax, 3
	syscall

	xor rdi, rdi
	mov rax, 60
	syscall

code db `section.text:%1$c	global _start%1$c	extern dprintf%1$c%1$c; Este programa genera un archivo Grace_kid.c que contiene su propio código%1$c%1$c%2$cdefine FILENAME %3$cGrace_kid.asm%3$c%1$c%2$cdefine init _start:%1$c%2$cmacro main 0%1$c	lea rdi, [rel filename]%1$c	mov rsi, 577%1$c	mov rdx, 420%1$c	mov rax, 2%1$c	syscall%1$c%1$c	push rax%1$c	pop rdi%1$c	lea rsi, [rel code]%1$c	mov rdx, 10%1$c	mov rcx, 37%1$c	mov r8, 96%1$c	mov r9, rsi%1$c	call dprintf%1$c%1$c	mov rax, 3%1$c	syscall%1$c%1$c	xor rdi, rdi%1$c	mov rax, 60%1$c	syscall%1$c%1$ccode db %3$c%4$s%3$c, 0x0%1$cfilename db FILENAME, 0x0%1$c%2$cendmacro%1$c%1$cinit%1$c	main%1$c`, 0x0
filename db FILENAME, 0x0
%endmacro

init
	main
