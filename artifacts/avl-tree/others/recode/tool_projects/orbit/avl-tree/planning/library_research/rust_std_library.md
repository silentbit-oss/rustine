# Rust Standard Library Research for AVL Tree Translation

## Overview

This document covers the relevant Rust standard library features for translating the C AVL tree implementation. Since Rust has a rich type system and memory safety guarantees, we'll leverage Rust's ownership model, smart pointers, and type system features.

## Core Libraries and Types

### std::boxed::Box

**Purpose**: Heap allocation with single ownership

**Documentation**: https://doc.rust-lang.org/std/boxed/struct.Box.html

**Usage for AVL Tree**:
- Box<T> provides heap allocation similar to C's malloc
- Single ownership ensures no manual free() needed
- Automatic cleanup when Box goes out of scope
- Used for allocating tree nodes on the heap

**Recommended Pattern**:
```rust
struct AvlNode<T> {
    left: Option<Box<AvlNode<T>>>,
    right: Option<Box<AvlNode<T>>>,
    // ...
}
```

**Trade-offs**:
- ✓ Memory safety guaranteed by compiler
- ✓ No memory leaks or double-free possible
- ✓ Zero-cost abstraction (no runtime overhead)
- ✗ Cannot have parent pointers with Box (would create cycles)

### std::rc::Rc and std::rc::Weak

**Purpose**: Reference counting for shared ownership

**Documentation**:
- https://doc.rust-lang.org/std/rc/struct.Rc.html
- https://doc.rust-lang.org/std/rc/struct.Weak.html

**Usage for AVL Tree**:
- NOT RECOMMENDED for this translation
- Would allow parent pointers but adds runtime overhead
- Requires RefCell for interior mutability (complex)
- Reference counting overhead contradicts AVL tree performance goals

**Why Not Using**:
- C implementation uses raw pointers for performance
- Parent pointers can be avoided by using iterative algorithms with explicit stack
- Maintaining 1:1 translation means we should match the C performance characteristics

### std::option::Option

**Purpose**: Represent nullable values type-safely

**Documentation**: https://doc.rust-lang.org/std/option/enum.Option.html

**Usage for AVL Tree**:
- Replace C's NULL pointers with Option<Box<AvlNode>>
- `None` represents nil/NULL
- `Some(node)` represents valid node pointer
- Forces explicit handling of null cases

**Recommended Pattern**:
```rust
fn avl_find<T>(&self, data: &T) -> Option<&AvlNode<T>>
```

**Trade-offs**:
- ✓ Compile-time null-safety
- ✓ Cannot dereference null by accident
- ✓ Pattern matching makes code intent clear
- ✓ Zero-cost abstraction

### std::cmp::Ordering

**Purpose**: Three-way comparison result

**Documentation**: https://doc.rust-lang.org/std/cmp/enum.Ordering.html

**Usage for AVL Tree**:
- Replace C's compare function returning int (-1, 0, +1)
- Rust's `Ordering` enum: `Less`, `Equal`, `Greater`
- More idiomatic and type-safe than integers

**Recommended Pattern**:
```rust
pub trait Compare {
    fn compare(&self, other: &Self) -> std::cmp::Ordering;
}
```

**Trade-offs**:
- ✓ Type-safe (cannot accidentally use 2 or -3)
- ✓ Self-documenting code
- ✓ Pattern matching support
- ✗ Slightly different from C API (but better)

### std::mem Functions

**Purpose**: Low-level memory operations

**Documentation**: https://doc.rust-lang.org/std/mem/

**Relevant Functions**:
- `std::mem::replace()`: Swap values
- `std::mem::take()`: Take value leaving default
- `std::mem::swap()`: Swap two mutable locations

**Usage for AVL Tree**:
- Used during node rotations
- Safe alternatives to pointer manipulation
- No undefined behavior possible

**Recommended Pattern**:
```rust
std::mem::swap(&mut node.left, &mut node.right);
```

### std::fmt Traits

**Purpose**: Formatting and printing

**Documentation**: https://doc.rust-lang.org/std/fmt/

**Usage for AVL Tree**:
- Replace C's function pointers for printing
- Implement `Display` or `Debug` traits
- More idiomatic than callback functions

**Recommended Pattern**:
```rust
impl<T: std::fmt::Display> std::fmt::Display for AvlTree<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        // ...
    }
}
```

**Trade-offs**:
- ✓ Integrates with Rust's print ecosystem
- ✓ No function pointer overhead
- ✓ More type-safe
- ✗ Less flexible than C callbacks (but adequate)

## Memory Management Strategy

### C Approach
- Manual malloc/free
- Function pointers for destroy callback
- Explicit memory management
- Risk of leaks and use-after-free

