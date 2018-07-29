//
//  io.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 2/18/18.
//

#include <input.hpp>
#include <linearBoot.hpp>
#include <keyboard.h>

char * keyBuffer          = 0x00;
char * lastKeyBuffer      = 0x00;
int keyBufferSize         = 0;
int lastKeyBufferSize     = 0;
int keyBufferPosition     = 0;
int io::addKeySetting     = 0;

void io::addKey(struct typedCharacter inKey)
{
  if(addKeySetting != 1) return;
  if(inKey.Code == ENTER) {
    keyBuffer[keyBufferSize] = '\0';
    lastKeyBuffer = keyBuffer, lastKeyBufferSize = keyBufferSize;
    keyBufferPosition = 0, keyBufferSize = 0;
    CoreTerminal.RunCommand(keyBuffer);  // Runs given input
    CoreTerminal.OpenShell(); // Re-opens shell
    UpdateCursor();
    return;
  }
  switch(inKey.Code) {

  case BACKSPACE:
    if(videoPosition <= OpenedTerminal) return;
    videoPosition--;
    videoBaseAddress[videoPosition] = 0x07;
    videoPosition--;
    videoBaseAddress[videoPosition] = ' ';
    keyBufferPosition--, keyBufferSize--;
    keyBuffer[keyBufferPosition] = ' ';
    UpdateCursor();
    return;

  case LEFT:
    if(videoPosition <= OpenedTerminal) return;
    videoPosition = videoPosition - 2;
    keyBufferPosition--;
    UpdateCursor();
    return;

  case RIGHT:
    if(keyBufferPosition >= keyBufferSize) return;
    videoPosition = videoPosition + 2;
    keyBufferPosition++;
    UpdateCursor();
    return;

  case UP:
    j = 0;
    videoPosition = OpenedTerminal;
    while(j <= keyBufferSize) {
      videoBaseAddress[videoPosition++] = ' ';
      videoBaseAddress[videoPosition++] = 0x07;
      j++;
    }
    videoPosition = OpenedTerminal;
    keyBuffer = lastKeyBuffer;
    keyBufferSize = lastKeyBufferSize;
    keyBufferPosition = keyBufferSize;
    j = 0; i = 0;
    Print(lastKeyBuffer);
    UpdateCursor();
    return;
  }

  keyBuffer[keyBufferPosition] = keyMap[inKey.Code + (90 * inKey.State)];
  if(keyBufferPosition == keyBufferSize) keyBufferSize++;
  keyBufferPosition++;

  videoBaseAddress[videoPosition++] = keyMap[inKey.Code + (90 * inKey.State)];
  videoBaseAddress[videoPosition++] = 0x07;
  UpdateCursor();

  return;
}
