















use std::os::raw::c_int;

use std::convert::TryInto;

use std::ffi::CStr;

extern "C" {
    /*
 * Copyright (c) 2011, Vicent Marti
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
    
    
    
    
    
    
    
    
    
    
    /*
 * Copyright (c) 2008, Natacha Porte
 * Copyright (c) 2011, Vicent Marti
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
    /* struct buf: character array buffer */
    /* actual character data */
    /* size of the string */
    /* allocated size (0 = volatile buffer) */
    /* reallocation unit size (0 = read-only buffer) */
    /* CONST_BUF: global buffer from a string litteral */
    /* VOLATILE_BUF: macro for creating a volatile buffer on the stack */
    /* BUFPUTSL: optimized bufputs of a string litteral */
    /* bufgrow: increasing the allocated size to the given value */
    /* bufnew: allocation of a new buffer */
    /* bufnullterm: NUL-termination of the string array (making a C-string) */
    /* bufprefix: compare the beginning of a buffer with a string */
    /* bufput: appends raw data to a buffer */
    /* bufputs: appends a NUL-terminated string to a buffer */
    /* bufputc: appends a single char to a buffer */
    /* bufrelease: decrease the reference count and free the buffer if needed */
    /* bufreset: frees internal data of the buffer */
    /* bufslurp: removes a given number of bytes from the head of the array */
    /* bufprintf: formatted printing to a buffer */
    /* buftruncate: truncates the buffer at `size` */
    
    
    
    
    
    
    
    
    
    
    
    
    #[no_mangle]
    fn strtol(_: *const std::os::raw::c_char, _: *mut *mut std::os::raw::c_char,
              _: std::os::raw::c_int) -> std::os::raw::c_long;
    #[no_mangle]
    fn malloc(_: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn calloc(_: std::os::raw::c_ulong, _: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn free(__ptr: *mut std::os::raw::c_void);
    
    
    
    
    
    
    #[no_mangle]
    fn memcpy(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn memmove(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn memset(_: *mut std::os::raw::c_void, _: std::os::raw::c_int, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn memcmp(_: *const std::os::raw::c_void, _: *const std::os::raw::c_void,
              _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn strcmp(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn strncmp(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char,
               _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn strchr(_: *const std::os::raw::c_char, _: std::os::raw::c_int) -> *mut std::os::raw::c_char;
    #[no_mangle]
    fn strlen(_: *const std::os::raw::c_char) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn strncasecmp(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char,
                   _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn __ctype_b_loc() -> *mut *const std::os::raw::c_ushort;
    #[no_mangle]
    fn tolower(_: std::os::raw::c_int) -> std::os::raw::c_int;
}
pub use crate::src::autolink::sd_autolink__email;
pub use crate::src::autolink::sd_autolink__subreddit;
pub use crate::src::autolink::sd_autolink__url;
pub use crate::src::autolink::sd_autolink__username;
pub use crate::src::autolink::sd_autolink__www;
pub use crate::src::buffer::bufgrow;
pub use crate::src::buffer::bufnew;
pub use crate::src::buffer::bufput;
pub use crate::src::buffer::bufputc;
pub use crate::src::buffer::bufrelease;
pub use crate::src::buffer::buftruncate;
pub use crate::src::stack::stack_free;
pub use crate::src::stack::stack_init;
pub use crate::src::stack::stack_push;
pub type size_t = crate::src::autolink::size_t;
pub type __uint8_t = crate::src::autolink::__uint8_t;
pub type __uint32_t = std::os::raw::c_uint;
pub type uint8_t = crate::src::autolink::uint8_t;
pub type uint32_t = __uint32_t;
// #[derive(Copy, Clone)]

pub type buf = crate::src::buffer::buf;
pub type mkd_autolink = std::os::raw::c_uint;
pub const MKDA_EMAIL: mkd_autolink = 2;
pub const MKDA_NORMAL: mkd_autolink = 1;
pub const MKDA_NOT_AUTOLINK: mkd_autolink = 0;
pub type mkd_tableflags = std::os::raw::c_uint;
pub const MKD_TABLE_HEADER: mkd_tableflags = 4;
pub const MKD_TABLE_ALIGNMASK: mkd_tableflags = 3;
pub const MKD_TABLE_ALIGN_CENTER: mkd_tableflags = 3;
pub const MKD_TABLE_ALIGN_R: mkd_tableflags = 2;
pub const MKD_TABLE_ALIGN_L: mkd_tableflags = 1;
pub type mkd_extensions = std::os::raw::c_uint;
pub const MKDEXT_NO_EMAIL_AUTOLINK: mkd_extensions = 512;
pub const MKDEXT_LAX_SPACING: mkd_extensions = 256;
pub const MKDEXT_SUPERSCRIPT: mkd_extensions = 128;
pub const MKDEXT_SPACE_HEADERS: mkd_extensions = 64;
pub const MKDEXT_STRIKETHROUGH: mkd_extensions = 16;
pub const MKDEXT_AUTOLINK: mkd_extensions = 8;
pub const MKDEXT_FENCED_CODE: mkd_extensions = 4;
pub const MKDEXT_TABLES: mkd_extensions = 2;
pub const MKDEXT_NO_INTRA_EMPHASIS: mkd_extensions = 1;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sd_callbacks {
    pub blockcode: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                               _: *const buf,
                                               _: *mut std::os::raw::c_void) -> ()>,
    pub blockquote: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                _: *mut std::os::raw::c_void) -> ()>,
    pub blockspoiler: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                  _: *mut std::os::raw::c_void)
                                 -> ()>,
    pub blockhtml: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                               _: *mut std::os::raw::c_void) -> ()>,
    pub header: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                            _: std::os::raw::c_int,
                                            _: *mut std::os::raw::c_void) -> ()>,
    pub hrule: Option<unsafe extern "C" fn(_: *mut buf, _: *mut std::os::raw::c_void)
                          -> ()>,
    pub list: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                          _: std::os::raw::c_int,
                                          _: *mut std::os::raw::c_void) -> ()>,
    pub listitem: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                              _: std::os::raw::c_int,
                                              _: *mut std::os::raw::c_void) -> ()>,
    pub paragraph: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                               _: *mut std::os::raw::c_void) -> ()>,
    pub table: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                           _: *const buf,
                                           _: *mut std::os::raw::c_void) -> ()>,
    pub table_row: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                               _: *mut std::os::raw::c_void) -> ()>,
    pub table_cell: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                _: std::os::raw::c_int,
                                                _: *mut std::os::raw::c_void,
                                                _: std::os::raw::c_int) -> ()>,
    pub autolink: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                              _: mkd_autolink,
                                              _: *mut std::os::raw::c_void)
                             -> std::os::raw::c_int>,
    pub codespan: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                              _: *mut std::os::raw::c_void)
                             -> std::os::raw::c_int>,
    pub spoilerspan: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                 _: *mut std::os::raw::c_void)
                                -> std::os::raw::c_int>,
    pub double_emphasis: Option<unsafe extern "C" fn(_: *mut buf,
                                                     _: *const buf,
                                                     _: *mut std::os::raw::c_void)
                                    -> std::os::raw::c_int>,
    pub emphasis: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                              _: *mut std::os::raw::c_void)
                             -> std::os::raw::c_int>,
    pub image: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                           _: *const buf, _: *const buf,
                                           _: *mut std::os::raw::c_void)
                          -> std::os::raw::c_int>,
    pub linebreak: Option<unsafe extern "C" fn(_: *mut buf,
                                               _: *mut std::os::raw::c_void)
                              -> std::os::raw::c_int>,
    pub link: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                          _: *const buf, _: *const buf,
                                          _: *mut std::os::raw::c_void)
                         -> std::os::raw::c_int>,
    pub raw_html_tag: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                  _: *mut std::os::raw::c_void)
                                 -> std::os::raw::c_int>,
    pub triple_emphasis: Option<unsafe extern "C" fn(_: *mut buf,
                                                     _: *const buf,
                                                     _: *mut std::os::raw::c_void)
                                    -> std::os::raw::c_int>,
    pub strikethrough: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                   _: *mut std::os::raw::c_void)
                                  -> std::os::raw::c_int>,
    pub superscript: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                 _: *mut std::os::raw::c_void)
                                -> std::os::raw::c_int>,
    pub entity: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                            _: *mut std::os::raw::c_void) -> ()>,
    pub normal_text: Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                                 _: *mut std::os::raw::c_void) -> ()>,
    pub doc_header: Option<unsafe extern "C" fn(_: *mut buf,
                                                _: *mut std::os::raw::c_void) -> ()>,
    pub doc_footer: Option<unsafe extern "C" fn(_: *mut buf,
                                                _: *mut std::os::raw::c_void) -> ()>,
}
/* char_trigger: function pointer to render active chars */
/*   returns the number of chars taken care of */
/*   data is the pointer of the beginning of the span */
/*   offset is the number of valid chars before data */
/* render structure containing one particular render */
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sd_markdown {
    pub cb: sd_callbacks,
    pub opaque: *mut std::os::raw::c_void,
    pub refs: [*mut link_ref; 8],
    pub active_char: [uint8_t; 256],
    pub work_bufs: [stack; 2],
    pub ext_flags: std::os::raw::c_uint,
    pub max_nesting: size_t,
    pub max_table_cols: size_t,
    pub in_link_body: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct stack {
    pub item: *mut *mut std::os::raw::c_void,
    pub size: size_t,
    pub asize: size_t,
}
/* **************
 * LOCAL TYPES *
 ***************/
/* link_ref: reference to a link */
#[derive(Copy, Clone)]
#[repr(C)]
pub struct link_ref {
    pub id: std::os::raw::c_uint,
    pub link: *mut buf,
    pub title: *mut buf,
    pub next: *mut link_ref,
}
pub const MD_CHAR_SUPERSCRIPT: markdown_char_t = 12;
pub const MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME: markdown_char_t = 11;
pub const MD_CHAR_AUTOLINK_WWW: markdown_char_t = 10;
pub const MD_CHAR_AUTOLINK_URL: markdown_char_t = 8;
pub const MD_CHAR_AUTOLINK_EMAIL: markdown_char_t = 9;
pub const MD_CHAR_ENTITITY: markdown_char_t = 7;
pub const MD_CHAR_ESCAPE: markdown_char_t = 6;
pub const MD_CHAR_LANGLE: markdown_char_t = 5;
pub const MD_CHAR_LINK: markdown_char_t = 4;
pub const MD_CHAR_LINEBREAK: markdown_char_t = 3;
pub const MD_CHAR_CODESPAN: markdown_char_t = 2;
pub const MD_CHAR_EMPHASIS: markdown_char_t = 1;
pub type char_trigger
    =
    Option<unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                _: *mut uint8_t, _: size_t, _: size_t,
                                _: size_t) -> size_t>;
pub const MAX_HASH_VALUE: C2RustUnnamed = 770;
pub const MIN_WORD_LENGTH: C2RustUnnamed = 4;
pub const MAX_WORD_LENGTH: C2RustUnnamed = 10;
pub type C2RustUnnamed = std::os::raw::c_uint;
pub const MIN_HASH_VALUE: C2RustUnnamed = 14;
pub const TOTAL_KEYWORDS: C2RustUnnamed = 253;
pub type u_int32_t = std::os::raw::c_uint;
pub const _ISalnum: C2RustUnnamed_1 = 8;
pub const _ISdigit: C2RustUnnamed_1 = 2048;
pub const _ISxdigit: C2RustUnnamed_1 = 4096;
pub const _ISpunct: C2RustUnnamed_1 = 4;
pub const MAX_HASH_VALUE_0: C2RustUnnamed_0 = 37;
pub const MIN_WORD_LENGTH_0: C2RustUnnamed_0 = 1;
pub const MAX_WORD_LENGTH_0: C2RustUnnamed_0 = 10;
pub type C2RustUnnamed_0 = std::os::raw::c_uint;
pub const MIN_HASH_VALUE_0: C2RustUnnamed_0 = 1;
pub const TOTAL_KEYWORDS_0: C2RustUnnamed_0 = 24;
pub type C2RustUnnamed_1 = std::os::raw::c_uint;
pub const _IScntrl: C2RustUnnamed_1 = 2;
pub const _ISblank: C2RustUnnamed_1 = 1;
pub const _ISgraph: C2RustUnnamed_1 = 32768;
pub const _ISprint: C2RustUnnamed_1 = 16384;
pub const _ISspace: C2RustUnnamed_1 = 8192;
pub const _ISalpha: C2RustUnnamed_1 = 1024;
pub const _ISlower: C2RustUnnamed_1 = 512;
pub const _ISupper: C2RustUnnamed_1 = 256;
pub type markdown_char_t = std::os::raw::c_uint;
pub const MD_CHAR_NONE: markdown_char_t = 0;
/* C code produced by gperf version 3.0.3 */
/* Command-line: gperf -N find_block_tag -H hash_block_tag -C -c -E --ignore-case html_block_names.txt  */
/* Computed positions: -k'1-2' */
/* maximum key range = 37, duplicates = 0 */
#[inline]
fn hash_block_tag(str: *const std::os::raw::c_char, len: u32) -> u32 {
    unsafe {
        let str_slice = std::ffi::CStr::from_ptr(str).to_bytes();
         static mut asso_values: [std::os::raw::c_uchar; 257] =
        [38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         8 as std::os::raw::c_int as std::os::raw::c_uchar,
         30 as std::os::raw::c_int as std::os::raw::c_uchar,
         25 as std::os::raw::c_int as std::os::raw::c_uchar,
         20 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         10 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         5 as std::os::raw::c_int as std::os::raw::c_uchar, 5 as std::os::raw::c_int as std::os::raw::c_uchar,
         5 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         10 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar, 5 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         5 as std::os::raw::c_int as std::os::raw::c_uchar, 5 as std::os::raw::c_int as std::os::raw::c_uchar,
         5 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         10 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         15 as std::os::raw::c_int as std::os::raw::c_uchar,
         0 as std::os::raw::c_int as std::os::raw::c_uchar, 5 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar,
         38 as std::os::raw::c_int as std::os::raw::c_uchar];
    let mut hval: i32 = len as i32;
let str_slice = std::ffi::CStr::from_ptr(str).to_bytes();
match hval {
    1 => { }
    _ => {
        hval += asso_values[str_slice[1] as usize + 1] as i32;
    }
}
// FALLTHROUGH
hval += asso_values[str_slice[0] as usize] as i32;
return hval as u32;


    }
}

#[inline]
unsafe extern "C" fn find_block_tag(mut str: *const std::os::raw::c_char,
                                    mut len: std::os::raw::c_uint)
 -> *const std::os::raw::c_char {
    static mut wordlist: [*const std::os::raw::c_char; 39] =
        [b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"p\x00" as *const u8 as *const std::os::raw::c_char,
         b"dl\x00" as *const u8 as *const std::os::raw::c_char,
         b"div\x00" as *const u8 as *const std::os::raw::c_char,
         b"math\x00" as *const u8 as *const std::os::raw::c_char,
         b"table\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"ul\x00" as *const u8 as *const std::os::raw::c_char,
         b"del\x00" as *const u8 as *const std::os::raw::c_char,
         b"form\x00" as *const u8 as *const std::os::raw::c_char,
         b"blockquote\x00" as *const u8 as *const std::os::raw::c_char,
         b"figure\x00" as *const u8 as *const std::os::raw::c_char,
         b"ol\x00" as *const u8 as *const std::os::raw::c_char,
         b"fieldset\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"h1\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"h6\x00" as *const u8 as *const std::os::raw::c_char,
         b"pre\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"script\x00" as *const u8 as *const std::os::raw::c_char,
         b"h5\x00" as *const u8 as *const std::os::raw::c_char,
         b"noscript\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"style\x00" as *const u8 as *const std::os::raw::c_char,
         b"iframe\x00" as *const u8 as *const std::os::raw::c_char,
         b"h4\x00" as *const u8 as *const std::os::raw::c_char,
         b"ins\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"h3\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"h2\x00" as *const u8 as *const std::os::raw::c_char,
         b"span\x00" as *const u8 as *const std::os::raw::c_char];
    if len <= MAX_WORD_LENGTH_0 as std::os::raw::c_int as std::os::raw::c_uint &&
           len >= MIN_WORD_LENGTH_0 as std::os::raw::c_int as std::os::raw::c_uint {
        let mut key: std::os::raw::c_int = hash_block_tag(str, len as u32) as std::os::raw::c_int;
        if key <= MAX_HASH_VALUE_0 as std::os::raw::c_int && key >= 0 as std::os::raw::c_int {
            let mut s: *const std::os::raw::c_char = wordlist[key as usize];
            if (*str as std::os::raw::c_uchar as std::os::raw::c_int ^
                    *s as std::os::raw::c_uchar as std::os::raw::c_int) & !(32 as std::os::raw::c_int)
                   == 0 as std::os::raw::c_int &&
                   strncasecmp(str, s, len as std::os::raw::c_ulong) == 0 &&
                   *s.offset(len as isize) as std::os::raw::c_int == '\u{0}' as i32 {
                return s
            }
        }
    }
    return 0 as *const std::os::raw::c_char;
}
/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: /usr/bin/gperf --output-file=html_entities.h html_entities.gperf  */
/* Computed positions: -k'2-7' */
/* Parsers tend to choke on entities with values greater than this */
#[no_mangle]
pub static mut MAX_NUM_ENTITY_VAL: u_int32_t =
    0x10ffff as std::os::raw::c_int as u_int32_t;
/* Any numeric entity longer than this is obviously above MAX_NUM_ENTITY_VAL
 * used to avoid dealing with overflows. */
#[no_mangle]
pub static mut MAX_NUM_ENTITY_LEN: size_t = 7 as std::os::raw::c_int as size_t;
#[inline]
fn is_valid_numeric_entity(entity_val: u32) -> i32 {
    const MAX_NUM_ENTITY_VAL: u32 = 0x10FFFF;

    (entity_val > 8 &&
        entity_val != 11 &&
        entity_val != 12 &&
        (entity_val < 14 || entity_val > 31) &&
        (entity_val < 55296 || entity_val > 57343) &&
        entity_val != 65534 &&
        entity_val != 65535 &&
        entity_val <= MAX_NUM_ENTITY_VAL) as i32
}

