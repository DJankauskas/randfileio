ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o
	$(CC) -o randfileio.out main.o

main.o: main.c
	$(CC) -c main.c

memtest:
	valgrind --leak-check=yes ./randfileio.out

run:
	./randfileio.out