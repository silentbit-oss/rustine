# C Project Research: libzahl-1.0

## Overview

libzahl is a C library for arbitrary-precision integer arithmetic (big integers). The library aims to be robust, fast, and usable for production programs. Key design principles include:

- **Error handling via longjmp**: Uses `setjmp`/`longjmp` for error propagation instead of return codes
- **Memory pooling**: Caches allocations for reuse instead of frequent malloc/free
- **Dedicated temporary variables**: Uses pre-allocated temporary bignum integers for internal calculations
- **Not thread-safe**: Currently single-threaded only
- **Not for cryptography**: Explicitly not designed for cryptographic applications

The library provides comprehensive bignum operations including:
- Arithmetic operations (add, subtract, multiply, divide, modulo, power)
- Bitwise operations (and, or, xor, not, shift, bit test/set)
- Comparison operations
- Number theory (GCD, primality testing)
- Random number generation
- String conversion (decimal)
- Serialization (save/load)

## Directory Structure

(Exact output of `mcp__project-analyzer__get_directory_tree`)

```
c/
├── LICENSE
├── Makefile
├── README
├── config.mk
├── man
│   ├── libzahl.7
│   ├── zabs.3
│   ├── zadd.3
│   ├── zand.3
│   ├── zbits.3
│   ├── zbset.3
│   ├── zbtest.3
│   ├── zcmp.3
│   ├── zcmpi.3
│   ├── zcmpmag.3
│   ├── zcmpu.3
│   ├── zdiv.3
│   ├── zdivmod.3
│   ├── zerror.3
│   ├── zeven.3
│   ├── zeven_nonzero.3
│   ├── zfree.3
│   ├── zgcd.3
│   ├── zinit.3
│   ├── zload.3
│   ├── zlsb.3
│   ├── zlsh.3
│   ├── zmod.3
│   ├── zmodmul.3
│   ├── zmodpow.3
│   ├── zmodpowu.3
│   ├── zmodsqr.3
│   ├── zmul.3
│   ├── zneg.3
│   ├── znot.3
│   ├── zodd.3
│   ├── zodd_nonzero.3
│   ├── zor.3
│   ├── zperror.3
│   ├── zpow.3
│   ├── zpowu.3
│   ├── zptest.3
│   ├── zrand.3
│   ├── zrsh.3
│   ├── zsave.3
│   ├── zset.3
│   ├── zseti.3
│   ├── zsets.3
│   ├── zsetu.3
│   ├── zsetup.3
│   ├── zsignum.3
│   ├── zsplit.3
│   ├── zsqr.3
│   ├── zstr.3
│   ├── zstr_length.3
│   ├── zsub.3
│   ├── zswap.3
│   ├── ztrunc.3
│   ├── zunsetup.3
│   ├── zxor.3
│   └── zzero.3
├── src
│   ├── allocator.c
│   ├── internals.h
│   ├── zabs.c
│   ├── zadd.c
│   ├── zand.c
│   ├── zbits.c
│   ├── zbset.c
│   ├── zbtest.c
│   ├── zcmp.c
│   ├── zcmpi.c
│   ├── zcmpmag.c
│   ├── zcmpu.c
│   ├── zdiv.c
│   ├── zdivmod.c
│   ├── zerror.c
│   ├── zfree.c
│   ├── zgcd.c
│   ├── zload.c
│   ├── zlsb.c
│   ├── zlsh.c
│   ├── zmod.c
│   ├── zmodmul.c
│   ├── zmodpow.c
│   ├── zmodpowu.c
│   ├── zmodsqr.c
│   ├── zmul.c
│   ├── zneg.c
│   ├── znot.c
│   ├── zor.c
│   ├── zperror.c
│   ├── zpow.c
│   ├── zpowu.c
│   ├── zptest.c
│   ├── zrand.c
│   ├── zrsh.c
│   ├── zsave.c
│   ├── zset.c
│   ├── zseti.c
│   ├── zsets.c
│   ├── zsetu.c
│   ├── zsetup.c
│   ├── zsplit.c
│   ├── zsqr.c
│   ├── zstr.c
│   ├── zstr_length.c
│   ├── zsub.c
│   ├── zswap.c
│   ├── ztrunc.c
│   ├── zunsetup.c
│   └── zxor.c
├── test-generate.py
├── test.c
└── zahl.h
```

## Structs & Interfaces

### Core Data Structure

**`z_t` (array typedef of struct):**
```c
typedef struct {
    int sign;              // Sign of the number: 0=zero, 1=positive, -1=negative
    size_t used;           // Number of chars actually used
    size_t alloced;        // Number of chars allocated
    zahl_char_t *chars;    // Array of 32-bit unsigned integers storing the magnitude
} z_t[1];
```

**`zahl_char_t`:**
```c
typedef uint32_t zahl_char_t;
```
- 32-bit unsigned integer used as the base unit for storing bignum digits
- Constants: `BITS_PER_CHAR = 32`, `ZAHL_CHAR_MAX = UINT32_MAX`

### Enumerations

**`enum zprimality`:** Primality test results
- `NONPRIME = 0`: Definitely composite
- `PROBABLY_PRIME`: Probably prime
- `PRIME`: Definitely prime (for small values)

**`enum zranddev`:** Random device selection
- `FAST_RANDOM = 0`: Use `/dev/urandom`
- `SECURE_RANDOM`: Use `/dev/random`

**`enum zranddist`:** Random distribution
- `QUASIUNIFORM = 0`: Quasi-uniform distribution
- `UNIFORM`: Uniform distribution

