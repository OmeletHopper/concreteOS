//
//  shell.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <graphics.h>
#include <shell.hpp>

unsigned int OpenedTerminal;
unsigned char * toEcho = 0x00;

void CoreTerminal::CommandError(const char * str)
{
  colorCode = 0x04;
  Print("[ ERROR ] ");
  colorCode = 0x07;
  j = 0;
  while(str[j] != '\0') {                             // While not terminating character
    if (str[j] == '\n') { Newline(); j++; }
    else {
      videoBaseAddress[videoPosition] = str[j];
      videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
      ++j;                                            // Increment
      videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
    }
  }
  return;
}
void CoreTerminal::OpenShell()
{
  colorCode = 0x02;
  Print("> ");
  if(videoPosition >= 3840) Scroll();
  colorCode = 0x07;
  OpenedTerminal = videoPosition;
  return;
}
void CoreTerminal::RunCommand(char * Command)
{
  j = 0;
  while(Command[j] == ' ') j++;

  if((Command[j] == 's' || Command[j] == 'S') &&          // SCROLL
  (Command[j+1] == 'c' || Command[j+1] == 'C') &&
  (Command[j+2] == 'r' || Command[j+2] == 'R') &&
  (Command[j+3] == 'o' || Command[j+3] == 'O') &&
  (Command[j+4] == 'l' || Command[j+4] == 'L') &&
  (Command[j+5] == 'l' || Command[j+5] == 'L') &&
  (Command[j+6] == '\0')) {
    Scroll();
    Newline();
    return;
  }
  if((Command[j] == 'c' || Command[j] == 'C') &&          // CLEAR
  (Command[j+1] == 'l' || Command[j+1] == 'L') &&
  (Command[j+2] == 'e' || Command[j+2] == 'E') &&
  (Command[j+3] == 'a' || Command[j+3] == 'A') &&
  (Command[j+4] == 'r' || Command[j+4] == 'R') &&
  (Command[j+5] == '\0')) {
    ClearConsole();
    return;
  }
  if((Command[j] == 'e' || Command[j] == 'E') &&          // ECHO
  (Command[j+1] == 'c' || Command[j+1] == 'C') &&
  (Command[j+2] == 'h' || Command[j+2] == 'H') &&
  (Command[j+3] == 'o' || Command[j+3] == 'O') &&
  (Command[j+4] == ' ')) {
    Newline();
    if(videoPosition >= 3840) Scroll();
    j = j + 5;
    i = 0;
    while(1) {
      toEcho[i] = Command[j];
      if(Command[j] == '\0') break;
      j++, i++;
    }
    if(videoPosition >= 3840) { while(i >= 80) { Scroll(); i = i - 80;} }
    Print((char *)toEcho);
		Newline();
		return;
  }
	if(Command[j] == '\0') {        // Nothing does nothing
    Newline();
    return;
  }
  Print("\n");
  CommandError("Unknown command '");
  Print(Command);
  PrintLn("'\n");
  videoPosition = videoPosition - 160;
  return;
}
