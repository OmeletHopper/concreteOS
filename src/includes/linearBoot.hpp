//
//  linearBoot.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/16/17.
//

#include <graphics.h>   // Video 80x25
#include <handlers.h>   // 'Driver' related
#include <shell.hpp>      // Shell stuff
#include <CPU.hpp>        // So we can detect our CPU
#include <input.hpp>      // Get input from keyboard
#include <keyboard.h>     // Keyboard managing

#ifndef linearBoot_hpp
#define linearBoot_hpp

extern "C" void EnableGDT(), EnableIDT();
extern "C" unsigned char keyCode;

#endif /* linearBoot_hpp */
