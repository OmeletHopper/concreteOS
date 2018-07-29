//
//  linearBoot.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <linearBoot.hpp>

extern "C" void CoreBoot(void)
{
  ClearConsole();

  Print("concreteOS ");
  Print(version); // Print version
  Print("-");
  Print(build_number);
  Print(" starting boot process on ");
  Print(DetectCPU.VendorString());
  Print(" CPU.\n");

  PrintLn("concreteOS (C) Jonathan Archer 2018.\n");

  EnableGDT();  // Enable our GDT
  PrintMessage("Global Descriptor Table initialized.");

  EnableIDT();  // Enable our IDT
  PrintMessage("Interrupt Descriptor Table initialized.");

  KeyboardHandler.Initialize(); // Enable keyboard
  PrintMessage("Keyboard driver initialized.");

  PrintError("Kernel incomplete, dropping to internal shell."); // Development not done

  Input.addKeySetting = 1; // Set variable to 1, prints text to screen, writes to buffer, and passes to internal shell.
  PrintMessage("Keyboard input enabled.");

  Newline();
  CoreTerminal.OpenShell(); // Opens shell and prints a > as well as sets backspace area
  UpdateCursor();

  while(1); // Code should not return
  return;
}
