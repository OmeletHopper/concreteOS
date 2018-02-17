CPP_C = g++ -c
C_C = gcc -c
ASM_C = nasm
EXEC = kernel
CPP_FLAGS = -Wall -m32 -fno-stack-protector
C_FLAGS = -Wall -m32 -fno-stack-protector
ASM_FLAGS = -f elf32
CPP_LIBS = -I cpp/CoreBoot -I cpp/CoreHandlers -I cpp/CoreKeyboard -I cpp/CoreTerminal -I cpp/CoreVideo -I cpp/DetectCPU
OBJ = objects/

.PHONY: all CPU graphics handling linearBoot shell

all: CPU graphics handling linearBoot shell
	-mkdir bin

	ld -m elf_i386 -T link.ld -o bin/concreteOS.elf \
	CPU/CPU.o \
	graphics/graphics.o \
	handling/handling.o \
	linearBoot/linearBoot.o \
	shell/shell.o

clean: clean-linearBoot
	-rm -rf objects

clean-binaries:
	-rm -rf bin

CPU:
	@$(MAKE) -C CPU

clean-CPU:
	@$(MAKE) -C CPU clean

graphics:
	@$(MAKE) -C graphics

clean-graphics:
	@$(MAKE) -C graphics clean

handling:
	@$(MAKE) -C handling

clean-handling:
	@$(MAKE) -C handling clean

linearBoot:
	@$(MAKE) -C linearBoot

clean-linearBoot:
	@$(MAKE) -C linearBoot clean

shell:
	@$(MAKE) -C shell

clean-shell:
	@$(MAKE) -C shell clean
