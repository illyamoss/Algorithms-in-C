CC = gcc
CFLAGS = -Wall -g

program: dijkstra.o graph.o
	$(CC) $(CFLAGS) -o program dijkstra.o graph.o

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

main.o: dijkstra.c graph.h
	$(CC) $(CFLAGS) -c dijkstra.c

clean:
	rm -f program dijkstra.o graph.o
