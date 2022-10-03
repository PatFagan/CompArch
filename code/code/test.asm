; Assignment 5.2 alternate
; Pin

.data	; start of the data program segment, to declare variables

; SUMMARY
; array of 4 ints
; for each element, check to see if they are within a range (ex. 3-6)
; if so set a validate variable to 1
; if not, set validate variable to 0 and end program


validated BYTE 2	; create variable that sets to 0 if invalid and 1 if valid (start at 2 by default)

pin WORD 4, 2, 3, 4	; create array of WORDS (2 bytes each element)

lowerboundlist WORD 3, 1, 7, 2	; create array of lowerbound values
upperboundlist WORD 6, 4, 9, 5	; create array of upperbound values


.code	; program segment that signals the start of code segment
extern ExitProcess : proc	; creates exit function to be used later
_main PROC	; start of main function

lea rsp, lowerboundlist	; load lowerbounds into array
lea rdi, upperboundlist	; load upperbounds into array

lea rsi, pin	; load pin array into rsi register

mov rdx, 0	; set rdx to 0 as the index for the first element of the arrays

restartloop:	; label used for restarting each loop, to go through each array element
mov ax, [rsi + rdx * 2]	; move current value of array into ax

mov bx, [rsp + rdx * 2]	; set first lowerbound to bx
cmp ax, bx	; compare the current array value to the lowerbound
jge checkupperbound	; jump if the current array value is greater than or equal to the lowerbound (valid)
mov validated, 0	; if comparison is false (element is out of bounds) then validated is set to 0
jmp endprogram	; and skip to the end of the program (since we already know this pin is invalid)

checkupperbound:	; if it is within lowerbounds then it jumps to here to continue comparisons
mov bx, [rdi + rdx * 2]	; set first upperbound to bx
cmp ax, bx	; compare the current array value to the upperbound
jle continueloop	; jump if the current array value is less than or equal to the upperbound to check next element
mov validated, 0	; if comparison is false (element is out of bounds) then validated is set to 0


continueloop:	; jumps to this section of code when preparing to restart the loop
inc rdx	; increment rdx to check next element of pin array

cmp validated, 0	; compare validated with 0
jz endprogram	; if validated is already 0, endprogram

cmp rdx, 4	; check if index is at end of list
jge endprogram	; if so, end the program and see validated variable for result (this only triggers if pin is valid)

jmp restartloop	; jump to the start of the loop to begin again

endprogram:	; jump here if validated is 0


xor rcx, rcx	; resets value of rcx
.code	; end of code segment
call ExitProcess	; calls exit function
_main ENDP	; end of main function
END	; end of program