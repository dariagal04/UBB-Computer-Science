bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf
import exit msvcrt.dll   
import printf msvcrt.dll   
import scanf msvcrt.dll 
         
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 0
    b dd 0
    c dd 0 
    media resd 2
    
    mesaja db "dati primul element = ", 0
    mesajb db "dati al doilea element = ", 0
    mesajc db "dati al treilea elemnet = ", 0
    format db "%d", 0
    formath db "%x", 10, 0

; our code starts here
segment code use32 class=code
    start:
        push dword mesaja
        call [printf]
        add esp, 4*1
        
        push dword a
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword mesajb
        call [printf]
        add esp, 4*1
        
        push dword b
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword mesajc
        call [printf]
        add esp, 4*1
        
        push dword c
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        add eax, [b]
        add eax, [c]
        mov edx, 0
        mov ebx, 3
        idiv ebx
        mov [media], eax
        
        push dword [media]
        push dword formath
        call [printf]
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
