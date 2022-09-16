; Assignment 3.3
; Syntax Translation - GAS, Clang/LLVM on macOS (64-bit)
; Copyright (c) 2019 Hall & Slonka

.data	

; UNINITIALIZED DATA

						; .bss
letter BYTE ?			; .lcomm letter, 1
r DWORD ?				; .lcomm r, 4
s DWORD ?				; .lcomm s, 4
t DWORD ?				; .lcomm t, 4
x WORD ?				; .lcomm x, 2
y WORD ?				; .lcomm y, 2
z WORD ?				; .lcomm z, 2

; START MAIN FUNCTION

.code					; .text
; .global _main
extern ExitProcess : proc
_main PROC				; _main:

; INITIALIZE DATA

mov letter, 0x77		; movb $0x77, letter(%rip)

mov r, 0x5				; movl $0x5, r(%rip)
mov s, 0x2				; movl $0x2, s(%rip)
mov x, 0xa				; movw $0xa, x(%rip)
mov y, 0x4				; movw $0x4, y(%rip)

mov ax, x				; movw x(%rip), %ax
add ax, y				; addw y(%rip), %ax
mov ax, z				; movw %ax, z(%rip)

mov ax, x				; movw x(%rip), %ax
sub ax, y				; subw y(%rip), %ax
mov ax, z				; movw %ax, z(%rip)

mov edx, 0x0			; movl $0x0, %edx
mov eax, r				; movl r(%rip), %eax
mov ecx, s				; movl s(%rip), %ecx
div ecx					; divl %ecx
mov eax, t				; movl %eax, t(%rip)

mov edx, 0x0			; movl $0x0, %edx
mov eax, r				; movl r(%rip), %eax
mov ecx, s				; movl s(%rip), %ecx
div ecx					; divl %ecx
mov edx, t				; movl %edx, t(%rip)

						; movq $0x2000001, %rax
xor rcx, rcx			; xorq %rdi, %rdi
.code ;	.text			; syscall
call ExitProcess
_main ENDP				; .end
END