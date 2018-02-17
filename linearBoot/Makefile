NAME		:= linearBoot
include ../configuration.mk

all:
	$(CC) $(NAME).cpp -o $(NAME)1.o $(CFLAGS)
	$(AS) $(NAME).s -o $(NAME)2.o $(AFLAGS)
	$(LD)	$(LFLAGS) $(NAME)1.o $(NAME)2.o

clean:
	rm -f *~ *.o
