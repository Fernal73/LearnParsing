SHELL := /bin/bash
CXX = g++
TERMUX_CLEANER = termux-elf-cleaner
BASE_CXX = $(BASE).cpp
override TARGET = a.out
LDFLAGS_COMMON = -std=c++2a
all:
	$(CXX) $(BASE_CXX) $(LDFLAGS_COMMON) -o $(TARGET)
	$(TERMUX_CLEANER) $(TARGET) &> /dev/null

run:
	./$(TARGET)

runxml:
	./$(TARGET) 1.toyxml
	./$(TARGET) 2.toyxml
	./$(TARGET) 3.toyxml
	./$(TARGET) 4.toyxml

clean:
	rm -rf $(TARGET)
