//
//  shell.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <graphics.h>
#include <shell.h>

unsigned int OpenedTerminal;
unsigned char *toEcho = 0x00;

void toLower(char *str) {
  while (*str != '\0') {
    if (*str >= 65 && *str <= 90)
      *str += +32;
    str++;
  }
}

int strcmp(char string1[], char string2[]) {
  for (int i = 0;; i++) {
    if (string1[i] != string2[i])
      return string1[i] < string2[i] ? -1 : 1;
    if (string1[i] == '\0')
      return 0;
  }
}

void strcpy(char dest[], const char source[]) {
  for (int i = 0; (dest[i] = source[i]); i++)
    if (dest[i] == '\0')
      break;
}

void strncpy(char dest[], const char source[], int limit) {
  for (int i = 0; (dest[i] = source[i]); i++)
    if (dest[i] == '\0' || i == limit)
      break;
}

void openShell() {
  ColorCode = 0x02;
  print("> ");
  if (VideoPosition >= 3840)
    scroll();
  ColorCode = 0x07;
  OpenedTerminal = VideoPosition;
  return;
}

void runCommand(char *Command) {
  while (Command[0] == ' ')
    Command++;

  char *LowerCommand;
  strcpy(LowerCommand, Command);
  toLower(LowerCommand);

  char *First5;
  strncpy(First5, LowerCommand, 4);

  if (!strcmp(LowerCommand, "scroll")) {
    scroll();
    newLine();
  } else if (!strcmp(LowerCommand, "clear"))
    clearScreen();
  else if (!strcmp(First5, "echo ")) {
    newLine();
    if (VideoPosition >= 3840)
      scroll();
    Command += 5;
    print(Command);
    newLine();
  } else if (Command[0] == '\0') { // Nothing does nothing
    newLine();
  } else {
    print("\n");
    printErr("Unknown command '");
    print(Command);
    printLn("'");
  }
  return;
}
