//
//  CoreTerminal.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <CoreVideo.h>
#include <CoreTerminal.h>

unsigned int OpenedTerminal;

extern unsigned int video_colorcode;
extern unsigned int video_position;

extern int j;

extern char *vidptr;

    void CoreTerminal::CommandError(const char * str) {
        video_colorcode = 0x04;
        CoreVideo.Print("[ ERROR ] ");
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
    void CoreTerminal::OpenShell(void) {
        video_colorcode = 0x02;
        CoreVideo.Print("> ");
        if(video_position >= 3840) { CoreVideo.Scroll(); }
        video_colorcode = 0x07;
        OpenedTerminal = video_position;
        return;
    }

    void CoreTerminal::RunCommand(char * Command) {

      j = 0;
      while(Command[j] == ' ') j++;

      if((Command[j] == 's' || Command[j] == 'S') &&          // SCROLL
         (Command[j+1] == 'c' || Command[j+1] == 'C') &&
         (Command[j+2] == 'r' || Command[j+2] == 'R') &&
         (Command[j+3] == 'o' || Command[j+3] == 'O') &&
         (Command[j+4] == 'l' || Command[j+4] == 'L') &&
         (Command[j+5] == 'l' || Command[j+5] == 'L') &&
           (Command[j+6] == '\0')) {
            CoreVideo.Scroll();
            CoreVideo.Newline();
            return;
        }

        if((Command[j] == 'c' || Command[j] == 'C') &&          // CLEAR
           (Command[j+1] == 'l' || Command[j+1] == 'L') &&
           (Command[j+2] == 'e' || Command[j+2] == 'E') &&
           (Command[j+3] == 'a' || Command[j+3] == 'A') &&
           (Command[j+4] == 'r' || Command[j+4] == 'R') &&
           (Command[j+5] == '\0')) {
            CoreVideo.ClearConsole();
            return;
        }

	      if((Command[j] == 'e' || Command[j] == 'E') &&          // ECHO
           (Command[j+1] == 'c' || Command[j+1] == 'C') &&
           (Command[j+2] == 'h' || Command[j+2] == 'H') &&
           (Command[j+3] == 'o' || Command[j+3] == 'O') &&
           (Command[j+4] == ' ')) {
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

		if(Command[j] == '\0') {        // Nothing does nothing
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
