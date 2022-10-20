; Assignment 7.2
; LOUD NOISES!

.data	; start of the data program segment, to declare variables

src BYTE "I DON'T KNOW WHAT WE'RE YELLING ABOUT!",0	; uppercase version of the string
lensrc EQU ($ - src)	; length of the src string
dst BYTE ":",0	; lowercase version


.code	; program segment that signals the start of code segment
extern ExitProcess : proc	; creates exit function to be used later
_main PROC	; start of main function


lea rsi, src	; load src string into rsi
lea rdi, dst	; load dst string into rdi

mov rcx, lensrc	; set counter to string length
mov rdx, 0	; set rdx to 0 for first element of array


cld	; clear direction flag to read left to right
rep movsd	; move src character to dst string


lea rdi, dst	; load new dst string into rdi

continueloop:	; tag for the lowercase conversion loop

mov ax, [rdi + rdx]	; move src character to rax

add ax, 32	; convert capital to lowercase character

mov [rdi + rdx], ax	; add new character to rdi

inc rdx	; add to rdx to access next element in the array

cmp rdx, lensrc - 2	; compare rdx to lensrc - 2 for some reason, bc wout the - 2 it prints the string twice
jle continueloop	; if counter is equal to or less than zero, the loop ends



xor rcx, rcx	; resets value of rcx
.code	; end of code segment
call ExitProcess	; calls exit function
_main ENDP	; end of main function
END	; end of program