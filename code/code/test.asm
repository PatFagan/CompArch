; Assignment 11
; Pat Fagan
; using Program 10.8 as a foundation, Copyright (c) 2017 Hall & Slonka

extrn ExitProcess : proc
extrn MessageBoxA : proc
extrn CreateFileA : proc
extern CopyFileA : proc
extrn ReadFile : proc
extrn CloseHandle : proc

.data
inputFile BYTE "read_only.txt",0
outputFile BYTE "new_file.txt",0
successMessage BYTE "Successful!",0
buffer BYTE 14 DUP (0)

firstFileContents QWORD ?
secondFileContents QWORD ?

charsRead QWORD 0
button QWORD ?
closed QWORD ?

.code
_main PROC

	sub rsp, 10h				; reserve for return and rbp
	sub rsp, 18h				; reserve for parameters
	sub rsp, 20h				; reserve shadow space for regs

	; copies input file data
	lea rcx, inputFile
	lea rdx, outputFile					; address of file name
	xor r8, r8							; 0 share mode
	xor r9, r9							; 0 security
	mov QWORD PTR [rsp+48h-28h], 3		; reverse order, 3 open existing
	mov QWORD PTR [rsp+48h-20h], 80h	; flags FILE_ATTRIBUTE_NORMAL
	mov QWORD PTR [rsp+48h-18h], 0		; 0 template
	call CopyFileA

	; creates output file using copied input file data
	lea rcx, outputFile					; address of file name
	mov rdx, 80000000h					; constant for GENERIC_READ
	xor r8, r8							; 0 share mode
	xor r9, r9							; 0 security
	mov QWORD PTR [rsp+48h-28h], 3		; reverse order, 3 open existing
	mov QWORD PTR [rsp+48h-20h], 80h	; flags FILE_ATTRIBUTE_NORMAL
	mov QWORD PTR [rsp+48h-18h], 0		; 0 template
	call CreateFileA
	mov secondFileContents, rax			; save handle

	; displays output file text
	mov rcx, secondFileContents			; pass the new file contents
	lea rdx, buffer						; pass address of buffer
	mov r8, 13							; pass buffer size
	lea r9, charsRead					; pass address of charsRead
	mov QWORD PTR [rsp+48h-28h], 0		; 0 overlap+
	call ReadFile

	xor rcx, rcx						; 0 handle owner
	lea rdx, buffer						; pass text address
	lea r8, successMessage				; pass caption address
	call MessageBoxA

	call ExitProcess			; exit

_main ENDP
END