;
;  linearBoot.s
;  concreteOS
;
;  Created by Jonathan Archer on 10/10/17.
;

bits 32                     ; 32 Bit code
section .text
align 4
dd 0x1BADB002               ; Magic
dd 0x00                     ; Flags
dd - (0x1BADB002 + 0x00)    ; Checksum

global start
extern CoreBoot             ; Our main kernel

start:
cli                         ; Clears interrupts
mov esp, stack_space        ; Stack pointer
call CoreBoot               ; Passes control to CoreBoot
hlt                         ; If CoreBoot returns, we halt

section .bss
resb 8192                   ; Measured in bytes, 8KB
stack_space:
