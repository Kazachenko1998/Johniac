CC=gcc
CFLAG=-pedantic -Wall -Wextra -c
CFLAGS=$(CFLAG) -o

all : run

run : main.o j_applied_functions.o j_double.o j_core.o j_message.o j_commands.o
	$(CC) $(CFLAG) run main.o j_applied_functions.o j_double.o j_core.o j_message.o j_commands.o

main.o : main.c
	$(CC) $(CFLAGS) main.o main.c

j_applied_functions.o : j_applied_functions.c
	$(CC) $(CFLAGS) j_applied_functions.o j_applied_functions.c

j_double.o : j_double.c
	$(CC) $(CFLAGS) j_double.o j_double.c

j_core.o : j_core.c
	$(CC) $(CFLAGS) j_core.o j_core.c

j_message.o : j_message.c
	$(CC) $(CFLAGS) j_message.o j_message.c

j_commands.o : j_commands.c
	$(CC) $(CFLAGS) j_commands.o j_commands.c
