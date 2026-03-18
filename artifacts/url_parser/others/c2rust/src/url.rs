use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn memmove(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strcpy(_: *mut libc::c_char, _: *const libc::c_char) -> *mut libc::c_char;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn sscanf(_: *const libc::c_char, _: *const libc::c_char, _: ...) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type _IO_lock_t = ();
pub type FILE = _IO_FILE;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct url_key_value {
    pub key: *const libc::c_char,
    pub value: *const libc::c_char,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct url_data {
    pub whole_url: *mut libc::c_char,
    pub protocol: *const libc::c_char,
    pub userinfo: *const libc::c_char,
    pub host: *const libc::c_char,
    pub port: *const libc::c_char,
    pub path: *const libc::c_char,
    pub query: *const url_key_value,
    pub fragment: *const libc::c_char,
}
pub type url_data_t = url_data;
pub type Category = libc::c_uint;
pub const IPv6Char: Category = 256;
pub const Userinfo: Category = 128;
pub const Fragment: Category = 64;
pub const Query: Category = 64;
pub const HexDigit: Category = 32;
pub const PCharSlash: Category = 16;
pub const SubDelim: Category = 8;
pub const GenDelim: Category = 4;
pub const Unreserved: Category = 2;
pub const Scheme: Category = 1;
#[inline]
unsafe extern "C" fn url_get_protocol(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    return url_get_scheme(url);
}
#[inline]
unsafe extern "C" fn url_get_hash(mut url: *const libc::c_char) -> *mut libc::c_char {
    return url_get_fragment(url);
}
static mut char_cat: [libc::c_ushort; 256] = [
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0x4 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd0 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd9 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0xd3 as libc::c_int as libc::c_ushort,
    0xd3 as libc::c_int as libc::c_ushort,
    0x54 as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1d4 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0xd8 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0x44 as libc::c_int as libc::c_ushort,
    0x54 as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0x4 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0x4 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0xd2 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0x1ff as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0xdf as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0xd2 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
    0 as libc::c_int as libc::c_ushort,
];
static mut URL_SCHEMES: [*const libc::c_char; 177] = [
    b"aaa\0" as *const u8 as *const libc::c_char,
    b"aaas\0" as *const u8 as *const libc::c_char,
    b"about\0" as *const u8 as *const libc::c_char,
    b"acap\0" as *const u8 as *const libc::c_char,
    b"acct\0" as *const u8 as *const libc::c_char,
    b"adiumxtra\0" as *const u8 as *const libc::c_char,
    b"afp\0" as *const u8 as *const libc::c_char,
    b"afs\0" as *const u8 as *const libc::c_char,
    b"aim\0" as *const u8 as *const libc::c_char,
    b"apt\0" as *const u8 as *const libc::c_char,
    b"attachment\0" as *const u8 as *const libc::c_char,
    b"aw\0" as *const u8 as *const libc::c_char,
    b"beshare\0" as *const u8 as *const libc::c_char,
    b"bitcoin\0" as *const u8 as *const libc::c_char,
    b"bolo\0" as *const u8 as *const libc::c_char,
    b"callto\0" as *const u8 as *const libc::c_char,
    b"cap\0" as *const u8 as *const libc::c_char,
    b"chrome\0" as *const u8 as *const libc::c_char,
    b"crome-extension\0" as *const u8 as *const libc::c_char,
    b"com-evenbrite-attendee\0" as *const u8 as *const libc::c_char,
    b"cid\0" as *const u8 as *const libc::c_char,
    b"coap\0" as *const u8 as *const libc::c_char,
    b"coaps\0" as *const u8 as *const libc::c_char,
    b"content\0" as *const u8 as *const libc::c_char,
    b"crid\0" as *const u8 as *const libc::c_char,
    b"cvs\0" as *const u8 as *const libc::c_char,
    b"data\0" as *const u8 as *const libc::c_char,
    b"dav\0" as *const u8 as *const libc::c_char,
    b"dict\0" as *const u8 as *const libc::c_char,
    b"lna-playsingle\0" as *const u8 as *const libc::c_char,
    b"dln-playcontainer\0" as *const u8 as *const libc::c_char,
    b"dns\0" as *const u8 as *const libc::c_char,
    b"dtn\0" as *const u8 as *const libc::c_char,
    b"dvb\0" as *const u8 as *const libc::c_char,
    b"ed2k\0" as *const u8 as *const libc::c_char,
    b"facetime\0" as *const u8 as *const libc::c_char,
    b"fax\0" as *const u8 as *const libc::c_char,
    b"feed\0" as *const u8 as *const libc::c_char,
    b"file\0" as *const u8 as *const libc::c_char,
    b"finger\0" as *const u8 as *const libc::c_char,
    b"fish\0" as *const u8 as *const libc::c_char,
    b"ftp\0" as *const u8 as *const libc::c_char,
    b"geo\0" as *const u8 as *const libc::c_char,
    b"gg\0" as *const u8 as *const libc::c_char,
    b"git\0" as *const u8 as *const libc::c_char,
    b"gizmoproject\0" as *const u8 as *const libc::c_char,
    b"go\0" as *const u8 as *const libc::c_char,
    b"gopher\0" as *const u8 as *const libc::c_char,
    b"gtalk\0" as *const u8 as *const libc::c_char,
    b"h323\0" as *const u8 as *const libc::c_char,
    b"hcp\0" as *const u8 as *const libc::c_char,
    b"http\0" as *const u8 as *const libc::c_char,
    b"https\0" as *const u8 as *const libc::c_char,
    b"iax\0" as *const u8 as *const libc::c_char,
    b"icap\0" as *const u8 as *const libc::c_char,
    b"icon\0" as *const u8 as *const libc::c_char,
    b"im\0" as *const u8 as *const libc::c_char,
    b"imap\0" as *const u8 as *const libc::c_char,
    b"info\0" as *const u8 as *const libc::c_char,
    b"ipn\0" as *const u8 as *const libc::c_char,
    b"ipp\0" as *const u8 as *const libc::c_char,
    b"irc\0" as *const u8 as *const libc::c_char,
    b"irc6\0" as *const u8 as *const libc::c_char,
    b"ircs\0" as *const u8 as *const libc::c_char,
    b"iris\0" as *const u8 as *const libc::c_char,
    b"iris.beep\0" as *const u8 as *const libc::c_char,
    b"iris.xpc\0" as *const u8 as *const libc::c_char,
    b"iris.xpcs\0" as *const u8 as *const libc::c_char,
    b"iris.lws\0" as *const u8 as *const libc::c_char,
    b"itms\0" as *const u8 as *const libc::c_char,
    b"jabber\0" as *const u8 as *const libc::c_char,
    b"jar\0" as *const u8 as *const libc::c_char,
    b"jms\0" as *const u8 as *const libc::c_char,
    b"keyparc\0" as *const u8 as *const libc::c_char,
    b"lastfm\0" as *const u8 as *const libc::c_char,
    b"ldap\0" as *const u8 as *const libc::c_char,
    b"ldaps\0" as *const u8 as *const libc::c_char,
    b"magnet\0" as *const u8 as *const libc::c_char,
    b"mailserver\0" as *const u8 as *const libc::c_char,
    b"mailto\0" as *const u8 as *const libc::c_char,
    b"maps\0" as *const u8 as *const libc::c_char,
    b"market\0" as *const u8 as *const libc::c_char,
    b"message\0" as *const u8 as *const libc::c_char,
    b"mid\0" as *const u8 as *const libc::c_char,
    b"mms\0" as *const u8 as *const libc::c_char,
    b"modem\0" as *const u8 as *const libc::c_char,
    b"ms-help\0" as *const u8 as *const libc::c_char,
    b"mssettings-power\0" as *const u8 as *const libc::c_char,
    b"msnim\0" as *const u8 as *const libc::c_char,
    b"msrp\0" as *const u8 as *const libc::c_char,
    b"msrps\0" as *const u8 as *const libc::c_char,
    b"mtqp\0" as *const u8 as *const libc::c_char,
    b"mumble\0" as *const u8 as *const libc::c_char,
    b"mupdate\0" as *const u8 as *const libc::c_char,
    b"mvn\0" as *const u8 as *const libc::c_char,
    b"news\0" as *const u8 as *const libc::c_char,
    b"nfs\0" as *const u8 as *const libc::c_char,
    b"ni\0" as *const u8 as *const libc::c_char,
    b"nih\0" as *const u8 as *const libc::c_char,
    b"nntp\0" as *const u8 as *const libc::c_char,
    b"notes\0" as *const u8 as *const libc::c_char,
    b"oid\0" as *const u8 as *const libc::c_char,
    b"paquelocktoken\0" as *const u8 as *const libc::c_char,
    b"pack\0" as *const u8 as *const libc::c_char,
    b"palm\0" as *const u8 as *const libc::c_char,
    b"paparazzi\0" as *const u8 as *const libc::c_char,
    b"pkcs11\0" as *const u8 as *const libc::c_char,
    b"platform\0" as *const u8 as *const libc::c_char,
    b"pop\0" as *const u8 as *const libc::c_char,
    b"pres\0" as *const u8 as *const libc::c_char,
    b"prospero\0" as *const u8 as *const libc::c_char,
    b"proxy\0" as *const u8 as *const libc::c_char,
    b"psyc\0" as *const u8 as *const libc::c_char,
    b"query\0" as *const u8 as *const libc::c_char,
    b"reload\0" as *const u8 as *const libc::c_char,
    b"res\0" as *const u8 as *const libc::c_char,
    b"resource\0" as *const u8 as *const libc::c_char,
    b"rmi\0" as *const u8 as *const libc::c_char,
    b"rsync\0" as *const u8 as *const libc::c_char,
    b"rtmp\0" as *const u8 as *const libc::c_char,
    b"rtsp\0" as *const u8 as *const libc::c_char,
    b"secondlife\0" as *const u8 as *const libc::c_char,
    b"service\0" as *const u8 as *const libc::c_char,
    b"session\0" as *const u8 as *const libc::c_char,
    b"sftp\0" as *const u8 as *const libc::c_char,
    b"sgn\0" as *const u8 as *const libc::c_char,
    b"shttp\0" as *const u8 as *const libc::c_char,
    b"sieve\0" as *const u8 as *const libc::c_char,
    b"sip\0" as *const u8 as *const libc::c_char,
    b"sips\0" as *const u8 as *const libc::c_char,
    b"skype\0" as *const u8 as *const libc::c_char,
    b"smb\0" as *const u8 as *const libc::c_char,
    b"sms\0" as *const u8 as *const libc::c_char,
    b"snews\0" as *const u8 as *const libc::c_char,
    b"snmp\0" as *const u8 as *const libc::c_char,
    b"soap.beep\0" as *const u8 as *const libc::c_char,
    b"soap.beeps\0" as *const u8 as *const libc::c_char,
    b"soldat\0" as *const u8 as *const libc::c_char,
    b"spotify\0" as *const u8 as *const libc::c_char,
    b"ssh\0" as *const u8 as *const libc::c_char,
    b"steam\0" as *const u8 as *const libc::c_char,
    b"svn\0" as *const u8 as *const libc::c_char,
    b"tag\0" as *const u8 as *const libc::c_char,
    b"teamspeak\0" as *const u8 as *const libc::c_char,
    b"tel\0" as *const u8 as *const libc::c_char,
    b"telnet\0" as *const u8 as *const libc::c_char,
    b"tftp\0" as *const u8 as *const libc::c_char,
    b"things\0" as *const u8 as *const libc::c_char,
    b"thismessage\0" as *const u8 as *const libc::c_char,
    b"tn3270\0" as *const u8 as *const libc::c_char,
    b"tip\0" as *const u8 as *const libc::c_char,
    b"tv\0" as *const u8 as *const libc::c_char,
    b"udp\0" as *const u8 as *const libc::c_char,
    b"unreal\0" as *const u8 as *const libc::c_char,
    b"urn\0" as *const u8 as *const libc::c_char,
    b"ut2004\0" as *const u8 as *const libc::c_char,
    b"vemmi\0" as *const u8 as *const libc::c_char,
    b"ventrilo\0" as *const u8 as *const libc::c_char,
    b"videotex\0" as *const u8 as *const libc::c_char,
    b"view-source\0" as *const u8 as *const libc::c_char,
    b"wais\0" as *const u8 as *const libc::c_char,
    b"webcal\0" as *const u8 as *const libc::c_char,
    b"ws\0" as *const u8 as *const libc::c_char,
    b"wss\0" as *const u8 as *const libc::c_char,
    b"wtai\0" as *const u8 as *const libc::c_char,
    b"wyciwyg\0" as *const u8 as *const libc::c_char,
    b"xcon\0" as *const u8 as *const libc::c_char,
    b"xcon-userid\0" as *const u8 as *const libc::c_char,
    b"xfire\0" as *const u8 as *const libc::c_char,
    b"xmlrpc.beep\0" as *const u8 as *const libc::c_char,
    b"xmlrpc.beeps\0" as *const u8 as *const libc::c_char,
    b"xmpp\0" as *const u8 as *const libc::c_char,
    b"xri\0" as *const u8 as *const libc::c_char,
    b"ymsgr\0" as *const u8 as *const libc::c_char,
    b"javascript\0" as *const u8 as *const libc::c_char,
    b"jdbc\0" as *const u8 as *const libc::c_char,
    b"doi\0" as *const u8 as *const libc::c_char,
];
#[no_mangle]
pub unsafe extern "C" fn strdup(mut str: *const libc::c_char) -> *mut libc::c_char {
    let n: libc::c_int = (strlen(str)).wrapping_add(1 as libc::c_int as libc::c_ulong)
        as libc::c_int;
    let mut dup: *mut libc::c_char = malloc(n as libc::c_ulong) as *mut libc::c_char;
    if !dup.is_null() {
        strcpy(dup, str);
    }
    return dup;
}
unsafe extern "C" fn unhex(mut s: *const libc::c_char) -> libc::c_int {
    if *s as libc::c_int >= '0' as i32 && *s as libc::c_int <= '9' as i32 {
        return *s as libc::c_int - '0' as i32;
    }
    if *s as libc::c_int >= 'A' as i32 && *s as libc::c_int <= 'F' as i32 {
        return *s as libc::c_int - 'A' as i32 + 10 as libc::c_int;
    }
    if *s as libc::c_int >= 'a' as i32 && *s as libc::c_int <= 'f' as i32 {
        return *s as libc::c_int - 'a' as i32 + 10 as libc::c_int;
    }
    return -(1 as libc::c_int);
}
unsafe extern "C" fn decode_percent(mut s: *mut libc::c_char) -> *mut libc::c_char {
    let mut in_0: *mut libc::c_char = s;
    let mut out: *mut libc::c_char = s;
    while *in_0 != 0 {
        if *in_0 as libc::c_int == '%' as i32 {
            in_0 = in_0.offset(1);
            let high: libc::c_int = unhex(in_0);
            if high < 0 as libc::c_int || *in_0 as libc::c_int == '\0' as i32 {
                return 0 as *mut libc::c_char;
            }
            in_0 = in_0.offset(1);
            let low: libc::c_int = unhex(in_0);
            if low < 0 as libc::c_int || *in_0 as libc::c_int == '\0' as i32 {
                return 0 as *mut libc::c_char;
            }
            *out = (high as libc::c_uint)
                .wrapping_mul(16 as libc::c_uint)
                .wrapping_add(low as libc::c_uint) as libc::c_char;
            out = out.offset(1);
            out;
            in_0 = in_0.offset(1);
            in_0;
        } else {
            let fresh0 = in_0;
            in_0 = in_0.offset(1);
            let fresh1 = out;
            out = out.offset(1);
            *fresh1 = *fresh0;
        }
    }
    *out = '\0' as i32 as libc::c_char;
    return s;
}
unsafe extern "C" fn scan_part(
    mut start: *mut libc::c_char,
    mut category: Category,
    mut delimiter1: libc::c_char,
    mut delimiter2: libc::c_char,
) -> *mut libc::c_char {
    let mut p: *mut libc::c_char = start;
    loop {
        if *p as libc::c_int == '\0' as i32
            || *p as libc::c_int == delimiter1 as libc::c_int
            || *p as libc::c_int == delimiter2 as libc::c_int
        {
            return p;
        }
        if char_cat[*p as libc::c_uchar as usize] as libc::c_uint
            & category as libc::c_uint != 0
        {
            p = p.offset(1);
            p;
        } else {
            return 0 as *mut libc::c_char
        }
    };
}
unsafe extern "C" fn scan_decimal_number(
    mut start: *mut libc::c_char,
) -> *mut libc::c_char {
    let mut p: *mut libc::c_char = start;
    while *p as libc::c_int >= '0' as i32 && *p as libc::c_int <= '9' as i32 {
        p = p.offset(1);
        p;
    }
    return if p != start { p } else { 0 as *mut libc::c_char };
}
unsafe extern "C" fn parse_query_string(
    mut begin: *mut libc::c_char,
    mut end: *mut libc::c_char,
) -> *mut url_key_value {
    let mut current_block: u64;
    let mut elements: libc::c_uint = 1 as libc::c_int as libc::c_uint;
    let mut p: *const libc::c_char = begin;
    while p != end as *const libc::c_char {
        if *p as libc::c_int == '&' as i32 || *p as libc::c_int == ';' as i32 {
            elements = elements.wrapping_add(1);
            elements;
        }
        p = p.offset(1);
        p;
    }
    let mut kv: *mut url_key_value = calloc(
        elements.wrapping_add(1 as libc::c_int as libc::c_uint) as libc::c_ulong,
        ::core::mem::size_of::<url_key_value>() as libc::c_ulong,
    ) as *mut url_key_value;
    if kv.is_null() {
        return 0 as *mut url_key_value;
    }
    let mut p_0: *mut libc::c_char = begin;
    let mut element: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    loop {
        if !(element <= elements && p_0 < end) {
            current_block = 11584701595673473500;
            break;
        }
        let mut key: *mut libc::c_char = p_0;
        let mut kv_end: *mut libc::c_char = scan_part(
            p_0,
            Query,
            '&' as i32 as libc::c_char,
            ';' as i32 as libc::c_char,
        );
        if kv_end.is_null() {
            fprintf(
                stderr,
                b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                    as *const libc::c_char,
                b"url.c\0" as *const u8 as *const libc::c_char,
                153 as libc::c_int,
                p_0,
            );
            current_block = 15328922629995699860;
            break;
        } else {
            *kv_end = '\0' as i32 as libc::c_char;
            let mut key_end: *mut libc::c_char = scan_part(
                p_0,
                Query,
                '=' as i32 as libc::c_char,
                '\0' as i32 as libc::c_char,
            );
            let has_value: bool = *key_end as libc::c_int == '=' as i32;
            *key_end = '\0' as i32 as libc::c_char;
            let ref mut fresh2 = (*kv.offset(element as isize)).key;
            *fresh2 = decode_percent(key);
            if has_value {
                let mut value: *mut libc::c_char = key_end
                    .offset(1 as libc::c_int as isize);
                let ref mut fresh3 = (*kv.offset(element as isize)).value;
                *fresh3 = decode_percent(value);
            } else {
                let ref mut fresh4 = (*kv.offset(element as isize)).value;
                *fresh4 = key_end;
            }
            p_0 = kv_end.offset(1 as libc::c_int as isize);
            element = element.wrapping_add(1);
            element;
        }
    }
    match current_block {
        11584701595673473500 => return kv,
        _ => {
            free(kv as *mut libc::c_void);
            return 0 as *mut url_key_value;
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn url_parse(mut url: *const libc::c_char) -> *mut url_data_t {
    let mut p_end: *const libc::c_char = 0 as *const libc::c_char;
    let mut protocol_end: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut is_ssh: bool = false;
    let mut second_slash: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut userinfo_end: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut hostname_end: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut path_end: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut has_query: bool = false;
    let mut has_fragment: bool = false;
    let mut current_block: u64;
    let mut data: *mut url_data_t = calloc(
        1 as libc::c_int as libc::c_ulong,
        ::core::mem::size_of::<url_data_t>() as libc::c_ulong,
    ) as *mut url_data_t;
    if data.is_null() {
        return 0 as *mut url_data_t;
    }
    let mut p: *mut libc::c_char = strdup(url);
    if p.is_null() {
        fprintf(
            stderr,
            b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                as *const libc::c_char,
            b"url.c\0" as *const u8 as *const libc::c_char,
            190 as libc::c_int,
            p,
        );
    } else {
        (*data).whole_url = p;
        p_end = p.offset(strlen(p) as isize);
        protocol_end = scan_part(
            p,
            Scheme,
            ':' as i32 as libc::c_char,
            '\0' as i32 as libc::c_char,
        );
        if protocol_end.is_null() || *protocol_end as libc::c_int == '\0' as i32 {
            fprintf(
                stderr,
                b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                    as *const libc::c_char,
                b"url.c\0" as *const u8 as *const libc::c_char,
                197 as libc::c_int,
                p,
            );
        } else {
            *protocol_end = '\0' as i32 as libc::c_char;
            (*data).protocol = p;
            is_ssh = url_is_ssh((*data).protocol);
            p = protocol_end.offset(1 as libc::c_int as isize);
            if p >= p_end as *mut libc::c_char || *p as libc::c_int != '/' as i32 {
                fprintf(
                    stderr,
                    b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                        as *const libc::c_char,
                    b"url.c\0" as *const u8 as *const libc::c_char,
                    205 as libc::c_int,
                    p,
                );
            } else {
                p = p.offset(1);
                p;
                if p >= p_end as *mut libc::c_char || *p as libc::c_int != '/' as i32 {
                    fprintf(
                        stderr,
                        b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                            as *const libc::c_char,
                        b"url.c\0" as *const u8 as *const libc::c_char,
                        209 as libc::c_int,
                        p,
                    );
                } else {
                    second_slash = p;
                    p = p.offset(1);
                    p;
                    if p >= p_end as *mut libc::c_char {
                        fprintf(
                            stderr,
                            b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                as *const libc::c_char,
                            b"url.c\0" as *const u8 as *const libc::c_char,
                            215 as libc::c_int,
                            p,
                        );
                    } else {
                        userinfo_end = scan_part(
                            p,
                            Userinfo,
                            '@' as i32 as libc::c_char,
                            '\0' as i32 as libc::c_char,
                        );
                        if !userinfo_end.is_null()
                            && *userinfo_end as libc::c_int == '@' as i32
                        {
                            *userinfo_end = '\0' as i32 as libc::c_char;
                            (*data).userinfo = p;
                            p = userinfo_end.offset(1 as libc::c_int as isize);
                        }
                        if p >= p_end as *mut libc::c_char {
                            fprintf(
                                stderr,
                                b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                    as *const libc::c_char,
                                b"url.c\0" as *const u8 as *const libc::c_char,
                                225 as libc::c_int,
                                p,
                            );
                        } else {
                            hostname_end = 0 as *mut libc::c_char;
                            if *p as libc::c_int == '[' as i32 {
                                p = p.offset(1);
                                p;
                                hostname_end = scan_part(
                                    p,
                                    IPv6Char,
                                    ']' as i32 as libc::c_char,
                                    '\0' as i32 as libc::c_char,
                                );
                                if hostname_end.is_null() {
                                    fprintf(
                                        stderr,
                                        b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                            as *const libc::c_char,
                                        b"url.c\0" as *const u8 as *const libc::c_char,
                                        234 as libc::c_int,
                                        p,
                                    );
                                    current_block = 7516573937151507373;
                                } else {
                                    *hostname_end = '\0' as i32 as libc::c_char;
                                    (*data).host = p;
                                    hostname_end = hostname_end.offset(1);
                                    hostname_end;
                                    if hostname_end < p_end as *mut libc::c_char && !is_ssh
                                        && *hostname_end as libc::c_int == ':' as i32
                                    {
                                        let mut port_end: *mut libc::c_char = scan_decimal_number(
                                            hostname_end.offset(1 as libc::c_int as isize),
                                        );
                                        if !port_end.is_null() {
                                            (*data)
                                                .port = hostname_end.offset(1 as libc::c_int as isize);
                                            p = port_end;
                                            current_block = 7252614138838059896;
                                        } else {
                                            fprintf(
                                                stderr,
                                                b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                                    as *const libc::c_char,
                                                b"url.c\0" as *const u8 as *const libc::c_char,
                                                247 as libc::c_int,
                                                p,
                                            );
                                            current_block = 7516573937151507373;
                                        }
                                    } else {
                                        p = hostname_end;
                                        current_block = 7252614138838059896;
                                    }
                                }
                            } else {
                                hostname_end = scan_part(
                                    p,
                                    (Unreserved as libc::c_int | SubDelim as libc::c_int)
                                        as Category,
                                    ':' as i32 as libc::c_char,
                                    '/' as i32 as libc::c_char,
                                );
                                if hostname_end.is_null() {
                                    fprintf(
                                        stderr,
                                        b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                            as *const libc::c_char,
                                        b"url.c\0" as *const u8 as *const libc::c_char,
                                        255 as libc::c_int,
                                        p,
                                    );
                                    current_block = 7516573937151507373;
                                } else {
                                    (*data).host = p;
                                    if !is_ssh && *hostname_end as libc::c_int == ':' as i32 {
                                        *hostname_end = '\0' as i32 as libc::c_char;
                                        let mut port_end_0: *mut libc::c_char = scan_decimal_number(
                                            hostname_end.offset(1 as libc::c_int as isize),
                                        );
                                        if !port_end_0.is_null() {
                                            (*data)
                                                .port = hostname_end.offset(1 as libc::c_int as isize);
                                            p = port_end_0;
                                            current_block = 7252614138838059896;
                                        } else {
                                            fprintf(
                                                stderr,
                                                b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                                    as *const libc::c_char,
                                                b"url.c\0" as *const u8 as *const libc::c_char,
                                                267 as libc::c_int,
                                                p,
                                            );
                                            current_block = 7516573937151507373;
                                        }
                                    } else {
                                        p = hostname_end;
                                        current_block = 7252614138838059896;
                                    }
                                }
                            }
                            match current_block {
                                7516573937151507373 => {}
                                _ => {
                                    memmove(
                                        second_slash as *mut libc::c_void,
                                        second_slash.offset(1 as libc::c_int as isize)
                                            as *const libc::c_void,
                                        p.offset_from(second_slash) as libc::c_long as libc::c_ulong,
                                    );
                                    if !((*data).userinfo).is_null() {
                                        (*data).userinfo = ((*data).userinfo).offset(-1);
                                        (*data).userinfo;
                                    }
                                    (*data).host = ((*data).host).offset(-1);
                                    (*data).host;
                                    if !((*data).port).is_null() {
                                        (*data).port = ((*data).port).offset(-1);
                                        (*data).port;
                                    }
                                    *p
                                        .offset(
                                            -(1 as libc::c_int) as isize,
                                        ) = '\0' as i32 as libc::c_char;
                                    if is_ssh as libc::c_int != 0
                                        && *p as libc::c_int == ':' as i32
                                    {
                                        p = p.offset(1);
                                        p;
                                    }
                                    path_end = scan_part(
                                        p,
                                        PCharSlash,
                                        '?' as i32 as libc::c_char,
                                        '#' as i32 as libc::c_char,
                                    );
                                    if path_end.is_null() {
                                        fprintf(
                                            stderr,
                                            b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                                as *const libc::c_char,
                                            b"url.c\0" as *const u8 as *const libc::c_char,
                                            295 as libc::c_int,
                                            p,
                                        );
                                    } else {
                                        has_query = *path_end as libc::c_int == '?' as i32;
                                        has_fragment = *path_end as libc::c_int == '#' as i32;
                                        *path_end = '\0' as i32 as libc::c_char;
                                        (*data).path = decode_percent(p);
                                        p = path_end.offset(1 as libc::c_int as isize);
                                        if has_query {
                                            let mut query_end: *mut libc::c_char = scan_part(
                                                p,
                                                Query,
                                                '#' as i32 as libc::c_char,
                                                '\0' as i32 as libc::c_char,
                                            );
                                            if !query_end.is_null() {
                                                let has_fragment_0: bool = *query_end as libc::c_int
                                                    == '#' as i32;
                                                *query_end = '\0' as i32 as libc::c_char;
                                                (*data).query = parse_query_string(p, query_end);
                                                if has_fragment_0 {
                                                    let mut fragment_end: *mut libc::c_char = scan_part(
                                                        query_end.offset(1 as libc::c_int as isize),
                                                        Fragment,
                                                        '\0' as i32 as libc::c_char,
                                                        '\0' as i32 as libc::c_char,
                                                    );
                                                    if !fragment_end.is_null() {
                                                        (*data)
                                                            .fragment = decode_percent(
                                                            query_end.offset(1 as libc::c_int as isize),
                                                        );
                                                        current_block = 6406431739208918833;
                                                    } else {
                                                        fprintf(
                                                            stderr,
                                                            b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                                                as *const libc::c_char,
                                                            b"url.c\0" as *const u8 as *const libc::c_char,
                                                            319 as libc::c_int,
                                                            p,
                                                        );
                                                        current_block = 7516573937151507373;
                                                    }
                                                } else {
                                                    current_block = 6406431739208918833;
                                                }
                                            } else {
                                                fprintf(
                                                    stderr,
                                                    b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                                        as *const libc::c_char,
                                                    b"url.c\0" as *const u8 as *const libc::c_char,
                                                    323 as libc::c_int,
                                                    p,
                                                );
                                                current_block = 7516573937151507373;
                                            }
                                        } else if has_fragment {
                                            let mut fragment_end_0: *mut libc::c_char = scan_part(
                                                p,
                                                Fragment,
                                                '\0' as i32 as libc::c_char,
                                                '\0' as i32 as libc::c_char,
                                            );
                                            if !fragment_end_0.is_null() {
                                                (*data).fragment = decode_percent(p);
                                                current_block = 6406431739208918833;
                                            } else {
                                                fprintf(
                                                    stderr,
                                                    b"ERROR %s Line %u! p=\xC2\xAB%s\xC2\xBB\n\0" as *const u8
                                                        as *const libc::c_char,
                                                    b"url.c\0" as *const u8 as *const libc::c_char,
                                                    332 as libc::c_int,
                                                    p,
                                                );
                                                current_block = 7516573937151507373;
                                            }
                                        } else {
                                            current_block = 6406431739208918833;
                                        }
                                        match current_block {
                                            7516573937151507373 => {}
                                            _ => return data,
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    url_free(data);
    return 0 as *mut url_data_t;
}
#[no_mangle]
pub unsafe extern "C" fn url_is_protocol(mut str: *const libc::c_char) -> bool {
    let count: libc::c_uint = (::core::mem::size_of::<[*const libc::c_char; 177]>()
        as libc::c_ulong)
        .wrapping_div(::core::mem::size_of::<*const libc::c_char>() as libc::c_ulong)
        as libc::c_uint;
    let mut i: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    while i < count {
        if 0 as libc::c_int == strcmp(URL_SCHEMES[i as usize], str) {
            return 1 as libc::c_int != 0;
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as libc::c_int != 0;
}
#[no_mangle]
pub unsafe extern "C" fn url_is_ssh(mut str: *const libc::c_char) -> bool {
    if 0 as libc::c_int == strcmp(str, b"ssh\0" as *const u8 as *const libc::c_char)
        || 0 as libc::c_int == strcmp(str, b"git\0" as *const u8 as *const libc::c_char)
    {
        return 1 as libc::c_int != 0;
    }
    return 0 as libc::c_int != 0;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_scheme(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut protocol: *mut libc::c_char = malloc(32 as libc::c_int as libc::c_ulong)
        as *mut libc::c_char;
    if protocol.is_null() {
        return 0 as *mut libc::c_char;
    }
    sscanf(url, b"%[^://]\0" as *const u8 as *const libc::c_char, protocol);
    if url_is_protocol(protocol) {
        return protocol;
    }
    free(protocol as *mut libc::c_void);
    return 0 as *mut libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_userinfo(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).userinfo).is_null()
    {
        strdup((*data).userinfo)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_hostname(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).host).is_null() {
        strdup((*data).host)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_host(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).host).is_null() {
        strdup((*data).host)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_pathname(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).path).is_null() {
        strdup((*data).path)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_path(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).path).is_null() {
        strdup((*data).path)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_query_value(
    mut url: *const url_data_t,
    mut key: *const libc::c_char,
) -> *const libc::c_char {
    if ((*url).query).is_null() {
        return 0 as *const libc::c_char;
    }
    let mut kv: *const url_key_value = (*url).query;
    while !((*kv).key).is_null() {
        if strcmp((*kv).key, key) == 0 as libc::c_int {
            return (*kv).value;
        }
        kv = kv.offset(1);
        kv;
    }
    return 0 as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_fragment(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).fragment).is_null()
    {
        strdup((*data).fragment)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_get_port(
    mut url: *const libc::c_char,
) -> *mut libc::c_char {
    let mut data: *mut url_data_t = url_parse(url);
    let mut out: *mut libc::c_char = if !data.is_null() && !((*data).port).is_null() {
        strdup((*data).port)
    } else {
        0 as *mut libc::c_char
    };
    url_free(data);
    return out;
}
#[no_mangle]
pub unsafe extern "C" fn url_inspect(mut url: *const libc::c_char) {
    url_data_inspect(url_parse(url));
}
#[no_mangle]
pub unsafe extern "C" fn url_data_inspect(mut data: *const url_data_t) {
    printf(b"#url =>\n\0" as *const u8 as *const libc::c_char);
    if !((*data).protocol).is_null() {
        printf(
            b"    .protocol: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).protocol,
        );
    } else {
        printf(b"    .protocol: (NULL)\n\0" as *const u8 as *const libc::c_char);
    }
    if !((*data).host).is_null() {
        printf(
            b"    .host: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).host,
        );
    } else {
        printf(b"    .host: (NULL)\n\0" as *const u8 as *const libc::c_char);
    }
    if !((*data).userinfo).is_null() {
        printf(
            b"    .userinfo: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).userinfo,
        );
    } else {
        printf(b"    .userinfo: (NULL)\n\0" as *const u8 as *const libc::c_char);
    }
    if !((*data).host).is_null() {
        printf(
            b"    .host: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).host,
        );
    } else {
        printf(b"    .host: (NULL)\n\0" as *const u8 as *const libc::c_char);
    }
    if !((*data).port).is_null() {
        printf(
            b"    .port: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).port,
        );
    } else {
        printf(b"    .port: (NULL)\n\0" as *const u8 as *const libc::c_char);
    }
    if !((*data).path).is_null() {
        printf(
            b"    .path: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).path,
        );
    } else {
        printf(b"    .path: (NULL)\n\0" as *const u8 as *const libc::c_char);
    }
    if !((*data).query).is_null() {
        let mut nr: libc::c_uint = 0 as libc::c_int as libc::c_uint;
        while !((*((*data).query).offset(nr as isize)).key).is_null() {
            printf(
                b"    .query[%u]: \"%s\" -> \0" as *const u8 as *const libc::c_char,
                nr,
                (*((*data).query).offset(nr as isize)).key,
            );
            if !((*((*data).query).offset(nr as isize)).value).is_null() {
                printf(
                    b"\"%s\"\n\0" as *const u8 as *const libc::c_char,
                    (*((*data).query).offset(nr as isize)).value,
                );
            } else {
                printf(b"(NULL)\n\0" as *const u8 as *const libc::c_char);
            }
            nr = nr.wrapping_add(1);
            nr;
        }
    }
    if !((*data).fragment).is_null() {
        printf(
            b"    .fragment: \"%s\"\n\0" as *const u8 as *const libc::c_char,
            (*data).fragment,
        );
    } else {
        printf(b"    .fragment: (NULL)\n\0" as *const u8 as *const libc::c_char);
    };
}
#[no_mangle]
pub unsafe extern "C" fn url_free(mut data: *mut url_data_t) {
    if data.is_null() {
        return;
    }
    free((*data).whole_url as *mut libc::c_void);
    free((*data).query as *mut libc::c_void);
    free(data as *mut libc::c_void);
}
