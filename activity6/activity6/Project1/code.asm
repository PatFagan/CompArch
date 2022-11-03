; Assignment 8.1 Computing Volume of a Cylinder

_printString PROTO	; printString c++ function prototype
_printDouble PROTO	; printDouble c++ function prototype
_getDouble PROTO	; getDouble c++ function prototype

extrn ExitProcess : proc	; creates exit functionality to be used later

.data	; start of the data program segment, to declare variables
ALIGN 16	; align the stack pointer

inputRadius BYTE "Input a radius: ",0	; 
inputHeight BYTE "Input a height: ",0	; 
volumeOutput BYTE "Velocity is: ",0	; 

volume REAL8 ?	; create variable for volume
radius REAL8 ?	; create variable for radius
height REAL8 ?	; create variable for height

; V=(pi)(r^2)h

.code	; program segment that signals the start of code segment


_asmMain PROC	; start of the asmMain function

finit	; initialize fpu

lea rsi, inputRadius	; load inputRadius string into rsi
mov rcx, rsi	; move string into parameter register
call _printString	; print instructions to the user
call _getDouble	; call the c++ function that asks the user for a double
movsd radius, xmm0	; move resulting value to radius from xmm0

lea rsi, inputHeight	; load inputHeight string into rsi
mov rcx, rsi	; move string into parameter register
call _printString	; print instructions to the user
call _getDouble	; call the c++ function that asks the user for a double
movsd height, xmm0	; move resulting value to radius from xmm0


fld radius
fmul radius

fldpi	; load pi onto fpu stack
fmul radius	; multiply radius by pi

;fist radius

; then put st(0) into volume



lea rsi, volumeOutput	; move volume output string into rsi
mov rcx, rsi	; load volume output string into parameter register
call _printString	; print volume output string
movsd xmm0, volume	; load volume result into parameter register
call _printDouble	; print volume result


xor rcx, rcx	; resets value of rcx

call ExitProcess	; calls exit function
_asmMain ENDP	; end of asmMain function
END



;push rbp	
;sub rsp, 20h	; subtract stack pointer by 20 hex
;lea rbp, [rsp + 20h]	; move stack to rbp


;fldpi	; load pi on fpu stack
;fstp volume	; float store single precision (32 bits) from top of FPU stack into volume variable

;fld volume	; load single precision value on FPU stack
;fadd ST(0), ST(1)
;movsd xmm0, volume