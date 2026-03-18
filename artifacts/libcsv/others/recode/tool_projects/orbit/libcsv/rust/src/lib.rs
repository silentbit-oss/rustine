// libcsv - CSV parsing and writing library
// Safe Rust translation of libcsv 3.0.3
// Original C library by Robert Gamble
// Licensed under LGPL 2.1
// This version uses only safe Rust - no unsafe blocks or raw pointers

use std::io::Write;

// Constants (from csv.h)
pub const CSV_MAJOR: u32 = 3;
pub const CSV_MINOR: u32 = 0;
pub const CSV_RELEASE: u32 = 3;

// Error codes (from csv.h)
pub const CSV_SUCCESS: i32 = 0;
pub const CSV_EPARSE: i32 = 1;
pub const CSV_ENOMEM: i32 = 2;
pub const CSV_ETOOBIG: i32 = 3;
pub const CSV_EINVALID: i32 = 4;

// Parser options (from csv.h)
pub const CSV_STRICT: u8 = 1;
pub const CSV_REPALL_NL: u8 = 2;
pub const CSV_STRICT_FINI: u8 = 4;
pub const CSV_APPEND_NULL: u8 = 8;
pub const CSV_EMPTY_IS_NULL: u8 = 16;

// Character values (from csv.h)
pub const CSV_TAB: u8 = 0x09;
pub const CSV_SPACE: u8 = 0x20;
pub const CSV_CR: u8 = 0x0d;
pub const CSV_LF: u8 = 0x0a;
pub const CSV_COMMA: u8 = 0x2c;
pub const CSV_QUOTE: u8 = 0x22;

// Internal constants (from libcsv.c)
const MEM_BLK_SIZE: usize = 128;

// State constants (from libcsv.c)
const ROW_NOT_BEGUN: i32 = 0;
const FIELD_NOT_BEGUN: i32 = 1;
const FIELD_BEGUN: i32 = 2;
const FIELD_MIGHT_HAVE_ENDED: i32 = 3;

// Main parser struct (from csv.h)
// Note: This struct is now completely safe - no raw pointers
pub struct csv_parser {
    pub pstate: i32,
    pub quoted: i32,
    pub spaces: usize,
    pub entry_buf: Vec<u8>,
    pub entry_pos: usize,
    pub entry_size: usize,
    pub status: i32,
    pub options: u8,
    pub quote_char: u8,
    pub delim_char: u8,
    pub is_space: Option<fn(u8) -> i32>,
    pub is_term: Option<fn(u8) -> i32>,
    pub blk_size: usize,
}

// Safe callback types - no raw pointers!
// FieldCallback receives field data as an optional byte slice
// None represents NULL in the original C API
pub type FieldCallback<'a> = dyn FnMut(Option<&[u8]>) + 'a;

// RowCallback receives the character code that ended the row
pub type RowCallback<'a> = dyn FnMut(i32) + 'a;

// Error strings array (from C libcsv.c)
static CSV_ERRORS: [&str; 5] = [
    "success",
    "error parsing data while strict checking enabled",
    "memory exhausted while increasing buffer size",
    "data size too large",
    "invalid status code",
];

// Error handling functions
pub fn csv_error(p: &csv_parser) -> i32 {
    // Return the current status of the parser
    p.status
}

pub fn csv_strerror(error: i32) -> &'static str {
    // Return a textual description of status
    if error >= CSV_EINVALID || error < 0 {
        CSV_ERRORS[CSV_EINVALID as usize]
    } else {
        CSV_ERRORS[error as usize]
    }
}

// Initialization and cleanup
pub fn csv_init(p: &mut csv_parser, options: u8) -> i32 {
    // Initialize a csv_parser object returns 0 on success, -1 on error
    p.entry_buf = Vec::new();
    p.pstate = ROW_NOT_BEGUN;
    p.quoted = 0;
    p.spaces = 0;
    p.entry_pos = 0;
    p.entry_size = 0;
    p.status = 0;
    p.options = options;
    p.quote_char = CSV_QUOTE;
    p.delim_char = CSV_COMMA;
    p.is_space = None;
    p.is_term = None;
    p.blk_size = MEM_BLK_SIZE;

    0
}

pub fn csv_free(p: &mut csv_parser) {
    // Free the entry_buffer of csv_parser object
    // In Rust, Vec handles deallocation automatically
    p.entry_buf.clear();
    p.entry_buf.shrink_to_fit();
    p.entry_size = 0;
}

