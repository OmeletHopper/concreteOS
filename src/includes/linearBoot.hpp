//
//  linearBoot.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/16/17.
//

#include <cpu.h>      // So we can detect our CPU
#include <graphics.h> // Video 80x25
#include <handlers.h> // 'Driver' related
#include <input.hpp>  // Get input from keyboard
#include <keyboard.h> // Keyboard managing
#include <shell.h>  // Shell stuff

#ifndef linearBoot_hpp
#define linearBoot_hpp

extern "C" void gdtEnable(), idtEnable();
extern "C" unsigned char keyCode;

#endif
