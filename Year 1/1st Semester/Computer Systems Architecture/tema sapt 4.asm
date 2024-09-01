bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; x/2+100*(a+b)-3/(c+d)+e*e; a,c-word; b,d-byte; e-doubleword; x-qword
    
    a dw 1
    c dw 1
    b db 3
    d db 2
    e dd 5
    x dq 6

; our code starts here
segment code use32 class=code
    start:
        ; (a+b)*100
        mov bx,[a]
        mov al,[b]
        mov ah,0
        add bx,ax
        mov ax,100
        imul bx
        mov bx,ax ; rezultatul e in bx
        
        ; bx+e*e
        mov eax,[e]
        imul eax
        movzx ebx,bx
        add ebx,eax ; rezultatul la 100*(a+b)+e*e e in ebx
        
        ;x/2+100*(a+b)+e*e
        mov ecx,2
        mov eax,dword[x]
        mov edx,dword[x+4]
        idiv ecx
        add eax,ebx ;rezultatul e in eax=x/2+100*(a+b)+e*e=428
        mov ecx,eax
        
        ;3/(c+d)
        mov ax,3
        mov dx,0
        movzx bx,byte[d]
        idiv bx
        movzx eax,ax
        
        sub ecx,eax
       
        
        
        
        
        
        
        
        
        
        
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
