NAME		:= handling
include ../configuration.mk

all:
	$(CC) GDT.c -o GDT.o $(CFLAGS)
	$(CC) IDT.c -o IDT.o $(CFLAGS)
	$(CC) keyboard.c -o keyboard.o $(CFLAGS)
	$(CXX) keyHandler.cpp -o keyHandler.o $(CFLAGS)
	$(AS) handlers.s -o handlers.o $(AFLAGS)
	$(LD)	$(LFLAGS) GDT.o IDT.o keyHandler.o keyboard.o handlers.o

clean:
	rm -f *~ *.o
