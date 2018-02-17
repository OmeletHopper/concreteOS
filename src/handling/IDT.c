//
//  IDT.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#define IDT_SIZE 256

extern void read_port(), write_port(), load_idt(), keyboard_handler();

struct IDT_entry {
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void EnableIDT(void) {

    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    // Keyboard entry
    keyboard_address = (unsigned long)keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08; // Offset
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e; // Gate
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    //          PIC1    PIC2
    // Command  0x20    0xA0
    // Data     0x21    0xA1

    // Initialize
    write_port(0x20 , 0x11);
    write_port(0xA0 , 0x11);

    // Remap
    write_port(0x21 , 0x20);
    write_port(0xA1 , 0x28);

    // Cascade
    write_port(0x21 , 0x00);
    write_port(0xA1 , 0x00);

    // Info
    write_port(0x21 , 0x01);
    write_port(0xA1 , 0x01);

    // Mask interrupts
    write_port(0x21 , 0xff);
    write_port(0xA1 , 0xff);

    // Fill descriptor
    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}
