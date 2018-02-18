//
//  keyHandler.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <keyMaps.h>
#include <linearBoot.hpp>

int KeyboardHandlerEnabled = 0;
int KeyPosition = 0;

int capslock = 0, shiftpressed = 0;

extern "C" void keyboard_handler_main(void) {
  if(KeyboardHandlerEnabled != 1) { return; }
  unsigned char status;

  /* Write EOI */
  write_port(0x20, 0x20);

  status = read_port(KEYBOARD_STATUS_PORT);
  /* Lowest bit of status will be set if buffer is not empty */
  if (status & 0x01) {

    char * keyLine = 0x00;
    char keyCode = read_port(KEYBOARD_DATA_PORT);

    if(keyCode < 0) return;
    if(keyCode == 0x0E) {
      if(videoPosition <= OpenedTerminal) return;

      videoPosition = videoPosition - 2;
      videoBaseAddress[videoPosition] = ' ';
      videoPosition = videoPosition + 1;
      videoBaseAddress[videoPosition] = 0x07;
      videoPosition = videoPosition - 1;

      KeyPosition = KeyPosition - 1;
      keyLine[KeyPosition] = ' ';

      CoreVideo.UpdateCursor();
      return;
    }
    else if(keyCode == 0x1C) {
      keyLine[KeyPosition] = '\0';
      KeyTaker(keyLine);
      KeyPosition = 0;
      keyLine = 0x00;
      return;
    }
    else if(keyCode == 0x3A) {
      if(capslock != 1) { capslock = 1; return; }
      else if(capslock != 0) { capslock = 0; return; }
      return;
    }

    if(videoPosition >= 3840) { CoreVideo.Scroll(); }
    if(shiftpressed != 0) {
      videoBaseAddress[videoPosition++] = keyboard_map_shift[keyCode];
      videoBaseAddress[videoPosition++] = 0x07;
      keyLine[KeyPosition] = keyboard_map_shift[keyCode];
      KeyPosition++;
      CoreVideo.UpdateCursor();
      return;
    }
    else if(capslock != 1) {
      videoBaseAddress[videoPosition++] = keyboard_map[keyCode];
      videoBaseAddress[videoPosition++] = 0x07; keyLine[KeyPosition] = keyboard_map[keyCode];
      KeyPosition++; CoreVideo.UpdateCursor(); return;
    }
    else if(capslock != 0) {
      videoBaseAddress[videoPosition++] = keyboard_map_uppercase[keyCode];
      videoBaseAddress[videoPosition++] = 0x07;
      keyLine[KeyPosition] = keyboard_map_uppercase[keyCode];
      CoreVideo.UpdateCursor();
      KeyPosition++;
      return;
    }
  }
}
