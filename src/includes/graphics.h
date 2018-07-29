//
//  graphics.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <handlers.h>

#ifndef graphics_h
#define graphics_h

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned short ColorCode;
extern char *VideoPointer;
extern int VideoPosition;

void newLine();
void refreshCursor();
void scroll();
void clearScreen();
void printMsg(const char *);
void printErr(const char *);
void print(const char *);
void printLn(const char *);

#ifdef __cplusplus
}
#endif

#endif
