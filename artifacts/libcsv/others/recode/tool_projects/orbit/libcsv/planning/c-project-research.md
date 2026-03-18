# C Project Research: libcsv

## Overview

libcsv is a lightweight C library for parsing and writing CSV (Comma-Separated Values) data. Version 3.0.3 is licensed under the LGPL v2.1. The library provides:

- **CSV Parsing**: Streaming parser that processes CSV data incrementally via callbacks
- **CSV Writing**: Functions to write properly escaped and quoted CSV fields
- **Configurability**: Customizable delimiters, quote characters, space/term detection functions, and memory allocation functions
- **Strict Mode**: Optional strict parsing with error detection
- **Minimal Dependencies**: Uses only standard C library (stdlib.h, stdio.h, assert.h, stdint.h)

The library is designed to handle large CSV files efficiently with incremental parsing and dynamic buffer allocation.

## Directory Structure

```
c/
├── COPYING
├── ChangeLog
├── FAQ
├── INSTALL
├── Makefile
├── Makefile.am
├── Makefile.in
├── README
├── aclocal.m4
├── autom4te.cache
│   ├── output.0
│   ├── output.1
│   ├── output.2
│   ├── requests
│   ├── traces.0
│   ├── traces.1
│   └── traces.2
├── compile
├── compile_commands.json
├── config.guess
├── config.log
├── config.status
├── config.sub
├── configure
├── configure.ac
├── configure~
├── csv.3
├── csv.h
├── csv.pdf
├── depcomp
├── examples
│   ├── csvfix.c
│   ├── csvinfo.c
│   ├── csvtest.c
│   └── csvvalid.c
├── fix-timestamps.sh
├── install-sh
├── libcsv.c
├── libtool
├── ltmain.sh
├── m4
│   ├── libtool.m4
│   ├── ltoptions.m4
│   ├── ltsugar.m4
│   ├── ltversion.m4
│   └── lt~obsolete.m4
├── missing
├── test-driver
├── test_csv.c
└── tests
    ├── test_01.csv
    ├── test_02.csv
    ├── test_03.csv
    ├── test_04.csv
    ├── test_05.csv
    ├── test_06.csv
    ├── test_07.csv
    ├── test_08.csv
    ├── test_10.csv
    ├── test_11.csv
    ├── test_12.csv
    └── test_13.csv
```

### Core Source Files

