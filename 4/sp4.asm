.model small
.stack 1000
.data
        old dd 0 
        s db "abc", '$'
.code
.486
        count db 0 
 
new_handle proc far      
        push ds si es di dx cx bx ax 
        
        xor ax, ax 
        xor dx, dx
        in  ax, 60h        
        cmp ax, 38h
        je switch

        mov dl, count
        cmp dl, 1
        je old_handler

        cmp al, 1Eh
        mov dl, 'A'
        je new_handler
        
        cmp al, 30h     
        mov dl, 'B'
        je new_handler
        
        cmp al, 3Eh        
        mov dl, 'C'
        je new_handler
        
        cmp al, 20h       
        mov dl, 'D'
        je new_handler
        
        cmp al, 12h  
        mov dl, 'E'
        je new_handler
        
        cmp al, 21h      
        mov dl, 'F'
        je new_handler
        
        cmp al, 22h       
        mov dl, 'G'
        je new_handler
        
        cmp al, 23h        
        mov dl, 'H'
        je new_handler
        
        cmp al, 17h       
        mov dl, 'I'
        je new_handler
        
        cmp al, 24h       
        mov dl, 'J'
        je new_handler
        
        cmp al, 25h       
        mov dl, 'K'
        je new_handler
        
        cmp al, 26h       
        mov dl, 'L'
        je new_handler
        
        cmp al, 32h        
        mov dl, 'M'
        je new_handler
        
        cmp al, 31h        
        mov dl, 'N'
        je new_handler
        
        cmp al, 18h      
        mov dl, 'O'
        je new_handler
        
        cmp al, 19h       
        mov dl, 'P'
        je new_handler
        
        cmp al, 10h     
        mov dl, 'Q'
        je new_handler
        
        cmp al, 13h    
        mov dl, 'R'
        je new_handler
        
        cmp al, 1Fh      
        mov dl, 'S'
        je new_handler
        
        cmp al, 14h        
        mov dl, 'T'
        je new_handler
        
        cmp al, 16h     
        mov dl, 'U'
        je new_handler
        
        cmp al, 2Fh      
        mov dl, 'V'
        je new_handler
        
        cmp al, 11h      
        mov dl, 'W'
        je new_handler
        
        cmp al, 2Dh       
        mov dl, 'X'
        je new_handler
        
        cmp al, 15h     
        mov dl, 'Y'
        je new_handler
        
        cmp al, 2Ch      
        mov dl, 'Z'
        je new_handler
        
        jmp old_handler

        switch:
            mov al, 1
            add count, al
            mov al, count
            cmp al, 2
            jne exit
            mov count, 0
            jmp exit
        new_handler:                
                mov ah, 02h
                int 21h
                ;mov ah, 02h
                ;int 21h

                jmp exit       
        old_handler: 
                pop ax bx cx dx di es si ds                       
                jmp dword ptr cs:old        
                
        exit:
                xor ax, ax
                mov al, 20h
                out 20h, al 
                pop ax bx cx dx di es si ds 
        iret
new_handle endp
 
 
new_end:
 
start:
        mov ax, @data
        mov ds, ax
        
        cli
        pushf 
        push 0        
        pop ds
        mov eax, ds:[09h*4] 
        mov cs:[old], eax 
        
        mov ax, cs
        shl eax, 16
        mov ax, offset new_handle
        mov ds:[09h*4], eax 
        sti 
        
        ;xor ax, ax
        ;mov ah, 31h
        MOV DX, (New_end - @code + 10FH) / 16 
        INT 27H 
end start