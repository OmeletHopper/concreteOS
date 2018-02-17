//
//  CoreVideo.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/12/17.
//

#include <stdarg.h>
#include <graphics.hpp>
#include <handlers.hpp>

char *vidptr = (char*)0xb8000;               // Video buffer start address
unsigned int video_position = 0;                    // Our position
unsigned int video_colorcode = 0x07;         // Colorcode
unsigned int j, i, x, y = 0;                 // 'Temp' variables

void CoreVideo::Newline(void) {

    video_position = video_position + (160 - video_position % (160));
    return;
}

void CoreVideo::UpdateCursor(void) {

    unsigned short position = video_position / 2;

    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char)(position&0xFF));

    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char)((position>>8)&0xFF));

}

void CoreVideo::Scroll(void) {

    if (video_position <= 160) {
        return;
    }
    for(i = 0; i < 25; i++){
        for (j = 0; j < 160; j++){
            vidptr[i * 160 + j] = vidptr[(i + 1) * 160 + j];
        }
    }
    video_position = video_position - 160;
    return;
}

void CoreVideo::ClearConsole(void) {


        j = 0;
        while(j < 80 * 25 * 2) {
            vidptr[j] = ' ';                    // Empty character
            vidptr[j+1] = 0x07;                 // Attribute for black background
            j = j + 2;
        }
    video_position = 0;
        return;
    }


void CoreVideo::PrintMessage(const char * str) {
        video_colorcode = 0x02;
        Print("[ OK ] ");
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


void CoreVideo::PrintError(const char * str) {
        video_colorcode = 0x04;
        Print("[ ERROR ] ");
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


void CoreVideo::Print(const char * str) {

        if(video_position >= 3840) { Scroll(); }

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

void CoreVideo::PrintLn(const char * str) {

        if(video_position >= 3840) { Scroll(); }

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
