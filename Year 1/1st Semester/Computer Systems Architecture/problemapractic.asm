bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern fopen, fclose, printf, scanf, fprintf, gets, fread, fscanf
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import gets msvcrt.dll
import fread msvcrt.dll
import fscanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    string resb 100
    caracter resb 100
    formats db "%s", 0
    p dd 0
    formatn db "%d", 0
    c dd 0
    formatc db "%c", 0
    mesaj db "introduceti un fisier, caracter si un numar: ", 10, 13, 0
    mod_acces db "r", 0
    mod_acces2 db "w", 0
    descriptor1 db -1
    descriptor2 db -1
    len equ 100
    sir resb 100
    lungimefisier db 0
    nume_fisier db "output.txt", 0
    char db 0
    

; our code starts here
segment code use32 class=code
    start:
        push dword mesaj
        call [printf]
        add esp, 4*1
        
        push dword string
        call [gets]
        add esp, 4*1
        
        push dword caracter
        push dword formats
        call [scanf]
        add esp, 4*2
        
        push dword p
        push dword formatn
        call [scanf]
        add esp, 4*2
        
        push dword mod_acces 
        push dword string
        call [fopen]
        add esp, 4*2
        
        mov [descriptor1], eax
        mov edi, 0
        citire_fisier:
     
            push dword char
            push dword formatc
            push dword [descriptor1]
            call [fscanf]
            add esp, 4*3
            
            cmp eax,1
            jne sirul
            
            
            cmp edi, dword[p]
            je scrie
            
            
            mov eax, dword[caracter]
            mov [sir+edi], eax
            inc edi
            jmp citire_fisier
            
            scrie: 
                mov eax,[char]
                mov [sir+edi], eax
                inc edi
                jmp citire_fisier
                
                
            sirul:    
                mov esi,sir
                push dword [descriptor1]
                call [fclose]
                add esp,4*1
         
         output :
            push dword mod_acces2
            push dword nume_fisier
            call [fopen]
            add esp, 4*2
            
            mov [descriptor2], eax
            
            lodsb
            movsx eax, al
            
            push dword eax
            push dword formats
            push dword [descriptor2]
            call [fprintf]
            add esp, 4*3
            
            push dword [descriptor2]
            call [fclose]
            add esp, 4*1
            
            
            
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
