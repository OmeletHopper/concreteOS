//
//  keyboard.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#ifndef keyboard_h

#define keyboard_h

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define BACKSPACE   0x0E
#define TAB         0x0F
#define CAPS_LOCK   0x3A
#define ENTER       0x1C
#define LSHIFT_DOWN 0x2A
#define LSHIFT_UP   0xAA
#define RSHIFT_DOWN 0x36
#define RSHIFT_UP   0xB6
#define CTRL_DOWN   0x1D
#define ALT_DOWN    0x38
#define CTRL_UP     0x9D
#define ALT_UP      0xB8
#define F1_KEY      0x3B
#define F2_KEY      0x3C
#define F3_KEY      0x3D

#define UP          0x48
#define DOWN        0x50
#define LEFT        0x4B
#define RIGHT       0x4D

struct typedCharacter {
    unsigned int Code;          // Keycode passed by the keyboard.
    int State;        // 1 is pressed, 0 is released.
};

#endif /* keyboard_h */

extern unsigned char keyMap[];
