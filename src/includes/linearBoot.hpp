//
//  linearBoot.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/16/17.
//

#ifndef CoreBoot_h
#define CoreBoot_h

extern "C" void EnableGDT(), EnableIDT();
extern void KeyTaker(char * Keys);

extern "C" char keyCode;

#include <graphics.hpp>          // Video 80x25
#include <handlers.hpp>       // 'Driver' related
#include <shell.hpp>       // Shell stuff
#include <CPU.hpp>    // So we can detect our CPU

#endif /* CoreBoot_h */