pub fn csv_fini(
    p: &mut csv_parser,
    cb1: &mut FieldCallback,
    cb2: &mut RowCallback,
) -> i32 {
    // Finalize parsing. Needed, for example, when file does not end in a newline
    let mut quoted = p.quoted;
    let pstate = p.pstate;
    let mut spaces = p.spaces;
    let mut entry_pos = p.entry_pos;

    if pstate == FIELD_BEGUN && p.quoted != 0 && (p.options & CSV_STRICT) != 0 && (p.options & CSV_STRICT_FINI) != 0 {
        // Current field is quoted, no end-quote was seen, and CSV_STRICT_FINI is set
        p.status = CSV_EPARSE;
        return -1;
    }

    match pstate {
        FIELD_MIGHT_HAVE_ENDED => {
            p.entry_pos = p.entry_pos.saturating_sub(p.spaces + 1); // get rid of spaces and original quote
            entry_pos = p.entry_pos;
            // Fall through to FIELD_NOT_BEGUN/FIELD_BEGUN
            // SUBMIT_FIELD
            if quoted == 0 {
                entry_pos = entry_pos.saturating_sub(spaces);
            }
            if (p.options & CSV_APPEND_NULL) != 0 {
                p.entry_buf[entry_pos] = 0;
            }
            if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                cb1(None);
            } else {
                cb1(Some(&p.entry_buf[..entry_pos]));
            }
            p.pstate = FIELD_NOT_BEGUN;
            p.entry_pos = 0;
            p.quoted = 0;
            p.spaces = 0;
            entry_pos = 0;
            quoted = 0;
            spaces = 0;

            // SUBMIT_ROW
            cb2(-1);
            p.pstate = ROW_NOT_BEGUN;
            p.entry_pos = 0;
            p.quoted = 0;
            p.spaces = 0;
        }
        FIELD_NOT_BEGUN | FIELD_BEGUN => {
            // SUBMIT_FIELD
            if quoted == 0 {
                entry_pos = entry_pos.saturating_sub(spaces);
            }
            if (p.options & CSV_APPEND_NULL) != 0 {
                p.entry_buf[entry_pos] = 0;
            }
            if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                cb1(None);
            } else {
                cb1(Some(&p.entry_buf[..entry_pos]));
            }
            p.pstate = FIELD_NOT_BEGUN;
            p.entry_pos = 0;
            p.quoted = 0;
            p.spaces = 0;

            // SUBMIT_ROW
            cb2(-1);
            p.pstate = ROW_NOT_BEGUN;
            p.entry_pos = 0;
            p.quoted = 0;
            p.spaces = 0;
        }
        ROW_NOT_BEGUN => {
            // Already ended properly
        }
        _ => {}
    }

    // Reset parser
    p.spaces = 0;
    p.quoted = 0;
    p.entry_pos = 0;
    p.status = 0;
    p.pstate = ROW_NOT_BEGUN;

    0
}

// Options getters/setters
pub fn csv_get_opts(p: &csv_parser) -> i32 {
    // Return the currently set options of parser
    p.options as i32
}

pub fn csv_set_opts(p: &mut csv_parser, options: u8) -> i32 {
    // Set the options
    p.options = options;
    0
}

// Delimiter and quote character
pub fn csv_set_delim(p: &mut csv_parser, c: u8) {
    // Set the delimiter
    p.delim_char = c;
}

pub fn csv_set_quote(p: &mut csv_parser, c: u8) {
    // Set the quote character
    p.quote_char = c;
}

pub fn csv_get_delim(p: &csv_parser) -> u8 {
    // Get the delimiter
    p.delim_char
}

pub fn csv_get_quote(p: &csv_parser) -> u8 {
    // Get the quote character
    p.quote_char
}

// Custom function setters
pub fn csv_set_space_func(p: &mut csv_parser, f: Option<fn(u8) -> i32>) {
    // Set the space function
    p.is_space = f;
}

pub fn csv_set_term_func(p: &mut csv_parser, f: Option<fn(u8) -> i32>) {
    // Set the term function
    p.is_term = f;
}

// Block size and buffer management
pub fn csv_set_blk_size(p: &mut csv_parser, size: usize) {
    // Set the block size used to increment buffer size
    p.blk_size = size;
}

pub fn csv_get_buffer_size(p: &csv_parser) -> usize {
    // Get the size of the entry buffer
    p.entry_size
}

