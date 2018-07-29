//
//  handlers.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#ifndef handlers_h
#define handlers_h

#ifdef __cplusplus
extern "C" {
#endif

int readPort(unsigned int);
void writePort(unsigned int, unsigned int);

#ifdef __cplusplus
}

class KeyboardHandler {

public:
  void Initialize(void)
    {
        /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
        writePort(0x21 , 0xFD);
    }
};

static KeyboardHandler KeyboardHandler;
#endif

#endif /* handlers_h */
