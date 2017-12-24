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

#include <CoreVideo.h>          // Video 80x25
#include <CoreHandlers.h>       // 'Driver' related
#include <CoreTerminal.h>       // Shell stuff
#include <DetectCPU.hpp>    // So we can detect our CPU

#endif /* CoreBoot_h */
