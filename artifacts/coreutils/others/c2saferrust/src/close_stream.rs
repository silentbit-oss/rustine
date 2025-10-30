
use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn rpl_fclose(stream: *mut FILE) -> libc::c_int;
    fn ferror_unlocked(__stream: *mut FILE) -> libc::c_int;
    fn __errno_location() -> *mut libc::c_int;
    fn __fpending(__fp: *mut FILE) -> size_t;
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
#[no_mangle]
pub fn close_stream(stream: *mut _IO_FILE) -> libc::c_int {
    let some_pending: bool = unsafe { __fpending(stream) != 0 };
    let prev_fail: bool = unsafe { ferror_unlocked(stream) != 0 };
    let fclose_fail: bool = unsafe { rpl_fclose(stream) != 0 };

    if prev_fail
        || fclose_fail && (some_pending || unsafe { *__errno_location() != 9 })
    {
        if !fclose_fail {
            unsafe { *__errno_location() = 0 };
        }
        return -1;
    }
    return 0;
}