// Internal buffer management
fn csv_increase_buffer(p: &mut csv_parser) -> i32 {
    // Increase the size of the entry buffer. Attempt to increase size by
    // p->blk_size, if this is larger than SIZE_MAX try to increase current
    // buffer size to SIZE_MAX. If allocation fails, try to allocate halve
    // the size and try again until successful or increment size is zero.

    let mut to_add = p.blk_size;

    if p.entry_size >= usize::MAX - to_add {
        to_add = usize::MAX - p.entry_size;
    }

    if to_add == 0 {
        p.status = CSV_ETOOBIG;
        return -1;
    }

    // Try to allocate, halving size on failure
    loop {
        let new_size = p.entry_size + to_add;

        // Try to reserve the capacity
        if p.entry_buf.try_reserve(to_add).is_ok() {
            // Success! Resize the buffer
            p.entry_buf.resize(new_size, 0);
            p.entry_size = new_size;
            return 0;
        }

        // Failed, try half the size
        to_add /= 2;
        if to_add == 0 {
            p.status = CSV_ENOMEM;
            return -1;
        }
    }
}

// Macro implementations (translated from C macros)
macro_rules! SUBMIT_CHAR {
    ($p:expr, $c:expr, $entry_pos:expr) => {
        $p.entry_buf[$entry_pos] = $c;
        $entry_pos += 1;
    };
}

