#!/bin/sh

#  build.sh
#  concreteOS
#
#  Created by Jonathan Archer on 10/10/17.
#  

cd ./assembly

nasm -f elf32 ./CoreBoot/CoreBoot.s -o ../asmCoreBoot.o
nasm -f elf32 ./CoreBoot/CoreIO.s -o ../asmCoreIO.o

cd ../c
i386-elf-gcc -m32 -c ./CoreBoot/CoreGDT.c -o ../cCoreGDT.o
i386-elf-gcc -m32 -c ./CoreBoot/CoreIDT.c -o ../cCoreIDT.o

cd ../cpp

i386-elf-g++ -m32 -c ./CoreBoot/CoreBoot.cpp -o ../cppCoreBoot.o
i386-elf-g++ -m32 -c ./CoreHandlers/CoreKeyboard.cpp -o ../cppCoreKeyboard.o

cd ../

i386-elf-ld -m elf_i386 -T link.ld -o kernel asmCoreBoot.o asmCoreIO.o cppCoreBoot.o cCoreGDT.o cCoreIDT.o cppCoreKeyboard.o
