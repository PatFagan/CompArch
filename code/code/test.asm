; Assignment 3.4
; Order of Operations

.data	; start of the data program segment, to declare variables

identifier BYTE "The answer is: "	; create string

answer DWORD ?	; create variable of four byte to hold the answer

; START MAIN FUNCTION

.code	; program segment that signals the start of code segment
extern ExitProcess : proc	; creates exit function to be used later
_main PROC	; start of main function

mov rax, 7	; assign rax register a value of 7
mov rbx, 5	; assign rbx register a value of 5
mov rcx, 3	; assign rcx register a value of 3
mov rdx, 4	; assign rdx register a value of 4

add rax, rbx	; adding rbx to rax
add rcx, rdx	; adding rdx to rcx
sub rax, rcx	; subtract rcx from rax
; the answer is rax

xor rcx, rcx	; resets value of rcx
.code	; end of code segment
call ExitProcess	; calls exit function
_main ENDP	; end of main function
END	; end of program