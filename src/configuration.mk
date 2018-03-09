UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)		# If host is Linux, then prefix is empty.
	PREFIX ?=
endif
ifeq ($(UNAME_S),Darwin)	# If host is macOS, then prefix is i386 elf.
	PREFIX ?= i386-elf-
endif
ifeq ($(OS),Windows_NT)		# If host is Windows, then prefix is i386 elf.
	PREFIX ?= i386-elf-
endif

BUILD_NUMBER ?= $(shell git log --pretty=format:'%h' -n 1)
VERSION	?= 0.0.3-$(BUILD_NUMBER)

CXX			:= $(PREFIX)g++ -c
CC			:= $(PREFIX)gcc -c
CFLAGS	:= -Wall -m32 -fno-stack-protector
CFLAGS	+= -I ../includes

AS			:= nasm
AFLAGS	:= -f elf32

LD			:= $(PREFIX)ld
LFLAGS	:= -m elf_i386 -r -o $(NAME).o