// Core parsing function - completely safe, no raw pointers!
pub fn csv_parse(
    p: &mut csv_parser,
    s: &[u8],
    cb1: &mut FieldCallback,
    cb2: &mut RowCallback,
) -> usize {
    if s.is_empty() {
        return 0;
    }

    let len = s.len();
    let mut pos: usize = 0; // The number of characters we have processed in this call

    // Store key fields into local variables for performance
    let delim = p.delim_char;
    let quote = p.quote_char;
    let is_space = p.is_space;
    let is_term = p.is_term;
    let mut quoted = p.quoted;
    let mut pstate = p.pstate;
    let mut spaces = p.spaces;
    let mut entry_pos = p.entry_pos;

    if p.entry_buf.is_empty() && pos < len {
        // Buffer hasn't been allocated yet and len > 0
        if csv_increase_buffer(p) != 0 {
            p.quoted = quoted;
            p.pstate = pstate;
            p.spaces = spaces;
            p.entry_pos = entry_pos;
            return pos;
        }
    }

    while pos < len {
        // Check memory usage, increase buffer if necessary
        let threshold = if (p.options & CSV_APPEND_NULL) != 0 {
            p.entry_size.saturating_sub(1)
        } else {
            p.entry_size
        };

        if entry_pos == threshold {
            if csv_increase_buffer(p) != 0 {
                p.quoted = quoted;
                p.pstate = pstate;
                p.spaces = spaces;
                p.entry_pos = entry_pos;
                return pos;
            }
        }

        let c = s[pos];
        pos += 1;

        match pstate {
            ROW_NOT_BEGUN | FIELD_NOT_BEGUN => {
                let is_space_char = if let Some(f) = is_space {
                    f(c) != 0
                } else {
                    c == CSV_SPACE || c == CSV_TAB
                };

                let is_term_char = if let Some(f) = is_term {
                    f(c) != 0
                } else {
                    c == CSV_CR || c == CSV_LF
                };

                if is_space_char && c != delim {
                    // Space or Tab
                    continue;
                } else if is_term_char {
                    // Carriage Return or Line Feed
                    if pstate == FIELD_NOT_BEGUN {
                        // SUBMIT_FIELD
                        if quoted == 0 {
                            entry_pos = entry_pos.saturating_sub(spaces);
                        }
                        if (p.options & CSV_APPEND_NULL) != 0 {
                            p.entry_buf[entry_pos] = 0;
                        }
                        if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                            cb1(None);
                        } else {
                            cb1(Some(&p.entry_buf[..entry_pos]));
                        }
                        pstate = FIELD_NOT_BEGUN;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;

                        // SUBMIT_ROW
                        cb2(c as i32);
                        pstate = ROW_NOT_BEGUN;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    } else {
                        // ROW_NOT_BEGUN
                        if (p.options & CSV_REPALL_NL) != 0 {
                            cb2(c as i32);
                            pstate = ROW_NOT_BEGUN;
                            entry_pos = 0;
                            quoted = 0;
                            spaces = 0;
                        }
                    }
                    continue;
                } else if c == delim {
                    // Comma - SUBMIT_FIELD
                    if quoted == 0 {
                        entry_pos = entry_pos.saturating_sub(spaces);
                    }
                    if (p.options & CSV_APPEND_NULL) != 0 {
                        p.entry_buf[entry_pos] = 0;
                    }
                    if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                        cb1(None);
                    } else {
                        cb1(Some(&p.entry_buf[..entry_pos]));
                    }
                    pstate = FIELD_NOT_BEGUN;
                    entry_pos = 0;
                    quoted = 0;
                    spaces = 0;
                } else if c == quote {
                    // Quote
                    pstate = FIELD_BEGUN;
                    quoted = 1;
                } else {
                    // Anything else
                    pstate = FIELD_BEGUN;
                    quoted = 0;
                    SUBMIT_CHAR!(p, c, entry_pos);
                }
            }
            FIELD_BEGUN => {
                if c == quote {
                    // Quote
                    if quoted != 0 {
                        SUBMIT_CHAR!(p, c, entry_pos);
                        pstate = FIELD_MIGHT_HAVE_ENDED;
                    } else {
                        // STRICT ERROR - double quote inside non-quoted field
                        if (p.options & CSV_STRICT) != 0 {
                            p.status = CSV_EPARSE;
                            p.quoted = quoted;
                            p.pstate = pstate;
                            p.spaces = spaces;
                            p.entry_pos = entry_pos;
                            return pos - 1;
                        }
                        SUBMIT_CHAR!(p, c, entry_pos);
                        spaces = 0;
                    }
                } else if c == delim {
                    // Comma
                    if quoted != 0 {
                        SUBMIT_CHAR!(p, c, entry_pos);
                    } else {
                        // SUBMIT_FIELD
                        if quoted == 0 {
                            entry_pos = entry_pos.saturating_sub(spaces);
                        }
                        if (p.options & CSV_APPEND_NULL) != 0 {
                            p.entry_buf[entry_pos] = 0;
                        }
                        if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                            cb1(None);
                        } else {
                            cb1(Some(&p.entry_buf[..entry_pos]));
                        }
                        pstate = FIELD_NOT_BEGUN;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    }
                } else {
                    let is_term_char = if let Some(f) = is_term {
                        f(c) != 0
                    } else {
                        c == CSV_CR || c == CSV_LF
                    };

                    if is_term_char {
                        // Carriage Return or Line Feed
                        if quoted == 0 {
                            // SUBMIT_FIELD
                            entry_pos = entry_pos.saturating_sub(spaces);
                            if (p.options & CSV_APPEND_NULL) != 0 {
                                p.entry_buf[entry_pos] = 0;
                            }
                            if (p.options & CSV_EMPTY_IS_NULL) != 0 && entry_pos == 0 {
                                cb1(None);
                            } else {
                                cb1(Some(&p.entry_buf[..entry_pos]));
                            }
                            pstate = FIELD_NOT_BEGUN;
                            entry_pos = 0;
                            quoted = 0;
                            spaces = 0;

                            // SUBMIT_ROW
                            cb2(c as i32);
                            pstate = ROW_NOT_BEGUN;
                            entry_pos = 0;
                            quoted = 0;
                            spaces = 0;
                        } else {
                            SUBMIT_CHAR!(p, c, entry_pos);
                        }
                    } else {
                        let is_space_char = if let Some(f) = is_space {
                            f(c) != 0
                        } else {
                            c == CSV_SPACE || c == CSV_TAB
                        };

                        if quoted == 0 && is_space_char {
                            // Tab or space for non-quoted field
                            SUBMIT_CHAR!(p, c, entry_pos);
                            spaces += 1;
                        } else {
                            // Anything else
                            SUBMIT_CHAR!(p, c, entry_pos);
                            spaces = 0;
                        }
                    }
                }
            }
            FIELD_MIGHT_HAVE_ENDED => {
                // This only happens when a quote character is encountered in a quoted field
                if c == delim {
                    // Comma
                    entry_pos = entry_pos.saturating_sub(spaces + 1); // get rid of spaces and original quote
                    // SUBMIT_FIELD
                    if quoted == 0 {
                        entry_pos = entry_pos.saturating_sub(spaces);
                    }
                    if (p.options & CSV_APPEND_NULL) != 0 {
                        p.entry_buf[entry_pos] = 0;
                    }
                    if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                        cb1(None);
                    } else {
                        cb1(Some(&p.entry_buf[..entry_pos]));
                    }
                    pstate = FIELD_NOT_BEGUN;
                    entry_pos = 0;
                    quoted = 0;
                    spaces = 0;
                } else {
                    let is_term_char = if let Some(f) = is_term {
                        f(c) != 0
                    } else {
                        c == CSV_CR || c == CSV_LF
                    };

                    if is_term_char {
                        // Carriage Return or Line Feed
                        entry_pos = entry_pos.saturating_sub(spaces + 1); // get rid of spaces and original quote
                        // SUBMIT_FIELD
                        if quoted == 0 {
                            entry_pos = entry_pos.saturating_sub(spaces);
                        }
                        if (p.options & CSV_APPEND_NULL) != 0 {
                            p.entry_buf[entry_pos] = 0;
                        }
                        if (p.options & CSV_EMPTY_IS_NULL) != 0 && quoted == 0 && entry_pos == 0 {
                            cb1(None);
                        } else {
                            cb1(Some(&p.entry_buf[..entry_pos]));
                        }
                        pstate = FIELD_NOT_BEGUN;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;

                        // SUBMIT_ROW
                        cb2(c as i32);
                        pstate = ROW_NOT_BEGUN;
                        entry_pos = 0;
                        quoted = 0;
                        spaces = 0;
                    } else {
                        let is_space_char = if let Some(f) = is_space {
                            f(c) != 0
                        } else {
                            c == CSV_SPACE || c == CSV_TAB
                        };

                        if is_space_char {
                            // Space or Tab
                            SUBMIT_CHAR!(p, c, entry_pos);
                            spaces += 1;
                        } else if c == quote {
                            // Quote
                            if spaces != 0 {
                                // STRICT ERROR - unescaped double quote
                                if (p.options & CSV_STRICT) != 0 {
                                    p.status = CSV_EPARSE;
                                    p.quoted = quoted;
                                    p.pstate = pstate;
                                    p.spaces = spaces;
                                    p.entry_pos = entry_pos;
                                    return pos - 1;
                                }
                                spaces = 0;
                                SUBMIT_CHAR!(p, c, entry_pos);
                            } else {
                                // Two quotes in a row
                                pstate = FIELD_BEGUN;
                            }
                        } else {
                            // Anything else
                            // STRICT ERROR - unescaped double quote
                            if (p.options & CSV_STRICT) != 0 {
                                p.status = CSV_EPARSE;
                                p.quoted = quoted;
                                p.pstate = pstate;
                                p.spaces = spaces;
                                p.entry_pos = entry_pos;
                                return pos - 1;
                            }
                            pstate = FIELD_BEGUN;
                            spaces = 0;
                            SUBMIT_CHAR!(p, c, entry_pos);
                        }
                    }
                }
            }
            _ => {}
        }
    }

    p.quoted = quoted;
    p.pstate = pstate;
    p.spaces = spaces;
    p.entry_pos = entry_pos;
    pos
}

