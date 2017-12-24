//
//  DetectCPU.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 12/23/17.
//

#ifndef DetectCPU_hpp
#define DetectCPU_hpp

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

class DetectCPU {
  unsigned long ebx, unused;
public:
  const char * VendorString();
};

static DetectCPU DetectCPU;

#endif /* DetectCPU_hpp */
