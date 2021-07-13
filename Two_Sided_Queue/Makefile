CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -Wshadow -fstack-protector-all

all: public01.x public02.x

public01.x: public01.o two-sided-queue.o
	$(CC) public01.o two-sided-queue.o -o public01.x

public02.x: public02.o two-sided-queue.o
	$(CC) public02.o two-sided-queue.o -o public02.x

public01.o: public01.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public02.c

two-sided-queue.o: two-sided-queue.c two-sided-queue.h
	$(CC) $(CFLAGS) -c two-sided-queue.c


clean:
	rm -f *.x *o
