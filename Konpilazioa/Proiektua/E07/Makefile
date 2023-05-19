CC= g++
SOURCES=main.cpp parser.cpp tokens.cpp Kodea.cpp Lag.cpp
TESTDIR=./test/*

all: parser test

.PHONY: clean test

clean:
	rm parser.cpp parser.h parser tokens.cpp *~

parser.cpp parser.h: parser.y
	bison -Wcounterexamples --defines=$(subst cpp,h,$@) -o $@ $^

tokens.cpp: tokens.l parser.h
	flex --yylineno -o $@ $<

parser: $(SOURCES) Kodea.h Lag.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $(SOURCES) -ll

test: $(TESTDIR)/*.in
	@for f in $^ ; do \
	echo "$${f} probatzen:" ;\
        ./parser < $${f} ; \
        done

