//
//  CoreKeyboard.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern unsigned int video_position;            // Our position

#include "CoreKeyboard.h"
#include "../../cpp/CoreBoot/CoreHandlers.h"
#include "../../cpp/CoreBoot/CoreTerminal.h"

extern "C" int read_port(unsigned int);
extern "C" void write_port(unsigned int, unsigned int);

extern void KeyTaker(char * Keys);

extern int OpenedTerminal;

int KeyboardHandlerEnabled = 0;
int KeyPosition = 0;

extern "C" void keyboard_handler_main(void) {
    
    if(KeyboardHandlerEnabled != 1) { return; }
    
    extern char * vidptr;               // Video buffer start address
    unsigned char status;
    char keycode;
    char * KeyLine = 0x00;
    
    /* write EOI */
    write_port(0x20, 0x20);
    
    status = read_port(KEYBOARD_STATUS_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        
        if(keycode == 0x0E) {
            
            if(video_position <= OpenedTerminal) return;
            
            video_position = video_position - 2;
            vidptr[video_position] = ' ';
            video_position = video_position + 1;
            vidptr[video_position] = 0x07;
            video_position = video_position - 1;
            return;
        }
        
        if(keycode == 0x1C) {
            KeyLine[KeyPosition + 1] = '\0';
            KeyTaker(KeyLine);
            KeyPosition = 0;
            KeyLine = 0x00;
            KeyLine[0] = ' ';
            return;
        }
        
        if(keycode < 0)
        return;
        
        KeyLine[KeyPosition] = keyboard_map[keycode];
        KeyPosition++;
        
        if(video_position >= 3840) { CoreVideo.Scroll(); }

        vidptr[video_position++] = keyboard_map[keycode];
        vidptr[video_position++] = 0x07;
    }
}
