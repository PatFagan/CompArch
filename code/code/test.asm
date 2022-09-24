; Assignment 4.4
; Differently-Sized Arrays

.data	; start of the data program segment, to declare variables

array WORD 5, 10, 15, 20	; create array of WORDS (2 bytes each element)
newArray DWORD ?, ?, ?, ?	; create array of DWORDS to fill later (4 bytes each element)
eight WORD 8

.code	; program segment that signals the start of code segment
extern ExitProcess : proc	; creates exit function to be used later
_main PROC	; start of main function

lea rsi, array	; load array into rsi register
lea rdi, newArray	; load newArray into rdi register

mov rdx, 0	; set rdx to 0 for first element of array
mov ax, [rsi + rdx * 2]	; mov first value of array into ax
mul eight	; multiply ax by 8
mov [rdi + rdx * 4], ax	; move resulting value into newArray

mov rdx, 1	; set rdx to 1 for first element of array
mov ax, [rsi + rdx * 2]	; mov first value of array into ax
mul eight	; multiply ax by 8
mov [rdi + rdx * 4], ax	; move resulting value into newArray

mov rdx, 2	; set rdx to 2 for first element of array
mov ax, [rsi + rdx * 2]	; mov first value of array into ax
mul eight	; multiply ax by 8
mov [rdi + rdx * 4], ax	; move resulting value into newArray

mov rdx, 3	; set rdx to 4 for first element of array
mov ax, [rsi + rdx * 2]	; mov first value of array into ax
mul eight	; multiply ax by 8
mov [rdi + rdx * 4], ax	; move resulting value into newArray



xor rcx, rcx	; resets value of rcx
.code	; end of code segment
call ExitProcess	; calls exit function
_main ENDP	; end of main function
END	; end of program