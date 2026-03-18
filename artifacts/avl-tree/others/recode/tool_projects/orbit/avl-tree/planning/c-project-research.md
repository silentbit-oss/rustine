# C Project Research: AVL Tree Implementation

## Overview

This is a C implementation of an AVL (Adelson-Velsky and Landis) self-balancing binary search tree. The implementation stores balance factors (rather than heights) and parent references, using an iterative (non-recursive) approach for insertion and deletion operations. The tree maintains the AVL property where the heights of two child subtrees of any node differ by at most one, ensuring O(log N) time complexity for search, insertion, and deletion operations.

Key characteristics:
- **Balance factor storage**: Each node stores `bf = height(right) - height(left)`
- **Parent references**: Nodes maintain pointers to their parent for efficient backtracking
- **Iterative operations**: Insert and delete use loops rather than recursion
- **Sentinel nodes**: Uses sentinel `root` and `nil` nodes to simplify boundary conditions
- **Generic data storage**: Stores `void*` data with user-provided compare/destroy/print callbacks
- **Optional min tracking**: Compile-time flag `AVL_MIN` enables tracking of minimal node

## Directory Structure

```
c/
├── README.md
├── avl_bf.c
├── avl_bf.h
├── avl_data.c
├── avl_data.h
├── avl_example.c
├── avl_test.c
├── avl_test.sh
└── minunit.h
```

## Structs & Interfaces

### Core Data Structures

**avlnode** (avl_bf.h:30-36)
```c
typedef struct avlnode {
    struct avlnode *left;    // Left child
    struct avlnode *right;   // Right child
    struct avlnode *parent;  // Parent node
    char bf;                 // Balance factor: {-1, 0, +1}
    void *data;              // Generic data pointer
} avlnode;
```

**avltree** (avl_bf.h:38-49)
```c
typedef struct {
    int (*compare)(const void *, const void *);  // Comparison function
    void (*print)(void *);                       // Print function
    void (*destroy)(void *);                     // Destructor function

    avlnode root;   // Sentinel root node
    avlnode nil;    // Sentinel nil node

    #ifdef AVL_MIN
    avlnode *min;   // Pointer to minimal node (optional)
    #endif
} avltree;
```

### Enumerations

**avlbf** (avl_bf.h:18-22) - Balance factor values
- `LEFTHEAVY = -1`: Left subtree is taller
- `BALANCED = 0`: Subtrees have equal height
- `RIGHTHEAVY = 1`: Right subtree is taller

**avltraversal** (avl_bf.h:24-28) - Tree traversal orders
- `PREORDER`: Visit node, then left, then right
- `INORDER`: Visit left, then node, then right
- `POSTORDER`: Visit left, then right, then node

### Public API Functions

**Tree Management** (avl_bf.h)
- `avl_create()`: Create new AVL tree with callbacks
- `avl_destroy()`: Destroy tree and free all nodes

**Search Operations** (avl_bf.h)
- `avl_find()`: Find node by data
- `avl_successor()`: Find next larger node (in-order successor)

**Modification Operations** (avl_bf.h)
- `avl_insert()`: Insert or update node
- `avl_delete()`: Delete node with optional data retention

**Traversal & Debugging** (avl_bf.h)
- `avl_apply()`: Apply function to all nodes in specified order
- `avl_print()`: Print tree structure
- `avl_check_order()`: Validate binary search property
- `avl_check_height()`: Validate AVL balance property

### Internal Functions

**Rotation Operations** (avl_bf.c)
- `rotate_left()`: Perform left rotation around node
- `rotate_right()`: Perform right rotation around node

**Rebalancing Functions** (avl_bf.c)
- `fix_insert_leftimbalance()`: Fix left-heavy imbalance after insert
- `fix_insert_rightimbalance()`: Fix right-heavy imbalance after insert
- `fix_delete_leftimbalance()`: Fix left-heavy imbalance after delete
- `fix_delete_rightimbalance()`: Fix right-heavy imbalance after delete

**Utility Functions** (avl_bf.c)
- `check_order()`: Recursive order validation
- `check_height()`: Recursive height validation
- `print()`: Recursive printing helper
- `destroy()`: Recursive destruction helper

### Example Data Model

**mydata** (avl_data.h:9-11)
```c
typedef struct {
    int key;
} mydata;
```

