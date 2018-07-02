BUILD_NUMBER	?= $(shell git log --pretty=format:'%h' -n 1)
VERSION		?= v0.0.3
KNAME		:= concreteOS.elf

SRC		:= src

CXX		:= clang -c
CC		:= clang -c
CFLAGS		:= -target i386-none-elf
CFLAGS		:= -Wall -m32 -fno-stack-protector
CFLAGS		+= -I $(SRC)/includes
CFLAGS		+= -D version=\"$(VERSION)\" -D build_number=\"$(BUILD_NUMBER)\"
CXXFLAGS	:= $(CFLAGS)

AS		:= nasm
ASFLAGS		:= -f elf32

LD		:= gold
LDFLAGS		:= -m elf_i386 -T link.ld -o $(KNAME)

SRCFILES	:= $(wildcard $(SRC)/arch/i386/*.s) \
		   $(wildcard $(SRC)/*.s) $(wildcard $(SRC)/*.c) \
		   $(wildcard $(SRC)/*.cpp)
OBJFILES	:= $(patsubst %.s, %.o, \
		   $(patsubst %.c, %.o, \
		   $(patsubst %.cpp, %.o, \
		   $(SRCFILES))))

.PHONY: all test clean-all clean clean-bin

all: $(OBJFILES)
	$(LD) $(LDFLAGS) $(OBJFILES)
	@echo Done building version $(VERSION).

test: all
	qemu-system-i386 -kernel ../$(BIN)

clean-all: clean clean-bin

clean:
	rm -f $(OBJFILES)

clean-bin:
	-rm -f ../concreteOS.elf
