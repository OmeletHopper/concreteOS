//
//  linearBoot.cpp
//  concreteOS
//
//  Created by Jonathan Archer on 10/10/17.
//

#include <linearBoot.hpp>

extern "C" void CoreBoot() {
  clearScreen();

  print("concreteOS ");
  print(version); // Print version
  print("-");
  print(build_number);
  print(" starting boot process on ");
  print(VendorString());
  print(" CPU.\n");

  printLn("concreteOS (C) Jonathan Archer 2018.\n");

  gdtEnable(); // Enable our GDT
  printMsg("Global Descriptor Table initialized.\n");

  idtEnable(); // Enable our IDT
  printMsg("Interrupt Descriptor Table initialized.\n");

  KeyboardHandler.Initialize(); // Enable keyboard
  printMsg("Keyboard driver initialized.\n");

  printErr("Kernel incomplete, dropping to internal shell.\n");

  Input.AddKeySetting = 1; // Set variable to 1, prints text to screen, writes
                           // to buffer, and passes to internal shell.
  printMsg("Keyboard input enabled.\n");

  newLine();
  CoreTerminal.openShell();
  refreshCursor();

  while (1)
    ; // Code should not return
  return;
}