### Rust Approach
- Box for heap allocation
- Automatic Drop trait implementation
- Ownership system prevents leaks
- Compiler enforces safety

### Recommended Translation Strategy

**Node Ownership**:
```rust
struct AvlNode<T> {
    left: Option<Box<AvlNode<T>>>,
    right: Option<Box<AvlNode<T>>>,
    // No parent pointer - use stack for backtracking
    bf: i8,
    data: T,
}
```

**Tree Structure**:
```rust
pub struct AvlTree<T> {
    root: Option<Box<AvlNode<T>>>,
    // No compare callback - use trait bound
    // No destroy callback - automatic Drop
    // No print callback - use Display trait
}
```

## Type System Features

### Generic Types

**Purpose**: Replace void* with type-safe generics

**Documentation**: https://doc.rust-lang.org/book/ch10-01-syntax.html

**Recommended Pattern**:
```rust
pub struct AvlTree<T: Ord> {
    root: Option<Box<AvlNode<T>>>,
}
```

**Benefits**:
- ✓ Type safety at compile time
- ✓ No casting needed
- ✓ Monomorphization for performance (no vtable overhead)
- ✓ Can constrain T with trait bounds (e.g., `T: Ord`)

### Trait Bounds

**Purpose**: Specify required capabilities of generic types

**Documentation**: https://doc.rust-lang.org/book/ch10-02-traits.html

**Recommended Traits**:
- `Ord`: Total ordering (replacement for compare function)
- `Clone`: If nodes need to be cloned
- `Debug`: For debugging output
- `Display`: For user-facing output

**Recommended Pattern**:
```rust
impl<T: Ord> AvlTree<T> {
    pub fn insert(&mut self, data: T) -> bool {
        // Use data.cmp() instead of callback
    }
}
```

## Error Handling

### C Approach
- Return NULL on allocation failure
- Return NULL on not-found
- No way to distinguish error types

### Rust Approach Options

**Option 1: Option<T>** (Recommended for this translation)
```rust
pub fn insert(&mut self, data: T) -> Option<&T>
```
- Simple and matches C semantics
- None for failure, Some for success
- Cannot distinguish allocation failure from other errors

**Option 2: Result<T, E>**
```rust
pub fn insert(&mut self, data: T) -> Result<&T, AvlError>
```
- More detailed error reporting
- Can distinguish allocation errors
- More idiomatic Rust
- Slight departure from C API

**Recommendation**: Use Option for 1:1 translation compatibility. In Rust, allocation failures are rare (typically abort) so distinction is less important.

## Iterator Support

### C Approach
- `avl_apply()` with function pointer callback
- Manual traversal with `avl_successor()`

### Rust Approach
- Implement `Iterator` trait
- Provides integration with Rust's for loops and iterator methods

**Recommended Addition** (not 1:1 but highly idiomatic):
```rust
impl<T> AvlTree<T> {
    pub fn iter(&self) -> AvlTreeIter<T> {
        // Return iterator over tree
    }
}
```

**Benefits**:
- Integrates with Rust's for loops
- Supports map, filter, collect, etc.
- More efficient than callbacks
- Can be added alongside apply() for compatibility

## Testing Infrastructure

### C Approach
- `minunit.h`: Minimal testing macros
- Manual test execution

### Rust Approach
- Built-in test framework with `#[cfg(test)]` and `#[test]`
- Assertions with `assert!`, `assert_eq!`
- Test modules

**Recommended Pattern**:
```rust
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_insert() {
        let mut tree = AvlTree::new();
        assert!(tree.insert(5).is_some());
    }
}
```

**Benefits**:
- ✓ Integrated with cargo test
- ✓ Better output formatting
- ✓ Parallel test execution
- ✓ No external dependencies needed

## Summary of Recommendations

### Use These Rust Features:
1. **Box<T>** for heap allocation (replaces malloc/free)
2. **Option<T>** for nullable pointers (replaces NULL)
3. **Generic types** for type safety (replaces void*)
4. **Ord trait** for comparison (replaces compare callback)
5. **Drop trait** for cleanup (replaces destroy callback)
6. **Display trait** for printing (replaces print callback)
7. **Ordering enum** for comparison results (replaces int)

### Avoid These:
1. **Rc/Weak** - unnecessary overhead for this use case
2. **RefCell** - not needed if we avoid parent pointers
3. **Unsafe code** - should not be necessary for this translation

### Key Translation Principles:
- Match C's performance characteristics (no reference counting)
- Use Rust's type system for safety (no raw pointers)
- Leverage zero-cost abstractions (Box, Option, generics)
- Replace callbacks with traits (more idiomatic)
- Maintain iterative algorithms (no recursion changes)
