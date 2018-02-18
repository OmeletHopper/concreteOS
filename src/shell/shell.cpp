//
//  shell.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <graphics.hpp>
#include <shell.hpp>

unsigned int OpenedTerminal;

extern unsigned int colorCode;
extern unsigned int videoPosition;

extern int j;

extern char *videoBaseAddress;

    void CoreTerminal::CommandError(const char * str) {
        colorCode = 0x04;
        CoreVideo.Print("[ ERROR ] ");
        colorCode = 0x07;
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character

            if (str[j] == '\n') { CoreVideo.Newline(); j++; }
            else {
                videoBaseAddress[videoPosition] = str[j];
                videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
                ++j;                                            // Increment
                videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
            }
        }
        return;
    }
    void CoreTerminal::OpenShell(void) {
        colorCode = 0x02;
        CoreVideo.Print("> ");
        if(videoPosition >= 3840) { CoreVideo.Scroll(); }
        colorCode = 0x07;
        OpenedTerminal = videoPosition;
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
                if(videoPosition >= 3840) { CoreVideo.Scroll(); }
				j = 5;
				while(Command[j] != '\0') {                             // While not terminating character
					videoBaseAddress[videoPosition] = Command[j];
					videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
					++j;                                            // Increment
					videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
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
        videoPosition = videoPosition - 160;
        return;
    }
