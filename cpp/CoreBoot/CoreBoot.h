//
//  CoreBoot.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/16/17.
//

#ifndef CoreBoot_h
#define CoreBoot_h

extern "C" void EnableGDT(), EnableIDT();

extern "C" char keycode;

#include "CoreVideo.h"          // Video 80x25
#include "CoreHandlers.h"       // 'Driver' related
#include "CoreTerminal.h"       // Shell stuff

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

#endif /* CoreBoot_h */
