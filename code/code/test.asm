; Assignment 7.2
; LOUD NOISES!

.data	; start of the data program segment, to declare variables

src BYTE "I DON'T KNOW WHAT WE'RE YELLING ABOUT!",0	; uppercase version of the string
lenSrc EQU ($ - src)	; length of the src string
dst BYTE "",0	; lowercase version

; for lenSrc, work through the string, getting caps versions of each letter
; decrement counter w rep

lea rdi, src	; load src string into rdi
mov rcx, lenSrc	; set counter to string length

.code	; program segment that signals the start of code segment
extern ExitProcess : proc	; creates exit function to be used later
_main PROC	; start of main function

mov rdx, 0	; set rdx to 0 as the index for the first element of the arrays

xor rcx, rcx	; resets value of rcx
.code	; end of code segment
call ExitProcess	; calls exit function
_main ENDP	; end of main function
END	; end of program