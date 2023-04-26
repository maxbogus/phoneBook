CC=gcc
vpath src
vpath inc
CFLAGS=-I inc

main: main.o
	$(CC) -o $(CFLAGS) $<

main.o: main.c
	$(CC) -c $(CFLAGS) $< $(CFLAGS)

clean:
	rm -rf *.o