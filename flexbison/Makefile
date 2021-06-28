SHELL := /bin/bash
CC = gcc
TERMUX_CLEANER = termux-elf-cleaner
FLEX_SOURCE_CXX = lex.yy.c
BISON_SOURCE_CXX = $(SOURCE).tab.c
BISON_SOURCE_HXX = $(SOURCE).tab.h
override TARGET = a.out
LDFLAGS_COMMON = -std=c2x -lfl -Wno-implicit-function-declaration 
FLEX_SOURCE = $(SOURCE).lex
BISON_SOURCE = $(SOURCE).y
flex:
	flex $(SOURCE)
	$(CC) $(FLEX_SOURCE_CXX) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
bison:
	bison -d $(BISON_SOURCE)
	flex $(FLEX_SOURCE)
	$(CC) $(FLEX_SOURCE_CXX) $(BISON_SOURCE_CXX) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
clean:
	rm -f $(TARGET) $(FLEX_SOURCE_CXX) $(BISON_SOURCE_CXX) $(BISON_SOURCE_HXX)
