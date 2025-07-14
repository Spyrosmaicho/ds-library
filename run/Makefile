# Μέσα στο run/Makefile
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -pedantic -I../include

PROGRAM = ./test
OBJS = ../src/bst.o ../tests/bst_test.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

../src/%.o: ../src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

../tests/%.o: ../tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)
