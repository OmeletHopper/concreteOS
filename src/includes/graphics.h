//
//  graphics.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#ifndef graphics_h
#define graphics_h

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int colorCode;
extern unsigned int videoPosition;
extern char * videoBaseAddress;
extern unsigned int i;
extern unsigned int j;

void Newline();
void UpdateCursor();
void Scroll();
void ClearConsole();
void PrintMessage(const char * str);
void PrintError(const char * str);
void PrintOne(const char * str);
void Print(const char * str);
void PrintLn(const char * str);

#ifdef __cplusplus
}
#endif

#endif // Defines CoreVideo_h
