//
//  graphics.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <graphics.h>

unsigned short ColorCode = 0x07;
char *VideoPointer = (char *)0xb8000; // Video buffer start address
int VideoPosition = 0;                // Our position

void newLine() { VideoPosition += (160 - VideoPosition % (160)); }

void refreshCursor() {
  unsigned short position = VideoPosition / 2;

  writePort(0x3D4, 0x0F);
  writePort(0x3D5, (unsigned char)(position & 0xFF));

  writePort(0x3D4, 0x0E);
  writePort(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

void scroll() {
  if (VideoPosition <= 160)
    return;

  for (int i = 0; i < 25; i++)
    for (int j = 0; j < 160; j++)
      VideoPointer[i * 160 + j] = VideoPointer[(i + 1) * 160 + j];
  VideoPosition -= 160;
}

void clearScreen() {
  int j = 0;
  while (j < 80 * 25 * 2) {
    VideoPointer[j] = ' ';      // Empty character
    VideoPointer[j + 1] = 0x07; // Attribute for black background
    j += 2;
  }
  VideoPosition = 0;
}

void printMsg(const char *String) {
  ColorCode = 0x02;
  print("{ OKAY } ");
  ColorCode = 0x07;
  print(String);
  newLine();
}

void printErr(const char *String) {
  ColorCode = 0x04;
  print("{ ERROR } ");
  ColorCode = 0x07;
  print(String);
  newLine();
}

void print(const char *str) {
  if (VideoPosition >= 3840)
    scroll();
  int j = 0;
  while (str[j] != '\0') { // While not terminating
    if (str[j] == '\n') {
      newLine();
      j++;
    } else {
      VideoPointer[VideoPosition] = str[j];
      VideoPointer[VideoPosition + 1] = ColorCode;
      j++;
      VideoPosition += 2;
    }
  }
}

void printLn(const char *String) {
  print(String);
  newLine();
}
