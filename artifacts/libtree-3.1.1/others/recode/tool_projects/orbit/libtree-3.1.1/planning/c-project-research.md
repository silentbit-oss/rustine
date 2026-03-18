# C Project Research: libtree

## Overview

`libtree` is a command-line utility that visualizes the dynamic dependency tree of ELF (Executable and Linkable Format) files on Linux and Unix-like systems. It serves as an enhanced replacement for the `ldd` command, providing:

1. **Tree visualization**: Displays library dependencies in a hierarchical tree structure
2. **Dependency resolution explanation**: Shows exactly how and where each shared library is located
3. **Verbosity control**: Allows filtering of common system libraries for cleaner output
4. **Path vs soname display**: Can show either file paths or sonames for libraries

The tool parses ELF binary files, extracts their dynamic section information (DT_NEEDED, DT_RPATH, DT_RUNPATH, DT_SONAME), and recursively resolves dependencies following the same search path rules as the dynamic linker (ld.so).

**Key Functionality:**
- Reads ELF headers and program headers to extract dynamic linking information
- Parses the dynamic section to find required libraries (DT_NEEDED entries)
- Resolves library locations using rpath, LD_LIBRARY_PATH, runpath, ld.so.conf, and default paths
- Recursively processes dependencies to build a complete tree
- Handles both 32-bit and 64-bit ELF files
- Supports variable interpolation in rpath/runpath ($ORIGIN, $LIB, $PLATFORM, $OSNAME, $OSREL)

## Directory Structure

```
c/
├── CHANGELOG.md
├── LICENSE
├── Makefile
├── README.md
├── compile_commands.json
├── doc
│   ├── libtree.1
│   └── screenshot.png
├── libtree.c
├── libtree.h
├── libtree.o
└── tests
    ├── 01_origin
    │   └── Makefile
    ├── 02_rpath_of_parents_parent
    │   └── Makefile
    ├── 03_direct_and_absolute_rpath
    │   └── Makefile
    ├── 04_rpath_over_env_over_runpath
    │   └── Makefile
    ├── 05_32_bits
    │   └── Makefile
    ├── 06_symbol_versions
    │   ├── Makefile
    │   ├── main.c
    │   ├── v1.c
    │   ├── v1.map
    │   ├── v2.c
    │   └── v2.map
    ├── 07_origin_is_relative_to_symlink_location_not_realpath
    │   └── Makefile
    ├── 08_nodeflib
    │   └── Makefile
    ├── 10_rpath_order
    │   └── Makefile
    └── test.c
```

## Structs & Interfaces

### ELF Data Structures

**`header_64_t` / `header_32_t`**: Represent ELF headers for 64-bit and 32-bit binaries respectively
- Contains: e_type (executable/shared library), e_machine (ISA), e_phoff (program header offset), e_phnum (number of program headers), etc.

**`prog_64_t` / `prog_32_t`**: Represent ELF program headers
- Contains: p_type (segment type: PT_LOAD, PT_DYNAMIC, etc.), p_offset (file offset), p_vaddr (virtual address), p_filesz, p_memsz, etc.

**`dyn_64_t` / `dyn_32_t`**: Represent entries in the dynamic section
- Contains: d_tag (entry type: DT_NEEDED, DT_RPATH, DT_STRTAB, etc.), d_val (value/offset)

### Core Data Structures

**`compat_t`**: Tracks architecture compatibility information
- `any`: Flag indicating whether to accept any architecture
- `class`: 32-bit (BITS32) or 64-bit (BITS64)
- `machine`: ISA/machine type (e.g., x86_64, ARM)

**`found_t`**: Records how a library was located
- `how`: Enum specifying the method (INPUT, DIRECT, RPATH, LD_LIBRARY_PATH, RUNPATH, LD_SO_CONF, DEFAULT)
- `depth`: Depth in the dependency tree (relevant for rpath resolution)

**`string_table_t`**: Dynamic string buffer
- `arr`: Character array pointer
- `n`: Current size
- `capacity`: Allocated capacity
- Purpose: Stores concatenated strings from rpath, runpath, needed libraries, sonames, etc.

**`visited_file_t` / `visited_file_array_t`**: Tracks visited files to avoid infinite recursion
- Uses device ID (st_dev) and inode (st_ino) for identification

**`libtree_state_t`**: Main state structure passed through the recursion
- Configuration: verbosity, path flag, color flag, ld_conf_file, max_depth
- String storage: string_table, visited file tracking
- rpath substitution values: PLATFORM, LIB, OSNAME, OSREL
- Search path offsets: rpath_offsets (stack), ld_library_path_offset, default_paths_offset, ld_so_conf_offset
- Tree rendering state: found_all_needed array

**`small_vec_u64_t`**: Stack-allocated vector with heap fallback
- Starts with a 16-element buffer on the stack
- Automatically moves to heap when capacity exceeded
- Used for tracking needed library offsets and PT_LOAD segments

## Data Models

### External Data Models

**ELF Binary Format** (file I/O):
- **ELF Header** (16-byte e_ident + architecture-specific header):
  - Magic bytes: 0x7f 'E' 'L' 'F'
  - Class: ELFCLASS32 (1) or ELFCLASS64 (2)
  - Data encoding: little-endian (1) or big-endian (2)
  - Type: ET_EXEC (2) or ET_DYN (3)
  - Machine: ISA identifier
  - Program header table offset and count

- **Program Headers**: Array of segments
  - Type: PT_LOAD (loadable segment), PT_DYNAMIC (dynamic linking info)
  - File offset and virtual address mappings

