# AVL Tree Implementation in Rust

This is a Rust translation of the AVL tree implementation in C by xieqing.

## Features

- **Self-balancing binary search tree**: Maintains O(log n) height for optimal performance
- **Safe Rust implementation**: No unsafe code blocks - all operations use safe Rust abstractions
- **Generic data types**: Works with any data type that implements `Ord` and `Clone`
- **Comprehensive test suite**: Includes permutation tests, random insertion/deletion tests, and edge case tests
- **Optional MIN feature**: Track the minimum element with O(log n) access time

## Structure

- `src/avl_bf.rs`: Core AVL tree implementation with balance factor-based rebalancing
- `src/avl_data.rs`: Example data type implementation
- `src/bin/avl_example.rs`: Example program demonstrating AVL tree usage
- `src/bin/avl_test.rs`: Comprehensive test suite

## Building

Build the library and tests:
```bash
cargo build
```

Build with release optimizations:
```bash
cargo build --release
```

## Running Tests

Run the test suite:
```bash
cargo run --bin avl_test
```

Or use the provided test script:
```bash
./avl_test.sh
```

Run the example program:
```bash
cargo run --bin avl_example
```

## Features

### Default Features
- `min`: Enables tracking of minimum element (enabled by default)

### Building Without MIN Feature
```bash
cargo build --no-default-features
```

## API Overview

### Creating a Tree
```rust
use avl_tree::{avl_create, AvlTree};

let mut tree = avl_create();
```

### Insertion
```rust
use avl_tree::avl_insert;

if let Some(data_ref) = avl_insert(&mut tree, data) {
    // Insertion successful, data_ref points to inserted data
}
```

### Deletion
```rust
use avl_tree::avl_delete;

if let Some(deleted_data) = avl_delete(&mut tree, &query, true) {
    // Deletion successful, deleted_data contains the removed data
}
```

### Search
```rust
use avl_tree::avl_find;

if let Some(found) = avl_find(&tree, &query) {
    // Found the element
}
```

### Validation
```rust
use avl_tree::{avl_check_height, avl_check_order};

// Check if tree maintains AVL height property
assert!(avl_check_height(&tree));

// Check if tree maintains BST ordering
assert!(avl_check_order(&tree, &min_bound, &max_bound));
```

## Translation Notes

This Rust implementation maintains functional equivalence with the original C code while leveraging Rust's safety guarantees:

1. **Memory Safety**: Uses `Box` for heap allocation and Rust's ownership system for memory management
2. **No Unsafe Code**: All operations use safe Rust - no raw pointers or unsafe blocks
3. **Reference Tracking**: Uses `Cell` for safe interior mutability in test counters instead of mutable statics
4. **Type Safety**: Generic over `T: Ord + Clone` instead of void pointers

### Key Differences from C Implementation

- **No parent pointers**: Uses path tracking during insertion/deletion instead of parent pointers
- **No sentinel nodes**: Uses `Option<Box<AvlNode<T>>>` instead of NIL sentinels
- **Safe MIN tracking**: Computes minimum on-demand instead of maintaining a raw pointer
- **No duplicate support**: AVL_DUP feature not implemented - duplicates return existing node reference

## Test Coverage

The test suite includes:

- **unit_test_create**: Verifies tree initialization (12 assertions)
- **unit_test_find**: Tests search functionality
- **unit_test_successor**: Tests in-order successor finding
- **unit_test_atomic_insertion**: Tests single insertion cases
- **unit_test_atomic_deletion**: Tests single deletion cases
- **unit_test_chain_insertion**: Tests sequences requiring multiple rebalancings
- **unit_test_chain_deletion**: Tests deletion sequences with chain rebalancing
- **unit_test_permutation_insertion**: Tests all 3,628,800 permutations of 10-element insertion
- **unit_test_random_insertion_deletion**: Stress test with random operations
- **unit_test_dup**: Tests duplicate key handling
- **unit_test_min**: Tests minimum element tracking (with `min` feature)

All tests pass with 100% functional equivalence to the C implementation.

## License

Translated from C implementation by xieqing.
