CC = gcc
CFLAGS= -g -ansi -pedantic-errors -Wall -fstack-protector-all -Werror -Wshadow

all: public07.x 

public07.x: public07.o forkfile.o make-target.o split.o safe-fork.o
	$(CC) public07.o forkfile.o make-target.o split.o safe-fork.o \
              -o public07.x

public07.o: public07.c forkfile.h forkfile-datastructure.h make-target.h
	$(CC) $(CFLAGS) -c public07.c

forkfile.o: forkfile.c forkfile.h forkfile-datastructure.h split.h safe-fork.h
	$(CC) $(CFLAGS) -c forkfile.c

make-target.o: make-target.c make-target.h forkfile.h forkfile-datastructure.h
	$(CC) $(CFLAGS) -c make-target.c

clean:
	rm -f public*.o public*.x forkfile.o
