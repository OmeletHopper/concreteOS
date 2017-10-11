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

int OpenedTerminal;

class CoreTerminal {
    
public:
    
    void OpenShell(void)
    {
        video_colorcode = 0x02;
        CoreVideo.Print("\n> ");
        video_colorcode = 0x07;
        OpenedTerminal = video_position;
        return;
    }
};

static CoreTerminal CoreTerminal;
