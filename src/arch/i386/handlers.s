;
;  handlers.s
;  concreteOS
;
;  Created by Jonathan Archer on 10/10/17.
;

bits 32                     ; 32 Bit code

global readPort
global writePort
global gdtFlush	; Allows the C code to link to this
global idtLoad
global keyboard_handler

extern GdtPtr	; Says that '_gp' is in another file
extern keyboardHandlerMain

readPort:
mov edx, [esp + 4]
in al, dx
ret

writePort:
mov   edx, [esp + 4]
mov   al, [esp + 4 + 4]
out   dx, al
ret

gdtFlush:
lgdt [GdtPtr]        ; Load the GDT with our '_gp' which is a special pointer
mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
ret               ; Returns back to the C code!

idtLoad:
mov edx, [esp + 4]
lidt [edx]
sti
ret

keyboard_handler:
call    keyboardHandlerMain
iretd
