CC = clang
CFLAGS = -Wall -g

program: main.o hashtable.o
	$(CC) $(CFLAGS) -o program main.o hashtable.o

main.o: main.c hashtable.h
	$(CC) $(CFLAGS) -c main.c

hashtable.o: hashtable.c hashtable.h
	$(CC) $(CFLAGS) -c hashtable.c

clean:
	rm -f program main.o hashtable.o
