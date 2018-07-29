//
//  graphics.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <stdarg.h>
#include <graphics.h>
#include <handlers.h>

char *videoBaseAddress = (char*)0xb8000;               // Video buffer start address
unsigned int videoPosition = 0;                    // Our position
unsigned int colorCode = 0x07;         // Colorcode
unsigned int j, i, x, y = 0;                 // 'Temp' variables

void Newline(void) {

    videoPosition = videoPosition + (160 - videoPosition % (160));
    return;
}

void UpdateCursor(void) {

    unsigned short position = videoPosition / 2;

    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char)(position&0xFF));

    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char)((position>>8)&0xFF));

}

void Scroll(void) {

    if (videoPosition <= 160) {
        return;
    }
    for(i = 0; i < 25; i++){
        for (j = 0; j < 160; j++){
            videoBaseAddress[i * 160 + j] = videoBaseAddress[(i + 1) * 160 + j];
        }
    }
    videoPosition = videoPosition - 160;
    return;
}

void ClearConsole(void) {


        j = 0;
        while(j < 80 * 25 * 2) {
            videoBaseAddress[j] = ' ';                    // Empty character
            videoBaseAddress[j+1] = 0x07;                 // Attribute for black background
            j = j + 2;
        }
    videoPosition = 0;
        return;
    }


void PrintMessage(const char * str) {
        colorCode = 0x02;
        Print("[ OK ] ");
        colorCode = 0x07;
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character

            if (str[j] == '\n') { Newline(); j++; }
            else {
                videoBaseAddress[videoPosition] = str[j];
                videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
                ++j;                                            // Increment
                videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
            }
        }
        Newline();
        return;
    }


void PrintError(const char * str) {
        colorCode = 0x04;
        Print("[ ERROR ] ");
        colorCode = 0x07;
        j = 0;
        while(str[j] != '\0') {                             // While not terminating character

            if (str[j] == '\n') { Newline(); j++; }
            else {
                videoBaseAddress[videoPosition] = str[j];
                videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
                ++j;                                            // Increment
                videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
            }
        }
        Newline();
        return;
    }


void Print(const char * str) {

        if(videoPosition >= 3840) { Scroll(); }

        j = 0;
        while(str[j] != '\0') {                             // While not terminating character

            if (str[j] == '\n') { Newline(); j++; }
            else {
                videoBaseAddress[videoPosition] = str[j];
                videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
                ++j;                                            // Increment
                videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
            }
        }
        return;
    }

void PrintLn(const char * str) {

        if(videoPosition >= 3840) { Scroll(); }

        j = 0;
        while(str[j] != '\0') {                             // While not terminating character

            if (str[j] == '\n') { Newline(); j++; }
            else {
                videoBaseAddress[videoPosition] = str[j];
                videoBaseAddress[videoPosition+1] = colorCode;     // Color attribute
                ++j;                                            // Increment
                videoPosition = videoPosition + 2;            // Also increment, count for attribute byte
            }

        }
        Newline();
        return;
    }
