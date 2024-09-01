bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 
    a dw 1600
    b dw 4
    c db 0
    d dd 0

; our code starts here
segment code use32 class=code
    start:
        ; Se dau doua cuvinte A si B. Sa se obtina un octet C care are:
        ;pe bitii 0-5, bitii 5-10 ai cuvantului A
        ;pe bitii 6-7 bitii 1-2 ai cuvantului B.
        mov ax,[a]
        shr ax,5
        and ax, 0000000000111111b
        or byte[c], al
        mov bx, [b]
        shl bx,5
        and bx, 0000000011000000b
        or byte[c], bl
        
        
        ;Sa se obtina dublucuvantul D care are :
        ;pe bitii 8-15, bitii lui C
        ;pe bitii 0-7, bitii 8-15 din B
        ;pe bitii 24-31, bitii 0-7 din A
        ;iar pe bitii 16-23, bitii 8-15 din A.
        movzx cx,byte[c]
        shl cx,8
        and cx, 1111111100000000b
        movzx ecx,cx
        or dword[d],ecx
        mov bx,[b]
        and bx,1111111100000000b
        movzx ebx,bx
        or dword[d],ebx
        movzx eax,word[a]
        shl eax,8
        and eax, 00000000111111110000000000000000b
        or dword[d],eax
        movzx eax,word[a]
        shr eax,24
        and eax, 11111111000000000000000000000000b
        or dword[d],eax
        
        
        mov eax,[d]
        mov bl,[c]
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
