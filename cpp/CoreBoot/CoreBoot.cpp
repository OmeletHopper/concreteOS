//
//  CoreBoot.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <CoreBoot.h>

const char * version = "0.0.2 prerelease";                                          // Version

unsigned long ebx, unused;

extern "C" void CoreBoot(void) {
    
    CoreVideo.ClearConsole();
    
    CoreVideo.Print("concreteOS version %c", version);                              // Print version
    CoreVideo.Print("starting boot process on ");
    
    CoreVideo.Print(CPUvendor());
    
    CoreVideo.PrintLn("concreteOS (C) Jonathan Archer 2017.\n");                    // (C) message
    
    EnableGDT();                                                                    // Enable our GDT
    CoreVideo.PrintMessage("Global Descriptor Table initialized.");
    
    EnableIDT();                                                                    // Enable our IDT
    CoreVideo.PrintMessage("Interrupt Descriptor Table initialized.");
    
    KeyboardHandler.Initialize();                                                   // Enable keyboard
    CoreVideo.PrintMessage("Keyboard driver initialized.");
        
    KeyboardHandlerEnabled = 1;                                                     // Enable keyboard input
    CoreVideo.PrintMessage("Keyboard input enabled.");
    
    CoreVideo.PrintError("Kernel not complete, dropping to internal shell.");       // Development not done
    
    CoreVideo.Print("\n");
    CoreTerminal.OpenShell();                                                       // Opens shell and prints a > as well as sets backspace area
    CoreVideo.UpdateCursor();
    
    while(1);                                                                       // Code should not return
    return;
}

void KeyTaker(char * Keys) {
    
    CoreTerminal.RunCommand(Keys);                                                  // Runs given input
    CoreTerminal.OpenShell();                                                       // Re-opens shell
    CoreVideo.UpdateCursor();
    
    return;
}
