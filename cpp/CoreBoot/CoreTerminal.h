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

extern unsigned int OpenedTerminal;
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
        CoreVideo.Print("> ");
        if(video_position >= 3840) { CoreVideo.Scroll(); }
        video_colorcode = 0x07;
        OpenedTerminal = video_position;
        return;
    }
    
    void RunCommand(char * Command) {
        
        if((Command[0] == 's' || Command[0] == 'S') &&          // SCROLL
           (Command[1] == 'c' || Command[1] == 'C') &&
           (Command[2] == 'r' || Command[2] == 'R') &&
           (Command[3] == 'o' || Command[3] == 'O') &&
           (Command[4] == 'l' || Command[4] == 'L') &&
           (Command[5] == 'l' || Command[5] == 'L') &&
           (Command[6] == '\0')) {
            CoreVideo.Scroll();
            CoreVideo.Newline();
            return;
        }
        
        if((Command[0] == 'c' || Command[0] == 'C') &&          // CLEAR
           (Command[1] == 'l' || Command[1] == 'L') &&
           (Command[2] == 'e' || Command[2] == 'E') &&
           (Command[3] == 'a' || Command[3] == 'A') &&
           (Command[4] == 'r' || Command[4] == 'R') &&
           (Command[5] == '\0')) {
            CoreVideo.ClearConsole();
            return;
        }
		
	    if((Command[0] == 'e' || Command[0] == 'E') &&          // ECHO
           (Command[1] == 'c' || Command[1] == 'C') &&
           (Command[2] == 'h' || Command[2] == 'H') &&
           (Command[3] == 'o' || Command[3] == 'O') &&
           (Command[4] == ' ')) {
			   CoreVideo.Newline();
                if(video_position >= 3840) { CoreVideo.Scroll(); }
				j = 5;
				while(Command[j] != '\0') {                             // While not terminating character
					vidptr[video_position] = Command[j];
					vidptr[video_position+1] = video_colorcode;     // Color attribute
					++j;                                            // Increment
					video_position = video_position + 2;            // Also increment, count for attribute byte
			}
				CoreVideo.Newline();
				return;
        }
        
		if(Command[0] == '\0') {        // Nothing does nothing
			CoreVideo.Newline();
            return;
        }
		
        CoreVideo.Print("\n");
        CommandError("Unknown command '");
        CoreVideo.Print(Command);
        CoreVideo.PrintLn("'\n");
        video_position = video_position - 160;
        return;
    }
    
};

static CoreTerminal CoreTerminal;
