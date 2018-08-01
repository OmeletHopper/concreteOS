//
//  shell.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/11/17.
//

#ifndef shell_h
#define shell_h

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int OpenedTerminal;

void openShell();
void runCommand(char *);

#ifdef __cplusplus
}
#endif

#endif /* CoreTerminal_h */
