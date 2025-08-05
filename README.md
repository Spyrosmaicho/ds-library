# ds-library
A collection of fundamental data structures implemented in C, including stacks, queues, linked lists, trees, graphs, and more. Each structure is modular, well-documented, and accompanied by usage examples and test cases. Useful for learning, practice, or as a personal library for future projects.

## How to Run

1. Navigate to the `run` Directory
```sh
cd run
```

2. Update the Makefile (if needed)
If you want to run test cases for a specific data structure, such as `vector`, update the `OBJS` line in the `Makefile` accordingly.

For example, to test the `vector` implementation:
```makefile
OBJS = ../src/vector.o ../tests/vector_test.o
```

If you're testing `jason`, it might look like:
```makefile
OBJS = ../src/jason.o ../tests/jason_test.o
```

Make sure the corresponding .c and .h files exist and are correct.

3. Compile and Run with:
```sh
./run.sh
```

4. (Optional) Make `run.sh` Executable

If you get a "Permission denied" error, give the script executable permissions:
```sh
chmod +x run.sh
```

Then run it again:
```sh
./run.sh
```