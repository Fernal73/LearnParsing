SHELL := /bin/bash
CC = gcc
CXX = g++
TERMUX_CLEANER = termux-elf-cleaner
FLEX_SOURCE_C = lex.yy.c
FLEX_SOURCE_CXX = lex.yy.cc
BISON_SOURCE_C = $(SOURCE).tab.c
BISON_SOURCE_H = $(SOURCE).tab.h
BISON_SOURCE_CXX = $(SOURCE).tab.cc
BISON_SOURCE_HXX = $(SOURCE).tab.hh
override TARGET = a.out
LDFLAGS_COMMON = -std=c2x -lfl -lm -Wno-implicit-function-declaration 
LDFLAGS_C++_COMMON = -std=c++2a -lm 
FLEX_SOURCE = $(SOURCE).lex
BISON_SOURCE = $(SOURCE).y
flex:
	flex -o $(FLEX_SOURCE_C) $(SOURCE)
	$(CC) $(FLEX_SOURCE_C) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
flexcpp:
	flex --c++ -o $(FLEX_SOURCE_CXX) $(SOURCE)
	$(CXX) $(FLEX_SOURCE_CXX) $(LDFLAGS_C++_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
bison:
	bison -d $(BISON_SOURCE)
	flex -o $(FLEX_SOURCE_C) $(FLEX_SOURCE)
	$(CC) $(FLEX_SOURCE_C) $(BISON_SOURCE_C) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
bisoncpp:
	bison -L c++ -d $(BISON_SOURCE)
	flex --c++ -o $(FLEX_SOURCE_CXX) $(FLEX_SOURCE)
	$(CXX) $(FLEX_SOURCE_CXX) $(BISON_SOURCE_CXX) $(LDFLAGS_C++_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
clean:
	rm -f $(TARGET) $(FLEX_SOURCE_C) $(FLEX_SOURCE_CXX) $(BISON_SOURCE_CXX) $(BISON_SOURCE_HXX) $(BISON_SOURCE_C) $(BISON_SOURCE_H)
