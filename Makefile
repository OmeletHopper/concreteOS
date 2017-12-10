CPP_C = g++ -c
C_C = gcc -c
ASM_C = nasm
EXEC = kernel
CPP_FLAGS = -Wall -m32 -fno-stack-protector
C_FLAGS = -Wall -m32 -fno-stack-protector
ASM_FLAGS = -f elf32
CPP_LIBS = -I cpp/CoreBoot -I cpp/CoreHandlers -I cpp/CoreKeyboard -I cpp/CoreTerminal -I cpp/CoreVideo
OBJ = objects/

all:
	-mkdir objects
	-mkdir bin

	$(ASM_C) assembly/CoreBoot/CoreBoot.s -o objects/asmCoreBoot.o $(ASM_FLAGS)
	$(ASM_C) $(ASM_FLAGS) assembly/CoreIO/CoreIO.s -o objects/asmCoreIO.o
	$(C_C) c/CoreGDT/CoreGDT.c -o objects/cCoreGDT.o $(C_FLAGS)
	$(C_C) c/CoreIDT/CoreIDT.c -o objects/cCoreIDT.o $(C_FLAGS)
	$(CPP_C) cpp/CoreBoot/CoreBoot.cpp -o objects/cppCoreBoot.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreKeyboard/CoreKeyboard.cpp -o objects/cppCoreKeyboard.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreVideo/CoreVideo.cpp -o objects/cppCoreVideo.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreTerminal/CoreTerminal.cpp -o objects/cppCoreTerminal.o $(CPP_FLAGS) $(CPP_LIBS)
	ld -m elf_i386 -T link.ld -o bin/concreteOS.elf $(OBJ)asmCoreBoot.o $(OBJ)asmCoreIO.o $(OBJ)cppCoreBoot.o $(OBJ)cppCoreVideo.o $(OBJ)cppCoreTerminal.o $(OBJ)cCoreGDT.o $(OBJ)cCoreIDT.o $(OBJ)cppCoreKeyboard.o

clean:
	-rm -rf objects

clean-binaries:
	-rm -rf bin
