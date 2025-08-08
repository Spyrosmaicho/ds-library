# ds-library
A collection of fundamental data structures implemented in C, including stacks, queues, linked lists, trees, graphs, and more. Each structure is modular, well-documented, and accompanied by usage examples and test cases. Useful for learning, practice, or as a personal library for future projects.


### Table of Contents
- [Avl Tree](#avl-tree)
- [Bst Tree](#bst-tree)
- [Hash Table](#hash-table)
- [Jason Parser](#jason-parser)
- [Linked List](#linked-list)
- [Queue](#queue)
- [Skip List](#skip-list)
- [Stack](#stack)
- [Vector](#vector)
- [Weighted Undirected Graph](#weighted-undirected-graph)

## How To Run
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

Make sure the corresponding .c and .h files exist and are correct. This change in the Makefile shoul only be done for the following data structures:
1) Avl Tree
2) Bst Tree
3) Hashtable
4) Linked List
5) Queue
6) Stack
7) Vector
8) Jason Parser

If you want to run the weighted graph tests you should do the following changes in the Makefile:
Change the second line of `run.sh` file with:
```sh
./test < ../tests/weightedgraph_test_cases/test1.txt
```
You can also change the number of the test or make new tests.

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


## Data Structures Explanation

### Avl Tree

`Key features`:

- Each node stores its height to efficiently calculate the balance factor.

- Supports core operations:

    Insertion: Inserts a node while maintaining balance through rotations.

    Deletion: Removes a node and rebalances the tree as needed.

    Search: Finds a node with a specific key if it exists.

    Implements left and right rotations to restore balance.

    Uses balance factor (difference between left and right subtree heights) to detect imbalance.

- Balance guarantee: Maintains tree height as O(log n), ensuring efficient search, insertion, and deletion.

- Additional utilities:

    Finds in-order successor to handle node deletion with two children.

    Frees all allocated memory upon tree destruction (destroy_avl).

### Bst Tree

- Generic data structure: Implements a BST that can store any data type via a `void*` pointer and keeps track of the element size (`element_size`).

- Key features:

1) Dynamically allocates memory for each inserted value, using memcpy to store data of any size.

2) Supports essential operations:

    Initialization: Creates a new BST node with specified element size.

    Insertion: Inserts a value using a user-provided comparison function (Compare cmp), allowing any data type.

    Search: Searches for a value, returning true if found, otherwise false.

    Deletion: Removes a node properly handling cases with zero, one, or two children.

    Free: Recursively frees all allocated memory in the tree.

    Comparison function pointer (`Compare cmp`):
    The user provides a comparison function, making the BST type-agnostic.

- Advantages:

    Flexibility to store any data type, not limited to integers.

    User-defined comparison logic for custom ordering.

- Limitations:

    This BST is not self-balancing; worst-case operations can degrade to O(n) time (like a linked list).

### Hash Table
- Key features:

1) The number of buckets is always a power of two for efficient indexing.

2) Uses the well-known djb2 hash function for good distribution.

3) Tracks load factor (ratio of entries to buckets) to decide when to resize the table.

4) Automatically doubles the table size when load factor exceeds a predefined threshold (`LOAD_FACTOR`).

5) Supports core operations:

    Create and initialize the hashtable.

    Insert key-value pairs, updating value if key already exists.

    Search for a value by key.

    Delete a key-value pair by key.

    Free all allocated memory.

    Uses linked lists in each bucket to handle collisions.

    Keys are stored by dynamically duplicating the string (strdup), ensuring safety.

- Advantages:

    Simple and efficient implementation.

    Automatic resizing for consistent performance.

    Good key distribution via djb2.

- Limitations:

    Only supports string keys.

    Values are limited to integers.

### Jason Parser
- Purpose:
A lightweight JSON validator that checks the correctness of JSON files without fully parsing them into objects. It ensures the JSON structure is valid according to the JSON syntax rules.

- Key Features:

1) Supports validation of all JSON value types:

    Objects { ... } with string keys and values.

    Arrays [ ... ] of values.

    Numbers, strings (with escape sequences), booleans (true/false), and null.

2) Handles nested objects and arrays with a helper counter to track braces.

3) Skips whitespace characters flexibly anywhere in the JSON.

4) Validates correct use of JSON syntax including:

    Proper string escaping (e.g., \", \\, unicode escapes).

    Valid number formats (rejects incomplete fractional parts).

    Correct punctuation (commas, colons, brackets).

    Processes JSON directly from a file, with size limits (up to 1 MB).

    Returns success (0) if JSON is valid, failure (1) otherwise.

    Treats empty files as valid JSON.

- Implementation details:

    Uses pointer arithmetic to scan through the JSON text without extra allocations.

    Employs recursive functions to validate objects and arrays.

    Uses `sscanf` for number validation and strncmp for keyword checks.

    No external JSON libraries used; purely manual parsing.

- Limitations:

    Only validates syntax; does not build an in-memory representation of JSON data.

    Limited file size (1 MB max) for practical memory usage.

### Linked List

- Key Features:

1) Maintains a pointer to the list head (head) and tracks the number of elements (size).

2) Supports essential operations:

    Creating a new list and nodes.

    Adding a node at the end of the list.

    Searching for a value (returns true/false).

    Deleting a node by value, freeing its memory.

    Freeing the entire list.

    Printing the list in the format val -> val -> ... -> NULL.

    Provides a helper function to get the head node.

- Advantages:

    Simple, clear, and easy-to-understand implementation.

    Keeps track of the list size for quick size queries.

    Suitable for basic use cases needing a dynamic list of integers.

- Limitations:

    Only supports integers as stored data.

    Not doubly linked — traversal only forward.

    Supports insertion only at the end (can be extended for insertion at other positions).

