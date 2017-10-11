//
//  CoreBoot.c
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

extern "C" void EnableGDT(), EnableIDT();

#include "CoreHandlers.h"
#include "CoreTerminal.h"

extern "C" void CoreBoot(void) {
    
    const char * version = "0.0.1";
        
    CoreVideo.ClearConsole();
    
    CoreVideo.Print("concreteOS version %c", version);
    CoreVideo.PrintLn("starting boot process.");
    
    CoreVideo.PrintLn("concreteOS (C) Jonathan Archer 2017.\n");
    
    EnableGDT();
    CoreVideo.PrintMessage("Global Descriptor Table initialized.");
    
    EnableIDT();
    CoreVideo.PrintMessage("Interrupt Descriptor Table initialized.");
    
    KeyboardHandler.Initialize();
    CoreVideo.PrintMessage("Keyboard driver initialized.");
    
    KeyboardHandlerEnabled = 1;
    CoreVideo.PrintMessage("Keyboard input enabled.");
    
    CoreVideo.PrintError("Kernel not complete, dropping to internal shell.");
    
    //while(1) {
    
        CoreTerminal.OpenShell();
        
        //char * UserInput = CoreIO.GetKeys();
        
        //CoreTerminal.RunCommand(UserInput);
        
    //}
    
    while(1);
    return;
}
