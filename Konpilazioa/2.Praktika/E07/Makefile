CFLAGS=-Wall
CPPFLAGS= -std=c++11
CC= g++
SOURCES=main.cpp parser.cpp tokens.cpp
TESTDIR=./test

all: parser proba

.PHONY: clean

clean:
	rm parser.cpp parser.hpp parser tokens.cpp *~

tokens.cpp: tokens.l parser.hpp
	flex --yylineno -o $@ $<

parser.cpp: parser.y
	bison -d -o $@ $^

parser.hpp: parser.cpp


parser: $(SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^

proba: parser $(TESTDIR)/*.in

$(TESTDIR)/%.in: parser
	@echo "PROBATZEN: ./$< < $@"
	./$< < $@
	


