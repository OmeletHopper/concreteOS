//
//  keyHandler.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <keyMaps.h>
#include <linearBoot.hpp>

int keyboardHandlerEnabled = 0;
int keyPosition = 0;

int caseState = 0;

extern "C" void keyboardHandlerMain(void) {
  if(keyboardHandlerEnabled != 1) { return; }
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

      keyPosition = keyPosition - 1;
      keyLine[keyPosition] = ' ';

      CoreVideo.UpdateCursor();
      return;
    }
    else if(keyCode == 0x1C) {
      keyLine[keyPosition] = '\0';
      KeyTaker(keyLine);
      keyPosition = 0;
      keyLine = 0x00;
      return;
    }
    else if(keyCode == 0x3A) {
      if(caseState != 1) { caseState = 1; return; }
      else if(caseState == 1) { caseState = 0; return; }
      return;
    }

    if(videoPosition >= 3840) { CoreVideo.Scroll(); }

    /* 90 is the amount in each 'section' of our key map. */

    videoBaseAddress[videoPosition++] = keyMap[keyCode + (90 * caseState)];
    videoBaseAddress[videoPosition++] = 0x07;
    keyLine[keyPosition] = keyMap[keyCode + (90 * caseState)];
    keyPosition++;
    CoreVideo.UpdateCursor();
    return;
  }
}
