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

add src, 32	; change ascii byte to lowercase equivalent by adding 32 bytes

mov rcx, lensrc	; set counter to string length

cld	; clear direction flag to read left to right
rep movsd	; move src character to dst string


xor rcx, rcx	; resets value of rcx
.code	; end of code segment
call ExitProcess	; calls exit function
_main ENDP	; end of main function
END	; end of program