/* maximum key range = 757, duplicates = 0 */
#[inline]
unsafe extern "C" fn hash_html_entity(mut str: *const std::os::raw::c_char,
                                      mut len: size_t) -> std::os::raw::c_uint {
    static mut asso_values: [std::os::raw::c_ushort; 257] =
        [771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         95 as std::os::raw::c_int as std::os::raw::c_ushort,
         90 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         115 as std::os::raw::c_int as std::os::raw::c_ushort,
         94 as std::os::raw::c_int as std::os::raw::c_ushort,
         55 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         150 as std::os::raw::c_int as std::os::raw::c_ushort,
         25 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         30 as std::os::raw::c_int as std::os::raw::c_ushort,
         195 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         30 as std::os::raw::c_int as std::os::raw::c_ushort,
         30 as std::os::raw::c_int as std::os::raw::c_ushort,
         5 as std::os::raw::c_int as std::os::raw::c_ushort,
         35 as std::os::raw::c_int as std::os::raw::c_ushort,
         45 as std::os::raw::c_int as std::os::raw::c_ushort,
         45 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         10 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         50 as std::os::raw::c_int as std::os::raw::c_ushort,
         125 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         5 as std::os::raw::c_int as std::os::raw::c_ushort,
         85 as std::os::raw::c_int as std::os::raw::c_ushort,
         75 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         40 as std::os::raw::c_int as std::os::raw::c_ushort,
         65 as std::os::raw::c_int as std::os::raw::c_ushort,
         20 as std::os::raw::c_int as std::os::raw::c_ushort,
         25 as std::os::raw::c_int as std::os::raw::c_ushort,
         60 as std::os::raw::c_int as std::os::raw::c_ushort,
         240 as std::os::raw::c_int as std::os::raw::c_ushort,
         240 as std::os::raw::c_int as std::os::raw::c_ushort,
         223 as std::os::raw::c_int as std::os::raw::c_ushort,
         10 as std::os::raw::c_int as std::os::raw::c_ushort,
         102 as std::os::raw::c_int as std::os::raw::c_ushort,
         20 as std::os::raw::c_int as std::os::raw::c_ushort,
         35 as std::os::raw::c_int as std::os::raw::c_ushort,
         135 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         5 as std::os::raw::c_int as std::os::raw::c_ushort,
         10 as std::os::raw::c_int as std::os::raw::c_ushort,
         183 as std::os::raw::c_int as std::os::raw::c_ushort,
         20 as std::os::raw::c_int as std::os::raw::c_ushort,
         5 as std::os::raw::c_int as std::os::raw::c_ushort,
         0 as std::os::raw::c_int as std::os::raw::c_ushort,
         50 as std::os::raw::c_int as std::os::raw::c_ushort,
         75 as std::os::raw::c_int as std::os::raw::c_ushort,
         10 as std::os::raw::c_int as std::os::raw::c_ushort,
         75 as std::os::raw::c_int as std::os::raw::c_ushort,
         175 as std::os::raw::c_int as std::os::raw::c_ushort,
         85 as std::os::raw::c_int as std::os::raw::c_ushort,
         15 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort,
         771 as std::os::raw::c_int as std::os::raw::c_ushort];
    let mut hval: u32 = len as u32;
let mut current_block_5: u64;

let str_slice = unsafe { std::slice::from_raw_parts(str, len as usize) };

match hval {
    6 => current_block_5 = 16299309038112539419,
    5 => current_block_5 = 14964981520188694172,
    4 => current_block_5 = 2667878016629255385,
    3 => current_block_5 = 17022361381020267513,
    2 => current_block_5 = 4358686903994191085,
    _ => {
        hval = hval.wrapping_add(asso_values[str_slice[6] as usize] as u32);
        current_block_5 = 16299309038112539419;
    }
}

match current_block_5 {
    16299309038112539419 => {
        hval = hval.wrapping_add(asso_values[str_slice[5] as usize] as u32);
        current_block_5 = 14964981520188694172;
    }
    _ => {}
}

match current_block_5 {
    14964981520188694172 => {
        hval = hval.wrapping_add(asso_values[str_slice[4] as usize] as u32);
        current_block_5 = 2667878016629255385;
    }
    _ => {}
}

match current_block_5 {
    2667878016629255385 => {
        hval = hval.wrapping_add(asso_values[str_slice[3] as usize] as u32);
        current_block_5 = 17022361381020267513;
    }
    _ => {}
}

match current_block_5 {
    17022361381020267513 => {
        hval = hval.wrapping_add(asso_values[str_slice[2] as usize + 1] as u32);
    }
    _ => {}
}

hval = hval.wrapping_add(asso_values[str_slice[1] as usize] as u32);
hval

}
#[no_mangle]
pub unsafe extern "C" fn is_allowed_named_entity(mut str: *const std::os::raw::c_char,
                                                 mut len: size_t)
 -> *const std::os::raw::c_char {
    static mut wordlist: [*const std::os::raw::c_char; 771] =
        [b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&or;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&not;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&int;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&psi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&isin;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&notin;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Rho;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&phi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&prop;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rho;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&nbsp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&thorn;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&thinsp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&chi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&prod;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&amp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Psi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&iota;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&omicron;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Phi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&and;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sdot;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&nu;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Chi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&emsp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Mu;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ensp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ocirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lt;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&uml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&icirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sup;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sup1;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Scaron;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&cap;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&part;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&pound;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&scaron;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ni;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lowast;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Omicron;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&cup;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Xi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&crarr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Nu;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&pi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&theta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&tau;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&nsub;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&acirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&thetasym;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ocirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rarr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ucirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&loz;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&darr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&trade;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&para;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ecirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&larr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&radic;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sub;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Pi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&kappa;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&iquest;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&eta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&supe;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rceil;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&there4;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rArr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&uarr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Kappa;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&dArr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&euro;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Theta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&circ;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Tau;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lceil;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lArr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ordm;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lrm;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&xi;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&acute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ccedil;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sup3;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ntilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&uArr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sup2;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&piv;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&otilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&shy;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Acirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&curren;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ucirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&oacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sube;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&nabla;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&iacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&mu;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&bull;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&oline;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ccedil;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sum;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&copy;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&equiv;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ntilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&prime;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&atilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&tilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ecirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Otilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&apos;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&aacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ne;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Eta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&macr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sim;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Oacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Iota;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&empty;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&uacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ouml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&exist;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&iuml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Prime;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&eacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rsquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&cent;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&zwj;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&zwnj;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&quot;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sbquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sect;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&infin;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&otimes;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&cong;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Icirc;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&brvbar;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&le;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lsquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ordf;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&clubs;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&oplus;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&perp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Yacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&micro;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ang;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&auml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&gt;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rlm;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ouml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&upsilon;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&minus;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&middot;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&uuml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&aring;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Atilde;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&divide;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rsaquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&epsilon;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&times;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ETH;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&euml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&szlig;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&frac14;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&diams;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&oslash;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Aacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lsaquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Delta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rdquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&spades;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Uacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&raquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rang;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&frasl;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&rfloor;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&harr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ndash;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Yuml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&cedil;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&eth;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ldquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&real;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&THORN;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&plusmn;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&laquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lang;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&delta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lfloor;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&beta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&omega;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Eacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Oslash;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&image;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&weierp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Zeta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&OElig;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&hArr;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Auml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&asymp;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Lambda;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&bdquo;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&zeta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Upsilon;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&lambda;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Uuml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Aring;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&yacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Beta;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Gamma;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&iexcl;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&forall;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Omega;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Epsilon;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Iacute;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Euml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&frac34;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&frac12;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&yen;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&yuml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ograve;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&AElig;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&igrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Iuml;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&alpha;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&permil;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&agrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&mdash;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ograve;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ugrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&upsih;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&ge;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&egrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&fnof;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&reg;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&deg;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Sigma;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sigma;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Alpha;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&hearts;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&oelig;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Agrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Ugrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&hellip;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&aelig;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Egrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Igrave;\x00" as *const u8 as *const std::os::raw::c_char,
         b"&gamma;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&Dagger;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&dagger;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&alefsym;\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"\x00" as *const u8 as *const std::os::raw::c_char,
         b"&sigmaf;\x00" as *const u8 as *const std::os::raw::c_char];
    if len <= MAX_WORD_LENGTH as u64 && len >= MIN_WORD_LENGTH as u64 {
    let key: u32 = hash_html_entity(str, len);
    if key <= MAX_HASH_VALUE as u32 {
        let s: *const i8 = wordlist[key as usize];
        let str_slice = unsafe { CStr::from_ptr(str).to_bytes() };
        let s_slice = unsafe { CStr::from_ptr(s).to_bytes() };

        if str_slice[0] == s_slice[0] &&
           str_slice[1..] == s_slice[1..len as usize] &&
           s_slice[len as usize] == 0 {
            return s;
        }
    }
}
return std::ptr::null();

}
static mut markdown_char_ptrs: [char_trigger; 13] =
    [None,
     Some(char_emphasis as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_codespan as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_linebreak as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_link as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_langle_tag as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_escape as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_entity as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_autolink_url as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_autolink_email as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_autolink_www as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_autolink_subreddit_or_username as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t),
     Some(char_superscript as
              unsafe extern "C" fn(_: *mut buf, _: *mut sd_markdown,
                                   _: *mut uint8_t, _: size_t, _: size_t,
                                   _: size_t) -> size_t)];
/* **************************
 * HELPER FUNCTIONS *
 ***************************/
#[inline]
unsafe extern "C" fn rndr_newbuf(mut rndr: *mut sd_markdown,
                                 mut type_0: std::os::raw::c_int) -> *mut buf {
    static mut buf_size: [size_t; 2] =
        [256 as std::os::raw::c_int as size_t, 64 as std::os::raw::c_int as size_t];
    let mut work: *mut buf = 0 as *mut buf;
    let mut pool: *mut stack =
        &mut *(*rndr).work_bufs.as_mut_ptr().offset(type_0 as isize) as
            *mut stack;
    if (*pool).size < (*pool).asize &&
           !(*(*pool).item.offset((*pool).size as isize)).is_null() {
        let fresh0 = (*pool).size;
        (*pool).size = (*pool).size.wrapping_add(1);
        work = *(*pool).item.offset(fresh0 as isize) as *mut buf;
        (*work).size = 0 as std::os::raw::c_int as size_t
    } else {
        let work_buf = bufnew(buf_size[type_0 as usize] as u64);
work = work_buf;
        stack_push(pool, work as *mut std::os::raw::c_void);
    }
    return work;
}
#[inline]
unsafe extern "C" fn rndr_popbuf(mut rndr: *mut sd_markdown,
                                 mut type_0: std::os::raw::c_int) {
    (*rndr).work_bufs[type_0 as usize].size =
        (*rndr).work_bufs[type_0 as usize].size.wrapping_sub(1);
}
unsafe extern "C" fn unscape_text(mut ob: *mut buf, mut src: *mut buf) {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut org: size_t = 0;
    while i < (*src).size {
        org = i;
        while i < (*src).size &&
                  *(*src).data.offset(i as isize) as std::os::raw::c_int !=
                      '\\' as i32 {
            i = i.wrapping_add(1)
        }
        if i > org {
            bufput(ob,
                   (*src).data.offset(org as isize) as *const std::os::raw::c_void,
                   i.wrapping_sub(org));
        }
        if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) >= (*src).size {
            break ;
        }
        bufputc(ob,
                *(*src).data.offset(i.wrapping_add(1 as std::os::raw::c_int as
                                                       std::os::raw::c_ulong) as
                                        isize) as std::os::raw::c_int);
        i =
            (i as
                 std::os::raw::c_ulong).wrapping_add(2 as std::os::raw::c_int as
                                                 std::os::raw::c_ulong) as size_t as
                size_t
    };
}
fn hash_link_ref(link_ref: &[u8]) -> std::os::raw::c_uint {
    let mut hash: std::os::raw::c_uint = 0;
    for &byte in link_ref {
        hash = (byte.to_ascii_lowercase() as std::os::raw::c_uint)
            .wrapping_add(hash << 6)
            .wrapping_add(hash << 16)
            .wrapping_sub(hash);
    }
    hash
}

unsafe extern "C" fn add_link_ref(mut references: *mut *mut link_ref,
                                  mut name: *const uint8_t,
                                  mut name_size: size_t) -> *mut link_ref {
    let mut ref_0: *mut link_ref =
        calloc(1 as std::os::raw::c_int as std::os::raw::c_ulong,
               ::std::mem::size_of::<link_ref>() as std::os::raw::c_ulong) as
            *mut link_ref;
    if ref_0.is_null() { return 0 as *mut link_ref }
    let name_slice = std::slice::from_raw_parts(name, name_size.try_into().unwrap());
(*ref_0).id = hash_link_ref(name_slice);
    (*ref_0).next =
        *references.offset((*ref_0).id.wrapping_rem(8 as std::os::raw::c_int as
                                                        std::os::raw::c_uint) as
                               isize);
    let ref mut fresh1 =
        *references.offset((*ref_0).id.wrapping_rem(8 as std::os::raw::c_int as
                                                        std::os::raw::c_uint) as
                               isize);
    *fresh1 = ref_0;
    return ref_0;
}
fn find_link_ref(references: &mut [*mut link_ref; 8], name: &[u8]) -> *mut link_ref {
    let hash: u32 = hash_link_ref(name);
    let index = (hash % 8) as usize;

    let mut ref_0 = unsafe { *references.get(index).unwrap() };
    while !ref_0.is_null() {
        if unsafe { (*ref_0).id } == hash {
            return ref_0;
        }
        ref_0 = unsafe { (*ref_0).next };
    }
    std::ptr::null_mut()
}

fn free_link_refs(references: &mut [*mut link_ref; 8]) {
    for i in 0..8 {
        let mut r = references[i];
        while !r.is_null() {
            let next = unsafe { (*r).next }; // Get the next link_ref
            unsafe {
                bufrelease((*r).link);
                bufrelease((*r).title);
                free(r as *mut std::os::raw::c_void); // Free the current link_ref
            }
            r = next; // Move to the next link_ref
        }
    }
}

/*
 * Check whether a char is a Markdown space.

 * Right now we only consider spaces the actual
 * space and a newline: tabs and carriage returns
 * are filtered out during the preprocessing phase.
 *
 * If we wanted to actually be UTF-8 compliant, we
 * should instead extract an Unicode codepoint from
 * this character and check for space properties.
 */
#[inline]
 fn _isspace(c: i32) -> i32 {
    (c == ' ' as i32 || c == '\n' as i32) as i32
}

/* ***************************
 * INLINE PARSING FUNCTIONS *
 ****************************/
