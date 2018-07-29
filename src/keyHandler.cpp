//
//  keyHandler.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <linearBoot.hpp>

int caseState         = 0;
unsigned char keyCode = 0x00;

struct typedCharacter KEY;

extern "C" void keyboardHandlerMain(void)
{
  unsigned char status;

  /* Write EOI */
  writePort(0x20, 0x20);

  status = readPort(KEYBOARD_STATUS_PORT);

  /* Lowest bit of status will be set if buffer is not empty */
  if(status & 0x01) {
    if(keyCode < 0) return;

    keyCode = readPort(KEYBOARD_DATA_PORT);
    switch(keyCode)
    {
      case LSHIFT_DOWN:
        caseState++;
        return;
      case LSHIFT_UP:
        caseState--;
        return;
      case CAPS_LOCK:
        if(caseState != 2) { caseState = 2; return; }
        else if(caseState == 2) { caseState = 0; return; }
        return;
    }

    if((keyCode & 128) == 128) return; // If released.
    if(videoPosition >= 3840) { Scroll(); }

    KEY.Code      = keyCode;
    KEY.State     = caseState;
    Input.addKey(KEY);
    return;
  }
}
