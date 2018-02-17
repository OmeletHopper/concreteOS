NAME		:= linearBoot

CC			:= g++ -c
CFLAGS	:= -Wall -m32 -fno-stack-protector
CFLAGS	+= -I ../includes

AS			:= nasm
AFLAGS	:= -f elf32

LD			:= ld
LFLAGS	:= -m elf_i386 -r -o $(NAME).o

all:
	$(CC) $(NAME).cpp -o $(NAME)1.o $(CFLAGS)
	$(AS) $(NAME).s -o $(NAME)2.o $(AFLAGS)
	$(LD)	$(LFLAGS) $(NAME)1.o $(NAME)2.o

clean:
	rm -f *~ *.o
