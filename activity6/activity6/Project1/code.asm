; Assignment 6.1 Sum

extrn ExitProcess : proc	; creates exit functionality to be used later

displayResult PROTO	; displayResult function prototype
getInput PROTO	; getInput function prototype

.data	; start of the data program segment, to declare variables
.code	; program segment that signals the start of code segment


asmMain PROC	; start of the asmMain function

call getInput	; call the getInput c++ function which receives input from the user
call setFirstValue	; set the input value to the rsi register

call getInput	; call the getInput c++ function which receives input from the user
call setSecondValue	; set the input value to the rdi register

call sum	; call the sum function

mov rcx, rax	; move resulting value to rcx (parameter register)
call displayResult	; call c++ function that displays the resulting sum

xor rcx, rcx	; resets value of rcx

call ExitProcess	; calls exit function
asmMain ENDP	; end of asmMain function


setFirstValue PROC	; start of setFirstValue function definition
mov rsi, rax	; set rcx (first parameter) to rax (current input number)
setFirstValue ENDP	; end of function definition


setSecondValue PROC	; start of setSecondValue function definition
mov rdi, rax	; set rdx (second parameter) to rax (current input number)
setSecondValue ENDP	; end of function definition


sum PROC	; start of sum function definition
push rbp	; save frame pointer
push rbx	; saved register for callee function
sub rsp, 20h	; subtracting from stack pointer to allocate for memory used by this function
lea rbp, [rsp + 20h]	; starting at top of stack frame pointer
mov rax, rsi	; set rax to first parameter (num1)
add rax, rdi	; add second parameter (num2) to rax
lea rsp, [rbp]	; adding stack frame pointer values to stack pointer array
pop rbx	; remove memory location of callee function from stack frame pointer
pop rbp	; remove frame pointer from stack frame pointer
ret	; return value
sum ENDP	; end of sum function definition
END	; end of program
