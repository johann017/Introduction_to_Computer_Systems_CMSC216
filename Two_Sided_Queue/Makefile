CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Werror -Wshadow -fstack-protector-all

all: public01.x public02.x public03.x public04.x public05.x public06.x \
	public07.x public08.x public09.x public10.x

public01.x: public01.o two-sided-queue.o
	$(CC) public01.o two-sided-queue.o -o public01.x

public02.x: public02.o two-sided-queue.o
	$(CC) public02.o two-sided-queue.o -o public02.x

public03.x: public03.o two-sided-queue.o
	$(CC) public03.o two-sided-queue.o -o public03.x

public04.x: public04.o two-sided-queue.o
	$(CC) public04.o two-sided-queue.o -o public04.x

public05.x: public05.o two-sided-queue.o
	$(CC) public05.o two-sided-queue.o -o public05.x

public06.x: public06.o two-sided-queue.o
	$(CC) public06.o two-sided-queue.o -o public06.x

public07.x: public07.o two-sided-queue.o
	$(CC) public07.o two-sided-queue.o -o public07.x

public08.x: public08.o two-sided-queue.o
	$(CC) public08.o two-sided-queue.o -o public08.x

public09.x: public09.o two-sided-queue.o
	$(CC) public09.o two-sided-queue.o -o public09.x

public10.x: public10.o two-sided-queue.o
	$(CC) public10.o two-sided-queue.o -o public10.x


public01.o: public01.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c two-sided-queue.h
	$(CC) $(CFLAGS) -c public10.c

two-sided-queue.o: two-sided-queue.c two-sided-queue.h
	$(CC) $(CFLAGS) -c two-sided-queue.c


clean:
	rm -f *.x *o