// Writing functions - completely safe!
pub fn csv_write(dest: Option<&mut [u8]>, src: &[u8]) -> usize {
    csv_write2(dest, src, CSV_QUOTE)
}

pub fn csv_fwrite<W: Write>(writer: &mut W, src: &[u8]) -> i32 {
    csv_fwrite2(writer, src, CSV_QUOTE)
}

pub fn csv_write2(
    mut dest: Option<&mut [u8]>,
    src: &[u8],
    quote: u8,
) -> usize {
    let mut chars: usize = 0;
    let dest_len = dest.as_ref().map(|d| d.len()).unwrap_or(0);

    // Write opening quote
    if let Some(ref mut d) = dest {
        if chars < dest_len {
            d[chars] = quote;
        }
    }
    chars += 1;

    // Write data, escaping quotes
    for &c in src {
        if c == quote {
            // Double the quote character
            if let Some(ref mut d) = dest {
                if chars < dest_len {
                    d[chars] = quote;
                }
            }
            if chars < usize::MAX {
                chars += 1;
            }
        }

        if let Some(ref mut d) = dest {
            if chars < dest_len {
                d[chars] = c;
            }
        }
        if chars < usize::MAX {
            chars += 1;
        }
    }

    // Write closing quote
    if let Some(ref mut d) = dest {
        if chars < dest_len {
            d[chars] = quote;
        }
    }
    if chars < usize::MAX {
        chars += 1;
    }

    chars
}

pub fn csv_fwrite2<W: Write>(
    writer: &mut W,
    src: &[u8],
    quote: u8,
) -> i32 {
    // Write opening quote
    if writer.write_all(&[quote]).is_err() {
        return -1;
    }

    // Write data, escaping quotes
    for &c in src {
        if c == quote {
            // Double the quote character
            if writer.write_all(&[quote]).is_err() {
                return -1;
            }
        }

        if writer.write_all(&[c]).is_err() {
            return -1;
        }
    }

    // Write closing quote
    if writer.write_all(&[quote]).is_err() {
        return -1;
    }

    0
}