### Queue

- Key Features:

1) Supports generic data types by specifying the size of each element when creating the queue.

2) Initial capacity of 100 elements, automatically doubles capacity when full using realloc.

3) Implements a simple "circular buffer" logic by shifting elements toward the front when the front index moves far enough, to avoid wasting memory.

4) Provides common operations:

    Initialize queue

    Enqueue (add element)

    Dequeue (remove element)

    Check if queue is empty or full

    Get current size and capacity

    Peek at front element

    Free all allocated memory

- Advantages:

    Generic: can hold any data type, not just integers.

    Dynamically resizes to handle arbitrary numbers of elements.

    Efficient memory use by shifting elements when needed.

- Limitations:

    Initial fixed capacity of 100, which grows as needed but could be tuned.

    Only direct access to the front element; no random access to other positions.

    No advanced features like thread safety or blocking behavior.

### Skip List
- Key Features

1) Data Structure: Uses multiple layers of linked lists to “skip” over nodes, improving search speed.

2) Nodes: Each node contains an item (key-value pair), multiple forward pointers (levels), and level size information.

3) Sentinels: Includes special sentinel nodes for minimum (`INT_MIN`) and maximum (`INT_MAX`) keys to simplify boundary cases.

4) Random Level Assignment: Node heights are assigned randomly to maintain a balanced structure probabilistically.

- Operations Supported:

    Initialization with maximum level parameter

    Insert new key-value pairs

    Search for keys efficiently

    Delete keys

    Merge two skip lists into one (handling duplicates)

    Print the structure by levels for debugging/visualization

    Get count of stored elements

    Destroy/free the entire skip list properly

- Advantages

    Average-case performance similar to balanced trees but often simpler to implement.

    Efficient memory use with dynamic node heights.

    Supports dynamic sets with ordered keys and fast updates.

- Usage Notes

    The maximum level max must be specified at initialization, balancing between speed and memory.

    Random seed is initialized during list creation for level assignment.

    Provides detailed control of skip list internals, useful for educational or performance-sensitive applications.

### Stack

- Key Features

1) Generic: Can store any data type by passing element size during stack creation.

2) Dynamic Resizing: Automatically doubles capacity when full to accommodate more elements.

3) Efficient Access: Supports fast push, pop, and peek operations with O(1) average time complexity.

4) Memory Management: Provides functions to initialize, destroy, and safely manage memory.

- Supported Operations

    Initialize: Create a stack with an initial capacity of 100 elements.

    Push: Add an element to the top of the stack; resizes automatically if full.

    Pop: Remove the top element from the stack.

    Peek: Retrieve (without removing) the top element of the stack.

    Check Empty/Full: Check if the stack is empty or full.

    Get Size: Get the current number of elements.

    Get Capacity: Retrieve the current capacity of the stack.

    Destroy: Free all memory associated with the stack.

- Implementation Details

    Uses a contiguous memory block (`void *data`) to store stack elements.

    Index top tracks the position of the top element (-1 when empty).

    All memory allocations are checked for failure to prevent errors.

    Uses memcpy to handle element copying generically, based on element size.

- Usage Notes

    Element size must be provided at stack initialization to properly allocate memory.

    Push automatically reallocates memory to double capacity when needed, ensuring seamless growth.

    Caller is responsible for managing the data stored in the stack (e.g., if storing pointers, memory they point to must be managed separately).

### Vector

- Key Features

1) Generic: Can store any data type by passing the element size at initialization.

2) Dynamic Resizing: Automatically doubles capacity when full to accommodate more elements.

3) Efficient Access: Supports fast insertion and element retrieval.

4) Memory Management: Provides functions to initialize, insert, search, peek, and destroy the vector safely.

- Supported Operations

    Initialize: Create a dynamic array with a specified initial capacity and element size.

    Insert: Add an element to the end of the array; automatically resizes if full.

    Search: Find an element using a user-provided comparison function.

    Peek: Access the last element without removing it.

    Check Empty/Full: Determine if the array is empty or full.

    Get Size: Return the current number of stored elements.

    Get Capacity: Return the current allocated capacity of the array.

    Destroy: Free all allocated memory used by the vector.

- Implementation Details

    Stores data in a contiguous block of memory (`void *data`) sized according to element size and capacity.

    Tracks the current number of elements with index (starting at -1 when empty).

    Uses memcpy for generic copying of elements.

    Automatically reallocates memory to double capacity when the array is full.

    Search uses a user-provided comparison function Compare for element matching.

- Usage Notes

    The Compare function must be provided by the user and should return 0 when elements match.

    The vector grows automatically, so no manual resizing is needed.

    Caller is responsible for managing the lifecycle of complex data types if stored in the vector (e.g., pointers).

### Weighted Undirected Graph

- Data Structures

1) Graph: Represents an undirected weighted graph with a specified number of nodes. Internally uses an array of adjacency lists, where each list stores edges as linked lists.

2) Edge: Represents a weighted edge with a destination node and weight. Edges are stored as linked lists for each node’s adjacency list.

3) KruskalEdge: A struct to hold edges with endpoints (u, v) and weight w for processing in Kruskal’s MST algorithm.

- Implementation Details

    The graph is undirected: inserting an edge adds two directed edges (both directions).

    Edge sorting is done with merge sort for stable and efficient sorting.

    MST uses Union-Find to detect cycles and unify sets of connected nodes.

    Memory is carefully managed with assertions and freeing allocated structures.

- Usage Notes

    Ensure that nodes inserted with edges are within the valid range [0, num_nodes-1].

    The MST function prints an error message if the graph is disconnected.

    The implementation is suitable for sparse graphs due to adjacency lists.

    Sorting edges and MST computation run in O(E log E) time, where E is the number of edges.