- **csv.h**: Public API header file (108 lines)
- **libcsv.c**: Implementation file (546 lines)
- **test_csv.c**: Comprehensive test suite (483 lines)
- **examples/**: Four example programs demonstrating usage

## Structs & Interfaces

### Main Structure: `csv_parser`

Located in csv.h:60-77, this structure maintains the parser state:

```c
struct csv_parser {
  int pstate;                            // Parser state (ROW_NOT_BEGUN, FIELD_NOT_BEGUN, FIELD_BEGUN, FIELD_MIGHT_HAVE_ENDED)
  int quoted;                            // Is the current field quoted?
  size_t spaces;                         // Continuous spaces after quote or in non-quoted field
  unsigned char *entry_buf;              // Entry buffer for accumulating field data
  size_t entry_pos;                      // Current position in entry_buf (current size of entry)
  size_t entry_size;                     // Size of entry buffer
  int status;                            // Operation status (error code)
  unsigned char options;                 // Parser options (bitmask)
  unsigned char quote_char;              // Quote character (default: '"')
  unsigned char delim_char;              // Delimiter character (default: ',')
  int (*is_space)(unsigned char);        // Custom space detection function
  int (*is_term)(unsigned char);         // Custom terminator detection function
  size_t blk_size;                       // Block size for buffer growth (default: 128)
  void *(*malloc_func)(size_t);          // Not used
  void *(*realloc_func)(void *, size_t); // Custom realloc function
  void (*free_func)(void *);             // Custom free function
};
```

### Parser States

Defined in libcsv.c:32-36:

- **ROW_NOT_BEGUN** (0): No fields encountered for this row
- **FIELD_NOT_BEGUN** (1): Have seen fields but not currently in one
- **FIELD_BEGUN** (2): Currently in a field
- **FIELD_MIGHT_HAVE_ENDED** (3): Encountered double quote inside quoted field (field either ended or quote is literal)

### Callback Function Signatures

The parser uses callbacks to deliver parsed data:

```c
void (*cb1)(void *data, size_t len, void *user_data);  // Field callback
void (*cb2)(int c, void *user_data);                   // Row callback (c = terminating character)
```

## Data Models

### External Data Models

**CSV Input Format:**
- Standard CSV format with configurable delimiters and quotes
- Default delimiter: comma (`,`)
- Default quote: double quote (`"`)
- Supports:
  - Quoted fields containing delimiters, quotes, and newlines
  - Empty fields
  - Embedded newlines in quoted fields
  - Quote escaping via double-quotes (`""`)
  - Optional carriage return + line feed (`\r\n`) or just line feed (`\n`)
  - Custom delimiters and quote characters

**CSV Output Format:**
- Quoted fields with proper escaping
- Double-quotes escaped as `""`
- Configurable quote character

### Internal Data Models

**Buffer Management:**
- Dynamic buffer (`entry_buf`) grows by blocks (`blk_size`, default 128 bytes)
- Buffer growth handled by `csv_increase_buffer()`
- Size limit: SIZE_MAX
- Growth strategy: try full block size, if allocation fails, halve the size repeatedly

**Parsing State:**
- State machine with 4 states (ROW_NOT_BEGUN, FIELD_NOT_BEGUN, FIELD_BEGUN, FIELD_MIGHT_HAVE_ENDED)
- Tracks: current state, quoted flag, space count, buffer position
- Local variable optimization: frequently accessed struct fields copied to local variables during parsing

## Error Handling

### Error Codes

Defined in csv.h:33-38:

```c
#define CSV_SUCCESS 0     // Successful operation
#define CSV_EPARSE 1      // Parse error in strict mode
#define CSV_ENOMEM 2      // Out of memory while increasing buffer size
#define CSV_ETOOBIG 3     // Buffer larger than SIZE_MAX needed
#define CSV_EINVALID 4    // Invalid error code
```

### Error Reporting

- **csv_error()**: Returns current error status from parser
- **csv_strerror()**: Converts error code to human-readable string
- Errors stored in `p->status` field
- Parse errors: Return position where parsing stopped (not full length)

### Error Handling Strategy

- **Graceful degradation**: Parser returns number of bytes processed
- **Strict mode option**: When enabled, triggers CSV_EPARSE on:
  - Double quote inside non-quoted field
  - Unescaped double quote in quoted field
  - Unterminated quoted field (with CSV_STRICT_FINI)
- **Memory errors**: Return -1 with CSV_ENOMEM or CSV_ETOOBIG status

## Options

Parser options (bitmask) defined in csv.h:41-49:

```c
#define CSV_STRICT 1           // Enable strict mode
#define CSV_REPALL_NL 2        // Report all unquoted carriage returns and linefeeds
#define CSV_STRICT_FINI 4      // csv_fini returns CSV_EPARSE if last field is quoted without ending quote
#define CSV_APPEND_NULL 8      // Ensure all fields are null-terminated
#define CSV_EMPTY_IS_NULL 16   // Pass NULL pointer to cb1 for empty, unquoted fields
```

## Dependencies

### Standard Library

- **stdlib.h**: malloc/realloc/free, size_t, SIZE_MAX
- **stdio.h**: FILE, fputc, EOF
- **assert.h**: assert() for null pointer checks
- **stdint.h**: SIZE_MAX (C99+, or manually defined for C89)

### No External Dependencies

The library has zero third-party dependencies, only standard C library functions.

## Public API

### Initialization & Cleanup

- `int csv_init(struct csv_parser *p, unsigned char options)` - Initialize parser
- `void csv_free(struct csv_parser *p)` - Free parser's internal buffer
- `int csv_fini(struct csv_parser *p, void (*cb1)(...), void (*cb2)(...), void *data)` - Finalize parsing

### Parsing

- `size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(...), void (*cb2)(...), void *data)` - Parse CSV data

### Writing

- `size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size)` - Write CSV field to buffer
- `int csv_fwrite(FILE *fp, const void *src, size_t src_size)` - Write CSV field to file
- `size_t csv_write2(...)` - Write with custom quote character
- `int csv_fwrite2(...)` - Write to file with custom quote character

### Configuration

- `int csv_get_opts(const struct csv_parser *p)` - Get options
- `int csv_set_opts(struct csv_parser *p, unsigned char options)` - Set options
- `void csv_set_delim(struct csv_parser *p, unsigned char c)` - Set delimiter
- `void csv_set_quote(struct csv_parser *p, unsigned char c)` - Set quote character
- `unsigned char csv_get_delim(const struct csv_parser *p)` - Get delimiter
- `unsigned char csv_get_quote(const struct csv_parser *p)` - Get quote character
- `void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char))` - Set custom space detector
- `void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char))` - Set custom terminator detector
- `void csv_set_realloc_func(struct csv_parser *p, void *(*)(void *, size_t))` - Set custom realloc
- `void csv_set_free_func(struct csv_parser *p, void (*)(void *))` - Set custom free
- `void csv_set_blk_size(struct csv_parser *p, size_t)` - Set buffer growth block size
- `size_t csv_get_buffer_size(const struct csv_parser *p)` - Get current buffer size

### Error Handling

- `int csv_error(const struct csv_parser *p)` - Get error code
- `const char *csv_strerror(int error)` - Get error message string

## Key Implementation Details

### Streaming Parser Design

- Incremental parsing: processes input in chunks
- Callbacks invoked for each field and row
- State preserved between calls for multi-chunk processing
- No requirement to load entire file into memory

### Performance Optimizations

- Local variable caching in `csv_parse()` for frequently accessed fields
- Macros for common operations (SUBMIT_FIELD, SUBMIT_ROW, SUBMIT_CHAR)
- Efficient buffer growth strategy

### Memory Management

- Lazy buffer allocation (only allocates when first data arrives)
- Exponential growth with fallback (try full block, then halve if allocation fails)
- User-configurable memory functions (realloc, free)

### Character Constants

Defined in csv.h:52-58:

```c
#define CSV_TAB    0x09
#define CSV_SPACE  0x20
#define CSV_CR     0x0d  // Carriage return
#define CSV_LF     0x0a  // Line feed
#define CSV_COMMA  0x2c
#define CSV_QUOTE  0x22
```
