SHELL := /bin/bash
CC = gcc
TERMUX_CLEANER = termux-elf-cleaner
SOURCE_CXX = lex.yy.c
override TARGET = a.out
LDFLAGS_COMMON = -lfl
all:
	flex $(SOURCE)
	$(CC) $(SOURCE_CXX) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
clean:
	rm -f $(TARGET) $(SOURCE_CXX)
