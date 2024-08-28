CC = gcc
CFLAGS = -Wall -g

program: main.o graph.o
	$(CC) $(CFLAGS) -o program main.o graph.o

main.o: main.c graph.h
	$(CC) $(CFLAGS) -c main.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

clean:
	rm -f program main.o graph.o
