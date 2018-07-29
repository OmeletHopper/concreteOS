//
//  idt.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <handlers.h>

#define IDT_SIZE 256

extern void idtLoad(), keyboard_handler();

struct IdtEntry {
  unsigned short int LowerBitsOffset;
  unsigned short int Selector;
  unsigned char Zero;
  unsigned char TypeAttributes;
  unsigned short int HigherBitsOffset;
};

struct IdtEntry IDT[IDT_SIZE];

void idtEnable() {
  unsigned long IdtAddress, IdtPtr[2];

  // Keyboard entry
  IDT[0x21].LowerBitsOffset = (unsigned long)keyboard_handler & 0xffff;
  IDT[0x21].Selector = 0x08; // Offset
  IDT[0x21].Zero = 0;
  IDT[0x21].TypeAttributes = 0x8e; // Gate
  IDT[0x21].HigherBitsOffset =
      ((unsigned long)keyboard_handler & 0xffff0000) >> 16;

  //          PIC1    PIC2
  // Command  0x20    0xA0
  // Data     0x21    0xA1

  // Initialize
  writePort(0x20, 0x11);
  writePort(0xA0, 0x11);

  // Remap
  writePort(0x21, 0x20);
  writePort(0xA1, 0x28);

  // Cascade
  writePort(0x21, 0x00);
  writePort(0xA1, 0x00);

  // Info
  writePort(0x21, 0x01);
  writePort(0xA1, 0x01);

  // Mask interrupts
  writePort(0x21, 0xff);
  writePort(0xA1, 0xff);

  // Fill descriptor
  IdtAddress = (unsigned long)IDT;
  IdtPtr[0] =
      (sizeof(struct IdtEntry) * IDT_SIZE) + ((IdtAddress & 0xffff) << 16);
  IdtPtr[1] = IdtAddress >> 16;

  idtLoad(IdtPtr);
}
