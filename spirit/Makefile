SHELL := /bin/bash
CXX = g++
TERMUX_CLEANER = termux-elf-cleaner
BASE_CXX = $(BASE).cpp
override TARGET = a.out
LDFLAGS_COMMON = -std=c++2a
all:
	$(CXX) $(BASE_CXX) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null
	./$(TARGET)
clean:
	rm -rf $(TARGET)
