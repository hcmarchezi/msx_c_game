; bios call to print a character on screen
CHPUT:      equ 0x00a2

            ; the address of our program
            org 0xD000




c_div_d:
;C Divided by D
;
;Inputs:
;     C is the numerator
;     D is the denominator
;Outputs:
;     A is the remainder
;     B is 0
;     C is the result of C/D
;     D,E,H,L are not changed
;
     ld b,8
     xor a
       sla c
       rla
       cp d
       jr c,$+4
         inc c
         sub d
       djnz $-8
     ret



conv_c_to_str:
;Convert C to string (str_from_num addr)
; 
;Inputs:
;	C -> number to be converted
; 	HL -> mem addr (reference to string output)
;Outpus:
;	D -> 10
;   HL -> str addr
;
    ld d, 10

    ld b, 2 ;<--- TODO: replace with register that contains str size
  	inc hl
    djnz $-1
    
    ; how to make for-loop here?????


    call c_div_d    
    add a, 0x30        
    ld (hl), a
    dec hl


    call c_div_d    
    add a, 0x30        
    ld (hl), a
    dec hl


    call c_div_d    
    add a, 0x30        
    ld (hl), a
    dec hl
  

    ret
    
    
    

printMessage:
;Print string message 
;
;Inputs:
;		HL -> string content mem addr (should finish with 0)
;Outputs:
;		None
;		
    ld a, (hl)
    cp 0
    ret z
    call CHPUT
    inc hl
    jr printMessage
    ret






message:
    db "Hello world!",0

life:
    db "000", 0

life_chrs:
	db 3



start:	; program entry point
    ld hl, message
    call printMessage
    
    
    ld c, 67    
    ld hl, life    
    call conv_c_to_str
    
    ld hl, life
    call printMessage   
    
    
    ; finish program
    end start
            


            