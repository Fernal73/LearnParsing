# This Makefile is designed to be simple and readable.  It does not
# aim at portability.  It requires GNU Make.

BASE = calc
BISON = bison
CXX = g++
FLEX = flex
XSLTPROC = xsltproc

all: $(BASE)

%.cpp %.hpp %.xml %.gv: %.ypp
	$(BISON) $(BISONFLAGS) --xml --graph=$*.gv -o $*.cpp $<

%.cpp: %.lex
	$(FLEX) $(FLEXFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BASE): $(BASE).o driver.o parser.o scanner.o
	$(CXX) -o $@ $^
	termux-elf-cleaner $@

$(BASE).o: parser.hpp
parser.o: parser.hpp
scanner.o: parser.hpp

run: $(BASE)
	@echo "Type arithmetic expressions.  Quit with ctrl-d."
	./$< calc.txt
	./$< literal.txt
	./$< add.txt
	./$< input.txt

html: parser.html
%.html: %.xml
	$(XSLTPROC) $(XSLTPROCFLAGS) -o $@ $$($(BISON) --print-datadir)/xslt/xml2xhtml.xsl $<

CLEANFILES =										\
  $(BASE) *.o										\
  parser.hpp parser.cpp parser.output parser.xml parser.html parser.gv location.hpp	\
  scanner.cpp
clean:
	rm -f $(CLEANFILES)
