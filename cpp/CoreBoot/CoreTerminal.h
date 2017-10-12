//
//  CoreTerminal.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/11/17.
//

#ifndef CoreTerminal_h
#define CoreTerminal_h
#endif /* CoreTerminal_h */

#include "CoreVideo.h"

extern unsigned int video_colorcode;
extern unsigned int video_position;

extern int OpenedTerminal;

class CoreTerminal {
    
public:
    
    int strcmp( const char * s1, const char * s2 )
    {
        while ( ( *s1 ) && ( *s1 == *s2 ) )
        {
            ++s1;
            ++s2;
        }
        return ( *s1 - *s2 );
    }
    
    void OpenShell(void) {
        video_colorcode = 0x02;
        CoreVideo.Print("\n> ");
        if(video_position >= 3840) { CoreVideo.Scroll(); }
        video_colorcode = 0x07;
        OpenedTerminal = video_position;
        return;
    }
    
    void RunCommand(char * Command) {
        if(Command[0] == 'h' || 'H' & Command[1] == 'i') {
            CoreVideo.Scroll();
            }
        return;
    }
    
};

static CoreTerminal CoreTerminal;
