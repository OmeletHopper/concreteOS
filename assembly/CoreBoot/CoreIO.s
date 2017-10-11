;
;  CoreIO.s
;  concreteOS
;
;  Created by Jonathan Archer on 10/10/17.
;

bits 32                     ; 32 Bit code

global read_port
global write_port
global gdt_flush     ; Allows the C code to link to this
global load_idt
global keyboard_handler

extern gp            ; Says that '_gp' is in another file
extern keyboard_handler_main

read_port:
mov edx, [esp + 4]
in al, dx
ret

write_port:
mov   edx, [esp + 4]
mov   al, [esp + 4 + 4]
out   dx, al
ret

gdt_flush:
lgdt [gp]        ; Load the GDT with our '_gp' which is a special pointer
mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
ret               ; Returns back to the C code!

load_idt:
mov edx, [esp + 4]
lidt [edx]
sti
ret

keyboard_handler:
call    keyboard_handler_main
iretd
