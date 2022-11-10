; Assignment 9.4 Encryption

_printString PROTO	; printString c++ function prototype
_printDouble PROTO	; printDouble c++ function prototype
_getDouble PROTO	; getDouble c++ function prototype

extrn ExitProcess : proc	; creates exit functionality to be used later

.data	; start of the data program segment, to declare variables
ALIGN 16	; align the stack pointer

inputRadius BYTE "Input a radius: ",0	; input radius text
inputHeight BYTE "Input a height: ",0	; input height text
volumeOutput BYTE "Velocity is: ",0	; output volume text

volume REAL8 ?	; create variable for volume
radius REAL8 ?	; create variable for radius
height REAL8 ?	; create variable for height

; V=(pi)(r^2)h

.code	; program segment that signals the start of code segment


_asmMain PROC	; start of the asmMain function

; align stack pointer (ref investment calculator in chapter 8)

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


fld radius	; load radius onto fpu stack
fmul radius	; multiply radius by radius
fstp volume	; store result into volume

fldpi	; load pi onto fpu stack
fmul volume	; multiply current volume by pi
fstp volume	; store result into volume

fld height	; load height onto fpu stack
fmul volume	; multiply current volume by height
fstp volume	; store result into volume 

lea rsi, volumeOutput	; move volume output string into rsi
mov rcx, rsi	; load volume output string into parameter register
call _printString	; print volume output string
movsd xmm0, volume	; load volume result into parameter register
call _printDouble	; print volume result


xor rcx, rcx	; resets value of rcx

call ExitProcess	; calls exit function
_asmMain ENDP	; end of asmMain function
END	; end of program
