# Rust Library Research: Error Handling Patterns

## Overview

Rust provides sophisticated error handling through its type system, replacing C's longjmp/setjmp pattern with more composable and type-safe alternatives. This document covers idiomatic Rust error handling patterns for translating libzahl's error model.

## Core Rust Error Handling: Result<T, E>

### The Result Type

```rust
pub enum Result<T, E> {
    Ok(T),      // Contains the success value
    Err(E),     // Contains the error value
}
```

**Purpose:** Force explicit handling of both success and failure cases, preventing silent failures.

### Basic Usage

```rust
fn divide(a: i32, b: i32) -> Result<i32, String> {
    if b == 0 {
        Err("Division by zero".to_string())
    } else {
        Ok(a / b)
    }
}

match divide(10, 2) {
    Ok(result) => println!("Result: {}", result),
    Err(e) => eprintln!("Error: {}", e),
}
```

## Essential Result Methods

### 1. unwrap() and expect()

**Emergency use only** - panics on error:

```rust
let x: Result<u32, &str> = Ok(2);
assert_eq!(x.unwrap(), 2);

// expect() provides custom panic message
let x: Result<u32, &str> = Err("emergency failure");
x.expect("Testing expect"); // panics: "Testing expect: emergency failure"
```

**When to use:**
- Prototyping
- Test code
- When error is genuinely impossible
- **Not in production library code**

### 2. The ? Operator (Most Idiomatic)

**Propagates errors up the call stack:**

```rust
use std::{fs, io};

fn read_file() -> io::Result<String> {
    // If read fails, immediately return the error
    let contents = fs::read_to_string("file.txt")?;
    Ok(contents)
}

fn process() -> io::Result<()> {
    let data = read_file()?;  // Propagate error
    println!("Read: {}", data);
    Ok(())
}
```

**Behavior:**
- Returns `Err` immediately if encountered
- Otherwise unwraps the `Ok` value
- Converts error types automatically via `From` trait
- Syntactic sugar for early return

### 3. map() - Transform Success Values

```rust
let result: Result<i32, &str> = Ok(5);
let doubled = result.map(|x| x * 2);
assert_eq!(doubled, Ok(10));

let error: Result<i32, &str> = Err("failed");
let doubled = error.map(|x| x * 2);
assert_eq!(doubled, Err("failed"));  // Error unchanged
```

### 4. and_then() - Chain Fallible Operations

```rust
fn sq_then_to_string(x: u32) -> Result<String, &'static str> {
    x.checked_mul(x)
        .map(|sq| sq.to_string())
        .ok_or("overflow")
}

let result = Ok(2).and_then(sq_then_to_string);
assert_eq!(result, Ok("4".to_string()));

let error = Err("not a number").and_then(sq_then_to_string);
assert_eq!(error, Err("not a number"));
```

### 5. unwrap_or() and unwrap_or_else() - Provide Defaults

```rust
// unwrap_or() - provide static default
let good: Result<i32, &str> = Ok(42);
assert_eq!(good.unwrap_or(0), 42);

let bad: Result<i32, &str> = Err("failed");
assert_eq!(bad.unwrap_or(0), 0);

// unwrap_or_else() - compute default lazily
let result = Err("foo").unwrap_or_else(|e| e.len());
assert_eq!(result, 3);
```

### 6. inspect() and inspect_err() - Side Effects

```rust
use std::fs;

fn read() -> std::io::Result<String> {
    fs::read_to_string("file.txt")
        .inspect_err(|e| eprintln!("Failed to read file: {}", e))
}
```

## Idiomatic Error Handling Patterns

### Pattern 1: Explicit Match

**When you need different handling for each case:**

```rust
match some_operation() {
    Ok(value) => {
        println!("Success: {}", value);
        process(value);
    }
    Err(e) => {
        eprintln!("Error: {}", e);
        handle_error(e);
    }
}
```

### Pattern 2: Early Return with ?

**Most idiomatic for propagating errors:**

```rust
fn complex_operation() -> Result<i32, Error> {
    let step1 = first_operation()?;
    let step2 = second_operation(step1)?;
    let step3 = third_operation(step2)?;
    Ok(step3)
}
```

### Pattern 3: Collecting Results

**Process collection of Results:**

```rust
let v = vec![1, 2, 3];
let results: Result<Vec<u32>, &'static str> = v
    .iter()
    .map(|x| x.checked_add(1).ok_or("Overflow!"))
    .collect();

assert_eq!(results, Ok(vec![2, 3, 4]));
```

### Pattern 4: Combining Multiple Results

```rust
use std::io;

fn operation1() -> io::Result<i32> { Ok(1) }
fn operation2() -> io::Result<i32> { Ok(2) }

fn combined() -> io::Result<i32> {
    let a = operation1()?;
    let b = operation2()?;
    Ok(a + b)
}
```

### Pattern 5: Convert to Option

**When you don't care about the error:**

```rust
let result: Result<i32, &str> = Ok(42);
let option = result.ok();
assert_eq!(option, Some(42));

let result: Result<i32, &str> = Err("failed");
let option = result.ok();
assert_eq!(option, None);
```

## Custom Error Types

### Simple String Errors

```rust
type Result<T> = std::result::Result<T, String>;

fn divide(a: i32, b: i32) -> Result<i32> {
    if b == 0 {
        Err("Division by zero".to_string())
    } else {
        Ok(a / b)
    }
}
```

### Enum-Based Errors

