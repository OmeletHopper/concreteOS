NAME		:= linearBoot
include ../configuration.mk

all:
	$(CXX) $(NAME).cpp -o $(NAME)1.o $(CFLAGS)
	$(CXX) input.cpp -o input.o $(CFLAGS)
	$(AS) $(NAME).s -o $(NAME)2.o $(AFLAGS)
	$(LD)	$(LFLAGS) $(NAME)1.o $(NAME)2.o input.o

clean:
	rm -f *~ *.o
