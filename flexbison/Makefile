SHELL := /usr/bin/env bash
CC = gcc
CXX = g++
TERMUX_CLEANER = termux-elf-cleaner
FLEX_SOURCE_C = lex.yy.c
FLEX_SOURCE_CXX = lex.yy.cc
BISON_SOURCE_C = $(SOURCE).tab.c
BISON_SOURCE_H = $(SOURCE).tab.h
BISON_SOURCE_CXX = $(SOURCE).tab.cc
BISON_O = bison.o
LEXER_O = lexer.o
BISON_SOURCE_HXX = $(SOURCE).tab.hh
override TARGET = a.out
LDFLAGS_COMMON = -std=c2x -lfl -lm -Wno-implicit-function-declaration 
LDFLAGS_C++_COMMON = -std=c++2a 
FLEX_SOURCE = $(SOURCE).lex
BISON_SOURCE = $(SOURCE).y
flex:
	flex -o $(FLEX_SOURCE_C) $(SOURCE).lex
	$(CC) $(FLEX_SOURCE_C) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET) < $(SOURCE).txt
flexcpp:
	flex --c++ -o $(FLEX_SOURCE_CXX) $(SOURCE).lex
	$(CXX) $(FLEX_SOURCE_CXX) $(LDFLAGS_C++_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET) < $(SOURCE).txt
bison:
	bison -d -v -Wcounterexamples $(BISON_SOURCE)
ifneq (,$(wildcard ./$(FLEX_SOURCE)))
	flex -o $(FLEX_SOURCE_C) $(FLEX_SOURCE)
	$(CC) $(FLEX_SOURCE_C) $(BISON_SOURCE_C) $(LDFLAGS_COMMON) -o $(TARGET)
else
	$(CC) $(BISON_SOURCE_C) $(LDFLAGS_COMMON) -o $(TARGET)
endif
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET) < $(SOURCE).txt
bisoncpp:
	bison -v -L c++ -d $(BISON_SOURCE)
	flex --c++ -o $(FLEX_SOURCE_CXX) $(FLEX_SOURCE)
	$(CXX) -c -o $(BISON_O) $(LDFLAGS_C++_COMMON)  $(BISON_SOURCE_CXX) 
	$(CXX) -c -o $(LEXER_O) $(LDFLAGS_C++_COMMON)  $(FLEX_SOURCE_CXX)  
	$(CXX) $(LDFLAGS_C++_COMMON) -o $(TARGET) $(BISON_O) $(LEXER_O) 
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET) < $(SOURCE).txt
clean:
	rm -f ./$(TARGET) ./$(FLEX_SOURCE_C) ./$(FLEX_SOURCE_CXX) ./$(BISON_SOURCE_CXX) \
		./$(BISON_SOURCE_HXX) ./$(BISON_SOURCE_C) ./$(BISON_SOURCE_H) \
		./$(BISON_O) ./$(LEXER_O) ./$(SOURCE).output
