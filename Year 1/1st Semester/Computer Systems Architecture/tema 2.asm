bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
   a dw 2
   x dw 5
   b dw 3
   d dw 1
   
; our code starts here
segment code use32 class=code
    start:
        ; (c+b+b)-(c+a+d)
     mov ax, [x] ; ax=5
     movzx eax, ax ; eax primeste 5
     add eax, [b] ;eax= c+b
     add eax, [b] ;eax= c+b+b
     sub eax, [x] ;eax= c+b+b-c
     sub eax, [a] ;eax= c+b+b-c-a
     sub eax, [d] ;eax= c+b+b-c-a-d => eax=(c+b+b)-(c+a+d)=3
     
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
