CC = gcc
CFLAGS = -Iinclude -g3 -Wall -Wextra -Werror -pedantic
PROGRAM = test

SRC_DIR = src
TEST_DIR = tests
OBJS = $(TEST_DIR)/list_test.o $(SRC_DIR)/list.o 

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROGRAM)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM) $(OBJS)