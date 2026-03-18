# Goblin Crate Research

## Overview

**Crate Name**: `goblin`
**Purpose**: Cross-platform binary parsing and loading library for executable formats
**Primary Use Case**: Parsing ELF, Mach-O, PE, and Unix archive formats

## Key Features

1. **Zero-copy, endian-aware parsers**: Efficient parsing without allocating copies of data
2. **Raw C struct definitions**: Uses `#[repr(C)]` for accurate binary format representation
3. **Type punning support**: Write functions once that work for both 32-bit and 64-bit variants
4. **No-std compatibility**: Can work in embedded/bare-metal environments
5. **Cross-platform**: Handles multiple executable formats (ELF, Mach-O, PE32/PE32+, Unix archives)

## Modules

- **`elf`, `elf32`, `elf64`**: ELF format handling with separate modules for 32/64-bit
- **`pe`**: PE format support (Windows executables)
- **`mach`**: Mach-O parsing (macOS/iOS executables)
- **`strtab`**: String table management utilities
- **`error`**: Custom error handling

## API Design

**Primary Entry Point**: `Object` enum
- `Object::parse(bytes)` - Parses binary data and returns appropriate variant
- Variants: `Object::Elf`, `Object::PE`, `Object::Mach`, `Object::Archive`

**Pattern**: Use pattern matching after parsing to handle different formats

## Recommended Usage for ELF Parsing

```rust
use goblin::Object;

let buffer = std::fs::read("binary")?;
match Object::parse(&buffer)? {
    Object::Elf(elf) => {
        // Access ELF structures
        // elf.header - ELF header
        // elf.program_headers - Program headers (PT_LOAD, PT_DYNAMIC, etc.)
        // elf.dynamic - Dynamic section
        // elf.dynsyms - Dynamic symbol table
        // elf.dynstrtab - Dynamic string table
        // elf.libraries - DT_NEEDED entries
    }
    _ => println!("Not an ELF file"),
}
```

## Trade-offs

**Advantages**:
- Well-established and widely used in Rust ecosystem
- Zero-copy design for performance
- Handles multiple formats (future-proof if we need to support non-ELF)
- Type-safe abstractions over raw binary structures
- No unsafe code required for typical use cases

**Disadvantages**:
- Slightly heavier dependency (supports multiple formats we don't need)
- May include more features than necessary for a simple ELF-only use case
- Opinionated about data structure representation

## Suitability for libtree Translation

**Rating**: ⭐⭐⭐⭐⭐ (5/5)

Goblin is highly suitable for the libtree translation because:
1. It provides exactly the ELF parsing primitives we need (headers, program headers, dynamic section)
2. The zero-copy design matches the C version's efficient file reading approach
3. It handles both 32-bit and 64-bit ELF files transparently
4. It provides convenient access to DT_NEEDED, DT_RPATH, DT_RUNPATH, DT_SONAME, and DT_STRTAB
5. Error handling is idiomatic Rust with Result types
6. It's actively maintained and battle-tested in production tools

## Migration Strategy

1. Replace manual ELF header parsing with `goblin::elf::header::Header`
2. Replace program header iteration with `elf.program_headers`
3. Replace dynamic section parsing with `elf.dynamic` iterator
4. Use `elf.libraries` to extract DT_NEEDED entries
5. Access string table via `elf.dynstrtab` or `elf.strtab`
6. Map goblin's error types to our custom error codes
