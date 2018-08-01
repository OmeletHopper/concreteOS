//
//  io.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 2/18/18.
//

#include <input.hpp>
#include <keyboard.h>
#include <linearBoot.hpp>

char *keyBuffer = 0x00;
char *lastKeyBuffer = 0x00;
int keyBufferSize = 0;
int lastKeyBufferSize = 0;
int keyBufferPosition = 0;
int io::AddKeySetting = 0;

void io::addKey(struct TypedCharacter inKey) {
  if (AddKeySetting != 1)
    return;
  if (inKey.Code == ENTER) {
    keyBuffer[keyBufferSize] = '\0';
    lastKeyBuffer = keyBuffer, lastKeyBufferSize = keyBufferSize;
    keyBufferPosition = 0, keyBufferSize = 0;
    runCommand(keyBuffer); // Runs given input
    openShell();           // Re-opens shell
    refreshCursor();
    return;
  }
  switch (inKey.Code) {

  case BACKSPACE:
    if (VideoPosition <= OpenedTerminal)
      return;
    VideoPosition--;
    VideoPointer[VideoPosition] = 0x07;
    VideoPosition--;
    VideoPointer[VideoPosition] = ' ';
    keyBufferPosition--, keyBufferSize--;
    keyBuffer[keyBufferPosition] = ' ';
    refreshCursor();
    return;

  case LEFT:
    if (VideoPosition <= OpenedTerminal)
      return;
    VideoPosition = VideoPosition - 2;
    keyBufferPosition--;
    refreshCursor();
    return;

  case RIGHT:
    if (keyBufferPosition >= keyBufferSize)
      return;
    VideoPosition = VideoPosition + 2;
    keyBufferPosition++;
    refreshCursor();
    return;

  case UP:
    int j = 0;
    VideoPosition = OpenedTerminal;
    while (j <= keyBufferSize) {
      VideoPointer[VideoPosition++] = ' ';
      VideoPointer[VideoPosition++] = 0x07;
      j++;
    }
    VideoPosition = OpenedTerminal;
    keyBuffer = lastKeyBuffer;
    keyBufferSize = lastKeyBufferSize;
    keyBufferPosition = keyBufferSize;
    j = 0;
    print(lastKeyBuffer);
    refreshCursor();
    return;
  }

  keyBuffer[keyBufferPosition] = KeyMap[inKey.Code + (90 * inKey.State)];
  if (keyBufferPosition == keyBufferSize)
    keyBufferSize++;
  keyBufferPosition++;

  VideoPointer[VideoPosition++] = KeyMap[inKey.Code + (90 * inKey.State)];
  VideoPointer[VideoPosition++] = 0x07;
  refreshCursor();

  return;
}
