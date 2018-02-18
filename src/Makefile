include ./configuration.mk

BIN			:= concreteOS.elf

LFLAGS	:= -m elf_i386 -T link.ld -o ../$(BIN)

.PHONY: all CPU graphics handling linearBoot shell

all: CPU graphics handling linearBoot shell
	$(LD) $(LFLAGS) \
	CPU/CPU.o \
	graphics/graphics.o \
	handling/handling.o \
	linearBoot/linearBoot.o \
	shell/shell.o

test:
	qemu-system-i386 -kernel ../$(BIN)

clean: clean-CPU clean-graphics clean-handling clean-linearBoot clean-shell

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
