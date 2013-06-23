#makefile
CC = gcc
WARNINGS = -Wall

all: Graphs.dll

Graphs.dll: quicksort.o graph.o kruskal.o
	$(CC) -shared -o Graphs.dll quicksort.o graph.o kruskal.o -Wl,--out-implib,libmessage.a
	
quicksort.o: quicksort.c quicksort.h
	$(CC) -c -DBUILD_DLL quicksort.c
	
graph.o: graph.c graph.h
	$(CC) -c -DBUILD_DLL graph.c
	
kruskal.o: kruskal.c kruskal.h
	$(CC) -c -DBUILD_DLL kruskal.c
	
clean:
	rm -rf *o Graphs.dll
