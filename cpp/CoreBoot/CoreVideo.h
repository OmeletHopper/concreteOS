//
//  CoreVideo.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <stdarg.h>

using namespace std;

#ifndef CoreVideo_h
#define CoreVideo_h
#endif // Defines CoreVideo_h

char *vidptr = (char*)0xb8000;               // Video buffer start address
unsigned int video_position = 0;                    // Our position
unsigned int video_colorcode = 0x07;         // Colorcode
unsigned int j, i, x, y = 0;                 // 'Temp' variables

class CoreVideo {

public:
    
    void Newline(void) { video_position = video_position + (160 - video_position % (160)); }
    
    void ClearConsole(void) {
        
             j = 0;
            while(j < 80 * 25 * 2) {
            vidptr[j] = ' ';                    // Empty character
            vidptr[j+1] = 0x07;                 // Attribute for black background
            j = j + 2;
        }
        return;
    }
    
    
    void PrintMessage(const char * str) {
        video_colorcode = 0x02;
        PrintOne("[ OK ] ");
        video_colorcode = 0x07;
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character
            
            if (str[j] == '\n') { Newline(); j++; }
            else {
                vidptr[video_position] = str[j];
                vidptr[video_position+1] = video_colorcode;     // Color attribute
                ++j;                                            // Increment
                video_position = video_position + 2;            // Also increment, count for attribute byte
            }
        }
        Newline();
        return;
    }
    
    
    void PrintError(const char * str) {
        video_colorcode = 0x04;
        PrintOne("[ ERROR ] ");
        video_colorcode = 0x07;
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character
            
            if (str[j] == '\n') { Newline(); j++; }
            else {
                vidptr[video_position] = str[j];
                vidptr[video_position+1] = video_colorcode;     // Color attribute
                ++j;                                            // Increment
                video_position = video_position + 2;            // Also increment, count for attribute byte
            }
        }
        Newline();
        return;
    }
    
    void PrintOne(const char * str) {
        
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character
            
            if (str[j] == '\n') { Newline(); j++; }
            else {
                vidptr[video_position] = str[j];
                vidptr[video_position+1] = video_colorcode;     // Color attribute
                ++j;                                            // Increment
                video_position = video_position + 2;            // Also increment, count for attribute byte
            }
        }
        return;
    }
    
    void Print(const char * str, ...) {
        
        unsigned int i;
        
        va_list arguments;
        va_start(arguments, str);
        
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character
            
            if (str[j] == '%') {
                j++;
                switch(str[j]) {
                        case 'c' :
                        i = j;
                        i = va_arg(arguments,int);        //Fetch char argument
                        PrintOne((char *)i);
                        j = i;
                }
            }
            if (str[j] == '\n') { Newline(); j++; }
            else {
                vidptr[video_position] = str[j];
                vidptr[video_position+1] = video_colorcode;     // Color attribute
                ++j;                                            // Increment
                video_position = video_position + 2;            // Also increment, count for attribute byte
            }
        }
        va_end(arguments);
        return;
    }

    void PrintLn(const char * str, ...) {
        
        unsigned int i;
        
        va_list arguments;
        va_start(arguments, str);

        j = 0;
        while(str[j] != '\0') {                             // While not terminating character
            
            if (str[j] == '%') {
                j++;
                switch(str[j]) {
                        case 'c' :
                        i = j;
                        i = va_arg(arguments,int);        //Fetch char argument
                        Print((char *)i);
                        j = i;
                }
            }
            if (str[j] == '\n') { Newline(); j++; }
            else {
                vidptr[video_position] = str[j];
                vidptr[video_position+1] = video_colorcode;     // Color attribute
                ++j;                                            // Increment
                video_position = video_position + 2;            // Also increment, count for attribute byte
            }
            
        }
        va_end(arguments);
        Newline();
        return;
    }

};

static CoreVideo CoreVideo;    // 'Enables' class for use in other functions
