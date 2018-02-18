//
//  linearBoot.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/16/17.
//

#ifndef linearBoot_hpp
#define linearBoot_hpp

extern "C" void EnableGDT(), EnableIDT();

extern "C" unsigned char keyCode;

#include <graphics.hpp>          // Video 80x25
#include <handlers.hpp>       // 'Driver' related
#include <shell.hpp>       // Shell stuff
#include <CPU.hpp>    // So we can detect our CPU
#include <input.hpp>
#include <keyboard.h>

#endif /* linearBoot_hpp */