**Example Functions** (avl_data.h)
- `makedata()`: Allocate and initialize mydata
- `compare_func()`: Compare two mydata by key
- `destroy_func()`: Free mydata
- `print_func()`: Print mydata key as integer
- `print_char_func()`: Print mydata key as character

## Data Models

### External Data Models

This implementation does not perform network I/O or file I/O directly. All data is managed in memory.

### Internal Data Models

**Node Structure**
- Each node contains left/right/parent pointers, balance factor, and void* data
- Sentinel nodes (`root` and `nil`) simplify boundary conditions
- `root.left` points to the actual tree root
- `nil` represents NULL but as an actual node object

**Balance Factor Semantics**
- Balance factor = height(right) - height(left)
- Valid values: -1 (left-heavy), 0 (balanced), +1 (right-heavy)
- Temporarily becomes ±2 during insertion/deletion, triggering rebalancing

**Tree Invariants**
1. **Binary Search Property**: For any node N, all keys in left subtree ≤ N.key ≤ all keys in right subtree
2. **AVL Balance Property**: For any node N, |height(left) - height(right)| ≤ 1
3. **Parent Consistency**: For any non-sentinel node N, N.parent.left == N or N.parent.right == N

## Error Handling

The C implementation uses a minimalist error handling approach:

**Memory Allocation Failures**
- `avl_create()` returns `NULL` if malloc fails
- `avl_insert()` returns `NULL` if malloc fails
- Caller responsible for checking return values

**Not Found Cases**
- `avl_find()` returns `NULL` if key not found
- `avl_successor()` returns `NULL` if no successor exists

**Invalid Operations**
- No explicit validation for NULL pointers passed to functions
- Undefined behavior if NULL tree or node passed
- No protection against invalid balance factors

**Callback Errors**
- `avl_apply()` returns non-zero if callback function returns error
- No exception handling (C doesn't have exceptions)

**Assertions**
- `avl_data.c` uses `assert()` to check for NULL pointers in example functions
- Assertions are debug-time checks, disabled in release builds

**Design Philosophy**
- Relies on caller correctness rather than defensive programming
- Minimal overhead, maximum performance
- Errors detected through return value checking

## Dependencies

### Standard C Library

**stdio.h**
- Used by: `avl_bf.c`, `avl_data.c`, `avl_example.c`, `avl_test.c`
- Functions: `printf()`, `fprintf()`
- Purpose: Console output for printing, debugging, and testing

**stdlib.h**
- Used by: `avl_bf.c`, `avl_data.c`, `avl_example.c`, `avl_test.c`
- Functions: `malloc()`, `free()`
- Purpose: Dynamic memory allocation for nodes and data

**assert.h**
- Used by: `avl_data.c`
- Functions: `assert()`
- Purpose: Debug-time validation of preconditions

**string.h**
- Used by: `avl_test.c`
- Functions: String manipulation (used in tests)
- Purpose: Test utilities

**time.h**
- Used by: `avl_test.c`
- Functions: `time()`
- Purpose: Random number seeding for randomized tests

**limits.h**
- Used by: `avl_test.c`
- Functions: Provides `INT_MAX`, `INT_MIN` constants
- Purpose: Boundary value testing

### Internal Dependencies

**avl_bf.h** - Core AVL tree interface
- Included by: `avl_bf.c`, `avl_example.c`, `avl_test.c`
- Defines: Tree structures, enums, and function prototypes

**avl_data.h** - Example data structure and callbacks
- Included by: `avl_data.c`, `avl_example.c`, `avl_test.c`
- Defines: `mydata` structure and callback functions

**minunit.h** - Minimal unit testing framework
- Included by: `avl_test.c`
- Provides: `mu_test()` macro for simple test assertions

### External Dependencies

None. This is a pure C implementation with no external libraries beyond the standard C library.

### Compilation

**Preprocessor Flags**
- `AVL_DUP`: Allow duplicate keys (default: update existing)
- `AVL_MIN`: Track minimal node pointer for O(1) minimum access

**Build Commands**
```bash
# Example program
gcc avl_example.c avl_bf.c avl_data.c && ./a.out

# Test program
gcc avl_test.c avl_bf.c avl_data.c && ./a.out
```

No special compiler flags or linker options required beyond standard C compilation.
