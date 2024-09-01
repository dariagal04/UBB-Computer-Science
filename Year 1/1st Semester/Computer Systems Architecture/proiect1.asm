bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir A de dublucuvinte. Cunstruiti doua siruri de octeti  
    ; - B1: contine ca elemente partea inferioara a cuvintelor inferioara din A
    ; - B2: contine ca elemente partea superioara a cuvintelor superioare din A
    s dd 12345678h, 1A2B3C4Dh
    lsd equ ($-s)/4
    b1 resb lsd
    b2 resb lsd
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, lsd
        mov esi, 3 ; b1
        mov edi, 0 ; b2
        mov ebp, 0 ; s
        repeta:
            mov al, [s+esi]
            mov [b1+ebp], al
            mov bl, [s+edi]
            mov [b2+ebp], bl 
            add esi, 4
            add edi, 4
            inc ebp
        loop repeta
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
