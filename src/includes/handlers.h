//
//  handlers.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <stdarg.h>

#ifndef handlers_h
#define handlers_h

#ifdef __cplusplus
extern "C" {
#endif

int read_port(unsigned int);
void write_port(unsigned int, unsigned int);

#ifdef __cplusplus
}

class KeyboardHandler {

public:
  void Initialize(void)
    {
        /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
        write_port(0x21 , 0xFD);
    }
};

static KeyboardHandler KeyboardHandler;
#endif

#endif /* handlers_h */
