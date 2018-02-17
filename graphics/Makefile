NAME		:= graphics

CC			:= g++ -c
CFLAGS	:= -Wall -m32 -fno-stack-protector
CFLAGS	+= -I ../includes

AS			:= nasm
AFLAGS	:= -f elf32

LD			:= ld
LFLAGS	:= -m elf_i386 -r -o $(NAME).o

all:
	$(CC) $(NAME).cpp -o $(NAME).o $(CFLAGS)

clean:
	rm -f *~ *.o
