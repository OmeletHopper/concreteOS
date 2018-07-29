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
  void commandError(const char *);
  void openShell();
  void runCommand(char *);
};

static CoreTerminal CoreTerminal;

#endif /* CoreTerminal_h */
