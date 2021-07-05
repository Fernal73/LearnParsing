 SHELL := /usr/bin/env bash

all:
	echo "Generating : " Scanner.cpp
	flex lexer.lex
	echo "Generating: " Parser.hpp Parser.cpp
	bison grammar.ypp
	g++ -std=c++20 -o calc.out Parser.cpp Scanner.cpp
	termux-elf-cleaner ./calc.out &> /dev/null

clean:
	rm -f Scanner.cpp Parser.* calc.out
