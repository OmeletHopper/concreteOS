CPP_C = i386-elf-g++ -c
C_C = i386-elf-gcc -c
ASM_C = nasm
EXEC = kernel
CPP_FLAGS = -Wall -m32
C_FLAGS = -Wall -m32
ASM_FLAGS = -f elf32
CPP_LIBS = -I cpp/CoreBoot
OBJ = objects/

all:
	$(ASM_C) assembly/CoreBoot/CoreBoot.s -o objects/asmCoreBoot.o $(ASM_FLAGS)
	$(ASM_C) $(ASM_FLAGS) assembly/CoreBoot/CoreIO.s -o objects/asmCoreIO.o
	$(C_C) c/CoreBoot/CoreGDT.c -o objects/cCoreGDT.o $(C_FLAGS)
	$(C_C) c/CoreBoot/CoreIDT.c -o objects/cCoreIDT.o $(C_FLAGS)
	$(CPP_C) cpp/CoreBoot/CoreBoot.cpp -o objects/cppCoreBoot.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreHandlers/CoreKeyboard.cpp -o objects/cppCoreKeyboard.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreBoot/CoreVideo.cpp -o objects/cppCoreVideo.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreBoot/CoreTerminal.cpp -o objects/cppCoreTerminal.o $(CPP_FLAGS) $(CPP_LIBS)
	i386-elf-ld -m elf_i386 -T link.ld -o bin/concreteOS.elf $(OBJ)asmCoreBoot.o $(OBJ)asmCoreIO.o $(OBJ)cppCoreBoot.o $(OBJ)cppCoreVideo.o $(OBJ)cppCoreTerminal.o $(OBJ)cCoreGDT.o $(OBJ)cCoreIDT.o $(OBJ)cppCoreKeyboard.o

clean:
