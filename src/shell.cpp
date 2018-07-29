//
//  shell.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <graphics.h>
#include <shell.hpp>

unsigned int OpenedTerminal;
unsigned char *toEcho = 0x00;

void CoreTerminal::commandError(const char *str) {
  ColorCode = 0x04;
  print("{ ERROR } ");
  ColorCode = 0x07;
  int j = 0;
  while (str[j] != '\0') { // While not terminating character
    if (str[j] == '\n') {
      newLine();
      j++;
    } else {
      VideoPointer[VideoPosition] = str[j];
      VideoPointer[VideoPosition + 1] = ColorCode; // Color attribute
      ++j;                                         // Increment
      VideoPosition =
          VideoPosition + 2; // Also increment, count for attribute byte
    }
  }
  return;
}
void CoreTerminal::openShell() {
  ColorCode = 0x02;
  print("> ");
  if (VideoPosition >= 3840)
    scroll();
  ColorCode = 0x07;
  OpenedTerminal = VideoPosition;
  return;
}
void CoreTerminal::runCommand(char *Command) {
  int j = 0;
  while (Command[j] == ' ')
    j++;

  if ((Command[j] == 's' || Command[j] == 'S') && // SCROLL
      (Command[j + 1] == 'c' || Command[j + 1] == 'C') &&
      (Command[j + 2] == 'r' || Command[j + 2] == 'R') &&
      (Command[j + 3] == 'o' || Command[j + 3] == 'O') &&
      (Command[j + 4] == 'l' || Command[j + 4] == 'L') &&
      (Command[j + 5] == 'l' || Command[j + 5] == 'L') &&
      (Command[j + 6] == '\0')) {
    scroll();
    newLine();
    return;
  }
  if ((Command[j] == 'c' || Command[j] == 'C') && // CLEAR
      (Command[j + 1] == 'l' || Command[j + 1] == 'L') &&
      (Command[j + 2] == 'e' || Command[j + 2] == 'E') &&
      (Command[j + 3] == 'a' || Command[j + 3] == 'A') &&
      (Command[j + 4] == 'r' || Command[j + 4] == 'R') &&
      (Command[j + 5] == '\0')) {
    clearScreen();
    return;
  }
  if ((Command[j] == 'e' || Command[j] == 'E') && // ECHO
      (Command[j + 1] == 'c' || Command[j + 1] == 'C') &&
      (Command[j + 2] == 'h' || Command[j + 2] == 'H') &&
      (Command[j + 3] == 'o' || Command[j + 3] == 'O') &&
      (Command[j + 4] == ' ')) {
    newLine();
    if (VideoPosition >= 3840)
      scroll();
    j = j + 5;
    int i = 0;
    while (1) {
      toEcho[i] = Command[j];
      if (Command[j] == '\0')
        break;
      j++, i++;
    }
    if (VideoPosition >= 3840) {
      while (i >= 80) {
        scroll();
        i = i - 80;
      }
    }
    print((char *)toEcho);
    newLine();
    return;
  }
  if (Command[j] == '\0') { // Nothing does nothing
    newLine();
    return;
  }
  print("\n");
  commandError("Unknown command '");
  print(Command);
  printLn("'\n");
  VideoPosition = VideoPosition - 160;
  return;
}
