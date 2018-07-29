//
//  cpu.h
//  concreteOS
//
//  Created by Jonathan Archer on 12/23/17.
//

#ifndef cpu_h
#define cpu_h

#ifdef __cplusplus
extern "C" {
#endif

#define cpuid(in, a, b, c, d)                                                  \
  __asm__("cpuid" : "=a"(a), "=b"(b), "=c"(c), "=d"(d) : "a"(in));

const char *VendorString();

#ifdef __cplusplus
}
#endif

#endif
