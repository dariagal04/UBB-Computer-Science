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
        ;citeste numele fisier, deschide fisierul, citeste fisierul, inlocuieste vocalele din fisier cu un caracter introdus afiseaza in output.txt
        string resb 100
        caracter resb 1
        mod_acces db "r",0
        mod_acces2 db "w",0
        descriptor1 dd -1
        descriptor2 dd -1
        output db "output.txt",0
        mesaj db "da numele fisierului: ", 0
        mesaj2 db "da caracter: ",0
        formats db "%s",0
        sir resb 100
        lungime resb 5
        
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mesaj
        call [printf]
        add esp, 4*1
        
        push dword string 
        call [gets]
        add esp, 4*1
        
        push dword mod_acces
        push dword string 
        call [fopen]
        add esp, 4*2
        
        mov dword [descriptor1], eax
        
        push dword [descriptor1]
        push dword 100
        push dword 1
        push dword sir
        call [fread]
        add esp, 4*4
        
        mov dword[lungime], eax
        
        push dword mesaj2
        call [printf]
        add esp, 4*1
        
        push dword caracter
        push dword formats
        call [scanf]
        add esp, 4*2
        
       mov edi, 0
       mov ecx, dword[lungime]
        parcurgere:
            cmp byte[sir +edi], 'a'
            je inlocuit
            
            cmp byte[sir +edi], 'e'
            je inlocuit

            
            cmp byte[sir +edi], 'i'
            je inlocuit

            
            cmp byte[sir +edi], 'o'
            je inlocuit
            
            cmp byte[sir +edi], 'u'
            je inlocuit

            
            cmp byte[sir +edi], 'A'
            je inlocuit

            
            cmp byte[sir +edi], 'E'
            je inlocuit

            
            cmp byte[sir +edi], 'I'
            je inlocuit

            
            cmp byte[sir +edi], 'O'
            je inlocuit

            
            cmp byte[sir +edi], 'U'
            je inlocuit
            
            inc edi
            jmp neinlocuit
            
            inlocuit:
                mov al, byte[caracter]
                mov byte[sir+edi], al
                inc edi
                
            neinlocuit:
           
            loop parcurgere
            
        push dword mod_acces2
        push dword output
        call [fopen]
        add esp, 4*2
        
        mov dword[descriptor2], eax
        
        push dword sir 
        push dword formats
        push dword [descriptor2]
        call [fprintf]
        add esp, 4*3

        push dword [descriptor1]
        call [fclose]
        add esp, 4*1
        
        push dword [descriptor2]
        call [fclose]
        add esp, 4*1
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program