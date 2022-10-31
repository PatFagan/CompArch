; Assignment 8.1 Computing Volume of a Cylinder

_printString PROTO
_printDouble PROTO
_getDouble PROTO

extrn ExitProcess : proc	; creates exit functionality to be used later

.data	; start of the data program segment, to declare variables

; V=(pi)(r^2)h

volume REAL4 ?
radius REAL4 ?
height REAL4 ?
pi REAL4 3.14

.code	; program segment that signals the start of code segment


_asmMain PROC	; start of the asmMain function

push rbp	
sub rsp, 20h	; subtract stack pointer by 20 hex
lea rbp, [rsp + 20h]	; move stack to rbp

finit			; initialize FPU
fldpi

fstp volume
movss xmm0, volume


call _getDouble	; call the c++ function that asks the user for a double
movss radius, xmm0	; move resulting value to rcx (parameter register)

call _getDouble	; call the c++ function that asks the user for a double
movss height, xmm0	; move resulting value to rcx (parameter register)

movss xmm0, radius
movss xmm1, radius
mul rcx

;mov rax, height
;mul rcx

;mov rax, pi
;mul rcx

;mov volume, rcx

call _printString	; print volume

xor rcx, rcx	; resets value of rcx

call ExitProcess	; calls exit function
_asmMain ENDP	; end of asmMain function
END