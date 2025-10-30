use ::libc;
use libc::syscall;
extern "C" {
    fn bufgrow(_: *mut buf, _: size_t) -> libc::c_int;
    fn bufnew(_: size_t) -> *mut buf;
    fn bufput(_: *mut buf, _: *const libc::c_void, _: size_t);
    fn bufputc(_: *mut buf, _: libc::c_int);
    fn bufrelease(_: *mut buf);
    fn buftruncate(buf: *mut buf, size: size_t) -> libc::c_int;
    fn sd_autolink__www(
        rewind_p: *mut size_t,
        link: *mut buf,
        data: *mut uint8_t,
        max_rewind: size_t,
        size: size_t,
        flags: libc::c_uint,
    ) -> size_t;
    fn sd_autolink__email(
        rewind_p: *mut size_t,
        link: *mut buf,
        data: *mut uint8_t,
        max_rewind: size_t,
        size: size_t,
        flags: libc::c_uint,
    ) -> size_t;
    fn sd_autolink__url(
        rewind_p: *mut size_t,
        link: *mut buf,
        data: *mut uint8_t,
        max_rewind: size_t,
        size: size_t,
        flags: libc::c_uint,
    ) -> size_t;
    fn sd_autolink__subreddit(
        rewind_p: *mut size_t,
        link: *mut buf,
        data: *mut uint8_t,
        max_rewind: size_t,
        max_lookbehind: size_t,
        size: size_t,
        no_slash: *mut libc::c_int,
    ) -> size_t;
    fn sd_autolink__username(
        rewind_p: *mut size_t,
        link: *mut buf,
        data: *mut uint8_t,
        max_rewind: size_t,
        max_lookbehind: size_t,
        size: size_t,
        no_slash: *mut libc::c_int,
    ) -> size_t;
    fn stack_free(_: *mut stack);
    fn stack_init(_: *mut stack, _: size_t) -> libc::c_int;
    fn stack_push(_: *mut stack, _: *mut libc::c_void) -> libc::c_int;
    fn strtol(
        _: *const libc::c_char,
        _: *mut *mut libc::c_char,
        _: libc::c_int,
    ) -> libc::c_long;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn siphash_nocase(
        in_0: *const uint8_t,
        inlen: size_t,
        k: *const uint8_t,
    ) -> uint64_t;
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memmove(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memcmp(
        _: *const libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strncmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn strchr(_: *const libc::c_char, _: libc::c_int) -> *mut libc::c_char;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn strncasecmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn __ctype_b_loc() -> *mut *const libc::c_ushort;
    fn __ctype_tolower_loc() -> *mut *const __int32_t;
}
pub type size_t = libc::c_ulong;
pub type __uint8_t = libc::c_uchar;
pub type __int32_t = libc::c_int;
pub type __uint32_t = libc::c_uint;
pub type __uint64_t = libc::c_ulong;
pub type uint8_t = __uint8_t;
pub type uint32_t = __uint32_t;
pub type uint64_t = __uint64_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct buf {
    pub data: *mut uint8_t,
    pub size: size_t,
    pub asize: size_t,
    pub unit: size_t,
}
pub type mkd_autolink = libc::c_uint;
pub const MKDA_EMAIL: mkd_autolink = 2;
pub const MKDA_NORMAL: mkd_autolink = 1;
pub const MKDA_NOT_AUTOLINK: mkd_autolink = 0;
pub type mkd_tableflags = libc::c_uint;
pub const MKD_TABLE_HEADER: mkd_tableflags = 4;
pub const MKD_TABLE_ALIGNMASK: mkd_tableflags = 3;
pub const MKD_TABLE_ALIGN_CENTER: mkd_tableflags = 3;
pub const MKD_TABLE_ALIGN_R: mkd_tableflags = 2;
pub const MKD_TABLE_ALIGN_L: mkd_tableflags = 1;
pub type mkd_extensions = libc::c_uint;
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
    pub blockcode: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub blockquote: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub blockspoiler: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub blockhtml: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub header: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub hrule: Option::<unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> ()>,
    pub list: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub listitem: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub paragraph: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub table: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub table_row: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub table_cell: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            libc::c_int,
            *mut libc::c_void,
            libc::c_int,
        ) -> (),
    >,
    pub autolink: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            mkd_autolink,
            *mut libc::c_void,
        ) -> libc::c_int,
    >,
    pub codespan: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub spoilerspan: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub double_emphasis: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub emphasis: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub image: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            *const buf,
            *const buf,
            *mut libc::c_void,
        ) -> libc::c_int,
    >,
    pub linebreak: Option::<
        unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub link: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            *const buf,
            *const buf,
            *mut libc::c_void,
        ) -> libc::c_int,
    >,
    pub raw_html_tag: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub triple_emphasis: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub strikethrough: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub superscript: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub entity: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub normal_text: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub doc_header: Option::<unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> ()>,
    pub doc_footer: Option::<unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> ()>,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sd_markdown {
    pub cb: sd_callbacks,
    pub opaque: *mut libc::c_void,
    pub refs: [*mut link_ref; 8],
    pub active_char: [uint8_t; 256],
    pub work_bufs: [stack; 2],
    pub ext_flags: libc::c_uint,
    pub max_nesting: size_t,
    pub max_table_cols: size_t,
    pub in_link_body: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct stack {
    pub item: *mut *mut libc::c_void,
    pub size: size_t,
    pub asize: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct link_ref {
    pub id: libc::c_uint,
    pub link: *mut buf,
    pub label: *mut buf,
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
pub type char_trigger = Option::<
    unsafe extern "C" fn(
        *mut buf,
        *mut sd_markdown,
        *mut uint8_t,
        size_t,
        size_t,
        size_t,
    ) -> size_t,
>;
pub const MAX_HASH_VALUE: C2RustUnnamed = 770;
pub const MIN_WORD_LENGTH: C2RustUnnamed = 4;
pub const MAX_WORD_LENGTH: C2RustUnnamed = 10;
pub type C2RustUnnamed = libc::c_uint;
pub const MIN_HASH_VALUE: C2RustUnnamed = 14;
pub const TOTAL_KEYWORDS: C2RustUnnamed = 253;
pub const _ISalnum: C2RustUnnamed_1 = 8;
pub const _ISdigit: C2RustUnnamed_1 = 2048;
pub const _ISxdigit: C2RustUnnamed_1 = 4096;
pub const _ISpunct: C2RustUnnamed_1 = 4;
pub const MAX_HASH_VALUE_0: C2RustUnnamed_0 = 37;
pub const MIN_WORD_LENGTH_0: C2RustUnnamed_0 = 1;
pub const MAX_WORD_LENGTH_0: C2RustUnnamed_0 = 10;
pub type C2RustUnnamed_0 = libc::c_uint;
pub const MIN_HASH_VALUE_0: C2RustUnnamed_0 = 1;
pub const TOTAL_KEYWORDS_0: C2RustUnnamed_0 = 24;
pub type C2RustUnnamed_1 = libc::c_uint;
pub const _IScntrl: C2RustUnnamed_1 = 2;
pub const _ISblank: C2RustUnnamed_1 = 1;
pub const _ISgraph: C2RustUnnamed_1 = 32768;
pub const _ISprint: C2RustUnnamed_1 = 16384;
pub const _ISspace: C2RustUnnamed_1 = 8192;
pub const _ISalpha: C2RustUnnamed_1 = 1024;
pub const _ISlower: C2RustUnnamed_1 = 512;
pub const _ISupper: C2RustUnnamed_1 = 256;
pub type markdown_char_t = libc::c_uint;
pub const MD_CHAR_NONE: markdown_char_t = 0;
#[inline]
unsafe extern "C" fn tolower(mut __c: libc::c_int) -> libc::c_int {
    return if __c >= -(128 as libc::c_int) && __c < 256 as libc::c_int {
        *(*__ctype_tolower_loc()).offset(__c as isize)
    } else {
        __c
    };
}
unsafe extern "C" fn hash_block_tag(
    mut str: *const libc::c_char,
    mut len: libc::c_uint,
) -> libc::c_uint {
    static mut asso_values: [libc::c_uchar; 257] = [
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        8 as libc::c_int as libc::c_uchar,
        30 as libc::c_int as libc::c_uchar,
        25 as libc::c_int as libc::c_uchar,
        20 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        10 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        10 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        10 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        15 as libc::c_int as libc::c_uchar,
        0 as libc::c_int as libc::c_uchar,
        5 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
        38 as libc::c_int as libc::c_uchar,
    ];
    let mut hval: libc::c_int = len as libc::c_int;
    match hval {
        1 => {}
        _ => {
            hval
                += asso_values[(*str.offset(1 as libc::c_int as isize) as libc::c_uchar
                    as libc::c_int + 1 as libc::c_int) as usize] as libc::c_int;
        }
    }
    hval
        += asso_values[*str.offset(0 as libc::c_int as isize) as libc::c_uchar as usize]
            as libc::c_int;
    return hval as libc::c_uint;
}
#[no_mangle]
pub unsafe extern "C" fn find_block_tag(
    mut str: *const libc::c_char,
    mut len: libc::c_uint,
) -> *const libc::c_char {
    static mut wordlist: [*const libc::c_char; 39] = [
        b"\0" as *const u8 as *const libc::c_char,
        b"p\0" as *const u8 as *const libc::c_char,
        b"dl\0" as *const u8 as *const libc::c_char,
        b"div\0" as *const u8 as *const libc::c_char,
        b"math\0" as *const u8 as *const libc::c_char,
        b"table\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"ul\0" as *const u8 as *const libc::c_char,
        b"del\0" as *const u8 as *const libc::c_char,
        b"form\0" as *const u8 as *const libc::c_char,
        b"blockquote\0" as *const u8 as *const libc::c_char,
        b"figure\0" as *const u8 as *const libc::c_char,
        b"ol\0" as *const u8 as *const libc::c_char,
        b"fieldset\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"h1\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"h6\0" as *const u8 as *const libc::c_char,
        b"pre\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"script\0" as *const u8 as *const libc::c_char,
        b"h5\0" as *const u8 as *const libc::c_char,
        b"noscript\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"style\0" as *const u8 as *const libc::c_char,
        b"iframe\0" as *const u8 as *const libc::c_char,
        b"h4\0" as *const u8 as *const libc::c_char,
        b"ins\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"h3\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"h2\0" as *const u8 as *const libc::c_char,
        b"span\0" as *const u8 as *const libc::c_char,
    ];
    if len <= MAX_WORD_LENGTH_0 as libc::c_int as libc::c_uint
        && len >= MIN_WORD_LENGTH_0 as libc::c_int as libc::c_uint
    {
        let mut key: libc::c_int = hash_block_tag(str, len) as libc::c_int;
        if key <= MAX_HASH_VALUE_0 as libc::c_int && key >= 0 as libc::c_int {
            let mut s: *const libc::c_char = wordlist[key as usize];
            if (*str as libc::c_uchar as libc::c_int
                ^ *s as libc::c_uchar as libc::c_int) & !(32 as libc::c_int)
                == 0 as libc::c_int && strncasecmp(str, s, len as libc::c_ulong) == 0
                && *s.offset(len as isize) as libc::c_int == '\0' as i32
            {
                return s;
            }
        }
    }
    return 0 as *const libc::c_char;
}
#[no_mangle]
pub static mut MAX_NUM_ENTITY_VAL: libc::c_uint = 0x10ffff as libc::c_int
    as libc::c_uint;
#[no_mangle]
pub static mut MAX_NUM_ENTITY_LEN: size_t = 7 as libc::c_int as size_t;
#[inline]
unsafe extern "C" fn is_valid_numeric_entity(mut entity_val: uint32_t) -> libc::c_int {
    return (entity_val > 8 as libc::c_int as uint32_t
        && (entity_val != 11 as libc::c_int as uint32_t
            && entity_val != 12 as libc::c_int as uint32_t)
        && (entity_val < 14 as libc::c_int as uint32_t
            || entity_val > 31 as libc::c_int as uint32_t)
        && (entity_val < 55296 as libc::c_int as uint32_t
            || entity_val > 57343 as libc::c_int as uint32_t)
        && (entity_val != 65534 as libc::c_int as uint32_t
            && entity_val != 65535 as libc::c_int as uint32_t)
        && entity_val <= MAX_NUM_ENTITY_VAL) as libc::c_int;
}
unsafe extern "C" fn hash_html_entity(
    mut str: *const libc::c_char,
    mut len: size_t,
) -> libc::c_uint {
    static mut asso_values: [libc::c_ushort; 257] = [
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        95 as libc::c_int as libc::c_ushort,
        90 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        115 as libc::c_int as libc::c_ushort,
        94 as libc::c_int as libc::c_ushort,
        55 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        150 as libc::c_int as libc::c_ushort,
        25 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        30 as libc::c_int as libc::c_ushort,
        195 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        30 as libc::c_int as libc::c_ushort,
        30 as libc::c_int as libc::c_ushort,
        5 as libc::c_int as libc::c_ushort,
        35 as libc::c_int as libc::c_ushort,
        45 as libc::c_int as libc::c_ushort,
        45 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        10 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        50 as libc::c_int as libc::c_ushort,
        125 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        5 as libc::c_int as libc::c_ushort,
        85 as libc::c_int as libc::c_ushort,
        75 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        40 as libc::c_int as libc::c_ushort,
        65 as libc::c_int as libc::c_ushort,
        20 as libc::c_int as libc::c_ushort,
        25 as libc::c_int as libc::c_ushort,
        60 as libc::c_int as libc::c_ushort,
        240 as libc::c_int as libc::c_ushort,
        240 as libc::c_int as libc::c_ushort,
        223 as libc::c_int as libc::c_ushort,
        10 as libc::c_int as libc::c_ushort,
        102 as libc::c_int as libc::c_ushort,
        20 as libc::c_int as libc::c_ushort,
        35 as libc::c_int as libc::c_ushort,
        135 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        5 as libc::c_int as libc::c_ushort,
        10 as libc::c_int as libc::c_ushort,
        183 as libc::c_int as libc::c_ushort,
        20 as libc::c_int as libc::c_ushort,
        5 as libc::c_int as libc::c_ushort,
        0 as libc::c_int as libc::c_ushort,
        50 as libc::c_int as libc::c_ushort,
        75 as libc::c_int as libc::c_ushort,
        10 as libc::c_int as libc::c_ushort,
        75 as libc::c_int as libc::c_ushort,
        175 as libc::c_int as libc::c_ushort,
        85 as libc::c_int as libc::c_ushort,
        15 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
        771 as libc::c_int as libc::c_ushort,
    ];
    let mut hval: libc::c_uint = len as libc::c_uint;
    let mut current_block_5: u64;
    match hval {
        6 => {
            current_block_5 = 12081597070177072672;
        }
        5 => {
            current_block_5 = 13986342074430558528;
        }
        4 => {
            current_block_5 = 13215153616776192185;
        }
        3 => {
            current_block_5 = 15574404683900076030;
        }
        2 => {
            current_block_5 = 378999934316175814;
        }
        _ => {
            hval = hval
                .wrapping_add(
                    asso_values[*str.offset(6 as libc::c_int as isize) as libc::c_uchar
                        as usize] as libc::c_uint,
                );
            current_block_5 = 12081597070177072672;
        }
    }
    match current_block_5 {
        12081597070177072672 => {
            hval = hval
                .wrapping_add(
                    asso_values[*str.offset(5 as libc::c_int as isize) as libc::c_uchar
                        as usize] as libc::c_uint,
                );
            current_block_5 = 13986342074430558528;
        }
        _ => {}
    }
    match current_block_5 {
        13986342074430558528 => {
            hval = hval
                .wrapping_add(
                    asso_values[*str.offset(4 as libc::c_int as isize) as libc::c_uchar
                        as usize] as libc::c_uint,
                );
            current_block_5 = 13215153616776192185;
        }
        _ => {}
    }
    match current_block_5 {
        13215153616776192185 => {
            hval = hval
                .wrapping_add(
                    asso_values[*str.offset(3 as libc::c_int as isize) as libc::c_uchar
                        as usize] as libc::c_uint,
                );
            current_block_5 = 15574404683900076030;
        }
        _ => {}
    }
    match current_block_5 {
        15574404683900076030 => {
            hval = hval
                .wrapping_add(
                    asso_values[(*str.offset(2 as libc::c_int as isize) as libc::c_uchar
                        as libc::c_int + 1 as libc::c_int) as usize] as libc::c_uint,
                );
        }
        _ => {}
    }
    hval = hval
        .wrapping_add(
            asso_values[*str.offset(1 as libc::c_int as isize) as libc::c_uchar as usize]
                as libc::c_uint,
        );
    return hval;
}
#[no_mangle]
pub unsafe extern "C" fn is_allowed_named_entity(
    mut str: *const libc::c_char,
    mut len: size_t,
) -> *const libc::c_char {
    static mut wordlist: [*const libc::c_char; 771] = [
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&or;\0" as *const u8 as *const libc::c_char,
        b"&not;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&int;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&psi;\0" as *const u8 as *const libc::c_char,
        b"&isin;\0" as *const u8 as *const libc::c_char,
        b"&notin;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Rho;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&phi;\0" as *const u8 as *const libc::c_char,
        b"&prop;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&rho;\0" as *const u8 as *const libc::c_char,
        b"&nbsp;\0" as *const u8 as *const libc::c_char,
        b"&thorn;\0" as *const u8 as *const libc::c_char,
        b"&thinsp;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&chi;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&prod;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&amp;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Psi;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&iota;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&omicron;\0" as *const u8 as *const libc::c_char,
        b"&Phi;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&and;\0" as *const u8 as *const libc::c_char,
        b"&sdot;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&nu;\0" as *const u8 as *const libc::c_char,
        b"&Chi;\0" as *const u8 as *const libc::c_char,
        b"&emsp;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Mu;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ensp;\0" as *const u8 as *const libc::c_char,
        b"&ocirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&lt;\0" as *const u8 as *const libc::c_char,
        b"&uml;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&icirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sup;\0" as *const u8 as *const libc::c_char,
        b"&sup1;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Scaron;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&cap;\0" as *const u8 as *const libc::c_char,
        b"&part;\0" as *const u8 as *const libc::c_char,
        b"&pound;\0" as *const u8 as *const libc::c_char,
        b"&scaron;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ni;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&lowast;\0" as *const u8 as *const libc::c_char,
        b"&Omicron;\0" as *const u8 as *const libc::c_char,
        b"&cup;\0" as *const u8 as *const libc::c_char,
        b"&Xi;\0" as *const u8 as *const libc::c_char,
        b"&crarr;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Nu;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&pi;\0" as *const u8 as *const libc::c_char,
        b"&theta;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&tau;\0" as *const u8 as *const libc::c_char,
        b"&nsub;\0" as *const u8 as *const libc::c_char,
        b"&acirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&thetasym;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Ocirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&rarr;\0" as *const u8 as *const libc::c_char,
        b"&ucirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&loz;\0" as *const u8 as *const libc::c_char,
        b"&darr;\0" as *const u8 as *const libc::c_char,
        b"&trade;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&para;\0" as *const u8 as *const libc::c_char,
        b"&ecirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&larr;\0" as *const u8 as *const libc::c_char,
        b"&radic;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sub;\0" as *const u8 as *const libc::c_char,
        b"&Pi;\0" as *const u8 as *const libc::c_char,
        b"&kappa;\0" as *const u8 as *const libc::c_char,
        b"&iquest;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&eta;\0" as *const u8 as *const libc::c_char,
        b"&supe;\0" as *const u8 as *const libc::c_char,
        b"&rceil;\0" as *const u8 as *const libc::c_char,
        b"&there4;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&rArr;\0" as *const u8 as *const libc::c_char,
        b"&uarr;\0" as *const u8 as *const libc::c_char,
        b"&Kappa;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&dArr;\0" as *const u8 as *const libc::c_char,
        b"&euro;\0" as *const u8 as *const libc::c_char,
        b"&Theta;\0" as *const u8 as *const libc::c_char,
        b"&circ;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Tau;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&lceil;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&lArr;\0" as *const u8 as *const libc::c_char,
        b"&ordm;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&lrm;\0" as *const u8 as *const libc::c_char,
        b"&xi;\0" as *const u8 as *const libc::c_char,
        b"&acute;\0" as *const u8 as *const libc::c_char,
        b"&ccedil;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sup3;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ntilde;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&uArr;\0" as *const u8 as *const libc::c_char,
        b"&sup2;\0" as *const u8 as *const libc::c_char,
        b"&piv;\0" as *const u8 as *const libc::c_char,
        b"&otilde;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&shy;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Acirc;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&curren;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Ucirc;\0" as *const u8 as *const libc::c_char,
        b"&oacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sube;\0" as *const u8 as *const libc::c_char,
        b"&nabla;\0" as *const u8 as *const libc::c_char,
        b"&iacute;\0" as *const u8 as *const libc::c_char,
        b"&mu;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&bull;\0" as *const u8 as *const libc::c_char,
        b"&oline;\0" as *const u8 as *const libc::c_char,
        b"&Ccedil;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sum;\0" as *const u8 as *const libc::c_char,
        b"&copy;\0" as *const u8 as *const libc::c_char,
        b"&equiv;\0" as *const u8 as *const libc::c_char,
        b"&Ntilde;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&prime;\0" as *const u8 as *const libc::c_char,
        b"&atilde;\0" as *const u8 as *const libc::c_char,
        b"&tilde;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Ecirc;\0" as *const u8 as *const libc::c_char,
        b"&Otilde;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&apos;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&aacute;\0" as *const u8 as *const libc::c_char,
        b"&ne;\0" as *const u8 as *const libc::c_char,
        b"&Eta;\0" as *const u8 as *const libc::c_char,
        b"&macr;\0" as *const u8 as *const libc::c_char,
        b"&sim;\0" as *const u8 as *const libc::c_char,
        b"&Oacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Iota;\0" as *const u8 as *const libc::c_char,
        b"&empty;\0" as *const u8 as *const libc::c_char,
        b"&uacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ouml;\0" as *const u8 as *const libc::c_char,
        b"&exist;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&iuml;\0" as *const u8 as *const libc::c_char,
        b"&Prime;\0" as *const u8 as *const libc::c_char,
        b"&eacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&rsquo;\0" as *const u8 as *const libc::c_char,
        b"&cent;\0" as *const u8 as *const libc::c_char,
        b"&zwj;\0" as *const u8 as *const libc::c_char,
        b"&zwnj;\0" as *const u8 as *const libc::c_char,
        b"&quot;\0" as *const u8 as *const libc::c_char,
        b"&sbquo;\0" as *const u8 as *const libc::c_char,
        b"&sect;\0" as *const u8 as *const libc::c_char,
        b"&infin;\0" as *const u8 as *const libc::c_char,
        b"&otimes;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&cong;\0" as *const u8 as *const libc::c_char,
        b"&Icirc;\0" as *const u8 as *const libc::c_char,
        b"&brvbar;\0" as *const u8 as *const libc::c_char,
        b"&le;\0" as *const u8 as *const libc::c_char,
        b"&lsquo;\0" as *const u8 as *const libc::c_char,
        b"&ordf;\0" as *const u8 as *const libc::c_char,
        b"&clubs;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&oplus;\0" as *const u8 as *const libc::c_char,
        b"&perp;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Yacute;\0" as *const u8 as *const libc::c_char,
        b"&micro;\0" as *const u8 as *const libc::c_char,
        b"&ang;\0" as *const u8 as *const libc::c_char,
        b"&auml;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&gt;\0" as *const u8 as *const libc::c_char,
        b"&rlm;\0" as *const u8 as *const libc::c_char,
        b"&Ouml;\0" as *const u8 as *const libc::c_char,
        b"&upsilon;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&minus;\0" as *const u8 as *const libc::c_char,
        b"&middot;\0" as *const u8 as *const libc::c_char,
        b"&uuml;\0" as *const u8 as *const libc::c_char,
        b"&aring;\0" as *const u8 as *const libc::c_char,
        b"&Atilde;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&divide;\0" as *const u8 as *const libc::c_char,
        b"&rsaquo;\0" as *const u8 as *const libc::c_char,
        b"&epsilon;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&times;\0" as *const u8 as *const libc::c_char,
        b"&ETH;\0" as *const u8 as *const libc::c_char,
        b"&euml;\0" as *const u8 as *const libc::c_char,
        b"&szlig;\0" as *const u8 as *const libc::c_char,
        b"&frac14;\0" as *const u8 as *const libc::c_char,
        b"&diams;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&oslash;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Aacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&lsaquo;\0" as *const u8 as *const libc::c_char,
        b"&Delta;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&rdquo;\0" as *const u8 as *const libc::c_char,
        b"&spades;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Uacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&raquo;\0" as *const u8 as *const libc::c_char,
        b"&rang;\0" as *const u8 as *const libc::c_char,
        b"&frasl;\0" as *const u8 as *const libc::c_char,
        b"&rfloor;\0" as *const u8 as *const libc::c_char,
        b"&harr;\0" as *const u8 as *const libc::c_char,
        b"&ndash;\0" as *const u8 as *const libc::c_char,
        b"&Yuml;\0" as *const u8 as *const libc::c_char,
        b"&cedil;\0" as *const u8 as *const libc::c_char,
        b"&eth;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ldquo;\0" as *const u8 as *const libc::c_char,
        b"&real;\0" as *const u8 as *const libc::c_char,
        b"&THORN;\0" as *const u8 as *const libc::c_char,
        b"&plusmn;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&laquo;\0" as *const u8 as *const libc::c_char,
        b"&lang;\0" as *const u8 as *const libc::c_char,
        b"&delta;\0" as *const u8 as *const libc::c_char,
        b"&lfloor;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&beta;\0" as *const u8 as *const libc::c_char,
        b"&omega;\0" as *const u8 as *const libc::c_char,
        b"&Eacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Oslash;\0" as *const u8 as *const libc::c_char,
        b"&image;\0" as *const u8 as *const libc::c_char,
        b"&weierp;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Zeta;\0" as *const u8 as *const libc::c_char,
        b"&OElig;\0" as *const u8 as *const libc::c_char,
        b"&hArr;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Auml;\0" as *const u8 as *const libc::c_char,
        b"&asymp;\0" as *const u8 as *const libc::c_char,
        b"&Lambda;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&bdquo;\0" as *const u8 as *const libc::c_char,
        b"&zeta;\0" as *const u8 as *const libc::c_char,
        b"&Upsilon;\0" as *const u8 as *const libc::c_char,
        b"&lambda;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Uuml;\0" as *const u8 as *const libc::c_char,
        b"&Aring;\0" as *const u8 as *const libc::c_char,
        b"&yacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Beta;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Gamma;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&iexcl;\0" as *const u8 as *const libc::c_char,
        b"&forall;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Omega;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Epsilon;\0" as *const u8 as *const libc::c_char,
        b"&Iacute;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Euml;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&frac34;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&frac12;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&yen;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&yuml;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ograve;\0" as *const u8 as *const libc::c_char,
        b"&AElig;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&igrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Iuml;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&alpha;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&permil;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&agrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&mdash;\0" as *const u8 as *const libc::c_char,
        b"&Ograve;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ugrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&upsih;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&ge;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&egrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&fnof;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&reg;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&deg;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Sigma;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sigma;\0" as *const u8 as *const libc::c_char,
        b"&Alpha;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&hearts;\0" as *const u8 as *const libc::c_char,
        b"&oelig;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Agrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Ugrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&hellip;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&aelig;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Egrave;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Igrave;\0" as *const u8 as *const libc::c_char,
        b"&gamma;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&Dagger;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&dagger;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&alefsym;\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"\0" as *const u8 as *const libc::c_char,
        b"&sigmaf;\0" as *const u8 as *const libc::c_char,
    ];
    if len <= MAX_WORD_LENGTH as libc::c_int as size_t
        && len >= MIN_WORD_LENGTH as libc::c_int as size_t
    {
        let mut key: libc::c_uint = hash_html_entity(str, len);
        if key <= MAX_HASH_VALUE as libc::c_int as libc::c_uint {
            let mut s: *const libc::c_char = wordlist[key as usize];
            if *str as libc::c_int == *s as libc::c_int
                && strncmp(
                    str.offset(1 as libc::c_int as isize),
                    s.offset(1 as libc::c_int as isize),
                    len.wrapping_sub(1 as libc::c_int as size_t),
                ) == 0 && *s.offset(len as isize) as libc::c_int == '\0' as i32
            {
                return s;
            }
        }
    }
    return 0 as *const libc::c_char;
}
static mut markdown_char_ptrs: [char_trigger; 13] = [
    None,
    Some(
        char_emphasis
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_codespan
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_linebreak
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_link
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_langle_tag
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_escape
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_entity
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_autolink_url
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_autolink_email
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_autolink_www
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_autolink_subreddit_or_username
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
    Some(
        char_superscript
            as unsafe extern "C" fn(
                *mut buf,
                *mut sd_markdown,
                *mut uint8_t,
                size_t,
                size_t,
                size_t,
            ) -> size_t,
    ),
];
#[no_mangle]
pub static mut sip_hash_key_init: libc::c_int = 0 as libc::c_int;
#[no_mangle]
pub static mut sip_hash_key: [uint8_t; 16] = [0; 16];
#[no_mangle]
pub unsafe extern "C" fn backport_getrandom(
    mut buf: *mut libc::c_void,
    mut buflen: size_t,
    mut flags: libc::c_uint,
) -> libc::c_int {
    return syscall((318 as libc::c_int).into(), buf, buflen, flags).try_into().unwrap();
}
#[inline]
unsafe extern "C" fn rndr_newbuf(
    mut rndr: *mut sd_markdown,
    mut type_0: libc::c_int,
) -> *mut buf {
    static mut buf_size: [size_t; 2] = [
        256 as libc::c_int as size_t,
        64 as libc::c_int as size_t,
    ];
    let mut work: *mut buf = 0 as *mut buf;
    let mut pool: *mut stack = &mut *((*rndr).work_bufs)
        .as_mut_ptr()
        .offset(type_0 as isize) as *mut stack;
    if (*pool).size < (*pool).asize
        && !(*((*pool).item).offset((*pool).size as isize)).is_null()
    {
        let fresh0 = (*pool).size;
        (*pool).size = ((*pool).size).wrapping_add(1);
        work = *((*pool).item).offset(fresh0 as isize) as *mut buf;
        (*work).size = 0 as libc::c_int as size_t;
    } else {
        work = bufnew(buf_size[type_0 as usize]);
        stack_push(pool, work as *mut libc::c_void);
    }
    return work;
}
#[inline]
unsafe extern "C" fn rndr_popbuf(mut rndr: *mut sd_markdown, mut type_0: libc::c_int) {
    (*rndr)
        .work_bufs[type_0 as usize]
        .size = ((*rndr).work_bufs[type_0 as usize].size).wrapping_sub(1);
    (*rndr).work_bufs[type_0 as usize].size;
}
unsafe extern "C" fn unscape_text(mut ob: *mut buf, mut src: *mut buf) {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut org: size_t = 0;
    while i < (*src).size {
        org = i;
        while i < (*src).size
            && *((*src).data).offset(i as isize) as libc::c_int != '\\' as i32
        {
            i = i.wrapping_add(1);
            i;
        }
        if i > org {
            bufput(
                ob,
                ((*src).data).offset(org as isize) as *const libc::c_void,
                i.wrapping_sub(org),
            );
        }
        if i.wrapping_add(1 as libc::c_int as size_t) >= (*src).size {
            break;
        }
        bufputc(
            ob,
            *((*src).data).offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int,
        );
        i = i.wrapping_add(2 as libc::c_int as size_t);
    }
}
unsafe extern "C" fn hash_link_ref(
    mut link_ref: *const uint8_t,
    mut length: size_t,
) -> libc::c_uint {
    return siphash_nocase(link_ref, length, sip_hash_key.as_mut_ptr()) as libc::c_uint;
}
unsafe extern "C" fn add_link_ref(
    mut references: *mut *mut link_ref,
    mut name: *const uint8_t,
    mut name_size: size_t,
) -> *mut link_ref {
    let mut hash: libc::c_uint = 0;
    let mut ref_0: *mut link_ref = 0 as *mut link_ref;
    hash = hash_link_ref(name, name_size);
    ref_0 = *references
        .offset(hash.wrapping_rem(8 as libc::c_int as libc::c_uint) as isize);
    while !ref_0.is_null() {
        if (*ref_0).id == hash && (*(*ref_0).label).size == name_size {
            if strncasecmp(
                (*(*ref_0).label).data as *mut libc::c_char,
                name as *mut libc::c_char,
                name_size,
            ) == 0 as libc::c_int
            {
                bufrelease((*ref_0).label);
                bufrelease((*ref_0).link);
                bufrelease((*ref_0).title);
                return ref_0;
            }
        }
        ref_0 = (*ref_0).next;
    }std::intrinsics::assume((ref_0).addr() == 0);
    ref_0 = calloc(
        1 as libc::c_int as libc::c_ulong,
        ::core::mem::size_of::<link_ref>() as libc::c_ulong,
    ) as *mut link_ref;
    if ref_0.is_null() {std::intrinsics::assume((ref_0).addr() == 0);
        return 0 as *mut link_ref;
    }
    (*ref_0).id = hash;
    (*ref_0)
        .next = *references
        .offset(((*ref_0).id).wrapping_rem(8 as libc::c_int as libc::c_uint) as isize);
    *references
        .offset(((*ref_0).id).wrapping_rem(8 as libc::c_int as libc::c_uint) as isize) = ref_0;
    return ref_0;
}
unsafe extern "C" fn find_link_ref(
    mut references: *mut *mut link_ref,
    mut name: *mut uint8_t,
    mut length: size_t,
) -> *mut link_ref {
    let mut hash: libc::c_uint = hash_link_ref(name, length);
    let mut ref_0: *mut link_ref = 0 as *mut link_ref;
    ref_0 = *references
        .offset(hash.wrapping_rem(8 as libc::c_int as libc::c_uint) as isize);
    while !ref_0.is_null() {
        if (*ref_0).id == hash && (*(*ref_0).label).size == length {
            if strncasecmp(
                (*(*ref_0).label).data as *mut libc::c_char,
                name as *mut libc::c_char,
                length,
            ) == 0 as libc::c_int
            {
                return ref_0;
            }
        }
        ref_0 = (*ref_0).next;
    }std::intrinsics::assume((ref_0).addr() == 0);
    return 0 as *mut link_ref;
}
unsafe extern "C" fn free_link_refs(mut references: *mut *mut link_ref) {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < 8 as libc::c_int as size_t {
        let mut r: *mut link_ref = *references.offset(i as isize);
        let mut next: *mut link_ref = 0 as *mut link_ref;
        while !r.is_null() {
            next = (*r).next;
            bufrelease((*r).label);
            bufrelease((*r).link);
            bufrelease((*r).title);
            free(r as *mut libc::c_void);
            r = next;
        }std::intrinsics::assume((r).addr() == 0);
        i = i.wrapping_add(1);
        i;
    }
}
#[inline]
unsafe extern "C" fn _isspace(mut c: libc::c_int) -> libc::c_int {
    return (c == ' ' as i32 || c == '\n' as i32) as libc::c_int;
}
unsafe extern "C" fn is_mail_autolink(
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut nb: size_t = 0 as libc::c_int as size_t;
    i = 0 as libc::c_int as size_t;
    while i < size {
        if !(*(*__ctype_b_loc()).offset(*data.offset(i as isize) as libc::c_int as isize)
            as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
            != 0)
        {
            match *data.offset(i as isize) as libc::c_int {
                64 => {
                    nb = nb.wrapping_add(1);
                    nb;
                }
                45 | 46 | 95 => {}
                62 => {
                    return if nb == 1 as libc::c_int as size_t {
                        i.wrapping_add(1 as libc::c_int as size_t)
                    } else {
                        0 as libc::c_int as size_t
                    };
                }
                _ => return 0 as libc::c_int as size_t,
            }
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn tag_length(
    mut data: *mut uint8_t,
    mut size: size_t,
    mut autolink: *mut mkd_autolink,
) -> size_t {
    let mut i: size_t = 0;
    let mut j: size_t = 0;
    if size < 3 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    if *data.offset(0 as libc::c_int as isize) as libc::c_int != '<' as i32 {
        return 0 as libc::c_int as size_t;
    }
    i = (if *data.offset(1 as libc::c_int as isize) as libc::c_int == '/' as i32 {
        2 as libc::c_int
    } else {
        1 as libc::c_int
    }) as size_t;
    if *(*__ctype_b_loc()).offset(*data.offset(i as isize) as libc::c_int as isize)
        as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int == 0
    {
        return 0 as libc::c_int as size_t;
    }
    *autolink = MKDA_NOT_AUTOLINK;
    while i < size
        && (*(*__ctype_b_loc()).offset(*data.offset(i as isize) as libc::c_int as isize)
            as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
            != 0 || *data.offset(i as isize) as libc::c_int == '.' as i32
            || *data.offset(i as isize) as libc::c_int == '+' as i32
            || *data.offset(i as isize) as libc::c_int == '-' as i32)
    {
        i = i.wrapping_add(1);
        i;
    }
    if i > 1 as libc::c_int as size_t
        && *data.offset(i as isize) as libc::c_int == '@' as i32
    {
        j = is_mail_autolink(data.offset(i as isize), size.wrapping_sub(i));
        if j != 0 as libc::c_int as size_t {
            *autolink = MKDA_EMAIL;
            return i.wrapping_add(j);
        }
    }
    if i > 2 as libc::c_int as size_t
        && *data.offset(i as isize) as libc::c_int == ':' as i32
    {
        *autolink = MKDA_NORMAL;
        i = i.wrapping_add(1);
        i;
    }
    if i >= size {
        *autolink = MKDA_NOT_AUTOLINK;
    } else if *autolink as u64 != 0 {
        j = i;
        while i < size {
            if *data.offset(i as isize) as libc::c_int == '\\' as i32 {
                i = i.wrapping_add(2 as libc::c_int as size_t);
            } else {
                if *data.offset(i as isize) as libc::c_int == '>' as i32
                    || *data.offset(i as isize) as libc::c_int == '\'' as i32
                    || *data.offset(i as isize) as libc::c_int == '"' as i32
                    || *data.offset(i as isize) as libc::c_int == ' ' as i32
                    || *data.offset(i as isize) as libc::c_int == '\n' as i32
                {
                    break;
                }
                i = i.wrapping_add(1);
                i;
            }
        }
        if i >= size {
            return 0 as libc::c_int as size_t;
        }
        if i > j && *data.offset(i as isize) as libc::c_int == '>' as i32 {
            return i.wrapping_add(1 as libc::c_int as size_t);
        }
        *autolink = MKDA_NOT_AUTOLINK;
    }
    while i < size && *data.offset(i as isize) as libc::c_int != '>' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i >= size {
        return 0 as libc::c_int as size_t;
    }
    return i.wrapping_add(1 as libc::c_int as size_t);
}
unsafe extern "C" fn parse_inline(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut end: size_t = 0 as libc::c_int as size_t;
    let mut last_special: size_t = 0 as libc::c_int as size_t;
    let mut action: uint8_t = 0 as libc::c_int as uint8_t;
    let mut work: buf = {
        let mut init = buf {
            data: 0 as *mut uint8_t,
            size: 0 as libc::c_int as size_t,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    if ((*rndr).work_bufs[1 as libc::c_int as usize].size)
        .wrapping_add((*rndr).work_bufs[0 as libc::c_int as usize].size)
        > (*rndr).max_nesting
    {
        return;
    }
    while i < size {
        while end < size
            && {
                action = (*rndr).active_char[*data.offset(end as isize) as usize];
                action as libc::c_int == 0 as libc::c_int
            }
        {
            end = end.wrapping_add(1);
            end;
        }
        if ((*rndr).cb.normal_text).is_some() {
            work.data = data.offset(i as isize);
            work.size = end.wrapping_sub(i);
            ((*rndr).cb.normal_text)
                .expect("non-null function pointer")(ob, &mut work, (*rndr).opaque);
        } else {
            bufput(
                ob,
                data.offset(i as isize) as *const libc::c_void,
                end.wrapping_sub(i),
            );
        }
        if end >= size {
            break;
        }
        i = end;
        end = (markdown_char_ptrs[action as libc::c_int as usize])
            .expect(
                "non-null function pointer",
            )(
            ob,
            rndr,
            data.offset(i as isize),
            i.wrapping_sub(last_special),
            i,
            size.wrapping_sub(i),
        );
        if end == 0 {
            end = i.wrapping_add(1 as libc::c_int as size_t);
        } else {
            i = i.wrapping_add(end);
            end = i;
            last_special = end;
        }
    }
}
unsafe extern "C" fn find_emph_char(
    mut data: *mut uint8_t,
    mut size: size_t,
    mut c: uint8_t,
) -> size_t {
    let mut i: size_t = 1 as libc::c_int as size_t;
    while i < size {
        while i < size && *data.offset(i as isize) as libc::c_int != c as libc::c_int
            && *data.offset(i as isize) as libc::c_int != '`' as i32
            && *data.offset(i as isize) as libc::c_int != '[' as i32
        {
            i = i.wrapping_add(1);
            i;
        }
        if i == size {
            return 0 as libc::c_int as size_t;
        }
        if i < size && c as libc::c_int == '<' as i32
            && *data.offset(i as isize) as libc::c_int == c as libc::c_int
            && *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '!' as i32
        {
            return i;
        }
        if *data.offset(i as isize) as libc::c_int == c as libc::c_int {
            return i;
        }
        if i != 0
            && *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '\\' as i32
        {
            i = i.wrapping_add(1);
            i;
        } else if *data.offset(i as isize) as libc::c_int == '`' as i32 {
            let mut span_nb: size_t = 0 as libc::c_int as size_t;
            let mut bt: size_t = 0;
            let mut tmp_i: size_t = 0 as libc::c_int as size_t;
            while i < size && *data.offset(i as isize) as libc::c_int == '`' as i32 {
                i = i.wrapping_add(1);
                i;
                span_nb = span_nb.wrapping_add(1);
                span_nb;
            }
            if i >= size {
                return 0 as libc::c_int as size_t;
            }
            bt = 0 as libc::c_int as size_t;
            while i < size && bt < span_nb {
                if tmp_i == 0
                    && *data.offset(i as isize) as libc::c_int == c as libc::c_int
                {
                    tmp_i = i;
                }
                if *data.offset(i as isize) as libc::c_int == '`' as i32 {
                    bt = bt.wrapping_add(1);
                    bt;
                } else {
                    bt = 0 as libc::c_int as size_t;
                }
                i = i.wrapping_add(1);
                i;
            }
            if i >= size {
                return tmp_i;
            }
        } else {
            if !(*data.offset(i as isize) as libc::c_int == '[' as i32) {
                continue;
            }
            let mut tmp_i_0: size_t = 0 as libc::c_int as size_t;
            let mut cc: uint8_t = 0;
            i = i.wrapping_add(1);
            i;
            while i < size && *data.offset(i as isize) as libc::c_int != ']' as i32 {
                if tmp_i_0 == 0
                    && *data.offset(i as isize) as libc::c_int == c as libc::c_int
                {
                    tmp_i_0 = i;
                }
                i = i.wrapping_add(1);
                i;
            }
            i = i.wrapping_add(1);
            i;
            while i < size
                && (*data.offset(i as isize) as libc::c_int == ' ' as i32
                    || *data.offset(i as isize) as libc::c_int == '\n' as i32)
            {
                i = i.wrapping_add(1);
                i;
            }
            if i >= size {
                return tmp_i_0;
            }
            match *data.offset(i as isize) as libc::c_int {
                91 => {
                    cc = ']' as i32 as uint8_t;
                }
                40 => {
                    cc = ')' as i32 as uint8_t;
                }
                _ => {
                    if !(tmp_i_0 != 0) {
                        continue;
                    }
                    return tmp_i_0;
                }
            }
            i = i.wrapping_add(1);
            i;
            while i < size
                && *data.offset(i as isize) as libc::c_int != cc as libc::c_int
            {
                if tmp_i_0 == 0
                    && *data.offset(i as isize) as libc::c_int == c as libc::c_int
                {
                    tmp_i_0 = i;
                }
                i = i.wrapping_add(1);
                i;
            }
            if i >= size {
                return tmp_i_0;
            }
            i = i.wrapping_add(1);
            i;
        }
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn parse_emph1(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut c: uint8_t,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut len: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    let mut r: libc::c_int = 0;
    if ((*rndr).cb.emphasis).is_none() {
        return 0 as libc::c_int as size_t;
    }
    if size > 1 as libc::c_int as size_t
        && *data.offset(0 as libc::c_int as isize) as libc::c_int == c as libc::c_int
        && *data.offset(1 as libc::c_int as isize) as libc::c_int == c as libc::c_int
    {
        i = 1 as libc::c_int as size_t;
    }
    while i < size {
        len = find_emph_char(data.offset(i as isize), size.wrapping_sub(i), c);
        if len == 0 {
            return 0 as libc::c_int as size_t;
        }
        i = i.wrapping_add(len);
        if i >= size {
            return 0 as libc::c_int as size_t;
        }
        if !(*data.offset(i as isize) as libc::c_int == c as libc::c_int
            && _isspace(
                *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                    as libc::c_int,
            ) == 0)
        {
            continue;
        }
        if (*rndr).ext_flags & MKDEXT_NO_INTRA_EMPHASIS as libc::c_int as libc::c_uint
            != 0 && c as libc::c_int == '_' as i32
        {
            if !(i.wrapping_add(1 as libc::c_int as size_t) == size
                || _isspace(
                    *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                        as libc::c_int,
                ) != 0
                || *(*__ctype_b_loc())
                    .offset(
                        *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                            as libc::c_int as isize,
                    ) as libc::c_int
                    & _ISpunct as libc::c_int as libc::c_ushort as libc::c_int != 0)
            {
                continue;
            }
        }
        work = rndr_newbuf(rndr, 1 as libc::c_int);
        parse_inline(work, rndr, data, i);
        r = ((*rndr).cb.emphasis)
            .expect("non-null function pointer")(ob, work, (*rndr).opaque);
        rndr_popbuf(rndr, 1 as libc::c_int);
        return if r != 0 {
            i.wrapping_add(1 as libc::c_int as size_t)
        } else {
            0 as libc::c_int as size_t
        };
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn parse_emph2(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut c: uint8_t,
) -> size_t {
    let mut render_method: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    > = None;
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut len: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    let mut r: libc::c_int = 0;
    render_method = if c as libc::c_int == '~' as i32 {
        (*rndr).cb.strikethrough
    } else {
        (*rndr).cb.double_emphasis
    };
    if render_method.is_none() {
        return 0 as libc::c_int as size_t;
    }
    while i < size {
        len = find_emph_char(data.offset(i as isize), size.wrapping_sub(i), c);
        if len == 0 {
            return 0 as libc::c_int as size_t;
        }
        i = i.wrapping_add(len);
        if i.wrapping_add(1 as libc::c_int as size_t) < size
            && *data.offset(i as isize) as libc::c_int == c as libc::c_int
            && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int == c as libc::c_int && i != 0
            && _isspace(
                *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                    as libc::c_int,
            ) == 0
        {
            work = rndr_newbuf(rndr, 1 as libc::c_int);
            parse_inline(work, rndr, data, i);
            r = render_method
                .expect("non-null function pointer")(ob, work, (*rndr).opaque);
            rndr_popbuf(rndr, 1 as libc::c_int);
            return if r != 0 {
                i.wrapping_add(2 as libc::c_int as size_t)
            } else {
                0 as libc::c_int as size_t
            };
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn parse_emph3(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut c: uint8_t,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut len: size_t = 0;
    let mut r: libc::c_int = 0;
    while i < size {
        len = find_emph_char(data.offset(i as isize), size.wrapping_sub(i), c);
        if len == 0 {
            return 0 as libc::c_int as size_t;
        }
        i = i.wrapping_add(len);
        if *data.offset(i as isize) as libc::c_int != c as libc::c_int
            || _isspace(
                *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                    as libc::c_int,
            ) != 0
        {
            continue;
        }
        if i.wrapping_add(2 as libc::c_int as size_t) < size
            && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int == c as libc::c_int
            && *data.offset(i.wrapping_add(2 as libc::c_int as size_t) as isize)
                as libc::c_int == c as libc::c_int
            && ((*rndr).cb.triple_emphasis).is_some()
        {
            let mut work: *mut buf = rndr_newbuf(rndr, 1 as libc::c_int);
            parse_inline(work, rndr, data, i);
            r = ((*rndr).cb.triple_emphasis)
                .expect("non-null function pointer")(ob, work, (*rndr).opaque);
            rndr_popbuf(rndr, 1 as libc::c_int);
            return if r != 0 {
                i.wrapping_add(3 as libc::c_int as size_t)
            } else {
                0 as libc::c_int as size_t
            };
        } else if i.wrapping_add(1 as libc::c_int as size_t) < size
            && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int == c as libc::c_int
        {
            len = parse_emph1(
                ob,
                rndr,
                data.offset(-(2 as libc::c_int as isize)),
                size.wrapping_add(2 as libc::c_int as size_t),
                c,
            );
            if len == 0 {
                return 0 as libc::c_int as size_t
            } else {
                return len.wrapping_sub(2 as libc::c_int as size_t)
            }
        } else {
            len = parse_emph2(
                ob,
                rndr,
                data.offset(-(1 as libc::c_int as isize)),
                size.wrapping_add(1 as libc::c_int as size_t),
                c,
            );
            if len == 0 {
                return 0 as libc::c_int as size_t
            } else {
                return len.wrapping_sub(1 as libc::c_int as size_t)
            }
        }
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn parse_spoilerspan(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut render_method: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    > = None;
    let mut len: size_t = 0;
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut work: *mut buf = 0 as *mut buf;
    let mut r: libc::c_int = 0;
    render_method = (*rndr).cb.spoilerspan;
    if render_method.is_none() {
        return 0 as libc::c_int as size_t;
    }
    while i < size {
        len = find_emph_char(
            data.offset(i as isize),
            size.wrapping_sub(i),
            '<' as i32 as uint8_t,
        );
        if len == 0 {
            return 0 as libc::c_int as size_t;
        }
        i = i.wrapping_add(len);
        if i < size && *data.offset(i as isize) as libc::c_int == '<' as i32
            && *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '!' as i32
        {
            work = rndr_newbuf(rndr, 1 as libc::c_int);
            parse_inline(work, rndr, data, i.wrapping_sub(1 as libc::c_int as size_t));
            r = render_method
                .expect("non-null function pointer")(ob, work, (*rndr).opaque);
            rndr_popbuf(rndr, 1 as libc::c_int);
            if r == 0 {
                return 0 as libc::c_int as size_t;
            }
            return i.wrapping_add(1 as libc::c_int as size_t);
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn char_emphasis(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut c: uint8_t = *data.offset(0 as libc::c_int as isize);
    let mut ret: size_t = 0;
    if size > 3 as libc::c_int as size_t && c as libc::c_int == '>' as i32
        && *data.offset(1 as libc::c_int as isize) as libc::c_int == '!' as i32
    {
        if _isspace(*data.offset(2 as libc::c_int as isize) as libc::c_int) != 0
            || {
                ret = parse_spoilerspan(
                    ob,
                    rndr,
                    data.offset(2 as libc::c_int as isize),
                    size.wrapping_sub(2 as libc::c_int as size_t),
                );
                ret == 0 as libc::c_int as size_t
            }
        {
            return 0 as libc::c_int as size_t;
        }
        return ret.wrapping_add(2 as libc::c_int as size_t);
    }
    if size > 2 as libc::c_int as size_t
        && *data.offset(1 as libc::c_int as isize) as libc::c_int != c as libc::c_int
    {
        if c as libc::c_int == '~' as i32 || c as libc::c_int == '>' as i32
            || _isspace(*data.offset(1 as libc::c_int as isize) as libc::c_int) != 0
            || {
                ret = parse_emph1(
                    ob,
                    rndr,
                    data.offset(1 as libc::c_int as isize),
                    size.wrapping_sub(1 as libc::c_int as size_t),
                    c,
                );
                ret == 0 as libc::c_int as size_t
            }
        {
            return 0 as libc::c_int as size_t;
        }
        return ret.wrapping_add(1 as libc::c_int as size_t);
    }
    if size > 3 as libc::c_int as size_t
        && *data.offset(1 as libc::c_int as isize) as libc::c_int == c as libc::c_int
        && *data.offset(2 as libc::c_int as isize) as libc::c_int != c as libc::c_int
    {
        if _isspace(*data.offset(2 as libc::c_int as isize) as libc::c_int) != 0
            || {
                ret = parse_emph2(
                    ob,
                    rndr,
                    data.offset(2 as libc::c_int as isize),
                    size.wrapping_sub(2 as libc::c_int as size_t),
                    c,
                );
                ret == 0 as libc::c_int as size_t
            }
        {
            return 0 as libc::c_int as size_t;
        }
        return ret.wrapping_add(2 as libc::c_int as size_t);
    }
    if size > 4 as libc::c_int as size_t
        && *data.offset(1 as libc::c_int as isize) as libc::c_int == c as libc::c_int
        && *data.offset(2 as libc::c_int as isize) as libc::c_int == c as libc::c_int
        && *data.offset(3 as libc::c_int as isize) as libc::c_int != c as libc::c_int
    {
        if c as libc::c_int == '~' as i32 || c as libc::c_int == '>' as i32
            || _isspace(*data.offset(3 as libc::c_int as isize) as libc::c_int) != 0
            || {
                ret = parse_emph3(
                    ob,
                    rndr,
                    data.offset(3 as libc::c_int as isize),
                    size.wrapping_sub(3 as libc::c_int as size_t),
                    c,
                );
                ret == 0 as libc::c_int as size_t
            }
        {
            return 0 as libc::c_int as size_t;
        }
        return ret.wrapping_add(3 as libc::c_int as size_t);
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn char_linebreak(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    if max_rewind < 2 as libc::c_int as size_t
        || *data.offset(-(1 as libc::c_int) as isize) as libc::c_int != ' ' as i32
        || *data.offset(-(2 as libc::c_int) as isize) as libc::c_int != ' ' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    while (*ob).size != 0
        && *((*ob).data)
            .offset(((*ob).size).wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == ' ' as i32
    {
        (*ob).size = ((*ob).size).wrapping_sub(1);
        (*ob).size;
    }
    return (if ((*rndr).cb.linebreak)
        .expect("non-null function pointer")(ob, (*rndr).opaque) != 0
    {
        1 as libc::c_int
    } else {
        0 as libc::c_int
    }) as size_t;
}
unsafe extern "C" fn char_codespan(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut end: size_t = 0;
    let mut nb: size_t = 0 as libc::c_int as size_t;
    let mut i: size_t = 0;
    let mut f_begin: size_t = 0;
    let mut f_end: size_t = 0;
    while nb < size && *data.offset(nb as isize) as libc::c_int == '`' as i32 {
        nb = nb.wrapping_add(1);
        nb;
    }
    i = 0 as libc::c_int as size_t;
    end = nb;
    while end < size && i < nb {
        if *data.offset(end as isize) as libc::c_int == '`' as i32 {
            i = i.wrapping_add(1);
            i;
        } else {
            i = 0 as libc::c_int as size_t;
        }
        end = end.wrapping_add(1);
        end;
    }
    if i < nb && end >= size {
        return 0 as libc::c_int as size_t;
    }
    f_begin = nb;
    while f_begin < end && *data.offset(f_begin as isize) as libc::c_int == ' ' as i32 {
        f_begin = f_begin.wrapping_add(1);
        f_begin;
    }
    f_end = end.wrapping_sub(nb);
    while f_end > nb
        && *data.offset(f_end.wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == ' ' as i32
    {
        f_end = f_end.wrapping_sub(1);
        f_end;
    }
    if f_begin < f_end {
        let mut work: buf = {
            let mut init = buf {
                data: data.offset(f_begin as isize),
                size: f_end.wrapping_sub(f_begin),
                asize: 0 as libc::c_int as size_t,
                unit: 0 as libc::c_int as size_t,
            };
            init
        };
        if ((*rndr).cb.codespan)
            .expect("non-null function pointer")(ob, &mut work, (*rndr).opaque) == 0
        {
            end = 0 as libc::c_int as size_t;
        }
    } else if ((*rndr).cb.codespan)
        .expect("non-null function pointer")(ob, 0 as *const buf, (*rndr).opaque) == 0
    {
        end = 0 as libc::c_int as size_t;
    }
    return end;
}
unsafe extern "C" fn char_escape(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    static mut escape_chars: *const libc::c_char = b"\\`*_{}[]()#+-.!:|&<>/^~\0"
        as *const u8 as *const libc::c_char;
    let mut work: buf = {
        let mut init = buf {
            data: 0 as *mut uint8_t,
            size: 0 as libc::c_int as size_t,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    if size > 1 as libc::c_int as size_t {
        if (strchr(escape_chars, *data.offset(1 as libc::c_int as isize) as libc::c_int))
            .is_null()
        {std::intrinsics::assume((strchr(escape_chars, *data.offset(1 as libc::c_int as isize) as libc::c_int)).addr() == 0);
            return 0 as libc::c_int as size_t;
        }
        if ((*rndr).cb.normal_text).is_some() {
            work.data = data.offset(1 as libc::c_int as isize);
            work.size = 1 as libc::c_int as size_t;
            ((*rndr).cb.normal_text)
                .expect("non-null function pointer")(ob, &mut work, (*rndr).opaque);
        } else {
            bufputc(ob, *data.offset(1 as libc::c_int as isize) as libc::c_int);
        }
    } else if size == 1 as libc::c_int as size_t {
        bufputc(ob, *data.offset(0 as libc::c_int as isize) as libc::c_int);
    }
    return 2 as libc::c_int as size_t;
}
unsafe extern "C" fn char_entity(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut end: size_t = 1 as libc::c_int as size_t;
    let mut content_start: size_t = 0;
    let mut content_end: size_t = 0;
    let mut work: buf = {
        let mut init = buf {
            data: 0 as *mut uint8_t,
            size: 0 as libc::c_int as size_t,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    let mut numeric: libc::c_int = 0 as libc::c_int;
    let mut hex: libc::c_int = 0 as libc::c_int;
    let mut entity_base: libc::c_int = 0;
    let mut entity_val: uint32_t = 0;
    if end < size && *data.offset(end as isize) as libc::c_int == '#' as i32 {
        numeric = 1 as libc::c_int;
        end = end.wrapping_add(1);
        end;
    }
    if end < size && numeric != 0
        && ({
            let mut __res: libc::c_int = 0;
            if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                > 1 as libc::c_int as libc::c_ulong
            {
                if 0 != 0 {
                    let mut __c: libc::c_int = *data.offset(end as isize) as libc::c_int;
                    __res = (if __c < -(128 as libc::c_int) || __c > 255 as libc::c_int {
                        __c
                    } else {
                        *(*__ctype_tolower_loc()).offset(__c as isize)
                    });
                } else {
                    __res = tolower(*data.offset(end as isize) as libc::c_int);
                }
            } else {
                __res = *(*__ctype_tolower_loc())
                    .offset(*data.offset(end as isize) as libc::c_int as isize);
            }
            __res
        }) == 'x' as i32
    {
        hex = 1 as libc::c_int;
        end = end.wrapping_add(1);
        end;
    }
    content_start = end;
    while end < size {
        let c: libc::c_char = *data.offset(end as isize) as libc::c_char;
        if hex != 0 {
            if *(*__ctype_b_loc()).offset(c as libc::c_int as isize) as libc::c_int
                & _ISxdigit as libc::c_int as libc::c_ushort as libc::c_int == 0
            {
                break;
            }
        } else if numeric != 0 {
            if *(*__ctype_b_loc()).offset(c as libc::c_int as isize) as libc::c_int
                & _ISdigit as libc::c_int as libc::c_ushort as libc::c_int == 0
            {
                break;
            }
        } else if *(*__ctype_b_loc()).offset(c as libc::c_int as isize) as libc::c_int
            & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int == 0
        {
            break;
        }
        end = end.wrapping_add(1);
        end;
    }
    content_end = end;
    if end > content_start && end < size
        && *data.offset(end as isize) as libc::c_int == ';' as i32
    {
        end = end.wrapping_add(1);
        end;
    } else {
        return 0 as libc::c_int as size_t
    }
    if numeric != 0 && content_end.wrapping_sub(content_start) > MAX_NUM_ENTITY_LEN {
        return 0 as libc::c_int as size_t;
    }
    if numeric != 0 {
        if hex != 0 {
            entity_base = 16 as libc::c_int;
        } else {
            entity_base = 10 as libc::c_int;
        }
        entity_val = strtol(
            (data as *mut libc::c_char).offset(content_start as isize),
            0 as *mut *mut libc::c_char,
            entity_base,
        ) as uint32_t;
        if is_valid_numeric_entity(entity_val) == 0 {
            return 0 as libc::c_int as size_t;
        }
    } else if (is_allowed_named_entity(data as *const libc::c_char, end)).is_null() {std::intrinsics::assume((is_allowed_named_entity(data as *const libc::c_char, end)).addr() == 0);
        return 0 as libc::c_int as size_t
    }
    if ((*rndr).cb.entity).is_some() {
        work.data = data;
        work.size = end;
        ((*rndr).cb.entity)
            .expect("non-null function pointer")(ob, &mut work, (*rndr).opaque);
    } else {
        bufputc(ob, '&' as i32);
        if numeric != 0 {
            bufputc(ob, '#' as i32);
        }
        if hex != 0 {
            bufputc(ob, 'x' as i32);
        }
        bufput(
            ob,
            data.offset(content_start as isize) as *const libc::c_void,
            end.wrapping_sub(content_start),
        );
    }
    return end;
}
unsafe extern "C" fn char_langle_tag(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut altype: mkd_autolink = MKDA_NOT_AUTOLINK;
    let mut end: size_t = tag_length(data, size, &mut altype);
    let mut work: buf = {
        let mut init = buf {
            data: data,
            size: end,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    let mut ret: libc::c_int = 0 as libc::c_int;
    if end > 2 as libc::c_int as size_t {
        if ((*rndr).cb.autolink).is_some()
            && altype as libc::c_uint != MKDA_NOT_AUTOLINK as libc::c_int as libc::c_uint
        {
            let mut u_link: *mut buf = rndr_newbuf(rndr, 1 as libc::c_int);
            work.data = data.offset(1 as libc::c_int as isize);
            work.size = end.wrapping_sub(2 as libc::c_int as size_t);
            unscape_text(u_link, &mut work);
            ret = ((*rndr).cb.autolink)
                .expect("non-null function pointer")(ob, u_link, altype, (*rndr).opaque);
            rndr_popbuf(rndr, 1 as libc::c_int);
        } else if ((*rndr).cb.raw_html_tag).is_some() {
            ret = ((*rndr).cb.raw_html_tag)
                .expect("non-null function pointer")(ob, &mut work, (*rndr).opaque);
        }
    }
    if ret == 0 { return 0 as libc::c_int as size_t } else { return end };
}
unsafe extern "C" fn char_autolink_www(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_url: *mut buf = 0 as *mut buf;
    let mut link_text: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    if ((*rndr).cb.link).is_none() || (*rndr).in_link_body != 0 {
        return 0 as libc::c_int as size_t;
    }
    link = rndr_newbuf(rndr, 1 as libc::c_int);
    link_len = sd_autolink__www(
        &mut rewind,
        link,
        data,
        max_rewind,
        size,
        0 as libc::c_int as libc::c_uint,
    );
    if link_len > 0 as libc::c_int as size_t {
        link_url = rndr_newbuf(rndr, 1 as libc::c_int);
        bufput(
            link_url,
            b"http://\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        bufput(link_url, (*link).data as *const libc::c_void, (*link).size);
        buftruncate(ob, ((*ob).size).wrapping_sub(rewind));
        if ((*rndr).cb.normal_text).is_some() {
            link_text = rndr_newbuf(rndr, 1 as libc::c_int);
            ((*rndr).cb.normal_text)
                .expect("non-null function pointer")(link_text, link, (*rndr).opaque);
            ((*rndr).cb.link)
                .expect(
                    "non-null function pointer",
                )(ob, link_url, 0 as *const buf, link_text, (*rndr).opaque);
            rndr_popbuf(rndr, 1 as libc::c_int);
        } else {
            ((*rndr).cb.link)
                .expect(
                    "non-null function pointer",
                )(ob, link_url, 0 as *const buf, link, (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as libc::c_int);
    }
    rndr_popbuf(rndr, 1 as libc::c_int);
    return link_len;
}
unsafe extern "C" fn char_autolink_subreddit_or_username(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_text: *mut buf = 0 as *mut buf;
    let mut link_url: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    let mut no_slash: libc::c_int = 0;
    if ((*rndr).cb.autolink).is_none() || (*rndr).in_link_body != 0 {
        return 0 as libc::c_int as size_t;
    }
    link = rndr_newbuf(rndr, 1 as libc::c_int);
    link_len = sd_autolink__subreddit(
        &mut rewind,
        link,
        data,
        max_rewind,
        max_lookbehind,
        size,
        &mut no_slash,
    );
    if link_len == 0 as libc::c_int as size_t {
        link_len = sd_autolink__username(
            &mut rewind,
            link,
            data,
            max_rewind,
            max_lookbehind,
            size,
            &mut no_slash,
        );
    }
    if link_len > 0 as libc::c_int as size_t {
        link_url = rndr_newbuf(rndr, 1 as libc::c_int);
        if no_slash != 0 {
            bufputc(link_url, '/' as i32);
        }
        bufput(link_url, (*link).data as *const libc::c_void, (*link).size);
        buftruncate(ob, ((*ob).size).wrapping_sub(rewind));
        if ((*rndr).cb.normal_text).is_some() {
            link_text = rndr_newbuf(rndr, 1 as libc::c_int);
            ((*rndr).cb.normal_text)
                .expect("non-null function pointer")(link_text, link, (*rndr).opaque);
            ((*rndr).cb.link)
                .expect(
                    "non-null function pointer",
                )(ob, link_url, 0 as *const buf, link_text, (*rndr).opaque);
            rndr_popbuf(rndr, 1 as libc::c_int);
        } else {
            ((*rndr).cb.link)
                .expect(
                    "non-null function pointer",
                )(ob, link_url, 0 as *const buf, link, (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as libc::c_int);
    }
    rndr_popbuf(rndr, 1 as libc::c_int);
    return link_len;
}
unsafe extern "C" fn char_autolink_email(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    if ((*rndr).cb.autolink).is_none() || (*rndr).in_link_body != 0 {
        return 0 as libc::c_int as size_t;
    }
    link = rndr_newbuf(rndr, 1 as libc::c_int);
    link_len = sd_autolink__email(
        &mut rewind,
        link,
        data,
        max_rewind,
        size,
        0 as libc::c_int as libc::c_uint,
    );
    if link_len > 0 as libc::c_int as size_t {
        buftruncate(ob, ((*ob).size).wrapping_sub(rewind));
        ((*rndr).cb.autolink)
            .expect("non-null function pointer")(ob, link, MKDA_EMAIL, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 1 as libc::c_int);
    return link_len;
}
unsafe extern "C" fn char_autolink_url(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut link: *mut buf = 0 as *mut buf;
    let mut link_len: size_t = 0;
    let mut rewind: size_t = 0;
    if ((*rndr).cb.autolink).is_none() || (*rndr).in_link_body != 0 {
        return 0 as libc::c_int as size_t;
    }
    link = rndr_newbuf(rndr, 1 as libc::c_int);
    link_len = sd_autolink__url(
        &mut rewind,
        link,
        data,
        max_rewind,
        size,
        0 as libc::c_int as libc::c_uint,
    );
    if link_len > 0 as libc::c_int as size_t {
        buftruncate(ob, ((*ob).size).wrapping_sub(rewind));
        ((*rndr).cb.autolink)
            .expect("non-null function pointer")(ob, link, MKDA_NORMAL, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 1 as libc::c_int);
    return link_len;
}
unsafe extern "C" fn char_link(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut current_block: u64;
    let mut is_img: libc::c_int = (max_rewind != 0
        && *data.offset(-(1 as libc::c_int) as isize) as libc::c_int == '!' as i32)
        as libc::c_int;
    let mut level: libc::c_int = 0;
    let mut i: size_t = 1 as libc::c_int as size_t;
    let mut txt_e: size_t = 0;
    let mut link_b: size_t = 0 as libc::c_int as size_t;
    let mut link_e: size_t = 0 as libc::c_int as size_t;
    let mut title_b: size_t = 0 as libc::c_int as size_t;
    let mut title_e: size_t = 0 as libc::c_int as size_t;
    let mut content: *mut buf = 0 as *mut buf;
    let mut link: *mut buf = 0 as *mut buf;
    let mut title: *mut buf = 0 as *mut buf;
    let mut u_link: *mut buf = 0 as *mut buf;
    let mut org_work_size: size_t = (*rndr).work_bufs[1 as libc::c_int as usize].size;
    let mut text_has_nl: libc::c_int = 0 as libc::c_int;
    let mut ret: libc::c_int = 0 as libc::c_int;
    let mut in_title: libc::c_int = 0 as libc::c_int;
    let mut qtype: libc::c_int = 0 as libc::c_int;
    if !(is_img != 0 && ((*rndr).cb.image).is_none()
        || is_img == 0 && ((*rndr).cb.link).is_none())
    {
        level = 1 as libc::c_int;
        while i < size {
            if *data.offset(i as isize) as libc::c_int == '\n' as i32 {
                text_has_nl = 1 as libc::c_int;
            } else if !(*data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '\\' as i32)
            {
                if *data.offset(i as isize) as libc::c_int == '[' as i32 {
                    level += 1;
                    level;
                } else if *data.offset(i as isize) as libc::c_int == ']' as i32 {
                    level -= 1;
                    level;
                    if level <= 0 as libc::c_int {
                        break;
                    }
                }
            }
            i = i.wrapping_add(1);
            i;
        }
        if !(i >= size) {
            txt_e = i;
            i = i.wrapping_add(1);
            i;
            while i < size && _isspace(*data.offset(i as isize) as libc::c_int) != 0 {
                i = i.wrapping_add(1);
                i;
            }
            if i < size && *data.offset(i as isize) as libc::c_int == '(' as i32 {
                i = i.wrapping_add(1);
                i;
                while i < size && _isspace(*data.offset(i as isize) as libc::c_int) != 0
                {
                    i = i.wrapping_add(1);
                    i;
                }
                link_b = i;
                while i < size {
                    if *data.offset(i as isize) as libc::c_int == '\\' as i32 {
                        i = i.wrapping_add(2 as libc::c_int as size_t);
                    } else {
                        if *data.offset(i as isize) as libc::c_int == ')' as i32 {
                            break;
                        }
                        if i >= 1 as libc::c_int as size_t
                            && _isspace(
                                *data
                                    .offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                                    as libc::c_int,
                            ) != 0
                            && (*data.offset(i as isize) as libc::c_int == '\'' as i32
                                || *data.offset(i as isize) as libc::c_int == '"' as i32)
                        {
                            break;
                        }
                        i = i.wrapping_add(1);
                        i;
                    }
                }
                if i >= size {
                    current_block = 15039610247979811031;
                } else {
                    link_e = i;
                    if *data.offset(i as isize) as libc::c_int == '\'' as i32
                        || *data.offset(i as isize) as libc::c_int == '"' as i32
                    {
                        qtype = *data.offset(i as isize) as libc::c_int;
                        in_title = 1 as libc::c_int;
                        i = i.wrapping_add(1);
                        i;
                        title_b = i;
                        while i < size {
                            if *data.offset(i as isize) as libc::c_int == '\\' as i32 {
                                i = i.wrapping_add(2 as libc::c_int as size_t);
                            } else if *data.offset(i as isize) as libc::c_int == qtype {
                                in_title = 0 as libc::c_int;
                                i = i.wrapping_add(1);
                                i;
                            } else {
                                if *data.offset(i as isize) as libc::c_int == ')' as i32
                                    && in_title == 0
                                {
                                    break;
                                }
                                i = i.wrapping_add(1);
                                i;
                            }
                        }
                        if i >= size {
                            current_block = 15039610247979811031;
                        } else {
                            title_e = i.wrapping_sub(1 as libc::c_int as size_t);
                            while title_e > title_b
                                && _isspace(*data.offset(title_e as isize) as libc::c_int)
                                    != 0
                            {
                                title_e = title_e.wrapping_sub(1);
                                title_e;
                            }
                            if *data.offset(title_e as isize) as libc::c_int
                                != '\'' as i32
                                && *data.offset(title_e as isize) as libc::c_int
                                    != '"' as i32
                            {
                                title_e = 0 as libc::c_int as size_t;
                                title_b = title_e;
                                link_e = i;
                            }
                            current_block = 6476622998065200121;
                        }
                    } else {
                        current_block = 6476622998065200121;
                    }
                    match current_block {
                        15039610247979811031 => {}
                        _ => {
                            while link_e > link_b
                                && _isspace(
                                    *data
                                        .offset(
                                            link_e.wrapping_sub(1 as libc::c_int as size_t) as isize,
                                        ) as libc::c_int,
                                ) != 0
                            {
                                link_e = link_e.wrapping_sub(1);
                                link_e;
                            }
                            if *data.offset(link_b as isize) as libc::c_int == '<' as i32
                            {
                                link_b = link_b.wrapping_add(1);
                                link_b;
                            }
                            if *data
                                .offset(
                                    link_e.wrapping_sub(1 as libc::c_int as size_t) as isize,
                                ) as libc::c_int == '>' as i32
                            {
                                link_e = link_e.wrapping_sub(1);
                                link_e;
                            }
                            if link_e > link_b {
                                link = rndr_newbuf(rndr, 1 as libc::c_int);
                                bufput(
                                    link,
                                    data.offset(link_b as isize) as *const libc::c_void,
                                    link_e.wrapping_sub(link_b),
                                );
                            }
                            if title_e > title_b {
                                title = rndr_newbuf(rndr, 1 as libc::c_int);
                                bufput(
                                    title,
                                    data.offset(title_b as isize) as *const libc::c_void,
                                    title_e.wrapping_sub(title_b),
                                );
                            }
                            i = i.wrapping_add(1);
                            i;
                            current_block = 7739940392431776979;
                        }
                    }
                }
            } else if i < size && *data.offset(i as isize) as libc::c_int == '[' as i32 {
                let mut id: buf = {
                    let mut init = buf {
                        data: 0 as *mut uint8_t,
                        size: 0 as libc::c_int as size_t,
                        asize: 0 as libc::c_int as size_t,
                        unit: 0 as libc::c_int as size_t,
                    };
                    init
                };
                let mut lr: *mut link_ref = 0 as *mut link_ref;
                i = i.wrapping_add(1);
                i;
                link_b = i;
                while i < size && *data.offset(i as isize) as libc::c_int != ']' as i32 {
                    i = i.wrapping_add(1);
                    i;
                }
                if i >= size {
                    current_block = 15039610247979811031;
                } else {
                    link_e = i;
                    if link_b == link_e {
                        if text_has_nl != 0 {
                            let mut b: *mut buf = rndr_newbuf(rndr, 1 as libc::c_int);
                            let mut j: size_t = 0;
                            j = 1 as libc::c_int as size_t;
                            while j < txt_e {
                                if *data.offset(j as isize) as libc::c_int != '\n' as i32 {
                                    bufputc(b, *data.offset(j as isize) as libc::c_int);
                                } else if *data
                                    .offset(j.wrapping_sub(1 as libc::c_int as size_t) as isize)
                                    as libc::c_int != ' ' as i32
                                {
                                    bufputc(b, ' ' as i32);
                                }
                                j = j.wrapping_add(1);
                                j;
                            }
                            id.data = (*b).data;
                            id.size = (*b).size;
                        } else {
                            id.data = data.offset(1 as libc::c_int as isize);
                            id.size = txt_e.wrapping_sub(1 as libc::c_int as size_t);
                        }
                    } else {
                        id.data = data.offset(link_b as isize);
                        id.size = link_e.wrapping_sub(link_b);
                    }
                    lr = find_link_ref(((*rndr).refs).as_mut_ptr(), id.data, id.size);
                    if lr.is_null() {std::intrinsics::assume((lr).addr() == 0);
                        current_block = 15039610247979811031;
                    } else {
                        link = (*lr).link;
                        title = (*lr).title;
                        i = i.wrapping_add(1);
                        i;
                        current_block = 7739940392431776979;
                    }
                }
            } else {
                let mut id_0: buf = {
                    let mut init = buf {
                        data: 0 as *mut uint8_t,
                        size: 0 as libc::c_int as size_t,
                        asize: 0 as libc::c_int as size_t,
                        unit: 0 as libc::c_int as size_t,
                    };
                    init
                };
                let mut lr_0: *mut link_ref = 0 as *mut link_ref;
                if text_has_nl != 0 {
                    let mut b_0: *mut buf = rndr_newbuf(rndr, 1 as libc::c_int);
                    let mut j_0: size_t = 0;
                    j_0 = 1 as libc::c_int as size_t;
                    while j_0 < txt_e {
                        if *data.offset(j_0 as isize) as libc::c_int != '\n' as i32 {
                            bufputc(b_0, *data.offset(j_0 as isize) as libc::c_int);
                        } else if *data
                            .offset(
                                j_0.wrapping_sub(1 as libc::c_int as size_t) as isize,
                            ) as libc::c_int != ' ' as i32
                        {
                            bufputc(b_0, ' ' as i32);
                        }
                        j_0 = j_0.wrapping_add(1);
                        j_0;
                    }
                    id_0.data = (*b_0).data;
                    id_0.size = (*b_0).size;
                } else {
                    id_0.data = data.offset(1 as libc::c_int as isize);
                    id_0.size = txt_e.wrapping_sub(1 as libc::c_int as size_t);
                }
                lr_0 = find_link_ref(((*rndr).refs).as_mut_ptr(), id_0.data, id_0.size);
                if lr_0.is_null() {std::intrinsics::assume((lr_0).addr() == 0);
                    current_block = 15039610247979811031;
                } else {
                    link = (*lr_0).link;
                    title = (*lr_0).title;
                    i = txt_e.wrapping_add(1 as libc::c_int as size_t);
                    current_block = 7739940392431776979;
                }
            }
            match current_block {
                15039610247979811031 => {}
                _ => {
                    if txt_e > 1 as libc::c_int as size_t {
                        content = rndr_newbuf(rndr, 1 as libc::c_int);
                        if is_img != 0 {
                            bufput(
                                content,
                                data.offset(1 as libc::c_int as isize)
                                    as *const libc::c_void,
                                txt_e.wrapping_sub(1 as libc::c_int as size_t),
                            );
                        } else {
                            (*rndr).in_link_body = 1 as libc::c_int;
                            parse_inline(
                                content,
                                rndr,
                                data.offset(1 as libc::c_int as isize),
                                txt_e.wrapping_sub(1 as libc::c_int as size_t),
                            );
                            (*rndr).in_link_body = 0 as libc::c_int;
                        }
                    }
                    if !link.is_null() {
                        u_link = rndr_newbuf(rndr, 1 as libc::c_int);
                        unscape_text(u_link, link);
                        if is_img != 0 {
                            if (*ob).size != 0
                                && *((*ob).data)
                                    .offset(
                                        ((*ob).size).wrapping_sub(1 as libc::c_int as size_t)
                                            as isize,
                                    ) as libc::c_int == '!' as i32
                            {
                                (*ob)
                                    .size = ((*ob).size)
                                    .wrapping_sub(1 as libc::c_int as size_t);
                            }
                            ret = ((*rndr).cb.image)
                                .expect(
                                    "non-null function pointer",
                                )(ob, u_link, title, content, (*rndr).opaque);
                        } else {
                            ret = ((*rndr).cb.link)
                                .expect(
                                    "non-null function pointer",
                                )(ob, u_link, title, content, (*rndr).opaque);
                        }
                    }else { std::intrinsics::assume((link).addr() == 0); }
                }
            }
        }
    }
    (*rndr)
        .work_bufs[1 as libc::c_int as usize]
        .size = org_work_size as libc::c_int as size_t;
    return if ret != 0 { i } else { 0 as libc::c_int as size_t };
}
unsafe extern "C" fn char_superscript(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
) -> size_t {
    let mut sup_start: size_t = 0;
    let mut sup_len: size_t = 0;
    let mut sup: *mut buf = 0 as *mut buf;
    if ((*rndr).cb.superscript).is_none() {
        return 0 as libc::c_int as size_t;
    }
    if size < 2 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    if *data.offset(1 as libc::c_int as isize) as libc::c_int == '(' as i32 {
        sup_len = 2 as libc::c_int as size_t;
        sup_start = sup_len;
        while sup_len < size
            && *data.offset(sup_len as isize) as libc::c_int != ')' as i32
            && *data.offset(sup_len.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\\' as i32
        {
            sup_len = sup_len.wrapping_add(1);
            sup_len;
        }
        if sup_len == size {
            return 0 as libc::c_int as size_t;
        }
    } else {
        sup_len = 1 as libc::c_int as size_t;
        sup_start = sup_len;
        while sup_len < size
            && _isspace(*data.offset(sup_len as isize) as libc::c_int) == 0
        {
            sup_len = sup_len.wrapping_add(1);
            sup_len;
        }
    }
    if sup_len.wrapping_sub(sup_start) == 0 as libc::c_int as size_t {
        return (if sup_start == 2 as libc::c_int as size_t {
            3 as libc::c_int
        } else {
            0 as libc::c_int
        }) as size_t;
    }
    sup = rndr_newbuf(rndr, 1 as libc::c_int);
    parse_inline(
        sup,
        rndr,
        data.offset(sup_start as isize),
        sup_len.wrapping_sub(sup_start),
    );
    ((*rndr).cb.superscript)
        .expect("non-null function pointer")(ob, sup, (*rndr).opaque);
    rndr_popbuf(rndr, 1 as libc::c_int);
    return if sup_start == 2 as libc::c_int as size_t {
        sup_len.wrapping_add(1 as libc::c_int as size_t)
    } else {
        sup_len
    };
}
unsafe extern "C" fn is_empty(mut data: *mut uint8_t, mut size: size_t) -> size_t {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < size && *data.offset(i as isize) as libc::c_int != '\n' as i32 {
        if *data.offset(i as isize) as libc::c_int != ' ' as i32 {
            return 0 as libc::c_int as size_t;
        }
        i = i.wrapping_add(1);
        i;
    }
    return i.wrapping_add(1 as libc::c_int as size_t);
}
unsafe extern "C" fn is_hrule(mut data: *mut uint8_t, mut size: size_t) -> libc::c_int {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut n: size_t = 0 as libc::c_int as size_t;
    let mut c: uint8_t = 0;
    if size < 3 as libc::c_int as size_t {
        return 0 as libc::c_int;
    }
    if *data.offset(0 as libc::c_int as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
        if *data.offset(1 as libc::c_int as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
            if *data.offset(2 as libc::c_int as isize) as libc::c_int == ' ' as i32 {
                i = i.wrapping_add(1);
                i;
            }
        }
    }
    if i.wrapping_add(2 as libc::c_int as size_t) >= size
        || *data.offset(i as isize) as libc::c_int != '*' as i32
            && *data.offset(i as isize) as libc::c_int != '-' as i32
            && *data.offset(i as isize) as libc::c_int != '_' as i32
    {
        return 0 as libc::c_int;
    }
    c = *data.offset(i as isize);
    while i < size && *data.offset(i as isize) as libc::c_int != '\n' as i32 {
        if *data.offset(i as isize) as libc::c_int == c as libc::c_int {
            n = n.wrapping_add(1);
            n;
        } else if *data.offset(i as isize) as libc::c_int != ' ' as i32 {
            return 0 as libc::c_int
        }
        i = i.wrapping_add(1);
        i;
    }
    return (n >= 3 as libc::c_int as size_t) as libc::c_int;
}
unsafe extern "C" fn prefix_codefence(
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut n: size_t = 0 as libc::c_int as size_t;
    let mut c: uint8_t = 0;
    if size < 3 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    if *data.offset(0 as libc::c_int as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
        if *data.offset(1 as libc::c_int as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
            if *data.offset(2 as libc::c_int as isize) as libc::c_int == ' ' as i32 {
                i = i.wrapping_add(1);
                i;
            }
        }
    }
    if i.wrapping_add(2 as libc::c_int as size_t) >= size
        || !(*data.offset(i as isize) as libc::c_int == '~' as i32
            || *data.offset(i as isize) as libc::c_int == '`' as i32)
    {
        return 0 as libc::c_int as size_t;
    }
    c = *data.offset(i as isize);
    while i < size && *data.offset(i as isize) as libc::c_int == c as libc::c_int {
        n = n.wrapping_add(1);
        n;
        i = i.wrapping_add(1);
        i;
    }
    if n < 3 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    return i;
}
unsafe extern "C" fn is_codefence(
    mut data: *mut uint8_t,
    mut size: size_t,
    mut syntax: *mut buf,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut syn_len: size_t = 0 as libc::c_int as size_t;
    let mut syn_start: *mut uint8_t = 0 as *mut uint8_t;
    i = prefix_codefence(data, size);
    if i == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    while i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    syn_start = data.offset(i as isize);
    if i < size && *data.offset(i as isize) as libc::c_int == '{' as i32 {
        i = i.wrapping_add(1);
        i;
        syn_start = syn_start.offset(1);
        syn_start;
        while i < size && *data.offset(i as isize) as libc::c_int != '}' as i32
            && *data.offset(i as isize) as libc::c_int != '\n' as i32
        {
            syn_len = syn_len.wrapping_add(1);
            syn_len;
            i = i.wrapping_add(1);
            i;
        }
        if i == size || *data.offset(i as isize) as libc::c_int != '}' as i32 {
            return 0 as libc::c_int as size_t;
        }
        while syn_len > 0 as libc::c_int as size_t
            && _isspace(*syn_start.offset(0 as libc::c_int as isize) as libc::c_int) != 0
        {
            syn_start = syn_start.offset(1);
            syn_start;
            syn_len = syn_len.wrapping_sub(1);
            syn_len;
        }
        while syn_len > 0 as libc::c_int as size_t
            && _isspace(
                *syn_start
                    .offset(syn_len.wrapping_sub(1 as libc::c_int as size_t) as isize)
                    as libc::c_int,
            ) != 0
        {
            syn_len = syn_len.wrapping_sub(1);
            syn_len;
        }
        i = i.wrapping_add(1);
        i;
    } else {
        while i < size && _isspace(*data.offset(i as isize) as libc::c_int) == 0 {
            syn_len = syn_len.wrapping_add(1);
            syn_len;
            i = i.wrapping_add(1);
            i;
        }
    }
    if !syntax.is_null() {
        (*syntax).data = syn_start;
        (*syntax).size = syn_len;
    }else { std::intrinsics::assume((syntax).addr() == 0); }
    while i < size && *data.offset(i as isize) as libc::c_int != '\n' as i32 {
        if _isspace(*data.offset(i as isize) as libc::c_int) == 0 {
            return 0 as libc::c_int as size_t;
        }
        i = i.wrapping_add(1);
        i;
    }
    return i.wrapping_add(1 as libc::c_int as size_t);
}
unsafe extern "C" fn is_atxheader(
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> libc::c_int {
    if *data.offset(0 as libc::c_int as isize) as libc::c_int != '#' as i32 {
        return 0 as libc::c_int;
    }
    if (*rndr).ext_flags & MKDEXT_SPACE_HEADERS as libc::c_int as libc::c_uint != 0 {
        let mut level: size_t = 0 as libc::c_int as size_t;
        while level < size && level < 6 as libc::c_int as size_t
            && *data.offset(level as isize) as libc::c_int == '#' as i32
        {
            level = level.wrapping_add(1);
            level;
        }
        if level < size && *data.offset(level as isize) as libc::c_int != ' ' as i32 {
            return 0 as libc::c_int;
        }
    }
    return 1 as libc::c_int;
}
unsafe extern "C" fn is_headerline(
    mut data: *mut uint8_t,
    mut size: size_t,
) -> libc::c_int {
    let mut i: size_t = 0 as libc::c_int as size_t;
    if *data.offset(i as isize) as libc::c_int == '=' as i32 {
        i = 1 as libc::c_int as size_t;
        while i < size && *data.offset(i as isize) as libc::c_int == '=' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        while i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        return if i >= size || *data.offset(i as isize) as libc::c_int == '\n' as i32 {
            1 as libc::c_int
        } else {
            0 as libc::c_int
        };
    }
    if *data.offset(i as isize) as libc::c_int == '-' as i32 {
        i = 1 as libc::c_int as size_t;
        while i < size && *data.offset(i as isize) as libc::c_int == '-' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        while i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        return if i >= size || *data.offset(i as isize) as libc::c_int == '\n' as i32 {
            2 as libc::c_int
        } else {
            0 as libc::c_int
        };
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn is_next_headerline(
    mut data: *mut uint8_t,
    mut size: size_t,
) -> libc::c_int {
    let mut i: size_t = 0 as libc::c_int as size_t;
    while i < size && *data.offset(i as isize) as libc::c_int != '\n' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    i = i.wrapping_add(1);
    if i >= size {
        return 0 as libc::c_int;
    }
    return is_headerline(data.offset(i as isize), size.wrapping_sub(i));
}
unsafe extern "C" fn prefix_quote(mut data: *mut uint8_t, mut size: size_t) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == '>' as i32
        && (i.wrapping_add(1 as libc::c_int as size_t) < size
            && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '!' as i32)
    {
        if i.wrapping_add(1 as libc::c_int as size_t) < size
            && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int == ' ' as i32
        {
            return i.wrapping_add(2 as libc::c_int as size_t);
        }
        return i.wrapping_add(1 as libc::c_int as size_t);
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn prefix_blockspoiler(
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i.wrapping_add(1 as libc::c_int as size_t) < size
        && *data.offset(i as isize) as libc::c_int == '>' as i32
        && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '!' as i32
    {
        let mut spoilerspan: size_t = find_emph_char(
            data.offset(i as isize).offset(1 as libc::c_int as isize),
            size.wrapping_sub(i).wrapping_sub(1 as libc::c_int as size_t),
            '<' as i32 as uint8_t,
        );
        if i.wrapping_add(spoilerspan) < size && spoilerspan > 0 as libc::c_int as size_t
            && *data.offset(i.wrapping_add(spoilerspan) as isize) as libc::c_int
                == '!' as i32
        {
            return 0 as libc::c_int as size_t;
        }
        if i.wrapping_add(2 as libc::c_int as size_t) < size
            && *data.offset(i.wrapping_add(2 as libc::c_int as size_t) as isize)
                as libc::c_int == ' ' as i32
        {
            return i.wrapping_add(3 as libc::c_int as size_t);
        }
        return i.wrapping_add(2 as libc::c_int as size_t);
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn prefix_code(mut data: *mut uint8_t, mut size: size_t) -> size_t {
    if size > 3 as libc::c_int as size_t
        && *data.offset(0 as libc::c_int as isize) as libc::c_int == ' ' as i32
        && *data.offset(1 as libc::c_int as isize) as libc::c_int == ' ' as i32
        && *data.offset(2 as libc::c_int as isize) as libc::c_int == ' ' as i32
        && *data.offset(3 as libc::c_int as isize) as libc::c_int == ' ' as i32
    {
        return 4 as libc::c_int as size_t;
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn prefix_oli(mut data: *mut uint8_t, mut size: size_t) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i >= size || (*data.offset(i as isize) as libc::c_int) < '0' as i32
        || *data.offset(i as isize) as libc::c_int > '9' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    while i < size && *data.offset(i as isize) as libc::c_int >= '0' as i32
        && *data.offset(i as isize) as libc::c_int <= '9' as i32
    {
        i = i.wrapping_add(1);
        i;
    }
    if i.wrapping_add(1 as libc::c_int as size_t) >= size
        || *data.offset(i as isize) as libc::c_int != '.' as i32
        || *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
            as libc::c_int != ' ' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    if is_next_headerline(data.offset(i as isize), size.wrapping_sub(i)) != 0 {
        return 0 as libc::c_int as size_t;
    }
    return i.wrapping_add(2 as libc::c_int as size_t);
}
unsafe extern "C" fn prefix_uli(mut data: *mut uint8_t, mut size: size_t) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i.wrapping_add(1 as libc::c_int as size_t) >= size
        || *data.offset(i as isize) as libc::c_int != '*' as i32
            && *data.offset(i as isize) as libc::c_int != '+' as i32
            && *data.offset(i as isize) as libc::c_int != '-' as i32
        || *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
            as libc::c_int != ' ' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    if is_next_headerline(data.offset(i as isize), size.wrapping_sub(i)) != 0 {
        return 0 as libc::c_int as size_t;
    }
    return i.wrapping_add(2 as libc::c_int as size_t);
}
unsafe extern "C" fn parse_blockquote(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut beg: size_t = 0;
    let mut end: size_t = 0 as libc::c_int as size_t;
    let mut pre: size_t = 0;
    let mut work_size: size_t = 0 as libc::c_int as size_t;
    let mut work_data: *mut uint8_t = 0 as *mut uint8_t;
    let mut out: *mut buf = 0 as *mut buf;
    out = rndr_newbuf(rndr, 0 as libc::c_int);
    beg = 0 as libc::c_int as size_t;
    while beg < size {
        end = beg.wrapping_add(1 as libc::c_int as size_t);
        while end < size
            && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\n' as i32
        {
            end = end.wrapping_add(1);
            end;
        }
        pre = prefix_quote(data.offset(beg as isize), end.wrapping_sub(beg));
        if pre != 0 {
            beg = beg.wrapping_add(pre);
        } else if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0
            && (end >= size
                || prefix_quote(data.offset(end as isize), size.wrapping_sub(end))
                    == 0 as libc::c_int as size_t
                    && is_empty(data.offset(end as isize), size.wrapping_sub(end)) == 0)
        {
            break;
        }
        if beg < end {
            if work_data.is_null() {std::intrinsics::assume((work_data).addr() == 0);
                work_data = data.offset(beg as isize);
            } else if data.offset(beg as isize) != work_data.offset(work_size as isize) {
                memmove(
                    work_data.offset(work_size as isize) as *mut libc::c_void,
                    data.offset(beg as isize) as *const libc::c_void,
                    end.wrapping_sub(beg),
                );
            }
            work_size = work_size.wrapping_add(end.wrapping_sub(beg));
        }
        beg = end;
    }
    parse_block(out, rndr, work_data, work_size);
    if ((*rndr).cb.blockquote).is_some() {
        ((*rndr).cb.blockquote)
            .expect("non-null function pointer")(ob, out, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as libc::c_int);
    return end;
}
unsafe extern "C" fn parse_blockspoiler(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut beg: size_t = 0;
    let mut end: size_t = 0 as libc::c_int as size_t;
    let mut pre: size_t = 0;
    let mut work_size: size_t = 0 as libc::c_int as size_t;
    let mut work_data: *mut uint8_t = 0 as *mut uint8_t;
    let mut out: *mut buf = 0 as *mut buf;
    out = rndr_newbuf(rndr, 0 as libc::c_int);
    beg = 0 as libc::c_int as size_t;
    while beg < size {
        end = beg.wrapping_add(1 as libc::c_int as size_t);
        while end < size
            && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\n' as i32
        {
            end = end.wrapping_add(1);
            end;
        }
        pre = prefix_blockspoiler(data.offset(beg as isize), end.wrapping_sub(beg));
        if pre != 0 {
            beg = beg.wrapping_add(pre);
        } else if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0
            && (end >= size
                || prefix_blockspoiler(data.offset(end as isize), size.wrapping_sub(end))
                    == 0 as libc::c_int as size_t
                    && is_empty(data.offset(end as isize), size.wrapping_sub(end)) == 0)
        {
            break;
        }
        if beg < end {
            if work_data.is_null() {std::intrinsics::assume((work_data).addr() == 0);
                work_data = data.offset(beg as isize);
            } else if data.offset(beg as isize) != work_data.offset(work_size as isize) {
                memmove(
                    work_data.offset(work_size as isize) as *mut libc::c_void,
                    data.offset(beg as isize) as *const libc::c_void,
                    end.wrapping_sub(beg),
                );
            }
            work_size = work_size.wrapping_add(end.wrapping_sub(beg));
        }
        beg = end;
    }
    parse_block(out, rndr, work_data, work_size);
    if ((*rndr).cb.blockspoiler).is_some() {
        ((*rndr).cb.blockspoiler)
            .expect("non-null function pointer")(ob, out, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as libc::c_int);
    return end;
}
unsafe extern "C" fn parse_paragraph(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut end: size_t = 0 as libc::c_int as size_t;
    let mut level: libc::c_int = 0 as libc::c_int;
    let mut work: buf = {
        let mut init = buf {
            data: data,
            size: 0 as libc::c_int as size_t,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    while i < size {
        end = i.wrapping_add(1 as libc::c_int as size_t);
        while end < size
            && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\n' as i32
        {
            end = end.wrapping_add(1);
            end;
        }
        if prefix_quote(data.offset(i as isize), end.wrapping_sub(i))
            != 0 as libc::c_int as size_t
        {
            end = i;
            break;
        } else {
            if is_empty(data.offset(i as isize), size.wrapping_sub(i)) != 0 {
                break;
            }
            level = is_headerline(data.offset(i as isize), size.wrapping_sub(i));
            if level != 0 as libc::c_int {
                break;
            }
            if is_atxheader(rndr, data.offset(i as isize), size.wrapping_sub(i)) != 0
                || is_hrule(data.offset(i as isize), size.wrapping_sub(i)) != 0
                || prefix_quote(data.offset(i as isize), size.wrapping_sub(i)) != 0
            {
                end = i;
                break;
            } else {
                if (*rndr).ext_flags & MKDEXT_LAX_SPACING as libc::c_int as libc::c_uint
                    != 0
                    && *(*__ctype_b_loc())
                        .offset(*data.offset(i as isize) as libc::c_int as isize)
                        as libc::c_int
                        & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int == 0
                {
                    if prefix_oli(data.offset(i as isize), size.wrapping_sub(i)) != 0
                        || prefix_uli(data.offset(i as isize), size.wrapping_sub(i)) != 0
                    {
                        end = i;
                        break;
                    } else if *data.offset(i as isize) as libc::c_int == '<' as i32
                        && ((*rndr).cb.blockhtml).is_some()
                        && parse_htmlblock(
                            ob,
                            rndr,
                            data.offset(i as isize),
                            size.wrapping_sub(i),
                            0 as libc::c_int,
                        ) != 0
                    {
                        end = i;
                        break;
                    } else if (*rndr).ext_flags
                        & MKDEXT_FENCED_CODE as libc::c_int as libc::c_uint
                        != 0 as libc::c_int as libc::c_uint
                        && is_codefence(
                            data.offset(i as isize),
                            size.wrapping_sub(i),
                            0 as *mut buf,
                        ) != 0 as libc::c_int as size_t
                    {
                        end = i;
                        break;
                    }
                }
                i = end;
            }
        }
    }
    work.size = i;
    while work.size != 0
        && *data.offset((work.size).wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '\n' as i32
    {
        work.size = (work.size).wrapping_sub(1);
        work.size;
    }
    if level == 0 {
        let mut tmp: *mut buf = rndr_newbuf(rndr, 0 as libc::c_int);
        parse_inline(tmp, rndr, work.data, work.size);
        if ((*rndr).cb.paragraph).is_some() {
            ((*rndr).cb.paragraph)
                .expect("non-null function pointer")(ob, tmp, (*rndr).opaque);
        }
        rndr_popbuf(rndr, 0 as libc::c_int);
    } else {
        let mut header_work: *mut buf = 0 as *mut buf;
        if work.size != 0 {
            let mut beg: size_t = 0;
            i = work.size;
            work.size = (work.size).wrapping_sub(1 as libc::c_int as size_t);
            while work.size != 0
                && *data.offset(work.size as isize) as libc::c_int != '\n' as i32
            {
                work.size = (work.size).wrapping_sub(1 as libc::c_int as size_t);
            }
            beg = (work.size).wrapping_add(1 as libc::c_int as size_t);
            while work.size != 0
                && *data
                    .offset(
                        (work.size).wrapping_sub(1 as libc::c_int as size_t) as isize,
                    ) as libc::c_int == '\n' as i32
            {
                work.size = (work.size).wrapping_sub(1 as libc::c_int as size_t);
            }
            if work.size > 0 as libc::c_int as size_t {
                let mut tmp_0: *mut buf = rndr_newbuf(rndr, 0 as libc::c_int);
                parse_inline(tmp_0, rndr, work.data, work.size);
                if ((*rndr).cb.paragraph).is_some() {
                    ((*rndr).cb.paragraph)
                        .expect("non-null function pointer")(ob, tmp_0, (*rndr).opaque);
                }
                rndr_popbuf(rndr, 0 as libc::c_int);
                work.data = (work.data).offset(beg as isize);
                work.size = i.wrapping_sub(beg);
            } else {
                work.size = i;
            }
        }
        header_work = rndr_newbuf(rndr, 1 as libc::c_int);
        parse_inline(header_work, rndr, work.data, work.size);
        if ((*rndr).cb.header).is_some() {
            ((*rndr).cb.header)
                .expect(
                    "non-null function pointer",
                )(ob, header_work, level, (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as libc::c_int);
    }
    return end;
}
unsafe extern "C" fn parse_fencedcode(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    let mut lang: buf = {
        let mut init = buf {
            data: 0 as *mut uint8_t,
            size: 0 as libc::c_int as size_t,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    beg = is_codefence(data, size, &mut lang);
    if beg == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    work = rndr_newbuf(rndr, 0 as libc::c_int);
    while beg < size {
        let mut fence_end: size_t = 0;
        let mut fence_trail: buf = {
            let mut init = buf {
                data: 0 as *mut uint8_t,
                size: 0 as libc::c_int as size_t,
                asize: 0 as libc::c_int as size_t,
                unit: 0 as libc::c_int as size_t,
            };
            init
        };
        fence_end = is_codefence(
            data.offset(beg as isize),
            size.wrapping_sub(beg),
            &mut fence_trail,
        );
        if fence_end != 0 as libc::c_int as size_t
            && fence_trail.size == 0 as libc::c_int as size_t
        {
            beg = beg.wrapping_add(fence_end);
            break;
        } else {
            end = beg.wrapping_add(1 as libc::c_int as size_t);
            while end < size
                && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                    as libc::c_int != '\n' as i32
            {
                end = end.wrapping_add(1);
                end;
            }
            if beg < end {
                if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0 {
                    bufputc(work, '\n' as i32);
                } else {
                    bufput(
                        work,
                        data.offset(beg as isize) as *const libc::c_void,
                        end.wrapping_sub(beg),
                    );
                }
            }
            beg = end;
        }
    }
    if (*work).size != 0
        && *((*work).data)
            .offset(((*work).size).wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int != '\n' as i32
    {
        bufputc(work, '\n' as i32);
    }
    if ((*rndr).cb.blockcode).is_some() {
        ((*rndr).cb.blockcode)
            .expect(
                "non-null function pointer",
            )(
            ob,
            work,
            if lang.size != 0 { &mut lang } else { 0 as *mut buf },
            (*rndr).opaque,
        );
    }
    rndr_popbuf(rndr, 0 as libc::c_int);
    return beg;
}
unsafe extern "C" fn parse_blockcode(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let mut pre: size_t = 0;
    let mut work: *mut buf = 0 as *mut buf;
    work = rndr_newbuf(rndr, 0 as libc::c_int);
    beg = 0 as libc::c_int as size_t;
    while beg < size {
        end = beg.wrapping_add(1 as libc::c_int as size_t);
        while end < size
            && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\n' as i32
        {
            end = end.wrapping_add(1);
            end;
        }
        pre = prefix_code(data.offset(beg as isize), end.wrapping_sub(beg));
        if pre != 0 {
            beg = beg.wrapping_add(pre);
        } else if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) == 0 {
            break;
        }
        if beg < end {
            if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0 {
                bufputc(work, '\n' as i32);
            } else {
                bufput(
                    work,
                    data.offset(beg as isize) as *const libc::c_void,
                    end.wrapping_sub(beg),
                );
            }
        }
        beg = end;
    }
    while (*work).size != 0
        && *((*work).data)
            .offset(((*work).size).wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '\n' as i32
    {
        (*work).size = ((*work).size).wrapping_sub(1 as libc::c_int as size_t);
    }
    bufputc(work, '\n' as i32);
    if ((*rndr).cb.blockcode).is_some() {
        ((*rndr).cb.blockcode)
            .expect(
                "non-null function pointer",
            )(ob, work, 0 as *const buf, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as libc::c_int);
    return beg;
}
unsafe extern "C" fn parse_listitem(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut flags: *mut libc::c_int,
) -> size_t {
    let mut work: *mut buf = 0 as *mut buf;
    let mut inter: *mut buf = 0 as *mut buf;
    let mut beg: size_t = 0 as libc::c_int as size_t;
    let mut end: size_t = 0;
    let mut pre: size_t = 0;
    let mut sublist: size_t = 0 as libc::c_int as size_t;
    let mut orgpre: size_t = 0 as libc::c_int as size_t;
    let mut i: size_t = 0;
    let mut in_empty: libc::c_int = 0 as libc::c_int;
    let mut has_inside_empty: libc::c_int = 0 as libc::c_int;
    let mut in_fence: libc::c_int = 0 as libc::c_int;
    while orgpre < 3 as libc::c_int as size_t && orgpre < size
        && *data.offset(orgpre as isize) as libc::c_int == ' ' as i32
    {
        orgpre = orgpre.wrapping_add(1);
        orgpre;
    }
    beg = prefix_uli(data, size);
    if beg == 0 {
        beg = prefix_oli(data, size);
    }
    if beg == 0 {
        return 0 as libc::c_int as size_t;
    }
    end = beg;
    while end < size
        && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int != '\n' as i32
    {
        end = end.wrapping_add(1);
        end;
    }
    work = rndr_newbuf(rndr, 1 as libc::c_int);
    inter = rndr_newbuf(rndr, 1 as libc::c_int);
    bufput(
        work,
        data.offset(beg as isize) as *const libc::c_void,
        end.wrapping_sub(beg),
    );
    beg = end;
    while beg < size {
        let mut has_next_uli: size_t = 0 as libc::c_int as size_t;
        let mut has_next_oli: size_t = 0 as libc::c_int as size_t;
        end = end.wrapping_add(1);
        end;
        while end < size
            && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\n' as i32
        {
            end = end.wrapping_add(1);
            end;
        }
        if is_empty(data.offset(beg as isize), end.wrapping_sub(beg)) != 0 {
            in_empty = 1 as libc::c_int;
            beg = end;
        } else {
            i = 0 as libc::c_int as size_t;
            while i < 4 as libc::c_int as size_t && beg.wrapping_add(i) < end
                && *data.offset(beg.wrapping_add(i) as isize) as libc::c_int
                    == ' ' as i32
            {
                i = i.wrapping_add(1);
                i;
            }
            pre = i;
            if (*rndr).ext_flags & MKDEXT_FENCED_CODE as libc::c_int as libc::c_uint != 0
            {
                if is_codefence(
                    data.offset(beg as isize).offset(i as isize),
                    end.wrapping_sub(beg).wrapping_sub(i),
                    0 as *mut buf,
                ) != 0 as libc::c_int as size_t
                {
                    in_fence = (in_fence == 0) as libc::c_int;
                }
            }
            if in_fence == 0 {
                has_next_uli = prefix_uli(
                    data.offset(beg as isize).offset(i as isize),
                    end.wrapping_sub(beg).wrapping_sub(i),
                );
                has_next_oli = prefix_oli(
                    data.offset(beg as isize).offset(i as isize),
                    end.wrapping_sub(beg).wrapping_sub(i),
                );
            }
            if in_empty != 0
                && (*flags & 1 as libc::c_int != 0 && has_next_uli != 0
                    || *flags & 1 as libc::c_int == 0 && has_next_oli != 0)
            {
                *flags |= 8 as libc::c_int;
                break;
            } else {
                if has_next_uli != 0
                    && is_hrule(
                        data.offset(beg as isize).offset(i as isize),
                        end.wrapping_sub(beg).wrapping_sub(i),
                    ) == 0 || has_next_oli != 0
                {
                    if in_empty != 0 {
                        has_inside_empty = 1 as libc::c_int;
                    }
                    if pre == orgpre {
                        break;
                    }
                    if sublist == 0 {
                        sublist = (*work).size;
                    }
                } else if in_empty != 0 && pre == 0 as libc::c_int as size_t {
                    *flags |= 8 as libc::c_int;
                    break;
                } else if in_empty != 0 {
                    bufputc(work, '\n' as i32);
                    has_inside_empty = 1 as libc::c_int;
                }
                in_empty = 0 as libc::c_int;
                bufput(
                    work,
                    data.offset(beg as isize).offset(i as isize) as *const libc::c_void,
                    end.wrapping_sub(beg).wrapping_sub(i),
                );
                beg = end;
            }
        }
    }
    if has_inside_empty != 0 {
        *flags |= 2 as libc::c_int;
    }
    if *flags & 2 as libc::c_int != 0 {
        if sublist != 0 && sublist < (*work).size {
            parse_block(inter, rndr, (*work).data, sublist);
            parse_block(
                inter,
                rndr,
                ((*work).data).offset(sublist as isize),
                ((*work).size).wrapping_sub(sublist),
            );
        } else {
            parse_block(inter, rndr, (*work).data, (*work).size);
        }
    } else if sublist != 0 && sublist < (*work).size {
        parse_inline(inter, rndr, (*work).data, sublist);
        parse_block(
            inter,
            rndr,
            ((*work).data).offset(sublist as isize),
            ((*work).size).wrapping_sub(sublist),
        );
    } else {
        parse_inline(inter, rndr, (*work).data, (*work).size);
    }
    if ((*rndr).cb.listitem).is_some() {
        ((*rndr).cb.listitem)
            .expect("non-null function pointer")(ob, inter, *flags, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 1 as libc::c_int);
    rndr_popbuf(rndr, 1 as libc::c_int);
    return beg;
}
unsafe extern "C" fn parse_list(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut flags: libc::c_int,
) -> size_t {
    let mut work: *mut buf = 0 as *mut buf;
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut j: size_t = 0;
    work = rndr_newbuf(rndr, 0 as libc::c_int);
    while i < size {
        j = parse_listitem(
            work,
            rndr,
            data.offset(i as isize),
            size.wrapping_sub(i),
            &mut flags,
        );
        i = i.wrapping_add(j);
        if j == 0 || flags & 8 as libc::c_int != 0 {
            break;
        }
    }
    if ((*rndr).cb.list).is_some() {
        ((*rndr).cb.list)
            .expect("non-null function pointer")(ob, work, flags, (*rndr).opaque);
    }
    rndr_popbuf(rndr, 0 as libc::c_int);
    return i;
}
unsafe extern "C" fn parse_atxheader(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut level: size_t = 0 as libc::c_int as size_t;
    let mut i: size_t = 0;
    let mut end: size_t = 0;
    let mut skip: size_t = 0;
    while level < size && level < 6 as libc::c_int as size_t
        && *data.offset(level as isize) as libc::c_int == '#' as i32
    {
        level = level.wrapping_add(1);
        level;
    }
    i = level;
    while i < size && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    end = i;
    while end < size && *data.offset(end as isize) as libc::c_int != '\n' as i32 {
        end = end.wrapping_add(1);
        end;
    }
    skip = end;
    while end != 0
        && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '#' as i32
    {
        end = end.wrapping_sub(1);
        end;
    }
    while end != 0
        && *data.offset(end.wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == ' ' as i32
    {
        end = end.wrapping_sub(1);
        end;
    }
    if end > i {
        let mut work: *mut buf = rndr_newbuf(rndr, 1 as libc::c_int);
        parse_inline(work, rndr, data.offset(i as isize), end.wrapping_sub(i));
        if ((*rndr).cb.header).is_some() {
            ((*rndr).cb.header)
                .expect(
                    "non-null function pointer",
                )(ob, work, level as libc::c_int, (*rndr).opaque);
        }
        rndr_popbuf(rndr, 1 as libc::c_int);
    }
    return skip;
}
unsafe extern "C" fn htmlblock_end_tag(
    mut tag: *const libc::c_char,
    mut tag_len: size_t,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut i: size_t = 0;
    let mut w: size_t = 0;
    if tag_len.wrapping_add(3 as libc::c_int as size_t) >= size
        || strncasecmp(
            (data as *mut libc::c_char).offset(2 as libc::c_int as isize),
            tag,
            tag_len,
        ) != 0 as libc::c_int
        || *data.offset(tag_len.wrapping_add(2 as libc::c_int as size_t) as isize)
            as libc::c_int != '>' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    i = tag_len.wrapping_add(3 as libc::c_int as size_t);
    w = 0 as libc::c_int as size_t;
    if i < size
        && {
            w = is_empty(data.offset(i as isize), size.wrapping_sub(i));
            w == 0 as libc::c_int as size_t
        }
    {
        return 0 as libc::c_int as size_t;
    }
    i = i.wrapping_add(w);
    w = 0 as libc::c_int as size_t;
    if i < size {
        w = is_empty(data.offset(i as isize), size.wrapping_sub(i));
    }
    return i.wrapping_add(w);
}
unsafe extern "C" fn htmlblock_end(
    mut curtag: *const libc::c_char,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut start_of_line: libc::c_int,
) -> size_t {
    let mut tag_size: size_t = strlen(curtag);
    let mut i: size_t = 1 as libc::c_int as size_t;
    let mut end_tag: size_t = 0;
    let mut block_lines: libc::c_int = 0 as libc::c_int;
    while i < size {
        i = i.wrapping_add(1);
        i;
        while i < size
            && !(*data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '<' as i32
                && *data.offset(i as isize) as libc::c_int == '/' as i32)
        {
            if *data.offset(i as isize) as libc::c_int == '\n' as i32 {
                block_lines += 1;
                block_lines;
            }
            i = i.wrapping_add(1);
            i;
        }
        if start_of_line != 0 && block_lines > 0 as libc::c_int
            && *data.offset(i.wrapping_sub(2 as libc::c_int as size_t) as isize)
                as libc::c_int != '\n' as i32
        {
            continue;
        }
        if i.wrapping_add(2 as libc::c_int as size_t).wrapping_add(tag_size) >= size {
            break;
        }
        end_tag = htmlblock_end_tag(
            curtag,
            tag_size,
            rndr,
            data.offset(i as isize).offset(-(1 as libc::c_int as isize)),
            size.wrapping_sub(i).wrapping_add(1 as libc::c_int as size_t),
        );
        if end_tag != 0 {
            return i.wrapping_add(end_tag).wrapping_sub(1 as libc::c_int as size_t);
        }
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn parse_htmlblock(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut do_render: libc::c_int,
) -> size_t {
    let mut i: size_t = 0;
    let mut j: size_t = 0 as libc::c_int as size_t;
    let mut tag_end: size_t = 0;
    let mut curtag: *const libc::c_char = 0 as *const libc::c_char;
    let mut work: buf = {
        let mut init = buf {
            data: data,
            size: 0 as libc::c_int as size_t,
            asize: 0 as libc::c_int as size_t,
            unit: 0 as libc::c_int as size_t,
        };
        init
    };
    if size < 2 as libc::c_int as size_t
        || *data.offset(0 as libc::c_int as isize) as libc::c_int != '<' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    i = 1 as libc::c_int as size_t;
    while i < size && *data.offset(i as isize) as libc::c_int != '>' as i32
        && *data.offset(i as isize) as libc::c_int != ' ' as i32
    {
        i = i.wrapping_add(1);
        i;
    }
    if i < size {
        curtag = find_block_tag(
            (data as *mut libc::c_char).offset(1 as libc::c_int as isize),
            (i as libc::c_int - 1 as libc::c_int) as libc::c_uint,
        );
    }
    if curtag.is_null() {std::intrinsics::assume((curtag).addr() == 0);
        if size > 5 as libc::c_int as size_t
            && *data.offset(1 as libc::c_int as isize) as libc::c_int == '!' as i32
            && *data.offset(2 as libc::c_int as isize) as libc::c_int == '-' as i32
            && *data.offset(3 as libc::c_int as isize) as libc::c_int == '-' as i32
        {
            i = 5 as libc::c_int as size_t;
            while i < size
                && !(*data.offset(i.wrapping_sub(2 as libc::c_int as size_t) as isize)
                    as libc::c_int == '-' as i32
                    && *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                        as libc::c_int == '-' as i32
                    && *data.offset(i as isize) as libc::c_int == '>' as i32)
            {
                i = i.wrapping_add(1);
                i;
            }
            i = i.wrapping_add(1);
            i;
            if i < size {
                j = is_empty(data.offset(i as isize), size.wrapping_sub(i));
            }
            if j != 0 {
                work.size = i.wrapping_add(j);
                if do_render != 0 && ((*rndr).cb.blockhtml).is_some() {
                    ((*rndr).cb.blockhtml)
                        .expect(
                            "non-null function pointer",
                        )(ob, &mut work, (*rndr).opaque);
                }
                return work.size;
            }
        }
        if size > 4 as libc::c_int as size_t
            && (*data.offset(1 as libc::c_int as isize) as libc::c_int == 'h' as i32
                || *data.offset(1 as libc::c_int as isize) as libc::c_int == 'H' as i32)
            && (*data.offset(2 as libc::c_int as isize) as libc::c_int == 'r' as i32
                || *data.offset(2 as libc::c_int as isize) as libc::c_int == 'R' as i32)
        {
            i = 3 as libc::c_int as size_t;
            while i < size && *data.offset(i as isize) as libc::c_int != '>' as i32 {
                i = i.wrapping_add(1);
                i;
            }
            if i.wrapping_add(1 as libc::c_int as size_t) < size {
                i = i.wrapping_add(1);
                i;
                j = is_empty(data.offset(i as isize), size.wrapping_sub(i));
                if j != 0 {
                    work.size = i.wrapping_add(j);
                    if do_render != 0 && ((*rndr).cb.blockhtml).is_some() {
                        ((*rndr).cb.blockhtml)
                            .expect(
                                "non-null function pointer",
                            )(ob, &mut work, (*rndr).opaque);
                    }
                    return work.size;
                }
            }
        }
        return 0 as libc::c_int as size_t;
    }
    tag_end = htmlblock_end(curtag, rndr, data, size, 1 as libc::c_int);
    if tag_end == 0
        && strcmp(curtag, b"ins\0" as *const u8 as *const libc::c_char)
            != 0 as libc::c_int
        && strcmp(curtag, b"del\0" as *const u8 as *const libc::c_char)
            != 0 as libc::c_int
    {
        tag_end = htmlblock_end(curtag, rndr, data, size, 0 as libc::c_int);
    }
    if tag_end == 0 {
        return 0 as libc::c_int as size_t;
    }
    work.size = tag_end;
    if do_render != 0 && ((*rndr).cb.blockhtml).is_some() {
        ((*rndr).cb.blockhtml)
            .expect("non-null function pointer")(ob, &mut work, (*rndr).opaque);
    }
    return tag_end;
}
unsafe extern "C" fn parse_table_row(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut columns: size_t,
    mut col_data: *mut libc::c_int,
    mut header_flag: libc::c_int,
) {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut col: size_t = 0;
    let mut cols_left: size_t = 0;
    let mut row_work: *mut buf = 0 as *mut buf;
    if ((*rndr).cb.table_cell).is_none() || ((*rndr).cb.table_row).is_none() {
        return;
    }
    row_work = rndr_newbuf(rndr, 1 as libc::c_int);
    if i < size && *data.offset(i as isize) as libc::c_int == '|' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    col = 0 as libc::c_int as size_t;
    while col < columns && i < size {
        let mut cell_start: size_t = 0;
        let mut cell_end: size_t = 0;
        let mut cell_work: *mut buf = 0 as *mut buf;
        cell_work = rndr_newbuf(rndr, 1 as libc::c_int);
        while i < size && _isspace(*data.offset(i as isize) as libc::c_int) != 0 {
            i = i.wrapping_add(1);
            i;
        }
        cell_start = i;
        while i < size && *data.offset(i as isize) as libc::c_int != '|' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        cell_end = i.wrapping_sub(1 as libc::c_int as size_t);
        while cell_end > cell_start
            && _isspace(*data.offset(cell_end as isize) as libc::c_int) != 0
        {
            cell_end = cell_end.wrapping_sub(1);
            cell_end;
        }
        parse_inline(
            cell_work,
            rndr,
            data.offset(cell_start as isize),
            (1 as libc::c_int as size_t).wrapping_add(cell_end).wrapping_sub(cell_start),
        );
        ((*rndr).cb.table_cell)
            .expect(
                "non-null function pointer",
            )(
            row_work,
            cell_work,
            *col_data.offset(col as isize) | header_flag,
            (*rndr).opaque,
            0 as libc::c_int,
        );
        rndr_popbuf(rndr, 1 as libc::c_int);
        i = i.wrapping_add(1);
        i;
        col = col.wrapping_add(1);
        col;
    }
    cols_left = columns.wrapping_sub(col);
    if cols_left > 0 as libc::c_int as size_t {
        let mut empty_cell: buf = {
            let mut init = buf {
                data: 0 as *mut uint8_t,
                size: 0 as libc::c_int as size_t,
                asize: 0 as libc::c_int as size_t,
                unit: 0 as libc::c_int as size_t,
            };
            init
        };
        ((*rndr).cb.table_cell)
            .expect(
                "non-null function pointer",
            )(
            row_work,
            &mut empty_cell,
            *col_data.offset(col as isize) | header_flag,
            (*rndr).opaque,
            cols_left as libc::c_int,
        );
    }
    ((*rndr).cb.table_row)
        .expect("non-null function pointer")(ob, row_work, (*rndr).opaque);
    rndr_popbuf(rndr, 1 as libc::c_int);
}
unsafe extern "C" fn parse_table_header(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
    mut columns: *mut size_t,
    mut column_data: *mut *mut libc::c_int,
) -> size_t {
    let mut pipes: libc::c_int = 0;
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut col: size_t = 0;
    let mut header_end: size_t = 0;
    let mut under_end: size_t = 0;
    pipes = 0 as libc::c_int;
    while i < size && *data.offset(i as isize) as libc::c_int != '\n' as i32 {
        let fresh2 = i;
        i = i.wrapping_add(1);
        if *data.offset(fresh2 as isize) as libc::c_int == '|' as i32 {
            pipes += 1;
            pipes;
        }
    }
    if i == size || pipes == 0 as libc::c_int {
        return 0 as libc::c_int as size_t;
    }
    header_end = i;
    while header_end > 0 as libc::c_int as size_t
        && _isspace(
            *data.offset(header_end.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int,
        ) != 0
    {
        header_end = header_end.wrapping_sub(1);
        header_end;
    }
    if *data.offset(0 as libc::c_int as isize) as libc::c_int == '|' as i32 {
        pipes -= 1;
        pipes;
    }
    if header_end != 0
        && *data.offset(header_end.wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '|' as i32
    {
        pipes -= 1;
        pipes;
    }
    if (pipes + 1 as libc::c_int) as size_t > (*rndr).max_table_cols {
        return 0 as libc::c_int as size_t;
    }
    *columns = (pipes + 1 as libc::c_int) as size_t;
    *column_data = calloc(
        *columns,
        ::core::mem::size_of::<libc::c_int>() as libc::c_ulong,
    ) as *mut libc::c_int;
    i = i.wrapping_add(1);
    i;
    if i < size && *data.offset(i as isize) as libc::c_int == '|' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    under_end = i;
    while under_end < size
        && *data.offset(under_end as isize) as libc::c_int != '\n' as i32
    {
        under_end = under_end.wrapping_add(1);
        under_end;
    }
    col = 0 as libc::c_int as size_t;
    while col < *columns && i < under_end {
        let mut dashes: size_t = 0 as libc::c_int as size_t;
        while i < under_end && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        if *data.offset(i as isize) as libc::c_int == ':' as i32 {
            i = i.wrapping_add(1);
            i;
            *(*column_data).offset(col as isize) |= MKD_TABLE_ALIGN_L as libc::c_int;
            dashes = dashes.wrapping_add(1);
            dashes;
        }
        while i < under_end && *data.offset(i as isize) as libc::c_int == '-' as i32 {
            i = i.wrapping_add(1);
            i;
            dashes = dashes.wrapping_add(1);
            dashes;
        }
        if i < under_end && *data.offset(i as isize) as libc::c_int == ':' as i32 {
            i = i.wrapping_add(1);
            i;
            *(*column_data).offset(col as isize) |= MKD_TABLE_ALIGN_R as libc::c_int;
            dashes = dashes.wrapping_add(1);
            dashes;
        }
        while i < under_end && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
        }
        if i < under_end && *data.offset(i as isize) as libc::c_int != '|' as i32 {
            break;
        }
        if dashes < 1 as libc::c_int as size_t {
            break;
        }
        i = i.wrapping_add(1);
        i;
        col = col.wrapping_add(1);
        col;
    }
    if col < *columns {
        return 0 as libc::c_int as size_t;
    }
    parse_table_row(
        ob,
        rndr,
        data,
        header_end,
        *columns,
        *column_data,
        MKD_TABLE_HEADER as libc::c_int,
    );
    return under_end.wrapping_add(1 as libc::c_int as size_t);
}
unsafe extern "C" fn parse_table(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) -> size_t {
    let mut i: size_t = 0;
    let mut header_work: *mut buf = 0 as *mut buf;
    let mut body_work: *mut buf = 0 as *mut buf;
    let mut columns: size_t = 0;
    let mut col_data: *mut libc::c_int = 0 as *mut libc::c_int;
    header_work = rndr_newbuf(rndr, 1 as libc::c_int);
    body_work = rndr_newbuf(rndr, 0 as libc::c_int);
    i = parse_table_header(header_work, rndr, data, size, &mut columns, &mut col_data);
    if i > 0 as libc::c_int as size_t {
        while i < size {
            let mut row_start: size_t = 0;
            let mut pipes: libc::c_int = 0 as libc::c_int;
            row_start = i;
            while i < size && *data.offset(i as isize) as libc::c_int != '\n' as i32 {
                let fresh3 = i;
                i = i.wrapping_add(1);
                if *data.offset(fresh3 as isize) as libc::c_int == '|' as i32 {
                    pipes += 1;
                    pipes;
                }
            }
            if pipes == 0 as libc::c_int || i == size {
                i = row_start;
                break;
            } else {
                parse_table_row(
                    body_work,
                    rndr,
                    data.offset(row_start as isize),
                    i.wrapping_sub(row_start),
                    columns,
                    col_data,
                    0 as libc::c_int,
                );
                i = i.wrapping_add(1);
                i;
            }
        }
        if ((*rndr).cb.table).is_some() {
            ((*rndr).cb.table)
                .expect(
                    "non-null function pointer",
                )(ob, header_work, body_work, (*rndr).opaque);
        }
    }
    free(col_data as *mut libc::c_void);
    rndr_popbuf(rndr, 1 as libc::c_int);
    rndr_popbuf(rndr, 0 as libc::c_int);
    return i;
}
unsafe extern "C" fn parse_block(
    mut ob: *mut buf,
    mut rndr: *mut sd_markdown,
    mut data: *mut uint8_t,
    mut size: size_t,
) {
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    let mut i: size_t = 0;
    let mut txt_data: *mut uint8_t = 0 as *mut uint8_t;
    beg = 0 as libc::c_int as size_t;
    if ((*rndr).work_bufs[1 as libc::c_int as usize].size)
        .wrapping_add((*rndr).work_bufs[0 as libc::c_int as usize].size)
        > (*rndr).max_nesting
    {
        return;
    }
    while beg < size {
        txt_data = data.offset(beg as isize);
        end = size.wrapping_sub(beg);
        if is_atxheader(rndr, txt_data, end) != 0 {
            beg = beg.wrapping_add(parse_atxheader(ob, rndr, txt_data, end));
        } else if *data.offset(beg as isize) as libc::c_int == '<' as i32
            && ((*rndr).cb.blockhtml).is_some()
            && {
                i = parse_htmlblock(ob, rndr, txt_data, end, 1 as libc::c_int);
                i != 0 as libc::c_int as size_t
            }
        {
            beg = beg.wrapping_add(i);
        } else {
            i = is_empty(txt_data, end);
            if i != 0 as libc::c_int as size_t {
                beg = beg.wrapping_add(i);
            } else if is_hrule(txt_data, end) != 0 {
                if ((*rndr).cb.hrule).is_some() {
                    ((*rndr).cb.hrule)
                        .expect("non-null function pointer")(ob, (*rndr).opaque);
                }
                while beg < size
                    && *data.offset(beg as isize) as libc::c_int != '\n' as i32
                {
                    beg = beg.wrapping_add(1);
                    beg;
                }
                beg = beg.wrapping_add(1);
                beg;
            } else if (*rndr).ext_flags
                & MKDEXT_FENCED_CODE as libc::c_int as libc::c_uint
                != 0 as libc::c_int as libc::c_uint
                && {
                    i = parse_fencedcode(ob, rndr, txt_data, end);
                    i != 0 as libc::c_int as size_t
                }
            {
                beg = beg.wrapping_add(i);
            } else if (*rndr).ext_flags & MKDEXT_TABLES as libc::c_int as libc::c_uint
                != 0 as libc::c_int as libc::c_uint
                && {
                    i = parse_table(ob, rndr, txt_data, end);
                    i != 0 as libc::c_int as size_t
                }
            {
                beg = beg.wrapping_add(i);
            } else if prefix_quote(txt_data, end) != 0 {
                beg = beg.wrapping_add(parse_blockquote(ob, rndr, txt_data, end));
            } else if prefix_blockspoiler(txt_data, end) != 0 {
                beg = beg.wrapping_add(parse_blockspoiler(ob, rndr, txt_data, end));
            } else if prefix_code(txt_data, end) != 0 {
                beg = beg.wrapping_add(parse_blockcode(ob, rndr, txt_data, end));
            } else if prefix_uli(txt_data, end) != 0 {
                beg = beg
                    .wrapping_add(parse_list(ob, rndr, txt_data, end, 0 as libc::c_int));
            } else if prefix_oli(txt_data, end) != 0 {
                beg = beg
                    .wrapping_add(parse_list(ob, rndr, txt_data, end, 1 as libc::c_int));
            } else {
                beg = beg.wrapping_add(parse_paragraph(ob, rndr, txt_data, end));
            }
        }
    }
}
unsafe extern "C" fn is_ref(
    mut data: *const uint8_t,
    mut beg: size_t,
    mut end: size_t,
    mut last: *mut size_t,
    mut refs: *mut *mut link_ref,
) -> libc::c_int {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut id_offset: size_t = 0;
    let mut id_end: size_t = 0;
    let mut link_offset: size_t = 0;
    let mut link_end: size_t = 0;
    let mut title_offset: size_t = 0;
    let mut title_end: size_t = 0;
    let mut line_end: size_t = 0;
    if beg.wrapping_add(3 as libc::c_int as size_t) >= end {
        return 0 as libc::c_int;
    }
    if *data.offset(beg as isize) as libc::c_int == ' ' as i32 {
        i = 1 as libc::c_int as size_t;
        if *data.offset(beg.wrapping_add(1 as libc::c_int as size_t) as isize)
            as libc::c_int == ' ' as i32
        {
            i = 2 as libc::c_int as size_t;
            if *data.offset(beg.wrapping_add(2 as libc::c_int as size_t) as isize)
                as libc::c_int == ' ' as i32
            {
                i = 3 as libc::c_int as size_t;
                if *data.offset(beg.wrapping_add(3 as libc::c_int as size_t) as isize)
                    as libc::c_int == ' ' as i32
                {
                    return 0 as libc::c_int;
                }
            }
        }
    }
    i = i.wrapping_add(beg);
    if *data.offset(i as isize) as libc::c_int != '[' as i32 {
        return 0 as libc::c_int;
    }
    i = i.wrapping_add(1);
    i;
    id_offset = i;
    while i < end && *data.offset(i as isize) as libc::c_int != '\n' as i32
        && *data.offset(i as isize) as libc::c_int != '\r' as i32
        && *data.offset(i as isize) as libc::c_int != ']' as i32
    {
        i = i.wrapping_add(1);
        i;
    }
    if i >= end || *data.offset(i as isize) as libc::c_int != ']' as i32 {
        return 0 as libc::c_int;
    }
    id_end = i;
    i = i.wrapping_add(1);
    i;
    if i >= end || *data.offset(i as isize) as libc::c_int != ':' as i32 {
        return 0 as libc::c_int;
    }
    i = i.wrapping_add(1);
    i;
    while i < end && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < end
        && (*data.offset(i as isize) as libc::c_int == '\n' as i32
            || *data.offset(i as isize) as libc::c_int == '\r' as i32)
    {
        i = i.wrapping_add(1);
        i;
        if i < end && *data.offset(i as isize) as libc::c_int == '\r' as i32
            && *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '\n' as i32
        {
            i = i.wrapping_add(1);
            i;
        }
    }
    while i < end && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i >= end {
        return 0 as libc::c_int;
    }
    if *data.offset(i as isize) as libc::c_int == '<' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    link_offset = i;
    while i < end && *data.offset(i as isize) as libc::c_int != ' ' as i32
        && *data.offset(i as isize) as libc::c_int != '\n' as i32
        && *data.offset(i as isize) as libc::c_int != '\r' as i32
    {
        i = i.wrapping_add(1);
        i;
    }
    if *data.offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize) as libc::c_int
        == '>' as i32
    {
        link_end = i.wrapping_sub(1 as libc::c_int as size_t);
    } else {
        link_end = i;
    }
    while i < end && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    if i < end && *data.offset(i as isize) as libc::c_int != '\n' as i32
        && *data.offset(i as isize) as libc::c_int != '\r' as i32
        && *data.offset(i as isize) as libc::c_int != '\'' as i32
        && *data.offset(i as isize) as libc::c_int != '"' as i32
        && *data.offset(i as isize) as libc::c_int != '(' as i32
    {
        return 0 as libc::c_int;
    }
    line_end = 0 as libc::c_int as size_t;
    if i >= end || *data.offset(i as isize) as libc::c_int == '\r' as i32
        || *data.offset(i as isize) as libc::c_int == '\n' as i32
    {
        line_end = i;
    }
    if i.wrapping_add(1 as libc::c_int as size_t) < end
        && *data.offset(i as isize) as libc::c_int == '\n' as i32
        && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '\r' as i32
    {
        line_end = i.wrapping_add(1 as libc::c_int as size_t);
    }
    if line_end != 0 {
        i = line_end.wrapping_add(1 as libc::c_int as size_t);
        while i < end && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_add(1);
            i;
        }
    }
    title_end = 0 as libc::c_int as size_t;
    title_offset = title_end;
    if i.wrapping_add(1 as libc::c_int as size_t) < end
        && (*data.offset(i as isize) as libc::c_int == '\'' as i32
            || *data.offset(i as isize) as libc::c_int == '"' as i32
            || *data.offset(i as isize) as libc::c_int == '(' as i32)
    {
        i = i.wrapping_add(1);
        i;
        title_offset = i;
        while i < end && *data.offset(i as isize) as libc::c_int != '\n' as i32
            && *data.offset(i as isize) as libc::c_int != '\r' as i32
        {
            i = i.wrapping_add(1);
            i;
        }
        if i.wrapping_add(1 as libc::c_int as size_t) < end
            && *data.offset(i as isize) as libc::c_int == '\n' as i32
            && *data.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '\r' as i32
        {
            title_end = i.wrapping_add(1 as libc::c_int as size_t);
        } else {
            title_end = i;
        }
        i = i.wrapping_sub(1 as libc::c_int as size_t);
        while i > title_offset && *data.offset(i as isize) as libc::c_int == ' ' as i32 {
            i = i.wrapping_sub(1 as libc::c_int as size_t);
        }
        if i > title_offset
            && (*data.offset(i as isize) as libc::c_int == '\'' as i32
                || *data.offset(i as isize) as libc::c_int == '"' as i32
                || *data.offset(i as isize) as libc::c_int == ')' as i32)
        {
            line_end = title_end;
            title_end = i;
        }
    }
    if line_end == 0 || link_end == link_offset {
        return 0 as libc::c_int;
    }
    if !last.is_null() {
        *last = line_end;
    }else { std::intrinsics::assume((last).addr() == 0); }
    if !refs.is_null() {
        let mut ref_0: *mut link_ref = 0 as *mut link_ref;
        ref_0 = add_link_ref(
            refs,
            data.offset(id_offset as isize),
            id_end.wrapping_sub(id_offset),
        );
        if ref_0.is_null() {std::intrinsics::assume((ref_0).addr() == 0);
            return 0 as libc::c_int;
        }
        (*ref_0).label = bufnew(id_end.wrapping_sub(id_offset));
        bufput(
            (*ref_0).label,
            data.offset(id_offset as isize) as *const libc::c_void,
            id_end.wrapping_sub(id_offset),
        );
        (*ref_0).link = bufnew(link_end.wrapping_sub(link_offset));
        bufput(
            (*ref_0).link,
            data.offset(link_offset as isize) as *const libc::c_void,
            link_end.wrapping_sub(link_offset),
        );
        if title_end > title_offset {
            (*ref_0).title = bufnew(title_end.wrapping_sub(title_offset));
            bufput(
                (*ref_0).title,
                data.offset(title_offset as isize) as *const libc::c_void,
                title_end.wrapping_sub(title_offset),
            );
        }
    }else { std::intrinsics::assume((refs).addr() == 0); }
    return 1 as libc::c_int;
}
unsafe extern "C" fn expand_tabs(
    mut ob: *mut buf,
    mut line: *const uint8_t,
    mut size: size_t,
) {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut tab: size_t = 0 as libc::c_int as size_t;
    while i < size {
        let mut org: size_t = i;
        while i < size && *line.offset(i as isize) as libc::c_int != '\t' as i32 {
            i = i.wrapping_add(1);
            i;
            tab = tab.wrapping_add(1);
            tab;
        }
        if i > org {
            bufput(
                ob,
                line.offset(org as isize) as *const libc::c_void,
                i.wrapping_sub(org),
            );
        }
        if i >= size {
            break;
        }
        loop {
            bufputc(ob, ' ' as i32);
            tab = tab.wrapping_add(1);
            tab;
            if !(tab % 4 as libc::c_int as size_t != 0) {
                break;
            }
        }
        i = i.wrapping_add(1);
        i;
    }
}
#[no_mangle]
pub unsafe extern "C" fn sd_markdown_new(
    mut extensions: libc::c_uint,
    mut max_nesting: size_t,
    mut max_table_cols: size_t,
    mut callbacks: *const sd_callbacks,
    mut opaque: *mut libc::c_void,
) -> *mut sd_markdown {
    let mut md: *mut sd_markdown = 0 as *mut sd_markdown;
    if max_nesting > 0 as libc::c_int as size_t
        && max_table_cols > 0 as libc::c_int as size_t && !callbacks.is_null()
    {} else {
        __assert_fail(
            b"max_nesting > 0 && max_table_cols > 0 && callbacks\0" as *const u8
                as *const libc::c_char,
            b"markdown.c\0" as *const u8 as *const libc::c_char,
            2651 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 103],
                &[libc::c_char; 103],
            >(
                b"struct sd_markdown *sd_markdown_new(unsigned int, size_t, size_t, const struct sd_callbacks *, void *)\0",
            ))
                .as_ptr(),
        );
    }
    'c_850: {
        if max_nesting > 0 as libc::c_int as size_t
            && max_table_cols > 0 as libc::c_int as size_t && !callbacks.is_null()
        {} else {
            __assert_fail(
                b"max_nesting > 0 && max_table_cols > 0 && callbacks\0" as *const u8
                    as *const libc::c_char,
                b"markdown.c\0" as *const u8 as *const libc::c_char,
                2651 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 103],
                    &[libc::c_char; 103],
                >(
                    b"struct sd_markdown *sd_markdown_new(unsigned int, size_t, size_t, const struct sd_callbacks *, void *)\0",
                ))
                    .as_ptr(),
            );
        }
    };
    md = malloc(::core::mem::size_of::<sd_markdown>() as libc::c_ulong)
        as *mut sd_markdown;
    if md.is_null() {std::intrinsics::assume((md).addr() == 0);
        return 0 as *mut sd_markdown;
    }
    if sip_hash_key_init == 0 {
        if backport_getrandom(
            sip_hash_key.as_mut_ptr() as *mut libc::c_void,
            16 as libc::c_int as size_t,
            0 as libc::c_int as libc::c_uint,
        ) < 16 as libc::c_int
        {
            return 0 as *mut sd_markdown;
        }
        sip_hash_key_init = 1 as libc::c_int;
    }
    memcpy(
        &mut (*md).cb as *mut sd_callbacks as *mut libc::c_void,
        callbacks as *const libc::c_void,
        ::core::mem::size_of::<sd_callbacks>() as libc::c_ulong,
    );
    stack_init(
        &mut *((*md).work_bufs).as_mut_ptr().offset(0 as libc::c_int as isize),
        4 as libc::c_int as size_t,
    );
    stack_init(
        &mut *((*md).work_bufs).as_mut_ptr().offset(1 as libc::c_int as isize),
        8 as libc::c_int as size_t,
    );
    memset(
        ((*md).active_char).as_mut_ptr() as *mut libc::c_void,
        0 as libc::c_int,
        256 as libc::c_int as libc::c_ulong,
    );
    if ((*md).cb.emphasis).is_some() || ((*md).cb.double_emphasis).is_some()
        || ((*md).cb.triple_emphasis).is_some()
    {
        (*md)
            .active_char['*' as i32
            as usize] = MD_CHAR_EMPHASIS as libc::c_int as uint8_t;
        (*md)
            .active_char['_' as i32
            as usize] = MD_CHAR_EMPHASIS as libc::c_int as uint8_t;
        (*md)
            .active_char['>' as i32
            as usize] = MD_CHAR_EMPHASIS as libc::c_int as uint8_t;
        if extensions & MKDEXT_STRIKETHROUGH as libc::c_int as libc::c_uint != 0 {
            (*md)
                .active_char['~' as i32
                as usize] = MD_CHAR_EMPHASIS as libc::c_int as uint8_t;
        }
    }
    if ((*md).cb.codespan).is_some() {
        (*md)
            .active_char['`' as i32
            as usize] = MD_CHAR_CODESPAN as libc::c_int as uint8_t;
    }
    if ((*md).cb.linebreak).is_some() {
        (*md)
            .active_char['\n' as i32
            as usize] = MD_CHAR_LINEBREAK as libc::c_int as uint8_t;
    }
    if ((*md).cb.image).is_some() || ((*md).cb.link).is_some() {
        (*md).active_char['[' as i32 as usize] = MD_CHAR_LINK as libc::c_int as uint8_t;
    }
    (*md).active_char['<' as i32 as usize] = MD_CHAR_LANGLE as libc::c_int as uint8_t;
    (*md).active_char['\\' as i32 as usize] = MD_CHAR_ESCAPE as libc::c_int as uint8_t;
    (*md).active_char['&' as i32 as usize] = MD_CHAR_ENTITITY as libc::c_int as uint8_t;
    if extensions & MKDEXT_AUTOLINK as libc::c_int as libc::c_uint != 0 {
        if extensions & MKDEXT_NO_EMAIL_AUTOLINK as libc::c_int as libc::c_uint == 0 {
            (*md)
                .active_char['@' as i32
                as usize] = MD_CHAR_AUTOLINK_EMAIL as libc::c_int as uint8_t;
        }
        (*md)
            .active_char[':' as i32
            as usize] = MD_CHAR_AUTOLINK_URL as libc::c_int as uint8_t;
        (*md)
            .active_char['w' as i32
            as usize] = MD_CHAR_AUTOLINK_WWW as libc::c_int as uint8_t;
        (*md)
            .active_char['/' as i32
            as usize] = MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME as libc::c_int as uint8_t;
    }
    if extensions & MKDEXT_SUPERSCRIPT as libc::c_int as libc::c_uint != 0 {
        (*md)
            .active_char['^' as i32
            as usize] = MD_CHAR_SUPERSCRIPT as libc::c_int as uint8_t;
    }
    (*md).ext_flags = extensions;
    (*md).opaque = opaque;
    (*md).max_nesting = max_nesting;
    (*md).max_table_cols = max_table_cols;
    (*md).in_link_body = 0 as libc::c_int;
    return md;
}
#[no_mangle]
pub unsafe extern "C" fn sd_markdown_render(
    mut ob: *mut buf,
    mut document: *const uint8_t,
    mut doc_size: size_t,
    mut md: *mut sd_markdown,
) {
    static mut UTF8_BOM: [libc::c_char; 3] = [
        0xef as libc::c_int as libc::c_char,
        0xbb as libc::c_int as libc::c_char,
        0xbf as libc::c_int as libc::c_char,
    ];
    let mut text: *mut buf = 0 as *mut buf;
    let mut beg: size_t = 0;
    let mut end: size_t = 0;
    text = bufnew(64 as libc::c_int as size_t);
    if text.is_null() {std::intrinsics::assume((text).addr() == 0);
        return;
    }
    bufgrow(text, doc_size);
    memset(
        &mut (*md).refs as *mut [*mut link_ref; 8] as *mut libc::c_void,
        0 as libc::c_int,
        (8 as libc::c_int as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<*mut libc::c_void>() as libc::c_ulong),
    );
    beg = 0 as libc::c_int as size_t;
    if doc_size >= 3 as libc::c_int as size_t
        && memcmp(
            document as *const libc::c_void,
            UTF8_BOM.as_ptr() as *const libc::c_void,
            3 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
    {
        beg = beg.wrapping_add(3 as libc::c_int as size_t);
    }
    while beg < doc_size {
        if is_ref(document, beg, doc_size, &mut end, ((*md).refs).as_mut_ptr()) != 0 {
            beg = end;
        } else {
            end = beg;
            while end < doc_size
                && *document.offset(end as isize) as libc::c_int != '\n' as i32
                && *document.offset(end as isize) as libc::c_int != '\r' as i32
            {
                end = end.wrapping_add(1);
                end;
            }
            if end > beg {
                expand_tabs(text, document.offset(beg as isize), end.wrapping_sub(beg));
            }
            while end < doc_size
                && (*document.offset(end as isize) as libc::c_int == '\n' as i32
                    || *document.offset(end as isize) as libc::c_int == '\r' as i32)
            {
                if *document.offset(end as isize) as libc::c_int == '\n' as i32
                    || end.wrapping_add(1 as libc::c_int as size_t) < doc_size
                        && *document
                            .offset(
                                end.wrapping_add(1 as libc::c_int as size_t) as isize,
                            ) as libc::c_int != '\n' as i32
                {
                    bufputc(text, '\n' as i32);
                }
                end = end.wrapping_add(1);
                end;
            }
            beg = end;
        }
    }
    bufgrow(ob, ((*text).size).wrapping_add((*text).size >> 1 as libc::c_int));
    if ((*md).cb.doc_header).is_some() {
        ((*md).cb.doc_header).expect("non-null function pointer")(ob, (*md).opaque);
    }
    if (*text).size != 0 {
        if *((*text).data)
            .offset(((*text).size).wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int != '\n' as i32
            && *((*text).data)
                .offset(((*text).size).wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int != '\r' as i32
        {
            bufputc(text, '\n' as i32);
        }
        parse_block(ob, md, (*text).data, (*text).size);
    }
    if ((*md).cb.doc_footer).is_some() {
        ((*md).cb.doc_footer).expect("non-null function pointer")(ob, (*md).opaque);
    }
    bufrelease(text);
    free_link_refs(((*md).refs).as_mut_ptr());
    if (*md).work_bufs[1 as libc::c_int as usize].size == 0 as libc::c_int as size_t
    {} else {
        __assert_fail(
            b"md->work_bufs[BUFFER_SPAN].size == 0\0" as *const u8
                as *const libc::c_char,
            b"markdown.c\0" as *const u8 as *const libc::c_char,
            2783 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 85],
                &[libc::c_char; 85],
            >(
                b"void sd_markdown_render(struct buf *, const uint8_t *, size_t, struct sd_markdown *)\0",
            ))
                .as_ptr(),
        );
    }
    'c_994: {
        if (*md).work_bufs[1 as libc::c_int as usize].size == 0 as libc::c_int as size_t
        {} else {
            __assert_fail(
                b"md->work_bufs[BUFFER_SPAN].size == 0\0" as *const u8
                    as *const libc::c_char,
                b"markdown.c\0" as *const u8 as *const libc::c_char,
                2783 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 85],
                    &[libc::c_char; 85],
                >(
                    b"void sd_markdown_render(struct buf *, const uint8_t *, size_t, struct sd_markdown *)\0",
                ))
                    .as_ptr(),
            );
        }
    };
    if (*md).work_bufs[0 as libc::c_int as usize].size == 0 as libc::c_int as size_t
    {} else {
        __assert_fail(
            b"md->work_bufs[BUFFER_BLOCK].size == 0\0" as *const u8
                as *const libc::c_char,
            b"markdown.c\0" as *const u8 as *const libc::c_char,
            2784 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 85],
                &[libc::c_char; 85],
            >(
                b"void sd_markdown_render(struct buf *, const uint8_t *, size_t, struct sd_markdown *)\0",
            ))
                .as_ptr(),
        );
    }
    'c_942: {
        if (*md).work_bufs[0 as libc::c_int as usize].size == 0 as libc::c_int as size_t
        {} else {
            __assert_fail(
                b"md->work_bufs[BUFFER_BLOCK].size == 0\0" as *const u8
                    as *const libc::c_char,
                b"markdown.c\0" as *const u8 as *const libc::c_char,
                2784 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 85],
                    &[libc::c_char; 85],
                >(
                    b"void sd_markdown_render(struct buf *, const uint8_t *, size_t, struct sd_markdown *)\0",
                ))
                    .as_ptr(),
            );
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn sd_markdown_free(mut md: *mut sd_markdown) {
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < (*md).work_bufs[1 as libc::c_int as usize].asize {
        bufrelease(
            *((*md).work_bufs[1 as libc::c_int as usize].item).offset(i as isize)
                as *mut buf,
        );
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < (*md).work_bufs[0 as libc::c_int as usize].asize {
        bufrelease(
            *((*md).work_bufs[0 as libc::c_int as usize].item).offset(i as isize)
                as *mut buf,
        );
        i = i.wrapping_add(1);
        i;
    }
    stack_free(&mut *((*md).work_bufs).as_mut_ptr().offset(1 as libc::c_int as isize));
    stack_free(&mut *((*md).work_bufs).as_mut_ptr().offset(0 as libc::c_int as isize));
    free(md as *mut libc::c_void);
}
#[no_mangle]
pub unsafe extern "C" fn sd_version(
    mut ver_major: *mut libc::c_int,
    mut ver_minor: *mut libc::c_int,
    mut ver_revision: *mut libc::c_int,
) {
    *ver_major = 1 as libc::c_int;
    *ver_minor = 16 as libc::c_int;
    *ver_revision = 0 as libc::c_int;
}