- **Dynamic Section**: Array of tags and values
  - DT_NEEDED: Required libraries (offsets into string table)
  - DT_STRTAB: String table virtual address
  - DT_SONAME: Shared object name (offset into string table)
  - DT_RPATH: Library search path (offset into string table)
  - DT_RUNPATH: Library search path, takes precedence over LD_LIBRARY_PATH (offset into string table)
  - DT_FLAGS_1: Flags including DT_1_NODEFLIB (ignore default search paths)

- **String Table**: Null-terminated strings referenced by dynamic section entries

**ld.so.conf Format** (file I/O):
- Text file with directory paths (one per line or colon-separated)
- Supports `include` directive for globbing additional config files
- Comments start with '#'

**Environment Variables**:
- `LD_LIBRARY_PATH`: Colon-separated library search paths
- `NO_COLOR`: Disables colored output when set

### Internal Data Models

**Search Path Hierarchy**: The tool follows the dynamic linker's search order:
1. RPATH of the executable and all parent libraries (unless RUNPATH is set)
2. LD_LIBRARY_PATH environment variable
3. RUNPATH of the current library
4. ld.so.conf paths (unless DT_1_NODEFLIB flag is set)
5. Default system paths (/lib:/usr/lib) (unless DT_1_NODEFLIB flag is set)

**Variable Interpolation**: Paths in RPATH/RUNPATH can contain:
- `$ORIGIN` or `${ORIGIN}`: Directory containing the binary
- `$LIB` or `${LIB}`: "lib" or "lib64" depending on architecture
- `$PLATFORM` or `${PLATFORM}`: Hardware platform (from uname)
- `$OSNAME` or `${OSNAME}`: Operating system name (from uname)
- `$OSREL` or `${OSREL}`: Operating system release (from uname)

**Exclude List**: Array of common system libraries hidden by default:
- Dynamic linker: ld-linux-*.so, ld64.so
- C library variants: libc.so, libc.musl-*.so
- Standard libraries: libdl.so, libgcc_s.so, libm.so, libstdc++.so

## Error Handling

Error handling in libtree uses integer error codes returned from functions. All functions in the recursion path return `int` status codes:

**Error Code Categories**:
- **11-16**: ELF validation errors (invalid magic, class, data, header, bits, endianness)
- **17**: Not an executable or dynamic library (ET_EXEC/ET_DYN)
- **18-19**: Program header errors (invalid offset, invalid program header)
- **20**: File stat failure
- **21-27**: Dynamic section errors (invalid section, array entry, missing string table, invalid soname/rpath/runpath/needed)
- **28**: Dependency not found
- **29-30**: PT_LOAD errors (none found, virtual addresses not ordered)
- **31**: Could not open file
- **32**: Incompatible ISA/architecture

**Error Handling Pattern**:
- Functions return 0 on success
- Non-zero return values indicate specific errors
- On error, functions clean up allocated resources (fclose, small_vec_u64_free, reset string_table.n)
- The main `recurse` function restores string_table.n to its original value before returning
- Visited file tracking prevents infinite loops on circular dependencies

**User-Facing Error Reporting**:
- Errors are printed to stderr with descriptive messages
- Missing dependencies trigger verbose error output showing all search paths considered
- Tree rendering uses visual indicators (red coloring) for missing dependencies

## Dependencies

### Standard C Library Dependencies

**`<stdint.h>`**: Fixed-width integer types
- `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`: ELF structure fields
- `int32_t`, `int64_t`: Dynamic section tag types

**`<stdio.h>`**: File I/O and standard output
- `FILE`, `fopen`, `fclose`, `fread`, `fseek`: Binary file reading
- `fprintf`, `fputs`, `putchar`, `puts`: Output rendering
- `getc`: Reading ld.so.conf files character-by-character

**`<stdlib.h>`**: Memory management and utilities
- `malloc`, `realloc`, `free`: Dynamic memory allocation
- `exit`: Fatal error handling
- `strtoul`: Parsing numeric command-line arguments
- `getenv`: Reading environment variables

**`<string.h>`**: String operations
- `strlen`, `strcmp`, `strncmp`: String comparison and length
- `strchr`, `strrchr`: Character searching
- `memcpy`, `memset`: Memory operations

**`<ctype.h>`**: Character classification
- `isspace`, `isalpha`: Parsing configuration files

**`<glob.h>`**: Filename pattern matching
- `glob()`, `globfree()`: Expanding wildcard patterns in ld.so.conf `include` directives
- Returns `glob_t` structure with matching paths

**`<sys/stat.h>` & `<sys/types.h>`**: File information
- `struct stat`, `stat()`: Getting device and inode for visited file tracking
- `dev_t`, `ino_t`: File identifier types

**`<sys/utsname.h>`**: System information
- `struct utsname`, `uname()`: Getting machine, sysname, release for variable interpolation

**`<unistd.h>`**: POSIX API
- `access()`: Checking file accessibility
- `isatty()`: Detecting if output is to a terminal (for color support)
- `STDOUT_FILENO`: Standard output file descriptor

### Build Dependencies

**Compiler**: C99-compliant compiler (gcc or clang)
- Flags: `-std=c99 -Wall -Wextra -Wshadow -pedantic`
- Defines: `-D_FILE_OFFSET_BITS=64` (for large file support)

**Make**: Build automation
- Targets: `all`, `check`, `install`, `clean`, `coverage`
- Test target builds and runs unit tests

### No External Libraries

The project has **zero external library dependencies** beyond the standard C library and POSIX APIs. It is designed to be a single-file, self-contained utility that can be compiled and linked statically for maximum portability.
