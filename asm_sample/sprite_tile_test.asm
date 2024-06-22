; bios call to print a character on screen
CHPUT:      equ 0x00a2
CHGMOD:	    equ 0x005F ; change screen mode
SETWRT:     equ 0x0053 ; enable VRAM to write (HL)
SETRD:      equ 0x0050 ; enable VRAM to read (HL)
LDIRVM:	    equ 0x005C ; copy mem to VRAM BC, DE, HL


; vram addresses
SPR_PAT:    equ 0x3800
SPR_ATTR:   equ 0x1B00

            ; the address of our program
            org 0xD000

message:
            db "===|<!#$     $#!>|===", 10, 13
            db "0123456789 ABCDEFGHIJ", 10, 13, 0

ascii_patterns:
            db 10, 20, 30, 40, 50, 60, 70, 80
            db 11, 21, 31, 41, 51, 61, 71, 81
            db 12, 22, 32, 42, 52, 62, 72, 82
            db 13, 23, 33, 43, 53, 63, 73, 83
            db 14, 24, 34, 44, 54, 64, 74, 84
            db 15, 25, 35, 45, 55, 65, 75, 85
            db 16, 26, 36, 46, 56, 66, 76, 86
            db 17, 27, 37, 47, 57, 67, 77, 87
            
sprite_patterns:
            db 24, 29, 26, 24, 24, 20, 18, 34
            db 24, 29, 26, 24, 24, 20, 20, 20
            db 40, 55, 40, 60, 60, 40, 55, 40

sprite_attrs:
            db  90, 120, 0, 7
            db  90, 100, 1, 2
            db 100, 180, 2, 10

start:
            ; screen 1
            ld a, 1
            call CHGMOD
            
            ; ascii pattern
            ld bc, 64
            ld de, 0x0180 ; ASCII 0x30 forward
            ld hl, ascii_patterns
            call LDIRVM
            
            ; sprite pattern
            ld bc, 24
            ld de, SPR_PAT
            ld hl, sprite_patterns
            call LDIRVM
            
            ; sprite attributes
            ld bc, 12
            ld de, SPR_ATTR
            ld hl, sprite_attrs
            call LDIRVM
            
            ; write text message
            ld hl, message
mainLoop:   ld a, (hl)
            cp 0
            JP Z, loop
            call CHPUT
            inc hl
            jr mainLoop
            
loop:       INC A
            jp loop

            ; use the label "start" as the entry point
            end start

