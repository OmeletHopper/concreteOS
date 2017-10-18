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

char CPUvendor(void) {
    
cpuid(0, unused, ebx, unused, unused);
switch(ebx) {
    case 0x756e6547: // Intel
        video_colorcode = 0x03;
        char * Detected = "Intel"
        video_colorcode = 0x07;
        break;
    case 0x68747541: // AMD
        video_colorcode = 0x04;
        char * Detected = "AMD"
        video_colorcode = 0x07;
        break;
    default:
        CoreVideo.PrintLn("Unknown CPU.");
        break;
}
    return Detected;
}

#endif /* CoreBoot_h */
