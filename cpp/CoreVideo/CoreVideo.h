//
//  CoreVideo.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

using namespace std;

#ifndef CoreVideo_h
#define CoreVideo_h

class CoreVideo {

public:

    void Newline(void);
    void UpdateCursor(void);
    void Scroll(void);
    void ClearConsole(void);
    void PrintMessage(const char * str);
    void PrintError(const char * str);
    void PrintOne(const char * str);
    void Print(const char * str, ...);
    void PrintLn(const char * str, ...);

};

static CoreVideo CoreVideo;    // 'Enables' class for use in other functions

#endif // Defines CoreVideo_h
