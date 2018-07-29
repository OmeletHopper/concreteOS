//
//  CPU.c
//  concreteOS
//
//  Created by Jonathan Archer on 12/23/17.
//

#include <cpu.h>

const char *VendorString() {
  unsigned long unused, ebx;
  cpuid(0, unused, ebx, unused, unused);
  switch (ebx) {
  case 0x756e6547: // Intel
    return "Intel";
    break;
  case 0x68747541: // AMD
    return "AMD";
    break;
  default:
    return "Unknown";
    break;
  }
}
