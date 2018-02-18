//
//  keyHandler.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <keyMaps.h>
#include <linearBoot.hpp>

int keyboardHandlerEnabled  = 0;
int keyLinePosition         = 0;
int keyLineSize             = 0;

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
    unsigned char keyCode = read_port(KEYBOARD_DATA_PORT);

    if(keyCode == LSHIFT_DOWN) {
      caseState++;
      return;
    }

    if(keyCode == LSHIFT_UP) {
      caseState--;
      return;
    }

    if((keyCode & 128) == 128) return;  // If released.

    if(keyCode < 0) return;

    if(keyCode == BACKSPACE) {
      if(videoPosition <= OpenedTerminal) return;

      videoPosition--;
      videoBaseAddress[videoPosition] = 0x07;
      videoPosition--;
      videoBaseAddress[videoPosition] = ' ';

      keyLinePosition--;
      keyLineSize--;
      keyLine[keyLinePosition] = ' ';

      CoreVideo.UpdateCursor();
      return;
    }

    else if(keyCode == LEFT) {
      if(videoPosition <= OpenedTerminal) return;
      videoPosition = videoPosition - 2;
      keyLinePosition--;
      CoreVideo.UpdateCursor();
      return;
    }

    else if(keyCode == RIGHT) {
      if(keyLinePosition == keyLineSize) return;
      videoPosition = videoPosition + 2;
      keyLinePosition++;
      CoreVideo.UpdateCursor();
      return;
    }

    else if(keyCode == ENTER) {
      keyLine[keyLineSize] = '\0';
      KeyTaker(keyLine);
      keyLinePosition = 0;
      keyLineSize = 0;
      keyLine = 0x00;
      return;
    }

    else if(keyCode == CAPS_LOCK) {
      if(caseState != 2) { caseState = 2; return; }
      else if(caseState == 2) { caseState = 0; return; }
      return;
    }

    if(videoPosition >= 3840) { CoreVideo.Scroll(); }

    /* 90 is the amount in each 'section' of our key map. */
    videoBaseAddress[videoPosition++] = keyMap[keyCode + (90 * caseState)];
    videoBaseAddress[videoPosition++] = 0x07;
    CoreVideo.UpdateCursor();

    keyLine[keyLinePosition] = keyMap[keyCode + (90 * caseState)];
    keyLinePosition++;
    if((keyLinePosition - 1) < keyLineSize) return;
    keyLineSize++;

    return;
  }
}
