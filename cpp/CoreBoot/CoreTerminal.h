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
extern int j;

extern char *vidptr;

class CoreTerminal {
    
public:
    
    void CommandError(const char * str) {
        video_colorcode = 0x04;
        CoreVideo.PrintOne("[ ERROR ] ");
        video_colorcode = 0x07;
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character
            
            if (str[j] == '\n') { CoreVideo.Newline(); j++; }
            else {
                vidptr[video_position] = str[j];
                vidptr[video_position+1] = video_colorcode;     // Color attribute
                ++j;                                            // Increment
                video_position = video_position + 2;            // Also increment, count for attribute byte
            }
        }
        return;
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
        if(Command[0] == 's' && Command[1] == 'c' && Command[2] == 'r' && Command[3] == 'o' && Command[4] == 'l' && Command[5] == 'l' && Command[6] == '\0') {
            CoreVideo.Scroll();
            return;
        }
        CoreVideo.Print("\n");
        CommandError("Unknown command '");
        CoreVideo.Print(Command);
        CoreVideo.PrintLn("'");
        video_position = video_position - 160;
        return;
    }
    
};

static CoreTerminal CoreTerminal;
