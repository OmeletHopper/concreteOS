//
//  handlers.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#ifndef CoreHandlers_h
#define CoreHandlers_h
#endif /* CoreHandlers_h */

#include <stdarg.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern int KeyboardHandlerEnabled;

extern "C" void write_port(unsigned int, unsigned int);

using namespace std;

class KeyboardHandler {

public:

    void Initialize(void)
    {
        /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
        write_port(0x21 , 0xFD);
    }
};

static KeyboardHandler KeyboardHandler;
