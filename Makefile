CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra

run : main.o help_func.o constant.o double_john.o
	$(CC) -o run main.o constant.o help_func.o double_john.o

main.o : main.c
	$(CC) $(CFLAGS) main.o main.c

constant.o : constant.c
	$(CC) $(CFLAGS) constant.o constant.c

help_func.o : help_func.c
	$(CC) $(CFLAGS) help_func.o help_func.c

double_john.o : double_john.c
	$(CC) $(CFLAGS) double_john.o double_john.c
