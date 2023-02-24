CFLAGS=-Wall
CPPFLAGS= 
CC= g++
SOURCES=main.cpp parser.cpp tokens.cpp
TESTDIR=./test

all: parser test

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

test: parser $(TESTDIR)/*.in

$(TESTDIR)/%.in: parser
	@echo "PROBATZEN: ./$< < $@"
	./$< < $@
	


