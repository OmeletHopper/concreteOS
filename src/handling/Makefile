NAME		:= handling
include ../configuration.mk

all:
	$(GCC) GDT.c -o GDT.o $(CFLAGS)
	$(GCC) IDT.c -o IDT.o $(CFLAGS)
	$(CC) keyHandler.cpp -o keyHandler.o $(CFLAGS)
	$(AS) handlers.s -o handlers.o $(AFLAGS)
	$(LD)	$(LFLAGS) GDT.o IDT.o keyHandler.o handlers.o

clean:
	rm -f *~ *.o
