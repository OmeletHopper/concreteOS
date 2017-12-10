//
//  CoreTerminal.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/11/17.
//

#ifndef CoreTerminal_h
#define CoreTerminal_h
#endif /* CoreTerminal_h */

extern unsigned int video_colorcode;
extern unsigned int video_position;

extern unsigned int OpenedTerminal;
extern int j;

extern char *vidptr;

class CoreTerminal {

public:

    void CommandError(const char * str);
    void OpenShell(void);
    void RunCommand(char * Command);

};

static CoreTerminal CoreTerminal;