```rust
#[derive(Debug)]
enum MathError {
    DivisionByZero,
    Overflow,
    Underflow,
}

impl std::fmt::Display for MathError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            MathError::DivisionByZero => write!(f, "Division by zero"),
            MathError::Overflow => write!(f, "Overflow"),
            MathError::Underflow => write!(f, "Underflow"),
        }
    }
}

impl std::error::Error for MathError {}

fn divide(a: i32, b: i32) -> Result<i32, MathError> {
    if b == 0 {
        Err(MathError::DivisionByZero)
    } else {
        Ok(a / b)
    }
}
```

### Using thiserror Crate

**Most ergonomic for library code:**

```rust
use thiserror::Error;

#[derive(Error, Debug)]
pub enum ZahlError {
    #[error("Division by zero")]
    DivisionByZero,

    #[error("Invalid domain: {0}")]
    InvalidDomain(String),

    #[error("Memory allocation failed")]
    AllocationFailed,

    #[error("I/O error: {0}")]
    Io(#[from] std::io::Error),

    #[error("Parse error: {0}")]
    ParseError(String),
}
```

### Using anyhow Crate

**For application code (not libraries):**

```rust
use anyhow::{Context, Result};

fn read_config() -> Result<Config> {
    let contents = fs::read_to_string("config.toml")
        .context("Failed to read config file")?;

    let config = toml::from_str(&contents)
        .context("Failed to parse config")?;

    Ok(config)
}
```

## Comparison: libzahl longjmp vs Rust Result

### libzahl C Pattern

```c
jmp_buf env;
if (setjmp(env)) {
    // Error handling
    zperror(0);
    return -1;
}
zsetup(env);

// Operations that may fail
zadd(result, a, b);  // May longjmp on error
```

**Characteristics:**
- Implicit control flow
- No type information about errors
- Manual cleanup required
- Global error state
- Not composable

### Rust Result Pattern

```rust
pub enum ZahlError {
    DivisionByZero,
    AllocationFailed,
    // ... other error variants
}

pub type Result<T> = std::result::Result<T, ZahlError>;

// Operations return Result
fn zadd(a: &BigInt, b: &BigInt) -> Result<BigInt> {
    // ... implementation
    Ok(result)
}

// Usage
fn calculation() -> Result<BigInt> {
    let result1 = zadd(&a, &b)?;  // Propagate error
    let result2 = zmul(&result1, &c)?;
    Ok(result2)
}
```

**Characteristics:**
- Explicit in function signatures
- Type-safe error information
- Automatic cleanup via RAII
- No global state
- Highly composable

## Recommended Approach for libzahl Translation

### 1. Define Custom Error Type

```rust
use thiserror::Error;

#[derive(Error, Debug)]
pub enum ZahlError {
    #[error("Division by zero")]
    DivisionByZero,

    #[error("Invalid domain: {0}")]
    InvalidDomain(String),

    #[error("Memory allocation failed")]
    AllocationFailed,

    #[error("Invalid exponent: {0}")]
    InvalidExponent(String),

    #[error("I/O error: {0}")]
    Io(#[from] std::io::Error),

    #[error("Parse error: {0}")]
    ParseError(String),
}

pub type Result<T> = std::result::Result<T, ZahlError>;
```

### 2. Use Result in All Fallible Functions

```rust
pub fn zadd(a: &BigInt, b: &BigInt) -> Result<BigInt> {
    // Implementation
    Ok(result)
}

pub fn zdiv(a: &BigInt, b: &BigInt) -> Result<BigInt> {
    if b == &BigInt::ZERO {
        return Err(ZahlError::DivisionByZero);
    }
    Ok(a / b)
}
```

### 3. No Setup/Teardown Required

Unlike libzahl's `zsetup()`/`zunsetup()`, Rust's RAII handles cleanup automatically:

```rust
// No setup needed!
let a = BigInt::from(10);
let b = BigInt::from(20);
let result = zadd(&a, &b)?;
// No teardown needed - automatic cleanup
```

### 4. Propagate Errors with ?

```rust
pub fn complex_calculation(
    a: &BigInt,
    b: &BigInt,
    c: &BigInt,
) -> Result<BigInt> {
    let temp1 = zadd(a, b)?;
    let temp2 = zmul(&temp1, c)?;
    let result = zdiv(&temp2, a)?;
    Ok(result)
}
```

## Performance Considerations

**Result<T, E> has zero-cost abstractions:**
- Same size as largest variant
- No heap allocation for Result itself
- Compiler optimizes away branches in many cases
- `?` operator compiles to simple branch

**Compared to longjmp:**
- No stack unwinding overhead
- More predictable performance
- Better compiler optimizations
- No global state access

## Testing Error Cases

```rust
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_division_by_zero() {
        let a = BigInt::from(10);
        let b = BigInt::ZERO;

        match zdiv(&a, &b) {
            Err(ZahlError::DivisionByZero) => (),
            _ => panic!("Expected DivisionByZero error"),
        }
    }

    #[test]
    fn test_successful_operation() {
        let a = BigInt::from(10);
        let b = BigInt::from(2);

        let result = zdiv(&a, &b).expect("Should succeed");
        assert_eq!(result, BigInt::from(5));
    }
}
```

## Summary: Key Recommendations

1. **Use `Result<T, E>`** for all fallible operations
2. **Define custom error type** using `thiserror` crate
3. **Use `?` operator** for error propagation
4. **Leverage RAII** - no manual setup/teardown
5. **Make errors explicit** in function signatures
6. **Document error conditions** in doc comments
7. **Test error paths** explicitly
8. **Never use `unwrap()`** in library code (only tests/examples)
