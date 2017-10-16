CPP_C = i386-elf-g++ -c
C_C = i386-elf-gcc -c
ASM_C = nasm
EXEC = kernel
CPP_FLAGS = -Wall -m32
C_FLAGS = -Wall -m32
ASM_FLAGS = -f elf32
CPP_LIBS = -I cpp/CoreBoot

all:
	$(ASM_C) assembly/CoreBoot/CoreBoot.s -o asmCoreBoot.o $(ASM_FLAGS)
	$(ASM_C) $(ASM_FLAGS) assembly/CoreBoot/CoreIO.s -o asmCoreIO.o
	$(C_C) c/CoreBoot/CoreGDT.c -o cCoreGDT.o $(C_FLAGS)
	$(C_C) c/CoreBoot/CoreIDT.c -o cCoreIDT.o $(C_FLAGS)
	$(CPP_C) cpp/CoreBoot/CoreBoot.cpp -o cppCoreBoot.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreHandlers/CoreKeyboard.cpp -o cppCoreKeyboard.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreBoot/CoreVideo.cpp -o cppCoreVideo.o $(CPP_FLAGS) $(CPP_LIBS)
	$(CPP_C) cpp/CoreBoot/CoreTerminal.cpp -o cppCoreTerminal.o $(CPP_FLAGS) $(CPP_LIBS)
	i386-elf-ld -m elf_i386 -T link.ld -o kernel asmCoreBoot.o asmCoreIO.o cppCoreBoot.o cppCoreVideo.o cppCoreTerminal.o cCoreGDT.o cCoreIDT.o cppCoreKeyboard.o

clean:
