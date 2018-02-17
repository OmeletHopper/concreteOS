CC			:= g++ -c
GCC			:= gcc -c
CFLAGS	:= -Wall -m32 -fno-stack-protector
CFLAGS	+= -I ../includes

AS			:= nasm
AFLAGS	:= -f elf32

LD			:= ld
LFLAGS	:= -m elf_i386 -r -o handling.o

all:
	$(GCC) GDT.c -o GDT.o $(CFLAGS)
	$(GCC) IDT.c -o IDT.o $(CFLAGS)
	$(CC) keyHandler.cpp -o keyHandler.o $(CFLAGS)
	$(AS) handlers.s -o handlers.o $(AFLAGS)
	$(LD)	$(LFLAGS) GDT.o IDT.o keyHandler.o handlers.o

clean:
	rm -f *~ *.o
