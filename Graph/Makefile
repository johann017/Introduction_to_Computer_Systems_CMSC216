CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -Wshadow -fstack-protector-all

all: public05.x 

public05.x: public05.o wstring-graph.o graph-utils.o
	$(CC) public05.o wstring-graph.o graph-utils.o -o public05.x

public05.o: public05.c wstring-graph.h
	$(CC) $(CFLAGS) -c public05.c

wstring-graph.o: wstring-graph.c wstring-graph-datastructure.h wstring-graph.h
	$(CC) $(CFLAGS) -c wstring-graph.c

#Cleans all executables and object files except for graph-utils.o
clean:
	rm -f *.x public05.o wstring-graph.o
