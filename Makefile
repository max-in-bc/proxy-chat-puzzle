CC              =       gcc
CFLAGS          =       -Wall -g
INCLUDES        =       -Iinclude

BINDIR          =       bin
SRCDIR          =       src

SOURCE1          =       $(SRCDIR)/proxy.c
SOURCE2          =       $(SRCDIR)/proxychat.c
OBJS1            =       proxy.o
OBJS2            =       proxychat.o
PROGNAME1        =       $(BINDIR)/proxy
PROGNAME2        =       $(BINDIR)/proxychat

default: a1
	
a1: codeCompile
	$(CC) -o $(PROGNAME1) $(OBJS1)
	$(CC) -o $(PROGNAME2) $(OBJS2)
	
codeCompile: 
	$(CC) $(CFLAGS) -c $(SOURCE1) $(INCLUDES)
	$(CC) $(CFLAGS) -c $(SOURCE2) $(INCLUDES)
	
all: default

lockdown: default
		
run: default
	./proxy
	
clean:
	rm $(BINDIR)/*
	rm *.o
	rm */*~
	rm *~