bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...x+(2-a*b)/(a*3)-a+c; a-byte; b-word; c-doubleword; x-qword
    a db 2
    b dw 7
    c dd 3
    x dq 4

; our code starts here
segment code use32 class=code
    start:
        ; (2-a*b)
        movzx ebx, word [b]        
        movzx eax, byte [a]    
        imul ebx
        mov ebx,2
        mov ecx,0
        sub ebx,eax
        sbb ecx,edx ;rezultat in ecx:ebx
        
        
        ;(2-a*b)/(a*3)
        mov dl,3
        mov al,[a]
        imul dl
        cwde
        mov ecx,eax
        mov eax,ebx
        mov edx,0
        mov ebx,ecx
        idiv ebx
        
        
         ;(2-a*b)/(a*3)->eax
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