**`enum zerror`:** Error codes
- `ZERROR_ERRNO_SET = 0`: Error code in errno

### Global State Variables

**Setup and error handling:**
- `libzahl_jmp_buf`: Jump buffer for error longjmp
- `libzahl_set_up`: Flag indicating if library is initialized
- `libzahl_error`: Current error code

**Memory pool (for performance):**
- `libzahl_pool`: Array of memory pools indexed by allocation size
- `libzahl_pool_n`: Number of free buffers in each pool
- `libzahl_pool_alloc`: Allocated size for each pool

**Temporary variables (19 total):**
Pre-allocated bignums for internal calculations to avoid allocation overhead:
- `libzahl_tmp_cmp`, `libzahl_tmp_str_num`, `libzahl_tmp_str_mag`, etc.

**Constants (5 total):**
- `libzahl_const_1e19`: 10^19 (largest power of 10 < 2^64)
- `libzahl_const_1e9`: 10^9 (largest power of 10 < 2^32)
- `libzahl_const_1`, `libzahl_const_2`, `libzahl_const_4`

### Public API Categories

1. **Library initialization:** `zsetup()`, `zunsetup()`
2. **Memory functions:** `zfree()`, `zswap()`, `zsave()`, `zload()`
3. **Assignment:** `zset()`, `zseti()`, `zsetu()`
4. **Comparison:** `zcmp()`, `zcmpi()`, `zcmpu()`, `zcmpmag()`
5. **Arithmetic:** `zadd()`, `zsub()`, `zmul()`, `zdiv()`, `zmod()`, `zsqr()`, `zpow()`, etc.
6. **Bitwise:** `zand()`, `zor()`, `zxor()`, `znot()`, `zlsh()`, `zrsh()`, etc.
7. **Number theory:** `zgcd()`, `zptest()`
8. **Random:** `zrand()`
9. **String conversion:** `zstr()`, `zsets()`, `zstr_length()`
10. **Error handling:** `zerror()`, `zperror()`
11. **Inline helpers:** `zinit()`, `zeven()`, `zodd()`, `zzero()`, `zsignum()`

## Data Models

### External Data Models

**Serialization format (zsave/zload):**
The library provides binary serialization via `zsave()` and `zload()`:
- Serializes the bignum to raw bytes
- Returns number of bytes written/read
- Format appears to be internal representation (not portable across architectures)

**String format (zstr/zsets):**
- Decimal string representation only
- Optional leading '+' or '-' for sign
- `zstr()` converts bignum to decimal string
- `zsets()` parses decimal string to bignum
- `zstr_length()` computes required string length in given radix

**Random number generation:**
- Reads raw bytes from `/dev/urandom` (FAST_RANDOM) or `/dev/random` (SECURE_RANDOM)
- Two distribution modes: QUASIUNIFORM (faster) and UNIFORM (exact)

### Internal Data Models

**Bignum representation:**
- Sign-magnitude representation (not two's complement)
- Magnitude stored as array of 32-bit unsigned integers (little-endian digit order)
- Sign stored separately: 0 (zero), 1 (positive), -1 (negative)
- Dynamic allocation with power-of-2 sizing

**Memory management:**
- Power-of-2 allocation sizes for efficient pooling
- Memory pool indexed by log2(size)
- Reuses freed memory from pool before calling `realloc()`

**Algorithm implementations:**
- **Karatsuba multiplication** (`zmul.c`): Recursive divide-and-conquer for large multiplications
- **Binary GCD** (`zgcd.c`): Efficient GCD using bitwise operations
- **Miller-Rabin primality test** (`zptest.c`): Probabilistic primality testing
- **Division**: Uses internal `zdivmod()` for both `zdiv()` and `zmod()`

## Error Handling

**Longjmp-based error handling:**
1. User calls `zsetup(env)` with a `jmp_buf` to register error handler
2. On error, library sets `libzahl_error` to errno value
3. Library calls `longjmp(libzahl_jmp_buf, 1)` to jump back to error handler
4. User's `setjmp()` returns non-zero on error
5. User can call `zerror()` or `zperror()` to get error details

**Error conditions:**
- Memory allocation failures (`ENOMEM`)
- Division by zero (`errno` value)
- Invalid domain for operations (`EDOM`)
- File I/O errors from `/dev/random` or `/dev/urandom`

**Failure macro:**
```c
#define FAILURE(error) (libzahl_error = (error), longjmp(libzahl_jmp_buf, 1))
```

**Error reporting functions:**
- `zerror(const char **desc)`: Returns error code and optional description
- `zperror(const char *prefix)`: Like `perror()` but supports libzahl errors

## Dependencies

**Standard C library headers:**
- `<stddef.h>`: For `size_t`
- `<setjmp.h>`: For `jmp_buf`, `setjmp()`, `longjmp()`
- `<stdint.h>`: For `uint32_t` (zahl_char_t)
- `<string.h>`: For `memcpy()`, `memmove()`, `memset()`, `memcmp()`, `strerror()`
- `<stdlib.h>`: For `malloc()`, `realloc()`, `free()`, `abort()`
- `<errno.h>`: For `errno`, `ENOMEM`, `EDOM`
- `<stdio.h>`: For `sprintf()` in string conversion
- `<fcntl.h>`: For `open()` flags
- `<unistd.h>`: For `read()`, `close()`

**System dependencies:**
- `/dev/urandom`: Fast random number source
- `/dev/random`: Secure random number source (blocking)

**Build system:**
- Standard Unix Makefile
- Uses `ar`, `ranlib` for static library creation
- Generates man pages (section 3 and 7)

**No external libraries required** - only standard C library and POSIX APIs.
