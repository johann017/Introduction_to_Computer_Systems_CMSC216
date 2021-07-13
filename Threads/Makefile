CC = gcc
CFLAGS= -g -ansi -pedantic-errors -Wall -fstack-protector-all -Werror -Wshadow

all: public2.x

public2.x: public2.c sum-files.x sum-files-threaded.x
	$(CC) public2.c -o public2.x


sum-files.x: sum-files.c
	$(CC) $(CFLAGS) -lpthread sum-files.c -o sum-files.x

sum-files-threaded.x: sum-files-threaded.c
	$(CC) $(CFLAGS) -lpthread sum-files-threaded.c -o sum-files-threaded.x


clean:
	rm -f public2.o public2.x sum-files.x sum-files-threaded.x \
              public2.inputdata
