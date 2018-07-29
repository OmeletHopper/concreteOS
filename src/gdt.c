//
//  GDT.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/11/17.
//

extern void gdtFlush();

struct GdtEntry {
  unsigned short LimitLow;
  unsigned short BaseLow;
  unsigned char BaseMiddle;
  unsigned char Access;
  unsigned char Granularity;
  unsigned char BaseHigh;
} __attribute__((packed));

struct GdtPointer {
  unsigned short Limit;
  unsigned int Base;
} __attribute__((packed));

struct GdtEntry Gdt[3];
struct GdtPointer GdtPtr;

void gdtSetGate(int Num, unsigned long Base, unsigned long Limit,
                unsigned char Access, unsigned char Gran) {
  Gdt[Num].BaseLow = (Base & 0xFFFF);
  Gdt[Num].BaseMiddle = (Base >> 16) & 0xFF;
  Gdt[Num].BaseHigh = (Base >> 24) & 0xFF;
  Gdt[Num].LimitLow = (Limit & 0xFFFF);
  Gdt[Num].Granularity = ((Limit >> 16) & 0x0F);
  Gdt[Num].Granularity |= (Gran & 0xF0);
  Gdt[Num].Access = Access;
}

void gdtEnable() {
  GdtPtr.Limit = (sizeof(struct GdtEntry) * 3) - 1;
  GdtPtr.Base = (int)&Gdt;

  gdtSetGate(0, 0, 0, 0, 0);                // Null descriptor
  gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

  gdtFlush();
}
