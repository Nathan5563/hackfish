CC=gcc
CFLAGS=-g3 -Wall -std=c17

all: main.exe

main.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^
	
main.o: main.c

clean:
	$(RM) main.exe main.o
