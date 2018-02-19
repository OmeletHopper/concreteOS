NAME		:= linearBoot
include ../configuration.mk

all:
	$(CXX) $(NAME).cpp -o $(NAME)1.o $(CFLAGS)
	$(CXX) io.cpp -o io.o $(CFLAGS)
	$(AS) $(NAME).s -o $(NAME)2.o $(AFLAGS)
	$(LD)	$(LFLAGS) $(NAME)1.o $(NAME)2.o io.o

clean:
	rm -f *~ *.o