/* is_mail_autolink -- looks for the address part of a mail autolink and '>' */
/* this is less strict than the original markdown e-mail address matching */
unsafe extern "C" fn is_mail_autolink(mut data: *mut uint8_t,
                                      mut size: size_t) -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut nb: size_t = 0 as std::os::raw::c_int as size_t;
    /* address is assumed to be: [-@._a-zA-Z0-9]+ with exactly one '@' */
    i = 0 as std::os::raw::c_int as size_t;
    while i < size {
        if !(*(*__ctype_b_loc()).offset(*data.offset(i as isize) as
                                            std::os::raw::c_int as isize) as
                 std::os::raw::c_int &
                 _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int !=
                 0) {
            match *data.offset(i as isize) as std::os::raw::c_int {
                64 => { nb = nb.wrapping_add(1) }
                45 | 46 | 95 => { }
                62 => {
                    return if nb == 1 as std::os::raw::c_int as std::os::raw::c_ulong {
                               i.wrapping_add(1 as std::os::raw::c_int as
                                                  std::os::raw::c_ulong)
                           } else { 0 as std::os::raw::c_int as std::os::raw::c_ulong }
                }
                _ => { return 0 as std::os::raw::c_int as size_t }
            }
        }
        i = i.wrapping_add(1)
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* tag_length -- returns the length of the given tag, or 0 is it's not valid */
unsafe extern "C" fn tag_length(mut data: *mut uint8_t, mut size: size_t,
                                mut autolink: *mut mkd_autolink) -> size_t {
    let mut i: size_t = 0;
    let mut j: size_t = 0;
    /* a valid tag can't be shorter than 3 chars */
    if size < 3 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    /* begins with a '<' optionally followed by '/', followed by letter or number */
    if *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int != '<' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    i =
        if *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               '/' as i32 {
            2 as std::os::raw::c_int
        } else { 1 as std::os::raw::c_int } as size_t;
    if *(*__ctype_b_loc()).offset(*data.offset(i as isize) as std::os::raw::c_int as
                                      isize) as std::os::raw::c_int &
           _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int == 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    /* scheme test */
    *autolink = MKDA_NOT_AUTOLINK;
    /* try to find the beginning of an URI */
    while i < size &&
              (*(*__ctype_b_loc()).offset(*data.offset(i as isize) as
                                              std::os::raw::c_int as isize) as
                   std::os::raw::c_int &
                   _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int !=
                   0 || *data.offset(i as isize) as std::os::raw::c_int == '.' as i32
                   || *data.offset(i as isize) as std::os::raw::c_int == '+' as i32 ||
                   *data.offset(i as isize) as std::os::raw::c_int == '-' as i32) {
        i = i.wrapping_add(1)
    }
    if i > 1 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(i as isize) as std::os::raw::c_int == '@' as i32 {
        j = is_mail_autolink(data.offset(i as isize), size.wrapping_sub(i));
        if j != 0 as std::os::raw::c_int as std::os::raw::c_ulong {
            *autolink = MKDA_EMAIL;
            return i.wrapping_add(j)
        }
    }
    if i > 2 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(i as isize) as std::os::raw::c_int == ':' as i32 {
        *autolink = MKDA_NORMAL;
        i = i.wrapping_add(1)
    }
    /* completing autolink test: no whitespace or ' or " */
    if i >= size {
        *autolink = MKDA_NOT_AUTOLINK
    } else if *autolink as u64 != 0 {
        j = i;
        while i < size {
            if *data.offset(i as isize) as std::os::raw::c_int == '\\' as i32 {
                i =
                    (i as
                         std::os::raw::c_ulong).wrapping_add(2 as std::os::raw::c_int as
                                                         std::os::raw::c_ulong) as
                        size_t as size_t
            } else {
                if *data.offset(i as isize) as std::os::raw::c_int == '>' as i32 ||
                       *data.offset(i as isize) as std::os::raw::c_int == '\'' as i32
                       ||
                       *data.offset(i as isize) as std::os::raw::c_int == '\"' as i32
                       ||
                       *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32
                       ||
                       *data.offset(i as isize) as std::os::raw::c_int == '\n' as i32
                   {
                    break ;
                }
                i = i.wrapping_add(1)
            }
        }
        if i >= size { return 0 as std::os::raw::c_int as size_t }
        if i > j && *data.offset(i as isize) as std::os::raw::c_int == '>' as i32 {
            return i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
        }
        /* one of the forbidden chars has been found */
        *autolink = MKDA_NOT_AUTOLINK
    }
    /* looking for sometinhg looking like a tag end */
    while i < size && *data.offset(i as isize) as std::os::raw::c_int != '>' as i32 {
        i = i.wrapping_add(1)
    }
    if i >= size { return 0 as std::os::raw::c_int as size_t }
    return i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
}
/* parse_inline -- parses inline markdown elements */
unsafe extern "C" fn parse_inline(mut ob: *mut buf,
                                  mut rndr: *mut sd_markdown,
                                  mut data: *mut uint8_t, mut size: size_t) {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut end: size_t = 0 as std::os::raw::c_int as size_t;
    let mut last_special: size_t = 0 as std::os::raw::c_int as size_t;
    let mut action: uint8_t = 0 as std::os::raw::c_int as uint8_t;
    let mut work: buf =
        {
            let mut init =
                buf{data: 0 as *mut uint8_t,
                    size: 0 as std::os::raw::c_int as size_t,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    if (*rndr).work_bufs[1 as std::os::raw::c_int as
                             usize].size.wrapping_add((*rndr).work_bufs[0 as
                                                                            std::os::raw::c_int
                                                                            as
                                                                            usize].size)
           > (*rndr).max_nesting {
        return
    }
    while i < size {
        /* copying inactive chars into the output */
        while end < size &&
                  {
                      action =
                          (*rndr).active_char[*data.offset(end as isize) as
                                                  usize];
                      (action as std::os::raw::c_int) == 0 as std::os::raw::c_int
                  } {
            end = end.wrapping_add(1)
        }
        if (*rndr).cb.normal_text.is_some() {
            work.data = data.offset(i as isize);
            work.size = end.wrapping_sub(i);
            (*rndr).cb.normal_text.expect("non-null function pointer")(ob,
                                                                       &mut work,
                                                                       (*rndr).opaque);
        } else {
            bufput(ob, data.offset(i as isize) as *const std::os::raw::c_void,
                   end.wrapping_sub(i));
        }
        if end >= size { break ; }
        i = end;
        end =
            markdown_char_ptrs[action as std::os::raw::c_int as
                                   usize].expect("non-null function pointer")(ob,
                                                                              rndr,
                                                                              data.offset(i
                                                                                              as
                                                                                              isize),
                                                                              i.wrapping_sub(last_special),
                                                                              i,
                                                                              size.wrapping_sub(i));
        if end == 0 {
            /* no action from the callback */
            end = i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
        } else {
            i = (i as std::os::raw::c_ulong).wrapping_add(end) as size_t as size_t;
            end = i;
            last_special = end
        }
    };
}
/* find_emph_char -- looks for the next emph uint8_t, skipping other constructs */
unsafe extern "C" fn find_emph_char(mut data: *mut uint8_t, mut size: size_t,
                                    mut c: uint8_t) -> size_t {
    let mut i: size_t = 1 as std::os::raw::c_int as size_t;
    while i < size {
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int != c as std::os::raw::c_int
                  && *data.offset(i as isize) as std::os::raw::c_int != '`' as i32 &&
                  *data.offset(i as isize) as std::os::raw::c_int != '[' as i32 {
            i = i.wrapping_add(1)
        }
        if i == size { return 0 as std::os::raw::c_int as size_t }
        if i < size && c as std::os::raw::c_int == '<' as i32 &&
               *data.offset(i as isize) as std::os::raw::c_int == c as std::os::raw::c_int &&
               *data.offset(i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == '!' as i32 {
            return i
        }
        if *data.offset(i as isize) as std::os::raw::c_int == c as std::os::raw::c_int {
            return i
        }
        /* not counting escaped chars */
        if i != 0 &&
               *data.offset(i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == '\\' as i32 {
            i = i.wrapping_add(1)
        } else if *data.offset(i as isize) as std::os::raw::c_int == '`' as i32 {
            let mut span_nb: size_t = 0 as std::os::raw::c_int as size_t;
            let mut bt: size_t = 0;
            let mut tmp_i: size_t = 0 as std::os::raw::c_int as size_t;
            /* counting the number of opening backticks */
            while i < size &&
                      *data.offset(i as isize) as std::os::raw::c_int == '`' as i32 {
                i = i.wrapping_add(1);
                span_nb = span_nb.wrapping_add(1)
            }
            if i >= size { return 0 as std::os::raw::c_int as size_t }
            /* finding the matching closing sequence */
            bt = 0 as std::os::raw::c_int as size_t;
            while i < size && bt < span_nb {
                if tmp_i == 0 &&
                       *data.offset(i as isize) as std::os::raw::c_int ==
                           c as std::os::raw::c_int {
                    tmp_i = i
                }
                if *data.offset(i as isize) as std::os::raw::c_int == '`' as i32 {
                    bt = bt.wrapping_add(1)
                } else { bt = 0 as std::os::raw::c_int as size_t }
                i = i.wrapping_add(1)
            }
            if i >= size { return tmp_i }
        } else {
            /* skipping a link */
            if !(*data.offset(i as isize) as std::os::raw::c_int == '[' as i32) {
                continue ;
            }
            let mut tmp_i_0: size_t = 0 as std::os::raw::c_int as size_t;
            let mut cc: uint8_t = 0;
            i = i.wrapping_add(1);
            while i < size &&
                      *data.offset(i as isize) as std::os::raw::c_int != ']' as i32 {
                if tmp_i_0 == 0 &&
                       *data.offset(i as isize) as std::os::raw::c_int ==
                           c as std::os::raw::c_int {
                    tmp_i_0 = i
                }
                i = i.wrapping_add(1)
            }
            i = i.wrapping_add(1);
            while i < size &&
                      (*data.offset(i as isize) as std::os::raw::c_int == ' ' as i32
                           ||
                           *data.offset(i as isize) as std::os::raw::c_int ==
                               '\n' as i32) {
                i = i.wrapping_add(1)
            }
            if i >= size { return tmp_i_0 }
            match *data.offset(i as isize) as std::os::raw::c_int {
                91 => { cc = ']' as i32 as uint8_t }
                40 => { cc = ')' as i32 as uint8_t }
                _ => { if !(tmp_i_0 != 0) { continue ; } return tmp_i_0 }
            }
            i = i.wrapping_add(1);
            while i < size &&
                      *data.offset(i as isize) as std::os::raw::c_int !=
                          cc as std::os::raw::c_int {
                if tmp_i_0 == 0 &&
                       *data.offset(i as isize) as std::os::raw::c_int ==
                           c as std::os::raw::c_int {
                    tmp_i_0 = i
                }
                i = i.wrapping_add(1)
            }
            if i >= size { return tmp_i_0 }
            i = i.wrapping_add(1)
        }
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* parse_emph1 -- parsing single emphase */
/* closed by a symbol not preceded by whitespace and not followed by symbol */
unsafe extern "C" fn parse_emph1(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t, mut size: size_t,
                                 mut c: uint8_t) -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut len: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    let mut r: std::os::raw::c_int = 0;
    if (*rndr).cb.emphasis.is_none() { return 0 as std::os::raw::c_int as size_t }
    /* skipping one symbol if coming from emph3 */
    if size > 1 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               c as std::os::raw::c_int &&
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               c as std::os::raw::c_int {
        i = 1 as std::os::raw::c_int as size_t
    }
    while i < size {
        len =
            find_emph_char(data.offset(i as isize), size.wrapping_sub(i), c);
        if len == 0 { return 0 as std::os::raw::c_int as size_t }
        i = (i as std::os::raw::c_ulong).wrapping_add(len) as size_t as size_t;
        if i >= size { return 0 as std::os::raw::c_int as size_t }
        if !(*data.offset(i as isize) as std::os::raw::c_int == c as std::os::raw::c_int &&
                 _isspace(*data.offset(i.wrapping_sub(1 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong) as
                                           isize) as std::os::raw::c_int) == 0) {
            continue ;
        }
        if (*rndr).ext_flags &
               MKDEXT_NO_INTRA_EMPHASIS as std::os::raw::c_int as std::os::raw::c_uint != 0 &&
               c as std::os::raw::c_int == '_' as i32 {
            if !(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) == size ||
                     _isspace(*data.offset(i.wrapping_add(1 as std::os::raw::c_int as
                                                              std::os::raw::c_ulong)
                                               as isize) as std::os::raw::c_int) != 0
                     ||
                     *(*__ctype_b_loc()).offset(*data.offset(i.wrapping_add(1
                                                                                as
                                                                                std::os::raw::c_int
                                                                                as
                                                                                std::os::raw::c_ulong)
                                                                 as isize) as
                                                    std::os::raw::c_int as isize) as
                         std::os::raw::c_int &
                         _ISpunct as std::os::raw::c_int as std::os::raw::c_ushort as
                             std::os::raw::c_int != 0) {
                continue ;
            }
        }
        work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
        parse_inline(work, rndr, data, i);
        r =
            (*rndr).cb.emphasis.expect("non-null function pointer")(ob, work,
                                                                    (*rndr).opaque);
        rndr_popbuf(rndr, 1 as std::os::raw::c_int);
        return if r != 0 {
                   i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
               } else { 0 as std::os::raw::c_int as std::os::raw::c_ulong }
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* parse_emph2 -- parsing single emphase */
unsafe extern "C" fn parse_emph2(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t, mut size: size_t,
                                 mut c: uint8_t) -> size_t {
    let mut render_method:
            Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                        _: *mut std::os::raw::c_void)
                       -> std::os::raw::c_int> = None;
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut len: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    let mut r: std::os::raw::c_int = 0;
    render_method =
        if c as std::os::raw::c_int == '~' as i32 {
            (*rndr).cb.strikethrough
        } else { (*rndr).cb.double_emphasis };
    if render_method.is_none() { return 0 as std::os::raw::c_int as size_t }
    while i < size {
        len =
            find_emph_char(data.offset(i as isize), size.wrapping_sub(i), c);
        if len == 0 { return 0 as std::os::raw::c_int as size_t }
        i = (i as std::os::raw::c_ulong).wrapping_add(len) as size_t as size_t;
        if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
               *data.offset(i as isize) as std::os::raw::c_int == c as std::os::raw::c_int &&
               *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == c as std::os::raw::c_int
               && i != 0 &&
               _isspace(*data.offset(i.wrapping_sub(1 as std::os::raw::c_int as
                                                        std::os::raw::c_ulong) as
                                         isize) as std::os::raw::c_int) == 0 {
            work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
            parse_inline(work, rndr, data, i);
            r =
                render_method.expect("non-null function pointer")(ob, work,
                                                                  (*rndr).opaque);
            rndr_popbuf(rndr, 1 as std::os::raw::c_int);
            return if r != 0 {
                       i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
                   } else { 0 as std::os::raw::c_int as std::os::raw::c_ulong }
        }
        i = i.wrapping_add(1)
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* parse_emph3 -- parsing single emphase */
/* finds the first closing tag, and delegates to the other emph */
unsafe extern "C" fn parse_emph3(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t, mut size: size_t,
                                 mut c: uint8_t) -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut len: size_t = 0;
    let mut r: std::os::raw::c_int = 0;
    while i < size {
        len =
            find_emph_char(data.offset(i as isize), size.wrapping_sub(i), c);
        if len == 0 { return 0 as std::os::raw::c_int as size_t }
        i = (i as std::os::raw::c_ulong).wrapping_add(len) as size_t as size_t;
        /* skip whitespace preceded symbols */
        if *data.offset(i as isize) as std::os::raw::c_int != c as std::os::raw::c_int ||
               _isspace(*data.offset(i.wrapping_sub(1 as std::os::raw::c_int as
                                                        std::os::raw::c_ulong) as
                                         isize) as std::os::raw::c_int) != 0 {
            continue ;
        }
        if i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
               *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == c as std::os::raw::c_int
               &&
               *data.offset(i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == c as std::os::raw::c_int
               && (*rndr).cb.triple_emphasis.is_some() {
            /* triple symbol found */
            let mut work: *mut buf = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
            parse_inline(work, rndr, data, i);
            r =
                (*rndr).cb.triple_emphasis.expect("non-null function pointer")(ob,
                                                                               work,
                                                                               (*rndr).opaque);
            rndr_popbuf(rndr, 1 as std::os::raw::c_int);
            return if r != 0 {
                       i.wrapping_add(3 as std::os::raw::c_int as std::os::raw::c_ulong)
                   } else { 0 as std::os::raw::c_int as std::os::raw::c_ulong }
        } else if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
                      *data.offset(i.wrapping_add(1 as std::os::raw::c_int as
                                                      std::os::raw::c_ulong) as isize)
                          as std::os::raw::c_int == c as std::os::raw::c_int {
            /* double symbol found, handing over to emph1 */
            len =
                parse_emph1(ob, rndr,
                            data.offset(-(2 as std::os::raw::c_int as isize)),
                            size.wrapping_add(2 as std::os::raw::c_int as
                                                  std::os::raw::c_ulong), c);
            if len == 0 {
                return 0 as std::os::raw::c_int as size_t
            } else {
                return len.wrapping_sub(2 as std::os::raw::c_int as std::os::raw::c_ulong)
            }
        } else {
            /* single symbol found, handing over to emph2 */
            len =
                parse_emph2(ob, rndr,
                            data.offset(-(1 as std::os::raw::c_int as isize)),
                            size.wrapping_add(1 as std::os::raw::c_int as
                                                  std::os::raw::c_ulong), c);
            if len == 0 {
                return 0 as std::os::raw::c_int as size_t
            } else {
                return len.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
            }
        }
    }
    return 0 as std::os::raw::c_int as size_t;
}
unsafe extern "C" fn parse_spoilerspan(mut ob: *mut buf,
                                       mut rndr: *mut sd_markdown,
                                       mut data: *mut uint8_t,
                                       mut size: size_t) -> size_t {
    let mut render_method:
            Option<unsafe extern "C" fn(_: *mut buf, _: *const buf,
                                        _: *mut std::os::raw::c_void)
                       -> std::os::raw::c_int> = None;
    let mut len: size_t = 0;
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut work: *mut buf = 0 as *mut buf;
    let mut r: std::os::raw::c_int = 0;
    render_method = (*rndr).cb.spoilerspan;
    if render_method.is_none() { return 0 as std::os::raw::c_int as size_t }
    while i < size {
        len =
            find_emph_char(data.offset(i as isize), size.wrapping_sub(i),
                           '<' as i32 as uint8_t);
        if len == 0 { return 0 as std::os::raw::c_int as size_t }
        i = (i as std::os::raw::c_ulong).wrapping_add(len) as size_t as size_t;
        if i < size && *data.offset(i as isize) as std::os::raw::c_int == '<' as i32
               &&
               *data.offset(i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == '!' as i32 {
            work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
            parse_inline(work, rndr, data,
                         i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong));
            r =
                render_method.expect("non-null function pointer")(ob, work,
                                                                  (*rndr).opaque);
            rndr_popbuf(rndr, 1 as std::os::raw::c_int);
            if r == 0 { return 0 as std::os::raw::c_int as size_t }
            return i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
        }
        i = i.wrapping_add(1)
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* char_emphasis -- single and double emphasis parsing */
unsafe extern "C" fn char_emphasis(mut ob: *mut buf,
                                   mut rndr: *mut sd_markdown,
                                   mut data: *mut uint8_t,
                                   mut max_rewind: size_t,
                                   mut max_lookbehind: size_t,
                                   mut size: size_t) -> size_t {
    let mut c: uint8_t = *data.offset(0 as std::os::raw::c_int as isize);
    let mut ret: size_t = 0;
    if size > 3 as std::os::raw::c_int as std::os::raw::c_ulong &&
           c as std::os::raw::c_int == '>' as i32 &&
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               '!' as i32 {
        if _isspace(*data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int) !=
               0 ||
               {
                   ret =
                       parse_spoilerspan(ob, rndr,
                                         data.offset(2 as std::os::raw::c_int as
                                                         isize),
                                         size.wrapping_sub(2 as std::os::raw::c_int as
                                                               std::os::raw::c_ulong));
                   (ret) == 0 as std::os::raw::c_int as std::os::raw::c_ulong
               } {
            return 0 as std::os::raw::c_int as size_t
        }
        return ret.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    if size > 2 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
               c as std::os::raw::c_int {
        /* whitespace cannot follow an opening emphasis;
		 * strikethrough only takes two characters '~~' */
        if c as std::os::raw::c_int == '~' as i32 || c as std::os::raw::c_int == '>' as i32 ||
               _isspace(*data.offset(1 as std::os::raw::c_int as isize) as
                            std::os::raw::c_int) != 0 ||
               {
                   ret =
                       parse_emph1(ob, rndr,
                                   data.offset(1 as std::os::raw::c_int as isize),
                                   size.wrapping_sub(1 as std::os::raw::c_int as
                                                         std::os::raw::c_ulong), c);
                   (ret) == 0 as std::os::raw::c_int as std::os::raw::c_ulong
               } {
            return 0 as std::os::raw::c_int as size_t
        }
        return ret.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    if size > 3 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               c as std::os::raw::c_int &&
           *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
               c as std::os::raw::c_int {
        if _isspace(*data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int) !=
               0 ||
               {
                   ret =
                       parse_emph2(ob, rndr,
                                   data.offset(2 as std::os::raw::c_int as isize),
                                   size.wrapping_sub(2 as std::os::raw::c_int as
                                                         std::os::raw::c_ulong), c);
                   (ret) == 0 as std::os::raw::c_int as std::os::raw::c_ulong
               } {
            return 0 as std::os::raw::c_int as size_t
        }
        return ret.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    if size > 4 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               c as std::os::raw::c_int &&
           *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               c as std::os::raw::c_int &&
           *data.offset(3 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
               c as std::os::raw::c_int {
        if c as std::os::raw::c_int == '~' as i32 || c as std::os::raw::c_int == '>' as i32 ||
               _isspace(*data.offset(3 as std::os::raw::c_int as isize) as
                            std::os::raw::c_int) != 0 ||
               {
                   ret =
                       parse_emph3(ob, rndr,
                                   data.offset(3 as std::os::raw::c_int as isize),
                                   size.wrapping_sub(3 as std::os::raw::c_int as
                                                         std::os::raw::c_ulong), c);
                   (ret) == 0 as std::os::raw::c_int as std::os::raw::c_ulong
               } {
            return 0 as std::os::raw::c_int as size_t
        }
        return ret.wrapping_add(3 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* char_linebreak -- '\n' preceded by two spaces (assuming linebreak != 0) */
unsafe extern "C" fn char_linebreak(mut ob: *mut buf,
                                    mut rndr: *mut sd_markdown,
                                    mut data: *mut uint8_t,
                                    mut max_rewind: size_t,
                                    mut max_lookbehind: size_t,
                                    mut size: size_t) -> size_t {
    if max_rewind < 2 as std::os::raw::c_int as std::os::raw::c_ulong ||
           *data.offset(-(1 as std::os::raw::c_int) as isize) as std::os::raw::c_int !=
               ' ' as i32 ||
           *data.offset(-(2 as std::os::raw::c_int) as isize) as std::os::raw::c_int !=
               ' ' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    /* removing the last space from ob and rendering */
    while (*ob).size != 0 &&
              *(*ob).data.offset((*ob).size.wrapping_sub(1 as std::os::raw::c_int as
                                                             std::os::raw::c_ulong) as
                                     isize) as std::os::raw::c_int == ' ' as i32 {
        (*ob).size = (*ob).size.wrapping_sub(1)
    }
    return if (*rndr).cb.linebreak.expect("non-null function pointer")(ob,
                                                                       (*rndr).opaque)
                  != 0 {
               1 as std::os::raw::c_int
           } else { 0 as std::os::raw::c_int } as size_t;
}
/* char_codespan -- '`' parsing a code span (assuming codespan != 0) */
unsafe extern "C" fn char_codespan(mut ob: *mut buf,
                                   mut rndr: *mut sd_markdown,
                                   mut data: *mut uint8_t,
                                   mut max_rewind: size_t,
                                   mut max_lookbehind: size_t,
                                   mut size: size_t) -> size_t {
    let mut end: size_t = 0;
    let mut nb: size_t = 0 as std::os::raw::c_int as size_t;
    let mut i: size_t = 0;
    let mut f_begin: size_t = 0;
    let mut f_end: size_t = 0;
    /* counting the number of backticks in the delimiter */
    while nb < size && *data.offset(nb as isize) as std::os::raw::c_int == '`' as i32
          {
        nb = nb.wrapping_add(1)
    }
    /* finding the next delimiter */
    i = 0 as std::os::raw::c_int as size_t; /* no matching delimiter */
    end = nb;
    while end < size && i < nb {
        if *data.offset(end as isize) as std::os::raw::c_int == '`' as i32 {
            i = i.wrapping_add(1)
        } else { i = 0 as std::os::raw::c_int as size_t }
        end = end.wrapping_add(1)
    }
    if i < nb && end >= size { return 0 as std::os::raw::c_int as size_t }
    /* trimming outside whitespaces */
    f_begin = nb;
    while f_begin < end &&
              *data.offset(f_begin as isize) as std::os::raw::c_int == ' ' as i32 {
        f_begin = f_begin.wrapping_add(1)
    }
    f_end = end.wrapping_sub(nb);
    while f_end > nb &&
              *data.offset(f_end.wrapping_sub(1 as std::os::raw::c_int as
                                                  std::os::raw::c_ulong) as isize) as
                  std::os::raw::c_int == ' ' as i32 {
        f_end = f_end.wrapping_sub(1)
    }
    /* real code span */
    if f_begin < f_end {
        let mut work: buf =
            {
                let mut init =
                    buf{data: data.offset(f_begin as isize),
                        size: f_end.wrapping_sub(f_begin),
                        asize: 0 as std::os::raw::c_int as size_t,
                        unit: 0 as std::os::raw::c_int as size_t,};
                init
            };
        if (*rndr).cb.codespan.expect("non-null function pointer")(ob,
                                                                   &mut work,
                                                                   (*rndr).opaque)
               == 0 {
            end = 0 as std::os::raw::c_int as size_t
        }
    } else if (*rndr).cb.codespan.expect("non-null function pointer")(ob,
                                                                      0 as
                                                                          *const buf,
                                                                      (*rndr).opaque)
                  == 0 {
        end = 0 as std::os::raw::c_int as size_t
    }
    return end;
}
/* char_escape -- '\\' backslash escape */
unsafe extern "C" fn char_escape(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t,
                                 mut max_rewind: size_t,
                                 mut max_lookbehind: size_t, mut size: size_t)
 -> size_t {
    static mut escape_chars: *const std::os::raw::c_char =
        b"\\`*_{}[]()#+-.!:|&<>/^~\x00" as *const u8 as *const std::os::raw::c_char;
    let mut work: buf =
        {
            let mut init =
                buf{data: 0 as *mut uint8_t,
                    size: 0 as std::os::raw::c_int as size_t,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    if size > 1 as std::os::raw::c_int as std::os::raw::c_ulong {
        if strchr(escape_chars,
                  *data.offset(1 as std::os::raw::c_int as isize) as
                      std::os::raw::c_int).is_null() {
            return 0 as std::os::raw::c_int as size_t
        }
        if (*rndr).cb.normal_text.is_some() {
            work.data = data.offset(1 as std::os::raw::c_int as isize);
            work.size = 1 as std::os::raw::c_int as size_t;
            (*rndr).cb.normal_text.expect("non-null function pointer")(ob,
                                                                       &mut work,
                                                                       (*rndr).opaque);
        } else {
            bufputc(ob,
                    *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int);
        }
    } else if size == 1 as std::os::raw::c_int as std::os::raw::c_ulong {
        bufputc(ob, *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int);
    }
    return 2 as std::os::raw::c_int as size_t;
}
/* char_entity -- '&' escaped when it doesn't belong to an entity */
unsafe extern "C" fn char_entity(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t,
                                 mut max_rewind: size_t,
                                 mut max_lookbehind: size_t, mut size: size_t)
 -> size_t {
    let mut end: size_t = 1 as std::os::raw::c_int as size_t; /* not an entity */
    let mut content_start: size_t = 0; /* well-formed entity */
    let mut content_end: size_t = 0;
    let mut work: buf =
        {
            let mut init =
                buf{data: 0 as *mut uint8_t,
                    size: 0 as std::os::raw::c_int as size_t,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    let mut numeric: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut hex: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut entity_base: std::os::raw::c_int = 0;
    let mut entity_val: uint32_t = 0;
    if end < size && *data.offset(end as isize) as std::os::raw::c_int == '#' as i32 {
        numeric = 1 as std::os::raw::c_int;
        end = end.wrapping_add(1)
    }
    if end < size && numeric != 0 &&
           tolower(*data.offset(end as isize) as std::os::raw::c_int) == 'x' as i32 {
        hex = 1 as std::os::raw::c_int;
        end = end.wrapping_add(1)
    }
    content_start = end;
    while end < size {
        let c: std::os::raw::c_char = *data.offset(end as isize) as std::os::raw::c_char;
        if hex != 0 {
            if *(*__ctype_b_loc()).offset(c as std::os::raw::c_int as isize) as
                   std::os::raw::c_int &
                   _ISxdigit as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int
                   == 0 {
                break ;
            }
        } else if numeric != 0 {
            if *(*__ctype_b_loc()).offset(c as std::os::raw::c_int as isize) as
                   std::os::raw::c_int &
                   _ISdigit as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int ==
                   0 {
                break ;
            }
        } else if *(*__ctype_b_loc()).offset(c as std::os::raw::c_int as isize) as
                      std::os::raw::c_int &
                      _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int
                      == 0 {
            break ;
        }
        end = end.wrapping_add(1)
    }
    content_end = end;
    if end > content_start && end < size &&
           *data.offset(end as isize) as std::os::raw::c_int == ';' as i32 {
        end = end.wrapping_add(1)
    } else { return 0 as std::os::raw::c_int as size_t }
    /* way too long to be a valid numeric entity */
    if numeric != 0 &&
           content_end.wrapping_sub(content_start) > MAX_NUM_ENTITY_LEN {
        return 0 as std::os::raw::c_int as size_t
    }
    /* Validate the entity's contents */
    if numeric != 0 {
        if hex != 0 {
            entity_base = 16 as std::os::raw::c_int
        } else { entity_base = 10 as std::os::raw::c_int }
        // This is ok because  it'll stop once it hits the ';'
        entity_val =
            strtol((data as *mut std::os::raw::c_char).offset(content_start as isize),
                   0 as *mut *mut std::os::raw::c_char, entity_base) as uint32_t;
        if is_valid_numeric_entity(entity_val) == 0 {
            return 0 as std::os::raw::c_int as size_t
        }
    } else if is_allowed_named_entity(data as *const std::os::raw::c_char,
                                      end).is_null() {
        return 0 as std::os::raw::c_int as size_t
    }
    if (*rndr).cb.entity.is_some() {
        work.data = data;
        work.size = end;
        (*rndr).cb.entity.expect("non-null function pointer")(ob, &mut work,
                                                              (*rndr).opaque);
    } else {
        /* Necessary so we can normalize `&#X3E;` to `&#x3E;` */
        bufputc(ob, '&' as i32);
        if numeric != 0 { bufputc(ob, '#' as i32); }
        if hex != 0 { bufputc(ob, 'x' as i32); }
        bufput(ob, data.offset(content_start as isize) as *const std::os::raw::c_void,
               end.wrapping_sub(content_start));
    }
    return end;
}
/* char_langle_tag -- '<' when tags or autolinks are allowed */
unsafe extern "C" fn char_langle_tag(mut ob: *mut buf,
                                     mut rndr: *mut sd_markdown,
                                     mut data: *mut uint8_t,
                                     mut max_rewind: size_t,
                                     mut max_lookbehind: size_t,
                                     mut size: size_t) -> size_t {
    let mut altype: mkd_autolink = MKDA_NOT_AUTOLINK;
    let mut end: size_t = tag_length(data, size, &mut altype);
    let mut work: buf =
        {
            let mut init =
                buf{data: data,
                    size: end,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    let mut ret: std::os::raw::c_int = 0 as std::os::raw::c_int;
    if end > 2 as std::os::raw::c_int as std::os::raw::c_ulong {
        if (*rndr).cb.autolink.is_some() &&
               altype as std::os::raw::c_uint !=
                   MKDA_NOT_AUTOLINK as std::os::raw::c_int as std::os::raw::c_uint {
            let mut u_link: *mut buf = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
            work.data = data.offset(1 as std::os::raw::c_int as isize);
            work.size = end.wrapping_sub(2 as std::os::raw::c_int as std::os::raw::c_ulong);
            unscape_text(u_link, &mut work);
            ret =
                (*rndr).cb.autolink.expect("non-null function pointer")(ob,
                                                                        u_link,
                                                                        altype,
                                                                        (*rndr).opaque);
            rndr_popbuf(rndr, 1 as std::os::raw::c_int);
        } else if (*rndr).cb.raw_html_tag.is_some() {
            ret =
                (*rndr).cb.raw_html_tag.expect("non-null function pointer")(ob,
                                                                            &mut work,
                                                                            (*rndr).opaque)
        }
    }
    if ret == 0 { return 0 as std::os::raw::c_int as size_t } else { return end };
}
unsafe extern "C" fn char_autolink_www(mut ob: *mut buf,
                                       mut rndr: *mut sd_markdown,
                                       mut data: *mut uint8_t,
                                       mut max_rewind: size_t,
                                       mut max_lookbehind: size_t,
                                       mut size: size_t) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_url: *mut buf = 0 as *mut buf;
    let mut link_text: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    if (*rndr).cb.link.is_none() || (*rndr).in_link_body != 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    link = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    link_len =
        sd_autolink__www(&mut rewind, link, data, max_rewind, size,
                         0 as std::os::raw::c_int as std::os::raw::c_uint);
    if link_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        link_url = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
        bufput(link_url,
               b"http://\x00" as *const u8 as *const std::os::raw::c_char as
                   *const std::os::raw::c_void,
               (::std::mem::size_of::<[std::os::raw::c_char; 8]>() as
                    std::os::raw::c_ulong).wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong));
        bufput(link_url, (*link).data as *const std::os::raw::c_void, (*link).size);
        let new_size = (*ob).size.wrapping_sub(rewind);
buftruncate(&mut *ob, new_size as u64);
        if (*rndr).cb.normal_text.is_some() {
            link_text = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
            (*rndr).cb.normal_text.expect("non-null function pointer")(link_text,
                                                                       link,
                                                                       (*rndr).opaque);
            (*rndr).cb.link.expect("non-null function pointer")(ob, link_url,
                                                                0 as
                                                                    *const buf,
                                                                link_text,
                                                                (*rndr).opaque);
            rndr_popbuf(rndr, 1 as std::os::raw::c_int);
        } else {
            (*rndr).cb.link.expect("non-null function pointer")(ob, link_url,
                                                                0 as
                                                                    *const buf,
                                                                link,
                                                                (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    }
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    return link_len;
}
unsafe extern "C" fn char_autolink_subreddit_or_username(mut ob: *mut buf,
                                                         mut rndr:
                                                             *mut sd_markdown,
                                                         mut data:
                                                             *mut uint8_t,
                                                         mut max_rewind:
                                                             size_t,
                                                         mut max_lookbehind:
                                                             size_t,
                                                         mut size: size_t)
 -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_text: *mut buf = 0 as *mut buf;
    let mut link_url: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    let mut no_slash: std::os::raw::c_int = 0;
    if (*rndr).cb.autolink.is_none() || (*rndr).in_link_body != 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    link = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    link_len =
        sd_autolink__subreddit(&mut rewind, link, data, max_rewind,
                               max_lookbehind, size, &mut no_slash);
    if link_len == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        link_len =
            sd_autolink__username(&mut rewind, link, data, max_rewind,
                                  max_lookbehind, size, &mut no_slash)
    }
    /* Found either a user or subreddit link */
    if link_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        link_url = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
        if no_slash != 0 { bufputc(link_url, '/' as i32); }
        bufput(link_url, (*link).data as *const std::os::raw::c_void, (*link).size);
        let new_size = (*ob).size.wrapping_sub(rewind);
buftruncate(&mut *ob, new_size as u64);
        if (*rndr).cb.normal_text.is_some() {
            link_text = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
            (*rndr).cb.normal_text.expect("non-null function pointer")(link_text,
                                                                       link,
                                                                       (*rndr).opaque);
            (*rndr).cb.link.expect("non-null function pointer")(ob, link_url,
                                                                0 as
                                                                    *const buf,
                                                                link_text,
                                                                (*rndr).opaque);
            rndr_popbuf(rndr, 1 as std::os::raw::c_int);
        } else {
            (*rndr).cb.link.expect("non-null function pointer")(ob, link_url,
                                                                0 as
                                                                    *const buf,
                                                                link,
                                                                (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    }
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    return link_len;
}
unsafe extern "C" fn char_autolink_email(mut ob: *mut buf,
                                         mut rndr: *mut sd_markdown,
                                         mut data: *mut uint8_t,
                                         mut max_rewind: size_t,
                                         mut max_lookbehind: size_t,
                                         mut size: size_t) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    if (*rndr).cb.autolink.is_none() || (*rndr).in_link_body != 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    link = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    link_len =
        sd_autolink__email(&mut rewind, link, data, max_rewind, size,
                           0 as std::os::raw::c_int as std::os::raw::c_uint);
    if link_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        let new_size = (*ob).size.wrapping_sub(rewind);
buftruncate(&mut *ob, new_size as u64);
        (*rndr).cb.autolink.expect("non-null function pointer")(ob, link,
                                                                MKDA_EMAIL,
                                                                (*rndr).opaque);
    }
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    return link_len;
}
unsafe extern "C" fn char_autolink_url(mut ob: *mut buf,
                                       mut rndr: *mut sd_markdown,
                                       mut data: *mut uint8_t,
                                       mut max_rewind: size_t,
                                       mut max_lookbehind: size_t,
                                       mut size: size_t) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    if (*rndr).cb.autolink.is_none() || (*rndr).in_link_body != 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    link = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    link_len =
        sd_autolink__url(&mut rewind, link, data, max_rewind, size,
                         0 as std::os::raw::c_int as std::os::raw::c_uint);
    if link_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        let new_size = (*ob).size.wrapping_sub(rewind);
buftruncate(&mut *ob, new_size as u64);
        (*rndr).cb.autolink.expect("non-null function pointer")(ob, link,
                                                                MKDA_NORMAL,
                                                                (*rndr).opaque);
    }
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    return link_len;
}
/* char_link -- '[': parsing a link or an image */
unsafe extern "C" fn char_link(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                               mut data: *mut uint8_t, mut max_rewind: size_t,
                               mut max_lookbehind: size_t, mut size: size_t)
 -> size_t {
    let mut current_block: u64;
    let mut is_img: std::os::raw::c_int =
        (max_rewind != 0 &&
             *data.offset(-(1 as std::os::raw::c_int) as isize) as std::os::raw::c_int ==
                 '!' as i32) as std::os::raw::c_int;
    let mut level: std::os::raw::c_int = 0;
    let mut i: size_t = 1 as std::os::raw::c_int as size_t;
    let mut txt_e: size_t = 0;
    let mut link_b: size_t = 0 as std::os::raw::c_int as size_t;
    let mut link_e: size_t = 0 as std::os::raw::c_int as size_t;
    let mut title_b: size_t = 0 as std::os::raw::c_int as size_t;
    let mut title_e: size_t = 0 as std::os::raw::c_int as size_t;
    let mut content: *mut buf = 0 as *mut buf;
    let mut link: *mut buf = 0 as *mut buf;
    let mut title: *mut buf = 0 as *mut buf;
    let mut u_link: *mut buf = 0 as *mut buf;
    let mut org_work_size: size_t =
        (*rndr).work_bufs[1 as std::os::raw::c_int as usize].size;
    let mut text_has_nl: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut ret: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut in_title: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut qtype: std::os::raw::c_int = 0 as std::os::raw::c_int;
    /* checking whether the correct renderer exists */
    if !(is_img != 0 && (*rndr).cb.image.is_none() ||
             is_img == 0 && (*rndr).cb.link.is_none()) {
        /* looking for the matching closing bracket */
        let mut level = 1;
let data_slice = unsafe { std::slice::from_raw_parts(data, size as usize) };

for (i, &byte) in data_slice.iter().enumerate() {
    if byte == b'\n' {
        text_has_nl = 1;
    } else if i > 0 && data_slice[i - 1] != b'\\' {
        match byte {
            b'[' => level += 1,
            b']' => {
                level -= 1;
                if level <= 0 { break; }
            },
            _ => {}
        }
    }
}

if !(i as u64 >= size) {
     let mut txt_e = i;
i = i.wrapping_add(1);

// Skip any amount of whitespace or newline
while i < size && _isspace(unsafe { *data.offset(i as isize) } as i32) != 0 {
    i = i.wrapping_add(1);
}

// Inline style link
if i < size && unsafe { *data.offset(i as isize) } as i32 == '(' as i32 {
     let mut i = i.wrapping_add(1);
while i < size && _isspace(unsafe { *data.add(i as usize) } as i32) != 0 {
    i = i.wrapping_add(1);
}
let mut link_b = i;

// looking for link end: ' " )
while i < size {
    if unsafe { *data.add(i as usize) } as i32 == '\\' as i32 {
        i = i.wrapping_add(2);
    } else {
        if unsafe { *data.add(i as usize) } as i32 == ')' as i32 {
            break;
        }
        if i >= 1 && _isspace(unsafe { *data.add(i.wrapping_sub(1) as usize) } as i32) != 0 &&
           (unsafe { *data.add(i as usize) } as i32 == '\'' as i32 || unsafe { *data.add(i as usize) } as i32 == '\"' as i32) {
            break;
        }
        i = i.wrapping_add(1);
    }
}

if i >= size {
    current_block = 5149211417002599448;
} else {
    let mut link_e = i;

    // looking for title end if present
    if unsafe { *data.add(i as usize) } as i32 == '\'' as i32 || unsafe { *data.add(i as usize) } as i32 == '\"' as i32 {
        let qtype = unsafe { *data.add(i as usize) } as i32;
        let mut in_title = 1;
        i = i.wrapping_add(1);
        let mut title_b = i;

        while i < size {
            if unsafe { *data.add(i as usize) } as i32 == '\\' as i32 {
                i = i.wrapping_add(2);
            } else if unsafe { *data.add(i as usize) } as i32 == qtype {
                in_title = 0;
                i = i.wrapping_add(1);
            } else {
                if unsafe { *data.add(i as usize) } as i32 == ')' as i32 && in_title == 0 {
                    break;
                }
                i = i.wrapping_add(1);
            }
        }

        if i >= size {
            current_block = 5149211417002599448;
        } else {
            let mut title_e = i.wrapping_sub(1);
            while title_e > title_b && _isspace(unsafe { *data.add(title_e as usize) } as i32) != 0 {
                title_e = title_e.wrapping_sub(1);
            }

            // checking for closing quote presence
            if unsafe { *data.add(title_e as usize) } as i32 != '\'' as i32 && unsafe { *data.add(title_e as usize) } as i32 != '\"' as i32 {
                title_e = 0;
                title_b = title_e;
                link_e = i;
            }
            current_block = 13325891313334703151;
        }
    } else {
        current_block = 13325891313334703151;
    }

    match current_block {
        5149211417002599448 => {}
        _ => {
            // remove whitespace at the end of the link
            while link_e > link_b && _isspace(unsafe { *data.add(link_e.wrapping_sub(1) as usize) } as i32) != 0 {
                link_e = link_e.wrapping_sub(1);
            }

            // remove optional angle brackets around the link
            if unsafe { *data.add(link_b as usize) } as i32 == '<' as i32 {
                link_b = link_b.wrapping_add(1);
            }
            if unsafe { *data.add(link_e.wrapping_sub(1) as usize) } as i32 == '>' as i32 {
                link_e = link_e.wrapping_sub(1);
            }

            // building escaped link and title
            if link_e > link_b {
                let link = rndr_newbuf(rndr, 1);
                bufput(link, unsafe { data.add(link_b as usize) } as *const std::os::raw::c_void, (link_e.wrapping_sub(link_b)) as u64);
            }
            if title_e > title_b {
                let title = rndr_newbuf(rndr, 1);
                bufput(title, unsafe { data.add(title_b as usize) } as *const std::os::raw::c_void, (title_e.wrapping_sub(title_b)) as u64);
            }
            i = i.wrapping_add(1);
            current_block = 1930794479672247912;
        }
    }
}


} else if i < size && unsafe { *data.offset(i as isize) } as i32 == '[' as i32 {
     let mut id = buf {
    data: Vec::new().into_boxed_slice().as_mut_ptr(),
    size: 0,
    asize: 0,
    unit: 0,
};

let mut lr: *mut link_ref = std::ptr::null_mut();
/* reference style link */
/* looking for the id */
i += 1;
link_b = i;

while i < size && unsafe { *data.offset(i as isize) } != b']' {
    i += 1;
}

if i >= size {
    current_block = 5149211417002599448;
} else {
    link_e = i;
    /* finding the link_ref */
    if link_b == link_e {
        if text_has_nl != 0 {
            let mut b = rndr_newbuf(rndr, 1);
            let mut j: u64 = 1;
            while j < txt_e {
                if unsafe { *data.offset(j as isize) } != b'\n' {
                    bufputc(b, unsafe { *data.offset(j as isize) } as i32);
                } else if unsafe { *data.offset(j.wrapping_sub(1) as isize) } != b' ' {
                    bufputc(b, b' ' as i32);
                }
                j += 1;
            }
            id.data = unsafe { (*b).data };
            id.size = unsafe { (*b).size };
        } else {
            id.data = unsafe { data.offset(1) };
            id.size = txt_e.wrapping_sub(1);
        }
    } else {
        id.data = unsafe { data.offset(link_b as isize) };
        id.size = link_e.wrapping_sub(link_b);
    }
    
    lr = find_link_ref(&mut (*rndr).refs, unsafe { std::slice::from_raw_parts(id.data, id.size as usize) });
    if lr.is_null() {
        current_block = 5149211417002599448;
    } else {
        /* keeping link and title from link_ref */
        link = unsafe { (*lr).link };
        title = unsafe { (*lr).title };
        i += 1;
        current_block = 1930794479672247912;
    }
}


} else {
    // Shortcut reference style link
     let mut id_0 = buf {
    data: std::ptr::null_mut(),
    size: 0,
    asize: 0,
    unit: 0,
};

let mut lr_0: *mut link_ref = std::ptr::null_mut();

/* crafting the id */
if text_has_nl != 0 {
    let mut b_0 = rndr_newbuf(rndr, 1);
    for j_0 in 1..txt_e {
        let current_char = unsafe { *data.offset(j_0 as isize) as char };
        if current_char != '\n' {
            bufputc(b_0, current_char as i32);
        } else if unsafe { *data.offset((j_0 - 1) as isize) as char } != ' ' {
            bufputc(b_0, ' ' as i32);
        }
    }
    id_0.data = unsafe { (*b_0).data };
    id_0.size = unsafe { (*b_0).size };
} else {
    id_0.data = unsafe { data.offset(1) };
    id_0.size = txt_e - 1;
}

/* finding the link_ref */
lr_0 = find_link_ref(unsafe { &mut (*rndr).refs }, unsafe { std::slice::from_raw_parts(id_0.data, id_0.size as usize) });
if lr_0.is_null() {
    current_block = 5149211417002599448;
} else {
    let lr = unsafe { &*lr_0 };
    link = lr.link;
    title = lr.title;
    /* rewinding the whitespace */
    i = txt_e + 1;
    current_block = 1930794479672247912;
}


}

match current_block {
    5149211417002599448 => {}
    _ => {
        // Building content: img alt is escaped, link content is parsed
        if txt_e > 1 {
            content = rndr_newbuf(rndr, 1);
            if is_img != 0 {
                let len = (txt_e.wrapping_sub(1)) as usize;
                bufput(content, unsafe { data.offset(1) as *const std::os::raw::c_void }, len.try_into().unwrap());
            } else {
                // Disable autolinking when parsing inline the content of a link
                let rndr_ref = unsafe { &mut *rndr };
                rndr_ref.in_link_body = 1;
                parse_inline(content, rndr_ref, unsafe { data.offset(1) }, txt_e.wrapping_sub(1));
                rndr_ref.in_link_body = 0;
            }
        }
        if !link.is_null() {
            u_link = rndr_newbuf(rndr, 1);
            unscape_text(u_link, link);
            // Calling the relevant rendering function
            if is_img != 0 {
                let ob_ref = unsafe { &mut *ob };
                if ob_ref.size != 0 && unsafe { *ob_ref.data.offset(ob_ref.size.wrapping_sub(1) as isize) } as i32 == '!' as i32 {
                    ob_ref.size = ob_ref.size.wrapping_sub(1);
                }
                ret = unsafe { (*rndr).cb.image.expect("non-null function pointer")(ob, u_link, title, content, (*rndr).opaque) };
            } else {
                ret = unsafe { (*rndr).cb.link.expect("non-null function pointer")(ob, u_link, title, content, (*rndr).opaque) };
            }
        }
    }
}

/*
The variables live at this point are:
(mut ob: *mut src::autolink::buf, mut rndr: *mut src::markdown::sd_markdown, mut data: *mut u8, mut size: u64, mut current_block: u64, mut is_img: i32, mut i: u64, mut txt_e: u64, mut link_b: u64, mut link_e: u64, mut title_b: u64, mut title_e: u64, mut content: *mut src::autolink::buf, mut link: *mut src::autolink::buf, mut title: *mut src::autolink::buf, mut u_link: *mut src::autolink::buf, mut text_has_nl: i32, mut ret: i32, mut in_title: i32, mut qtype: i32)
*/


}

    }
    /* cleanup */
    (*rndr).work_bufs[1 as std::os::raw::c_int as usize].size =
        org_work_size as std::os::raw::c_int as size_t;
    return if ret != 0 { i } else { 0 as std::os::raw::c_int as std::os::raw::c_ulong };
}
unsafe extern "C" fn char_superscript(mut ob: *mut buf,
                                      mut rndr: *mut sd_markdown,
                                      mut data: *mut uint8_t,
                                      mut max_rewind: size_t,
                                      mut max_lookbehind: size_t,
                                      mut size: size_t) -> size_t {
    let mut sup_start: size_t = 0;
    let mut sup_len: size_t = 0;
    let mut sup: *mut buf = 0 as *mut buf;
    if (*rndr).cb.superscript.is_none() { return 0 as std::os::raw::c_int as size_t }
    if size < 2 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    if *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int == '(' as i32 {
        sup_len = 2 as std::os::raw::c_int as size_t;
        sup_start = sup_len;
        while sup_len < size &&
                  *data.offset(sup_len as isize) as std::os::raw::c_int != ')' as i32
                  &&
                  *data.offset(sup_len.wrapping_sub(1 as std::os::raw::c_int as
                                                        std::os::raw::c_ulong) as
                                   isize) as std::os::raw::c_int != '\\' as i32 {
            sup_len = sup_len.wrapping_add(1)
        }
        if sup_len == size { return 0 as std::os::raw::c_int as size_t }
    } else {
        sup_len = 1 as std::os::raw::c_int as size_t;
        sup_start = sup_len;
        while sup_len < size &&
                  _isspace(*data.offset(sup_len as isize) as std::os::raw::c_int) == 0
              {
            sup_len = sup_len.wrapping_add(1)
        }
    }
    if sup_len.wrapping_sub(sup_start) == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return if sup_start == 2 as std::os::raw::c_int as std::os::raw::c_ulong {
                   3 as std::os::raw::c_int
               } else { 0 as std::os::raw::c_int } as size_t
    }
    sup = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    parse_inline(sup, rndr, data.offset(sup_start as isize),
                 sup_len.wrapping_sub(sup_start));
    (*rndr).cb.superscript.expect("non-null function pointer")(ob, sup,
                                                               (*rndr).opaque);
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    return if sup_start == 2 as std::os::raw::c_int as std::os::raw::c_ulong {
               sup_len.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
           } else { sup_len };
}
/* ********************************
 * BLOCK-LEVEL PARSING FUNCTIONS *
 *********************************/
/* is_empty -- returns the line length when it is empty, 0 otherwise */
unsafe extern "C" fn is_empty(mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut i: size_t = 0;
    i = 0 as std::os::raw::c_int as size_t;
    while i < size && *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 {
        if *data.offset(i as isize) as std::os::raw::c_int != ' ' as i32 {
            return 0 as std::os::raw::c_int as size_t
        }
        i = i.wrapping_add(1)
    }
    return i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
}
/* is_hrule -- returns whether a line is a horizontal rule */
fn is_hrule(data: *mut u8, size: u64) -> i32 {
    let size_usize: usize = size.try_into().unwrap(); // Convert u64 to usize
    let data_slice = unsafe { std::slice::from_raw_parts(data, size_usize) };
    let mut i: usize = 0;
    let mut n: usize = 0;
    let mut c: u8 = 0;

    // Skipping initial spaces
    if size_usize < 3 { return 0; }
    while i < size_usize && data_slice[i] == b' ' {
        i += 1;
    }

    // Check for hrule character
    if i + 2 >= size_usize || !(data_slice[i] == b'*' || data_slice[i] == b'-' || data_slice[i] == b'_') {
        return 0;
    }
    c = data_slice[i];

    // The whole line must be the char or whitespace
    while i < size_usize && data_slice[i] != b'\n' {
        if data_slice[i] == c {
            n += 1;
        } else if data_slice[i] != b' ' {
            return 0;
        }
        i += 1;
    }
    return (n >= 3) as i32;
}

/* check if a line begins with a code fence; return the
 * width of the code fence */
unsafe extern "C" fn prefix_codefence(mut data: *mut uint8_t,
                                      mut size: size_t) -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut n: size_t = 0 as std::os::raw::c_int as size_t;
    let mut c: uint8_t = 0;
    /* skipping initial spaces */
    if size < 3 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    if *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        if *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               ' ' as i32 {
            i = i.wrapping_add(1);
            if *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                   ' ' as i32 {
                i = i.wrapping_add(1)
            }
        }
    }
    /* looking at the hrule uint8_t */
    if i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong) >= size ||
           !(*data.offset(i as isize) as std::os::raw::c_int == '~' as i32 ||
                 *data.offset(i as isize) as std::os::raw::c_int == '`' as i32) {
        return 0 as std::os::raw::c_int as size_t
    }
    c = *data.offset(i as isize);
    /* the whole line must be the uint8_t or whitespace */
    while i < size &&
              *data.offset(i as isize) as std::os::raw::c_int == c as std::os::raw::c_int {
        n = n.wrapping_add(1);
        i = i.wrapping_add(1)
    }
    if n < 3 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    return i;
}
/* check if a line is a code fence; return its size if it is */
unsafe extern "C" fn is_codefence(mut data: *mut uint8_t, mut size: size_t,
                                  mut syntax: *mut buf) -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut syn_len: size_t = 0 as std::os::raw::c_int as size_t;
    let mut syn_start: *mut uint8_t = 0 as *mut uint8_t;
    i = prefix_codefence(data, size);
    if i == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    while i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    syn_start = data.offset(i as isize);
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == '{' as i32 {
        i = i.wrapping_add(1);
        syn_start = syn_start.offset(1);
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int != '}' as i32 &&
                  *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 {
            syn_len = syn_len.wrapping_add(1);
            i = i.wrapping_add(1)
        }
        if i == size || *data.offset(i as isize) as std::os::raw::c_int != '}' as i32
           {
            return 0 as std::os::raw::c_int as size_t
        }
        /* strip all whitespace at the beginning and the end
		 * of the {} block */
        while syn_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
                  _isspace(*syn_start.offset(0 as std::os::raw::c_int as isize) as
                               std::os::raw::c_int) != 0 {
            syn_start = syn_start.offset(1);
            syn_len = syn_len.wrapping_sub(1)
        }
        while syn_len > 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
                  _isspace(*syn_start.offset(syn_len.wrapping_sub(1 as
                                                                      std::os::raw::c_int
                                                                      as
                                                                      std::os::raw::c_ulong)
                                                 as isize) as std::os::raw::c_int) !=
                      0 {
            syn_len = syn_len.wrapping_sub(1)
        }
        i = i.wrapping_add(1)
    } else {
        while i < size &&
                  _isspace(*data.offset(i as isize) as std::os::raw::c_int) == 0 {
            syn_len = syn_len.wrapping_add(1);
            i = i.wrapping_add(1)
        }
    }
    if !syntax.is_null() {
        (*syntax).data = syn_start;
        (*syntax).size = syn_len
    }
    while i < size && *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 {
        if _isspace(*data.offset(i as isize) as std::os::raw::c_int) == 0 {
            return 0 as std::os::raw::c_int as size_t
        }
        i = i.wrapping_add(1)
    }
    return i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
}
/* is_atxheader -- returns whether the line is a hash-prefixed header */
unsafe extern "C" fn is_atxheader(mut rndr: *mut sd_markdown,
                                  mut data: *mut uint8_t, mut size: size_t)
 -> std::os::raw::c_int {
    if *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int != '#' as i32 {
        return 0 as std::os::raw::c_int
    }
    if (*rndr).ext_flags & MKDEXT_SPACE_HEADERS as std::os::raw::c_int as std::os::raw::c_uint
           != 0 {
        let mut level: size_t = 0 as std::os::raw::c_int as size_t;
        while level < size && level < 6 as std::os::raw::c_int as std::os::raw::c_ulong &&
                  *data.offset(level as isize) as std::os::raw::c_int == '#' as i32 {
            level = level.wrapping_add(1)
        }
        if level < size &&
               *data.offset(level as isize) as std::os::raw::c_int != ' ' as i32 {
            return 0 as std::os::raw::c_int
        }
    }
    return 1 as std::os::raw::c_int;
}
/* is_headerline -- returns whether the line is a setext-style hdr underline */
unsafe extern "C" fn is_headerline(mut data: *mut uint8_t, mut size: size_t)
 -> std::os::raw::c_int {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    /* test of level 1 header */
    if *data.offset(i as isize) as std::os::raw::c_int == '=' as i32 {
        i = 1 as std::os::raw::c_int as size_t;
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int == '=' as i32 {
            i = i.wrapping_add(1)
        }
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
            i = i.wrapping_add(1)
        }
        return if i >= size ||
                      *data.offset(i as isize) as std::os::raw::c_int == '\n' as i32 {
                   1 as std::os::raw::c_int
               } else { 0 as std::os::raw::c_int }
    }
    /* test of level 2 header */
    if *data.offset(i as isize) as std::os::raw::c_int == '-' as i32 {
        i = 1 as std::os::raw::c_int as size_t;
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int == '-' as i32 {
            i = i.wrapping_add(1)
        }
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
            i = i.wrapping_add(1)
        }
        return if i >= size ||
                      *data.offset(i as isize) as std::os::raw::c_int == '\n' as i32 {
                   2 as std::os::raw::c_int
               } else { 0 as std::os::raw::c_int }
    }
    return 0 as std::os::raw::c_int;
}
unsafe extern "C" fn is_next_headerline(mut data: *mut uint8_t,
                                        mut size: size_t) -> std::os::raw::c_int {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    while i < size && *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 {
        i = i.wrapping_add(1)
    }
    i = i.wrapping_add(1);
    if i >= size { return 0 as std::os::raw::c_int }
    return is_headerline(data.offset(i as isize), size.wrapping_sub(i));
}
/* prefix_quote -- returns blockquote prefix length */
unsafe extern "C" fn prefix_quote(mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == '>' as i32 &&
           (i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
                *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                 as isize) as std::os::raw::c_int != '!' as i32) {
        if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
               *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == ' ' as i32 {
            return i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
        }
        return i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    return 0 as std::os::raw::c_int as size_t;
}
unsafe extern "C" fn prefix_blockspoiler(mut data: *mut uint8_t,
                                         mut size: size_t) -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
           *data.offset(i as isize) as std::os::raw::c_int == '>' as i32 &&
           *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
                            isize) as std::os::raw::c_int == '!' as i32 {
        let mut spoilerspan: size_t =
            find_emph_char(data.offset(i as
                                           isize).offset(1 as std::os::raw::c_int as
                                                             isize),
                           size.wrapping_sub(i).wrapping_sub(1 as std::os::raw::c_int
                                                                 as
                                                                 std::os::raw::c_ulong),
                           '<' as i32 as uint8_t);
        if i.wrapping_add(spoilerspan) < size &&
               spoilerspan > 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
               *data.offset(i.wrapping_add(spoilerspan) as isize) as
                   std::os::raw::c_int == '!' as i32 {
            return 0 as std::os::raw::c_int as size_t
        }
        if i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong) < size &&
               *data.offset(i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == ' ' as i32 {
            return i.wrapping_add(3 as std::os::raw::c_int as std::os::raw::c_ulong)
        }
        return i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* prefix_code -- returns prefix length for block code*/
unsafe extern "C" fn prefix_code(mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    if size > 3 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               ' ' as i32 &&
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               ' ' as i32 &&
           *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               ' ' as i32 &&
           *data.offset(3 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
               ' ' as i32 {
        return 4 as std::os::raw::c_int as size_t
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* prefix_oli -- returns ordered list item prefix */
unsafe extern "C" fn prefix_oli(mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i >= size || (*data.offset(i as isize) as std::os::raw::c_int) < '0' as i32 ||
           *data.offset(i as isize) as std::os::raw::c_int > '9' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    while i < size && *data.offset(i as isize) as std::os::raw::c_int >= '0' as i32 &&
              *data.offset(i as isize) as std::os::raw::c_int <= '9' as i32 {
        i = i.wrapping_add(1)
    }
    if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) >= size ||
           *data.offset(i as isize) as std::os::raw::c_int != '.' as i32 ||
           *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
                            isize) as std::os::raw::c_int != ' ' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    if is_next_headerline(data.offset(i as isize), size.wrapping_sub(i)) != 0
       {
        return 0 as std::os::raw::c_int as size_t
    }
    return i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong);
}
/* prefix_uli -- returns ordered list item prefix */
unsafe extern "C" fn prefix_uli(mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) >= size ||
           *data.offset(i as isize) as std::os::raw::c_int != '*' as i32 &&
               *data.offset(i as isize) as std::os::raw::c_int != '+' as i32 &&
               *data.offset(i as isize) as std::os::raw::c_int != '-' as i32 ||
           *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
                            isize) as std::os::raw::c_int != ' ' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    if is_next_headerline(data.offset(i as isize), size.wrapping_sub(i)) != 0
       {
        return 0 as std::os::raw::c_int as size_t
    }
    return i.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong);
}
/* parse_blockquote -- handles parsing of a blockquote fragment */
unsafe extern "C" fn parse_blockquote(mut ob: *mut buf,
                                      mut rndr: *mut sd_markdown,
                                      mut data: *mut uint8_t,
                                      mut size: size_t) -> size_t {
    let mut beg: size_t = 0; /* skipping prefix */
    let mut end: size_t = 0 as std::os::raw::c_int as size_t;
    let mut pre: size_t = 0;
    let mut work_size: size_t = 0 as std::os::raw::c_int as size_t;
    let mut work_data: *mut uint8_t = 0 as *mut uint8_t;
    let mut out: *mut buf = 0 as *mut buf;
    out = rndr_newbuf(rndr, 0 as std::os::raw::c_int);
    beg = 0 as std::os::raw::c_int as size_t;
    while beg < size {
        end = beg.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
        while end < size &&
                  *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
                      as std::os::raw::c_int != '\n' as i32 {
            end = end.wrapping_add(1)
        }
        pre = prefix_quote(data.offset(beg as isize), end.wrapping_sub(beg));
        if pre != 0 {
            beg = (beg as std::os::raw::c_ulong).wrapping_add(pre) as size_t as size_t
        } else if is_empty(data.offset(beg as isize), end.wrapping_sub(beg))
                      != 0 &&
                      (end >= size ||
                           prefix_quote(data.offset(end as isize),
                                        size.wrapping_sub(end)) ==
                               0 as std::os::raw::c_int as std::os::raw::c_ulong &&
                               is_empty(data.offset(end as isize),
                                        size.wrapping_sub(end)) == 0)
         /* empty line followed by non-quote line */
         {
            break ;
        }
        if beg < end {
            /* copy into the in-place working buffer */
            /* bufput(work, data + beg, end - beg); */
            if work_data.is_null() {
                work_data = data.offset(beg as isize)
            } else if data.offset(beg as isize) !=
                          work_data.offset(work_size as isize) {
                memmove(work_data.offset(work_size as isize) as
                            *mut std::os::raw::c_void,
                        data.offset(beg as isize) as *const std::os::raw::c_void,
                        end.wrapping_sub(beg));
            }
            work_size =
                (work_size as
                     std::os::raw::c_ulong).wrapping_add(end.wrapping_sub(beg)) as
                    size_t as size_t
        }
        beg = end
    }
    parse_block(out, rndr, work_data, work_size);
    if (*rndr).cb.blockquote.is_some() {
        (*rndr).cb.blockquote.expect("non-null function pointer")(ob, out,
                                                                  (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as std::os::raw::c_int);
    return end;
}
/* parse_blockspoiler -- handles parsing of a blockspoiler fragment */
unsafe extern "C" fn parse_blockspoiler(mut ob: *mut buf,
                                        mut rndr: *mut sd_markdown,
                                        mut data: *mut uint8_t,
                                        mut size: size_t) -> size_t {
    let mut beg: size_t = 0; /* skipping prefix */
    let mut end: size_t = 0 as std::os::raw::c_int as size_t;
    let mut pre: size_t = 0;
    let mut work_size: size_t = 0 as std::os::raw::c_int as size_t;
    let mut work_data: *mut uint8_t = 0 as *mut uint8_t;
    let mut out: *mut buf = 0 as *mut buf;
    out = rndr_newbuf(rndr, 0 as std::os::raw::c_int);
    beg = 0 as std::os::raw::c_int as size_t;
    while beg < size {
        end = beg.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
        while end < size &&
                  *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
                      as std::os::raw::c_int != '\n' as i32 {
            end = end.wrapping_add(1)
        }
        pre =
            prefix_blockspoiler(data.offset(beg as isize),
                                end.wrapping_sub(beg));
        if pre != 0 {
            beg = (beg as std::os::raw::c_ulong).wrapping_add(pre) as size_t as size_t
        } else if is_empty(data.offset(beg as isize), end.wrapping_sub(beg))
                      != 0 &&
                      (end >= size ||
                           prefix_blockspoiler(data.offset(end as isize),
                                               size.wrapping_sub(end)) ==
                               0 as std::os::raw::c_int as std::os::raw::c_ulong &&
                               is_empty(data.offset(end as isize),
                                        size.wrapping_sub(end)) == 0)
         /* empty line followed by non-blockspoiler line */
         {
            break ;
        }
        if beg < end {
            /* copy into the in-place working buffer */
            /* bufput(work, data + beg, end - beg); */
            if work_data.is_null() {
                work_data = data.offset(beg as isize)
            } else if data.offset(beg as isize) !=
                          work_data.offset(work_size as isize) {
                memmove(work_data.offset(work_size as isize) as
                            *mut std::os::raw::c_void,
                        data.offset(beg as isize) as *const std::os::raw::c_void,
                        end.wrapping_sub(beg));
            }
            work_size =
                (work_size as
                     std::os::raw::c_ulong).wrapping_add(end.wrapping_sub(beg)) as
                    size_t as size_t
        }
        beg = end
    }
    parse_block(out, rndr, work_data, work_size);
    if (*rndr).cb.blockspoiler.is_some() {
        (*rndr).cb.blockspoiler.expect("non-null function pointer")(ob, out,
                                                                    (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as std::os::raw::c_int);
    return end;
}
/* parse_blockquote -- handles parsing of a regular paragraph */
unsafe extern "C" fn parse_paragraph(mut ob: *mut buf,
                                     mut rndr: *mut sd_markdown,
                                     mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut end: size_t = 0 as std::os::raw::c_int as size_t;
    let mut level: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut work: buf =
        {
            let mut init =
                buf{data: data,
                    size: 0 as std::os::raw::c_int as size_t,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    while i < size {
        end = i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
        while end < size &&
                  *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
                      as std::os::raw::c_int != '\n' as i32 {
            /* empty */
            end = end.wrapping_add(1)
        }
        if prefix_quote(data.offset(i as isize), end.wrapping_sub(i)) !=
               0 as std::os::raw::c_int as std::os::raw::c_ulong {
            end = i;
            break ;
        } else {
            if is_empty(data.offset(i as isize), size.wrapping_sub(i)) != 0 {
                break ;
            }
            level =
                is_headerline(data.offset(i as isize), size.wrapping_sub(i));
            if level != 0 as std::os::raw::c_int { break ; }
            if is_atxheader(rndr, data.offset(i as isize),
                            size.wrapping_sub(i)) != 0 ||
                   is_hrule(data.offset(i as isize), size.wrapping_sub(i)) !=
                       0 ||
                   prefix_quote(data.offset(i as isize), size.wrapping_sub(i))
                       != 0 {
                end = i;
                break ;
            } else {
                /*
		 * Early termination of a paragraph with the same logic
		 * as Markdown 1.0.0. If this logic is applied, the
		 * Markdown 1.0.3 test suite won't pass cleanly
		 *
		 * :: If the first character in a new line is not a letter,
		 * let's check to see if there's some kind of block starting
		 * here
		 */
                if (*rndr).ext_flags &
                       MKDEXT_LAX_SPACING as std::os::raw::c_int as std::os::raw::c_uint != 0
                       &&
                       *(*__ctype_b_loc()).offset(*data.offset(i as isize) as
                                                      std::os::raw::c_int as isize) as
                           std::os::raw::c_int &
                           _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as
                               std::os::raw::c_int == 0 {
                    if prefix_oli(data.offset(i as isize),
                                  size.wrapping_sub(i)) != 0 ||
                           prefix_uli(data.offset(i as isize),
                                      size.wrapping_sub(i)) != 0 {
                        end = i;
                        break ;
                    } else if *data.offset(i as isize) as std::os::raw::c_int ==
                                  '<' as i32 && (*rndr).cb.blockhtml.is_some()
                                  &&
                                  parse_htmlblock(ob, rndr,
                                                  data.offset(i as isize),
                                                  size.wrapping_sub(i),
                                                  0 as std::os::raw::c_int) != 0 {
                        end = i;
                        break ;
                    } else if (*rndr).ext_flags &
                                  MKDEXT_FENCED_CODE as std::os::raw::c_int as
                                      std::os::raw::c_uint !=
                                  0 as std::os::raw::c_int as std::os::raw::c_uint &&
                                  is_codefence(data.offset(i as isize),
                                               size.wrapping_sub(i),
                                               0 as *mut buf) !=
                                      0 as std::os::raw::c_int as std::os::raw::c_ulong {
                        end = i;
                        break ;
                    }
                }
                i = end
            }
        }
    }
    work.size = i;
    while work.size != 0 &&
              *data.offset(work.size.wrapping_sub(1 as std::os::raw::c_int as
                                                      std::os::raw::c_ulong) as isize)
                  as std::os::raw::c_int == '\n' as i32 {
        work.size = work.size.wrapping_sub(1)
    }
    if level == 0 {
    let tmp = rndr_newbuf(rndr, 0);
    parse_inline(tmp, rndr, work.data, work.size);
    if let Some(paragraph_cb) = unsafe { (*rndr).cb.paragraph } {
        paragraph_cb(ob, tmp, unsafe { (*rndr).opaque });
    }
    rndr_popbuf(rndr, 0);
} else {
    let mut header_work: *mut buf = std::ptr::null_mut();
    if work.size != 0 {
        let mut beg: u64 = 0; // Change to u64 to match work.size
        i = work.size;
        work.size -= 1;

        while work.size != 0 && unsafe { *data.add(work.size.wrapping_sub(1) as usize) } != b'\n' {
            work.size -= 1;
        }

        beg = work.size + 1;

        while work.size != 0 && unsafe { *data.add(work.size.wrapping_sub(1) as usize) } == b'\n' {
            work.size -= 1;
        }

        if work.size > 0 {
            let tmp_0 = rndr_newbuf(rndr, 0);
            parse_inline(tmp_0, rndr, work.data, work.size);
            if let Some(paragraph_cb) = unsafe { (*rndr).cb.paragraph } {
                paragraph_cb(ob, tmp_0, unsafe { (*rndr).opaque });
            }
            rndr_popbuf(rndr, 0);
            work.data = unsafe { work.data.add(beg as usize) };
            work.size = i.wrapping_sub(beg);
        } else {
            work.size = i;
        }
    }

    header_work = rndr_newbuf(rndr, 1);
    parse_inline(header_work, rndr, work.data, work.size);
    if let Some(header_cb) = unsafe { (*rndr).cb.header } {
        header_cb(ob, header_work, level, unsafe { (*rndr).opaque });
    }
    rndr_popbuf(rndr, 1);
}
return end;

}
/* see if an html block starts here */
/* see if a code fence starts here */
/* parse_fencedcode -- handles parsing of a block-level code fragment */
unsafe extern "C" fn parse_fencedcode(mut ob: *mut buf,
                                      mut rndr: *mut sd_markdown,
                                      mut data: *mut uint8_t,
                                      mut size: size_t) -> size_t {
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    let mut lang: buf =
        {
            let mut init =
                buf{data: 0 as *mut uint8_t,
                    size: 0 as std::os::raw::c_int as size_t,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    beg = is_codefence(data, size, &mut lang);
    if beg == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    work = rndr_newbuf(rndr, 0 as std::os::raw::c_int);
    while beg < size {
        let mut fence_end: size_t = 0;
        let mut fence_trail: buf =
            {
                let mut init =
                    buf{data: 0 as *mut uint8_t,
                        size: 0 as std::os::raw::c_int as size_t,
                        asize: 0 as std::os::raw::c_int as size_t,
                        unit: 0 as std::os::raw::c_int as size_t,};
                init
            };
        fence_end =
            is_codefence(data.offset(beg as isize), size.wrapping_sub(beg),
                         &mut fence_trail);
        if fence_end != 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
               fence_trail.size == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
            beg =
                (beg as std::os::raw::c_ulong).wrapping_add(fence_end) as size_t as
                    size_t;
            break ;
        } else {
            end = beg.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
            while end < size &&
                      *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as
                                                        std::os::raw::c_ulong) as
                                       isize) as std::os::raw::c_int != '\n' as i32 {
                end = end.wrapping_add(1)
            }
            if beg < end {
                /* verbatim copy to the working buffer,
				escaping entities */
                if is_empty(data.offset(beg as isize), end.wrapping_sub(beg))
                       != 0 {
                    bufputc(work, '\n' as i32); /* skipping prefix */
                } else {
                    bufput(work,
                           data.offset(beg as isize) as *const std::os::raw::c_void,
                           end.wrapping_sub(beg));
                }
            }
            beg = end
        }
    }
    if (*work).size != 0 &&
           *(*work).data.offset((*work).size.wrapping_sub(1 as std::os::raw::c_int as
                                                              std::os::raw::c_ulong)
                                    as isize) as std::os::raw::c_int != '\n' as i32 {
        bufputc(work, '\n' as i32);
    }
    if (*rndr).cb.blockcode.is_some() {
        (*rndr).cb.blockcode.expect("non-null function pointer")(ob, work,
                                                                 if lang.size
                                                                        != 0 {
                                                                     &mut lang
                                                                 } else {
                                                                     0 as
                                                                         *mut buf
                                                                 },
                                                                 (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as std::os::raw::c_int);
    return beg;
}
unsafe extern "C" fn parse_blockcode(mut ob: *mut buf,
                                     mut rndr: *mut sd_markdown,
                                     mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let mut pre: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    work = rndr_newbuf(rndr, 0 as std::os::raw::c_int);
    beg = 0 as std::os::raw::c_int as size_t;
    while beg < size {
        end = beg.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
        while end < size &&
                  *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
                      as std::os::raw::c_int != '\n' as i32 {
            end = end.wrapping_add(1)
        }
        pre = prefix_code(data.offset(beg as isize), end.wrapping_sub(beg));
        if pre != 0 {
            beg = (beg as std::os::raw::c_ulong).wrapping_add(pre) as size_t as size_t
        } else if is_empty(data.offset(beg as isize), end.wrapping_sub(beg))
                      == 0 {
            break ;
        }
        if beg < end {
            /* verbatim copy to the working buffer,
				escaping entities */
            if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0
               {
                bufputc(work, '\n' as i32);
            } else {
                bufput(work, data.offset(beg as isize) as *const std::os::raw::c_void,
                       end.wrapping_sub(beg));
            }
        }
        beg = end
    }
    while (*work).size != 0 &&
              *(*work).data.offset((*work).size.wrapping_sub(1 as std::os::raw::c_int
                                                                 as
                                                                 std::os::raw::c_ulong)
                                       as isize) as std::os::raw::c_int == '\n' as i32
          {
        (*work).size =
            ((*work).size as
                 std::os::raw::c_ulong).wrapping_sub(1 as std::os::raw::c_int as
                                                 std::os::raw::c_ulong) as size_t as
                size_t
    }
    bufputc(work, '\n' as i32);
    if (*rndr).cb.blockcode.is_some() {
        (*rndr).cb.blockcode.expect("non-null function pointer")(ob, work,
                                                                 0 as
                                                                     *const buf,
                                                                 (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as std::os::raw::c_int);
    return beg;
}
/* parse_listitem -- parsing of a single list item */
/*	assuming initial prefix is already removed */
unsafe extern "C" fn parse_listitem(mut ob: *mut buf,
                                    mut rndr: *mut sd_markdown,
                                    mut data: *mut uint8_t, mut size: size_t,
                                    mut flags: *mut std::os::raw::c_int) -> size_t {
    let mut work: *mut buf = 0 as *mut buf;
    let mut inter: *mut buf = 0 as *mut buf;
    let mut beg: size_t = 0 as std::os::raw::c_int as size_t;
    let mut end: size_t = 0;
    let mut pre: size_t = 0;
    let mut sublist: size_t = 0 as std::os::raw::c_int as size_t;
    let mut orgpre: size_t = 0 as std::os::raw::c_int as size_t;
    let mut i: size_t = 0;
    let mut in_empty: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut has_inside_empty: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut in_fence: std::os::raw::c_int = 0 as std::os::raw::c_int;
    /* keeping track of the first indentation prefix */
    while orgpre < 3 as std::os::raw::c_int as std::os::raw::c_ulong && orgpre < size &&
              *data.offset(orgpre as isize) as std::os::raw::c_int == ' ' as i32 {
        orgpre = orgpre.wrapping_add(1)
    }
    beg = prefix_uli(data, size);
    if beg == 0 { beg = prefix_oli(data, size) }
    if beg == 0 { return 0 as std::os::raw::c_int as size_t }
    /* skipping to the beginning of the following line */
    end = beg;
    while end < size &&
              *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                               as isize) as std::os::raw::c_int != '\n' as i32 {
        end = end.wrapping_add(1)
    }
    /* getting working buffers */
    work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    inter = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    /* putting the first line into the working buffer */
    bufput(work, data.offset(beg as isize) as *const std::os::raw::c_void,
           end.wrapping_sub(beg));
    beg = end;
    /* process the following lines */
    while beg < size {
        let mut has_next_uli: size_t = 0 as std::os::raw::c_int as size_t;
        let mut has_next_oli: size_t = 0 as std::os::raw::c_int as size_t;
        end = end.wrapping_add(1);
        while end < size &&
                  *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
                      as std::os::raw::c_int != '\n' as i32 {
            end = end.wrapping_add(1)
        }
        /* process an empty line */
        if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0 {
            in_empty = 1 as std::os::raw::c_int;
            beg = end
        } else {
            /* calculating the indentation */
            i = 0 as std::os::raw::c_int as size_t;
            while i < 4 as std::os::raw::c_int as std::os::raw::c_ulong &&
                      beg.wrapping_add(i) < end &&
                      *data.offset(beg.wrapping_add(i) as isize) as
                          std::os::raw::c_int == ' ' as i32 {
                i = i.wrapping_add(1)
            }
            pre = i;
            if (*rndr).ext_flags &
                   MKDEXT_FENCED_CODE as std::os::raw::c_int as std::os::raw::c_uint != 0 {
                if is_codefence(data.offset(beg as isize).offset(i as isize),
                                end.wrapping_sub(beg).wrapping_sub(i),
                                0 as *mut buf) !=
                       0 as std::os::raw::c_int as std::os::raw::c_ulong {
                    in_fence = (in_fence == 0) as std::os::raw::c_int
                }
            }
            /* Only check for new list items if we are **not** inside
		 * a fenced code block */
            if in_fence == 0 {
                has_next_uli =
                    prefix_uli(data.offset(beg as isize).offset(i as isize),
                               end.wrapping_sub(beg).wrapping_sub(i));
                has_next_oli =
                    prefix_oli(data.offset(beg as isize).offset(i as isize),
                               end.wrapping_sub(beg).wrapping_sub(i))
            }
            /* checking for ul/ol switch */
            if in_empty != 0 &&
                   (*flags & 1 as std::os::raw::c_int != 0 && has_next_uli != 0 ||
                        *flags & 1 as std::os::raw::c_int == 0 && has_next_oli != 0) {
                *flags |= 8 as std::os::raw::c_int;
                break ;
                /* the following item must have same list type */
            } else {
                /* checking for a new item */
                if has_next_uli != 0 &&
                       is_hrule(data.offset(beg as isize).offset(i as isize),
                                end.wrapping_sub(beg).wrapping_sub(i)) == 0 ||
                       has_next_oli != 0 {
                    if in_empty != 0 {
                        has_inside_empty = 1 as std::os::raw::c_int
                    } /* the same indentation */
                    if pre == orgpre { break ; }
                    if sublist == 0 { sublist = (*work).size }
                } else if in_empty != 0 &&
                              pre == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
                    *flags |= 8 as std::os::raw::c_int;
                    break ;
                } else if in_empty != 0 {
                    bufputc(work, '\n' as i32);
                    has_inside_empty = 1 as std::os::raw::c_int
                }
                in_empty = 0 as std::os::raw::c_int;
                /* joining only indented stuff after empty lines;
		 * note that now we only require 1 space of indentation
		 * to continue a list */
                /* adding the line without prefix into the working buffer */
                bufput(work,
                       data.offset(beg as isize).offset(i as isize) as
                           *const std::os::raw::c_void,
                       end.wrapping_sub(beg).wrapping_sub(i));
                beg = end
            }
        }
    }
    /* render of li contents */
    if has_inside_empty != 0 { *flags |= 2 as std::os::raw::c_int }
    if *flags & 2 as std::os::raw::c_int != 0 {
        /* intermediate render of block li */
        if sublist != 0 && sublist < (*work).size {
            parse_block(inter, rndr, (*work).data, sublist);
            parse_block(inter, rndr, (*work).data.offset(sublist as isize),
                        (*work).size.wrapping_sub(sublist));
        } else { parse_block(inter, rndr, (*work).data, (*work).size); }
    } else if sublist != 0 && sublist < (*work).size {
        parse_inline(inter, rndr, (*work).data, sublist);
        parse_block(inter, rndr, (*work).data.offset(sublist as isize),
                    (*work).size.wrapping_sub(sublist));
    } else { parse_inline(inter, rndr, (*work).data, (*work).size); }
    /* intermediate render of inline li */
    /* render of li itself */
    if (*rndr).cb.listitem.is_some() {
        (*rndr).cb.listitem.expect("non-null function pointer")(ob, inter,
                                                                *flags,
                                                                (*rndr).opaque);
    }
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    return beg;
}
/* parse_list -- parsing ordered or unordered list block */
unsafe extern "C" fn parse_list(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                mut data: *mut uint8_t, mut size: size_t,
                                mut flags: std::os::raw::c_int) -> size_t {
    let mut work: *mut buf = 0 as *mut buf;
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut j: size_t = 0;
    work = rndr_newbuf(rndr, 0 as std::os::raw::c_int);
    while i < size {
        j =
            parse_listitem(work, rndr, data.offset(i as isize),
                           size.wrapping_sub(i), &mut flags);
        i = (i as std::os::raw::c_ulong).wrapping_add(j) as size_t as size_t;
        if j == 0 || flags & 8 as std::os::raw::c_int != 0 { break ; }
    }
    if (*rndr).cb.list.is_some() {
        (*rndr).cb.list.expect("non-null function pointer")(ob, work, flags,
                                                            (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as std::os::raw::c_int);
    return i;
}
/* parse_atxheader -- parsing of atx-style headers */
unsafe extern "C" fn parse_atxheader(mut ob: *mut buf,
                                     mut rndr: *mut sd_markdown,
                                     mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut level: size_t = 0 as std::os::raw::c_int as size_t;
    let mut i: size_t = 0;
    let mut end: size_t = 0;
    let mut skip: size_t = 0;
    while level < size && level < 6 as std::os::raw::c_int as std::os::raw::c_ulong &&
              *data.offset(level as isize) as std::os::raw::c_int == '#' as i32 {
        level = level.wrapping_add(1)
    }
    i = level;
    while i < size && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    end = i;
    while end < size &&
              *data.offset(end as isize) as std::os::raw::c_int != '\n' as i32 {
        end = end.wrapping_add(1)
    }
    skip = end;
    while end != 0 &&
              *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                               as isize) as std::os::raw::c_int == '#' as i32 {
        end = end.wrapping_sub(1)
    }
    while end != 0 &&
              *data.offset(end.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                               as isize) as std::os::raw::c_int == ' ' as i32 {
        end = end.wrapping_sub(1)
    }
    if end > i {
        let mut work: *mut buf = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
        parse_inline(work, rndr, data.offset(i as isize),
                     end.wrapping_sub(i));
        if (*rndr).cb.header.is_some() {
            (*rndr).cb.header.expect("non-null function pointer")(ob, work,
                                                                  level as
                                                                      std::os::raw::c_int,
                                                                  (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    }
    return skip;
}
/* htmlblock_end -- checking end of HTML block : </tag>[ \t]*\n[ \t*]\n */
/*	returns the length on match, 0 otherwise */
unsafe extern "C" fn htmlblock_end_tag(mut tag: *const std::os::raw::c_char,
                                       mut tag_len: size_t,
                                       mut rndr: *mut sd_markdown,
                                       mut data: *mut uint8_t,
                                       mut size: size_t) -> size_t {
    let mut i: size_t = 0;
    let mut w: size_t = 0;
    /* checking if tag is a match */
    if tag_len.wrapping_add(3 as std::os::raw::c_int as std::os::raw::c_ulong) >= size ||
           strncasecmp((data as
                            *mut std::os::raw::c_char).offset(2 as std::os::raw::c_int as
                                                          isize), tag,
                       tag_len) != 0 as std::os::raw::c_int ||
           *data.offset(tag_len.wrapping_add(2 as std::os::raw::c_int as
                                                 std::os::raw::c_ulong) as isize) as
               std::os::raw::c_int != '>' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    /* checking white lines */
    i =
        tag_len.wrapping_add(3 as std::os::raw::c_int as
                                 std::os::raw::c_ulong); /* non-blank after tag */
    w = 0 as std::os::raw::c_int as size_t;
    if i < size &&
           {
               w = is_empty(data.offset(i as isize), size.wrapping_sub(i));
               (w) == 0 as std::os::raw::c_int as std::os::raw::c_ulong
           } {
        return 0 as std::os::raw::c_int as size_t
    }
    i = (i as std::os::raw::c_ulong).wrapping_add(w) as size_t as size_t;
    w = 0 as std::os::raw::c_int as size_t;
    if i < size {
        w = is_empty(data.offset(i as isize), size.wrapping_sub(i))
    }
    return i.wrapping_add(w);
}
unsafe extern "C" fn htmlblock_end(mut curtag: *const std::os::raw::c_char,
                                   mut rndr: *mut sd_markdown,
                                   mut data: *mut uint8_t, mut size: size_t,
                                   mut start_of_line: std::os::raw::c_int) -> size_t {
    let mut tag_size: size_t = strlen(curtag);
    let mut i: size_t = 1 as std::os::raw::c_int as size_t;
    let mut end_tag: size_t = 0;
    let mut block_lines: std::os::raw::c_int = 0 as std::os::raw::c_int;
    while i < size {
        i = i.wrapping_add(1);
        while i < size &&
                  !(*data.offset(i.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
                        as std::os::raw::c_int == '<' as i32 &&
                        *data.offset(i as isize) as std::os::raw::c_int == '/' as i32)
              {
            if *data.offset(i as isize) as std::os::raw::c_int == '\n' as i32 {
                block_lines += 1
            }
            i = i.wrapping_add(1)
        }
        /* If we are only looking for unindented tags, skip the tag
		 * if it doesn't follow a newline.
		 *
		 * The only exception to this is if the tag is still on the
		 * initial line; in that case it still counts as a closing
		 * tag
		 */
        if start_of_line != 0 && block_lines > 0 as std::os::raw::c_int &&
               *data.offset(i.wrapping_sub(2 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int != '\n' as i32 {
            continue ;
        }
        if i.wrapping_add(2 as std::os::raw::c_int as
                              std::os::raw::c_ulong).wrapping_add(tag_size) >= size {
            break ;
        }
        end_tag =
            htmlblock_end_tag(curtag, tag_size, rndr,
                              data.offset(i as
                                              isize).offset(-(1 as std::os::raw::c_int
                                                                  as isize)),
                              size.wrapping_sub(i).wrapping_add(1 as
                                                                    std::os::raw::c_int
                                                                    as
                                                                    std::os::raw::c_ulong));
        if end_tag != 0 {
            return i.wrapping_add(end_tag).wrapping_sub(1 as std::os::raw::c_int as
                                                            std::os::raw::c_ulong)
        }
    }
    return 0 as std::os::raw::c_int as size_t;
}
/* parse_htmlblock -- parsing of inline HTML block */
unsafe extern "C" fn parse_htmlblock(mut ob: *mut buf,
                                     mut rndr: *mut sd_markdown,
                                     mut data: *mut uint8_t, mut size: size_t,
                                     mut do_render: std::os::raw::c_int) -> size_t {
    let mut i: size_t = 0;
    let mut j: size_t = 0 as std::os::raw::c_int as size_t;
    let mut tag_end: size_t = 0;
    let mut curtag: *const std::os::raw::c_char = 0 as *const std::os::raw::c_char;
    let mut work: buf =
        {
            let mut init =
                buf{data: data,
                    size: 0 as std::os::raw::c_int as size_t,
                    asize: 0 as std::os::raw::c_int as size_t,
                    unit: 0 as std::os::raw::c_int as size_t,};
            init
        };
    /* identification of the opening tag */
    if size < 2 as std::os::raw::c_int as std::os::raw::c_ulong ||
           *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
               '<' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    i = 1 as std::os::raw::c_int as size_t;
    while i < size && *data.offset(i as isize) as std::os::raw::c_int != '>' as i32 &&
              *data.offset(i as isize) as std::os::raw::c_int != ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < size {
        curtag =
            find_block_tag((data as
                                *mut std::os::raw::c_char).offset(1 as std::os::raw::c_int as
                                                              isize),
                           (i as std::os::raw::c_int - 1 as std::os::raw::c_int) as
                               std::os::raw::c_uint)
    }
    /* handling of special cases */
    if curtag.is_null() {
        /* HTML comment, laxist form */
        if size > 5 as std::os::raw::c_int as std::os::raw::c_ulong &&
               *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                   '!' as i32 &&
               *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                   '-' as i32 &&
               *data.offset(3 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                   '-' as i32 {
            i = 5 as std::os::raw::c_int as size_t;
            while i < size &&
                      !(*data.offset(i.wrapping_sub(2 as std::os::raw::c_int as
                                                        std::os::raw::c_ulong) as
                                         isize) as std::os::raw::c_int == '-' as i32
                            &&
                            *data.offset(i.wrapping_sub(1 as std::os::raw::c_int as
                                                            std::os::raw::c_ulong) as
                                             isize) as std::os::raw::c_int ==
                                '-' as i32 &&
                            *data.offset(i as isize) as std::os::raw::c_int ==
                                '>' as i32) {
                i = i.wrapping_add(1)
            }
            i = i.wrapping_add(1);
            if i < size {
                j = is_empty(data.offset(i as isize), size.wrapping_sub(i))
            }
            if j != 0 {
                work.size = i.wrapping_add(j);
                if do_render != 0 && (*rndr).cb.blockhtml.is_some() {
                    (*rndr).cb.blockhtml.expect("non-null function pointer")(ob,
                                                                             &mut work,
                                                                             (*rndr).opaque);
                }
                return work.size
            }
        }
        /* HR, which is the only self-closing block tag considered */
        if size > 4 as std::os::raw::c_int as std::os::raw::c_ulong &&
               (*data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                    'h' as i32 ||
                    *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                        'H' as i32) &&
               (*data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                    'r' as i32 ||
                    *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                        'R' as i32) {
            i = 3 as std::os::raw::c_int as size_t;
            while i < size &&
                      *data.offset(i as isize) as std::os::raw::c_int != '>' as i32 {
                i = i.wrapping_add(1)
            }
            if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < size {
                i = i.wrapping_add(1);
                j = is_empty(data.offset(i as isize), size.wrapping_sub(i));
                if j != 0 {
                    work.size = i.wrapping_add(j);
                    if do_render != 0 && (*rndr).cb.blockhtml.is_some() {
                        (*rndr).cb.blockhtml.expect("non-null function pointer")(ob,
                                                                                 &mut work,
                                                                                 (*rndr).opaque);
                    }
                    return work.size
                }
            }
        }
        /* no special case recognised */
        return 0 as std::os::raw::c_int as size_t
    }
    /* looking for an unindented matching closing tag */
	/*	followed by a blank line */
    tag_end = htmlblock_end(curtag, rndr, data, size, 1 as std::os::raw::c_int);
    /* if not found, trying a second pass looking for indented match */
	/* but not if tag is "ins" or "del" (following original Markdown.pl) */
    if tag_end == 0 &&
           strcmp(curtag, b"ins\x00" as *const u8 as *const std::os::raw::c_char) !=
               0 as std::os::raw::c_int &&
           strcmp(curtag, b"del\x00" as *const u8 as *const std::os::raw::c_char) !=
               0 as std::os::raw::c_int {
        tag_end = htmlblock_end(curtag, rndr, data, size, 0 as std::os::raw::c_int)
    }
    if tag_end == 0 { return 0 as std::os::raw::c_int as size_t }
    /* the end of the block has been found */
    work.size = tag_end;
    if do_render != 0 && (*rndr).cb.blockhtml.is_some() {
        (*rndr).cb.blockhtml.expect("non-null function pointer")(ob,
                                                                 &mut work,
                                                                 (*rndr).opaque);
    }
    return tag_end;
}
unsafe extern "C" fn parse_table_row(mut ob: *mut buf,
                                     mut rndr: *mut sd_markdown,
                                     mut data: *mut uint8_t, mut size: size_t,
                                     mut columns: size_t,
                                     mut col_data: *mut std::os::raw::c_int,
                                     mut header_flag: std::os::raw::c_int) {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut col: size_t = 0;
    let mut cols_left: size_t = 0;
    let mut row_work: *mut buf = 0 as *mut buf;
    if (*rndr).cb.table_cell.is_none() || (*rndr).cb.table_row.is_none() {
        return
    }
    row_work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == '|' as i32 {
        i = i.wrapping_add(1)
    }
    col = 0 as std::os::raw::c_int as size_t;
    while col < columns && i < size {
        let mut cell_start: size_t = 0;
        let mut cell_end: size_t = 0;
        let mut cell_work: *mut buf = 0 as *mut buf;
        cell_work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
        while i < size &&
                  _isspace(*data.offset(i as isize) as std::os::raw::c_int) != 0 {
            i = i.wrapping_add(1)
        }
        cell_start = i;
        while i < size &&
                  *data.offset(i as isize) as std::os::raw::c_int != '|' as i32 {
            i = i.wrapping_add(1)
        }
        cell_end = i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong);
        while cell_end > cell_start &&
                  _isspace(*data.offset(cell_end as isize) as std::os::raw::c_int) !=
                      0 {
            cell_end = cell_end.wrapping_sub(1)
        }
        parse_inline(cell_work, rndr, data.offset(cell_start as isize),
                     (1 as std::os::raw::c_int as
                          std::os::raw::c_ulong).wrapping_add(cell_end).wrapping_sub(cell_start));
        (*rndr).cb.table_cell.expect("non-null function pointer")(row_work,
                                                                  cell_work,
                                                                  *col_data.offset(col
                                                                                       as
                                                                                       isize)
                                                                      |
                                                                      header_flag,
                                                                  (*rndr).opaque,
                                                                  0 as
                                                                      std::os::raw::c_int);
        rndr_popbuf(rndr, 1 as std::os::raw::c_int);
        i = i.wrapping_add(1);
        col = col.wrapping_add(1)
    }
    cols_left = columns.wrapping_sub(col);
    if cols_left > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        let mut empty_cell: buf =
            {
                let mut init =
                    buf{data: 0 as *mut uint8_t,
                        size: 0 as std::os::raw::c_int as size_t,
                        asize: 0 as std::os::raw::c_int as size_t,
                        unit: 0 as std::os::raw::c_int as size_t,};
                init
            };
        (*rndr).cb.table_cell.expect("non-null function pointer")(row_work,
                                                                  &mut empty_cell,
                                                                  *col_data.offset(col
                                                                                       as
                                                                                       isize)
                                                                      |
                                                                      header_flag,
                                                                  (*rndr).opaque,
                                                                  cols_left as
                                                                      std::os::raw::c_int);
    }
    (*rndr).cb.table_row.expect("non-null function pointer")(ob, row_work,
                                                             (*rndr).opaque);
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
}
unsafe extern "C" fn parse_table_header(mut ob: *mut buf,
                                        mut rndr: *mut sd_markdown,
                                        mut data: *mut uint8_t,
                                        mut size: size_t,
                                        mut columns: *mut size_t,
                                        mut column_data:
                                            *mut *mut std::os::raw::c_int) -> size_t {
    let mut pipes: std::os::raw::c_int = 0;
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut col: size_t = 0;
    let mut header_end: size_t = 0;
    let mut under_end: size_t = 0;
    pipes = 0 as std::os::raw::c_int;
    while i < size && *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 {
        let fresh2 = i;
        i = i.wrapping_add(1);
        if *data.offset(fresh2 as isize) as std::os::raw::c_int == '|' as i32 {
            pipes += 1
        }
    }
    if i == size || pipes == 0 as std::os::raw::c_int {
        return 0 as std::os::raw::c_int as size_t
    }
    header_end = i;
    while header_end > 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
              _isspace(*data.offset(header_end.wrapping_sub(1 as std::os::raw::c_int
                                                                as
                                                                std::os::raw::c_ulong)
                                        as isize) as std::os::raw::c_int) != 0 {
        header_end = header_end.wrapping_sub(1)
    }
    if *data.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int == '|' as i32 {
        pipes -= 1
    }
    if header_end != 0 &&
           *data.offset(header_end.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) as isize)
               as std::os::raw::c_int == '|' as i32 {
        pipes -= 1
    }
    if (pipes + 1 as std::os::raw::c_int) as std::os::raw::c_ulong > (*rndr).max_table_cols {
        return 0 as std::os::raw::c_int as size_t
    }
    *columns = (pipes + 1 as std::os::raw::c_int) as size_t;
    *column_data =
        calloc(*columns,
               ::std::mem::size_of::<std::os::raw::c_int>() as std::os::raw::c_ulong) as
            *mut std::os::raw::c_int;
    /* Parse the header underline */
    i = i.wrapping_add(1);
    if i < size && *data.offset(i as isize) as std::os::raw::c_int == '|' as i32 {
        i = i.wrapping_add(1)
    }
    under_end = i;
    while under_end < size &&
              *data.offset(under_end as isize) as std::os::raw::c_int != '\n' as i32 {
        under_end = under_end.wrapping_add(1)
    }
    col = 0 as std::os::raw::c_int as size_t;
    while col < *columns && i < under_end {
        let mut dashes: size_t = 0 as std::os::raw::c_int as size_t;
        while i < under_end &&
                  *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
            i = i.wrapping_add(1)
        }
        if *data.offset(i as isize) as std::os::raw::c_int == ':' as i32 {
            i = i.wrapping_add(1);
            *(*column_data).offset(col as isize) |=
                MKD_TABLE_ALIGN_L as std::os::raw::c_int;
            dashes = dashes.wrapping_add(1)
        }
        while i < under_end &&
                  *data.offset(i as isize) as std::os::raw::c_int == '-' as i32 {
            i = i.wrapping_add(1);
            dashes = dashes.wrapping_add(1)
        }
        if i < under_end &&
               *data.offset(i as isize) as std::os::raw::c_int == ':' as i32 {
            i = i.wrapping_add(1);
            *(*column_data).offset(col as isize) |=
                MKD_TABLE_ALIGN_R as std::os::raw::c_int;
            dashes = dashes.wrapping_add(1)
        }
        while i < under_end &&
                  *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
            i = i.wrapping_add(1)
        }
        if i < under_end &&
               *data.offset(i as isize) as std::os::raw::c_int != '|' as i32 {
            break ;
        }
        if dashes < 1 as std::os::raw::c_int as std::os::raw::c_ulong { break ; }
        i = i.wrapping_add(1);
        col = col.wrapping_add(1)
    }
    if col < *columns { return 0 as std::os::raw::c_int as size_t }
    parse_table_row(ob, rndr, data, header_end, *columns, *column_data,
                    MKD_TABLE_HEADER as std::os::raw::c_int);
    return under_end.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
}
unsafe extern "C" fn parse_table(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t, mut size: size_t)
 -> size_t {
    let mut i: size_t = 0;
    let mut header_work: *mut buf = 0 as *mut buf;
    let mut body_work: *mut buf = 0 as *mut buf;
    let mut columns: size_t = 0;
    let mut col_data: *mut std::os::raw::c_int = 0 as *mut std::os::raw::c_int;
    header_work = rndr_newbuf(rndr, 1 as std::os::raw::c_int);
    body_work = rndr_newbuf(rndr, 0 as std::os::raw::c_int);
    i =
        parse_table_header(header_work, rndr, data, size, &mut columns,
                           &mut col_data);
    if i > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        while i < size {
            let mut row_start: size_t = 0;
            let mut pipes: std::os::raw::c_int = 0 as std::os::raw::c_int;
            row_start = i;
            while i < size &&
                      *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 {
                let fresh3 = i;
                i = i.wrapping_add(1);
                if *data.offset(fresh3 as isize) as std::os::raw::c_int == '|' as i32
                   {
                    pipes += 1
                }
            }
            if pipes == 0 as std::os::raw::c_int || i == size {
                i = row_start;
                break ;
            } else {
                parse_table_row(body_work, rndr,
                                data.offset(row_start as isize),
                                i.wrapping_sub(row_start), columns, col_data,
                                0 as std::os::raw::c_int);
                i = i.wrapping_add(1)
            }
        }
        if (*rndr).cb.table.is_some() {
            (*rndr).cb.table.expect("non-null function pointer")(ob,
                                                                 header_work,
                                                                 body_work,
                                                                 (*rndr).opaque);
        }
    }
    free(col_data as *mut std::os::raw::c_void);
    rndr_popbuf(rndr, 1 as std::os::raw::c_int);
    rndr_popbuf(rndr, 0 as std::os::raw::c_int);
    return i;
}
/* parse_block -- parsing of one block, returning next uint8_t to parse */
/* parse_block -- parsing of one block, returning next uint8_t to parse */
unsafe extern "C" fn parse_block(mut ob: *mut buf, mut rndr: *mut sd_markdown,
                                 mut data: *mut uint8_t, mut size: size_t) {
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let mut i: size_t = 0;
    let mut txt_data: *mut uint8_t = 0 as *mut uint8_t;
    beg = 0 as std::os::raw::c_int as size_t;
    if (*rndr).work_bufs[1 as std::os::raw::c_int as
                             usize].size.wrapping_add((*rndr).work_bufs[0 as
                                                                            std::os::raw::c_int
                                                                            as
                                                                            usize].size)
           > (*rndr).max_nesting {
        return
    }
    while beg < size {
        txt_data = data.offset(beg as isize);
        end = size.wrapping_sub(beg);
        if is_atxheader(rndr, txt_data, end) != 0 {
            beg =
                (beg as
                     std::os::raw::c_ulong).wrapping_add(parse_atxheader(ob, rndr,
                                                                 txt_data,
                                                                 end)) as
                    size_t as size_t
        } else if *data.offset(beg as isize) as std::os::raw::c_int == '<' as i32 &&
                      (*rndr).cb.blockhtml.is_some() &&
                      {
                          i =
                              parse_htmlblock(ob, rndr, txt_data, end,
                                              1 as std::os::raw::c_int);
                          (i) != 0 as std::os::raw::c_int as std::os::raw::c_ulong
                      } {
            beg = (beg as std::os::raw::c_ulong).wrapping_add(i) as size_t as size_t
        } else {
            i = is_empty(txt_data, end);
            if i != 0 as std::os::raw::c_int as std::os::raw::c_ulong {
                beg =
                    (beg as std::os::raw::c_ulong).wrapping_add(i) as size_t as size_t
            } else if is_hrule(txt_data, end) != 0 {
                if (*rndr).cb.hrule.is_some() {
                    (*rndr).cb.hrule.expect("non-null function pointer")(ob,
                                                                         (*rndr).opaque);
                }
                while beg < size &&
                          *data.offset(beg as isize) as std::os::raw::c_int !=
                              '\n' as i32 {
                    beg = beg.wrapping_add(1)
                }
                beg = beg.wrapping_add(1)
            } else if (*rndr).ext_flags &
                          MKDEXT_FENCED_CODE as std::os::raw::c_int as std::os::raw::c_uint !=
                          0 as std::os::raw::c_int as std::os::raw::c_uint &&
                          {
                              i = parse_fencedcode(ob, rndr, txt_data, end);
                              (i) != 0 as std::os::raw::c_int as std::os::raw::c_ulong
                          } {
                beg =
                    (beg as std::os::raw::c_ulong).wrapping_add(i) as size_t as size_t
            } else if (*rndr).ext_flags &
                          MKDEXT_TABLES as std::os::raw::c_int as std::os::raw::c_uint !=
                          0 as std::os::raw::c_int as std::os::raw::c_uint &&
                          {
                              i = parse_table(ob, rndr, txt_data, end);
                              (i) != 0 as std::os::raw::c_int as std::os::raw::c_ulong
                          } {
                beg =
                    (beg as std::os::raw::c_ulong).wrapping_add(i) as size_t as size_t
            } else if prefix_quote(txt_data, end) != 0 {
                beg =
                    (beg as
                         std::os::raw::c_ulong).wrapping_add(parse_blockquote(ob,
                                                                      rndr,
                                                                      txt_data,
                                                                      end)) as
                        size_t as size_t
            } else if prefix_blockspoiler(txt_data, end) != 0 {
                beg =
                    (beg as
                         std::os::raw::c_ulong).wrapping_add(parse_blockspoiler(ob,
                                                                        rndr,
                                                                        txt_data,
                                                                        end))
                        as size_t as size_t
            } else if prefix_code(txt_data, end) != 0 {
                beg =
                    (beg as
                         std::os::raw::c_ulong).wrapping_add(parse_blockcode(ob, rndr,
                                                                     txt_data,
                                                                     end)) as
                        size_t as size_t
            } else if prefix_uli(txt_data, end) != 0 {
                beg =
                    (beg as
                         std::os::raw::c_ulong).wrapping_add(parse_list(ob, rndr,
                                                                txt_data, end,
                                                                0 as
                                                                    std::os::raw::c_int))
                        as size_t as size_t
            } else if prefix_oli(txt_data, end) != 0 {
                beg =
                    (beg as
                         std::os::raw::c_ulong).wrapping_add(parse_list(ob, rndr,
                                                                txt_data, end,
                                                                1 as
                                                                    std::os::raw::c_int))
                        as size_t as size_t
            } else {
                beg =
                    (beg as
                         std::os::raw::c_ulong).wrapping_add(parse_paragraph(ob, rndr,
                                                                     txt_data,
                                                                     end)) as
                        size_t as size_t
            }
        }
    };
}
/* ********************
 * REFERENCE PARSING *
 *********************/
/* is_ref -- returns whether a line is a reference or not */
unsafe extern "C" fn is_ref(mut data: *const uint8_t, mut beg: size_t,
                            mut end: size_t, mut last: *mut size_t,
                            mut refs: *mut *mut link_ref) -> std::os::raw::c_int {
    /*	int n; */
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut id_offset: size_t = 0;
    let mut id_end: size_t = 0;
    let mut link_offset: size_t = 0;
    let mut link_end: size_t = 0;
    let mut title_offset: size_t = 0;
    let mut title_end: size_t = 0;
    let mut line_end: size_t = 0;
    /* up to 3 optional leading spaces */
    if beg.wrapping_add(3 as std::os::raw::c_int as std::os::raw::c_ulong) >= end {
        return 0 as std::os::raw::c_int
    }
    if *data.offset(beg as isize) as std::os::raw::c_int == ' ' as i32 {
        i = 1 as std::os::raw::c_int as size_t;
        if *data.offset(beg.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
                            isize) as std::os::raw::c_int == ' ' as i32 {
            i = 2 as std::os::raw::c_int as size_t;
            if *data.offset(beg.wrapping_add(2 as std::os::raw::c_int as
                                                 std::os::raw::c_ulong) as isize) as
                   std::os::raw::c_int == ' ' as i32 {
                i = 3 as std::os::raw::c_int as size_t;
                if *data.offset(beg.wrapping_add(3 as std::os::raw::c_int as
                                                     std::os::raw::c_ulong) as isize)
                       as std::os::raw::c_int == ' ' as i32 {
                    return 0 as std::os::raw::c_int
                }
            }
        }
    }
    i = (i as std::os::raw::c_ulong).wrapping_add(beg) as size_t as size_t;
    /* id part: anything but a newline between brackets */
    if *data.offset(i as isize) as std::os::raw::c_int != '[' as i32 {
        return 0 as std::os::raw::c_int
    }
    i = i.wrapping_add(1);
    id_offset = i;
    while i < end && *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 &&
              *data.offset(i as isize) as std::os::raw::c_int != '\r' as i32 &&
              *data.offset(i as isize) as std::os::raw::c_int != ']' as i32 {
        i = i.wrapping_add(1)
    }
    if i >= end || *data.offset(i as isize) as std::os::raw::c_int != ']' as i32 {
        return 0 as std::os::raw::c_int
    }
    id_end = i;
    /* spacer: colon (space | tab)* newline? (space | tab)* */
    i = i.wrapping_add(1);
    if i >= end || *data.offset(i as isize) as std::os::raw::c_int != ':' as i32 {
        return 0 as std::os::raw::c_int
    }
    i = i.wrapping_add(1);
    while i < end && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < end &&
           (*data.offset(i as isize) as std::os::raw::c_int == '\n' as i32 ||
                *data.offset(i as isize) as std::os::raw::c_int == '\r' as i32) {
        i = i.wrapping_add(1);
        if i < end && *data.offset(i as isize) as std::os::raw::c_int == '\r' as i32
               &&
               *data.offset(i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                                as isize) as std::os::raw::c_int == '\n' as i32 {
            i = i.wrapping_add(1)
        }
    }
    while i < end && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i >= end { return 0 as std::os::raw::c_int }
    /* link: whitespace-free sequence, optionally between angle brackets */
    if *data.offset(i as isize) as std::os::raw::c_int == '<' as i32 {
        i = i.wrapping_add(1)
    }
    link_offset = i;
    while i < end && *data.offset(i as isize) as std::os::raw::c_int != ' ' as i32 &&
              *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 &&
              *data.offset(i as isize) as std::os::raw::c_int != '\r' as i32 {
        i = i.wrapping_add(1)
    }
    if *data.offset(i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
                        isize) as std::os::raw::c_int == '>' as i32 {
        link_end = i.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
    } else { link_end = i }
    /* optional spacer: (space | tab)* (newline | '\'' | '"' | '(' ) */
    while i < end && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32 {
        i = i.wrapping_add(1)
    }
    if i < end && *data.offset(i as isize) as std::os::raw::c_int != '\n' as i32 &&
           *data.offset(i as isize) as std::os::raw::c_int != '\r' as i32 &&
           *data.offset(i as isize) as std::os::raw::c_int != '\'' as i32 &&
           *data.offset(i as isize) as std::os::raw::c_int != '\"' as i32 &&
           *data.offset(i as isize) as std::os::raw::c_int != '(' as i32 {
        return 0 as std::os::raw::c_int
    }
    line_end = 0 as std::os::raw::c_int as size_t;
    /* computing end-of-line */
    if i >= end || *data.offset(i as isize) as std::os::raw::c_int == '\r' as i32 ||
           *data.offset(i as isize) as std::os::raw::c_int == '\n' as i32 {
        line_end = i
    }
    if i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) < end &&
           *data.offset(i as isize) as std::os::raw::c_int == '\n' as i32 &&
           *data.offset(i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
                            isize) as std::os::raw::c_int == '\r' as i32 {
        line_end = i.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong)
    }
    /* optional (space|tab)* spacer after a newline */
    if line_end != 0 {
        i = line_end.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong);
        while i < end && *data.offset(i as isize) as std::os::raw::c_int == ' ' as i32
              {
            i = i.wrapping_add(1)
        }
    }
    /* optional title: any non-newline sequence enclosed in '"()
					alone on its line */
    title_end = 0 as std::os::raw::c_int as size_t;
    title_offset = title_end;
    if i + 1 < end && (unsafe { *data.offset(i as isize) } == b'\'' || unsafe { *data.offset(i as isize) } == b'"' || unsafe { *data.offset(i as isize) } == b'(') {
    i += 1;
    title_offset = i;

    // looking for EOL
    while i < end && (unsafe { *data.offset(i as isize) } != b'\n' && unsafe { *data.offset(i as isize) } != b'\r') {
        i += 1;
    }

    if i + 1 < end && unsafe { *data.offset(i as isize) } == b'\n' && unsafe { *data.offset(i.wrapping_add(1) as isize) } == b'\r' {
        title_end = i + 1;
    } else {
        title_end = i;
    }

    // stepping back
    i = i.saturating_sub(1); // garbage after the link empty link
    while i > title_offset && unsafe { *data.offset(i as isize) } == b' ' {
        i = i.saturating_sub(1);
    }

    if i > title_offset && (unsafe { *data.offset(i as isize) } == b'\'' || unsafe { *data.offset(i as isize) } == b'"' || unsafe { *data.offset(i as isize) } == b')') {
        line_end = title_end;
        title_end = i;
    }
}

if line_end == 0 || link_end == link_offset {
    return 0;
}

// a valid ref has been found, filling-in return structures
if let Some(last_ref) = last.as_mut() {
    *last_ref = line_end;
}

if let Some(refs_ref) = refs.as_mut() {
    let ref_0 = add_link_ref(refs_ref, data.offset(id_offset as isize), id_end.wrapping_sub(id_offset));
    if ref_0.is_null() {
        return 0;
    }
    (*ref_0).link = bufnew(link_end.wrapping_sub(link_offset));
    bufput((*ref_0).link, data.offset(link_offset as isize) as *const std::os::raw::c_void, link_end.wrapping_sub(link_offset));
    
    if title_end > title_offset {
        (*ref_0).title = bufnew(title_end.wrapping_sub(title_offset));
        bufput((*ref_0).title, data.offset(title_offset as isize) as *const std::os::raw::c_void, title_end.wrapping_sub(title_offset));
    }
}

return 1;

}
unsafe extern "C" fn expand_tabs(mut ob: *mut buf, mut line: *const uint8_t,
                                 mut size: size_t) {
    let mut i: size_t = 0 as std::os::raw::c_int as size_t;
    let mut tab: size_t = 0 as std::os::raw::c_int as size_t;
    while i < size {
        let mut org: size_t = i;
        while i < size &&
                  *line.offset(i as isize) as std::os::raw::c_int != '\t' as i32 {
            i = i.wrapping_add(1);
            tab = tab.wrapping_add(1)
        }
        if i > org {
            bufput(ob, line.offset(org as isize) as *const std::os::raw::c_void,
                   i.wrapping_sub(org));
        }
        if i >= size { break ; }
        loop  {
            bufputc(ob, ' ' as i32);
            tab = tab.wrapping_add(1);
            if !(tab.wrapping_rem(4 as std::os::raw::c_int as std::os::raw::c_ulong) != 0) {
                break ;
            }
        }
        i = i.wrapping_add(1)
    };
}
/* <li> containing block data */
/* *********************
 * EXPORTED FUNCTIONS *
 **********************/
/* *********************
 * EXPORTED FUNCTIONS *
 **********************/
#[no_mangle]
pub unsafe extern "C" fn sd_markdown_new(mut extensions: std::os::raw::c_uint,
                                         mut max_nesting: size_t,
                                         mut max_table_cols: size_t,
                                         mut callbacks: *const sd_callbacks,
                                         mut opaque: *mut std::os::raw::c_void)
 -> *mut sd_markdown {
    let mut md: *mut sd_markdown = 0 as *mut sd_markdown;
    md =
        malloc(::std::mem::size_of::<sd_markdown>() as std::os::raw::c_ulong) as
            *mut sd_markdown;
    if md.is_null() { return 0 as *mut sd_markdown }
    memcpy(&mut (*md).cb as *mut sd_callbacks as *mut std::os::raw::c_void,
           callbacks as *const std::os::raw::c_void,
           ::std::mem::size_of::<sd_callbacks>() as std::os::raw::c_ulong);
    let work_buf = &mut (*md).work_bufs[0];
stack_init(work_buf, 4);
    let work_buf = &mut (*md).work_bufs[1];
stack_init(work_buf, 8);
    memset((*md).active_char.as_mut_ptr() as *mut std::os::raw::c_void,
           0 as std::os::raw::c_int, 256 as std::os::raw::c_int as std::os::raw::c_ulong);
    if (*md).cb.emphasis.is_some() || (*md).cb.double_emphasis.is_some() ||
           (*md).cb.triple_emphasis.is_some() {
        (*md).active_char['*' as i32 as usize] =
            MD_CHAR_EMPHASIS as std::os::raw::c_int as uint8_t;
        (*md).active_char['_' as i32 as usize] =
            MD_CHAR_EMPHASIS as std::os::raw::c_int as uint8_t;
        (*md).active_char['>' as i32 as usize] =
            MD_CHAR_EMPHASIS as std::os::raw::c_int as uint8_t;
        if extensions & MKDEXT_STRIKETHROUGH as std::os::raw::c_int as std::os::raw::c_uint !=
               0 {
            (*md).active_char['~' as i32 as usize] =
                MD_CHAR_EMPHASIS as std::os::raw::c_int as uint8_t
        }
    }
    if (*md).cb.codespan.is_some() {
        (*md).active_char['`' as i32 as usize] =
            MD_CHAR_CODESPAN as std::os::raw::c_int as uint8_t
    }
    if (*md).cb.linebreak.is_some() {
        (*md).active_char['\n' as i32 as usize] =
            MD_CHAR_LINEBREAK as std::os::raw::c_int as uint8_t
    }
    if (*md).cb.image.is_some() || (*md).cb.link.is_some() {
        (*md).active_char['[' as i32 as usize] =
            MD_CHAR_LINK as std::os::raw::c_int as uint8_t
    }
    (*md).active_char['<' as i32 as usize] =
        MD_CHAR_LANGLE as std::os::raw::c_int as uint8_t;
    (*md).active_char['\\' as i32 as usize] =
        MD_CHAR_ESCAPE as std::os::raw::c_int as uint8_t;
    (*md).active_char['&' as i32 as usize] =
        MD_CHAR_ENTITITY as std::os::raw::c_int as uint8_t;
    if extensions & MKDEXT_AUTOLINK as std::os::raw::c_int as std::os::raw::c_uint != 0 {
        if extensions &
               MKDEXT_NO_EMAIL_AUTOLINK as std::os::raw::c_int as std::os::raw::c_uint == 0 {
            (*md).active_char['@' as i32 as usize] =
                MD_CHAR_AUTOLINK_EMAIL as std::os::raw::c_int as uint8_t
        }
        (*md).active_char[':' as i32 as usize] =
            MD_CHAR_AUTOLINK_URL as std::os::raw::c_int as uint8_t;
        (*md).active_char['w' as i32 as usize] =
            MD_CHAR_AUTOLINK_WWW as std::os::raw::c_int as uint8_t;
        (*md).active_char['/' as i32 as usize] =
            MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME as std::os::raw::c_int as uint8_t
    }
    if extensions & MKDEXT_SUPERSCRIPT as std::os::raw::c_int as std::os::raw::c_uint != 0 {
        (*md).active_char['^' as i32 as usize] =
            MD_CHAR_SUPERSCRIPT as std::os::raw::c_int as uint8_t
    }
    /* Extension data */
    (*md).ext_flags = extensions;
    (*md).opaque = opaque;
    (*md).max_nesting = max_nesting;
    (*md).max_table_cols = max_table_cols;
    (*md).in_link_body = 0 as std::os::raw::c_int;
    return md;
}
#[no_mangle]
pub unsafe extern "C" fn sd_markdown_render(mut ob: *mut buf,
                                            mut document: *const uint8_t,
                                            mut doc_size: size_t,
                                            mut md: *mut sd_markdown) {
    static mut UTF8_BOM: [std::os::raw::c_char; 3] =
        [0xef as std::os::raw::c_int as std::os::raw::c_char,
         0xbb as std::os::raw::c_int as std::os::raw::c_char,
         0xbf as std::os::raw::c_int as std::os::raw::c_char];
    let mut text: *mut buf = 0 as *mut buf;
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let text_buf = bufnew(64);
text = text_buf;
    if text.is_null() { return }
    /* Preallocate enough space for our buffer to avoid expanding while copying */
    bufgrow(text, doc_size);
    /* reset the references table */
    memset(&mut (*md).refs as *mut [*mut link_ref; 8] as *mut std::os::raw::c_void,
           0 as std::os::raw::c_int,
           (8 as std::os::raw::c_int as
                std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<*mut std::os::raw::c_void>()
                                                as std::os::raw::c_ulong));
    /* first pass: looking for references, copying everything else */
    beg = 0 as std::os::raw::c_int as size_t;
    /* Skip a possible UTF-8 BOM, even though the Unicode standard
	 * discourages having these in UTF-8 documents */
    if doc_size >= 3 as std::os::raw::c_int as std::os::raw::c_ulong &&
           memcmp(document as *const std::os::raw::c_void,
                  UTF8_BOM.as_ptr() as *const std::os::raw::c_void,
                  3 as std::os::raw::c_int as std::os::raw::c_ulong) == 0 as std::os::raw::c_int {
        beg =
            (beg as
                 std::os::raw::c_ulong).wrapping_add(3 as std::os::raw::c_int as
                                                 std::os::raw::c_ulong) as size_t as
                size_t
    }
    while beg < doc_size {
        /* iterating over lines */
        if is_ref(document, beg, doc_size, &mut end, (*md).refs.as_mut_ptr())
               != 0 {
            beg = end
        } else {
            /* skipping to the next line */
            end = beg;
            while end < doc_size &&
                      *document.offset(end as isize) as std::os::raw::c_int !=
                          '\n' as i32 &&
                      *document.offset(end as isize) as std::os::raw::c_int !=
                          '\r' as i32 {
                end = end.wrapping_add(1)
            }
            /* adding the line body if present */
            if end > beg {
                expand_tabs(text, document.offset(beg as isize),
                            end.wrapping_sub(beg));
            }
            while end < doc_size &&
                      (*document.offset(end as isize) as std::os::raw::c_int ==
                           '\n' as i32 ||
                           *document.offset(end as isize) as std::os::raw::c_int ==
                               '\r' as i32) {
                /* add one \n per newline */
                if *document.offset(end as isize) as std::os::raw::c_int ==
                       '\n' as i32 ||
                       end.wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) <
                           doc_size &&
                           *document.offset(end.wrapping_add(1 as std::os::raw::c_int
                                                                 as
                                                                 std::os::raw::c_ulong)
                                                as isize) as std::os::raw::c_int !=
                               '\n' as i32 {
                    bufputc(text, '\n' as i32);
                }
                end = end.wrapping_add(1)
            }
            beg = end
        }
    }
    /* pre-grow the output buffer to minimize allocations */
    bufgrow(ob, (*text).size.wrapping_add((*text).size >> 1 as std::os::raw::c_int));
    /* second pass: actual rendering */
    if (*md).cb.doc_header.is_some() {
        (*md).cb.doc_header.expect("non-null function pointer")(ob,
                                                                (*md).opaque);
    }
    if (*text).size != 0 {
        /* adding a final newline if not already present */
        if *(*text).data.offset((*text).size.wrapping_sub(1 as std::os::raw::c_int as
                                                              std::os::raw::c_ulong)
                                    as isize) as std::os::raw::c_int != '\n' as i32 &&
               *(*text).data.offset((*text).size.wrapping_sub(1 as std::os::raw::c_int
                                                                  as
                                                                  std::os::raw::c_ulong)
                                        as isize) as std::os::raw::c_int !=
                   '\r' as i32 {
            bufputc(text, '\n' as i32);
        }
        parse_block(ob, md, (*text).data, (*text).size);
    }
    if (*md).cb.doc_footer.is_some() {
        (*md).cb.doc_footer.expect("non-null function pointer")(ob,
                                                                (*md).opaque);
    }
    /* clean-up */
    bufrelease(text);
    free_link_refs(&mut (*md).refs);
}
#[no_mangle]
pub fn sd_markdown_free(md: &mut sd_markdown) {
    for i in 0..md.work_bufs[1].asize {
        let buf = unsafe { &mut *(md.work_bufs[1].item.offset(i as isize) as *mut buf) };
        unsafe { bufrelease(buf) };
    }
    
    for i in 0..md.work_bufs[0].asize {
        let buf = unsafe { &mut *(md.work_bufs[0].item.offset(i as isize) as *mut buf) };
        unsafe { bufrelease(buf) };
    }
    
    stack_free(&mut md.work_bufs[1]);
    stack_free(&mut md.work_bufs[0]);
}

#[no_mangle]
pub fn sd_version() -> (i32, i32, i32) {
    (1, 16, 0)
}

/* vim: set filetype=c: */
