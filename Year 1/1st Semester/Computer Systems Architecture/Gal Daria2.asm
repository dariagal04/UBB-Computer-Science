bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern printf, scanf
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
     x dd 0
     y dd 0
     e resb 100
     formatx db "%d", 0
     formaty db "%x", 0
     mesajx db "dati x: ", 0
     mesajy db "dati y: ", 0
     
     
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mesajx
        call [printf]
        add esp, 4*1
        
        push dword x
        push dword formatx
        call [scanf]
        add esp,4*2
        
        push dword mesajy
        call [printf]
        add esp, 4*1
        
        push dword y
        push dword formaty
        call [scanf]
        add esp,4*2
        
        mov eax, [x]
        cdq
        idiv dword[y]
        
        sub eax, 3
        
        mov dword[e], eax
        
        push dword eax
        push dword formatx
        call [printf]
        add esp, 4*2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
