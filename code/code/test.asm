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
_main PROC				; _main:

; INITIALIZE DATA

mov letter, 0x77		; movb $0x77, letter(%rip)
mov BYTE PTR letter, 0x77

mov r, 0x5				; movl $0x5, r(%rip)
mov BYTE PTR r, 0x5
mov s, 0x2				; movl $0x2, s(%rip)
mov BYTE PTR s, 0x2
mov x, 0xa				; movw $0xa, x(%rip)
mov BYTE PTR x, 0xa
mov y, 0x4				; movw $0x4, y(%rip)
mov BYTE PTR y, 0x4

mov ax, x				; movw x(%rip), %ax
add ax, y				; addw y(%rip), %ax
mov ax, z				; movw %ax, z(%rip)

mov ax, x				; movw x(%rip), %ax
subw y(%rip), %ax
movw %ax, z(%rip)

movl $0x0, %edx
movl r(%rip), %eax
movl s(%rip), %ecx
divl %ecx
movl %eax, t(%rip)

movl $0x0, %edx
movl r(%rip), %eax
movl s(%rip), %ecx
divl %ecx
movl %edx, t(%rip)

						; movq $0x2000001, %rax
xor rcx, rcx			; xorq %rdi, %rdi
.code ;	.text			; syscall
END	; .end