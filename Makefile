CC=gcc
CFLAGS=-g3 -Wall -std=c17

all: main

main: main.o
	$(CC) $(CFLAGS) -o $@ $^
	
main.o: main.c

clean:
	$(RM) main *.o
