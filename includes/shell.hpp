//
//  shell.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/11/17.
//

#ifndef CoreTerminal_h
#define CoreTerminal_h

extern unsigned int OpenedTerminal;

class CoreTerminal {

public:

    void CommandError(const char * str);
    void OpenShell(void);
    void RunCommand(char * Command);

};

static CoreTerminal CoreTerminal;

#endif /* CoreTerminal_h */
